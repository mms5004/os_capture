#pragma once
#include "godot_cpp/classes/image_texture.hpp"
#include "godot_cpp/classes/node.hpp"
#include "godot_cpp/classes/wrapped.hpp"


class Splashscreen : public godot::Node {
    GDCLASS(Splashscreen, Node)

protected:
    static void _bind_methods();
public:
    godot::Ref<godot::ImageTexture> Screenshot();
};
