#pragma once

#include <iostream>

#include <key-v8/expose_headers.hpp>

namespace key 
{

	class Translate
	{
	public:
		double x;
		double y;
		double z;

		Translate(double x, double y, double z) {};
		~Translate() {};

		typedef cvv8::Signature<key::Translate (
			cvv8::CtorForwarder<key::Translate *(double, double, double)>
		)> Ctors;
		
		static void reflect(std::vector<std::string> & items, cvv8::ClassCreator<key::Translate> & cc, 
			v8::Handle<v8::ObjectTemplate> proto, bool for_static) {

		}
	};

}

namespace cvv8 {
    CVV8_TypeName_DECL((key::Translate));

    template <>
    class ClassCreator_Factory<key::Translate>
     : public ClassCreator_Factory_Dispatcher< key::Translate,
          CtorArityDispatcher<key::Translate::Ctors> >
    {};

    template <>
    struct JSToNative< key::Translate > : JSToNative_ClassCreator< key::Translate >
    {};
}