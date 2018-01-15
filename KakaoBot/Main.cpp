#include "Hook.h"


#pragma comment(lib, "ws2_32.lib")

void Start();
CRITICAL_SECTION cs;
typedef int (__stdcall *KAKAO_WRITE) (DWORD *, DWORD *);

//?? Unused Value
//static int S_CNT = 0x2CFB9D83;

DWORD koraa = 0;

//int TEST = 0xE0CC10;

wchar_t buf2[4096];
char buf3[4096];


CHook HookR;
CHook HookW;


typedef struct t1
{
	BYTE a[4096] = { 0xaa, };

}t1;

typedef struct t2
{
	BYTE a[4096] = { 0x00, };

}t2;

typedef struct t3
{
	BYTE a[4096] = { 0x00, };

}t3;

typedef struct t4
{
	BYTE a[4096] = { 0x00, };

}t4;

typedef struct Send_STR
{
	unsigned long long len;
	BYTE str[4096] = { 0x00, };
}Send_STR;


t1 TT1;
t2 TT2;
t3 TT3;
t4 TT4;
Send_STR SendSTR;


t1* ar0=&TT1;
t2* ar1=&TT2;
t3* ar2 = &TT3;
t4* ar3 = &TT4;


KAKAO_WRITE WRITECALL;
DWORD dwKakao = 0;
unsigned long long *poi2 = NULL;
unsigned long long CHATID = 0;
DWORD Kakao_Read_Return = 0;
DWORD Kakao_Write_Return = 0;


int check = 0;
BYTE *poi = 0;
char READ_BUF[4096] = { 0x00, };
long long READ_CHATID = 0;
int nLen = 0;
int nLen2 = 0;
wchar_t strUnicode[4096] = { 0, };
char	buf[4096] = { 0, };
char temp[4096] = { 0, };
char *bufptr;
char *bufptr2;
char	*strUTF8;
int writeflag = 0;

LONG WINAPI TestUnhandledExceptionFilter(_EXCEPTION_POINTERS *ExceptionInfo)
{
	//MessageBox(NULL, TEXT("예외 발생"), TEXT("Test"), MB_OK);
	return 0;
}


/*
bool bCompare(const BYTE* pData, const BYTE* bMask, const char* szMask)
{
	for (; *szMask; ++szMask, ++pData, ++bMask)
		if (*szMask == 'x' && *pData != *bMask) return 0;
	return (*szMask) == NULL;

}
DWORD FindPattern(DWORD dwAddress, DWORD dwLen, BYTE *bMask, char * szMask)
{
	for (DWORD i = 0; i<dwLen; i++)
		if (bCompare((BYTE*)(dwAddress + i), bMask, szMask)) return (DWORD)(dwAddress + i);
	return 0;
}//version 2.6.3.1672


*/


void kakao_write(char *msg,int len,unsigned long long c_id)
{
	EnterCriticalSection(&cs);

	nLen2 = MultiByteToWideChar(CP_ACP, 0, msg, len, NULL, NULL);
	MultiByteToWideChar(CP_ACP, 0, msg, len, buf2, nLen2);
	nLen2 = WideCharToMultiByte(CP_UTF8, 0, buf2, lstrlenW(buf2), NULL, 0, NULL, NULL);
	WideCharToMultiByte(CP_UTF8, 0, buf2, lstrlenW(buf2), buf3, nLen2, NULL, NULL);

	SendSTR.len = nLen2;
	strncpy((char *)SendSTR.str, buf3,nLen2);

	*(DWORD *)((BYTE *)ar0 + 0x1B8) =(DWORD)ar1;
	*(unsigned long long *)((BYTE *)ar1 + 0x10) = (CHATID);
	if (c_id != 0)
	{
		*(unsigned long long *)((BYTE *)ar1 + 0x10) = (c_id);
	}

	*(DWORD *)((BYTE *)ar2) = (DWORD)ar3;
	*(DWORD *)((BYTE *)ar0 + 0x310) = (DWORD)((BYTE *)ar0 + 0x310);
	*(DWORD *)((BYTE *)ar0 + 0x314) = (DWORD)((BYTE *)ar0 + 0x310);
	*(DWORD *)((BYTE *)ar0 + 0x304) = (DWORD)((BYTE *)ar0 + 0x310);
	*(DWORD *)((BYTE *)ar0 + 0x308) = (DWORD)((BYTE *)ar0 + 0x310);
	*(DWORD *)((BYTE *)ar3 + 0x30) = (DWORD)SendSTR.str;
	*(DWORD *)((BYTE *)ar3 + 0x2C) = (DWORD)0;
	*(DWORD *)((BYTE *)ar3 + 0x28) = ++*(DWORD *)((BYTE *)ar3 + 0x28);//2CFB9D7C
	*(DWORD *)((BYTE *)ar3 + 0x10) = (DWORD)1;
	*(DWORD *)((BYTE *)ar3 + 0x64) = (DWORD)0xE0FEA2; //뭐지? //0xE0CB1A
	*(DWORD *)((BYTE *)ar3 + 0xA0) = (DWORD)0xA;
	*(BYTE *)((BYTE *)ar3 + 0xC4) = (DWORD)0x0;

	WRITECALL((DWORD *)ar0, (DWORD *)ar2);
	memset(buf2, 0, 4096);
	memset(SendSTR.str, 0, 4096);
	
	LeaveCriticalSection(&cs);

}

