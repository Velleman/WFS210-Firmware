/* 
 * File:   wfs210_protocol.h
 * Author: edc
 *
 * Created on 28 juni 2013, 14:35
 */

#ifndef WFS210_PROTOCOL_H
#define	WFS210_PROTOCOL_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "common.h"

// packet format : <STX> <cmd> <packetsize_low><packetsize_high> <offset_low> <offset_high> <data_0>	... <data_n> <checksum> <ETX>
//
// checksum = 8-bit two's complement of sum of all previous bytes
//
// in packets
// ----------
// wifi settings request:	<STX> <WFS210_CMD_WIFI_SETTINGS_REQ> <WFS210_WIFI_SETTINGS_REQ_PACKET_SIZE> <0> <0> <0> <checksum> <ETX>
//
// wifi settings:			<STX> <WFS210_CMD_WIFI_SETTINGS> <WFS210_WIFI_SETTINGS_PACKET_SIZE> <0> <0> <0>
//							<Wifi_channel> <0>
//							<SSID-char1> <SSID-char2> <SSID-char3> ? <SSID-char32>
//							<Password-char1> <Password-char2> <Password-char3> ? <Password-char32>
//							<checksum> <ETX>
//
// clear debug mode:		<STX> <WFS210_CMD_CLEAR_DEBUG> <WFS210_CLEAR_DEBUG_PACKET_SIZE> <0> <0> <0> <checksum> <ETX>
//
// clear debug mode:		<STX> <WFS210_CMD_SET_DEBUG> <WFS210_SET_DEBUG_PACKET_SIZE> <0> <0> <0> <checksum> <ETX>
//
// enter firmware upgrade:	<STX> <WFS210_CMD_SET_FIRMWARE_UPGRADE> <WFS210_SET_FIRMWARE_UPGRADE_PACKET_SIZE> <0> <0> <0> <checksum> <ETX>
//
// status request:			<STX> <WFS210_CMD_STATUS_RQ> <WFS210_STATUS_REQ_PACKET_SIZE> <0> <0> <0> <checksum> <ETX>
//
// settings:				<STX> <WFS210_CMD_SETTINGS> <WFS210_STATUS_PACKET_SIZE> <0>	<0> <0>
//							<Ch1 coupling> <Ch1 sensitivity> <Ch1 y-position> <Ch2 coupling> <Ch2 sensitivity> <Ch2 y-position>
//							<Timebase> <Trigger level> <Trigger settings> <0>
//							<checksum> <ETX>
//
// sample data request:		<STX> <WFS210_CMD_SAMPLES_REQ> <WFS210_SAMPLES_REQ_PACKET_SIZE> <0> <0> <0> <checksum> <ETX>
//
// start calibration:		<STX> <WFS210_CMD_START_CALIBRATION> <WFS210_START_CALIBRATION_PACKET_SIZE> <0> <0> <0> <checksum> <ETX>
//
// out packets
// -----------
// status:					<STX> <WFS210_CMD_STATUS> <WFS210_SETTINGS_PACKET_SIZE> <0>	<0> <0>
//							<Ch1 coupling> <Ch1 sensitivity> <Ch1 y-position> <Ch2 coupling> <Ch2 sensitivity> <Ch2 y-position>
//							<Timebase> <Trigger level> <Trigger settings> <Module status>
//							<checksum> <ETX>
//
// sample data:				<STX> <WFS210_CMD_SAMPLES> <Data-length-low-byte> <Data-length-high-byte> <Offset-low-byte> <Offset-high-byte>
//							<CH1-input-coupling> <CH1-V/div> <CH1-Yposition> <CH2-input-coupling> <CH2-V/div> <CH2-Yposition>
//							<Timebase> <Trigger-level> <Trigger-settings> <Module-status>
//							<Sample-1-ch1> <Sample-1-ch2> <Sample-2-ch1> <Sample-2-ch2> ? <Sample-n-ch1> <Sample-n-ch2>
//							<CHKSUM> <ETX>
//
// wifi status:				<STX> <WFS210_CMD_WIFI_STATUS> <WFS210_WIFI_STATUS_PACKET_SIZE> <0> <0> <0>
//							<Wifi_channel> <0>
//							<SSID-char1> <SSID-char2> <SSID-char3> ? <SSID-char32>
//							<Password-char1> <Password-char2> <Password-char3> ? <Password-char32>
//							<Build-char1> <Build-char2> <Build-char3> <Build-char4>
//							<version-char1> <version-char2> ... <version-char16>
//							<checksum> <ETX>

