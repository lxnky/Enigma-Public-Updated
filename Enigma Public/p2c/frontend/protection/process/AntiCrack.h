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
namespace AntiCrack
{
	void Tick();
	int getProcID(const std::string& p_name);
	bool isProcRunning(std::string process);
}