#pragma once
#include "../../includes.hpp"
#include "aimbot/function.hpp"
#define IM_ARRAYSIZE(_ARR)          ((int)(sizeof(_ARR)/sizeof(*_ARR)))
typedef struct
{
	DWORD R;
	DWORD G;
	DWORD B;
	DWORD A;
}RGBA;


char* wchar_to_char(const wchar_t* pwchar)
{
	int currentCharIndex = 0;
	char currentChar = pwchar[currentCharIndex];

	while (currentChar != '\0')
	{
		currentCharIndex++;
		currentChar = pwchar[currentCharIndex];
	}

	const int charCount = currentCharIndex + 1;

	char* filePathC = (char*)malloc(sizeof(char) * charCount);

	for (int i = 0; i < charCount; i++)
	{
		char character = pwchar[i];

		*filePathC = character;

		filePathC += sizeof(char);

	}
	filePathC += '\0';

	filePathC -= (sizeof(char) * charCount);

	return filePathC;
}

void AimAt(DWORD_PTR entity)
{
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
	
	if (bone.y != 0 || bone.y != 0)
	{
		aimfunction(bone.x, bone.y);
	}
}
void DrawLine(int x1, int y1, int x2, int y2, const ImColor color, int thickness)
{
	static ImVec2 p1;
	static ImVec2 p2;

	p1.x = static_cast<float>(x1);
	p1.y = static_cast<float>(y1);

	p2.x = static_cast<float>(x2);
	p2.y = static_cast<float>(y2);

	ImGui::GetBackgroundDrawList()->AddLine(p1, p2, color, thickness);
}

