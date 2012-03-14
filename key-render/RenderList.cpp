#include "RenderList.h"

using namespace key;

namespace cvv8 {
    CVV8_TypeName_IMPL((key::RenderList),"RenderList");
}

internal::RenderListItemWrapper::RenderListItemWrapper(key::RenderItemBase * nativeItem, v8::Handle<v8::Object> obj) 
	: object(object), nativeItem(nativeItem) {
		
}

internal::RenderListItemWrapper::~RenderListItemWrapper() {

}

void internal::RenderListItemWrapper::process() {
	if (this->nativeItem != NULL) {
		this->nativeItem->process();
		return;
	}
}

v8::Handle<v8::Object> internal::RenderListItemWrapper::getObject() {
	v8::HandleScope scope;
	return scope.Close(this->object);
}

RenderList::RenderList() {

}

RenderList::~RenderList() {

}

static const char* ToCString(const v8::String::Utf8Value& value) {return*value ?*value : "<string conversion failed>";}

uint32_t RenderList::appendRenderObject(v8::Handle<v8::Object> & obj) {
	auto count = obj->InternalFieldCount();
	// our objects *have* internal field count
	RenderItemBase * nativeItem = NULL;

	if (count > 1) {
		// and first internal field contains pointer to char * name of the object
		auto typeId = obj->GetPointerFromInternalField(0); // type
		if (typeId == cvv8::TypeName<RenderList>::Value) {
			auto ext = obj->GetPointerFromInternalField(1); // object data
			if (ext != NULL) {
				nativeItem = static_cast<RenderItemBase *>(ext);
			}
		}
	}

	if (nativeItem != NULL) {
		internal::RenderListItemWrapper w(nativeItem, obj);
		items.push_back(w);

		return 1;
	}

	return 0;
}

uint32_t RenderList::appendArray(v8::Handle<v8::Array> & items) {
	uint32_t appendCount = 0;

	for (uint32_t i = 0; i < items->Length(); i++) {
		auto value = items->Get(i);
		if (value->IsArray()) {
			appendCount += this->appendArray(value.As<v8::Array>());
		} else if (value->IsObject()) {
			appendCount += this->appendRenderObject(value.As<v8::Object>());
		}
	}

	return appendCount;
}

uint32_t RenderList::append(const v8::Arguments & args) {
	v8::HandleScope scope;

	uint32_t appendCount = 0;

	if (args.Length() > 0) {
		for (int i = 0; i < args.Length(); i++) {
			auto value = args[i];
			if (value->IsArray()) {
				appendCount += this->appendArray(value.As<v8::Array>());
			} else if (value->IsObject()) {
				appendCount += this->appendRenderObject(value.As<v8::Object>());
			}
		}
	}

	return appendCount;
}

v8::Handle<v8::Object> RenderList::replace(const v8::Arguments & args) {
	v8::HandleScope scope;

	auto arr = v8::Array::New((int)this->items.size());
	for (size_t i = 0; i < this->items.size(); i++) {
		arr->Set((uint32_t)i, this->items.at(i).getObject());
	}
	this->items.clear();

	this->append(args);

	return scope.Close(arr);
}

void RenderList::setVisible(bool value) {

}

void RenderList::process() {
	for each (auto i in this->items) {
		i.process();
	}
}