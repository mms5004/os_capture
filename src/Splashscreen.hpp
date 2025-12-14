#pragma once
#include "godot_cpp/classes/node.hpp"
#include "godot_cpp/classes/wrapped.hpp"

class Splashscreen  : public godot::Node {
    GDCLASS(Splashscreen, Node)

protected:
    static void _bind_methods();
public:
    void Screenshot();
//private:
};




