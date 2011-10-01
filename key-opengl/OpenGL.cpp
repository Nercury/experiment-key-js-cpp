#include "OpenGL.h"

#include <key-opengl/OpenGLInstance.h>
#include <key-window/Window.h>

using namespace key;
using namespace std;

fun_res_obj<DeviceInstance> OpenGL::createDevice(key::Window * window) {
	OpenGLInstance * device = new OpenGLInstance(window);
	shared_ptr<DeviceInstance> instance(device);

	// todo: pass settings to device.
	
	return fun_ok(instance);
}