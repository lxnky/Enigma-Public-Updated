#pragma once

#ifndef ENTRY
#define ENTRY

#include "includes.hpp"
#include "backend/mapper/driver_map.h"
#include "backend/auth/auth.h"
#include "frontend/protection/process/AntiCrack.h"

auto Cinit() -> void
{
	
	for (;;)
	{
		entity->cache();
		std::this_thread::sleep_for(std::chrono::milliseconds(11));
	}
}

bool SearchFileRecursive(const std::string& directory, const char* filename) {
	std::string searchPath = directory + "\\*.*";
	WIN32_FIND_DATA findFileData;
	HANDLE hFind = FindFirstFile(searchPath.c_str(), &findFileData);

	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
				if (strcmp(findFileData.cFileName, ".") != 0 && strcmp(findFileData.cFileName, "..") != 0) {
					std::string subdirectory = directory + "\\" + findFileData.cFileName;
					if (SearchFileRecursive(subdirectory, filename)) {
						return true;
					}
				}
			}
			else {
				if (strcmp(findFileData.cFileName, filename) == 0) {
					std::cout << "File found: " << directory + "\\" + filename << std::endl;
					return true;
				}
			}
		} while (FindNextFile(hFind, &findFileData) != 0);
		FindClose(hFind);
	}
	return false;
}

DWORD Get_PID(LPCWSTR processName)
{
	HANDLE handle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	DWORD procID = NULL;

	if (handle == INVALID_HANDLE_VALUE)
		return procID;


	PROCESSENTRY32W entry = { 0 };
	entry.dwSize = sizeof(PROCESSENTRY32W);

	if (Process32FirstW(handle, &entry)) {
		if (!_wcsicmp(processName, entry.szExeFile)) {
			procID = entry.th32ProcessID;
		}
		else while (Process32NextW(handle, &entry)) {
			if (!_wcsicmp(processName, entry.szExeFile)) {
				procID = entry.th32ProcessID;
			}
		}
	}

	CloseHandle(handle);
	return procID;
}
auto init_driver() -> void
{
	system(_("cls"));
	if (!driver.init())
	{
		Sleep(3500);
		exit(0);
	}
	globals->pid = Get_PID(_(L"FortniteClient-Win64-Shipping.exe"));
	driver.attach(globals->pid);
	globals->imagebase = driver.get_process_base(globals->pid);
	system(_("cls"));

}
auto driver_map() -> void
{
	system(_("cls"));
	int choice;
	printf(_("\n [1] Load Cheat with Driver\n [2] Load Cheat without Driver\n  \n\n > "));
	std::cin >> choice;
	switch (choice) {
	case 1:
		driver_mapper();
		break;
	case 2:
		break;
	}
	system(_("cls"));
}
void main()
{
	/*const char* filenameToSearch = "x64dbg.dll";

	for (char drive = 'A'; drive <= 'Z'; ++drive) {
		std::string drivePath = std::string(1, drive) + ":\\";
		bool hasX64DBGInstalled = SearchFileRecursive(drivePath, filenameToSearch);
	}*/
	//std::thread([&]() { for (;;) { AntiCrack::Tick(); } }).detach();

	//std::cout << _("\n [i] Loading...\n");
	auth();
	driver_map();

	std::cout << _("\n [i] Waiting For Fortnite...\n");
	while (hwnd == NULL)
	{
		hwnd = FindWindowA(0, _("Fortnite  "));
		Sleep(100);
	}
	
	init_driver();
	Mouse::Init();
	globals->width = GetSystemMetrics(SM_CXSCREEN);
	globals->height = GetSystemMetrics(SM_CYSCREEN);
	

	
	if (!render->hijack())
	{
		if (globals->developermode)
		{
			MessageBoxA(0, _("overlay failure"), _(" "), MB_OK);
			exit(0);
		}
		else
		{
			MessageBoxA(0, _("{!} Cheat failed"), _(""), MB_ICONINFORMATION);
			exit(0);
		}
	}
	
	render->initiate();
	render->draw();

	//std::thread([&]() { for (;;) { Cinit(); } }).detach();

	//system(_("pause"));
}

#endif