#pragma once

#include <iostream>

//-----------------------------------
// My favourite debugging mechanism...
#define CERR std::cerr << __FILE__ << ":" << \
        std::dec << __LINE__ << ":" <<__FUNCTION__ << "(): "

#include <string>
#include <memory>
#include <list>

#include <key-common/types.h>

#define V8STDINT_H_ // defined in types.h
#include <v8.h>

#include <key-v8/Scripting.hpp>
#include <key-v8/lib_key_v8.h>

#include <cvv8/ClassCreator.hpp>

// Convenience namespace alias:
namespace cv = cvv8;

namespace key {
	//-----------------------------------
	// The type we want to bind to v8.
	class BootStrapV8
	{
	private:
		static void bindCoreBootstrap(v8::Handle<v8::Object> & dest);
	public:
		BootStrapV8() {
		}
		~BootStrapV8() {
		}
    
		typedef cv::Signature<BootStrapV8 (
			cv::CtorForwarder<BootStrapV8 *()>
		)> Ctors;

		void log( std::string val ) { std::cout << val << std::endl; }
		v8::Handle<v8::Value> executeFile( const v8::Arguments& args );

		static v8::Handle<BootStrapV8> run(std::list<std::shared_ptr<key::Scripting>> & subsystems, std::string short_filename);
		static v8::Handle<BootStrapV8> run(std::string short_filename);
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

/*namespace key {

	class CodeV8
	{
	private:
		std::vector<std::shared_ptr<key::Scripting>> subsystems;
		void initScope(v8::Handle<v8::ObjectTemplate> & dest);
		void initCore(v8::Handle<v8::Object> & dest);
	public:
		LIB_KEY_V8 CodeV8();
		LIB_KEY_V8 ~CodeV8();

		LIB_KEY_V8 std::string getVersion();
		LIB_KEY_V8 bool runFile(std::string & filename, std::string & short_filename);
		LIB_KEY_V8 void addScriptingSubsystem(std::shared_ptr<key::Scripting> scripting);
	};

}*/
