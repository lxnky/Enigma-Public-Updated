#pragma once
#ifndef OVERLAY
#define OVERLAY

//#include "../../../../includes.hpp"
//#include "../../framework/imgui/imgui_impl_win32.cpp"
#include "../entity.hpp"

#include <dxgi.h>
#include <d3d11.h>
#include "../../../framework/d3d/D3DX11tex.h"
#include "hijack.h"
#include "../../../framework/imgui/imgui_internal.h"
#include "../../../framework/fonts/image.h"
#include "../../../framework/fonts/font.h"
#pragma comment(lib, "D3DX11.lib")
ID3D11Device* g_pd3dDevice;
ID3D11DeviceContext* g_pd3dDeviceContext;
IDXGISwapChain* g_pSwapChain;
ID3D11RenderTargetView* g_mainRenderTargetView;
const char* font1;

float rounding = 9.f;
ImFont* m_pFont;
bool clickable = false;
DWORD picker_flags;

namespace c {

	ImVec4 accent = ImColor(0, 255, 19, 255);

	namespace bg
	{

		ImVec4 background = ImColor(0, 0, 0, 230);
		inline ImVec2 size = ImVec2(850, 500);
		inline float rounding = 9.f;

	}

	namespace child
	{

		ImVec4 background = ImColor(17, 17, 19, 200);
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







void change_click(bool canclick)
{
	SPOOF;
	long style = ::GetWindowLong(window, GWL_EXSTYLE);
	if (canclick)
	{
		style &= ~WS_EX_LAYERED;
		SetWindowLong(window, GWL_EXSTYLE, style);
		SetFocus(window);
		clickable = true;
	}
	else
	{
		style |= WS_EX_LAYERED;
		SetWindowLong(window, GWL_EXSTYLE, style);
		SetFocus(window);
		clickable = false;
	}
}
namespace pic
{
	ID3D11ShaderResourceView* background = nullptr;

	ID3D11ShaderResourceView* aimbot = nullptr;
	ID3D11ShaderResourceView* visuals = nullptr;
	ID3D11ShaderResourceView* skins = nullptr;
	ID3D11ShaderResourceView* settings = nullptr;

	ID3D11ShaderResourceView* combo_widget = nullptr;
	ID3D11ShaderResourceView* input_widget = nullptr;

	ID3D11ShaderResourceView* menu_settings_icon = nullptr;

	ID3D11ShaderResourceView* circle_success = nullptr;
	ID3D11ShaderResourceView* circle_error = nullptr;

}

namespace font
{
	ImFont* inter_bold = nullptr;
	ImFont* inter_default = nullptr;
	ImFont* icon = nullptr;
}
namespace DirectX
{
	class DirectX11
	{
	public:

		__forceinline auto hijack() -> bool
		{
			SPOOF;
			while (!window) {
				window = SetUp::HiJackNotepadWindow();
				Sleep(10);
			}

			MARGINS margin = { -1 };
			DwmExtendFrameIntoClientArea(window, &margin);
			SetMenu(window, NULL);
			SetWindowLongPtr(window, GWL_STYLE, WS_VISIBLE);
			SetWindowLongPtr(window, GWL_EXSTYLE, WS_EX_LAYERED | WS_EX_TRANSPARENT);

			ShowWindow(window, SW_SHOW);
			UpdateWindow(window);

			SetWindowLong(window, GWL_EXSTYLE, GetWindowLong(window, GWL_EXSTYLE) | WS_EX_LAYERED | WS_EX_TRANSPARENT);

			return true;

		}

		LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
		{
			SPOOF;
			if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
				return true;

			switch (msg)
			{
			case WM_SIZE:
				if (g_pd3dDevice != NULL && wParam != SIZE_MINIMIZED)
				{
					cleanrender();
					g_pSwapChain->ResizeBuffers(0, (UINT)LOWORD(lParam), (UINT)HIWORD(lParam), DXGI_FORMAT_UNKNOWN, 0);
					createrender();
				}
				return 0;
			case WM_SYSCOMMAND:
				if ((wParam & 0xfff0) == SC_KEYMENU)
					return 0;
				break;
			case WM_DESTROY:
				::PostQuitMessage(0);
				return 0;
			}
			return ::DefWindowProc(hWnd, msg, wParam, lParam);
		}

