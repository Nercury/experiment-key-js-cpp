#pragma once

#include <key-v8/expose_headers.hpp>
#include <key-v8/reflect.hpp>

namespace key {

	struct Keycode
	{
	private:
		static void loadKeycodes(std::vector<std::string> & items, cvv8::ClassCreator<key::Keycode> & cc, v8::Handle<v8::ObjectTemplate> proto);
	public:
		/* reflection */
		typedef cvv8::Signature<key::Keycode (
		)> Ctors;
		
		static void reflect(std::vector<std::string> & items, cvv8::ClassCreator<key::Keycode> & cc, 
			v8::Handle<v8::ObjectTemplate> proto, bool for_static) {

			if (for_static) {
				loadKeycodes(items, cc, proto);
			}
		}
	};
}

namespace cvv8 {
    CVV8_TypeName_DECL((key::Keycode));

    template <>
    class ClassCreator_Factory<key::Keycode>
     : public ClassCreator_Factory_Dispatcher< key::Keycode,
          CtorArityDispatcher<key::Keycode::Ctors> >
    {};

    template <>
    struct JSToNative< key::Keycode > : JSToNative_ClassCreator< key::Keycode >
    {};
}