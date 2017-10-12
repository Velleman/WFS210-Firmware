#include "wfs210/wifi.h"
#include "wfs210/wfs210.h"

WIFI	wifi;


VOID InitWifiBuffers(VOID)
{
	InitWifiCmdReplyParser(&wifi.cmd_reply_parser);
	InitParser(&wifi.parser);
}

VOID ClearApInUse(VOID)
{
	int ch;

	memset(wifi.access_point, 0, sizeof(wifi.access_point));

	// init wifi channel levels
	for (ch = 0; ch < 13; ++ch) wifi.access_point[ch].level = -128;

	wifi.cmd_out.status.end_scan = FALSE;
}

VOID ResetWifi(VOID)
{
	mWifiReset();
	__delay_us(1000);
	InitWifiBuffers();
	wifi.cmd_out.status.run = FALSE;
	wifi.cmd_timeout_cntr = 0;
	mReleaseWifiReset();
}

VOID ExitWifiCmdMode(VOID)
{
	wifi.cmd_out.status.mode = FALSE;
	wifi.cmd_out.status.ap = TRUE;
	wifi.cmd_out.sm = SM_IDLE;
	wifi.cmd_timeout_cntr = 0;
	mStopWifiCmdReplyTimer();
}


VOID WifiInit(VOID)
{
	BYTE c;

	// Initialize Wifi (UART) pins
	mInitWifiPins();

	// reset wifi module
	ResetWifi();

	// Initialize UART1 at High Speed (460800 baud) //1100000 baud)
	OpenUART1(HS_UARTMODE, HS_UARTSTA, HS_BRGVAL);

	// Wifi module configured as access point
	wifi.cmd_out.status.ap = TRUE;

	// enter command mode
	wifi.cmd_out.status.mode = TRUE;
	wifi.cmd_out.sm = SM_START_GET_SETTINGS;
	wifi.cmd_out.status.empty = TRUE;

	// read two bytes from wifi powerup message
	while (!DataRdyUART1());
	c = (BYTE)ReadUART1();
	while (!DataRdyUART1());
	c = (BYTE)ReadUART1();


	// check baudrate mismatch
	if (c == 0)
	{ // wifi module not yet configured
		CloseUART1();

		// reset wifi module
		ResetWifi();

		// Initialize UART1 (9600 baud)
		OpenUART1(UARTMODE, UARTSTA, BRGVAL);

		// Wifi module is not configured as access point
		wifi.cmd_out.status.ap = FALSE;

		// enter command mode
		wifi.cmd_out.status.mode = TRUE;
		wifi.cmd_out.sm = SM_RESET;
		wifi.cmd_out.status.empty = TRUE;
	}
	else
	{
		if (!mGetFactoryDefaultsPB())
		{ // restore factory defaults if button is pressed
			memset(wifi.ssid, 0, sizeof(wifi.ssid));
			strcpy(wifi.ssid, DEFAULT_WIFI_SSID);
			memset(wifi.password, 0, sizeof(wifi.password));
			strcpy(wifi.password, DEFAULT_WIFI_PASSWORD);
			wifi.channel = DEFAULT_WIFI_CHANNEL;
			wifi.cmd_out.status.mode = TRUE;
			wifi.cmd_out.sm = SM_START_CUSTOM_SETTINGS;
			wifi.cmd_out.status.empty = TRUE;
		}
	}

	memcpy(wifi.build, BUILD, sizeof(wifi.build));
	memset(wifi.version, 0, sizeof(wifi.version));
}



VOID SetWifiDebugMode(BOOL debug)
{
	wifi.debug_out.mode = debug;
}


BOOL GetWifiDebugMode(VOID)
{
	return wifi.debug_out.mode;
}


VOID SetWifiCmdMode(BOOL mode)
{
	wifi.cmd_out.status.mode = mode;
	InitWifiBuffers();
}

BOOL WifiConnected(VOID)
{
	return mWifiTcpOpen();
}

BOOL WifiTxReady(VOID)
{
	return (wifi.out.sm == SM_IDLE);
}


VOID FeedWifiDebugOut(BYTE *data, WORD size)
{
	if ((sizeof(wifi.debug_out.data) - 1 - wifi.debug_out.size) < size) size = sizeof(wifi.debug_out.data) - 1 - wifi.debug_out.size;
	if (size > 0) memcpy((void *)&wifi.debug_out.data[wifi.debug_out.size], (const void *)data, size);
	wifi.debug_out.size += size;
	wifi.debug_out.bytes_to_send += size;
}


