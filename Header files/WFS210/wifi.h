/* 
 * File:   wifi.h
 * Author: edc
 *
 * Created on 8 juli 2013, 11:26
 */

#ifndef WIFI_H
#define	WIFI_H

#ifdef	__cplusplus
extern "C" {
#endif


#include "common.h"

#include "wfs210/wfs210_hal.h"
#include "wfs210/wfs210_protocol.h"
#include "wfs210/parser.h"
#include "wfs210/wifi_cmd_reply_parser.h"
#include "wfs210/checksum.h"
	
#include <libpic30.h>
#include <uart.h>
#include <string.h>
#include <ctype.h>


#define	WIFI_PACKET_MAX_SIZE	1042
#define NUMBER_OF_WIFI_CHANNELS	13


#define BAUDRATE	9600
#define BRGVAL		(((GetPeripheralClock() / BAUDRATE) / 16) - 1)	// 259 for 9600 baud
#define UARTMODE	(UART_EN & UART_IDLE_CON & UART_IrDA_DISABLE & UART_MODE_SIMPLEX & \
					 UART_UEN_00 & UART_DIS_WAKE & UART_DIS_LOOPBACK & UART_DIS_ABAUD & \
					 UART_UXRX_IDLE_ONE & UART_BRGH_SIXTEEN & UART_NO_PAR_8BIT & UART_1STOPBIT)
#define UARTSTA		(UART_INT_TX_BUF_EMPTY & UART_IrDA_POL_INV_ZERO & UART_SYNC_BREAK_DISABLED & \
					 UART_TX_ENABLE & UART_INT_RX_CHAR & UART_ADR_DETECT_DIS & UART_RX_OVERRUN_CLEAR)


#define HS_BAUDRATE	460800 /*1100000*/
//#define HS_BRGVAL	(((GetPeripheralClock() / HS_BAUDRATE) / 4) - 1)	// 8 for 1100000 baud (10 for 921600 baud)
//#define HS_BRGVAL	8  // 8 for 1100000 baud
#define HS_BRGVAL	21 // 21 for 460800 baud
//#define HS_BRGVAL	86 // 86 for 115200 baud

#define HS_UARTMODE	(UART_EN & UART_IDLE_CON & UART_IrDA_DISABLE & UART_MODE_FLOW & \
					 UART_UEN_10 & UART_DIS_WAKE & UART_DIS_LOOPBACK & UART_DIS_ABAUD & \
					 UART_UXRX_IDLE_ONE & UART_BRGH_FOUR & UART_NO_PAR_8BIT & UART_2STOPBITS)
#define HS_UARTSTA	(UART_INT_TX_BUF_EMPTY & UART_IrDA_POL_INV_ZERO & UART_SYNC_BREAK_DISABLED & \
					 UART_TX_ENABLE & UART_INT_RX_CHAR & UART_ADR_DETECT_DIS & UART_RX_OVERRUN_CLEAR)

#define DEFAULT_WIFI_SSID			"WFS210"
#define DEFAULT_WIFI_PASSWORD		"WFS210scope"
#define DEFAULT_WIFI_CHANNEL		5

// wifi configuration command strings
#define ENTER_WIFI_CMD_MODE			"$$$"
#define SET_WIFI_FACTORY_DEFAULTS	"factory RESET\r\n"
#define SET_WIFI_TX_POWER			"set wlan tx 12\r\n"
#define SET_WIFI_ACCESS_POINT		"set wlan join 7\r\n"


