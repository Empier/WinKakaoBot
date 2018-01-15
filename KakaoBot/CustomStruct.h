#pragma once

#pragma pack(push, 1)  

//BSON 라이브러리가 잘 안되서 일단 작성해둠
//단톡이나 오픈챗이나 조금 달라서 일단 보류 Write는 OK Read가 문제.
struct RecvMsg
{
	DWORD WhatSize;
	BYTE Unknown[0x16];
	CHAR EventName[0xC];
	//unknown len
	DWORD UnknownNum1;
	DWORD UnknownNum2;
	CHAR p;
};

struct RealMSG
{
	DWORD status;
	unsigned long long int chatId1;
	unsigned long long int logId1;
	DWORD LenNick;
	PCHAR authorNickname;
	DWORD chatLog;
	unsigned long long int logId2;
	unsigned long long int chatId2;
	DWORD type;
	unsigned long long int authorId;
	DWORD LenMsg;
	PCHAR Msg;
	DWORD sendAt;
	DWORD LenAttachment;
	PCHAR attachment;

};


struct _WRITE
{
	DWORD Index;
	SHORT Reversed;		// must 00
	CHAR WRITE[12];	// WRITE + 0x00 ~ LOGINLIST 같은게 들어가있어서 적당한 크기로 하드코딩한듯.
	DWORD Len1;		// dwMsgLen + 0x37

					//여기서 부터 BSON 구조 ** Len 이 두번있는 이유는 여기에 있었다.
	DWORD Len2;		// dwMsgLen + 0x37
	BYTE DataType1; // 아마 데이터 타입
	CHAR chatId[7];		// chatId\x00
	unsigned long long int chatIdValue; //채팅방 고유번호.
	BYTE DataType2; //아마 데이터 타입
	CHAR msg[4];		// msg
	DWORD dwMsgLen; // 즉 strlen(szChat)+1
	CHAR szChat[0];	// 가변 UTF-8 String
};

struct _WRITE2
{
	BYTE Unknown0; //아마 데이터 타입.
	CHAR msgId[6]; //msgId\x00
	unsigned long long int msgIdValue;//내가 보낸 메세지중 이 메세지가 몇번째인가.
	BYTE Unknown1; //아마 데이터 타입
	CHAR type[5]; //type\x00
	DWORD dwType;		// 일반 1 사진일경우 2
	BYTE Unknown2;		// 뭔가 적힐수도 있는가?;
};

#pragma pack(pop)   