VOID WifiTxFrag(WIFI_OUT *packet)
{
	BYTE *pdst;
	WORD nr;

	if (packet->bytes_to_send > packet->size)
	{ // fragmentation
		// number of samples send by previous fragment
		nr = packet->size - WFS210_PACKET_HEADER_SIZE - WFS210_PACKET_SETTINGS_SIZE - 2;

		// total number of bytes not yet transmitted
		packet->bytes_to_send -= nr;

		// load offset
		packet->offset += nr;

		// load size
		if (packet->bytes_to_send > WIFI_PACKET_MAX_SIZE)
			packet->size = WIFI_PACKET_MAX_SIZE;
		else packet->size = packet->bytes_to_send;

		// load sample data
		nr = packet->size - WFS210_PACKET_HEADER_SIZE - WFS210_PACKET_SETTINGS_SIZE - 2;
		memcpy((void *)&packet->data[WFS210_PACKET_SAMPLE_BUFFER_INDEX], (const void *)packet->pfrag, nr);
		packet->pfrag += nr;	// pointer to next fragment

		// load checksum
		pdst = &packet->data[packet->size - WFS210_PACKET_HEADER_SIZE - 2];
		*pdst++ = CalcChecksum((BYTE *)&packet->stx, packet->size - 2);

		// load ETX
		*pdst = WFS210_ETX;

		// start transmit
		packet->sm = SM_SEND;
		packet->cntr = packet->size;
	}
	else
	{	// end of fragmentation
		packet->bytes_to_send = 0;
		packet->sm = SM_IDLE;
	}
}


VOID WifiTransmit(WFS210_OUT_PACKET* packet)
{

	BYTE *psrc, *pdst;
	WORD nr;

	// load STX
	wifi.out.stx = WFS210_STX;

	// load command
	wifi.out.cmd = packet->cmd;

	// load size
	if (packet->size > WIFI_PACKET_MAX_SIZE)
		wifi.out.size = WIFI_PACKET_MAX_SIZE;
	else wifi.out.size = packet->size;

	// load offset
	wifi.out.offset = packet->offset;

	// load settings
	memcpy((void *)wifi.out.data, (const void *)packet->data, WFS210_PACKET_SETTINGS_SIZE);

	// load data
	psrc = &packet->data[WFS210_PACKET_SAMPLE_BUFFER_INDEX];
	pdst = &wifi.out.data[WFS210_PACKET_SAMPLE_BUFFER_INDEX];
	nr = wifi.out.size - WFS210_PACKET_HEADER_SIZE - WFS210_PACKET_SETTINGS_SIZE - 2;
	memcpy((void *)pdst, (const void *)psrc, nr);
	wifi.out.pfrag = psrc + nr;	// pointer to next fragment

	// load checksum
	pdst = &wifi.out.data[wifi.out.size - WFS210_PACKET_HEADER_SIZE - 2];
	*pdst++ = CalcChecksum((BYTE *)&wifi.out.stx, wifi.out.size - 2);

	// load ETX
	*pdst = WFS210_ETX;

	// start transmit
	wifi.out.bytes_to_send = packet->size;
	wifi.out.cntr = wifi.out.size;
	wifi.out.sm = SM_SEND;
}


void StrToUpper(char *str)
{
	while (*str)
	{
		*str = toupper(*str);
		str++;
	}
}


