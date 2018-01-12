#pragma once

#pragma pack(push, 1)  

//BSON ���̺귯���� �� �ȵǼ� �ϴ� �ۼ��ص�
//�����̳� ����ê�̳� ���� �޶� �ϴ� ���� Write�� OK Read�� ����.
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
	CHAR WRITE[12];	// WRITE + 0x00 ~ LOGINLIST ������ ���־ ������ ũ��� �ϵ��ڵ��ѵ�.
	DWORD Len1;		// dwMsgLen + 0x37

					//���⼭ ���� BSON ���� ** Len �� �ι��ִ� ������ ���⿡ �־���.
	DWORD Len2;		// dwMsgLen + 0x37
	BYTE DataType1; // �Ƹ� ������ Ÿ��
	CHAR chatId[7];		// chatId\x00
	unsigned long long int chatIdValue; //ä�ù� ������ȣ.
	BYTE DataType2; //�Ƹ� ������ Ÿ��
	CHAR msg[4];		// msg
	DWORD dwMsgLen; // �� strlen(szChat)+1
	CHAR szChat[0];	// ���� UTF-8 String
};

struct _WRITE2
{
	BYTE Unknown0; //�Ƹ� ������ Ÿ��.
	CHAR msgId[6]; //msgId\x00
	unsigned long long int msgIdValue;//���� ���� �޼����� �� �޼����� ���°�ΰ�.
	BYTE Unknown1; //�Ƹ� ������ Ÿ��
	CHAR type[5]; //type\x00
	DWORD dwType;		// �Ϲ� 1 �����ϰ�� 2
	BYTE Unknown2;		// ���� �������� �ִ°�?;
};

#pragma pack(pop)   