		__forceinline void createrender()
		{
			SPOOF;
			ID3D11Texture2D* pBackBuffer;
			g_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
			g_pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &g_mainRenderTargetView);
			pBackBuffer->Release();
		}

		__forceinline void cleanrender()
		{
			SPOOF;
			if (g_mainRenderTargetView)
			{
				g_mainRenderTargetView->Release();
				g_mainRenderTargetView = NULL;
			}
		}

		void cleand3d()
		{
			SPOOF;
			cleanrender();
			if (g_pSwapChain)
			{
				g_pSwapChain->Release(); g_pSwapChain = NULL;
			}
			if (g_pd3dDeviceContext)
			{
				g_pd3dDeviceContext->Release();
				g_pd3dDeviceContext = NULL;
			}
			if (g_pd3dDevice)
			{
				g_pd3dDevice->Release();
				g_pd3dDevice = NULL;
			}
		}

		__forceinline auto initiate() -> bool
		{
			SPOOF;

			DXGI_SWAP_CHAIN_DESC SwapChainDesc;
			ZeroMemory(&SwapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));
			SwapChainDesc.Windowed = TRUE;
			SwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
			SwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			SwapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
			SwapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
			SwapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
			SwapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
			SwapChainDesc.BufferDesc.Height = 0;
			SwapChainDesc.BufferDesc.Width = 0;
			SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
			SwapChainDesc.BufferCount = 1;
			SwapChainDesc.OutputWindow = window;
			SwapChainDesc.SampleDesc.Count = 8;
			SwapChainDesc.SampleDesc.Quality = 0;

			UINT createDeviceFlags = 0;
			D3D_FEATURE_LEVEL featureLevel;
			const D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };
			if (D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &SwapChainDesc, &g_pSwapChain, &g_pd3dDevice, &featureLevel, &g_pd3dDeviceContext) != S_OK)
			{
				return false;
			}

			IMGUI_CHECKVERSION();
			ImGui::CreateContext();
			ImGuiIO& io = ImGui::GetIO(); (void)io;

			ImGui::SetNextWindowSize(io.DisplaySize);
			io.IniFilename = NULL;
			font1 = _("C:\\fortnite.otf");
			m_pFont = io.Fonts->AddFontFromFileTTF(font1, 16.0f, nullptr, io.Fonts->GetGlyphRangesDefault());
			/*ImFontConfig cfg;
			font::inter_default = io.Fonts->AddFontFromMemoryTTF(inter_medium, sizeof(inter_medium), 17.f, &cfg, io.Fonts->GetGlyphRangesCyrillic());
			font::inter_bold = io.Fonts->AddFontFromMemoryTTF(inter_bold, sizeof(inter_bold), 17.f, &cfg, io.Fonts->GetGlyphRangesCyrillic());
			font::icon = io.Fonts->AddFontFromMemoryTTF(icon_font, sizeof(icon_font), 15.f, &cfg, io.Fonts->GetGlyphRangesCyrillic());*/
			ID3D11Texture2D* pBackBuffer;

