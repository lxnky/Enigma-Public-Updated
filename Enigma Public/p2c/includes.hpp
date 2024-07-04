#pragma once
#ifndef INCLUDES
#define INCLUDES

#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include <iostream>
#include <vector>
#include <TlHelp32.h>
#include <stdio.h>
#include <string_view>
#include <chrono>
#include <wtypes.h>
#include <dwmapi.h>
#include <cstdint>
#include <thread>

#include "frontend/protection/encryption/function/spoof.hpp"
#include "frontend/protection/encryption/string/xor.hpp"
#include "frontend/protection/encryption/function/lazy.h"

#include "backend/globals.hpp"

#include "backend/game/offsets.hpp"
#include "backend/game/world/sdk/worldtoscreen.hpp"

#include "backend/framework/d3d/d3dx9math.h"
#include "backend/framework/d3d/d3dx9.h"
#include "backend/framework/imgui/imgui.h"
#include "backend/framework/imgui/imgui_impl_win32.h"
#include "backend/framework/imgui/imgui_impl_dx11.h"
#include "backend/framework/imgui/imgui_impl_win32.cpp"

#include "backend/kernel/driver.h"
#include "backend/game/utils.h"
#include "backend/game/world/overlay/render.hpp"
#include "backend/game/world/overlay/overlay.hpp"
#include "backend/game/world/sdk/decrypt.hpp"
#include "backend/game/world/entity.hpp"
#endif



