#pragma once

#include <memory>

#include <key-v8/lib_key_v8.h>
#include <key-v8/expose_headers.hpp>
#include <key-v8/PersistentV8.h>

#include <cvv8/arguments.hpp>

namespace key
{
	class PersistentKeyV8;

	/**
	Main V8Helper used to expose Classes to Js
	*/
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

		/**
		Execute string script: filename is just for info in exception to know what crashed if something crashes
		*/
		static bool ExecuteScript(v8::Handle<v8::String> script, std::string & short_filename);

		/**
		Forgot what this does
		*/
		template<class T>
		static void NewObjectRef(key::PersistentV8<T> & persistentRef, v8::Handle<v8::Context> context, int argc, v8::Handle<v8::Value> * argv)
		{
			v8::HandleScope handle_scope;

			auto & cc = KeyV8::Class<T>();
			auto value = cc.CtorFunction()->CallAsConstructor(argc, argv);

			persistentRef.Assign(value, true);
		}

		/**
		Get shared_ptr for V8 object
		*/
		template<class T>
		static std::shared_ptr<key::PersistentV8<T>> NewSharedObject(v8::Handle<v8::Context> context, int argc, v8::Handle<v8::Value> * argv)
		{
			v8::HandleScope handle_scope;

			auto & cc = KeyV8::Class<T>();
			auto value = cc.CtorFunction()->CallAsConstructor(argc, argv);

			return std::make_shared<key::PersistentV8<T>>(value);
		}

		template<class T>
		static cvv8::ClassCreator<T> & Class() {
			cvv8::ClassCreator<T> & cc(cvv8::ClassCreator<T>::Instance());

			if( cc.IsSealed() ) // if this class is already created, just return it
				return cc;

			v8::Handle<v8::ObjectTemplate> const & proto( cc.Prototype() );
			std::vector<std::string> items;

			// since we can't register new object methods once our object is sealed, we have to separate this process into two steps:
			// first, register non-static stuff, and then static stuff on function prototype
			T::reflect(items, cc, proto, false); // register non-static object stuff
			T::reflect(items, cc, proto, true); // register static stuff (usually reflection helpers) so prototype can be inspected

			auto ctor = cc.CtorFunction();
			ctor->Set(JSTR("__fields"), cvv8::CastToJS(items)); // define magic "__fields" property to list all fields on prototype

			return cc;
		}

		/**
		Get a namespace to define class object into. This basically creates nested function prototypes in javascript.
		*/
		template<class T>
		v8::Handle<v8::Function> GetNamespaceFunction(v8::Handle<v8::Object> parent, std::string jsNamespace) {
			v8::HandleScope handle_scope;
			v8::Context::Scope context_scope(context);

			std::string::size_type dotIndex = jsNamespace.rfind( ".", jsNamespace.size() );
			if (dotIndex != std::string::npos) {
				std::string parentNamespace = jsNamespace.substr(0, dotIndex);
				jsNamespace.erase(0, dotIndex + 1);
				parent = GetNamespaceFunction<T>(parent, parentNamespace); // recursion!
			}

			auto fun = parent->Get(JSTR(jsNamespace.c_str())).As<v8::Function>();
			if (fun->IsUndefined()) {
				auto functionTemplate = v8::FunctionTemplate::New();
				functionTemplate->SetClassName(v8::String::NewSymbol(jsNamespace.c_str()));
				fun = functionTemplate->GetFunction();
				parent->Set(JSTR(jsNamespace.c_str()), fun.As<v8::Object>());
			}

			return handle_scope.Close(fun);
		}

		/**
		Reflect a class. Class must have a "reflect" method defined and bunch of other not yet documented stuff.
		*/
		template<class T>
		void Reflect(std::string jsNamespace) {
			v8::HandleScope handle_scope;
			v8::Context::Scope context_scope(context);

			auto namespaceFun = GetNamespaceFunction<T>(context->Global(), jsNamespace);

			auto cc = KeyV8::Class<T>();
			cc.AddClassTo( cvv8::TypeName<T>::Value, namespaceFun );
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
		void Reflect(std::string jsNamespace) { this->native->Reflect<T>(jsNamespace); }
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