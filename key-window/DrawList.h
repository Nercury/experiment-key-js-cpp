#pragma once

#include <vector>

#include <key-common/types.h>
#include <key-v8/expose_headers.hpp>
#include <key-v8/reflect.hpp>

namespace key
{
	struct DrawListItem
	{
		std::vector<v8::Handle<v8::Object>> transformations;
		v8::Handle<v8::Object> item;
	};

	class DrawList
	{
	private:
		std::vector<key::DrawListItem> list;

		void addItem(v8::Handle<v8::Object> item) { DrawListItem li; li.item = item; list.push_back(li); }
	public:
		DrawList();
		~DrawList();

		FLECT_M(key::DrawList, at, v8::Handle<v8::Object> (const v8::Arguments &), "void", "(transformArray, childList)", 
			"Use this to add child render list transformed by specified parameters.")
		v8::Handle<v8::Object> at(const v8::Arguments & args);

		FLECT_M(key::DrawList, add, v8::Handle<v8::Object> (const v8::Arguments &), "void", "(listObject)", 
			"Use this to add child to this render list.")
		v8::Handle<v8::Object> add(const v8::Arguments & args);

		typedef cvv8::Signature<key::DrawList (
			cvv8::CtorForwarder<key::DrawList *()>
		)> Ctors;
		
		static void reflect(std::vector<std::string> & items, cvv8::ClassCreator<key::DrawList> & cc, 
			v8::Handle<v8::ObjectTemplate> proto, bool for_static) {
			
			REFLECT(at)
			REFLECT(add)
		}
	};

}

namespace cvv8 {
    CVV8_TypeName_DECL((key::DrawList));

    template <>
    class ClassCreator_Factory<key::DrawList>
     : public ClassCreator_Factory_Dispatcher< key::DrawList,
          CtorArityDispatcher<key::DrawList::Ctors> >
    {};

    template <>
    struct JSToNative< key::DrawList > : JSToNative_ClassCreator< key::DrawList >
    {};
}