#pragma once

#include <vector>

#include <key-opengl/sdl_gl_headers.h>

#include <key-common/types.h>

namespace key {

	struct OpData;

	typedef void (*OpFunction)(OpData *);

	struct OpData {
		uint8_t next; // next execution point offset from current position
		union {
			GLenum GL_enum;
			GLbitfield GL_bitfield;
			GLuint GL_uint;
			GLint GL_int;
			GLsizei GL_sizei;
			GLboolean GL_boolean;
			GLbyte GL_byte;
			GLshort GL_short;
			GLubyte GL_ubyte;
			GLushort GL_ushort;
			GLulong GL_ulong;
			GLfloat GL_float;
			GLclampf GL_clampf;
			GLdouble GL_double;
			GLclampd GL_clampd;
			OpFunction function;
		};
	public:
		OpData() {}
		OpData(OpFunction op, uint8_t next) : function(op), next(next) { }
		OpData(GLulong val) : GL_ulong(val) { }
		OpData(GLint val) : GL_int(val) { }
		OpData(GLuint val) : GL_uint(val) { }
		OpData(GLshort val) : GL_short(val) { }
		OpData(GLushort val) : GL_ushort(val) { }
		OpData(GLbyte val) : GL_byte(val) { }
		OpData(GLubyte val) : GL_ubyte(val) { }
		OpData(GLfloat val) : GL_float(val) { }
		OpData(GLdouble val) : GL_double(val) { }
	};

	inline void fw_glLoadIdentity(OpData * data) {
		glLoadIdentity();
	};

	inline void fw_glTranslated(OpData * data) {
		glTranslated((data - 3)->GL_double, (data - 2)->GL_double, (data - 1)->GL_double);
	};

	inline void fw_glTranslatef(OpData * data) {
		glTranslatef((data - 3)->GL_float, (data - 2)->GL_float, (data - 1)->GL_float);
	};

	inline void fw_test(OpData * data) {
		glBegin(GL_QUADS);
			glColor3f(1, 0, 0); glVertex3f(0, 0, 0);
			glColor3f(1, 1, 0); glVertex3f(100, 0, 0);
			glColor3f(1, 0, 1); glVertex3f(100, 100, 0);
			glColor3f(1, 1, 1); glVertex3f(0, 100, 0);
		glEnd();
	};

}