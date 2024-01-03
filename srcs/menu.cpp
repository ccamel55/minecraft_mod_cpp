#include <menu.hpp>
#include <instance.hpp>

#include <cassert>

#include <lib_gui/interface/ui_drag_bar.hpp>
#include <lib_gui/interface/ui_form.hpp>

void menu::init()
{
    assert(_gui_ptr == nullptr);

    _gui_ptr = std::make_unique<lib::gui::gui>();
    _gui_ptr->init(instance::get().input_handler, instance::get().renderer);

    // build gui
    const auto some_tab = std::make_shared<lib::gui::ui_drag_bar>("Test bar");
    {

    }
    _gui_ptr->register_window(some_tab);

    const auto some_tab_2 = std::make_shared<lib::gui::ui_drag_bar>("Test bar 2");
    {

    }
    _gui_ptr->register_window(some_tab_2);

    const auto some_form = std::make_shared<lib::gui::ui_form>("Test window", lib::point2Di(600, 400));
    {

    }
    _gui_ptr->register_window(some_form);

    const auto some_form_2 = std::make_shared<lib::gui::ui_form>("Test window 2", lib::point2Di(300, 600));
    {

    }
   _gui_ptr->register_window(some_form_2);
}

void menu::destroy()
{
    assert(_gui_ptr != nullptr);

    _gui_ptr->destroy();
    _gui_ptr.reset();
}

[[nodiscard]] bool menu::is_open() const
{
    if (!_gui_ptr) [[unlikely]]
    {
        return false;
    }

    return _gui_ptr->is_visible();
}

void menu::update_screen_size(const lib::point2Di& screen_size)
{
    lib::gui::context::screen_size = screen_size;
}
