#pragma once

#include <iostream>
#include <string>
#include <memory>
#include <list>

#include <key-v8/SubsystemBase.hpp>
#include <key-v8/lib_key_v8.h>

namespace key {
	//-----------------------------------
	// The type we want to bind to v8.
	class BootStrapV8
	{
	private:
		static void bindCoreBootstrap(v8::Handle<v8::Object> & dest, std::string & working_dir);
		std::string working_dir;
	public:
		BootStrapV8(std::string working_dir) : working_dir(working_dir) {
		}
		~BootStrapV8() {
		}
    
		typedef cvv8::Signature<key::BootStrapV8 (
			cvv8::CtorForwarder<key::BootStrapV8 *(std::string)>
		)> Ctors;

		void log( std::string val ) { std::cout << val << std::endl; }
		v8::Handle<v8::Value> executeFile( const v8::Arguments& args );

		static v8::Handle<key::BootStrapV8> run(std::list<std::shared_ptr<key::SubsystemBase>> & subsystems, std::string & working_dir, std::string short_filename);
		static v8::Handle<key::BootStrapV8> run(std::string & working_dir, std::string short_filename);
		static bool executeScript(v8::Handle<v8::String> script, std::string & short_filename);
	};

}

namespace cvv8 {
    CVV8_TypeName_DECL((key::BootStrapV8));

    template <>
    class ClassCreator_Factory<key::BootStrapV8>
     : public ClassCreator_Factory_Dispatcher< key::BootStrapV8,
          CtorArityDispatcher<key::BootStrapV8::Ctors> >
    {};

    template <>
    struct JSToNative< key::BootStrapV8 > : JSToNative_ClassCreator< key::BootStrapV8 >
    {};
}