__forceinline auto skeleton(uintptr_t mesh) -> void
{
	const int color = ImColor(1.0f, 1.0f, 1.0f);

	// we are using a array to initializes it with bone positions to make the code more clean   - Bender
	Vector3 bonePositions[] = {
		uengine->bonewithrotation(mesh, 109),  // HeadBone
		uengine->bonewithrotation(mesh, 2),   // Hip
		uengine->bonewithrotation(mesh, 67),  // Neck
		uengine->bonewithrotation(mesh, 9),   // UpperArmLeft
		uengine->bonewithrotation(mesh, 38),  // UpperArmRight
		uengine->bonewithrotation(mesh, 10),  // LeftHand
		uengine->bonewithrotation(mesh, 39),  // RightHand
		uengine->bonewithrotation(mesh, 11),  // LeftHand1
		uengine->bonewithrotation(mesh, 40),  // RightHand1
		uengine->bonewithrotation(mesh, 78),  // RightThigh
		uengine->bonewithrotation(mesh, 71),  // LeftThigh
		uengine->bonewithrotation(mesh, 79),  // RightCalf
		uengine->bonewithrotation(mesh, 72),  // LeftCalf
		uengine->bonewithrotation(mesh, 74),  // LeftFoot
		uengine->bonewithrotation(mesh, 81)   // RightFoot
	};

	Vector2 bonePositionsOut[16];
	for (int i = 0; i < 16; ++i) {
		bonePositionsOut[i] = uengine->worldtscreen(bonePositions[i]);
	}


	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(bonePositionsOut[1].x, bonePositionsOut[1].y), ImVec2(bonePositionsOut[2].x, bonePositionsOut[2].y), color, 1.0f);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(bonePositionsOut[3].x, bonePositionsOut[3].y), ImVec2(bonePositionsOut[2].x, bonePositionsOut[2].y), color, 1.0f);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(bonePositionsOut[4].x, bonePositionsOut[4].y), ImVec2(bonePositionsOut[2].x, bonePositionsOut[2].y), color, 1.0f);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(bonePositionsOut[5].x, bonePositionsOut[5].y), ImVec2(bonePositionsOut[3].x, bonePositionsOut[3].y), color, 1.0f);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(bonePositionsOut[6].x, bonePositionsOut[6].y), ImVec2(bonePositionsOut[4].x, bonePositionsOut[4].y), color, 1.0f);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(bonePositionsOut[5].x, bonePositionsOut[5].y), ImVec2(bonePositionsOut[7].x, bonePositionsOut[7].y), color, 1.0f);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(bonePositionsOut[6].x, bonePositionsOut[6].y), ImVec2(bonePositionsOut[8].x, bonePositionsOut[8].y), color, 1.0f);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(bonePositionsOut[10].x, bonePositionsOut[10].y), ImVec2(bonePositionsOut[1].x, bonePositionsOut[1].y), color, 1.0f);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(bonePositionsOut[9].x, bonePositionsOut[9].y), ImVec2(bonePositionsOut[1].x, bonePositionsOut[1].y), color, 1.0f);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(bonePositionsOut[12].x, bonePositionsOut[12].y), ImVec2(bonePositionsOut[10].x, bonePositionsOut[10].y), color, 1.0f);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(bonePositionsOut[11].x, bonePositionsOut[11].y), ImVec2(bonePositionsOut[9].x, bonePositionsOut[9].y), color, 1.0f);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(bonePositionsOut[13].x, bonePositionsOut[13].y), ImVec2(bonePositionsOut[12].x, bonePositionsOut[12].y), color, 1.0f);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(bonePositionsOut[14].x, bonePositionsOut[14].y), ImVec2(bonePositionsOut[11].x, bonePositionsOut[11].y), color, 1.0f);

}
inline double GetCrossDistance(double x1, double y1, double x2, double y2) {
	return sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
}
inline std::wstring MBytesToWString(const char* lpcszString)
{
	SPOOF;

		int len = strlen(lpcszString);
	int unicodeLen = ::MultiByteToWideChar(CP_ACP, 0, lpcszString, -1, NULL, 0);
	wchar_t* pUnicode = new wchar_t[unicodeLen + 1];
	memset(pUnicode, 0, (unicodeLen + 1) * sizeof(wchar_t));
	::MultiByteToWideChar(CP_ACP, 0, lpcszString, -1, (LPWSTR)pUnicode, unicodeLen);
	std::wstring wString = (wchar_t*)pUnicode;
	delete[] pUnicode;
	return wString;
}
inline std::string WStringToUTF8(const wchar_t* lpwcszWString)
{
	SPOOF;

		char* pElementText;
	int iTextLen = ::WideCharToMultiByte(CP_UTF8, 0, (LPWSTR)lpwcszWString, -1, NULL, 0, NULL, NULL);
	pElementText = new char[iTextLen + 1];
	memset((void*)pElementText, 0, (iTextLen + 1) * sizeof(char));
	::WideCharToMultiByte(CP_UTF8, 0, (LPWSTR)lpwcszWString, -1, pElementText, iTextLen, NULL, NULL);
	std::string strReturn(pElementText);
	delete[] pElementText;
	return strReturn;
}
inline void DrawString(float fontSize, int x, int y, ImColor color, bool bCenter, bool stroke, const char* pText, ...)
{
	va_list va_alist;
	char buf[1024] = { 0 };
	va_start(va_alist, pText);
	_vsnprintf_s(buf, sizeof(buf), pText, va_alist);
	va_end(va_alist);
	std::string text = WStringToUTF8(MBytesToWString(buf).c_str());
	if (bCenter)
	{
		ImVec2 textSize = ImGui::CalcTextSize(text.c_str());
		x = x - textSize.x / 4;
		y = y - textSize.y;
	}
	if (stroke)
	{
		ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x + 1, y + 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), text.c_str());
		ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x - 1, y - 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), text.c_str());
		ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x + 1, y - 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), text.c_str());
		ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x - 1, y + 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), text.c_str());
	}
	ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x, y), ImColor(color), text.c_str());
}

