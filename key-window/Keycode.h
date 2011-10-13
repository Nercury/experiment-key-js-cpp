#pragma once

#include <key-v8/expose_headers.hpp>
#include <key-v8/reflect.hpp>

namespace key {

	struct KeyCode
	{
	private:
		static void loadKeyCodes(std::vector<std::string> & items, cvv8::ClassCreator<key::KeyCode> & cc, v8::Handle<v8::ObjectTemplate> proto);
	public:
		/* reflection */
		typedef cvv8::Signature<key::KeyCode (
		)> Ctors;
		
		static void reflect(std::vector<std::string> & items, cvv8::ClassCreator<key::KeyCode> & cc, 
			v8::Handle<v8::ObjectTemplate> proto, bool for_static) {

			if (for_static) {
				loadKeyCodes(items, cc, proto);
			}
		}
	};
}

namespace cvv8 {
    CVV8_TypeName_DECL((key::KeyCode));

    template <>
    class ClassCreator_Factory<key::KeyCode>
     : public ClassCreator_Factory_Dispatcher< key::KeyCode,
          CtorArityDispatcher<key::KeyCode::Ctors> >
    {};

    template <>
    struct JSToNative< key::KeyCode > : JSToNative_ClassCreator< key::KeyCode >
    {};
}