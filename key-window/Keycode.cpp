#include "KeyCode.h"

#include <vector>
#include <string>
#include <boost/tuple/tuple.hpp>
#include <boost/assign.hpp>

#include <SDL2/SDL_keycode.h>

using namespace v8;

namespace cvv8 {
    CVV8_TypeName_IMPL((key::KeyCode),"KeyCode");
}

void key::KeyCode::loadKeyCodes(std::vector<std::string> & items, cvv8::ClassCreator<key::KeyCode> & cc, v8::Handle<v8::ObjectTemplate> proto)
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

    ("CAPSLOCK", SDLK_CAPSLOCK, "ScanCode.CAPSLOCK")

    ("F1", SDLK_F1, "ScanCode.F1")
    ("F2", SDLK_F2, "ScanCode.F2")
    ("F3", SDLK_F3, "ScanCode.F3")
    ("F4", SDLK_F4, "ScanCode.F4")
    ("F5", SDLK_F5, "ScanCode.F5")
    ("F6", SDLK_F6, "ScanCode.F6")
    ("F7", SDLK_F7, "ScanCode.F7")
    ("F8", SDLK_F8, "ScanCode.F8")
    ("F9", SDLK_F9, "ScanCode.F9")
    ("F10", SDLK_F10, "ScanCode.F10")
    ("F11", SDLK_F11, "ScanCode.F11")
    ("F12", SDLK_F12, "ScanCode.F12")

    ("PRINTSCREEN", SDLK_PRINTSCREEN, "ScanCode.PRINTSCREEN")
    ("SCROLLLOCK", SDLK_SCROLLLOCK, "ScanCode.SCROLLLOCK")
    ("PAUSE", SDLK_PAUSE, "ScanCode.PAUSE")
    ("INSERT", SDLK_INSERT, "ScanCode.INSERT")
    ("HOME", SDLK_HOME, "ScanCode.HOME")
    ("PAGEUP", SDLK_PAGEUP, "ScanCode.PAGEUP")
    ("DELETE", SDLK_DELETE, "")
    ("END", SDLK_END, "ScanCode.END")
    ("PAGEDOWN", SDLK_PAGEDOWN, "ScanCode.PAGEDOWN")
    ("RIGHT", SDLK_RIGHT, "ScanCode.RIGHT")
    ("LEFT", SDLK_LEFT, "ScanCode.LEFT")
    ("DOWN", SDLK_DOWN, "ScanCode.DOWN")
    ("UP", SDLK_UP, "ScanCode.UP")

    ("NUMLOCKCLEAR", SDLK_NUMLOCKCLEAR, "ScanCode.NUMLOCKCLEAR")
    ("KP_DIVIDE", SDLK_KP_DIVIDE, "ScanCode.KP_DIVIDE")
    ("KP_MULTIPLY", SDLK_KP_MULTIPLY, "ScanCode.KP_MULTIPLY")
    ("KP_MINUS", SDLK_KP_MINUS, "ScanCode.KP_MINUS")
    ("KP_PLUS", SDLK_KP_PLUS, "ScanCode.KP_PLUS")
    ("KP_ENTER", SDLK_KP_ENTER, "ScanCode.KP_ENTER")
    ("KP_1", SDLK_KP_1, "ScanCode.KP_1")
    ("KP_2", SDLK_KP_2, "ScanCode.KP_2")
    ("KP_3", SDLK_KP_3, "ScanCode.KP_3")
    ("KP_4", SDLK_KP_4, "ScanCode.KP_4")
    ("KP_5", SDLK_KP_5, "ScanCode.KP_5")
    ("KP_6", SDLK_KP_6, "ScanCode.KP_6")
    ("KP_7", SDLK_KP_7, "ScanCode.KP_7")
    ("KP_8", SDLK_KP_8, "ScanCode.KP_8")
    ("KP_9", SDLK_KP_9, "ScanCode.KP_9")
    ("KP_0", SDLK_KP_0, "ScanCode.KP_0")
    ("KP_PERIOD", SDLK_KP_PERIOD, "ScanCode.KP_PERIOD")

    ("APPLICATION", SDLK_APPLICATION, "ScanCode.APPLICATION")
    ("POWER", SDLK_POWER, "ScanCode.POWER")
    ("KP_EQUALS", SDLK_KP_EQUALS, "ScanCode.KP_EQUALS")
    ("F13", SDLK_F13, "ScanCode.F13")
    ("F14", SDLK_F14, "ScanCode.F14")
    ("F15", SDLK_F15, "ScanCode.F15")
    ("F16", SDLK_F16, "ScanCode.F16")
    ("F17", SDLK_F17, "ScanCode.F17")
    ("F18", SDLK_F18, "ScanCode.F18")
    ("F19", SDLK_F19, "ScanCode.F19")
    ("F20", SDLK_F20, "ScanCode.F20")
    ("F21", SDLK_F21, "ScanCode.F21")
    ("F22", SDLK_F22, "ScanCode.F22")
    ("F23", SDLK_F23, "ScanCode.F23")
    ("F24", SDLK_F24, "ScanCode.F24")
    ("EXECUTE", SDLK_EXECUTE, "ScanCode.EXECUTE")
    ("HELP", SDLK_HELP, "ScanCode.HELP")
    ("MENU", SDLK_MENU, "ScanCode.MENU")
    ("SELECT", SDLK_SELECT, "ScanCode.SELECT")
    ("STOP", SDLK_STOP, "ScanCode.STOP")
    ("AGAIN", SDLK_AGAIN, "ScanCode.AGAIN")
    ("UNDO", SDLK_UNDO, "ScanCode.UNDO")
    ("CUT", SDLK_CUT, "ScanCode.CUT")
    ("COPY", SDLK_COPY, "ScanCode.COPY")
    ("PASTE", SDLK_PASTE, "ScanCode.PASTE")
    ("FIND", SDLK_FIND, "ScanCode.FIND")
    ("MUTE", SDLK_MUTE, "ScanCode.MUTE")
    ("VOLUMEUP", SDLK_VOLUMEUP, "ScanCode.VOLUMEUP")
    ("VOLUMEDOWN", SDLK_VOLUMEDOWN, "ScanCode.VOLUMEDOWN")
    ("KP_COMMA", SDLK_KP_COMMA, "ScanCode.KP_COMMA")
    ("KP_EQUALSAS400", SDLK_KP_EQUALSAS400,
        "ScanCode.KP_EQUALSAS400")

    ("ALTERASE", SDLK_ALTERASE, "ScanCode.ALTERASE")
    ("SYSREQ", SDLK_SYSREQ, "ScanCode.SYSREQ")
    ("CANCEL", SDLK_CANCEL, "ScanCode.CANCEL")
    ("CLEAR", SDLK_CLEAR, "ScanCode.CLEAR")
    ("PRIOR", SDLK_PRIOR, "ScanCode.PRIOR")
    ("RETURN2", SDLK_RETURN2, "ScanCode.RETURN2")
    ("SEPARATOR", SDLK_SEPARATOR, "ScanCode.SEPARATOR")
    ("OUT", SDLK_OUT, "ScanCode.OUT")
    ("OPER", SDLK_OPER, "ScanCode.OPER")
    ("CLEARAGAIN", SDLK_CLEARAGAIN, "ScanCode.CLEARAGAIN")
    ("CRSEL", SDLK_CRSEL, "ScanCode.CRSEL")
    ("EXSEL", SDLK_EXSEL, "ScanCode.EXSEL")

    ("KP_00", SDLK_KP_00, "ScanCode.KP_00")
    ("KP_000", SDLK_KP_000, "ScanCode.KP_000")
    ("THOUSANDSSEPARATOR", SDLK_THOUSANDSSEPARATOR,
        "ScanCode.THOUSANDSSEPARATOR")
    ("DECIMALSEPARATOR", SDLK_DECIMALSEPARATOR,
        "ScanCode.DECIMALSEPARATOR")
    ("CURRENCYUNIT", SDLK_CURRENCYUNIT, "ScanCode.CURRENCYUNIT")
    ("CURRENCYSUBUNIT", SDLK_CURRENCYSUBUNIT,
        "ScanCode.CURRENCYSUBUNIT")
    ("KP_LEFTPAREN", SDLK_KP_LEFTPAREN, "ScanCode.KP_LEFTPAREN")
    ("KP_RIGHTPAREN", SDLK_KP_RIGHTPAREN, "ScanCode.KP_RIGHTPAREN")
    ("KP_LEFTBRACE", SDLK_KP_LEFTBRACE, "ScanCode.KP_LEFTBRACE")
    ("KP_RIGHTBRACE", SDLK_KP_RIGHTBRACE, "ScanCode.KP_RIGHTBRACE")
    ("KP_TAB", SDLK_KP_TAB, "ScanCode.KP_TAB")
    ("KP_BACKSPACE", SDLK_KP_BACKSPACE, "ScanCode.KP_BACKSPACE")
    ("KP_A", SDLK_KP_A, "ScanCode.KP_A")
    ("KP_B", SDLK_KP_B, "ScanCode.KP_B")
    ("KP_C", SDLK_KP_C, "ScanCode.KP_C")
    ("KP_D", SDLK_KP_D, "ScanCode.KP_D")
    ("KP_E", SDLK_KP_E, "ScanCode.KP_E")
    ("KP_F", SDLK_KP_F, "ScanCode.KP_F")
    ("KP_XOR", SDLK_KP_XOR, "ScanCode.KP_XOR")
    ("KP_POWER", SDLK_KP_POWER, "ScanCode.KP_POWER")
    ("KP_PERCENT", SDLK_KP_PERCENT, "ScanCode.KP_PERCENT")
    ("KP_LESS", SDLK_KP_LESS, "ScanCode.KP_LESS")
    ("KP_GREATER", SDLK_KP_GREATER, "ScanCode.KP_GREATER")
    ("KP_AMPERSAND", SDLK_KP_AMPERSAND, "ScanCode.KP_AMPERSAND")
    ("KP_DBLAMPERSAND", SDLK_KP_DBLAMPERSAND,
        "ScanCode.KP_DBLAMPERSAND")
    ("KP_VERTICALBAR", SDLK_KP_VERTICALBAR,
        "ScanCode.KP_VERTICALBAR")
    ("KP_DBLVERTICALBAR", SDLK_KP_DBLVERTICALBAR,
        "ScanCode.KP_DBLVERTICALBAR")
    ("KP_COLON", SDLK_KP_COLON, "ScanCode.KP_COLON")
    ("KP_HASH", SDLK_KP_HASH, "ScanCode.KP_HASH")
    ("KP_SPACE", SDLK_KP_SPACE, "ScanCode.KP_SPACE")
    ("KP_AT", SDLK_KP_AT, "ScanCode.KP_AT")
    ("KP_EXCLAM", SDLK_KP_EXCLAM, "ScanCode.KP_EXCLAM")
    ("KP_MEMSTORE", SDLK_KP_MEMSTORE, "ScanCode.KP_MEMSTORE")
    ("KP_MEMRECALL", SDLK_KP_MEMRECALL, "ScanCode.KP_MEMRECALL")
    ("KP_MEMCLEAR", SDLK_KP_MEMCLEAR, "ScanCode.KP_MEMCLEAR")
    ("KP_MEMADD", SDLK_KP_MEMADD, "ScanCode.KP_MEMADD")
    ("KP_MEMSUBTRACT", SDLK_KP_MEMSUBTRACT,
        "ScanCode.KP_MEMSUBTRACT")
    ("KP_MEMMULTIPLY", SDLK_KP_MEMMULTIPLY,
        "ScanCode.KP_MEMMULTIPLY")
    ("KP_MEMDIVIDE", SDLK_KP_MEMDIVIDE, "ScanCode.KP_MEMDIVIDE")
    ("KP_PLUSMINUS", SDLK_KP_PLUSMINUS, "ScanCode.KP_PLUSMINUS")
    ("KP_CLEAR", SDLK_KP_CLEAR, "ScanCode.KP_CLEAR")
    ("KP_CLEARENTRY", SDLK_KP_CLEARENTRY, "ScanCode.KP_CLEARENTRY")
    ("KP_BINARY", SDLK_KP_BINARY, "ScanCode.KP_BINARY")
    ("KP_OCTAL", SDLK_KP_OCTAL, "ScanCode.KP_OCTAL")
    ("KP_DECIMAL", SDLK_KP_DECIMAL, "ScanCode.KP_DECIMAL")
    ("KP_HEXADECIMAL", SDLK_KP_HEXADECIMAL,
        "ScanCode.KP_HEXADECIMAL")

    ("LCTRL", SDLK_LCTRL, "ScanCode.LCTRL")
    ("LSHIFT", SDLK_LSHIFT, "ScanCode.LSHIFT")
    ("LALT", SDLK_LALT, "ScanCode.LALT")
    ("LGUI", SDLK_LGUI, "ScanCode.LGUI")
    ("RCTRL", SDLK_RCTRL, "ScanCode.RCTRL")
    ("RSHIFT", SDLK_RSHIFT, "ScanCode.RSHIFT")
    ("RALT", SDLK_RALT, "ScanCode.RALT")
    ("RGUI", SDLK_RGUI, "ScanCode.RGUI")

    ("MODE", SDLK_MODE, "ScanCode.MODE")

    ("AUDIONEXT", SDLK_AUDIONEXT, "ScanCode.AUDIONEXT")
    ("AUDIOPREV", SDLK_AUDIOPREV, "ScanCode.AUDIOPREV")
    ("AUDIOSTOP", SDLK_AUDIOSTOP, "ScanCode.AUDIOSTOP")
    ("AUDIOPLAY", SDLK_AUDIOPLAY, "ScanCode.AUDIOPLAY")
    ("AUDIOMUTE", SDLK_AUDIOMUTE, "ScanCode.AUDIOMUTE")
    ("MEDIASELECT", SDLK_MEDIASELECT, "ScanCode.MEDIASELECT")
    ("WWW", SDLK_WWW, "ScanCode.WWW")
    ("MAIL", SDLK_MAIL, "ScanCode.MAIL")
    ("CALCULATOR", SDLK_CALCULATOR, "ScanCode.CALCULATOR")
    ("COMPUTER", SDLK_COMPUTER, "ScanCode.COMPUTER")
    ("AC_SEARCH", SDLK_AC_SEARCH, "ScanCode.AC_SEARCH")
    ("AC_HOME", SDLK_AC_HOME, "ScanCode.AC_HOME")
    ("AC_BACK", SDLK_AC_BACK, "ScanCode.AC_BACK")
    ("AC_FORWARD", SDLK_AC_FORWARD, "ScanCode.AC_FORWARD")
    ("AC_STOP", SDLK_AC_STOP, "ScanCode.AC_STOP")
    ("AC_REFRESH", SDLK_AC_REFRESH, "ScanCode.AC_REFRESH")
    ("AC_BOOKMARKS", SDLK_AC_BOOKMARKS, "ScanCode.AC_BOOKMARKS")

    ("BRIGHTNESSDOWN", SDLK_BRIGHTNESSDOWN,
        "ScanCode.BRIGHTNESSDOWN")
    ("BRIGHTNESSUP", SDLK_BRIGHTNESSUP, "ScanCode.BRIGHTNESSUP")
    ("DISPLAYSWITCH", SDLK_DISPLAYSWITCH, "ScanCode.DISPLAYSWITCH")
    ("KBDILLUMTOGGLE", SDLK_KBDILLUMTOGGLE,
        "ScanCode.KBDILLUMTOGGLE")
    ("KBDILLUMDOWN", SDLK_KBDILLUMDOWN, "ScanCode.KBDILLUMDOWN")
    ("KBDILLUMUP", SDLK_KBDILLUMUP, "ScanCode.KBDILLUMUP")
    ("EJECT", SDLK_EJECT, "ScanCode.EJECT")
    ("SLEEP", SDLK_SLEEP, "ScanCode.SLEEP")
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