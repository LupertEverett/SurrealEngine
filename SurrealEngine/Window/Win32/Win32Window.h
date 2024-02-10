#pragma once

#include <list>
#include "Window/Window.h"
#include <zvulkan/vulkandevice.h>

// Modern OpenGL helpers... probably better having them in a separate header?

typedef HGLRC (*pfnWGLCREATECONTEXTATTRIBSARB)(HDC hDC, HGLRC hShareContext, const int* attribList);

#define WGL_CONTEXT_MAJOR_VERSION_ARB					0x2091
#define WGL_CONTEXT_MINOR_VERSION_ARB					0x2092
#define WGL_CONTEXT_LAYER_PLANE_ARB						0x2093
#define WGL_CONTEXT_FLAGS_ARB							0x2094
#define WGL_CONTEXT_PROFILE_MASK_ARB					0x9126

#define WGL_CONTEXT_DEBUG_BIT_ARB						0x0001
#define WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB			0x0002

#define WGL_CONTEXT_CORE_PROFILE_BIT_ARB			0x00000001
#define WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB	0x00000002

#define ERROR_INVALID_VERSION_ARB						0x2095
#define ERROR_INVALID_PROFILE_ARB						0x2096

class Win32Window : public GameWindow
{
public:
	Win32Window(GameWindowHost* windowHost);
	~Win32Window();

	void SetWindowTitle(const std::string& text) override;
	void SetWindowFrame(const Rect& box) override;
	void SetClientFrame(const Rect& box) override;
	void Show() override;
	void ShowFullscreen() override;
	void ShowMaximized() override;
	void ShowMinimized() override;
	void ShowNormal() override;
	void Hide() override;
	void Activate() override;
	void ShowCursor(bool enable) override;
	void LockCursor() override;
	void UnlockCursor() override;
	void Update() override;
	bool GetKeyState(EInputKey key) override;

	RenderDevice* GetRenderDevice() override { return Device.get(); }

	Rect GetWindowFrame() const override;
	Size GetClientSize() const override;
	int GetPixelWidth() const override;
	int GetPixelHeight() const override;
	double GetDpiScale() const override;
	std::vector<Size> QueryAvailableResolutions() const override;

	Point GetLParamPos(LPARAM lparam) const;

	static void ProcessEvents();
	static void RunLoop();
	static void ExitLoop();

	static bool ExitRunLoop;
	static std::list<Win32Window*> Windows;
	std::list<Win32Window*>::iterator WindowsIterator;

	void OpenGL_Init() override;
	void OpenGL_Deinit() override;
	OpenGLProcAddress OpenGL_GetProcAddress() override;

	void Vulkan_Init() override;
	void Vulkan_Deinit() override;

	LRESULT OnWindowMessage(UINT msg, WPARAM wparam, LPARAM lparam);
	static LRESULT CALLBACK WndProc(HWND windowhandle, UINT msg, WPARAM wparam, LPARAM lparam);

	GameWindowHost* WindowHost = nullptr;

	HWND WindowHandle = 0;

	bool MouseLocked = false;
	POINT MouseLockPos = {};

	std::unique_ptr<RenderDevice> Device;

	HGLRC glRenderContext = nullptr;
};
