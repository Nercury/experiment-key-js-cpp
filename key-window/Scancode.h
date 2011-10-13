#pragma once

#include <key-v8/expose_headers.hpp>
#include <key-v8/reflect.hpp>

namespace key {

	struct ScanCode
	{
	private:
		static void loadScanCodes(std::vector<std::string> & items, cvv8::ClassCreator<key::ScanCode> & cc, v8::Handle<v8::ObjectTemplate> proto);
	public:
		/* reflection */
		typedef cvv8::Signature<key::ScanCode (
		)> Ctors;
		
		static void reflect(std::vector<std::string> & items, cvv8::ClassCreator<key::ScanCode> & cc, 
			v8::Handle<v8::ObjectTemplate> proto, bool for_static) {

			if (for_static) {
				loadScanCodes(items, cc, proto);
			}
		}
	};
}

namespace cvv8 {
    CVV8_TypeName_DECL((key::ScanCode));

    template <>
    class ClassCreator_Factory<key::ScanCode>
     : public ClassCreator_Factory_Dispatcher< key::ScanCode,
          CtorArityDispatcher<key::ScanCode::Ctors> >
    {};

    template <>
    struct JSToNative< key::ScanCode > : JSToNative_ClassCreator< key::ScanCode >
    {};
}