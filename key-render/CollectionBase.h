#pragma once

#include <key-render/lib_key_render.h>
#include <key-common/types.h>
#include <key-v8/expose_headers.hpp>

#include <key-render/RenderItemBase.h>

namespace key {

	class CollectionBase 
		: public RenderItemBase
	{
	protected:
		std::vector<internal::RenderListItemWrapper> items;
		bool visible;

		uint32_t appendRenderObject(v8::Handle<v8::Object> & obj);
		uint32_t appendArray(v8::Handle<v8::Array> & items);
	public:
		CollectionBase() {};
		virtual ~CollectionBase() {};
		virtual uint32_t append(const v8::Arguments & args);
		virtual v8::Handle<v8::Object> replace(const v8::Arguments & args);
		virtual void setVisible(bool value);
		bool getVisible() { return this->visible };
	};

}