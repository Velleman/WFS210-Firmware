#include "wfs210/wfs210_process.h"


VOID SetDebugMode(BOOL debug)
{
	SetScopeDebugMode(debug);
	SetWifiDebugMode(debug);
	WFS210SetUSBDebugMode(debug);
};


BOOL ValidateSSID(BYTE* ssid)
{
	WORD i = 0;

	// At least one charater must be used
	if (*ssid == 0) return FALSE;
	
	// Only the following characters are allowed: -, 0...9, a...z, A...Z and underscore
	while ((i < sizeof(wifi.ssid)) && (*ssid != 0))
	{	
		if ((*ssid < '-') || ((*ssid > '-') && (*ssid < '0')) || ((*ssid > '9') && (*ssid < 'A')) ||
			((*ssid > 'Z') && (*ssid < '_')) || ((*ssid > '_') && (*ssid < 'a')) || (*ssid > 'z')
			)
			return FALSE;
		ssid++;
		i++;
	}

	return TRUE;
}



BOOL ValidateReceivedPacket(WFS210_IN_PACKET* packet)
{
	// check valid command
	switch (packet->cmd)
	{
		case WFS210_CMD_WIFI_SETTINGS_REQ:
		{ // check valid packet size
			if (packet->size == WFS210_WIFI_SETTINGS_REQ_PACKET_SIZE) return TRUE;
			break;
		}
		case WFS210_CMD_WIFI_SETTINGS:
		{ // check valid packet size & wifi channel
			if ((packet->size == WFS210_WIFI_SETTINGS_PACKET_SIZE) &&
				(packet->data[WFS210_PACKET_WIFI_CHANNEL_INDEX] > 0) &&
				(packet->data[WFS210_PACKET_WIFI_CHANNEL_INDEX] < 14) &&
				(packet->data[WFS210_PACKET_WIFI_CHANNEL_INDEX + 1] == 0) &&
				ValidateSSID(&packet->data[WFS210_PACKET_WIFI_SSID_INDEX])
				)
				return TRUE;
			break;
		}
		case WFS210_CMD_CLEAR_DEBUG:
		{ // check valid packet size
			if (packet->size == WFS210_CLEAR_DEBUG_PACKET_SIZE) return TRUE;
			break;
		}
		case WFS210_CMD_SET_DEBUG:
		{ // check valid packet size
			if (packet->size == WFS210_SET_DEBUG_PACKET_SIZE) return TRUE;
			break;
		}
		case WFS210_CMD_SET_FIRMWARE_UPGRADE:
		{
			if (packet->size == WFS210_SET_FIRMWARE_UPGRADE_PACKET_SIZE) return TRUE;
			break;
		}
		case WFS210_CMD_STATUS_REQ:
		{ // check valid packet size
			if (packet->size == WFS210_STATUS_REQ_PACKET_SIZE) return TRUE;
			break;
		}
		case WFS210_CMD_SETTINGS:
		{ // check valid packet size & settings
			if ((packet->size == WFS210_STATUS_PACKET_SIZE) &&
				(packet->data[WFS210_PACKET_CH1_COUPLING_INDEX] <= REFGND) &&
				(packet->data[WFS210_PACKET_CH1_V_DIV_INDEX] <= CH_5MV_DIV) &&
				(packet->data[WFS210_PACKET_CH2_COUPLING_INDEX] <= REFGND) &&
				(packet->data[WFS210_PACKET_CH2_V_DIV_INDEX] <= CH_5MV_DIV) &&
				(packet->data[WFS210_PACKET_TIMEBASE_INDEX] <= CH_1S_DIV)
				)
				return TRUE;
			break;
		}
		case WFS210_CMD_SAMPLES_REQ:
		{ // check valid packet size
			if (packet->size == WFS210_SAMPLES_REQ_PACKET_SIZE) return TRUE;
			break;
		}
		case WFS210_CMD_START_CALIBRATION:
		{ // check valid packet size
			if (packet->size == WFS210_START_CALIBRATION_PACKET_SIZE) return TRUE;
			break;
		}
	}

	return FALSE;
}