VOID WifiCmdReplyReceive(char *cmd_reply)
{
	char *str;
	int	i, level;

	// check prompt "<x.xx> " received
    if (cmd_reply[0]== '<')
	{
		wifi.cmd_out.status.accept = TRUE;
		if (wifi.cmd_out.sm == SM_FIRST_SCAN)
		{ // load wifi firmware version
			str = strtok(cmd_reply, ">");
			strcpy(wifi.version , ++str);
		}
		return;
	}

	// detect end of startup message
	if ((wifi.cmd_out.sm == SM_START_CMD_MODE) || (wifi.cmd_out.sm == SM_START_SETTINGS_CMD_MODE) ||
		(wifi.cmd_out.sm == SM_CHANNEL_RESET_READY) || (wifi.cmd_out.sm == SM_START_CUSTOM_SETTINGS_CMD_MODE) ||
		(wifi.cmd_out.sm == SM_CUSTOM_RESET_DELAY) || (wifi.cmd_out.sm == SM_CUSTOM_SETTINGS_RESET_READY) ||
		(wifi.cmd_out.sm == SM_START_SLEEP_CMD_MODE)
	   )
	{
		// check wifi module running
		if (wifi.cmd_out.status.ap)
		{ // access point mode running?
			if (strstr(cmd_reply, "DHCP") != NULL) {wifi.cmd_out.status.run = TRUE; return;}
			// workaround for beta release version 4.10c
			if (strstr(cmd_reply, "DCHP") != NULL) {wifi.cmd_out.status.run = TRUE; return;}

		}
		else if (strstr(cmd_reply, "*READY*") != NULL) {wifi.cmd_out.status.run = TRUE; return;}
	}

	// check wifi module reboot
	if (wifi.cmd_out.sm == SM_EXIT_READY)
	{
		if (strstr(cmd_reply, "*Reboot*") != NULL) {wifi.cmd_out.status.run = TRUE; return;}
	}

	if (wifi.cmd_out.sm == SM_FIRST_SCAN)
	{
	 	// search delimiter '='
		if (strchr(cmd_reply, '=') != NULL)
		{
			str = strtok(cmd_reply, "=");
			StrToUpper(str);
			if (strcmp(str, "SSID") == 0) strcpy(wifi.ssid, strtok(NULL, "\r"));
			else if (strcmp(str, "CHAN") == 0) wifi.channel = atoi(strtok(NULL, "\r"));
			else if (strcmp(str, "PASSPHRASE") == 0) strcpy(wifi.password, strtok(NULL, "\r"));
		}
		return;
	}

	if ((wifi.cmd_out.sm == SM_SECOND_SCAN) || (wifi.cmd_out.sm == SM_CHECK_SCAN))
	{
		if (strstr(cmd_reply, "END") != NULL) {wifi.cmd_out.status.end_scan = TRUE; return;}

		// search delimiter ','
		if (strchr(cmd_reply, ',') != NULL)
		{
			str = strtok(cmd_reply, ",");
			i = atoi(strtok(NULL, ",")) - 1;
			if (wifi.access_point[i].used)
			{
				level = atoi(strtok(NULL, ","));
				if (wifi.access_point[i].level < level) wifi.access_point[i].level = level;
			}
			else
			{
				wifi.access_point[i].used = TRUE;
				wifi.access_point[i].level = atoi(strtok(NULL, ","));
			}
		}
	}
}


VOID WifiReadTasks(VOID)
{
	static WFS210_IN_PACKET packet;
	WORD num_bytes_read;

	num_bytes_read = 0;

	// read uart rx buffer
	while (DataRdyUART1()) wifi.buffer_in[num_bytes_read++] = (BYTE)ReadUART1();

	// clear uart overrun error
	if (mUART1OERR()) mClrUART1OERR();

	// check uart rx timeout into cmd mode
	if (wifi.cmd_out.status.mode)
	{
		if ((num_bytes_read == 0) && (!WifiCmdParserEmty(&wifi.cmd_reply_parser)) && (wifi.cmd_timeout_cntr > 5))
		{
			wifi.buffer_in[0] = '\n';
			mRestartWifiCmdReplyTimer();
			FeedWifiCmdReplyParser(&wifi.cmd_reply_parser, (BYTE *)wifi.buffer_in, 1);
			while (ParseWifiCmdReply(&wifi.cmd_reply_parser, wifi.cmd_reply))
			{
				WifiCmdReplyReceive(wifi.cmd_reply);
			}
		}
	}

	if(num_bytes_read != 0)
	{
		// debug event
		WifiReceiveRaw((BYTE *)wifi.buffer_in, num_bytes_read);

		if (wifi.cmd_out.status.mode)
		 { // cmd mode
			mRestartWifiCmdReplyTimer();
			FeedWifiCmdReplyParser(&wifi.cmd_reply_parser, (BYTE *)wifi.buffer_in, num_bytes_read);
			while (ParseWifiCmdReply(&wifi.cmd_reply_parser, wifi.cmd_reply))
			{
				WifiCmdReplyReceive(wifi.cmd_reply);
			}
		}
		else
		{ // packet mode
			FeedParser(&wifi.parser, (BYTE *)wifi.buffer_in, num_bytes_read);
			while (ParsePacket(&wifi.parser, &packet))
			{
				WifiReceive(&packet);	// event
			}
		}
	}
}

VOID WifiLoadCmd(const char *cmd)
{
	wifi.cmd_timeout_cntr = 0;
	wifi.cmd_out.status.accept = FALSE;
	wifi.cmd_out.pos = 0;
	wifi.cmd_out.status.empty = FALSE;
	strcpy(wifi.cmd_out.data, cmd);
	wifi.cmd_out.sm++;
}

BOOL WifiRunning(VOID)
{
	return wifi.cmd_out.status.run;
}

