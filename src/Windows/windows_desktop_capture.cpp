#include "windows_desktop_capture.h"

#include <godot_cpp/classes/image.hpp>
#include <godot_cpp/classes/image_texture.hpp>
#include <windows.h>
#include <vector>

WindowsDesktopCapture::WindowsDesktopCapture() {}
WindowsDesktopCapture::~WindowsDesktopCapture() {}



godot::Ref<godot::Image> WindowsDesktopCapture::capture_desktop_image() {
    int width = GetSystemMetrics(SM_CXSCREEN);
    int height = GetSystemMetrics(SM_CYSCREEN);

    HDC hScreenDC = GetDC(NULL);
    HDC hMemoryDC = CreateCompatibleDC(hScreenDC);

    HBITMAP hBitmap = CreateCompatibleBitmap(hScreenDC, width, height);
    SelectObject(hMemoryDC, hBitmap);

    // Copier le bureau
    BitBlt(hMemoryDC, 0, 0, width, height, hScreenDC, 0, 0, SRCCOPY);

    // Préparer buffer RGBA
    BITMAPINFO bmi;
    ZeroMemory(&bmi, sizeof(bmi));
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = width;
    bmi.bmiHeader.biHeight = -height; // flip vertical
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 32;
    bmi.bmiHeader.biCompression = BI_RGB;

    std::vector<uint8_t> pixels(width * height * 4);
    GetDIBits(hMemoryDC, hBitmap, 0, height, pixels.data(), &bmi, DIB_RGB_COLORS);

    // Cleanup
    DeleteObject(hBitmap);
    DeleteDC(hMemoryDC);
    ReleaseDC(NULL, hScreenDC);

    // Convertir en godot::Image
    godot::PackedByteArray arr;
    arr.resize(width * height * 4);
    memcpy(arr.ptrw(), pixels.data(), arr.size());

    godot::Ref<godot::Image> img = godot::Image::create_from_data(
        width,
        height,
        false,
        godot::Image::FORMAT_RGBA8,
        arr
    );

    return img;
}
