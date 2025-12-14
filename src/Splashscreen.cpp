#include "splashscreen.hpp"

#include "godot_cpp/classes/image_texture.hpp"
#include "godot_cpp/core/class_db.hpp"
#include <godot_cpp/core/print_string.hpp>

#include "Windows/windows_Desktop_capture.h"

namespace NeverSilly {
}

void Splashscreen::_bind_methods() {
	godot::ClassDB::bind_method(godot::D_METHOD("Screenshot"), &Splashscreen::Screenshot);
}


godot::Ref<godot::ImageTexture> Splashscreen::Screenshot() {
	godot::print_line("LET4S GOOO");

    #ifdef _WIN32

        WindowsDesktopCapture windows;
        if(windows.init()) {

            auto img = windows.capture_desktop_image();
            if (img.is_valid()) {
                return godot::ImageTexture::create_from_image(img);
            }
            else {
                godot::print_line("Failed to Capture Desktop Image");
            }  

        } 
        else {
            godot::print_line("Failed to initialize Windows Desktop Capture");
        }
    #endif
    
    return nullptr;
}