BOOL WifiCmdAccept(VOID)
{
	return wifi.cmd_out.status.accept;
}

BOOL WifiScanDone(VOID)
{
	return wifi.cmd_out.status.end_scan;
}

VOID WifiCmdTimeoutCheck(VOID)
{
	if (mGetWifiCmdReplyTimerIntFlag())
	{
		mRestartWifiCmdReplyTimer();
		wifi.cmd_timeout_cntr++;
		if ((wifi.cmd_timeout_cntr > 20) && ((wifi.cmd_out.sm > SM_GET_SETTINGS) && (wifi.cmd_out.sm < SM_START_CUSTOM_SETTINGS)))
		{
			ExitWifiCmdMode();
			ResetWifi();
		}
	}
}


int WeakestWifiChannel(VOID)
{
	int	i, weakest_ch = 0, weakest_weight = 1000;

	// calculate weight levels
	for (i = 0; i < 13; i++)
	{
		wifi.access_point[i].weight = 0;

		if (i > 2)
			wifi.access_point[i].weight += (wifi.access_point[i-3].level + 128) >> 3;
		if (i > 1)
			wifi.access_point[i].weight += (wifi.access_point[i-2].level + 128) >> 2;
		if (i > 0)
			wifi.access_point[i].weight += (wifi.access_point[i-1].level + 128) >> 1;
		wifi.access_point[i].weight += wifi.access_point[i].level + 128;
		if (i < 12)
			wifi.access_point[i].weight += (wifi.access_point[i+1].level + 128) >> 1;
		if (i < 11)
			wifi.access_point[i].weight +=	(wifi.access_point[i+2].level + 128) >> 2;
		if (i < 10)
			wifi.access_point[i].weight +=	(wifi.access_point[i+3].level + 128) >> 2;

	}

	// search weakest channel
	for (i = 0; i < 13; i++)
	{
		// search weakest channel in use
		if (wifi.access_point[i].weight < weakest_weight)
		{
			weakest_ch = i;
			weakest_weight = wifi.access_point[i].weight;
		}
	}

	return ++weakest_ch;
}


BOOL WifiChannelFree(VOID)
{
	int	i, free_ch = 0, weakest_ch = 0, weakest_level = 0;
	BOOL free = TRUE;

	// check channel in use
	if (wifi.access_point[wifi.channel - 1].used)
	{
		free = FALSE;

		for (i = 0; i < 13; i++)
		{
			// search first free channel
			if ((free_ch == 0) && (!wifi.access_point[i].used)) free_ch = i + 1;

			// search weakest channel in use
			if (wifi.access_point[i].used && (wifi.access_point[i].level < weakest_level))
			{
				weakest_ch = i + 1;
				weakest_level = wifi.access_point[i].level;
			}
		}

		if (free_ch != 0) wifi.channel = free_ch;
                else wifi.channel = weakest_ch;
	}
	
	return free;
}


