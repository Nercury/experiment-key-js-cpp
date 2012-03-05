#pragma once

#include <memory>

#include <key-render/lib_key_render.h>
#include <key-common/types.h>
#include <key-v8/reflect.hpp>

namespace key {

	class RenderList
	{
	private:
		std::vector<v8::Handle<v8::Object>> items;

		uint32_t appendRenderObject(v8::Handle<v8::Object> & obj);
		uint32_t appendArray(v8::Handle<v8::Array> & items);
	public:
		RenderList();
		~RenderList();

		FLECT_M(key::RenderList, append, uint32_t (const v8::Arguments &), "int", "(itemList)", 
			"Append child list items to this render list. Return number of objects appended.")
		uint32_t append(const v8::Arguments & args);

		FLECT_M(key::RenderList, replace, v8::Handle<v8::Object> (const v8::Arguments &), "array", "(itemList)", 
			"Set child list items to this render list. Returns items previously contained in the list.")
		v8::Handle<v8::Object> replace(const v8::Arguments & args);

		FLECT_GS(key::RenderList, visible, 
			Member, bool, visible, 
			Method, void (bool), setVisible, 
			"bool", "Get or set visibility of this render list item")
		bool visible; void setVisible(bool value);

		typedef cvv8::Signature<key::RenderList (
			cvv8::CtorForwarder<key::RenderList *()>
		)> Ctors;

		static void reflect(std::vector<std::string> & items, cvv8::ClassCreator<key::RenderList> & cc, 
			v8::Handle<v8::ObjectTemplate> proto, bool for_static) {
			
				REFLECT(append);
				REFLECT(replace);
				REFLECT(visible);

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