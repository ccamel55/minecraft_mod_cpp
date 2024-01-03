#pragma once

#include <memory>
#include <core_sdk/singleton.hpp>

#include <lib_gui/lib_gui.hpp>

class menu: public lib::singleton<menu>
{
public:
    void init();
    void destroy();

    [[nodiscard]] bool is_open() const;

    static void update_screen_size(const lib::point2Di& screen_size);

private:
    std::unique_ptr<lib::gui::gui> _gui_ptr = nullptr;
};