float DrawOutlinedText(ImFont* pFont, const std::string& text, const ImVec2& pos, float size, ImU32 color, bool center)
{
	std::stringstream stream(text);
	std::string line;

	float y = 0.0f;
	int i = 0;

	while (std::getline(stream, line))
	{
		ImVec2 textSize = pFont->CalcTextSizeA(size, FLT_MAX, 0.0f, line.c_str());

		if (center)
		{
			ImGui::GetBackgroundDrawList()->AddText(pFont, size, ImVec2((pos.x - textSize.x / 2.0f) + 1, (pos.y + textSize.y * i) + 1), ImGui::GetColorU32(ImVec4(0, 0, 0, 255)), line.c_str());
			ImGui::GetBackgroundDrawList()->AddText(pFont, size, ImVec2((pos.x - textSize.x / 2.0f) - 1, (pos.y + textSize.y * i) - 1), ImGui::GetColorU32(ImVec4(0, 0, 0, 255)), line.c_str());
			ImGui::GetBackgroundDrawList()->AddText(pFont, size, ImVec2((pos.x - textSize.x / 2.0f) + 1, (pos.y + textSize.y * i) - 1), ImGui::GetColorU32(ImVec4(0, 0, 0, 255)), line.c_str());
			ImGui::GetBackgroundDrawList()->AddText(pFont, size, ImVec2((pos.x - textSize.x / 2.0f) - 1, (pos.y + textSize.y * i) + 1), ImGui::GetColorU32(ImVec4(0, 0, 0, 255)), line.c_str());

			ImGui::GetBackgroundDrawList()->AddText(pFont, size, ImVec2(pos.x - textSize.x / 2.0f, pos.y + textSize.y * i), ImGui::GetColorU32(color), line.c_str());
		}
		else
		{
			ImGui::GetBackgroundDrawList()->AddText(pFont, size, ImVec2((pos.x) + 1, (pos.y + textSize.y * i) + 1), ImGui::GetColorU32(ImVec4(0, 0, 0, 255)), line.c_str());
			ImGui::GetBackgroundDrawList()->AddText(pFont, size, ImVec2((pos.x) - 1, (pos.y + textSize.y * i) - 1), ImGui::GetColorU32(ImVec4(0, 0, 0, 255)), line.c_str());
			ImGui::GetBackgroundDrawList()->AddText(pFont, size, ImVec2((pos.x) + 1, (pos.y + textSize.y * i) - 1), ImGui::GetColorU32(ImVec4(0, 0, 0, 255)), line.c_str());
			ImGui::GetBackgroundDrawList()->AddText(pFont, size, ImVec2((pos.x) - 1, (pos.y + textSize.y * i) + 1), ImGui::GetColorU32(ImVec4(0, 0, 0, 255)), line.c_str());

			ImGui::GetBackgroundDrawList()->AddText(pFont, size, ImVec2(pos.x, pos.y + textSize.y * i), ImGui::GetColorU32(color), line.c_str());
		}

		y = pos.y + textSize.y * (i + 1);
		i++;
	}
	return y;
}
void DrawThreeDBox(const Vector3& base, const Vector3& head, float width, float height, float tick, ImU32 color) {
	// Calculate the corner points
	Vector3 halfWidthOffset = { width / 2, 0, 0 };
	Vector3 halfHeightOffset = { 0, height / 2, 0 };

	Vector3 bottom1 = { base.x - halfWidthOffset.x, base.y - halfHeightOffset.y, base.z };
	Vector3 bottom2 = { base.x + halfWidthOffset.x, base.y - halfHeightOffset.y, base.z };
	Vector3 bottom3 = { base.x + halfWidthOffset.x, base.y + halfHeightOffset.y, base.z };
	Vector3 bottom4 = { base.x - halfWidthOffset.x, base.y + halfHeightOffset.y, base.z };

	Vector3 top1 = { head.x - halfWidthOffset.x, head.y - halfHeightOffset.y, head.z + 20 };
	Vector3 top2 = { head.x + halfWidthOffset.x, head.y - halfHeightOffset.y, head.z + 20 };
	Vector3 top3 = { head.x + halfWidthOffset.x, head.y + halfHeightOffset.y, head.z + 20 };
	Vector3 top4 = { head.x - halfWidthOffset.x, head.y + halfHeightOffset.y, head.z + 20 };

	// Project the 3D world coordinates to 2D screen coordinates
	Vector2 screenBottom1 = uengine->worldtscreen(bottom1);
	Vector2 screenBottom2 = uengine->worldtscreen(bottom2);
	Vector2 screenBottom3 = uengine->worldtscreen(bottom3);
	Vector2 screenBottom4 = uengine->worldtscreen(bottom4);

	Vector2 screenTop1 = uengine->worldtscreen(top1);
	Vector2 screenTop2 = uengine->worldtscreen(top2);
	Vector2 screenTop3 = uengine->worldtscreen(top3);
	Vector2 screenTop4 = uengine->worldtscreen(top4);

	// Draw the lines
	auto draw_list = ImGui::GetForegroundDrawList();
	ImVec2 points[] = { ImVec2(screenBottom1.x, screenBottom1.y), ImVec2(screenBottom2.x, screenBottom2.y), ImVec2(screenBottom3.x, screenBottom3.y), ImVec2(screenBottom4.x, screenBottom4.y),
						ImVec2(screenTop1.x, screenTop1.y), ImVec2(screenTop2.x, screenTop2.y), ImVec2(screenTop3.x, screenTop3.y), ImVec2(screenTop4.x, screenTop4.y) };

	for (int i = 0; i < 4; i++) {
		draw_list->AddLine(points[i], points[(i + 1) % 4], color, tick);
		draw_list->AddLine(points[i + 4], points[(i + 1) % 4 + 4], color, tick);
		draw_list->AddLine(points[i], points[i + 4], color, tick);
	}
}
void DrawLineXD(Vector2 ScreenPositionA, Vector2 ScreenPositionB, float Thickness, ImColor RenderColor) {
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(ScreenPositionA.x, ScreenPositionA.y), ImVec2(ScreenPositionB.x, ScreenPositionB.y), RenderColor, Thickness);
}

