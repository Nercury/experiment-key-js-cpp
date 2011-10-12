#include "Keycode.h"

#include <vector>
#include <string>
#include <boost/tuple/tuple.hpp>
#include <boost/assign.hpp>

#include <SDL2/SDL_keycode.h>

using namespace v8;

namespace cvv8 {
    CVV8_TypeName_IMPL((key::Keycode),"Keycode");
}

void key::Keycode::loadKeycodes(std::vector<std::string> & items, cvv8::ClassCreator<key::Keycode> & cc, v8::Handle<v8::ObjectTemplate> proto)
{
	std::vector<boost::tuple<std::string, int32_t, std::string>> enum_items =
	boost::assign::tuple_list_of
    ("UNKNOWN", SDLK_UNKNOWN, "")

    ("RETURN", SDLK_RETURN, "\r")
    ("ESCAPE", SDLK_ESCAPE, "\033")
    ("BACKSPACE", SDLK_BACKSPACE, "\b")
    ("TAB", SDLK_TAB, "\t")
    ("SPACE", SDLK_SPACE, " ")
    ("EXCLAIM", SDLK_EXCLAIM, "!")
    ("QUOTEDBL", SDLK_QUOTEDBL, "\"")
    ("HASH", SDLK_HASH, "#")
    ("PERCENT", SDLK_PERCENT, "%")
    ("DOLLAR", SDLK_DOLLAR, "$")
    ("AMPERSAND", SDLK_AMPERSAND, "&")
    ("QUOTE", SDLK_QUOTE, "'")
    ("LEFTPAREN", SDLK_LEFTPAREN, "(")
    ("RIGHTPAREN", SDLK_RIGHTPAREN, ")")
    ("ASTERISK", SDLK_ASTERISK, "*")
    ("PLUS", SDLK_PLUS, "+")
    ("COMMA", SDLK_COMMA, ",")
    ("MINUS", SDLK_MINUS, "-")
    ("PERIOD", SDLK_PERIOD, ".")
    ("SLASH", SDLK_SLASH, "/")
    ("0", SDLK_0, "0")
    ("1", SDLK_1, "1")
    ("2", SDLK_2, "2")
    ("3", SDLK_3, "3")
    ("4", SDLK_4, "4")
    ("5", SDLK_5, "5")
    ("6", SDLK_6, "6")
    ("7", SDLK_7, "7")
    ("8", SDLK_8, "8")
    ("9", SDLK_9, "9")
    ("COLON", SDLK_COLON, ":")
    ("SEMICOLON", SDLK_SEMICOLON, ";")
    ("LESS", SDLK_LESS, "<")
    ("EQUALS", SDLK_EQUALS, "=")
    ("GREATER", SDLK_GREATER, ">")
    ("QUESTION", SDLK_QUESTION, "?")
    ("AT", SDLK_AT, "@")
    /* 
       Skip uppercase letters
     */
    ("LEFTBRACKET", SDLK_LEFTBRACKET, "[")
    ("BACKSLASH", SDLK_BACKSLASH, "\\")
    ("RIGHTBRACKET", SDLK_RIGHTBRACKET, "]")
    ("CARET", SDLK_CARET, "^")
    ("UNDERSCORE", SDLK_UNDERSCORE, "_")
    ("BACKQUOTE", SDLK_BACKQUOTE, "`")
    ("a", SDLK_a, "a")
    ("b", SDLK_b, "b")
    ("c", SDLK_c, "c")
    ("d", SDLK_d, "d")
    ("e", SDLK_e, "e")
    ("f", SDLK_f, "f")
    ("g", SDLK_g, "g")
    ("h", SDLK_h, "h")
    ("i", SDLK_i, "i")
    ("j", SDLK_j, "j")
    ("k", SDLK_k, "k")
    ("l", SDLK_l, "l")
    ("m", SDLK_m, "m")
    ("n", SDLK_n, "n")
    ("o", SDLK_o, "o")
    ("p", SDLK_p, "p")
    ("q", SDLK_q, "q")
    ("r", SDLK_r, "r")
    ("s", SDLK_s, "s")
    ("t", SDLK_t, "t")
    ("u", SDLK_u, "u")
    ("v", SDLK_v, "v")
    ("w", SDLK_w, "w")
    ("x", SDLK_x, "x")
    ("y", SDLK_y, "y")
    ("z", SDLK_z, "z")

    ("CAPSLOCK", SDLK_CAPSLOCK, "Scancode.CAPSLOCK")

    ("F1", SDLK_F1, "Scancode.F1")
    ("F2", SDLK_F2, "Scancode.F2")
    ("F3", SDLK_F3, "Scancode.F3")
    ("F4", SDLK_F4, "Scancode.F4")
    ("F5", SDLK_F5, "Scancode.F5")
    ("F6", SDLK_F6, "Scancode.F6")
    ("F7", SDLK_F7, "Scancode.F7")
    ("F8", SDLK_F8, "Scancode.F8")
    ("F9", SDLK_F9, "Scancode.F9")
    ("F10", SDLK_F10, "Scancode.F10")
    ("F11", SDLK_F11, "Scancode.F11")
    ("F12", SDLK_F12, "Scancode.F12")

    ("PRINTSCREEN", SDLK_PRINTSCREEN, "Scancode.PRINTSCREEN")
    ("SCROLLLOCK", SDLK_SCROLLLOCK, "Scancode.SCROLLLOCK")
    ("PAUSE", SDLK_PAUSE, "Scancode.PAUSE")
    ("INSERT", SDLK_INSERT, "Scancode.INSERT")
    ("HOME", SDLK_HOME, "Scancode.HOME")
    ("PAGEUP", SDLK_PAGEUP, "Scancode.PAGEUP")
    ("DELETE", SDLK_DELETE, "")
    ("END", SDLK_END, "Scancode.END")
    ("PAGEDOWN", SDLK_PAGEDOWN, "Scancode.PAGEDOWN")
    ("RIGHT", SDLK_RIGHT, "Scancode.RIGHT")
    ("LEFT", SDLK_LEFT, "Scancode.LEFT")
    ("DOWN", SDLK_DOWN, "Scancode.DOWN")
    ("UP", SDLK_UP, "Scancode.UP")

    ("NUMLOCKCLEAR", SDLK_NUMLOCKCLEAR, "Scancode.NUMLOCKCLEAR")
    ("KP_DIVIDE", SDLK_KP_DIVIDE, "Scancode.KP_DIVIDE")
    ("KP_MULTIPLY", SDLK_KP_MULTIPLY, "Scancode.KP_MULTIPLY")
    ("KP_MINUS", SDLK_KP_MINUS, "Scancode.KP_MINUS")
    ("KP_PLUS", SDLK_KP_PLUS, "Scancode.KP_PLUS")
    ("KP_ENTER", SDLK_KP_ENTER, "Scancode.KP_ENTER")
    ("KP_1", SDLK_KP_1, "Scancode.KP_1")
    ("KP_2", SDLK_KP_2, "Scancode.KP_2")
    ("KP_3", SDLK_KP_3, "Scancode.KP_3")
    ("KP_4", SDLK_KP_4, "Scancode.KP_4")
    ("KP_5", SDLK_KP_5, "Scancode.KP_5")
    ("KP_6", SDLK_KP_6, "Scancode.KP_6")
    ("KP_7", SDLK_KP_7, "Scancode.KP_7")
    ("KP_8", SDLK_KP_8, "Scancode.KP_8")
    ("KP_9", SDLK_KP_9, "Scancode.KP_9")
    ("KP_0", SDLK_KP_0, "Scancode.KP_0")
    ("KP_PERIOD", SDLK_KP_PERIOD, "Scancode.KP_PERIOD")

    ("APPLICATION", SDLK_APPLICATION, "Scancode.APPLICATION")
    ("POWER", SDLK_POWER, "Scancode.POWER")
    ("KP_EQUALS", SDLK_KP_EQUALS, "Scancode.KP_EQUALS")
    ("F13", SDLK_F13, "Scancode.F13")
    ("F14", SDLK_F14, "Scancode.F14")
    ("F15", SDLK_F15, "Scancode.F15")
    ("F16", SDLK_F16, "Scancode.F16")
    ("F17", SDLK_F17, "Scancode.F17")
    ("F18", SDLK_F18, "Scancode.F18")
    ("F19", SDLK_F19, "Scancode.F19")
    ("F20", SDLK_F20, "Scancode.F20")
    ("F21", SDLK_F21, "Scancode.F21")
    ("F22", SDLK_F22, "Scancode.F22")
    ("F23", SDLK_F23, "Scancode.F23")
    ("F24", SDLK_F24, "Scancode.F24")
    ("EXECUTE", SDLK_EXECUTE, "Scancode.EXECUTE")
    ("HELP", SDLK_HELP, "Scancode.HELP")
    ("MENU", SDLK_MENU, "Scancode.MENU")
    ("SELECT", SDLK_SELECT, "Scancode.SELECT")
    ("STOP", SDLK_STOP, "Scancode.STOP")
    ("AGAIN", SDLK_AGAIN, "Scancode.AGAIN")
    ("UNDO", SDLK_UNDO, "Scancode.UNDO")
    ("CUT", SDLK_CUT, "Scancode.CUT")
    ("COPY", SDLK_COPY, "Scancode.COPY")
    ("PASTE", SDLK_PASTE, "Scancode.PASTE")
    ("FIND", SDLK_FIND, "Scancode.FIND")
    ("MUTE", SDLK_MUTE, "Scancode.MUTE")
    ("VOLUMEUP", SDLK_VOLUMEUP, "Scancode.VOLUMEUP")
    ("VOLUMEDOWN", SDLK_VOLUMEDOWN, "Scancode.VOLUMEDOWN")
    ("KP_COMMA", SDLK_KP_COMMA, "Scancode.KP_COMMA")
    ("KP_EQUALSAS400", SDLK_KP_EQUALSAS400,
        "Scancode.KP_EQUALSAS400")

    ("ALTERASE", SDLK_ALTERASE, "Scancode.ALTERASE")
    ("SYSREQ", SDLK_SYSREQ, "Scancode.SYSREQ")
    ("CANCEL", SDLK_CANCEL, "Scancode.CANCEL")
    ("CLEAR", SDLK_CLEAR, "Scancode.CLEAR")
    ("PRIOR", SDLK_PRIOR, "Scancode.PRIOR")
    ("RETURN2", SDLK_RETURN2, "Scancode.RETURN2")
    ("SEPARATOR", SDLK_SEPARATOR, "Scancode.SEPARATOR")
    ("OUT", SDLK_OUT, "Scancode.OUT")
    ("OPER", SDLK_OPER, "Scancode.OPER")
    ("CLEARAGAIN", SDLK_CLEARAGAIN, "Scancode.CLEARAGAIN")
    ("CRSEL", SDLK_CRSEL, "Scancode.CRSEL")
    ("EXSEL", SDLK_EXSEL, "Scancode.EXSEL")

    ("KP_00", SDLK_KP_00, "Scancode.KP_00")
    ("KP_000", SDLK_KP_000, "Scancode.KP_000")
    ("THOUSANDSSEPARATOR", SDLK_THOUSANDSSEPARATOR,
        "Scancode.THOUSANDSSEPARATOR")
    ("DECIMALSEPARATOR", SDLK_DECIMALSEPARATOR,
        "Scancode.DECIMALSEPARATOR")
    ("CURRENCYUNIT", SDLK_CURRENCYUNIT, "Scancode.CURRENCYUNIT")
    ("CURRENCYSUBUNIT", SDLK_CURRENCYSUBUNIT,
        "Scancode.CURRENCYSUBUNIT")
    ("KP_LEFTPAREN", SDLK_KP_LEFTPAREN, "Scancode.KP_LEFTPAREN")
    ("KP_RIGHTPAREN", SDLK_KP_RIGHTPAREN, "Scancode.KP_RIGHTPAREN")
    ("KP_LEFTBRACE", SDLK_KP_LEFTBRACE, "Scancode.KP_LEFTBRACE")
    ("KP_RIGHTBRACE", SDLK_KP_RIGHTBRACE, "Scancode.KP_RIGHTBRACE")
    ("KP_TAB", SDLK_KP_TAB, "Scancode.KP_TAB")
    ("KP_BACKSPACE", SDLK_KP_BACKSPACE, "Scancode.KP_BACKSPACE")
    ("KP_A", SDLK_KP_A, "Scancode.KP_A")
    ("KP_B", SDLK_KP_B, "Scancode.KP_B")
    ("KP_C", SDLK_KP_C, "Scancode.KP_C")
    ("KP_D", SDLK_KP_D, "Scancode.KP_D")
    ("KP_E", SDLK_KP_E, "Scancode.KP_E")
    ("KP_F", SDLK_KP_F, "Scancode.KP_F")
    ("KP_XOR", SDLK_KP_XOR, "Scancode.KP_XOR")
    ("KP_POWER", SDLK_KP_POWER, "Scancode.KP_POWER")
    ("KP_PERCENT", SDLK_KP_PERCENT, "Scancode.KP_PERCENT")
    ("KP_LESS", SDLK_KP_LESS, "Scancode.KP_LESS")
    ("KP_GREATER", SDLK_KP_GREATER, "Scancode.KP_GREATER")
    ("KP_AMPERSAND", SDLK_KP_AMPERSAND, "Scancode.KP_AMPERSAND")
    ("KP_DBLAMPERSAND", SDLK_KP_DBLAMPERSAND,
        "Scancode.KP_DBLAMPERSAND")
    ("KP_VERTICALBAR", SDLK_KP_VERTICALBAR,
        "Scancode.KP_VERTICALBAR")
    ("KP_DBLVERTICALBAR", SDLK_KP_DBLVERTICALBAR,
        "Scancode.KP_DBLVERTICALBAR")
    ("KP_COLON", SDLK_KP_COLON, "Scancode.KP_COLON")
    ("KP_HASH", SDLK_KP_HASH, "Scancode.KP_HASH")
    ("KP_SPACE", SDLK_KP_SPACE, "Scancode.KP_SPACE")
    ("KP_AT", SDLK_KP_AT, "Scancode.KP_AT")
    ("KP_EXCLAM", SDLK_KP_EXCLAM, "Scancode.KP_EXCLAM")
    ("KP_MEMSTORE", SDLK_KP_MEMSTORE, "Scancode.KP_MEMSTORE")
    ("KP_MEMRECALL", SDLK_KP_MEMRECALL, "Scancode.KP_MEMRECALL")
    ("KP_MEMCLEAR", SDLK_KP_MEMCLEAR, "Scancode.KP_MEMCLEAR")
    ("KP_MEMADD", SDLK_KP_MEMADD, "Scancode.KP_MEMADD")
    ("KP_MEMSUBTRACT", SDLK_KP_MEMSUBTRACT,
        "Scancode.KP_MEMSUBTRACT")
    ("KP_MEMMULTIPLY", SDLK_KP_MEMMULTIPLY,
        "Scancode.KP_MEMMULTIPLY")
    ("KP_MEMDIVIDE", SDLK_KP_MEMDIVIDE, "Scancode.KP_MEMDIVIDE")
    ("KP_PLUSMINUS", SDLK_KP_PLUSMINUS, "Scancode.KP_PLUSMINUS")
    ("KP_CLEAR", SDLK_KP_CLEAR, "Scancode.KP_CLEAR")
    ("KP_CLEARENTRY", SDLK_KP_CLEARENTRY, "Scancode.KP_CLEARENTRY")
    ("KP_BINARY", SDLK_KP_BINARY, "Scancode.KP_BINARY")
    ("KP_OCTAL", SDLK_KP_OCTAL, "Scancode.KP_OCTAL")
    ("KP_DECIMAL", SDLK_KP_DECIMAL, "Scancode.KP_DECIMAL")
    ("KP_HEXADECIMAL", SDLK_KP_HEXADECIMAL,
        "Scancode.KP_HEXADECIMAL")

    ("LCTRL", SDLK_LCTRL, "Scancode.LCTRL")
    ("LSHIFT", SDLK_LSHIFT, "Scancode.LSHIFT")
    ("LALT", SDLK_LALT, "Scancode.LALT")
    ("LGUI", SDLK_LGUI, "Scancode.LGUI")
    ("RCTRL", SDLK_RCTRL, "Scancode.RCTRL")
    ("RSHIFT", SDLK_RSHIFT, "Scancode.RSHIFT")
    ("RALT", SDLK_RALT, "Scancode.RALT")
    ("RGUI", SDLK_RGUI, "Scancode.RGUI")

    ("MODE", SDLK_MODE, "Scancode.MODE")

    ("AUDIONEXT", SDLK_AUDIONEXT, "Scancode.AUDIONEXT")
    ("AUDIOPREV", SDLK_AUDIOPREV, "Scancode.AUDIOPREV")
    ("AUDIOSTOP", SDLK_AUDIOSTOP, "Scancode.AUDIOSTOP")
    ("AUDIOPLAY", SDLK_AUDIOPLAY, "Scancode.AUDIOPLAY")
    ("AUDIOMUTE", SDLK_AUDIOMUTE, "Scancode.AUDIOMUTE")
    ("MEDIASELECT", SDLK_MEDIASELECT, "Scancode.MEDIASELECT")
    ("WWW", SDLK_WWW, "Scancode.WWW")
    ("MAIL", SDLK_MAIL, "Scancode.MAIL")
    ("CALCULATOR", SDLK_CALCULATOR, "Scancode.CALCULATOR")
    ("COMPUTER", SDLK_COMPUTER, "Scancode.COMPUTER")
    ("AC_SEARCH", SDLK_AC_SEARCH, "Scancode.AC_SEARCH")
    ("AC_HOME", SDLK_AC_HOME, "Scancode.AC_HOME")
    ("AC_BACK", SDLK_AC_BACK, "Scancode.AC_BACK")
    ("AC_FORWARD", SDLK_AC_FORWARD, "Scancode.AC_FORWARD")
    ("AC_STOP", SDLK_AC_STOP, "Scancode.AC_STOP")
    ("AC_REFRESH", SDLK_AC_REFRESH, "Scancode.AC_REFRESH")
    ("AC_BOOKMARKS", SDLK_AC_BOOKMARKS, "Scancode.AC_BOOKMARKS")

    ("BRIGHTNESSDOWN", SDLK_BRIGHTNESSDOWN,
        "Scancode.BRIGHTNESSDOWN")
    ("BRIGHTNESSUP", SDLK_BRIGHTNESSUP, "Scancode.BRIGHTNESSUP")
    ("DISPLAYSWITCH", SDLK_DISPLAYSWITCH, "Scancode.DISPLAYSWITCH")
    ("KBDILLUMTOGGLE", SDLK_KBDILLUMTOGGLE,
        "Scancode.KBDILLUMTOGGLE")
    ("KBDILLUMDOWN", SDLK_KBDILLUMDOWN, "Scancode.KBDILLUMDOWN")
    ("KBDILLUMUP", SDLK_KBDILLUMUP, "Scancode.KBDILLUMUP")
    ("EJECT", SDLK_EJECT, "Scancode.EJECT")
    ("SLEEP", SDLK_SLEEP, "Scancode.SLEEP")
	;

	HandleScope handle_scope;

	for (auto it = enum_items.cbegin(); it != enum_items.cend(); ++it) {
		cc.CtorFunction()->Set(
			v8::String::NewSymbol(boost::get<0>(*it).c_str()),
			cvv8::CastToJS<int32_t>(boost::get<1>(*it)),
			v8::PropertyAttribute::ReadOnly
		);
		items.push_back(boost::get<0>(*it));
		std::map<std::string, std::string> info = boost::assign::map_list_of<std::string, std::string>
			("field", "static enum")
			("return_type", "int")
			("doc", boost::get<2>(*it));

		cc.CtorFunction()->Set(
			v8::String::NewSymbol((std::string("reflect__") + boost::get<0>(*it)).c_str()),
			cvv8::CastToJS(info), PropertyAttribute::ReadOnly
			);
	}
}