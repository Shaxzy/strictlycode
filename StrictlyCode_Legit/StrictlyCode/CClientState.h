#pragma once
#include <memory>
#include "SqchSDK\SDK\QAngle.h"
namespace NSDK
{
	class INetChannel
	{
	public:
		char pad_0000[20];           //0x0000
		bool m_bProcessingMessages;  //0x0014
		bool m_bShouldDelete;        //0x0015
		char pad_0016[2];            //0x0016
		int32_t m_nOutSequenceNr;    //0x0018 last send outgoing sequence number
		int32_t m_nInSequenceNr;     //0x001C last received incoming sequnec number
		int32_t m_nOutSequenceNrAck; //0x0020 last received acknowledge outgoing sequnce number
		int32_t m_nOutReliableState; //0x0024 state of outgoing reliable data (0/1) flip flop used for loss detection
		int32_t m_nInReliableState;  //0x0028 state of incoming reliable data
		int32_t m_nChokedPackets;    //0x002C number of choked packets
		char pad_0030[1044];         //0x0030
	}; //Size: 0x0444

	class CClockDriftMgr
	{
	public:
		float m_ClockOffsets[16];   //0x0000
		uint32_t m_iCurClockOffset; //0x0040
		int32_t m_nServerTick;      //0x0044
		int32_t m_nClientTick;      //0x0048
	}; //Size: 0x004C
	class CClientState
	{
	public:
		static void ForceFullUpdate();

		char pad_0000[148];              //0x0000
		INetChannel* m_NetChannel; //0x0094
		uint32_t m_nChallengeNr;         //0x0098
		double m_flConnectTime;          //0x009C
		int32_t m_nRetryNumber;          //0x00A4
		char pad_00A8[88];               //0x00A8
		int32_t m_nSignonState;          //0x0100
		char pad_0104[8];                //0x0104
		float m_flNextCmdTime;           //0x010C
		int32_t m_nServerCount;          //0x0110
		uint32_t m_nCurrentSequence;     //0x0114
		char pad_0118[8];                //0x0118
		CClockDriftMgr m_ClockDriftMgr;  //0x0120
		int32_t m_nDeltaTick;            //0x016C
		bool m_bPaused;                  //0x0170
		char pad_0171[3];                //0x0171
		int32_t m_nViewEntity;           //0x0174
		int32_t m_nPlayerSlot;           //0x0178
		char pad_017C[4];                //0x017C
		char m_szLevelName[260];         //0x0180
		char m_szLevelNameShort[40];     //0x0284
		char pad_02AC[92];               //0x02AC
		int32_t m_nMaxClients;           //0x0308
		char pad_030C[4083];             //0x030C
		uint32_t m_StringTableContainer; //0x12FF
		char pad_1303[14737];            //0x1303
		float m_flLastServerTickTime;    //0x4C94
		bool insimulation;               //0x4C98
		char pad_4C99[3];                //0x4C99
		uint32_t oldtickcount;           //0x4C9C
		float m_tickRemainder;           //0x4CA0
		float m_frameTime;               //0x4CA4
		int32_t lastoutgoingcommand;     //0x4CA8
		int32_t chokedcommands;          //0x4CAC
		int32_t last_command_ack;        //0x4CB0
		int32_t command_ack;             //0x4CB4
		int32_t m_nSoundSequence;        //0x4CB8
		char pad_4CBC[80];               //0x4CBC
		QAngle viewangles;               //0x4D0C
	}; //Size: 0x4D18
}