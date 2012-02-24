#pragma once

#include <vector>

#include <key-common/types.h>
#include <key-v8/expose_headers.hpp>
#include <key-v8/reflect.hpp>

namespace key
{
	struct DrawTreeItem
	{
		std::vector<v8::Handle<v8::Object>> transformations;
		v8::Handle<v8::Object> item;
	};

	class DrawTree
	{
	private:
		std::vector<key::DrawTreeItem> list;

		void addItem(v8::Handle<v8::Object> item) { DrawTreeItem li; li.item = item; list.push_back(li); }
	public:
		DrawTree();
		~DrawTree();

		FLECT_M(key::DrawTree, at, v8::Handle<v8::Object> (const v8::Arguments &), "void", "(transformArray, childList)", 
			"Use this to add child render list transformed by specified parameters.")
		v8::Handle<v8::Object> at(const v8::Arguments & args);

		FLECT_M(key::DrawTree, add, v8::Handle<v8::Object> (const v8::Arguments &), "void", "(listObject)", 
			"Use this to add child to this render list.")
		v8::Handle<v8::Object> add(const v8::Arguments & args);

		typedef cvv8::Signature<key::DrawTree (
			cvv8::CtorForwarder<key::DrawTree *()>
		)> Ctors;
		
		static void reflect(std::vector<std::string> & items, cvv8::ClassCreator<key::DrawTree> & cc, 
			v8::Handle<v8::ObjectTemplate> proto, bool for_static) {
			
			REFLECT(at)
			REFLECT(add)
		}
	};

}

namespace cvv8 {
    CVV8_TypeName_DECL((key::DrawTree));

    template <>
    class ClassCreator_Factory<key::DrawTree>
     : public ClassCreator_Factory_Dispatcher< key::DrawTree,
          CtorArityDispatcher<key::DrawTree::Ctors> >
    {};

    template <>
    struct JSToNative< key::DrawTree > : JSToNative_ClassCreator< key::DrawTree >
    {};
}