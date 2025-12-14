#pragma once

#ifdef _WIN32
#include <d3d11.h>
#include <dxgi1_2.h>
#include <godot_cpp/classes/image.hpp>

class WindowsDesktopCapture {
public:
    WindowsDesktopCapture();
    ~WindowsDesktopCapture();

    bool init();
    bool capture_frame(uint8_t*& out_data, int& width, int& height);

    godot::Ref<godot::Image> capture_desktop_image();

private:
    ID3D11Device* device = nullptr;
    ID3D11DeviceContext* context = nullptr;
    IDXGIOutputDuplication* duplication = nullptr;
};
#endif