VOID WifiCmdTask(VOID)
{
	int ch;
	char *ptr;
	static char str[64];

	switch (wifi.cmd_out.sm)
	{
		case SM_IDLE:
			break;

		// configure wifi module
		case SM_RESET:
			ResetWifi();
			wifi.cmd_out.sm++;
			break;
		case SM_START_CMD_MODE:
			if (WifiRunning())
			{
				mRestartWifiCmdReplyTimer();
				wifi.cmd_out.sm++;
			}
			break;
		case SM_SET_CMD_MODE:
			if (mGetWifiCmdReplyTimerIntFlag())
			{
				WifiLoadCmd(ENTER_WIFI_CMD_MODE);
				wifi.cmd_out.status.run = FALSE;
				mRestartWifiCmdReplyTimer();
			}
			break;
		case SM_SET_FACTORY_DEFAULTS: 
			if (mGetWifiCmdReplyTimerIntFlag()) WifiLoadCmd(SET_WIFI_FACTORY_DEFAULTS);
			break;
		case SM_SET_TX_POWER:
			if (WifiCmdAccept()) WifiLoadCmd(SET_WIFI_TX_POWER);
			break;
		case SM_SET_WIFI_ACCESS_POINT:
			if (WifiCmdAccept()) WifiLoadCmd(SET_WIFI_ACCESS_POINT);
			break;
		case SM_SET_WIFI_SSID:
			if (WifiCmdAccept())
			{
				memset(wifi.ssid, 0, sizeof(wifi.ssid));
				strcpy(wifi.ssid, DEFAULT_WIFI_SSID);
				strcpy(str, SET_WIFI_SSID);
				strcat(str, wifi.ssid);
				strcat(str, "\r\n");
				WifiLoadCmd(str);
			}
			break;
		case SM_SET_WIFI_SECURITY:
			if (WifiCmdAccept())
			{
				wifi.wpa2 = FALSE;
				WifiLoadCmd(SET_WIFI_SECURITY_OPEN);
			}
			break;
        case SM_SET_WIFI_PASSWORD:
			if (WifiCmdAccept())
			{
				memset(wifi.password, 0, sizeof(wifi.password));
				strcpy(wifi.password, DEFAULT_WIFI_PASSWORD);
				strcpy(str, SET_WIFI_PASSWORD);
				strcat(str, wifi.password);
				strcat(str, "\r\n");
				WifiLoadCmd(str);
			}
			break;
		case SM_SET_WIFI_AP_SSID:
			if (WifiCmdAccept())
			{
				memset(wifi.ssid, 0, sizeof(wifi.ssid));
				strcpy(wifi.ssid, DEFAULT_WIFI_SSID);
				strcpy(str, SET_WIFI_AP_SSID);
				strcat(str, wifi.ssid);
				strcat(str, "\r\n");
				WifiLoadCmd(str);
			}
			break;
//        case SM_SET_WIFI_AP_PASSWORD:
//			if (WifiCmdAccept())
//			{
//				strcpy(str, SET_WIFI_AP_PASSWORD);
//				strcat(str, wifi.password);
//				strcat(str, "\r\n");
//				WifiLoadCmd(str);
//			}
			break;
		case SM_SET_WIFI_DHCP:
			if (WifiCmdAccept()) WifiLoadCmd(SET_WIFI_DHCP);
			break;
		case SM_SET_WIFI_IP_ADDRESS:
			if (WifiCmdAccept()) WifiLoadCmd(SET_WIFI_IP_ADDRESS);
			break;
		case SM_SET_WIFI_NETMASK:
			if (WifiCmdAccept()) WifiLoadCmd(SET_WIFI_NETMASK);
			break;
		case SM_SET_WIFI_GATEWAY:
			if (WifiCmdAccept()) WifiLoadCmd(SET_WIFI_GATEWAY);
			break;
		case SM_SET_WIFI_LOCAL_PORT:
			if (WifiCmdAccept()) WifiLoadCmd(SET_WIFI_LOCAL_PORT);
			break;
		case SM_SET_WIFI_HOST_PORT:
			if (WifiCmdAccept()) WifiLoadCmd(SET_WIFI_HOST_PORT);
			break;
		case SM_SET_WIFI_TCP_PROTOCOL:
			if (WifiCmdAccept()) WifiLoadCmd(SET_WIFI_TCP_PROTOCOL);
			break;
		case SM_SET_WIFI_IP_HOST:
			if (WifiCmdAccept()) WifiLoadCmd(SET_WIFI_IP_HOST);
			break;
		case SM_SET_WIFI_BROADCAST_INTERVAL:
			if (WifiCmdAccept()) WifiLoadCmd(SET_WIFI_BROADCAST_INTERVAL);
			break;
		case SM_SET_WIFI_FLUSH_TIME:
			if (WifiCmdAccept()) WifiLoadCmd(SET_WIFI_FLUSH_TIME);
			break;
		case SM_SET_WIFI_FLUSH_SIZE:
			if (WifiCmdAccept()) WifiLoadCmd(SET_WIFI_FLUSH_SIZE);
			break;
		case SM_SET_WIFI_GPIO:
			if (WifiCmdAccept()) WifiLoadCmd(SET_WIFI_GPIO);
			break;
		case SM_SET_WIFI_BAUDRATE:
			if (WifiCmdAccept()) WifiLoadCmd(SET_WIFI_BAUDRATE);
			break;
		case SM_SET_WIFI_FLOW:
			if (WifiCmdAccept()) WifiLoadCmd(SET_WIFI_FLOW);
			break;
		case SM_SET_WIFI_CHANNEL:
			if (WifiCmdAccept())
			{
				wifi.channel = DEFAULT_WIFI_CHANNEL;
				strcpy(str, SET_WIFI_CHANNEL);
				itoa(&str[strlen(str)], wifi.channel, 10);
				strcat(str, "\r\n");
				WifiLoadCmd(str);
			}
			break;
		case SM_STORE_WIFI_SETTINGS:
			if (WifiCmdAccept()) WifiLoadCmd(STORE_WIFI_SETTINGS);
			break;
		case SM_RESET_WIFI:
			if (WifiCmdAccept())
			{
				wifi.cmd_out.status.run = FALSE;
				mWifiReset();
				InitWifiBuffers();
				wifi.cmd_timeout_cntr = 0;
				CloseUART1();
				mRestartWifiCmdReplyTimer();
				wifi.cmd_out.sm++;
			}
			break;
		case SM_RESET_READY:
			if (mGetWifiCmdReplyTimerIntFlag())
			{
				OpenUART1(HS_UARTMODE, HS_UARTSTA, HS_BRGVAL); // Initialize UART1 at High Speed (460800 baud)
				mReleaseWifiReset();
				mRestartWifiCmdReplyTimer();
				wifi.cmd_out.sm = SM_START_SETTINGS_CMD_MODE;
			}
			break;

		// get wifi settings
		case SM_START_GET_SETTINGS: 
			if (scope_settings.status.flags.low_voltage) ExitWifiCmdMode();
			else
			{
				ResetWifi();
				wifi.cmd_out.sm++;
			}
			break;
		case SM_START_SETTINGS_CMD_MODE:
			if (WifiRunning())
			{
				mRestartWifiCmdReplyTimer();
				wifi.cmd_out.sm++;
			}
			break;
		case SM_SET_SETTINGS_CMD_MODE:
			if (mGetWifiCmdReplyTimerIntFlag())
			{
				WifiLoadCmd(ENTER_WIFI_CMD_MODE);
				wifi.cmd_out.status.run = FALSE;
				mRestartWifiCmdReplyTimer();
			}
			break;
		case SM_GET_SETTINGS:
			if (mGetWifiCmdReplyTimerIntFlag()) WifiLoadCmd(GET_WIFI_SETTINGS);
			break;
		case SM_FIRST_SCAN:
			if (WifiCmdAccept()) WifiLoadCmd(SCAN_WIFI);
			break;
		case SM_SECOND_SCAN:
			if (WifiScanDone())
			{
				ClearApInUse();
				WifiLoadCmd(SCAN_WIFI);
			}
			break;
		case SM_CHECK_SCAN:
			if (WifiScanDone())
			{
				ch = WeakestWifiChannel();
				if (ch == wifi.channel) wifi.cmd_out.sm++;
				else
				{
					wifi.channel = ch;
					wifi.cmd_out.status.accept = TRUE;
					wifi.cmd_out.sm = SM_CUSTOM_CHANNEL;
				}

				if (WifiChannelFree()) wifi.cmd_out.sm++;
				else
				{
					wifi.cmd_out.status.accept = TRUE;
					wifi.cmd_out.sm = SM_CUSTOM_CHANNEL;
				}
                                wifi.cmd_out.sm = SM_CUSTOM_CHANNEL;
			}
			break;
		case SM_EXIT:
			wifi.cmd_out.status.run = FALSE;
			WifiLoadCmd(REBOOT_WIFI);
			break;
		case SM_EXIT_READY:
			if (WifiRunning()) ExitWifiCmdMode();
			break;

		// set free channel
		case SM_SET_FREE_CHANNEL:
			strcpy(str, SET_WIFI_CHANNEL);
			itoa(&str[strlen(str)], wifi.channel, 10);
                        //itoa(&str[strlen(str)], 6, 10);
			strcat(str, "\r\n");
			WifiLoadCmd(str);
			break;
		case SM_STORE_CHANNEL:
			if (WifiCmdAccept()) WifiLoadCmd(STORE_WIFI_SETTINGS);
			break;
		case SM_CHANNEL_RESET:
			if (WifiCmdAccept())
			{
				wifi.cmd_out.status.run = FALSE;
				ResetWifi();
				wifi.cmd_out.sm++;
			}
			break;
		case SM_CHANNEL_RESET_READY:
			if (WifiRunning()) ExitWifiCmdMode();
			break;

		// set custom settings (SSID, password & channel)
		case SM_START_CUSTOM_SETTINGS:
			if (scope_settings.status.flags.low_voltage) ExitWifiCmdMode();
			else
			{
				ResetWifi();
				wifi.cmd_out.sm++;
			}
			break;
		case SM_START_CUSTOM_SETTINGS_CMD_MODE:
			if (WifiRunning())
			{
				mRestartWifiCmdReplyTimer();
				wifi.cmd_out.sm++;
			}
			break;
		case SM_CUSTOM_SETTINGS_CMD_MODE:
			if (mGetWifiCmdReplyTimerIntFlag())
			{
				WifiLoadCmd(ENTER_WIFI_CMD_MODE);
				wifi.cmd_out.status.run = FALSE;
				mRestartWifiCmdReplyTimer();
			}
			break;
		case SM_CUSTOM_BAUDRATE_9600:
			wifi.cmd_out.sm++;
 //         if (mGetWifiCmdReplyTimerIntFlag()) WifiLoadCmd(SET_WIFI_BAUDRATE_9600);
			break;
		case SM_CUSTOM_NO_FLOW:
			wifi.cmd_out.sm++;
//			if (WifiCmdAccept()) WifiLoadCmd(SET_WIFI_NO_FLOW);
			break;
		case SM_CUSTOM_STORE:
			wifi.cmd_out.sm++;
//			if (WifiCmdAccept()) WifiLoadCmd(STORE_WIFI_SETTINGS);
			break;
		case SM_CUSTOM_RESET:
			wifi.cmd_out.sm++;
//			if (WifiCmdAccept())
//			{
//				wifi.cmd_out.status.run = FALSE;
//				mWifiReset();
//				InitWifiBuffers();
//				wifi.cmd_timeout_cntr = 0;
//				CloseUART1();
//				mRestartWifiCmdReplyTimer();
//				wifi.cmd_out.sm++;
//			}
			break;
		case SM_CUSTOM_RESET_READY:
			wifi.cmd_out.sm++;
//			if (mGetWifiCmdReplyTimerIntFlag())
//			{
//				OpenUART1(UARTMODE, UARTSTA, BRGVAL); // Initialize UART1 (9600 baud)
//				mReleaseWifiReset();
//				mRestartWifiCmdReplyTimer();
//				wifi.cmd_out.sm++;
//			}
			break;
		case SM_CUSTOM_RESET_DELAY:
			wifi.cmd_out.sm++;
//			if (WifiRunning())
//			{
//				mRestartWifiCmdReplyTimer();
//				wifi.cmd_out.sm++;
//			}
//			break;
		case SM_CUSTOM_CMD_MODE:
			wifi.cmd_out.sm++;
//			if (mGetWifiCmdReplyTimerIntFlag())
//			{
//				WifiLoadCmd(ENTER_WIFI_CMD_MODE);
//				wifi.cmd_out.status.run = FALSE;
//				mRestartWifiCmdReplyTimer();
//			}
			break;
		case SM_CUSTOM_SSID:
			if (mGetWifiCmdReplyTimerIntFlag())
			{
				strcpy(str, SET_WIFI_SSID);
				strcat(str, wifi.ssid);
				strcat(str, "\r\n");
				WifiLoadCmd(str);
			}
			break;
   		case SM_CUSTOM_AP_SSID:
            if (strcmp(wifi.version, "4.00") == 0) wifi.cmd_out.sm++;
            else if (WifiCmdAccept())
			{
				strcpy(str, SET_WIFI_AP_SSID);
				strcat(str, wifi.ssid);
				strcat(str, "\r\n");
				WifiLoadCmd(str);
			}
			break;
//        case SM_CUSTOM_PASSWORD:
//			wifi.cmd_out.sm++;
//            if (WifiCmdAccept())
//      	{
//				strcpy(str, SET_WIFI_PASSWORD);
//				strcat(str, wifi.password);
//				strcat(str, "\r\n");
//				WifiLoadCmd(str);
//			}
//			break;
		case SM_CUSTOM_AP_PASSWORD:
			wifi.cmd_out.sm +=2;
//			if (WifiCmdAccept())
//			{
//				strcpy(str, SET_WIFI_AP_PASSWORD);
//				strcat(str, wifi.password);
//				strcat(str, "\r\n");
//				WifiLoadCmd(str);
//			}
			break;
		case SM_CUSTOM_CHANNEL:
			if (WifiCmdAccept())
			{
				strcpy(str, SET_WIFI_CHANNEL);
				itoa(&str[strlen(str)], wifi.channel, 10);
                                //itoa(&str[strlen(str)], 6, 10);
				strcat(str, "\r\n");
				WifiLoadCmd(str);
			}
			break;
		case SM_CUSTOM_BAUDRATE_460K:
			wifi.cmd_out.sm++;
//			if (WifiCmdAccept()) WifiLoadCmd(SET_WIFI_BAUDRATE);
			break;
		case SM_CUSTOM_FLOW:
			wifi.cmd_out.sm++;
//			if (WifiCmdAccept()) WifiLoadCmd(SET_WIFI_FLOW);
			break;
		case SM_CUSTOM_SETTINGS_SAVE:
			if (WifiCmdAccept()) WifiLoadCmd(STORE_WIFI_SETTINGS);
			break;
		case SM_CUSTOM_SETTINGS_RESET:
			if (WifiCmdAccept())
			{
				wifi.cmd_out.status.run = FALSE;
//				CloseUART1();
//				OpenUART1(HS_UARTMODE, HS_UARTSTA, HS_BRGVAL); // Initialize UART1 at High Speed (460800 baud)
				ResetWifi();
				wifi.cmd_out.sm++;
			}
			break;
		case SM_CUSTOM_SETTINGS_RESET_READY:
			if (WifiRunning()){
                            ExitWifiCmdMode();
                            //wifi.cmd_out.sm = SM_EXIT;
                        }
			break;
		// enter sleep mode
		case SM_START_SLEEP:
			ResetWifi();
			wifi.cmd_out.sm++;
			break;
		case SM_START_SLEEP_CMD_MODE:
			if (WifiRunning())
			{
				mRestartWifiCmdReplyTimer();
				wifi.cmd_out.sm++;
			}
			break;
		case SM_SLEEP_CMD_MODE:
			if (mGetWifiCmdReplyTimerIntFlag())
			{
				WifiLoadCmd(ENTER_WIFI_CMD_MODE);
				wifi.cmd_out.status.run = FALSE;
				mRestartWifiCmdReplyTimer();
			}
			break;
		case SM_ENTER_SLEEP:
			if (mGetWifiCmdReplyTimerIntFlag()) WifiLoadCmd(ENTER_WIFI_SLEEP);
			break;

		case SM_SLEEP:
			if (mGetWifiCmdReplyTimerIntFlag())	WFS210Sleep();
			break;
            case SM_CUSTOM_IP:
                if (WifiCmdAccept()) WifiLoadCmd(SET_WIFI_IP_ADDRESS);
                break;
            case SM_CUSTOM_GATEWAY:
                if (WifiCmdAccept()) WifiLoadCmd(SET_WIFI_GATEWAY);
                break;
	}

	// send wifi config command
	while ((!BusyUART1()) && (!wifi.cmd_out.status.empty))
	{
		ptr = &wifi.cmd_out.data[wifi.cmd_out.pos];
		WriteUART1(*ptr++);
		wifi.cmd_out.pos++;
		if (*ptr == 0) wifi.cmd_out.status.empty = TRUE;
	}

	// check command timeout
	WifiCmdTimeoutCheck();
}