static auto DrawCircle(int x, int y, int radius, ImU32 color, int segments) -> void
{
	ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(x, y), radius, color, segments, 2);
}
void DrawFilledRect(int x, int y, int w, int h, ImU32 color)
{
	ImGui::GetForegroundDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), color, 0, 0);
}
void CorneredBox(int x, int y, int w, int h, int borderPx, ImU32 color)
{
	int borderWidth = (borderPx < (w / 2) && borderPx < (h / 2)) ? borderPx : ((w / 2) < (h / 2) ? (w / 2) : (h / 2));


	DrawFilledRect(x + borderWidth, y, w / 3, borderWidth, color);//, round_box); //top 
	DrawFilledRect(x + w - w / 3, y, w / 3, borderWidth, color); //top 
	DrawFilledRect(x, y, borderWidth, h / 3, color); //left 
	DrawFilledRect(x, y + h - h / 3, borderWidth, h / 3, color); //left 
	DrawFilledRect(x + borderWidth, y + h - borderWidth, w / 3, borderWidth, color); //bottom 
	DrawFilledRect(x + w - w / 3, y + h - borderWidth, w / 3, borderWidth, color); //bottom 
	DrawFilledRect(x + w - borderWidth, y, borderWidth, h / 3, color);//right 
	DrawFilledRect(x + w - borderWidth, y + h - h / 3, borderWidth, h / 3, color);//right 
}

void DrawBox(int X, int Y, int W, int H, ImU32 color, int thickness) {
	SPOOF;
	float lineW = (W / 1);
	float lineH = (H / 1);
	ImDrawList* Drawlist = ImGui::GetForegroundDrawList();
	Drawlist->AddLine(ImVec2(X, Y), ImVec2(X, Y + lineH), ImGui::GetColorU32(color), thickness);
	Drawlist->AddLine(ImVec2(X, Y), ImVec2(X + lineW, Y), ImGui::GetColorU32(color), thickness);
	Drawlist->AddLine(ImVec2(X + W - lineW, Y), ImVec2(X + W, Y), ImGui::GetColorU32(color), thickness);
	Drawlist->AddLine(ImVec2(X + W, Y), ImVec2(X + W, Y + lineH), ImGui::GetColorU32(color), thickness);
	Drawlist->AddLine(ImVec2(X, Y + H - lineH), ImVec2(X, Y + H), ImGui::GetColorU32(color), thickness);
	Drawlist->AddLine(ImVec2(X, Y + H), ImVec2(X + lineW, Y + H), ImGui::GetColorU32(color), thickness);
	Drawlist->AddLine(ImVec2(X + W - lineW, Y + H), ImVec2(X + W, Y + H), ImGui::GetColorU32(color), thickness);
	Drawlist->AddLine(ImVec2(X + W, Y + H - lineH), ImVec2(X + W, Y + H), ImGui::GetColorU32(color), thickness);
}

void draw_filled_rect(int x, int y, int w, int h, const ImColor color)
{
	ImGui::GetForegroundDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), color, 0, 0);
}

