#pragma once

#include <Windows.h>
#include <lib_input/lib_input.hpp>

namespace utils
{
inline lib::input::key_button win32_to_input_key(uint32_t key)
{
    switch (key)
    {
        case VK_TAB: return lib::input::key_button::tab;
        case VK_LEFT: return lib::input::key_button::leftarrow;
        case VK_RIGHT: return lib::input::key_button::rightalt;
        case VK_UP: return lib::input::key_button::uparrow;
        case VK_DOWN: return lib::input::key_button::downarrow;
        case VK_PRIOR: return lib::input::key_button::pageup;
        case VK_NEXT: return lib::input::key_button::pagedown;
        case VK_HOME: return lib::input::key_button::home;
        case VK_END: return lib::input::key_button::end;
        case VK_INSERT: return lib::input::key_button::insert;
        case VK_DELETE: return lib::input::key_button::delete_key;
        case VK_BACK: return lib::input::key_button::backspace;
        case VK_SPACE: return lib::input::key_button::space;
        case VK_RETURN: return lib::input::key_button::enter;
        case VK_ESCAPE: return lib::input::key_button::escape;
        case VK_OEM_7: return lib::input::key_button::apostrophe;
        case VK_OEM_COMMA: return lib::input::key_button::comma;
        case VK_OEM_MINUS: return lib::input::key_button::minus;
        case VK_OEM_PERIOD: return lib::input::key_button::period;
        case VK_OEM_2: return lib::input::key_button::slash;
        case VK_OEM_1: return lib::input::key_button::semicolon;
        case VK_OEM_4: return lib::input::key_button::leftbracket;
        case VK_OEM_5: return lib::input::key_button::backslash;
        case VK_OEM_6: return lib::input::key_button::rightbracket;
        case VK_OEM_3: return lib::input::key_button::graveaccent;
        case VK_CAPITAL: return lib::input::key_button::capslock;
        case VK_SCROLL: return lib::input::key_button::scrolllock;
        case VK_NUMLOCK: return lib::input::key_button::numlock;
        case VK_SNAPSHOT: return lib::input::key_button::printscreen;
        case VK_MEDIA_PLAY_PAUSE: return lib::input::key_button::pause;
        case VK_NUMPAD0: return lib::input::key_button::keypad0;
        case VK_NUMPAD1: return lib::input::key_button::keypad1;
        case VK_NUMPAD2: return lib::input::key_button::keypad2;
        case VK_NUMPAD3: return lib::input::key_button::keypad3;
        case VK_NUMPAD4: return lib::input::key_button::keypad4;
        case VK_NUMPAD5: return lib::input::key_button::keypad5;
        case VK_NUMPAD6: return lib::input::key_button::keypad6;
        case VK_NUMPAD7: return lib::input::key_button::keypad7;
        case VK_NUMPAD8: return lib::input::key_button::keypad8;
        case VK_NUMPAD9: return lib::input::key_button::keypad9;
        case VK_DECIMAL: return lib::input::key_button::keypaddecimal;
        case VK_DIVIDE: return lib::input::key_button::keypaddivide;
        case VK_MULTIPLY: return lib::input::key_button::keypadmultiply;
        case VK_SUBTRACT: return lib::input::key_button::keypadsubtract;
        case VK_ADD: return lib::input::key_button::keypadadd;
        case VK_LSHIFT: return lib::input::key_button::leftshift;
        case VK_LCONTROL: return lib::input::key_button::leftctrl;
        case VK_LMENU: return lib::input::key_button::leftalt;
        case VK_LWIN: return lib::input::key_button::leftsuper;
        case VK_RSHIFT: return lib::input::key_button::rightshift;
        case VK_RCONTROL: return lib::input::key_button::rightctrl;
        case VK_RMENU: return lib::input::key_button::rightalt;
        case VK_RWIN: return lib::input::key_button::rightsuper;
        case 0x30: return lib::input::key_button::num_0;
        case 0x31: return lib::input::key_button::num_1;
        case 0x32: return lib::input::key_button::num_2;
        case 0x33: return lib::input::key_button::num_3;
        case 0x34: return lib::input::key_button::num_4;
        case 0x35: return lib::input::key_button::num_5;
        case 0x36: return lib::input::key_button::num_6;
        case 0x37: return lib::input::key_button::num_7;
        case 0x38: return lib::input::key_button::num_8;
        case 0x39: return lib::input::key_button::num_9;
        case 0x41: return lib::input::key_button::a;
        case 0x42: return lib::input::key_button::b;
        case 0x43: return lib::input::key_button::c;
        case 0x44: return lib::input::key_button::d;
        case 0x45: return lib::input::key_button::e;
        case 0x46: return lib::input::key_button::f;
        case 0x47: return lib::input::key_button::g;
        case 0x48: return lib::input::key_button::h;
        case 0x49: return lib::input::key_button::i;
        case 0x4A: return lib::input::key_button::j;
        case 0x4B: return lib::input::key_button::k;
        case 0x4C: return lib::input::key_button::l;
        case 0x4D: return lib::input::key_button::m;
        case 0x4E: return lib::input::key_button::n;
        case 0x4F: return lib::input::key_button::o;
        case 0x50: return lib::input::key_button::p;
        case 0x51: return lib::input::key_button::q;
        case 0x52: return lib::input::key_button::r;
        case 0x53: return lib::input::key_button::s;
        case 0x54: return lib::input::key_button::t;
        case 0x55: return lib::input::key_button::u;
        case 0x56: return lib::input::key_button::v;
        case 0x57: return lib::input::key_button::w;
        case 0x58: return lib::input::key_button::x;
        case 0x59: return lib::input::key_button::y;
        case 0x5A: return lib::input::key_button::z;
        case VK_F1: return lib::input::key_button::f1;
        case VK_F2: return lib::input::key_button::f2;
        case VK_F3: return lib::input::key_button::f3;
        case VK_F4: return lib::input::key_button::f4;
        case VK_F5: return lib::input::key_button::f5;
        case VK_F6: return lib::input::key_button::f6;
        case VK_F7: return lib::input::key_button::f7;
        case VK_F8: return lib::input::key_button::f8;
        case VK_F9: return lib::input::key_button::f9;
        case VK_F10: return lib::input::key_button::f10;
        case VK_F11: return lib::input::key_button::f11;
        case VK_F12: return lib::input::key_button::f12;
		default: return lib::input::key_button::none;
    }
}
}