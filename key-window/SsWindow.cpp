#include "SsWindow.h"

#include <cvv8/properties.hpp>
#include <key-window/Window.h>

namespace cv = cvv8;
using namespace v8;

void key::SsWindow::initCore(Handle<Object> & dest) {
	typedef cvv8::ClassCreator<key::Window> CC;

	CC & cc(CC::Instance());

	if( cc.IsSealed() ) {
		cc.AddClassTo( cvv8::TypeName<key::Window>::Value, dest );
		return;
	}

	Handle<ObjectTemplate> const & proto( cc.Prototype() );
	proto->SetAccessor(JSTR("windowTitle"),
		cv::MemberToGetter<key::Window,std::string,&key::Window::windowTitle>::Get,
		cv::MethodToSetter<key::Window, void (std::string), &key::Window::setWindowTitle>::Set
	);
	proto->SetAccessor(JSTR("onWindowInit"),
		cv::MemberToGetter<key::Window,Persistent<Function>, &key::Window::onWindowInit>::Get,
		cv::MethodToSetter<key::Window,void (Handle<Value>),&key::Window::setOnWindowInit>::Set
	);

	cc
		("run", cv::MethodToInCa<key::Window, void (const Arguments & args),
			&key::Window::run>::Call)
		.AddClassTo( cvv8::TypeName<key::Window>::Value, dest );
}