void __declspec(naked) MyRead()
{
	
	__asm
	{

		mov poi, esp
	}

	nLen = MultiByteToWideChar(CP_UTF8, 0, (*(const char **)(poi + 0xc4)), strlen(*(const char **)(poi + 0xc4)), NULL, NULL);
	MultiByteToWideChar(CP_UTF8, 0, (*(const char **)(poi + 0xc4)), strlen(*(const char **)(poi + 0xc4)), strUnicode, nLen);
	nLen = WideCharToMultiByte(CP_ACP, 0, strUnicode, -1, NULL, 0, NULL, NULL);
	WideCharToMultiByte(CP_ACP, 0, strUnicode, -1, buf, nLen, NULL, NULL);

	CHATID = (*(unsigned long long *)(poi + 0x9c));

	buf[nLen] = 0;
	printf("\nChatRoomID: %llu -> Msg: %s", CHATID, buf);

	if(1)
	{
		if (buf[0] == 0x2F)
		{
			if (!strncmp(buf + 1, "날씨",4))
			{
				kakao_write("날씨 안알려줄거야", strlen("날씨 안알려줄거야"),0);
			}
			else if (!strncmp(buf + 1, "자살", 4))
			{
				kakao_write("자살안할거야 ㅡㅡ", strlen("자살안할거야 ㅡㅡ"),0);
			}
			else if (!strncmp(buf + 1, "안녕", 4))
			{	
				kakao_write("응 안녕!", strlen("응 안녕!"),0);
			}
			else if (!strncmp(buf + 1, "테스트", 6))
			{
				kakao_write("TEST", strlen("TEST"),0);
			}
			else
			{
				kakao_write("커맨드가 맞지 않아! 개발중이니까 기다려", strlen("커맨드가 맞지 않아! 개발중이니까 기다려"),0);
			}
		}
	}
	
	ZeroMemory(buf, 4086);
	ZeroMemory(strUnicode, 4086);




	__asm
	{
		
		lea edx,[esp+0x94]

		jmp[Kakao_Read_Return]
	}

	
}

void __declspec(naked) MyWrite()
{


		__asm
		{

			pushad

			push 0x1000
			push edx
			push ar0
			call memcpy
			add esp, 0x0C

			push 0x1000
			push edi
			push ar2
			call memcpy
			add esp, 0x0C


			push 0x1000
			push [edi]
			push ar3
			call memcpy
			add esp, 0x0C
			
		}


		__asm {

			popad


			push edi
			push edx
			call koraa
			jmp[Kakao_Write_Return]
		}

	
}

void Start()
{
	DWORD dwSize = 0x180000;
	DWORD ReadAddress = 0;
	DWORD WriteAddress = 0;
	DWORD dwAddress = 0;
	do
	{
		dwKakao = (DWORD)GetModuleHandleA("KakaoTalk.exe");
		Sleep(10);
	} while (!dwKakao);
	Sleep(100);
	printf("Kakao Chat Bot\nModule: %p\n", dwKakao);
	

	ReadAddress = 0x8b59ce; //0x8b3c6e
	Kakao_Read_Return = ReadAddress + 7;
	Kakao_Write_Return = 0x5cd244; //0x5d505f
	


	printf("Read --> %08X\n", Kakao_Read_Return);
	printf("Write --> %08X\n", Kakao_Write_Return);


	HookR.AddressHook(Kakao_Read_Return-7, MyRead);
	HookW.AddressHook(Kakao_Write_Return-7, MyWrite);

	koraa = Kakao_Write_Return+ (*(DWORD*)(HookW.OrgBytes + 3));


}
BOOL APIENTRY DllMain(HMODULE hModul, DWORD ul_reason_for_ca, LPVOID lpReserve)
{
	switch (ul_reason_for_ca)
	{
	case DLL_PROCESS_ATTACH:
		AllocConsole();
		freopen("CON", "w", stdout);
		WRITECALL = (KAKAO_WRITE)0x008a8f00;
		InitializeCriticalSection(&cs);

		SetUnhandledExceptionFilter(TestUnhandledExceptionFilter);

		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)Start, NULL, NULL, NULL);

	case DLL_THREAD_ATTACH:

	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}