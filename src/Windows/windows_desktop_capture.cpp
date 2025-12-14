#include "windows_desktop_capture.h"

#include <godot_cpp/classes/image.hpp>
#include <godot_cpp/classes/image_texture.hpp>

WindowsDesktopCapture::WindowsDesktopCapture() {}
WindowsDesktopCapture::~WindowsDesktopCapture() {
    if (duplication) duplication->Release();
    if (context) context->Release();
    if (device) device->Release();
}

bool WindowsDesktopCapture::init() {
    HRESULT hr;

    hr = D3D11CreateDevice(
        nullptr,
        D3D_DRIVER_TYPE_HARDWARE,
        nullptr,
        0,
        nullptr,
        0,
        D3D11_SDK_VERSION,
        &device,
        nullptr,
        &context
    );

    godot::print_line("Create D3D11 Device");
    if (FAILED(hr)) return false;

    IDXGIDevice* dxgiDevice;
    device->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgiDevice);

    IDXGIAdapter* adapter;
    dxgiDevice->GetAdapter(&adapter);

    IDXGIOutput* output;
    adapter->EnumOutputs(0, &output);

    IDXGIOutput1* output1;
    output->QueryInterface(__uuidof(IDXGIOutput1), (void**)&output1);

    hr = output1->DuplicateOutput(device, &duplication);

    godot::print_line("try something on D3D11 Device");

    output1->Release();
    output->Release();
    adapter->Release();
    dxgiDevice->Release();

    return SUCCEEDED(hr);
}

bool WindowsDesktopCapture::capture_frame(uint8_t*& out_data, int& width, int& height) {
    if (!duplication) return false;

    DXGI_OUTDUPL_FRAME_INFO frameInfo;
    IDXGIResource* resource;

    HRESULT hr = duplication->AcquireNextFrame(16, &frameInfo, &resource);
    if (FAILED(hr)) return false;

    ID3D11Texture2D* texture;
    resource->QueryInterface(__uuidof(ID3D11Texture2D), (void**)&texture);

    D3D11_TEXTURE2D_DESC desc;
    texture->GetDesc(&desc);

    width = desc.Width;
    height = desc.Height;

    D3D11_TEXTURE2D_DESC stagingDesc = desc;
    stagingDesc.Usage = D3D11_USAGE_STAGING;
    stagingDesc.BindFlags = 0;
    stagingDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;

    ID3D11Texture2D* staging;
    device->CreateTexture2D(&stagingDesc, nullptr, &staging);

    context->CopyResource(staging, texture);

    D3D11_MAPPED_SUBRESOURCE map;
    context->Map(staging, 0, D3D11_MAP_READ, 0, &map);

    out_data = new uint8_t[width * height * 4];
    memcpy(out_data, map.pData, width * height * 4);

    context->Unmap(staging, 0);

    staging->Release();
    texture->Release();
    resource->Release();

    duplication->ReleaseFrame();

    return true;
}

godot::Ref<godot::Image> WindowsDesktopCapture::capture_desktop_image() {

    static bool initialized = init();
    if (!initialized) return nullptr;

    godot::print_line("init not nullptr");

    uint8_t* data;
    int w, h;

    if (!capture_frame(data, w, h)) return nullptr;

    godot::print_line("Capture frame success");

    godot::PackedByteArray arr;
    arr.resize(w * h * 4);
    memcpy(arr.ptrw(), data, arr.size());

    delete[] data;

    godot::Ref<godot::Image> img = godot::Image::create_from_data(
        w,
        h,
        false,
        godot::Image::FORMAT_RGBA8,
        arr
    );
    //godot::Ref<godot::ImageTexture> tex = godot::ImageTexture::create_from_image(img);

    return img;
}
