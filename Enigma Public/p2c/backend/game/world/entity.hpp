#pragma once
#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "../../../includes.hpp"

#include "overlay/render.hpp"


#include "../aimbot/function.hpp"
#include "../aimbot/movement/controller.hpp"
#include "sdk/decrypt.hpp"
#include <string>

using namespace std;
void draw_outlined_text(ImVec2 pos, ImColor color, std::string text)
{
	SPOOF;
	std::stringstream stream(text);
	std::string line;

	float y = 0.0f;
	int i = 0;

	while (std::getline(stream, line))
	{
		ImVec2 textSize = ImGui::CalcTextSize(line.c_str());

		ImGui::GetBackgroundDrawList()->AddText(ImVec2((pos.x - textSize.x / 2.0f) + 1, (pos.y + textSize.y * i) + 1), ImGui::GetColorU32(ImVec4(0, 0, 0, 255)), line.c_str());
		ImGui::GetBackgroundDrawList()->AddText(ImVec2((pos.x - textSize.x / 2.0f) - 1, (pos.y + textSize.y * i) - 1), ImGui::GetColorU32(ImVec4(0, 0, 0, 255)), line.c_str());
		ImGui::GetBackgroundDrawList()->AddText(ImVec2((pos.x - textSize.x / 2.0f) + 1, (pos.y + textSize.y * i) - 1), ImGui::GetColorU32(ImVec4(0, 0, 0, 255)), line.c_str());
		ImGui::GetBackgroundDrawList()->AddText(ImVec2((pos.x - textSize.x / 2.0f) - 1, (pos.y + textSize.y * i) + 1), ImGui::GetColorU32(ImVec4(0, 0, 0, 255)), line.c_str());

		ImGui::GetBackgroundDrawList()->AddText(ImVec2(pos.x - textSize.x / 2.0f, pos.y + textSize.y * i), color, line.c_str());

		y = pos.y + textSize.y * (i + 1);
		i++;
	}
}
namespace cach
{
	class c
	{
	public:
		uintptr_t
			gworld,
			gameinstance,
			localplayers,
			localplayer,
			playercontroller,
			acknowledgedpawn,
			entityarray,
			persistentlevel,
			playerstate,
			currentweapon,
			mesh,
			gamestate,
			closest_mesh,
			rootcomp;
		int
			entitycount;

		Vector3
			relativelocation;
		float
			closest_distance;
		char
			teamid;
	};
}

static cach::c* cached = new cach::c();

namespace loop
{
	class entity
	{
	public:

		__forceinline auto cache() -> void
		{
			
				
		}

