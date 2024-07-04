#pragma once
#ifndef DECRYPT
#define DECRYPT

#include "../../../../includes.hpp"
#include "hexray.hpp"

namespace cach
{
	class decrypt
	{
	public:

		uintptr_t
			pname,
			weapondata,
			displayname,
			weaponlength;

		wchar_t*
			weaponname;
	};
}

static cach::decrypt* decryptcached = new cach::decrypt();

namespace unrealenginedecryption
{
	class decrypt
	{
	public:

		__forceinline std::string platform(uint64_t PlayerState)
		{
			DWORD_PTR test_platform = driver.read<DWORD_PTR>(PlayerState + 0x438);
			wchar_t platform[64];
			driver.read_buffer((uint64_t)test_platform, (uint8_t*)platform, sizeof(platform));
			std::wstring platform_wstr(platform);
			std::string platform_str(platform_wstr.begin(), platform_wstr.end());
			return platform_str;
		}

		__forceinline std::string username(__int64 playerstate)
		{
			
			__int64 Name = driver.read<__int64>(playerstate + 0xAE8);
			if (!Name) return std::string("Bot/Ai");
			int Length = driver.read<int>(Name + 16i64);
			__int64 v6 = Length;
			if (!v6) return std::string("Bot/Ai");
			uintptr_t Data = driver.read<__int64>(Name + 8);
			if (!Data) return std::string("Bot/Ai");
			wchar_t* NameBuffer = new wchar_t[Length];
			driver.read_buffer(Data, (uint8_t*)(NameBuffer), (Length * 2));

			char v21; // al
			int v22; // r8d
			int i; // ecx
			int v25; // eax
			_WORD* v23;

			v21 = v6 - 1;
			if (!(_DWORD)v6)
				v21 = 0;
			v22 = 0;
			v23 = (_WORD*)NameBuffer;
			for (i = (v21) & 3; ; *v23++ += i & 7)
			{
				v25 = v6 - 1;
				if (!(_DWORD)v6)
					v25 = 0;
				if (v22 >= v25)
					break;
				i += 3;
				++v22;
			}

			std::wstring Temp{ NameBuffer };
			delete[] NameBuffer;
			return std::string(Temp.begin(), Temp.end());
			
			
		}
		//__forceinline std::string weapon(uintptr_t actor)
		//{
		//	/*std::string weapon_name = _("");
		//	uint64_t player_weapon = driver.read<uint64_t>(actor + 0x948);
		//	if (player_weapon) {
		//		uint64_t weapon_data = driver.read<uint64_t>(player_weapon + 0x498);
		//		if (weapon_data) {
		//			uint64_t ftext_ptr = driver.read<uint64_t>(weapon_data + 0x90);

		//			if (ftext_ptr) {
		//				uint64_t ftext_data = driver.read<uint64_t>(ftext_ptr + 0x28);
		//				int ftext_length = driver.read<int>(ftext_ptr + 0x30);
		//				if (ftext_length > 0 && ftext_length < 50) {
		//					wchar_t* ftext_buf = new wchar_t[ftext_length];
		//					ctx->read_array((uintptr_t)ftext_data, (uintptr_t)ftext_buf, ftext_length * sizeof(wchar_t));
		//					std::wstring wstr_buf(ftext_buf);
		//					weapon_name = std::string(wstr_buf.begin(), wstr_buf.end());
		//					delete[] ftext_buf;
		//				}
		//			}
		//		}
		//	}
		//	return weapon_name;*/
		//	
		//}
		__forceinline std::string weapon(uint64_t CurrentWeapon) {
			auto ItemData = driver.read<DWORD_PTR>(CurrentWeapon + 0x498);
			auto DisplayName = driver.read<uint64_t>(ItemData + 0x98);
			auto WeaponLength = driver.read<uint32_t>(DisplayName + 0x40);
			wchar_t* WeaponName = new wchar_t[uint64_t(WeaponLength) + 1];
			driver.read_buffer((ULONG64)driver.read<PVOID>(DisplayName + 0x38), (uint8_t*)WeaponName, WeaponLength * sizeof(wchar_t));

			BYTE tier;
			tier = driver.read<BYTE>(ItemData + 0x73);
			ImColor Color;

			if (tier == 2)
			{
				Color = IM_COL32(0, 255, 0, 255);
			}
			else if ((tier == 3))
			{
				Color = IM_COL32(0, 0, 255, 255);
			}
			else if ((tier == 4))
			{
				Color = IM_COL32(128, 0, 128, 255); // p
			}
			else if ((tier == 5))
			{
				Color = IM_COL32(255, 255, 0, 255); // p
			}
			else if ((tier == 6))
			{
				Color = IM_COL32(255, 255, 0, 255); // p
			}
			else if ((tier == 0) || (tier == 1))
			{
				Color = IM_COL32(255, 255, 255, 255); // p
			}
			if (!WeaponName || !tier)
			{
				delete[] WeaponName;
				WeaponName = new wchar_t[5];
				wcscpy(WeaponName, L"None");
			}
			
			std::string wep_str = wchar_to_char(WeaponName);
			return wep_str;
			
			


			/*std::string wep_str = wchar_to_char(WeaponName);
			ImVec2 TextSize = ImGui::CalcTextSize(wep_str.c_str());
			draw_outlined_text(ImVec2((bottom2d.x) - (TextSize.x / 2), (Headbox.y - 15)), Color, wep_str.c_str());*/
			
		}
		__forceinline auto reloading() -> bool
		{
			
		}

		__forceinline auto ammocount() -> int
		{
	
		}
	};
}
static unrealenginedecryption::decrypt* decrypt = new unrealenginedecryption::decrypt();
#endif 