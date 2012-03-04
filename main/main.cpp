#include <memory>
#include <key-common/app.h>
#include <key-common/JsonConfig.h>

#include <key-v8/KeyV8.h>
#include <key-opengl/GLRenderer.h>

#include <key-window/Window.h>
#include <key-window/MouseMotion.h>
#include <key-window/Scancode.h>
#include <key-window/Keycode.h>
#include <key-window/KeyEvent.h>
#include <key-window/DrawTree.h>
#include <key-window/Translate.h>
#include <key-render/RenderList.h>

using namespace key;

int main(int argc, char* argv[])
{
	setAppPath(*argv);

	std::cout << getAppPath() << std::endl;
	
	Renderer::addRenderer("OpenGL", std::make_shared<key::GLRenderer>());

	JsonConfig config("config.js");
	std::string js_dir(joinPath(getAppPath(), config.js_root_dir));

	{
		auto v8 = KeyV8::New(js_dir);
		v8->Reflect<Window>("key.input");
		v8->Reflect<MouseMotion>("key.input");
		v8->Reflect<ScanCode>("key.input");
		v8->Reflect<KeyCode>("key.input");
		v8->Reflect<KeyEvent>("key.input");
		v8->Reflect<DrawTree>("key.scene");
		v8->Reflect<Translate>("key.scene");
		v8->Reflect<RenderList>("key.render");

		v8->Run(config.js_main_file);

		v8::V8::Dispose();
	}

	system("PAUSE");

	return 0;
}