void draw_line(Vector2 target, const ImColor color)
{
	ImGui::GetForegroundDrawList()->AddLine(ImVec2(globals->width, globals->height), ImVec2(target.x, target.y), color, 0.1f);
}

void draw_distance(Vector2 location, float distance, const ImColor color)
{
	char dist[64];
	sprintf_s(dist, _("%.fm"), distance);
	ImVec2 text_size = ImGui::CalcTextSize(dist);
	ImGui::GetForegroundDrawList()->AddText(ImVec2(location.x - text_size.x / 2, location.y - text_size.y / 2), color, dist);
}
float GRD_TO_BOG(float GRD) {
	return (M_PI / 180) * GRD;
}
float BOG_TO_GRD(float BOG) {
	return (180 / M_PI) * BOG;
}
#define IM_ARRAYSIZE(_ARR)          ((int)(sizeof(_ARR)/sizeof(*_ARR)))

namespace hotkeys
{
	int aimkey = 2;
}

static int keystatus = 0;
static int keystatuss = 0;
static int keystatusssss = 0;
static int realkey = 0;
static int realkeyy = 0;
static int keystatusss = 0;
static int keystatussss = 0;
static int realkeyyy = 0;
static int realkeyyyy = 0;
static int backtrackkey = 0;

bool GetKey(int key)
{
	realkey = key;
	return true;
}

void ChangeKey(void* blank)
{
	keystatus = 1;
	while (true)
	{
		for (int i = 0; i < 0x87; i++)
		{
			if (GetKeyState(i) & 0x8000)
			{
				hotkeys::aimkey = i;
				keystatus = 0;
				return;
			}
		}
	}
}



static const char* keyNames[] =
{
	(""),
	("Left Mouse"),
	("Right Mouse"),
	("Cancel"),
	("Middle Mouse"),
	("Mouse 5"),
	("Mouse 4"),
	(""),
	("Backspace"),
	("Tab"),
	(""),
	(""),
	("Clear"),
	("Enter"),
	(""),
	(""),
	("Shift"),
	("Control"),
	("Alt"),
	("Pause"),
	("Caps"),
	(""),
	(""),
	(""),
	(""),
	(""),
	(""),
	("Escape"),
	(""),
	(""),
	(""),
	(""),
	("Space"),
	("Page Up"),
	("Page Down"),
	("End"),
	("Home"),
	("Left"),
	("Up"),
	("Right"),
	("Down"),
	(""),
	(""),
	(""),
	("Print"),
	("Insert"),
	("Delete"),
	(""),
	("0"),
	("1"),
	("2"),
	("3"),
	("4"),
	("5"),
	("6"),
	("7"),
	("8"),
	("9"),
	(""),
	(""),
	(""),
	(""),
	(""),
	(""),
	(""),
	("A"),
	("B"),
	("C"),
	("D"),
	("E"),
	("F"),
	("G"),
	("H"),
	("I"),
	("J"),
	("K"),
	("L"),
	("M"),
	("N"),
	("O"),
	("P"),
	("Q"),
	("R"),
	("S"),
	("T"),
	("U"),
	("V"),
	("W"),
	("X"),
	("Y"),
	("Z"),
	(""),
	(""),
	(""),
	(""),
	(""),
	("Numpad 0"),
	("Numpad 1"),
	("Numpad 2"),
	("Numpad 3"),
	("Numpad 4"),
	("Numpad 5"),
	("Numpad 6"),
	("Numpad 7"),
	("Numpad 8"),
	("Numpad 9"),
	("Multiply"),
	("Add"),
	(""),
	("Subtract"),
	("Decimal"),
	("Divide"),
	("F1"),
	("F2"),
	("F3"),
	("F4"),
	("F5"),
	("F6"),
	("F7"),
	("F8"),
	("F9"),
	("F10"),
	("F11"),
	("F12")
};
static bool Items_ArrayGetter(void* data, int idx, const char** out_text)
{
	const char* const* items = (const char* const*)data;
	if (out_text)
		*out_text = items[idx];
	return true;
}
void HotkeyButton(int aimkey, void* changekey, int status)
{
	const char* preview_value = NULL;
	if (aimkey >= 0 && aimkey < IM_ARRAYSIZE(keyNames))
		Items_ArrayGetter(keyNames, aimkey, &preview_value);

	std::string aimkeys;
	if (preview_value == NULL)
		aimkeys = _("Select Key");
	else
		aimkeys = preview_value;

	if (status == 1)
	{
		aimkeys = _("Press the key");
	}
	if (ImGui::Button(aimkeys.c_str(), ImVec2(125, 20)))
	{
		if (status == 0)
		{
			CreateThread(0, 0, (LPTHREAD_START_ROUTINE)changekey, nullptr, 0, nullptr);
		}
	}
}
BOOL WritePrivateProfileInt(LPCSTR lpAppName, LPCSTR lpKeyName, int nInteger, LPCSTR lpFileName) {
	char lpString[1024];
	sprintf_s(lpString, sizeof(lpString), TEXT("%d"), nInteger);
	return WritePrivateProfileStringA(lpAppName, lpKeyName, lpString, lpFileName);
}

