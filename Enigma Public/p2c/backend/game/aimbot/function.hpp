#pragma once
#ifndef MOUSE
#define MOUSE
#include <iostream>
#include <coroutine>
#include "../../framework/imgui/imgui.h"
#include "../../globals.hpp"

#include "movement/mouse.hpp"
#include "movement/controller.hpp"

static auto aimfunction(float x, float y) -> void
{
	SPOOF;
	
	float ScreenCenterX = (globals->width / 2);
	float ScreenCenterY = (globals->height / 2);
	int AimSpeed = aimbot->smoothing;
	float TargetX = 0;
	float TargetY = 0;

	if (x != 0)
	{
		if (x > ScreenCenterX)
		{
			TargetX = -(ScreenCenterX - x);
			TargetX /= AimSpeed;
			if (TargetX + ScreenCenterX > ScreenCenterX * 2) TargetX = 0;
		}

		if (x < ScreenCenterX)
		{
			TargetX = x - ScreenCenterX;
			TargetX /= AimSpeed;
			if (TargetX + ScreenCenterX < 0) TargetX = 0;
		}
	}

	if (y != 0)
	{
		if (y > ScreenCenterY)
		{
			TargetY = -(ScreenCenterY - y);
			TargetY /= AimSpeed;
			if (TargetY + ScreenCenterY > ScreenCenterY * 2) TargetY = 0;
		}

		if (y < ScreenCenterY)
		{
			TargetY = y - ScreenCenterY;
			TargetY = y - ScreenCenterY;
			TargetY /= AimSpeed;
			if (TargetY + ScreenCenterY < 0) TargetY = 0;
		}
	}

	
	//SPOOF_CALL(mouse_event, MOUSEEVENTF_MOVE, static_cast<DWORD>(TargetX), static_cast<DWORD>(TargetY), NULL, NULL);
	mouse_event(MOUSEEVENTF_MOVE, static_cast<DWORD>(TargetX), static_cast<DWORD>(TargetY), NULL, NULL);
	/*driver.write(cachedplayercontroller + 0x520, TargetX);
	driver.write(cachedplayercontroller + 0x520, TargetY);*/
	return;
}

__int64 TargetedBuild;
bool bTargetedBuild;
class CKey {
private:
	BYTE bPrevState[0x100];
public:
	CKey() {
		memset(bPrevState, 0, sizeof(bPrevState));
	}

	BOOL IsKeyPushing(BYTE vKey) {
		SPOOF;

		return GetAsyncKeyState(vKey) & 0x8000;
	}

	BOOL IsKeyPushed(BYTE vKey) {
		SPOOF;

		BOOL bReturn = FALSE;

		if (IsKeyPushing(vKey))
			bPrevState[vKey] = TRUE;
		else
		{
			if (bPrevState[vKey] == TRUE)
				bReturn = TRUE;
			bPrevState[vKey] = FALSE;
		}

		return bReturn;
	}
};
CKey Key;

void trigger() {
	INPUT    Input = { 0 };
	// left down 
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
	::SendInput(1, &Input, sizeof(INPUT));
	// left up
	std::this_thread::sleep_for(std::chrono::milliseconds(11));
	::ZeroMemory(&Input, sizeof(INPUT));
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
	::SendInput(1, &Input, sizeof(INPUT));
}
void aimbott(DWORD_PTR entity) {
	SPOOF;
	uintptr_t cachedgworld = driver.read<uintptr_t>(globals->imagebase + offsets->gworld);
	uintptr_t cachedgameinstance = driver.read<uintptr_t>(cachedgworld + offsets->gameinstance);
	uintptr_t cachedlocalplayers = driver.read<uintptr_t>(cachedgameinstance + offsets->localplayers);
	uintptr_t cachedlocalplayer = driver.read<uintptr_t>(cachedlocalplayers);
	uintptr_t cachedplayercontroller = driver.read<uintptr_t>(cachedlocalplayer + offsets->playercontroller);
	Vector2 screen_center = { static_cast<double>(globals->width) / 2, static_cast<double>(globals->height) / 2 };
	Vector2 target{};
	Vector2 bone;
	uint64_t currentactormesh = driver.read<uint64_t>(entity + offsets->mesh);
	if (aimbot->bone == 0) {
		bone = uengine->worldtscreen(uengine->bonewithrotation(currentactormesh, 109));
	}
	else if (aimbot->bone == 1) {
		bone = uengine->worldtscreen(uengine->bonewithrotation(currentactormesh, 67));
	}
	else if (aimbot->bone == 2) {
		Vector2 chest_left = uengine->worldtscreen(uengine->bonewithrotation(currentactormesh, 37));
		Vector2 chest_right = uengine->worldtscreen(uengine->bonewithrotation(currentactormesh, 8));
		bone = { chest_left.x + (chest_right.x - chest_left.x) / 2, chest_left.y };
	}

	target.x = (bone.x > screen_center.x) ? -(screen_center.x - bone.x) : bone.x - screen_center.x;
	target.x /= aimbot->smoothing;
	target.x = (target.x + screen_center.x > screen_center.x * 2 || target.x + screen_center.x < 0) ? 0 : target.x;

	target.y = (bone.y > screen_center.y) ? -(screen_center.y - bone.y) : bone.y - screen_center.y;
	target.y /= aimbot->smoothing;
	target.y = (target.y + screen_center.y > screen_center.y * 2 || target.y + screen_center.y < 0) ? 0 : target.y;

	Vector3 Angles(-target.y / aimbot->smoothing, target.x / aimbot->smoothing, 0);

	Vector3 original1(0, 0, 0);
	//if (aimbot->enable && (Controller::IsPressingLeftTrigger() || GetAsyncKeyState(aimkey) < 0)) {
		driver.write(cachedplayercontroller + 0x520, Angles.x);
		driver.write(cachedplayercontroller + 0x520 + 0x8, Angles.y);
	//}
	if (aimbot->triggerbot){ //&& ( Controller::IsPressingLeftTrigger() || GetAsyncKeyState(aimkey) < 0)) {
		
		std::thread t(trigger);

		// Wait for the thread to finish
		t.join();
	}

	
	
	
	

}
#endif 
