#pragma once

#include <stdio.h>
#include <Windows.h>
#include <Iphlpapi.h>
#include <string>
#include <Assert.h>
#pragma comment(lib, "iphlpapi.lib")

namespace Mac 
{
	char* get_mac()
	{
		PIP_ADAPTER_INFO AdapterInfo;
		DWORD dwBufLen = sizeof(AdapterInfo);
		char *mac_addr = (char*)malloc(17);

		AdapterInfo = (IP_ADAPTER_INFO *)malloc(sizeof(IP_ADAPTER_INFO));

		if (GetAdaptersInfo(AdapterInfo, &dwBufLen) == ERROR_BUFFER_OVERFLOW)
			AdapterInfo = (IP_ADAPTER_INFO *)malloc(dwBufLen);

		if (GetAdaptersInfo(AdapterInfo, &dwBufLen) == NO_ERROR)
		{
			PIP_ADAPTER_INFO pAdapterInfo = AdapterInfo;
			do {
				sprintf(mac_addr, "%02X:%02X:%02X:%02X:%02X:%02X",
					pAdapterInfo->Address[0], pAdapterInfo->Address[1],
					pAdapterInfo->Address[2], pAdapterInfo->Address[3],
					pAdapterInfo->Address[4], pAdapterInfo->Address[5]);

				char* cAddr = mac_addr;

				return cAddr;

				pAdapterInfo = pAdapterInfo->Next;
			} while (pAdapterInfo);
		}
		return "";
		free(AdapterInfo);
	}
}