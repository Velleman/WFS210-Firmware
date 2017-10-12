#include "WFS210/wfs210_process.h"

TX_QUEUE tx_queue;


VOID LoadWifiStatusTxPacket(WFS210_OUT_PACKET* packet)
{
	packet->cmd = WFS210_CMD_WIFI_STATUS;
//TODO: remove scanned wifi channels
	packet->size = WFS210_WIFI_STATUS_PACKET_SIZE;  // + sizeof(wifi.access_point);
	packet->offset = 0;
	packet->data[0] = wifi.channel;
	packet->data[1] = 0;
	memcpy((void *)&packet->data[sizeof(wifi.channel)], (const void *)wifi.ssid, sizeof(wifi.ssid));
	memcpy((void *)&packet->data[sizeof(wifi.channel) + sizeof(wifi.ssid)], (const void *)wifi.password, sizeof(wifi.password));
	memcpy((void *)&packet->data[sizeof(wifi.channel) + sizeof(wifi.ssid) + sizeof(wifi.password)], (const void *)wifi.build, sizeof(wifi.build));
	memcpy((void *)&packet->data[sizeof(wifi.channel) + sizeof(wifi.ssid) + sizeof(wifi.password) + sizeof(wifi.build)], (const void *)wifi.version, sizeof(wifi.version));

//TODO: remove scanned wifi channels
//	int i;

//	for (i=0; i<13; ++i)
//	{
//		wifi.access_point[i].used = 1;
//		wifi.access_point[i].level = 2;
//		wifi.access_point[i].weight = 3;
//	}

	memcpy((void *)&packet->data[sizeof(wifi.channel) + sizeof(wifi.ssid) + sizeof(wifi.password) + sizeof(wifi.build) + sizeof(wifi.version)], (const void *)wifi.access_point, sizeof(wifi.access_point));
//TODO: end

}


VOID LoadStatusTxPacket(WFS210_OUT_PACKET* packet)
{
	packet->cmd = WFS210_CMD_STATUS;
	packet->size = WFS210_STATUS_PACKET_SIZE;
	packet->offset = 0;
	ReadChargerStatus();
	memcpy((void *)packet->data, (const void *)&scope_settings, sizeof(scope_settings));
}


VOID LoadSamplesTxPacket(WFS210_OUT_PACKET* packet, WORD nr_samples)
{
	packet->cmd = WFS210_CMD_SAMPLES;
	packet->size = 	WFS210_PACKET_HEADER_SIZE + WFS210_PACKET_SETTINGS_SIZE + (2 * nr_samples /*NUMBER_OF_SAMPLES_PER_CHANNEL*/) + 2;
	packet->offset = 0;
	ReadChargerStatus();
	memcpy((void *)packet->data, (const void *)&scope_settings, sizeof(scope_settings));
	memcpy((void *)&packet->data[WFS210_PACKET_SAMPLE_BUFFER_INDEX], (const void *)&sample_buffer[2 * PMP_LATENCY], 2 * nr_samples /*sizeof(sample_buffer) - (2 * PMP_LATENCY)*/);
}


VOID TransmitSamples(WFS210_OUT_PACKET* packet, WORD nr_samples)
{
	if (WifiTxReady() && WFS210USBTxReady())
	{	
		LoadSamplesTxPacket(packet, nr_samples);
		WFS210USBTransmit(packet);
		WifiTransmit(packet);
		tx_queue.samples = 0;
	}
	else tx_queue.samples = nr_samples;
}


VOID TransmitStatus(WFS210_OUT_PACKET* packet)
{
	if (WifiTxReady() && WFS210USBTxReady())
	{
		LoadStatusTxPacket(packet);
		WFS210USBTransmit(packet);
		WifiTransmit(packet);
		tx_queue.status = FALSE;
	}
	else tx_queue.status = TRUE;
}


VOID TransmitWifiStatus(WFS210_OUT_PACKET* packet)
{
	if (WifiTxReady() && WFS210USBTxReady())
	{
		LoadWifiStatusTxPacket(packet);
		WFS210USBTransmit(packet);
		WifiTransmit(packet);
		tx_queue.wifistatus = FALSE;
	}
	else tx_queue.wifistatus = TRUE;
}


BOOL TxQueueEmpty(VOID)
{
	return ((tx_queue.samples == 0) && (!tx_queue.status) && (!tx_queue.wifistatus));
}


BOOL TxReady(VOID)
{
	return (WifiTxReady() && WFS210USBTxReady() && TxQueueEmpty());
}


VOID TransmitTask(VOID)
{
	if ((!TxQueueEmpty()) && WifiTxReady() && WFS210USBTxReady())
	{
		if (tx_queue.samples != 0) TransmitSamples(&wfs210out, tx_queue.samples);
		else if (tx_queue.status) TransmitStatus(&wfs210out);
		else if (tx_queue.wifistatus) TransmitWifiStatus(&wfs210out);
	}
}
