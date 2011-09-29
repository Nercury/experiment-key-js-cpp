#include "SsWindow.h"

#include <cvv8/properties.hpp>
#include <key-window/Window.h>

namespace cv = cvv8;
using namespace v8;

void key::SsWindow::initCore(Handle<Object> & dest) {
	{
		typedef cvv8::ClassCreator<key::Window> WindowCC;

		WindowCC & cc(WindowCC::Instance());

		if( cc.IsSealed() ) {
			cc.AddClassTo( cvv8::TypeName<key::Window>::Value, dest );
			return;
		}

		Handle<ObjectTemplate> const & proto( cc.Prototype() );
		std::vector<std::string> items;

		Window::reflect(items, cc, proto, false);
		Window::reflect(items, cc, proto, true);
		cc.CtorFunction()->Set(JSTR("__fields"), cv::CastToJS(items));

		cc.AddClassTo( cvv8::TypeName<key::Window>::Value, dest );
	}
}