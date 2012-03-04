#pragma once

#include <memory>

#include <key-render/lib_key_render.h>
#include <key-common/types.h>
#include <key-v8/reflect.hpp>

namespace key {

	class RenderList
	{
	public:
		RenderList();
		~RenderList();

		typedef cvv8::Signature<key::RenderList (
			cvv8::CtorForwarder<key::RenderList *()>
		)> Ctors;

		static void reflect(std::vector<std::string> & items, cvv8::ClassCreator<key::RenderList> & cc, 
			v8::Handle<v8::ObjectTemplate> proto, bool for_static) {
			
		}
	};

}

namespace cvv8 {
    CVV8_TypeName_DECL((key::RenderList));

    template <>
    class ClassCreator_Factory<key::RenderList>
     : public ClassCreator_Factory_Dispatcher< key::RenderList,
          CtorArityDispatcher<key::RenderList::Ctors> >
    {};

    template <>
    struct JSToNative< key::RenderList > : JSToNative_ClassCreator< key::RenderList >
    {};
}