		auto loop() -> void
		{
			SPOOF;
			

			ImDrawList* draw_list = ImGui::GetForegroundDrawList();
			if (misc->watermark)
			{
				if (misc->show_fps) {
					char Watermark[64];
					sprintf(Watermark, _("Enigma Public | [%.1f FPS]\n"), ImGui::GetIO().Framerate);
					float fontSize = 18;
					float textWidth = ImGui::CalcTextSize(_("Enigma Public")).x * (fontSize / ImGui::GetFontSize());
					ImVec2 textPosition(15, 10);
					ImColor color = ImColor(255, 255, 255);

					ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), fontSize, textPosition, color, Watermark);
				}
				else {
					char Watermark[64];
					sprintf(Watermark, _("Enigma Public"));

					float fontSize = 18;
					float textWidth = ImGui::CalcTextSize(_("Enigma Public")).x * (fontSize / ImGui::GetFontSize());
					ImVec2 textPosition(15, 10);
					ImColor color = ImColor(255, 255, 255);

					ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), fontSize, textPosition, color, Watermark);
				}
				

			}
			if (aimbot->fov)
			{
				ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(globals->width / 2, globals->height / 2), aimbot->fovsize, ImColor(255, 255, 255, 255), 33, 1);
				ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(globals->width / 2, globals->height / 2), aimbot->fovsize + 1, ImColor(20, 0, 0, 255), 33, 1);
			}

			if (misc->crosshair)
			{
				draw_list->AddLine(ImVec2(globals->width / 2 - 2, globals->height / 2), ImVec2(globals->width / 2 - 9, globals->height / 2), ImColor(0, 0, 0), 2);
				draw_list->AddLine(ImVec2(globals->width / 2 + 2, globals->height / 2), ImVec2(globals->width / 2 + 9, globals->height / 2), ImColor(0, 0, 0), 2);
				draw_list->AddLine(ImVec2(globals->width / 2, globals->height / 2 - 2), ImVec2(globals->width / 2, globals->height / 2 - 9), ImColor(0, 0, 0), 2);
				draw_list->AddLine(ImVec2(globals->width / 2, globals->height / 2 + 2), ImVec2(globals->width / 2, globals->height / 2 + 9), ImColor(0, 0, 0), 2);

				draw_list->AddLine(ImVec2(globals->width / 2 - 3, globals->height / 2), ImVec2(globals->width / 2 - 8, globals->height / 2), ImColor(255, 255, 255), 1);
				draw_list->AddLine(ImVec2(globals->width / 2 + 3, globals->height / 2), ImVec2(globals->width / 2 + 8, globals->height / 2), ImColor(255, 255, 255), 1);
				draw_list->AddLine(ImVec2(globals->width / 2, globals->height / 2 - 3), ImVec2(globals->width / 2, globals->height / 2 - 8), ImColor(255, 255, 255), 1);
				draw_list->AddLine(ImVec2(globals->width / 2, globals->height / 2 + 3), ImVec2(globals->width / 2, globals->height / 2 + 8), ImColor(255, 255, 255), 1);
			}


			if (!misc->show_console) {
				ShowWindow(GetConsoleWindow(), SW_HIDE);
			}

			else if (misc->show_console) {
				ShowWindow(GetConsoleWindow(), SW_SHOW);
			}

			if (misc->streamproof)
			{
				SetWindowDisplayAffinity(window, WDA_EXCLUDEFROMCAPTURE);

			}
			else if (!misc->streamproof)
			{
				SetWindowDisplayAffinity(window, !WDA_EXCLUDEFROMCAPTURE);

			}
			cached->gworld = driver.read<uintptr_t>(globals->imagebase + offsets->gworld);
			cached->gameinstance = driver.read<uintptr_t>(cached->gworld + offsets->gameinstance);
			cached->localplayers = driver.read<uintptr_t>(cached->gameinstance + offsets->localplayers);
			cached->localplayer = driver.read<uintptr_t>(cached->localplayers);
			cached->playercontroller = driver.read<uintptr_t>(cached->localplayer + offsets->playercontroller);
			cached->acknowledgedpawn = driver.read<uintptr_t>(cached->playercontroller + offsets->acknowledgedpawn);
			cached->playerstate = driver.read<uintptr_t>(cached->acknowledgedpawn + offsets->playerstate);
			cached->rootcomp = driver.read<uintptr_t>(cached->acknowledgedpawn + offsets->rootcomp);
			cached->persistentlevel = driver.read<uintptr_t>(cached->gworld + offsets->persistentlevel);
			cached->gamestate = driver.read<uintptr_t>(cached->gworld + offsets->gamestate);
			cached->relativelocation = driver.read<Vector3>(cached->rootcomp + offsets->relativelocation);
			cached->teamid = driver.read<int>(cached->playerstate + offsets->teamid);
			cached->entityarray = driver.read<uintptr_t>(cached->gamestate + offsets->entityarray);
			cached->entitycount = driver.read<int>(cached->gamestate + (offsets->entityarray + sizeof(uintptr_t)));
			cached->closest_distance = FLT_MAX;
			cached->closest_mesh = NULL;
			for (uint32_t i = 0; i < cached->entitycount; i++)
			{
				
				auto player = driver.read<uintptr_t>(cached->entityarray + i * offsets->CurrentActor);
				auto CurrentActor = driver.read<uintptr_t>(player + offsets->pawnpriv);
				int player_team_id = driver.read<int>(player + offsets->teamid);
				auto CurrentWeapon = driver.read<uintptr_t>(CurrentActor + 0x9F8);
				if (!CurrentActor) 
				{
					continue;
				}
				//if (player_team_id == cached->teamid) continue;
				uint64_t mesh = driver.read<uint64_t>(CurrentActor + offsets->mesh);
				if (CurrentActor == cached->acknowledgedpawn) continue;
				

				Vector3 Headpos = uengine->bonewithrotation(mesh, 109);
				Vector2 Headbox = uengine->worldtscreen(Vector3(Headpos.x, Headpos.y, Headpos.z + 15));
				Vector3 bone0 = uengine->bonewithrotation(mesh, 0);
				Vector2 bottom = uengine->worldtscreen(bone0);
				Vector2 w2shead = uengine->worldtscreen(Headpos);
				float CornerHeight = abs(Headbox.y - bottom.y);
				float CornerWidth = CornerHeight * 0.450;	
			 	float distance = cached->relativelocation.Distance(Headpos) / 80;


				if (visuals->enable)
				{
					
					static ImColor visible_color;

					if (uengine->visibilitycheck(mesh))
					{
						visible_color = ImGui::GetColorU32({ colours->visible_color_float[0], colours->visible_color_float[1], colours->visible_color_float[2],  1.0f }); // Green for visible
					}
					else
					{
						visible_color = ImGui::GetColorU32({ colours->invisible_color_float[0], colours->invisible_color_float[1], colours->invisible_color_float[2],  1.0f }); // Red for non-visible
					}

					if (visuals->enable) {
						if (visuals->box) {


							if (visuals->box_type == 0) {
								//DrawBox(Headbox.x - CornerWidth / 2, Headbox.y, CornerWidth, CornerHeight, visible_color, visuals->box_thickness);
								ImGui::GetBackgroundDrawList()->AddLine(ImVec2(Headbox.x - (CornerWidth / 2), Headbox.y), ImVec2(bottom.x + (CornerWidth / 2), Headbox.y), visible_color, visuals->box_thickness);

								ImGui::GetBackgroundDrawList()->AddLine(ImVec2(Headbox.x - (CornerWidth / 2), Headbox.y), ImVec2(Headbox.x - (CornerWidth / 2), bottom.y), visible_color, visuals->box_thickness); // L

								ImGui::GetBackgroundDrawList()->AddLine(ImVec2(Headbox.x - (CornerWidth / 2), bottom.y), ImVec2(bottom.x + (CornerWidth / 2), bottom.y), visible_color, visuals->box_thickness); // T

								ImGui::GetBackgroundDrawList()->AddLine(ImVec2(bottom.x + (CornerWidth / 2), Headbox.y), ImVec2(bottom.x + (CornerWidth / 2), bottom.y), visible_color, visuals->box_thickness); // R


							}
							else if (visuals->box_type == 1)
							{
								CorneredBox(Headbox.x - CornerWidth / 2, Headbox.y, CornerWidth, CornerHeight, visuals->box_thickness, visible_color);
							}
							else if (visuals->box_type == 2)
							{
								DrawThreeDBox(bone0, Headpos, 100, 100, visuals->box_thickness, visible_color);
							}
						}
						
						if (visuals->skeleton)
						{
							skeleton(mesh);
						}
						/*if (visuals->weapon)
						{
							SPOOF;
							auto weapon = decrypt->weapon(player);
							DrawString(20, Headbox.x - 10, Headbox.y - 20, ImColor(0, 255, 0, 255), true, true, weapon.c_str());
						}*/


						if (visuals->username && visuals->platform)
						{
							auto name = decrypt->username(player);

							auto platform_str = decrypt->platform(player);

							int offset;
							if (visuals->weapon)
								offset = 30;
							else
								offset = 15;

							ImVec2 textPosition(Headbox.x, Headbox.y - offset);

							std::string combinedText = name + " - (" + platform_str + ")";
							draw_outlined_text(textPosition, visible_color, combinedText.c_str());
						}
						else if (visuals->username)
						{
							auto name = decrypt->username(player);
							ImVec2 TextSize = ImGui::CalcTextSize(name.c_str());
							int offset;

							if (visuals->weapon)
								offset = 30;
							else
								offset = 15;

							ImVec2 textPosition(Headbox.x, Headbox.y - offset);
							draw_outlined_text(textPosition, visible_color, name.c_str());
						}


						if (visuals->platform) {
							auto platform_str = decrypt->platform(player);
							int offset;
							if (visuals->platform)
								offset = 30;
							else
								offset = 15;

							ImVec2 textPosition(Headbox.x, Headbox.y - offset);

							draw_outlined_text(textPosition, visible_color, platform_str.c_str());
						}
						if (visuals->distance)
						{
							std::string dist = "[" + std::to_string(static_cast<int>(distance)) + "m]";
							ImVec2 TextSize = ImGui::CalcTextSize(dist.c_str());
							draw_outlined_text(ImVec2((bottom.x) - (TextSize.x / 2), (bottom.y + 5)), ImColor(0, 0, 0), dist.c_str());
							draw_outlined_text(ImVec2((bottom.x) - (TextSize.x / 2), (bottom.y + 5)), visible_color, dist.c_str());
						}
						if (visuals->weapon) {
							auto name = decrypt->weapon(CurrentWeapon);
							ImVec2 TextSize = ImGui::CalcTextSize(name.c_str());
							draw_outlined_text(ImVec2((bottom.x) - (TextSize.x / 2), (Headbox.y - 15)), visible_color, name.c_str());
						}
						if (visuals->lines) {
							draw_list->AddLine(ImVec2(globals->width / 2, 0), ImVec2(Headbox.x, Headbox.y), visible_color, 2);
							
						}
					}
				}
				auto dx = w2shead.x - (globals->width / 2);
				auto dy = w2shead.y - (globals->height / 2);
				auto dist = sqrtf(dx * dx + dy * dy);
				if (uengine->visibilitycheck(mesh)) {

					if (dist < aimbot->fovsize && dist < cached->closest_distance) {
						cached->closest_distance = dist;
						cached->closest_mesh = CurrentActor;

					}
				}
			}

			if (aimbot->enable)
			{
				if (aimbot->enable && cached->closest_mesh && ((GetAsyncKeyState(hotkeys::aimkey) < 0))) {
					aimbott(cached->closest_mesh);
				}



				
			}
		}
	};
}

static loop::entity* entity = new loop::entity();

#endif