#include "RenderList.h"

using namespace key;

namespace cvv8 {
    CVV8_TypeName_IMPL((key::RenderList),"RenderList");
}

RenderList::RenderList() {

}

RenderList::~RenderList() {

}

static const char* ToCString(const v8::String::Utf8Value& value) {return*value ?*value : "<string conversion failed>";}

uint32_t RenderList::appendRenderObject(v8::Handle<v8::Object> & obj) {
	auto count = obj->InternalFieldCount();
	// our objects *have* internal field count
	if (count > 0) {
		// and first internal field contains pointer to char * name of the object
		auto className = (const char*)obj->GetPointerFromInternalField(0);

		// if this is another list
		if (strcmp(className, cvv8::TypeName<RenderList>::Value) == 0) {
			// make it as sub-render
		} else {
			// if this an object
			// make it construct render sequence
		}
		auto res = cvv8::CastFromJS<RenderList>(obj);
		
		//std::cout << val << std::endl;
	}

	auto v = *obj;

	items.push_back(obj);
	return 1;
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
		arr->Set((uint32_t)i, this->items.at(i));
	}
	this->items.clear();

	this->append(args);

	return scope.Close(arr);
}

void RenderList::setVisible(bool value) {

}

