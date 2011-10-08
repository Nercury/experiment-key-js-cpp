#pragma once

#include <memory>

#include <key-v8/lib_key_v8.h>
#include <key-v8/expose_headers.hpp>

#include <cvv8/arguments.hpp>

namespace key
{
	/**
	Persistent handle wrapper for objects created from javascript.
	Keeps v8::Persistent reference to prevent javascript from deleting the
	object while it is in use by C++. Wrap this class in shared ptr.
	*/
	template<class T>
	class PersistentV8
	{
	private:
		v8::Persistent<v8::Value> keeper;
		PersistentV8& operator=(const PersistentV8&) {}
	protected:
		T * native;
	public:
		PersistentV8(v8::Handle<v8::Value> handle) 
			: keeper(handle), native(cvv8::CastFromJS<T>(handle)) {}

		virtual ~PersistentV8() { keeper.Dispose(); native = NULL; }

		T * NativeObject() { return native; }
	};

	class PersistentKeyV8;

	class KeyV8
	{
	private:
		v8::Persistent<v8::Context> context;
		std::string working_dir;
		void LoadEnvironment();
	public:
		KeyV8(std::string working_dir);
		~KeyV8();

		static std::shared_ptr<key::PersistentKeyV8> KeyV8::New(std::string working_dir);

		void Log( std::string val ) { std::cout << val << std::endl; }
		v8::Handle<v8::Value> ExecuteFile(std::string short_filename);
		static bool ExecuteScript(v8::Handle<v8::String> script, std::string & short_filename);

		template<class T>
		void Reflect() {
			v8::HandleScope handle_scope;
			v8::Context::Scope context_scope(context);

			cvv8::ClassCreator<T> & cc(cvv8::ClassCreator<T>::Instance());

			if( cc.IsSealed() ) {
				cc.AddClassTo( cvv8::TypeName<T>::Value, context->Global() );
				return;
			}

			v8::Handle<v8::ObjectTemplate> const & proto( cc.Prototype() );
			std::vector<std::string> items;

			T::reflect(items, cc, proto, false);
			T::reflect(items, cc, proto, true);
			auto ctor = cc.CtorFunction();
			ctor->Set(JSTR("__fields"), cvv8::CastToJS(items));

			cc.AddClassTo( cvv8::TypeName<T>::Value, context->Global() );
		}

		typedef cvv8::Signature<key::KeyV8 (
			cvv8::CtorForwarder<key::KeyV8 *(std::string)>
		)> Ctors;
	};

	class PersistentKeyV8
		: public PersistentV8<KeyV8>
	{
	public:
		PersistentKeyV8(v8::Handle<v8::Value> handle) 
			: PersistentV8<KeyV8>(handle) {}

		template<class T>
		void Reflect() { this->native->Reflect<T>(); }
		void Run(std::string js_relative_file_path) 
		{ 
			this->native->ExecuteFile(js_relative_file_path);
		}
	};
}

namespace cvv8 {
    CVV8_TypeName_DECL((key::KeyV8));

    template <>
    class ClassCreator_Factory<key::KeyV8>
     : public ClassCreator_Factory_Dispatcher< key::KeyV8,
          CtorArityDispatcher<key::KeyV8::Ctors> >
    {};

    template <>
    struct JSToNative< key::KeyV8 > : JSToNative_ClassCreator< key::KeyV8 >
    {};
}