// out packet size limits
#define	WFS210_PACKET_HEADER_SIZE				6
#define	WFS210_PACKET_SETTINGS_SIZE				10
#define	WFS210_PACKET_MAX_SIZE					8210


// in packet size limits
#define WFS210_IN_PACKET_MIN_SIZE				8
#define WFS210_IN_PACKET_MAX_SIZE				74

// index
#define	WFS210_PACKET_CMD_INDEX					1
#define WFS210_PACKET_SIZE_INDEX				2
#define WFS210_PACKET_CH1_COUPLING_INDEX		0
#define WFS210_PACKET_CH1_V_DIV_INDEX			1
#define WFS210_PACKET_CH1_YPOS_INDEX			2
#define WFS210_PACKET_CH2_COUPLING_INDEX		3
#define WFS210_PACKET_CH2_V_DIV_INDEX			4
#define WFS210_PACKET_CH2_YPOS_INDEX			5
#define WFS210_PACKET_TIMEBASE_INDEX			6
#define WFS210_PACKET_TRIG_LEVEL_INDEX			7
#define WFS210_PACKET_TRIG_SETTINGS_INDEX		8
#define WFS210_PACKET_CHARGER_STATUS_INDEX		9
#define WFS210_PACKET_SAMPLE_BUFFER_INDEX		10
#define WFS210_PACKET_WIFI_CHANNEL_INDEX		0
#define WFS210_PACKET_WIFI_SSID_INDEX			2
#define WFS210_PACKET_WIFI_PASSWORD_INDEX		34



#define WFS210_STX								0x02
#define WFS210_ETX								0x0A

// in packet commands
#define WFS210_CMD_WIFI_SETTINGS_REQ			0x0A
#define WFS210_CMD_WIFI_SETTINGS				0x0B
#define WFS210_CMD_CLEAR_DEBUG					0x0C
#define WFS210_CMD_SET_DEBUG					0x0D
#define WFS210_CMD_SET_FIRMWARE_UPGRADE			0x0F
#define WFS210_CMD_STATUS_REQ					0x10
#define WFS210_CMD_SETTINGS						0x11
#define WFS210_CMD_SAMPLES_REQ					0x12
#define WFS210_CMD_START_CALIBRATION			0xCA

// out packet commands
#define WFS210_CMD_STATUS						0x20
#define WFS210_CMD_SAMPLES						0x21
#define WFS210_CMD_WIFI_STATUS					0x22

// in packet size
#define WFS210_WIFI_SETTINGS_REQ_PACKET_SIZE	8
#define WFS210_WIFI_SETTINGS_PACKET_SIZE		74
#define WFS210_CLEAR_DEBUG_PACKET_SIZE			8
#define WFS210_SET_DEBUG_PACKET_SIZE			8
#define WFS210_SET_FIRMWARE_UPGRADE_PACKET_SIZE	8
#define WFS210_STATUS_REQ_PACKET_SIZE			8
#define WFS210_SETTINGS_PACKET_SIZE				18
#define WFS210_SAMPLES_REQ_PACKET_SIZE			8
#define WFS210_START_CALIBRATION_PACKET_SIZE	8

// out packet size
#define WFS210_STATUS_PACKET_SIZE				18
#define WFS210_WIFI_STATUS_PACKET_SIZE			94


#define	SM_IDLE				0
#define	SM_SEND				1
#define	SM_FLUSH			2
#define SM_FLUSH_TIMEOUT	3
#define	SM_FRAG				4

typedef struct
{
	BYTE	stx;
	BYTE	cmd;
	WORD	size;
	WORD	offset;
	BYTE	data[256];
} WFS210_IN_PACKET;

typedef struct
{
	BYTE	stx;
	BYTE	cmd;
	WORD	size;
	WORD	offset;
	BYTE	data[WFS210_PACKET_MAX_SIZE - WFS210_PACKET_HEADER_SIZE];
} WFS210_OUT_PACKET;




#ifdef	__cplusplus
}
#endif

#endif	/* WFS210_PROTOCOL_H */

