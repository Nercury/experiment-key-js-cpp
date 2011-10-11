#pragma once

#include <key-v8/expose_headers.hpp>
#include <key-v8/reflect.hpp>

namespace key {

	struct MouseMotion
	{
	public:
		FLECT_PROP(key::MouseMotion, bLeft, bool, "bool", "Left button is pressed")
		bool bLeft;
		FLECT_PROP(key::MouseMotion, bMiddle, bool, "bool", "Middle button is pressed")
		bool bMiddle;
		FLECT_PROP(key::MouseMotion, bRight, bool, "bool", "Right button is pressed")
		bool bRight;
		FLECT_PROP(key::MouseMotion, bX1, bool, "bool", "Extra 1 button is pressed")
		bool bX1;
		FLECT_PROP(key::MouseMotion, bX2, bool, "bool", "Extra 2 button is pressed")
		bool bX2;
		FLECT_PROP(key::MouseMotion, xRel, int32_t, "bool", "Relative motion in the X direction")
		int32_t xRel;
		FLECT_PROP(key::MouseMotion, yRel, int32_t, "bool", "Relative motion in the Y direction")
		int32_t yRel;
		FLECT_PROP(key::MouseMotion, x, int32_t, "bool", "X coordinate, relative to window")
		int32_t x;
		FLECT_PROP(key::MouseMotion, y, int32_t, "bool", "Y coordinate, relative to window")
		int32_t y;

		/* reflection */
		typedef cvv8::Signature<key::MouseMotion (
			cvv8::CtorForwarder<key::MouseMotion *()>
		)> Ctors;

		static void reflect(std::vector<std::string> & items, cvv8::ClassCreator<key::MouseMotion> & cc, 
			v8::Handle<v8::ObjectTemplate> proto, bool for_static) {

			REFLECT(bLeft)
			REFLECT(bMiddle)
			REFLECT(bRight)
			REFLECT(bX1)
			REFLECT(bX2)
			REFLECT(xRel)
			REFLECT(yRel)
			REFLECT(x)
			REFLECT(y)
		}
	};
}

namespace cvv8 {
    CVV8_TypeName_DECL((key::MouseMotion));

    template <>
    class ClassCreator_Factory<key::MouseMotion>
     : public ClassCreator_Factory_Dispatcher< key::MouseMotion,
          CtorArityDispatcher<key::MouseMotion::Ctors> >
    {};

    template <>
    struct JSToNative< key::MouseMotion > : JSToNative_ClassCreator< key::MouseMotion >
    {};
}