#define SET_WIFI_SSID				"set wlan ssid "
#define SET_WIFI_SECURITY_OPEN		"set wlan auth 0\r\n"
#define SET_WIFI_SECURITY_WPA2		"set wlan auth 2\r\n"
#define SET_WIFI_PASSWORD			"set wlan phrase "
#define SET_WIFI_AP_PASSWORD		"set ap pass "
#define SET_WIFI_DHCP				"set ip dhcp 4\r\n"
#define SET_WIFI_IP_ADDRESS			"set ip address 169.254.1.1\r\n"
#define SET_WIFI_NETMASK			"set ip netmask 255.255.255.0\r\n"
#define SET_WIFI_GATEWAY			"set ip gateway 169.254.1.1\r\n"
#define SET_WIFI_LOCAL_PORT			"set ip localport 2000\r\n"
#define SET_WIFI_HOST_PORT			"set ip remote 2000\r\n"
//#define SET_WIFI_UDP_PROTOCOL		"set ip protocol 1\r\n"
#define SET_WIFI_TCP_PROTOCOL		"set ip protocol 2\r\n"
//#define SET_WIFI_TCP_PROTOCOL		"set ip protocol 3\r\n"
#define SET_WIFI_IP_HOST			"set ip host 255.255.255.255\r\n"
#define SET_WIFI_BROADCAST_INTERVAL	"set broadcast interval 0\r\n"
//#define SET_WIFI_BROADCAST_INTERVAL	"set broadcast interval 7\r\n"
#define SET_WIFI_FLUSH_TIME			"set comm time 2\r\n"
#define SET_WIFI_FLUSH_SIZE			"set comm size 1042\r\n"
#define SET_WIFI_GPIO				"set sys iofunc 0x40\r\n"
#define SET_WIFI_INSTANT_BAUDRATE	"set uart instant 9600\r\n"
#define SET_WIFI_BAUDRATE_9600		"set uart baud 9600\r\n"
#define SET_WIFI_BAUDRATE			"set uart baud 460800\r\n"
#define SET_WIFI_FLOW				"set uart flow 1\r\n"
#define SET_WIFI_NO_FLOW			"set uart flow 0\r\n"
#define SET_WIFI_CHANNEL			"set wlan channel "
#define GET_WIFI_SETTINGS			"get wlan\r\n"
#define SCAN_WIFI					"scan\r\n"
#define EXIT_WIFI_CMD_MODE			"exit\r\n"
#define STORE_WIFI_SETTINGS			"save\r\n"
#define REBOOT_WIFI					"reboot\r\n"
#define ENTER_WIFI_SLEEP			"sleep\r\n"


// state machine wifi configuration
#define SM_IDLE							0
#define SM_RESET						1
#define SM_START_CMD_MODE				2
#define SM_SET_CMD_MODE					3
#define SM_SET_FACTORY_DEFAULTS			4
#define SM_SET_TX_POWER					5
#define SM_SET_WIFI_ACCESS_POINT		6
#define SM_SET_WIFI_SSID				7
#define SM_SET_WIFI_SECURITY			8
#define SM_SET_WIFI_PASSWORD			9
#define SM_SET_WIFI_AP_PASSWORD			10
#define SM_SET_WIFI_DHCP				11
#define SM_SET_WIFI_IP_ADDRESS			12
#define SM_SET_WIFI_NETMASK				13
#define SM_SET_WIFI_GATEWAY				14
#define SM_SET_WIFI_LOCAL_PORT			15
#define SM_SET_WIFI_HOST_PORT			16
#define SM_SET_WIFI_TCP_PROTOCOL		17
#define SM_SET_WIFI_IP_HOST				18
#define SM_SET_WIFI_BROADCAST_INTERVAL	19
#define SM_SET_WIFI_FLUSH_TIME			20
#define SM_SET_WIFI_FLUSH_SIZE			21
#define SM_SET_WIFI_GPIO				22
#define SM_SET_WIFI_BAUDRATE			23
#define SM_SET_WIFI_FLOW				24
#define SM_SET_WIFI_CHANNEL				25
#define SM_STORE_WIFI_SETTINGS			26
#define SM_RESET_WIFI					27
#define SM_RESET_READY					28


// state machine get wifi settings (SSID, password, channel ...)
#define SM_START_GET_SETTINGS			29
#define SM_START_SETTINGS_CMD_MODE		30
#define SM_SET_SETTINGS_CMD_MODE		31
#define SM_GET_SETTINGS					32
#define SM_FIRST_SCAN					33
#define SM_SECOND_SCAN					34
#define SM_CHECK_SCAN					35
#define SM_EXIT							36
#define SM_EXIT_READY					37
#define SM_SET_FREE_CHANNEL				38
#define SM_STORE_CHANNEL				39
#define SM_CHANNEL_RESET				40
#define SM_CHANNEL_RESET_READY			41

