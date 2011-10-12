#pragma once

#include <key-v8/expose_headers.hpp>
#include <key-v8/reflect.hpp>

namespace key {

	struct Scancode
	{
	private:
		static void loadScancodes(std::vector<std::string> & items, cvv8::ClassCreator<key::Scancode> & cc, v8::Handle<v8::ObjectTemplate> proto);
	public:
		/* reflection */
		typedef cvv8::Signature<key::Scancode (
		)> Ctors;
		
		static void reflect(std::vector<std::string> & items, cvv8::ClassCreator<key::Scancode> & cc, 
			v8::Handle<v8::ObjectTemplate> proto, bool for_static) {

			if (for_static) {
				loadScancodes(items, cc, proto);
			}
		}
	};
}

namespace cvv8 {
    CVV8_TypeName_DECL((key::Scancode));

    template <>
    class ClassCreator_Factory<key::Scancode>
     : public ClassCreator_Factory_Dispatcher< key::Scancode,
          CtorArityDispatcher<key::Scancode::Ctors> >
    {};

    template <>
    struct JSToNative< key::Scancode > : JSToNative_ClassCreator< key::Scancode >
    {};
}