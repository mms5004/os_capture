#pragma once

#ifdef _WIN32
#include <d3d11.h>
#include <dxgi1_2.h>
#include <godot_cpp/classes/image.hpp>

class WindowsDesktopCapture {
public:
    WindowsDesktopCapture();
    ~WindowsDesktopCapture();
    godot::Ref<godot::Image> capture_desktop_image();
};
#endif
