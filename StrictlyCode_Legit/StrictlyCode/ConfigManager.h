#pragma once
#pragma comment(lib,"urlmon.lib")
#include "SqchSDK\SDK\Color.h"
class Config
{
public:
	void SaveConfig();
	void LoadConfig();
	char* Handle();
	bool CheckConfigs();
	int ReadInt(char* Cat, char* Name, int defaultval);
	NSDK::Color ReadColor(char * Cata, char * Name, NSDK::Color DefaultVal);
	float ReadFloat(char* Cat, char* Name, float defaultval);
	char* ReadString(char* Cat, char* Name, char* defaultval);
	void WriteInt(char* Cat, char* Name, int defaultval);
	void WriteColor(char * Cata, char * Name, NSDK::Color SetVal);
	void WriteFloat(char* Cata, char* Name, float setVal);
	void WriteString(char* Cat, char* Name, char* defaultval);
private:
	char Path[255];
	char Path2[255];
	char Path3[255];
	char Path4[255];
	char Picture[255];
};

extern Config* ConSys;