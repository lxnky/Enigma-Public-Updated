#include <Windows.h>
#include <iostream>
#include "driver.h"
#include "defs.h"
#include "../../frontend/protection/encryption/function/spoof.hpp"

#include "../../frontend/protection/encryption/string/xor.hpp"
#define win_1803 17134
#define win_1809 17763
#define win_1903 18362
#define win_1909 18363
#define win_2004 19041
#define win_20H2 19569
#define win_21H1 20180
#define win_22H2 20180
kernel::driver::driver() : pid(0u)
{}

kernel::driver::~driver()
{}



typedef __int64(__fastcall* pfunc_hk_t)(uintptr_t a1);
pfunc_hk_t pHookFunc = (pfunc_hk_t)NULL;



template<bool debug>
bool invoke_driver(fptr_data::kernel_com* com, fptr_data::kernel_opr op)
{
	SPOOF;
	if (!pHookFunc) return false;

	com->error = fptr_data::kernel_err::unset_err;
	com->opr = op;
	if (!pHookFunc((uintptr_t)com) &&
		com->error == fptr_data::kernel_err::unset_err)
	{
		printf(_("Driver not loaded.\n"));
		return false;
	}

	if (com->success) return true && com->error == fptr_data::kernel_err::no_error;
	if (!debug) return false;

	switch (com->error)
	{
	case fptr_data::kernel_err::check_fail:
	{
		printf(_("Security check failure.\n"));
		break;
	}
	case fptr_data::kernel_err::invalid_data:
	{
		//printf(("Invalid data.\n"));
		break;
	}
	case fptr_data::kernel_err::invalid_process:
	{
		printf(_("Invalid process.\n"));
		break;
	}
	case fptr_data::kernel_err::no_operation:
	{
		printf(_("Invalid funciton operation sent to driver.\n"));
		break;
	}
	}
	return false;
}




HMODULE ensure_dll_load()
{
	SPOOF;
#define LOAD_DLL(str) LoadLibrary((str))

	LOAD_DLL(_("user32.dll"));

#undef LOAD_DLL
	return LoadLibrary(_("win32u.dll"));
}


bool kernel::driver::init()
{

	SPOOF;
	if (!pHookFunc)
	{
		HMODULE hDll = GetModuleHandle(_("win32u.dll"));
		if (!hDll)
		{
			hDll = ensure_dll_load();
			if (!hDll) return false;
		}

		pHookFunc = (pfunc_hk_t)GetProcAddress(hDll, (_("NtGdiXLATEOBJ_hGetColorTransform")));
		if (!pHookFunc)
		{
			pHookFunc = (pfunc_hk_t)NULL;
			return false;
		}
	}

	if (get_process_base(GetCurrentProcessId()) != (uintptr_t)GetModuleHandle(NULL))
		return false;
	return true;
}



uintptr_t kernel::driver::get_process_module(const char* name)
{
	SPOOF;
	fptr_data::kernel_com com{};
	com.target_pid = this->pid;
	com.name = name;

	if (!invoke_driver<true>(&com, fptr_data::kernel_opr::get_process_module))
		return 0;
	return com.buffer;
}

uintptr_t kernel::driver::get_process_base(uint32_t _pid)
{
	SPOOF;
	fptr_data::kernel_com com{};
	com.target_pid = _pid ? _pid : this->pid;

	if (invoke_driver<true>(&com, fptr_data::kernel_opr::get_process_base))
		return com.buffer;
	return 0;
}


bool kernel::driver::read_buffer(uintptr_t addr, uint8_t* buffer, size_t size, size_t* transfer)
{
	SPOOF;
	fptr_data::kernel_com com{};
	com.target_pid = this->pid;
	com.user_pid = GetCurrentProcessId();

	com.address = addr;
	com.buffer = (uintptr_t)buffer;
	com.size = size;

	if (!invoke_driver<true>(&com, fptr_data::kernel_opr::read))
		return false;

	if (transfer)
		*transfer = com.transfer;
	return true;
}

bool kernel::driver::write_buffer(uintptr_t addr, uint8_t* buffer, size_t size, size_t* transfer)
{
	SPOOF;
	fptr_data::kernel_com com{};
	com.target_pid = this->pid;
	com.user_pid = GetCurrentProcessId();

	com.address = addr;
	com.buffer = (uintptr_t)buffer;
	com.size = size;

	if (!invoke_driver<true>(&com, fptr_data::kernel_opr::write))
		return false;

	if (transfer)
		*transfer = com.transfer;
	return true;
}

