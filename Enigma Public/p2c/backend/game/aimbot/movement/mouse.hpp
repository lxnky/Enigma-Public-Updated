#pragma once
#include <wtypes.h>
#include "../../../../frontend/protection/encryption/string/xor.hpp"
inline const BYTE XOR_KEY = 0xACACACADDEDFFFA;
inline void EncryptFunctionBytes(BYTE* bytes, size_t size) {
	for (size_t i = 0; i < size; ++i) {
		bytes[i] ^= XOR_KEY;
	}
}
inline void DecryptFunctionBytes(BYTE* bytes, size_t size) {
	for (size_t i = 0; i < size; ++i) {
		bytes[i] ^= XOR_KEY;
	}
}
enum InjectedInputMouseOptions
{
	Absolute = 32768,
	HWheel = 4096,
	LeftDown = 2,
	LeftUp = 4,
	MiddleDown = 32,
	MiddleUp = 64,
	Move = 1,
	MoveNoCoalesce = 8192,
	None = 0,
	RightDown = 8,
	RightUp = 16,
	VirtualDesk = 16384,
	Wheel = 2048,
	XDown = 128,
	XUp = 256
};
typedef struct _InjectedInputMouseInfo {
	int DeltaX;
	int DeltaY;
	unsigned int MouseData;
	InjectedInputMouseOptions MouseOptions;
	unsigned int TimeOffsetInMilliseconds;
	void* ExtraInfo;
} InjectedInputMouseInfo;

typedef bool (WINAPI* InjectMouseInput_t)(InjectedInputMouseInfo* inputs, int count);
inline InjectMouseInput_t InjectMouseInput;
namespace Mouse
{
	
	static BYTE NtUserInjectMouseInput_Bytes[30];


	static BOOLEAN WINAPI Init()
	{
		SPOOF;
		// windows 8.1 / windows 10
		LPVOID NtUserInjectMouseInput_Addr = GetProcAddress(GetModuleHandle(_("win32u")), _("NtUserInjectMouseInput"));
		if (!NtUserInjectMouseInput_Addr)
		{
			NtUserInjectMouseInput_Addr = GetProcAddress(GetModuleHandle("user32"), "NtUserInjectMouseInput");
			if (!NtUserInjectMouseInput_Addr)
			{
				// Windows 7 or lower detected
				NtUserInjectMouseInput_Addr = GetProcAddress(GetModuleHandle("user32"), "InjectMouseInput");
				if (!NtUserInjectMouseInput_Addr)
					return FALSE;
			}
		}
		memcpy(NtUserInjectMouseInput_Bytes, NtUserInjectMouseInput_Addr, 30);
		EncryptFunctionBytes(NtUserInjectMouseInput_Bytes, 30);
		return TRUE;
	}

	static BOOLEAN WINAPI NtInjectMouse(InjectedInputMouseInfo* input, int count)
	{
		SPOOF;
		LPVOID NtUserInjectMouseInput_Spoof = VirtualAlloc(0, 0x1000, MEM_COMMIT, PAGE_EXECUTE_READWRITE); // allocate space for syscall
		if (!NtUserInjectMouseInput_Spoof)
			return FALSE;

		DecryptFunctionBytes(NtUserInjectMouseInput_Bytes, 30);
		memcpy(NtUserInjectMouseInput_Spoof, NtUserInjectMouseInput_Bytes, 30); // copy syscall
		EncryptFunctionBytes(NtUserInjectMouseInput_Bytes, 30);


		NTSTATUS Result = reinterpret_cast<NTSTATUS(NTAPI*)(InjectedInputMouseInfo*, int)>(NtUserInjectMouseInput_Spoof)(input, count); // calling spoofed function
		ZeroMemory(NtUserInjectMouseInput_Spoof, 0x1000); // clean address
		VirtualFree(NtUserInjectMouseInput_Spoof, 0, MEM_RELEASE); // free it
		return (Result > 0); // return the status
	}

	/* This function moves the mouse using the syscall */
	static BOOLEAN WINAPI NtInjectMouse(int X, int Y)
	{
		SPOOF;
		InjectedInputMouseInfo info = { 0 };
		info.DeltaX = X;
		info.DeltaY = Y;
		return NtInjectMouse(&info, 1);
	}
}
