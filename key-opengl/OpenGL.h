#pragma once

#include <string>

#include <key-opengl/lib_key_opengl.h>
#include <key-window/Renderer.h>

namespace key {

	class OpenGL
		: public Renderer
	{
	public:
		OpenGL() {};
		virtual ~OpenGL() {};
		virtual std::string getName() { return "OpenGL Render Device"; };
		LIB_KEY_OPENGL virtual fun_res_obj<DeviceInstance> createDevice(key::Window * window);
	};

}