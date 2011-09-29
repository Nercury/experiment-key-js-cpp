#include "OpenGL.h"

#include <key-opengl/OpenGLInstance.h>

using namespace key;
using namespace std;

fun_res_obj<DeviceInstance> OpenGL::createDevice() {
	OpenGLInstance * device = new OpenGLInstance();
	shared_ptr<DeviceInstance> instance(device);

	// todo: pass settings to device.
	
	return fun_ok(instance);
}