BOOL WritePrivateProfileFloat(LPCSTR lpAppName, LPCSTR lpKeyName, float nInteger, LPCSTR lpFileName) {
	char lpString[1024];
	sprintf_s(lpString, sizeof(lpString), TEXT("%f"), nInteger);
	return WritePrivateProfileStringA(lpAppName, lpKeyName, lpString, lpFileName);
}
float GetPrivateProfileFloat(LPCSTR lpAppName, LPCSTR lpKeyName, FLOAT flDefault, LPCSTR lpFileName)
{
	char szData[32];

	GetPrivateProfileStringA(lpAppName, lpKeyName, std::to_string(flDefault).c_str(), szData, 32, lpFileName);

	return (float)atof(szData);
}

void savecfg(LPCSTR path)
{
	WritePrivateProfileInt(("a"), TEXT("Aimbot Enbale"), aimbot->enable, path);
	WritePrivateProfileInt(("a"), TEXT("Triggerbot Enbale"), aimbot->triggerbot, path);

	WritePrivateProfileInt(("a"), TEXT("Show fov"), aimbot->fov, path);
	WritePrivateProfileFloat(("a"), TEXT("fov size"), aimbot->fovsize, path);
	WritePrivateProfileFloat(("a"), TEXT("smooth size"), aimbot->smoothing, path);
	WritePrivateProfileInt(("a"), TEXT("Aimbot Key"), hotkeys::aimkey, path);
	WritePrivateProfileInt(("a"), TEXT("Aimbot Bone"), aimbot->bone, path);



	WritePrivateProfileInt(("b"), TEXT("Enable visuals"), visuals->enable, path);
	WritePrivateProfileInt(("b"), TEXT("Enable boxes"), visuals->box, path);
	WritePrivateProfileInt(("b"), TEXT("Box type"), visuals->box_type, path);
	WritePrivateProfileInt(("b"), TEXT("Skeleton"), visuals->skeleton, path);
	WritePrivateProfileInt(("b"), TEXT("Line"), visuals->lines, path);
	WritePrivateProfileInt(("b"), TEXT("Distance"), visuals->distance, path);
	WritePrivateProfileInt(("b"), TEXT("Weapon"), visuals->weapon, path);
	WritePrivateProfileInt(("b"), TEXT("Username"), visuals->username, path);
	WritePrivateProfileInt(("b"), TEXT("Platform"), visuals->platform, path);
	WritePrivateProfileFloat(("b"), TEXT("Box thick"), visuals->box_thickness, path);
	WritePrivateProfileFloat(("b"), TEXT("Skel thick"), visuals->skel_thickness, path);

	WritePrivateProfileFloat(("b"), TEXT("VisibleColorR"), colours->visible_color_float[0], path);
	WritePrivateProfileFloat(("b"), TEXT("VisibleColorG"), colours->visible_color_float[1], path);
	WritePrivateProfileFloat(("b"), TEXT("VisibleColorB"), colours->visible_color_float[2], path);

	WritePrivateProfileFloat(("b"), TEXT("InvisibleColorR"), colours->invisible_color_float[0], path);
	WritePrivateProfileFloat(("b"), TEXT("InvisibleColorG"), colours->invisible_color_float[1], path);
	WritePrivateProfileFloat(("b"), TEXT("InvisibleColorB"), colours->invisible_color_float[2], path);




	WritePrivateProfileInt(("c"), TEXT("Streamproof"), misc->streamproof, path);
	WritePrivateProfileInt(("c"), TEXT("Crosshair"), misc->crosshair, path);
	WritePrivateProfileInt(("c"), TEXT("Show Console"), misc->show_console, path);
	WritePrivateProfileInt(("c"), TEXT("Show FPS"), misc->show_fps, path);
}
void loadcfg(LPCSTR path)
{
	aimbot->enable = GetPrivateProfileIntA(("a"), TEXT("Aimbot Enbale"), aimbot->enable, path);
	aimbot->triggerbot = GetPrivateProfileIntA(("a"), TEXT("Triggerbot Enbale"), aimbot->triggerbot, path);
	aimbot->fov = GetPrivateProfileIntA(("a"), TEXT("Show fov"), aimbot->fov, path);
	aimbot->fovsize = GetPrivateProfileFloat(("a"), TEXT("fov size"), aimbot->fovsize, path);
	aimbot->smoothing = GetPrivateProfileFloat(("a"), TEXT("smooth size"), aimbot->smoothing, path);
	hotkeys::aimkey = GetPrivateProfileIntA(("a"), TEXT("Aimbot Key"), hotkeys::aimkey, path);
	aimbot->bone = GetPrivateProfileIntA(("a"), TEXT("Aimbot Bone"), aimbot->bone, path);



	visuals->enable = GetPrivateProfileIntA(("b"), TEXT("Enable visuals"), visuals->enable, path);
	visuals->box = GetPrivateProfileIntA(("b"), TEXT("Enable boxes"), visuals->box, path);
	visuals->box_type = GetPrivateProfileIntA(("b"), TEXT("Box type"), visuals->box_type, path);
	visuals->skeleton = GetPrivateProfileIntA(("b"), TEXT("Skeleton"), visuals->skeleton, path);
	visuals->skeleton = GetPrivateProfileIntA(("b"), TEXT("Line"), visuals->lines, path);
	visuals->distance = GetPrivateProfileIntA(("b"), TEXT("Distance"), visuals->distance, path);
	visuals->weapon = GetPrivateProfileIntA(("b"), TEXT("Weapon"), visuals->weapon, path);
	visuals->username = GetPrivateProfileIntA(("b"), TEXT("Username"), visuals->username, path);
	visuals->platform = GetPrivateProfileIntA(("b"), TEXT("Platform"), visuals->platform, path);
	visuals->box_thickness = GetPrivateProfileFloat(("b"), TEXT("Box thick"), visuals->box_thickness, path);
	visuals->skel_thickness = GetPrivateProfileFloat(("b"), TEXT("Skel thick"), visuals->skel_thickness, path);

	colours->visible_color_float[0] = GetPrivateProfileFloat(("b"), TEXT("VisibleColorR"), colours->visible_color_float[0], path);
	colours->visible_color_float[1] = GetPrivateProfileFloat(("b"), TEXT("VisibleColorG"), colours->visible_color_float[1], path);
	colours->visible_color_float[2] = GetPrivateProfileFloat(("b"), TEXT("VisibleColorB"), colours->visible_color_float[2], path);

	colours->invisible_color_float[0] = GetPrivateProfileFloat(("b"), TEXT("InvisibleColorR"), colours->invisible_color_float[0], path);
	colours->invisible_color_float[1] = GetPrivateProfileFloat(("b"), TEXT("InvisibleColorG"), colours->invisible_color_float[1], path);
	colours->invisible_color_float[2] = GetPrivateProfileFloat(("b"), TEXT("InvisibleColorB"), colours->invisible_color_float[2], path);


	misc->streamproof = GetPrivateProfileIntA(("c"), TEXT("Streamproof"), misc->streamproof, path);
	misc->crosshair = GetPrivateProfileIntA(("c"), TEXT("Crosshair"), misc->crosshair, path);
	misc->show_console = GetPrivateProfileIntA(("c"), TEXT("Show Console"), misc->show_console, path);
	misc->show_fps = GetPrivateProfileIntA(("c"), TEXT("Show FPS"), misc->show_fps, path);
}