			g_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));

			g_pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &g_mainRenderTargetView);

			ImGui_ImplWin32_Init(window);

			ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext);

			pBackBuffer->Release();

			SetWindowPos(window, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);

		}

		__forceinline auto init() -> void
		{
			SPOOF;
			LPDIRECT3D9              g_pD3D = NULL;
			LPDIRECT3DDEVICE9       g_pd3dDevice = NULL;
			D3DPRESENT_PARAMETERS    g_d3dpp = {};
			auto& io = ImGui::GetIO();
			auto& style = ImGui::GetStyle();

			io.MouseDrawCursor = false;

			ImGui_ImplDX11_NewFrame();
			ImGui_ImplWin32_NewFrame();

			ImGui::NewFrame(); {


				if (GetAsyncKeyState(VK_INSERT) & 1)
					globals->show_menu = !globals->show_menu;


				if (globals->show_menu)
				{
					if (clickable != true)
						change_click(true);

					menu();

				}
				else
				{
					if (clickable != false)
						change_click(false);
				}
			}
			entity->loop();
			ImGui::Render();
			ImGui::EndFrame();
			ImVec4 clear_color = ImVec4(0., 0., 0., 0.);
			g_pd3dDeviceContext->OMSetRenderTargets(1, &g_mainRenderTargetView, NULL);
			g_pd3dDeviceContext->ClearRenderTargetView(g_mainRenderTargetView, (float*)&clear_color);
			g_d3dpp.FullScreen_RefreshRateInHz = true;

			ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
			g_pSwapChain->Present(0, 0);
		}

		__forceinline auto draw() -> bool
		{
			SPOOF;
			static RECT old_rc;
			MSG Message = { NULL };
			ZeroMemory(&Message, sizeof(MSG));
			while (Message.message != WM_QUIT)
			{
				if (PeekMessage(&Message, window, 0, 0, PM_REMOVE))
				{
					TranslateMessage(&Message);
					DispatchMessage(&Message);
				}
				ImGuiIO& io = ImGui::GetIO(); (void)io;
				POINT p;
				POINT xy;
				GetCursorPos(&p);
				io.MousePos.x = p.x;
				io.MousePos.y = p.y;
				if (GetAsyncKeyState(VK_LBUTTON)) {
					io.MouseDown[0] = true;
					io.MouseClicked[0] = true;
					io.MouseClickedPos[0].x = io.MousePos.x;
					io.MouseClickedPos[0].x = io.MousePos.y;
				}
				else
					io.MouseDown[0] = false;

				init();
			}

			ImGui_ImplDX11_Shutdown();
			ImGui_ImplWin32_Shutdown();
			ImGui::DestroyContext();
			cleand3d();
			DestroyWindow(window);
			return Message.wParam;
		}
		__forceinline auto setup_colors() -> void
		{
			SPOOF;
			D3DX11_IMAGE_LOAD_INFO info; ID3DX11ThreadPump* pump{ nullptr };
			picker_flags= ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaPreview;
			if (pic::background == nullptr) D3DX11CreateShaderResourceViewFromMemory(g_pd3dDevice, bg_bytes, sizeof(bg_bytes), &info, pump, &pic::background, 0);

			if (pic::aimbot == nullptr) D3DX11CreateShaderResourceViewFromMemory(g_pd3dDevice, aimbot_bytes, sizeof(aimbot_bytes), &info, pump, &pic::aimbot, 0);
			if (pic::visuals == nullptr) D3DX11CreateShaderResourceViewFromMemory(g_pd3dDevice, visuals_bytes, sizeof(visuals_bytes), &info, pump, &pic::visuals, 0);
			//if (pic::skins == nullptr) D3DX11CreateShaderResourceViewFromMemory(g_pd3dDevice, skins, sizeof(skins), &info, pump, &pic::skins, 0);
			if (pic::settings == nullptr) D3DX11CreateShaderResourceViewFromMemory(g_pd3dDevice, settings_bytes, sizeof(settings_bytes), &info, pump, &pic::settings, 0);

			if (pic::combo_widget == nullptr) D3DX11CreateShaderResourceViewFromMemory(g_pd3dDevice, combo_widget_bytes, sizeof(combo_widget_bytes), &info, pump, &pic::combo_widget, 0);
			if (pic::input_widget == nullptr) D3DX11CreateShaderResourceViewFromMemory(g_pd3dDevice, input_widget_bytes, sizeof(input_widget_bytes), &info, pump, &pic::input_widget, 0);

			if (pic::menu_settings_icon == nullptr) D3DX11CreateShaderResourceViewFromMemory(g_pd3dDevice, menu_settings_icon_bytes, sizeof(menu_settings_icon_bytes), &info, pump, &pic::menu_settings_icon, 0);

			if (pic::circle_success == nullptr) D3DX11CreateShaderResourceViewFromMemory(g_pd3dDevice, circle_success, sizeof(circle_success), &info, pump, &pic::circle_success, 0);
			if (pic::circle_error == nullptr) D3DX11CreateShaderResourceViewFromMemory(g_pd3dDevice, circle_error, sizeof(circle_error), &info, pump, &pic::circle_error, 0);
		}
		
		__forceinline auto menu() -> void
		{
			SPOOF;
			setup_colors();
			
			if (globals->show_menu)
			{
				ImGuiStyle* style = &ImGui::GetStyle();

				style->WindowPadding = ImVec2(0, 0);
				style->WindowBorderSize = 0;
				style->ItemSpacing = ImVec2(20, 20);
				style->ScrollbarSize = 8.f;
				ImGui::SetNextWindowSize({ 850,500 });
				ImGui::Begin("", nullptr, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoBringToFrontOnFocus);
				const ImVec2& pos = ImGui::GetWindowPos();
				const ImVec2& spacing = style->ItemSpacing;
				const ImVec2& region = ImGui::GetContentRegionMax();

				
				
				
				ImGui::GetBackgroundDrawList()->AddRectFilled(pos, pos + region, ImGui::GetColorU32(c::bg::background), c::bg::rounding);


				ImGui::GetBackgroundDrawList()->AddRectFilled(pos + ImVec2(0, spacing.y - 15) + spacing, pos + ImVec2(180, region.y - spacing.y), ImGui::GetColorU32(c::child::background), c::child::rounding);

				

				ImGui::SetCursorPos(ImVec2(spacing.x * 2, spacing.y * 2 + 60));
				ImGui::BeginGroup();
				{
					if (ImGui::Tabs(0 == misc->tab, pic::aimbot, _("Aimbot"), ImVec2(180 - spacing.x * 3, 35), NULL)) misc->tab = 0;

					if (ImGui::Tabs(1 == misc->tab, pic::visuals, _("Visuals"), ImVec2(180 - spacing.x * 3, 35), NULL)) misc->tab = 1;

					if (ImGui::Tabs(2 == misc->tab, pic::settings, _("Settings"), ImVec2(180 - spacing.x * 3, 35), NULL)) misc->tab = 2;
				}
				ImGui::EndGroup();
				ImGui::SetCursorPos(ImVec2(180, spacing.y - 15) + spacing);

				switch (misc->tab) {
					case 0:
					{
						ImGui::BeginGroup();
						{
							ImGui::CustomBeginChild(_("AIMBOT"), ImVec2((region.x - (spacing.x * 3 + 200)) / 2, (region.y - (spacing.y * 2 - 370)) / 2.0f + 40));
							{

								static float color[4] = { 0.f, 1.f, 0.f, 1.f };
								ImGui::Checkbox(_("Enable Aimbot"), &aimbot->enable);
								ImGui::Checkbox(_("Enable Triggerbot"), &aimbot->triggerbot);
								ImGui::Checkbox(_("Show Fov"), &aimbot->fov);
							}
							ImGui::CustomEndChild();
						}
						ImGui::EndGroup();

						ImGui::SameLine();

						ImGui::BeginGroup();
						{
							ImGui::CustomBeginChild(_("SETTINGS"), ImVec2((region.x - (spacing.x * 3 + 160)) / 2, (region.y - (spacing.y * 2 - 370)) / 2.0f + 40));
							{

								ImGui::Checkbox(_("Show Fov"), &aimbot->fov);
								ImGui::PushItemWidth(350);
								ImGui::SliderInt(_("Fov Size:  "), &aimbot->fovsize, 50, 300);
								ImGui::PopItemWidth();
								ImGui::SliderFloat(_("Smoothness Size: "), &aimbot->smoothing, 1, 100);
								ImGui::Text(_("Aim Key:"));
								ImGui::SameLine();
								HotkeyButton(hotkeys::aimkey, ChangeKey, keystatus);
								static const char* bonename[] =
								{
									_("Head"),
									_("Neck"),
									_("Chest")
								};
								ImGui::Combo(_("Target Bone"), &aimbot->bone, bonename, IM_ARRAYSIZE(bonename));
							}
							ImGui::CustomEndChild();
						}
						ImGui::EndGroup();
						break;
					}
					case 1 :
					{
						
						ImGui::BeginGroup();
						{
							ImGui::CustomBeginChild(_("VISUALS"), ImVec2((region.x - (spacing.x * 3 + 200)) / 2, (region.y - (spacing.y * 2 - 370)) / 2.0f + 40));
							{
								ImGui::Checkbox(_("Enable Visuals"), &visuals->enable);
								static const char* box_type_name[] =
								{
									_("Full"),
									_("Cornered"),
									_("Three-Dimensional")
								};
								ImGui::Checkbox(_("Enable Boxes"), &visuals->box);
								if (visuals->box)
								{
									ImGui::Combo(_("Box Type"), &visuals->box_type, box_type_name, IM_ARRAYSIZE(box_type_name));
								}

								ImGui::Checkbox(_("Skeleton"), &visuals->skeleton);
								ImGui::Checkbox(_("Line"), &visuals->lines);
								ImGui::Checkbox(_("Distance"), &visuals->distance);
								ImGui::Checkbox(_("Draw Weapon"), &visuals->weapon);
								ImGui::Checkbox(_("Draw Username"), &visuals->username);
								ImGui::Checkbox(_("Draw Platform"), &visuals->platform);
							}
							ImGui::CustomEndChild();
						}
						ImGui::EndGroup();

						ImGui::SameLine();

						ImGui::BeginGroup();
						{
							ImGui::CustomBeginChild(_("CUSTOMISATION"), ImVec2((region.x - (spacing.x * 3 + 160)) / 2, (region.y - (spacing.y * 2 - 370)) / 2.0f + 40));
							{

								ImGui::SliderFloat(_("Box Thickness: "), &visuals->box_thickness, 1, 5);
								ImGui::SliderFloat(_("Skeleton Thickness: "), &visuals->skel_thickness, 1, 5);
								ImGui::ColorEdit4(_("Visible Color"), colours->visible_color_float, picker_flags);
								ImGui::ColorEdit4(_("Invisible Color"), colours->invisible_color_float, picker_flags);
							}
							ImGui::CustomEndChild();
						}
						ImGui::EndGroup();
						break;
					}
					case 2:
					{

						ImGui::BeginGroup(); 
						{
							ImGui::CustomBeginChild(_("SETTINGS"), ImVec2((region.x - (spacing.x * 3 + 200)) / 2, (region.y - (spacing.y * 2 - 370)) / 2.0f + 40));
							{
								ImGui::Checkbox(_("Contoller Support"), &misc->controller);
								ImGui::Checkbox(_("Streamproof"), &misc->streamproof);
								ImGui::Checkbox(_("Crosshair"), &misc->crosshair);
								ImGui::Checkbox(_("Show Console"), &misc->show_console);
								ImGui::Checkbox(_("Show FPS"), &misc->show_fps);
								if (ImGui::Button(_("Unload"), { 120, 20 })) {
									system(_("taskkill /F /IM mmc.exe"));
									exit(0);
								}
							}
							ImGui::CustomEndChild();
						}
						ImGui::EndGroup();

						ImGui::SameLine();

						ImGui::BeginGroup(); 
						{
							ImGui::CustomBeginChild("CONFIG", ImVec2((region.x - (spacing.x * 3 + 160)) / 2, (region.y - (spacing.y * 2 - 370)) / 2.0f + 40));
							{
								if (ImGui::Button(("Save Config"), ImVec2(80,80)))
								{
									savecfg(TEXT(_("C:\\cfgfn")));
								}
								if (ImGui::Button(("Load Config"), ImVec2(80, 80)))
								{
									loadcfg(TEXT(_("C:\\cfgfn")));
								}
							}
							ImGui::CustomEndChild();
						}
						ImGui::EndGroup();
						break;
					}
				}
				
				/*switch (misc->tab)
				{
				case 0:
				{
					ImGui::Checkbox(_("Enable Aimbot"), &aimbot->enable);
					ImGui::Checkbox(_("Enable Triggerbot"), &aimbot->triggerbot);
					ImGui::Checkbox(_("Show Fov"), &aimbot->fov);
					ImGui::PushItemWidth(350);
					ImGui::SliderInt(_("Fov Size:  "), &aimbot->fovsize, 50, 300);
					ImGui::PopItemWidth();
					ImGui::SliderFloat(_("Smoothness Size: "), &aimbot->smoothing, 1, 100);
					ImGui::Text(_("Aim Key:"));
					ImGui::SameLine();
					HotkeyButton(hotkeys::aimkey, ChangeKey, keystatus);
					static const char* bonename[] =
					{
						_("Head"),
						_("Neck"),
						_("Chest")
					};
					ImGui::Combo(_("Target Bone"), &aimbot->bone, bonename, IM_ARRAYSIZE(bonename));
					break;
				}
				case 1:
				{

					ImGui::Checkbox(_("Enable Visuals"), &visuals->enable);
					static const char* box_type_name[] =
					{
						_("Full"),
						_("Cornered"),
						_("Three-Dimensional")
					};
					ImGui::Checkbox(_("Enable Boxes"), &visuals->box);
					if (visuals->box)
					{
						ImGui::Combo(_("Box Type"), &visuals->box_type, box_type_name, IM_ARRAYSIZE(box_type_name));
					}

					ImGui::Checkbox(_("Skeleton"), &visuals->skeleton);
					ImGui::Checkbox(_("Line"), &visuals->lines);
					ImGui::Checkbox(_("Distance"), &visuals->distance);
					ImGui::Checkbox(_("Draw Weapon"), &visuals->weapon);
					ImGui::Checkbox(_("Draw Username"), &visuals->username);
					break;
				}
				case 2:
				{
					ImGui::SliderInt(_("Box Thickness: "), &visuals->box_thickness, 1, 5);
					ImGui::SliderInt(_("Skeleton Thickness: "), &visuals->skel_thickness, 1, 5);
					ImGui::Checkbox(_("Streamproof"), &misc->streamproof);
					ImGui::Checkbox(_("Crosshair"), &misc->crosshair);
					ImGui::Checkbox(_("Show Console"), &misc->show_console);
					ImGui::Checkbox(_("Show FPS"), &misc->show_fps);
					if (ImGui::Button(_("Unload"), { 120, 20 })) {
						system(_("taskkill /F /IM mmc.exe"));
						exit(0);
					}
					break;
				}*/
				/*ImGui::SetNextWindowSize({ 620, 350 });
				ImGui::Begin(_(""), 0, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar);
				if (ImGui::Button(_("Aimbot"), { 196, 20 })) misc->tab = 0;
				ImGui::SameLine();
				if (ImGui::Button(_("Visuals"), { 196, 20 })) misc->tab = 1;
				ImGui::SameLine();
				if (ImGui::Button(_("Misc"), { 196, 20 })) misc->tab = 2;
				
				switch (misc->tab)
				{
				case 0:
				{
					ImGui::Checkbox(_("Enable Aimbot"), &aimbot->enable);
					ImGui::Checkbox(_("Enable Triggerbot"), &aimbot->triggerbot);
					ImGui::Checkbox(_("Show Fov"), &aimbot->fov);
					ImGui::PushItemWidth(350);
					ImGui::SliderInt(_("Fov Size:  "), &aimbot->fovsize, 50, 300);
					ImGui::PopItemWidth();
					ImGui::SliderFloat(_("Smoothness Size: "), &aimbot->smoothing, 1, 100);
					ImGui::Text(_("Aim Key:"));
					ImGui::SameLine();
					HotkeyButton(hotkeys::aimkey, ChangeKey, keystatus);
					static const char* bonename[] =
					{
						_("Head"),
						_("Neck"),
						_("Chest")
					};
					ImGui::Combo(_("Target Bone"), &aimbot->bone, bonename, IM_ARRAYSIZE(bonename));
					break;
				}
				case 1:
				{
					
					ImGui::Checkbox(_("Enable Visuals"), &visuals->enable);
					static const char* box_type_name[] =
					{
						_("Full"),
						_("Cornered"),
						_("Three-Dimensional")
					};
					ImGui::Checkbox(_("Enable Boxes"), &visuals->box);
					if (visuals->box)
					{
						ImGui::Combo(_("Box Type"), &visuals->box_type, box_type_name, IM_ARRAYSIZE(box_type_name));
					}
					
					ImGui::Checkbox(_("Skeleton"), &visuals->skeleton);
					ImGui::Checkbox(_("Line"), &visuals->lines);
					ImGui::Checkbox(_("Distance"), &visuals->distance);
					ImGui::Checkbox(_("Draw Weapon"), &visuals->weapon);
					ImGui::Checkbox(_("Draw Username"), &visuals->username);
					break;
				}
				case 2:
				{
					ImGui::SliderInt(_("Box Thickness: "), &visuals->box_thickness, 1, 5);
					ImGui::SliderInt(_("Skeleton Thickness: "), &visuals->skel_thickness, 1, 5);
					ImGui::Checkbox(_("Streamproof"), &misc->streamproof);
					ImGui::Checkbox(_("Crosshair"), &misc->crosshair);
					ImGui::Checkbox(_("Show Console"), &misc->show_console);
					ImGui::Checkbox(_("Show FPS"), &misc->show_fps);
					if (ImGui::Button(_("Unload"), { 120, 20 })) {
						system(_("taskkill /F /IM mmc.exe"));
						exit(0);
					} 
					break;
				}
				}
				ImGui::End();*/
			}
			ImGui::PopStyleVar();
		}
	};
}
static DirectX::DirectX11* render = new DirectX::DirectX11();

#endif