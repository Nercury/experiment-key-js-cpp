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