#pragma once
#include "../../backend/mapper/mapper/kdmapper.hpp"
#include "../../backend/mapper/utils/driver.h"
HANDLE iqvw64e_device_handle;
using namespace kdmapper;
using namespace intel_driver;


auto driver_mapper() -> int
{
	HANDLE device_handler = Load();

	if (!device_handler || device_handler == INVALID_HANDLE_VALUE)
	{
		return -1;
	}

	if (!MapDriverBytes(device_handler, RawData))
	{
		Unload(device_handler);
		return -1;
	}

	Unload(device_handler);
}