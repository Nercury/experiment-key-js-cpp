#include "SsWindow.h"

#include <cvv8/properties.hpp>
#include <key-window/Window.h>

void key::SsWindow::initCore(v8::Handle<v8::Object> & dest) {
	typedef cvv8::ClassCreator<key::Window> CC;

	CC & cc(CC::Instance());

	if( cc.IsSealed() ) {
		cc.AddClassTo( cvv8::TypeName<key::Window>::Value, dest );
		return;
	}

	v8::Handle<v8::ObjectTemplate> const & proto( cc.Prototype() );
	proto->SetAccessor(JSTR("windowTitle"),
		cvv8::MemberToGetter<key::Window,std::string,&key::Window::windowTitle>::Get,
		cvv8::MemberToSetter<key::Window,std::string,&key::Window::windowTitle>::Set
	);

	cc
		.AddClassTo( cvv8::TypeName<key::Window>::Value, dest );
}