VOID WFS210Receive(WFS210_IN_PACKET* packet)
{
	if (!ValidateReceivedPacket(packet)) return;

	switch (packet->cmd)
	{
		case WFS210_CMD_WIFI_SETTINGS_REQ:
		{
			TransmitWifiStatus(&wfs210out);
			break;
		}
		case WFS210_CMD_WIFI_SETTINGS:
		{
			if ((!scope_settings.status.flags.calibrating) && (!wifi.cmd_out.status.mode))
			{
				wifi.cmd_out.sm = SM_START_CUSTOM_SETTINGS;
				wifi.channel = packet->data[WFS210_PACKET_WIFI_CHANNEL_INDEX];
				memcpy(wifi.ssid, &packet->data[WFS210_PACKET_WIFI_SSID_INDEX], sizeof(wifi.ssid));
				memcpy(wifi.password, &packet->data[WFS210_PACKET_WIFI_PASSWORD_INDEX], sizeof(wifi.password));
			}
			break;
		}
		case WFS210_CMD_CLEAR_DEBUG:
		{
			SetDebugMode(FALSE);
			TransmitStatus(&wfs210out);
			break;
		}
		case WFS210_CMD_SET_DEBUG:
		{
			SetDebugMode(TRUE);
			TransmitStatus(&wfs210out);
			break;
		}
		case WFS210_CMD_SET_FIRMWARE_UPGRADE:
		{
			RCONbits.POR = 0;
			__asm__ volatile (" reset");
			break;
		}
		case WFS210_CMD_SETTINGS:
		{
			if (!scope_settings.status.flags.calibrating)
			{
				StopSampling();

				if (packet->data[WFS210_PACKET_TRIG_SETTINGS_INDEX] & 0x80)
				{ // autorange on
					if (scope_settings.sensitivityCh1 != CH_OFF_V_DIV)
					{
						SetInputCouplingCh1(packet->data[WFS210_PACKET_CH1_COUPLING_INDEX]);
						SetYposCh1(YPOS_CENTER);
					}
					if (scope_settings.sensitivityCh2 != CH_OFF_V_DIV)
					{
						SetInputCouplingCh2(packet->data[WFS210_PACKET_CH2_COUPLING_INDEX]);
						SetYposCh2(YPOS_CENTER);
					}
					SetTrigLevel(TRIG_LVL_CENTER);
					SetTriggering((packet->data[WFS210_PACKET_TRIG_SETTINGS_INDEX] & 0b11111100) | 1);
				}
				else
				{ // autorange off
					SetVoltDivCh1(packet->data[WFS210_PACKET_CH1_V_DIV_INDEX]);
					if (packet->data[WFS210_PACKET_CH1_V_DIV_INDEX] != CH_OFF_V_DIV)
					{
						SetInputCouplingCh1(packet->data[WFS210_PACKET_CH1_COUPLING_INDEX]);
						SetYposCh1(packet->data[WFS210_PACKET_CH1_YPOS_INDEX]);
					}
					SetVoltDivCh2(packet->data[WFS210_PACKET_CH2_V_DIV_INDEX]);
					if (packet->data[WFS210_PACKET_CH2_V_DIV_INDEX] != CH_OFF_V_DIV)
					{
						SetInputCouplingCh2(packet->data[WFS210_PACKET_CH2_COUPLING_INDEX]);
						SetYposCh2(packet->data[WFS210_PACKET_CH2_YPOS_INDEX]);
					}
					SetTimebase(packet->data[WFS210_PACKET_TIMEBASE_INDEX]);
					SetTrigLevel(packet->data[WFS210_PACKET_TRIG_LEVEL_INDEX]);
					SetTriggering(packet->data[WFS210_PACKET_TRIG_SETTINGS_INDEX]);
				}

				if (scope_settings.status.flags.trigger_hold) sampling_sm = SM_IDLE; else sampling_sm = SM_SAMPLING_START;
			}
		}
		case WFS210_CMD_STATUS_REQ:
		{
			TransmitStatus(&wfs210out);
			break;
		}
		case WFS210_CMD_SAMPLES_REQ:
		{ 
			TransmitSamples(&wfs210out, NUMBER_OF_SAMPLES_PER_CHANNEL);
			break;
		}
		case WFS210_CMD_START_CALIBRATION:
		{
			if (!scope_settings.status.flags.calibrating) StartCalibration();
			break;
		}
	}
}



VOID CALLBACK WFS210USBReceive(WFS210_IN_PACKET* packet)
{
	WFS210Receive(packet); // pass to the main handler
}


VOID CALLBACK WifiReceive(WFS210_IN_PACKET* packet)
{
	WFS210Receive(packet); // pass to the main handler
}


VOID CALLBACK WifiReceiveRaw(BYTE *data, WORD size)
{ 
	// into debug mode send received Wifi raw data to the USB port
	if (WFS210GetUSBDebugMode()) WFS210FeedUSBDebugOut(data, size);
}


VOID CALLBACK WFS210USBReceiveRaw(BYTE *data, WORD size)
{
	// into debug mode send received USB raw data to the Wifi module
	if (GetWifiDebugMode()) FeedWifiDebugOut(data, size);
}


