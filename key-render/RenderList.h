#pragma once

#include <memory>
#include <key-v8/reflect.hpp>

#include <key-render/CollectionBase.h>

namespace key {

	namespace internal {
		class RenderListItemWrapper {
		private:
			RenderItemBase * nativeItem;
			v8::Handle<v8::Object> object;
		public:
			RenderListItemWrapper(key::RenderItemBase * nativeItem, v8::Handle<v8::Object> obj);
			~RenderListItemWrapper();
			void process();
			v8::Handle<v8::Object> getObject();
		};
	}

	class RenderList
		: public CollectionBase
	{
	public:
		RenderList();
		~RenderList();

		FLECT_M(key::RenderList, append, uint32_t (const v8::Arguments &), "int", "(itemList)", 
			"Append child list items to this render list. Return number of objects appended.")
		virtual uint32_t append(const v8::Arguments & args);

		FLECT_M(key::RenderList, replace, v8::Handle<v8::Object> (const v8::Arguments &), "array", "(itemList)", 
			"Set child list items to this render list. Returns items previously contained in the list.")
		virtual v8::Handle<v8::Object> replace(const v8::Arguments & args);

		FLECT_GS(key::RenderList, visible, 
			Member, bool, visible, 
			Method, void (bool), setVisible, 
			"bool", "Get or set visibility of this render list item")
		virtual void setVisible(bool value);

		virtual void process();

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