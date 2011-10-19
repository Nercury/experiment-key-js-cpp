#include "DrawTree.h"

#include <key-v8/KeyV8.h>

using namespace key;
using namespace v8;

namespace cvv8 {
    CVV8_TypeName_IMPL((key::DrawTree),"DrawTree");
}

DrawTree::DrawTree()
{
}

DrawTree::~DrawTree()
{
}

v8::Handle<v8::Object> DrawTree::at(const v8::Arguments & args)
{
	HandleScope handle_scope;

	if (args.Length() > 1) {
		auto transformations = args[0];
		DrawTreeItem li;
		if (transformations->IsArray()) {
			auto transformationsArray = transformations.As<Array>();
			for (uint32_t i = 0; i < transformationsArray->Length(); i++) {
				auto transformationValue = transformationsArray->Get(i);
				if (transformationValue->IsObject()) {
					li.transformations.push_back(
						transformationValue.As<Object>()
					);
				}
			}
		} else if (transformations->IsObject()) {
			li.transformations.push_back(
				transformations.As<Object>()
			);
		}

		if (li.transformations.size() > 0) {
			if (args.Length() == 2) {
				auto value = args[1];
				if (value->IsObject()) {
					li.item = value.As<v8::Object>();
				}
			} else {
				auto drawList = KeyV8::Class<DrawTree>().CtorFunction()->CallAsConstructor(0, NULL);
				auto drawListNative = cvv8::CastFromJS<DrawTree>(drawList);

				for (int i = 1; i < args.Length(); i++) {
					auto value = args[i];
					if (value->IsObject()) {
						drawListNative->addItem(value.As<v8::Object>());
					}
				}

				li.item = Handle<Object>(drawList.As<v8::Object>());
			}
		}

		if (!li.item.IsEmpty()) {
			list.push_back(li);
		}
	}

	return handle_scope.Close(args.This());
}

v8::Handle<v8::Object> DrawTree::add(const v8::Arguments & args)
{
	HandleScope handle_scope;

	for (int i = 0; i < args.Length(); i++) {
		auto value = args[i];
		if (value->IsObject()) {
			DrawTreeItem li;
			li.item = args[i].As<v8::Object>();
			list.push_back(li);
		}
	}

	return handle_scope.Close(args.This());
}