// state machine wifi custom settings (SSID, password & channel)
#define SM_START_CUSTOM_SETTINGS			42
#define SM_START_CUSTOM_SETTINGS_CMD_MODE	43
#define SM_CUSTOM_SETTINGS_CMD_MODE			44
#define SM_CUSTOM_BAUDRATE_9600				45
#define SM_CUSTOM_NO_FLOW					46
#define SM_CUSTOM_STORE						47
#define SM_CUSTOM_RESET						48
#define SM_CUSTOM_RESET_READY				49
#define SM_CUSTOM_RESET_DELAY				50
#define SM_CUSTOM_CMD_MODE					51
#define SM_CUSTOM_SSID						52
#define SM_CUSTOM_PASSWORD					53
#define SM_CUSTOM_AP_PASSWORD				54
#define SM_CUSTOM_CHANNEL					55
#define SM_CUSTOM_BAUDRATE_460K				56
#define SM_CUSTOM_FLOW						57
#define SM_CUSTOM_SETTINGS_SAVE				58
#define SM_CUSTOM_SETTINGS_RESET			59
#define SM_CUSTOM_SETTINGS_RESET_READY		60

// state machine enter sleep mode
#define SM_START_SLEEP						61
#define SM_START_SLEEP_CMD_MODE				62
#define SM_SLEEP_CMD_MODE					63
#define SM_ENTER_SLEEP						64
#define SM_SLEEP							65




typedef struct
{
	BYTE	*pfrag;
	WORD	sm;
	WORD	cntr;
	WORD	bytes_to_send;
	BYTE	stx;
	BYTE	cmd;
	WORD	size;
	WORD	offset;
	BYTE	data[WIFI_PACKET_MAX_SIZE - WFS210_PACKET_HEADER_SIZE];
} WIFI_OUT;

typedef struct
{
	BOOL	mode;
	WORD	size;
	WORD	bytes_to_send;
	BYTE	data[256];
} WIFI_DEBUG_OUT;


typedef struct
{
	unsigned	mode		: 1;
	unsigned	run			: 1;
	unsigned	ap			: 1;
	unsigned	accept		: 1;
	unsigned	end_scan	: 1;
	unsigned	empty		: 1;
	unsigned	reserved	: 10;
} WIFI_CMD_STATUS;


typedef struct
{
	WIFI_CMD_STATUS	status;
	WORD			sm;
	WORD			pos;
	char			data[96];
} WIFI_CMD_OUT;

typedef struct
{
	BOOL used;
	int	 level;
	int  weight;
} WIFI_ACCESS_POINT;

typedef struct
{
	BOOL					tx_settings;
	char					buffer_in[64];
	WIFI_OUT				out;
	WIFI_DEBUG_OUT			debug_out;
	WIFI_CMD_OUT			cmd_out;
	PACKET_PARSER			parser;
	WIFI_CMD_REPLY_PARSER	cmd_reply_parser;
	char					cmd_reply[256];
	int						cmd_timeout_cntr;
	char					ssid[32];
	char					password[32];
	char					build[4];
	char					version[16];
	int						channel;
	BOOL					wpa2;
	WIFI_ACCESS_POINT		access_point[NUMBER_OF_WIFI_CHANNELS];
} WIFI;



extern WIFI wifi;



/**
 *
 */
VOID WifiInit(VOID);


/**
 * Copy data from the packet buffer to Wifi_out buffer and set Wifi_send flag
 * @param packet pointer to data to send
 * @return none
 */
//VOID WFS210WifiTransmit(WFS210_OUT_PACKET *packet);


/**
 *
 * @param debug
 * @return
 */
VOID SetWifiDebugMode(BOOL debug);


/**
 * 
 * @param 
 * @return 
 */
BOOL GetWifiDebugMode(VOID);


/**
 *
 * @param
 * @return
 */
BOOL WifiConnected(VOID);


/**
 *
 * @param
 * @return
 */
BOOL WifiTxReady(VOID);


/**
 *
 * @param data
 * @param size
 * @return
 */
VOID FeedWifiDebugOut(BYTE *data, WORD size);


/**
 * 
 * @param packet
 * @return
 */
VOID WifiTransmit(WFS210_OUT_PACKET* packet);


/**
 *
 * @param debug
 * @param wificonfig
 * @return
 */
VOID WifiTasks(VOID);


/**
 *
 */
VOID CALLBACK WifiReceive(WFS210_IN_PACKET* packet);


/**
 *
 * @param data
 * @param size
 */
VOID CALLBACK WifiReceiveRaw(BYTE *data, WORD size);



#ifdef	__cplusplus
}
#endif

#endif	/* WIFI_H */

