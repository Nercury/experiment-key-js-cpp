#include <memory>
#include <iostream>
#include <key-common/app.h>
#include <key-common/JsonConfig.h>

#include <key-v8/KeyV8.h>
#include <key-opengl/GLRenderer.h>

#include <key-window/Window.h>
#include <key-window/MouseMotion.h>
#include <key-window/ScanCode.h>
#include <key-window/Keycode.h>
#include <key-window/KeyEvent.h>

using namespace std;
using namespace key;

int main(int argc, char* argv[])
{
	setAppPath(*argv);
	
	Renderer::addRenderer("OpenGL", make_shared<key::GLRenderer>());

	JsonConfig config("config.js");
	std::string js_dir(joinPath(getAppPath(), config.js_root_dir));

	{
		auto v8 = KeyV8::New(js_dir);
		v8->Reflect<Window>();
		v8->Reflect<MouseMotion>();
		v8->Reflect<ScanCode>();
		v8->Reflect<KeyCode>();
		v8->Reflect<KeyEvent>();

		v8->Run(config.js_main_file);
	}

	system("PAUSE");

	return 0;
}
