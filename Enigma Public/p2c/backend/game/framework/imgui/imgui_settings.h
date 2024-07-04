#include "imgui.h"

namespace c {

	inline ImVec4 accent = ImColor(0, 255, 19, 255);

	namespace bg
	{

		inline ImVec4 background = ImColor(0, 0, 0, 200);
		inline ImVec2 size = ImVec2(850, 500);
		inline float rounding = 9.f;

	}

	namespace child
	{

		inline ImVec4 background = ImColor(17, 17, 19, 145);
		inline ImVec4 outline = ImColor(18, 20, 18, 255);
		inline float rounding = 8.f;

	}

	namespace checkbox
	{
		inline ImVec4 background = ImColor(34, 34, 37, 255);
		inline ImVec4 circle_inactive = ImColor(46, 48, 55, 255);
		inline float rounding = 2.f;
	}

	namespace slider
	{
		inline ImVec4 background = ImColor(34, 34, 37, 255);
		inline ImVec4 circle_inactive = ImColor(46, 48, 55, 255);
		inline float rounding = 2.f;
	}

	namespace tabs
	{
		inline ImVec4 background = ImColor(16, 17, 19, 255);

		inline ImVec4 outline = ImColor(22, 24, 26, 255);
		inline float rounding = 6.f;
	}

	namespace combo
	{
		inline ImVec4 background = ImColor(16, 17, 19, 255);
		inline ImVec4 outline = ImColor(22, 24, 26, 255);
		inline ImVec4 icon = ImColor(26, 27, 31, 255);

		inline float rounding = 2.f;
	}

	namespace picker
	{
		inline ImVec4 background = ImColor(16, 17, 19, 255);
		inline ImVec4 outline = ImColor(22, 24, 26, 255);

		inline float rounding = 2.f;
	}

	namespace button
	{
		inline ImVec4 background_active = ImColor(26, 27, 29, 255);
		inline ImVec4 background_inactive = ImColor(16, 17, 19, 255);

		inline ImVec4 outline = ImColor(22, 24, 26, 255);

		inline float rounding = 2.f;
	}

	namespace keybind
	{
		inline ImVec4 background_active = ImColor(26, 27, 29, 255);
		inline ImVec4 background_inactive = ImColor(16, 17, 19, 255);

		inline ImVec4 outline = ImColor(22, 24, 26, 255);

		inline float rounding = 2.f;
	}

	namespace input
	{
		inline ImVec4 background_active = ImColor(26, 27, 29, 255);
		inline ImVec4 background_inactive = ImColor(16, 17, 19, 255);

		inline ImVec4 outline = ImColor(22, 24, 26, 255);
		inline ImVec4 icon = ImColor(26, 27, 31, 255);

		inline float rounding = 2.f;
	}

	namespace scroll
	{
		inline float rounding = 30.f;
	}

	namespace text
	{
		inline ImVec4 text_active = ImColor(255, 255, 255, 255);
		inline ImVec4 text_hov = ImColor(86, 88, 95, 255);
		inline ImVec4 text = ImColor(46, 48, 55, 255);

		inline float glow_size = 8.f;
	}
}