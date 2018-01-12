#include <winsock2.h>
#include <windows.h>
#include <stdio.h>
#include <atlstr.h>
#include <iostream>

#include "CustomStruct.h"

#pragma once

// 바이트따위를 고려하지않은 발로짠 후킹클레스임으로
// 5바이트 패치가 딱 이루어지는 경우만 작동함
class CHook
{
public:
	CHook();
	virtual ~CHook();

	void AddressHook(DWORD Addr, LPVOID Fun)
	{
		dwAddr = Addr;
		VirtualProtect((LPVOID)Addr, 7, PAGE_EXECUTE_READWRITE, &OldProtect);
		memcpy(OrgBytes, (LPVOID)dwAddr,7);
		(*(BYTE*)Addr) = 0xe9;
		(*(DWORD*)(Addr + 1)) = ((DWORD)Fun - (DWORD)Addr - 5);
		(*(BYTE*)(Addr + 5)) = 0xc3;
		VirtualProtect((LPVOID)Addr, 7, OldProtect, NULL);
	}
	/*
	void UnHook()
	{
		VirtualProtect((LPVOID)dwAddr, 5, PAGE_EXECUTE_READWRITE, &OldProtect);
		memcpy((LPVOID)dwAddr, OrgBytes, 5);
		VirtualProtect((LPVOID)dwAddr, 5, OldProtect, NULL);
	}*/

public:
	DWORD dwAddr;
	DWORD OldProtect;
	DWORD OrgCallAddr;
	BYTE OrgBytes[7]; //for koraa
};

