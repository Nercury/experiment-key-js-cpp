#include "BootStrapV8.h"

#include <iostream>
#include <sstream>
#include <boost/bind.hpp>
#include <key-common/app.h>

#include <cvv8/v8-convert.hpp>

namespace cv = cvv8;
using namespace v8;

namespace cvv8 {
    CVV8_TypeName_IMPL((key::BootStrapV8),"BootStrapJs");
}

static const char* ToCString(const v8::String::Utf8Value& value) {return*value ?*value : "<string conversion failed>";}

static void ReportException(v8::TryCatch* try_catch) {
	// todo: refactor to something that returns a string without printing directly to console.

	v8::HandleScope handle_scope;  
	v8::String::Utf8Value exception(try_catch->Exception());
	const char* exception_string = ToCString(exception);  
	v8::Handle<v8::Message> message = try_catch->Message();
	if (message.IsEmpty()) {
		// V8 didn't provide any extra information about this error; just// print the exception.    
		printf("%s\n\n", exception_string);  
	} else {
		// Print (filename):(line number): (message).    
		v8::String::Utf8Value filename(message->GetScriptResourceName());
		const char* filename_string = ToCString(filename);
		int linenum = message->GetLineNumber();    
		printf("%s:%i: %s\n", filename_string, linenum, exception_string);
		// Print line of source code.    
		v8::String::Utf8Value sourceline(message->GetSourceLine());
		const char* sourceline_string = ToCString(sourceline);  
		std::string sourceline_str(sourceline_string);
		printf("%s\n", sourceline_string);
		// Print wavy underline (GetUnderline is deprecated).
		int start = message->GetStartColumn();
		for (int i =0; i < start; i++) {  
			if (i < sourceline_str.size()) {
				if (sourceline_str.at(i) == '\t')
					printf("\t");
				else
					printf("");  
			} else {
				printf("");    
			}
		}
		int end = message->GetEndColumn();
		for (int i = start; i < end; i++) {   
			if (i < sourceline_str.size()) {
				if (sourceline_str.at(i) == '\t')
					printf("\t");
				else
					printf("^");  
			} else {
				printf("^");    
			}
  
		}    
		printf("\n");    
		v8::String::Utf8Value stack_trace(try_catch->StackTrace());
		if (stack_trace.length() >0) {
			const char* stack_trace_string = ToCString(stack_trace);      
			printf("%s\n", stack_trace_string);    
		}  
		printf("\n");  
	}
}

Handle<Value> key::BootStrapV8::executeFile(const Arguments& args ) {
	if (args.Length() < 1)
		return String::New("Insufficient parameters for js file execution.");
	std::string short_filename(cv::CastFromJS<std::string>(args[0]));
	std::cout << "loading " << working_dir << " -> " << short_filename << std::endl;
	std::string filename(rootDirPathTo(working_dir, short_filename));
	std::string contents;
	if (!stringFromFile(contents, filename)) {
		std::ostringstream ss;
		ss << "Javascript file \"" << short_filename << "\" was not found.";
		return String::New(ss.str().c_str());
	}

	bool result = executeScript(String::New(contents.c_str()), short_filename);
	if (result) {
		return Boolean::New(true);
	} else {
		std::ostringstream ss;
		ss << "Error executing file \"" << short_filename << "\".";
		return String::New(ss.str().c_str());
	}
}

void key::BootStrapV8::bindCoreBootstrap(Handle<Object> & dest, std::string & working_dir) {
	typedef cv::ClassCreator<BootStrapV8> CC;
    CC & cc(CC::Instance());
    if( cc.IsSealed() ) {
        cc.AddClassTo( cv::TypeName<BootStrapV8>::Value, dest );
        return;
    }
    cc
        ("textLog", cv::MethodToInCa<BootStrapV8, void (std::string),
                &BootStrapV8::log>::Call)
		("executeFile", cv::MethodToInCa<BootStrapV8, Handle<Value> (const Arguments& args),
				&BootStrapV8::executeFile>::Call)
        .AddClassTo( cv::TypeName<BootStrapV8>::Value, dest );
	
	Handle<Value> param(String::New(working_dir.c_str()));

	dest->Set(String::New("js_main"), cc.CtorFunction()->CallAsConstructor(1, &param));
}

Handle<key::BootStrapV8> key::BootStrapV8::run(std::string & working_dir, std::string short_filename) {
	std::list<std::shared_ptr<key::SubsystemBase>> empty_subsystems(0);
	return run(empty_subsystems, working_dir, short_filename);
}

Handle<key::BootStrapV8> key::BootStrapV8::run(std::list<std::shared_ptr<key::SubsystemBase>> & subsystems, std::string & working_dir, std::string short_filename) {
	std::cout << "loading " << working_dir << " -> " << short_filename << std::endl;
	std::string filename(rootDirPathTo(working_dir, short_filename));
	std::string contents;
	if (!stringFromFile(contents, filename)) {
		std::cout << "Javascript file \"" << filename << "\" was not found." << std::endl;
		return Handle<key::BootStrapV8>();
	}

	HandleScope handle_scope;
	Handle<Context> context = Context::New();
	Context::Scope context_scope(context);

	bindCoreBootstrap(context->Global(), working_dir);
	for (auto it = subsystems.begin(); it != subsystems.end(); ++it)
		(*it)->initCore(context->Global());

	bool result = executeScript(String::New(contents.c_str()), short_filename);
	if (!result)
		std::cout << std::endl;

	return Handle<key::BootStrapV8>();
}

bool key::BootStrapV8::executeScript(Handle<String> script, std::string & short_filename) {
	HandleScope handle_scope;

	TryCatch try_catch;

	Handle<Script> compiled_script = Script::New(script, String::New(short_filename.c_str()));
	if (compiled_script.IsEmpty()) {
		String::Utf8Value error(try_catch.Exception());
		ReportException(&try_catch);
		// The script failed to compile; bail out.
		return false;
	}

	// Run the script!
	Handle<Value> result = compiled_script->Run();
	if (result.IsEmpty()) {
		// The TryCatch above is still in effect and will have caught the error.
		ReportException(&try_catch);
		return false;
	}
	return true;
}