VOID WifiTransmitTasks(VOID)
{
	BYTE	*ptr;

	if (wifi.cmd_out.status.mode)
	{ // into wifi configuration mode

		// clear wifi packet buffer
		wifi.out.sm = SM_IDLE;
		wifi.out.bytes_to_send = 0;

		// send wifi config command
		WifiCmdTask();
	}
	else if (WifiTxReady() && ((wifi.cmd_out.sm == SM_START_CUSTOM_SETTINGS) || (wifi.cmd_out.sm == SM_START_SLEEP)))
	{
		wifi.cmd_out.status.mode = TRUE;
	}



	if (wifi.debug_out.mode)
	{ // into debug mode
		ptr = (BYTE *)&wifi.debug_out.data[wifi.debug_out.size - wifi.debug_out.bytes_to_send];
		while ((!BusyUART1()) && wifi.debug_out.bytes_to_send)
		{
			WriteUART1(*ptr++);
			wifi.debug_out.bytes_to_send--;
			if (wifi.debug_out.bytes_to_send == 0) wifi.debug_out.size = 0;
		}
	}

	if(!mWifiTcpOpen())
	{ // no tcp connnecting open
		wifi.out.sm = SM_IDLE;
		wifi.out.bytes_to_send = 0;
	}
	else if (!BusyUART1())
	{
		switch (wifi.out.sm)
		{
			case SM_SEND:
			{
				ptr = (BYTE *)&wifi.out.stx + (wifi.out.size - wifi.out.cntr);
				while ((!BusyUART1()) && wifi.out.cntr)
				{ // send bytes
					WriteUART1(*ptr++);
					wifi.out.cntr--;
				}
				if (wifi.out.cntr == 0)
				{ // all bytes of the packet are send
					wifi.out.sm++;
				}
				break;
			}
			case SM_FLUSH:
				mRestartWifiFlushTimer();
				wifi.out.sm++;
				break;
			case SM_FLUSH_TIMEOUT:
				if (mGetWifiFlushTimerIntFlag())
				{
					mStopWifiFlushTimer();
					wifi.out.sm++;
				}
				break;
			case SM_FRAG:
			{
				WifiTxFrag(&wifi.out);
				break;
			}
		}
	}
}




VOID WifiTasks(VOID)
{
	WifiReadTasks();
	WifiTransmitTasks();
}
