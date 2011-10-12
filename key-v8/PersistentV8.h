#pragma once

#include <key-v8/expose_headers.hpp>

namespace key {
/**
	Persistent handle wrapper for objects created from javascript.
	Keeps v8::Persistent reference to prevent javascript from deleting the
	object while it is in use by C++. Wrap this class in shared ptr.
	*/
	template<class T>
	class PersistentV8
	{
	private:
		bool owned;
		v8::Persistent<v8::Value> keeper;
		PersistentV8& operator=(const PersistentV8&) {}
	protected:
		T * native;
	public:
		PersistentV8() : owned(false), native(NULL) {}
		PersistentV8(v8::Handle<v8::Value> handle, bool owned = true) 
			: keeper(v8::Persistent<v8::Value>::New(handle)), native(cvv8::CastFromJS<T>(handle)), owned(owned) {}

		// not virtual. 
		~PersistentV8() { if (this->owned) keeper.Dispose(); }
		
		void Assign(v8::Handle<v8::Value> handle, bool owned = true) {
			this->Reset();
			this->keeper = v8::Persistent<v8::Value>::New(handle);
			this->native = cvv8::CastFromJS<T>(handle);
			this->owned = owned;
		}

		void Reset() {
			if (!keeper.IsEmpty()) {
				if (this->owned) {
					this->keeper.Dispose();
					this->keeper.Clear();
				}
			}
			this->native = NULL;
		}

		T * NativeObject() { return native; }
		inline v8::Persistent<v8::Value> & JsObject() { return this->keeper; }
	};
}