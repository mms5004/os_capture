#include "Splashscreen.hpp"
#include "godot_cpp/core/class_db.hpp"
#include <godot_cpp/core/print_string.hpp>

namespace NeverSilly{
}

    
    void Splashscreen::Screenshot()
    {
        godot::print_line("LET4S GOOO");
    }
    
    void Splashscreen::_bind_methods()
    {
        godot::ClassDB::bind_method(godot::D_METHOD("Screenshot"), &Splashscreen::Screenshot);
    }
    