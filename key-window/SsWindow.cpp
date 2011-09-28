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
	std::vector<std::string> items;

	Window::reflect(items, cc, proto, false);
	cc("run", cv::MethodToInCa<key::Window, void (const Arguments & args), &key::Window::run>::Call);

	Window::reflect(items, cc, proto, true);
	cc.CtorFunction()->Set(JSTR("__fields"), cv::CastToJS(items));

	cc.AddClassTo( cvv8::TypeName<key::Window>::Value, dest );


	/*proto->SetAccessor(JSTR("onWindowInit"),
		cv::MemberToGetter<key::Window,Persistent<Function>, &key::Window::onWindowInit>::Get,
		cv::MethodToSetter<key::Window,void (Handle<Value>),&key::Window::setOnWindowInit>::Set
	);
	proto->SetAccessor(JSTR("onWindowResize"),
		cv::MemberToGetter<key::Window,Persistent<Function>, &key::Window::onWindowResize>::Get,
		cv::MethodToSetter<key::Window,void (Handle<Value>),&key::Window::setOnWindowResize>::Set
	);*/
	/*proto->SetAccessor(JSTR("allRenderDevices"),
		cv::MemberToGetter<key::Window,std::vector<std::string>, &key::Window::allRenderDevices>::Get
	);*/
	
	//cc.CtorFunction()->SetAccessor(JSTR("test"), cv::FunctionToGetter<std::string (), &key::Window::test>::Get);
}