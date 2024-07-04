#pragma once
#ifndef GLOBALS
#define GLOBALS

HWND window;
HWND hwnd;
namespace globalsdef
{
	class main
	{
	public:
		uintptr_t imagebase;
		DWORD pid;
		int width, height;
		bool show_menu = true;
		bool visibilitycheck = true;
		bool developermode = false;
	};

	class aimbot
	{
	public:
		bool enable = true;

		int key = 2;
		int bone = 0;
		bool fov = false;
		bool filledfov = true;
		int fovsize = 50;
		float smoothing = 5;
		bool triggerbot = false;
	};

	class visual
	{
	public:
		float box_thickness = 1;
		float skel_thickness = 1;
		int box_type = 0;
		bool enable = true;
		bool regular = true;
		bool filled = false;
		bool skeleton = false;
		bool box = false;
		bool lines = false;
		bool weapon = false;
		bool playerdetails = false;
		bool distance = false;
		bool platform = false;
		bool username = false;
		bool cornered = false;
		bool ThreeDBox = false;
	};

	class colours
	{
	public:
		/*float fov[4] = { 255, 0 , 0 , 255 };
		float regularbox[4] = { 255, 0 , 0 , 255 };
		float skeleton[4] = { 255, 0 , 0 , 255 };
		float visible[4] = { color.Red[0], color.Red[1], color.Red[2] };
		float invisible[4] = { color.Red[0], color.Red[1], color.Red[2] };*/


		float visible_color_float[4] = { 0.f, 1.f, 0.f, 1.f };
		float invisible_color_float[4] = { 0.f, 1.f, 0.f, 1.f };
	};

	class exploits
	{
	public:
		bool enable = false;
		bool fovslider = false;
		bool big_players = false;
		bool small_players = false;
		bool car_fly = false;
	};

	class misc
	{
	public:
		int tab = 0;
		bool crosshair = false;
		bool watermark = true;
		bool show_console = false;
		bool streamproof = false;
		bool controller = false;
		bool show_fps = false;
	};
};

static globalsdef::main* globals = new globalsdef::main();
static globalsdef::aimbot* aimbot = new globalsdef::aimbot();
static globalsdef::visual* visuals = new globalsdef::visual();
static globalsdef::colours* colours = new globalsdef::colours();
static globalsdef::exploits* exploits = new globalsdef::exploits();
static globalsdef::misc* misc = new globalsdef::misc();

#endif

