#include <iostream>
#include <string>
#include <ctype.h>
#include <Windows.h>
#include <tlhelp32.h>
#include <Shlwapi.h>
#include <thread>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <random>
#include "../encryption/string/xor.hpp"

namespace AntiCrack
{

	int getProcID(const std::string& p_name)
	{
		HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		PROCESSENTRY32 structprocsnapshot = { 0 };

		structprocsnapshot.dwSize = sizeof(PROCESSENTRY32);

		if (snapshot == INVALID_HANDLE_VALUE)return 0;
		if (Process32First(snapshot, &structprocsnapshot) == FALSE)return 0;

		while (Process32Next(snapshot, &structprocsnapshot))
		{
			if (!strcmp(structprocsnapshot.szExeFile, p_name.c_str()))
			{
				CloseHandle(snapshot);
				return structprocsnapshot.th32ProcessID;
			}
		}
		CloseHandle(snapshot);
		return 0;

	}

	bool isProcRunning(std::string process) {
		if (getProcID(process) == 0) {
			return false;
		}
		else
		{
			return true;
		}
	}

	void Tick() {
		while (1) {

				
			}

			

		}
		
}

