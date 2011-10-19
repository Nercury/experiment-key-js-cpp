#include "KeyV8.h"

#include <boost/format.hpp>

#include <cvv8/v8-convert.hpp>
#include <key-common/app.h>
#include <key-v8/exception.h>

using namespace v8;
using namespace key;

namespace cvv8 {
    CVV8_TypeName_IMPL((key::KeyV8),"KeyV8");
}

std::shared_ptr<key::PersistentKeyV8> KeyV8::New(std::string working_dir) 
{
	HandleScope handle_scope;

	auto context = Context::New();
	Context::Scope context_scope(context);

	auto dest = context->Global();

	typedef cvv8::ClassCreator<KeyV8> CC;
    CC & cc(CC::Instance());
    if( cc.IsSealed() ) {
        cc.AddClassTo( cvv8::TypeName<KeyV8>::Value, dest );
    } else {
		cc
			("criticalMessage", cvv8::ToInCa<void, void (const std::string, const std::string),
				::critical_message>::Call)
			("terminateApp", cvv8::ToInCa<void, void (),
				::terminate_app>::Call)
			("textLog", cvv8::MethodToInCa<KeyV8, void (std::string),
					&KeyV8::Log>::Call)
			("executeFile", cvv8::MethodToInCa<KeyV8, Handle<Value> (std::string),
					&KeyV8::ExecuteFile>::Call)
			.AddClassTo( cvv8::TypeName<KeyV8>::Value, dest );
	}

	Handle<Value> param(String::New(working_dir.c_str()));
	Handle<Value> js_main = cc.CtorFunction()->CallAsConstructor(1, &param);
	dest->Set(String::New("js_main"), js_main);

	auto persistent_result = std::make_shared<key::PersistentKeyV8>(js_main);
	persistent_result->NativeObject()->context = context;
	persistent_result->NativeObject()->LoadEnvironment();
	return persistent_result;
}

KeyV8::KeyV8(std::string working_dir) : working_dir(working_dir)
{
	std::cout << "Using V8 " << V8::GetVersion() << " Javascript Engine" << std::endl;
}

bool key::KeyV8::ExecuteScript(Handle<String> script, std::string & short_filename) {
	HandleScope handle_scope;

	TryCatch try_catch;

	Handle<Script> compiled_script = Script::New(script, String::New(short_filename.c_str()));
	if (compiled_script.IsEmpty()) {
		String::Utf8Value error(try_catch.Exception());
		report_exception(&try_catch);
		// The script failed to compile; bail out.
		return false;
	}

	// Run the script!
	Handle<Value> result = compiled_script->Run();
	if (result.IsEmpty()) {
		// The TryCatch above is still in effect and will have caught the error.
		report_exception(&try_catch);
		return false;
	}

	return true;
}

Handle<Value> key::KeyV8::ExecuteFile(std::string short_filename) {
	v8::HandleScope handle_scope;
	v8::Context::Scope context_scope(context);

	std::cout << "loading " << working_dir << " -> " << short_filename << std::endl;
	std::string filename(rootDirPathTo(working_dir, short_filename));
	std::string contents;
	if (!stringFromFile(contents, filename)) {
		std::ostringstream ss;
		ss << "Javascript file \"" << short_filename << "\" was not found.";
		return String::New(ss.str().c_str());
	}

	bool result = ExecuteScript(String::New(contents.c_str()), short_filename);
	if (result) {
		return Boolean::New(true);
	} else {
		std::ostringstream ss;
		ss << "Error executing file \"" << short_filename << "\".";
		return String::New(ss.str().c_str());
	}
}

KeyV8::~KeyV8()
{
	context.Dispose();
}

void KeyV8::LoadEnvironment()
{
	v8::HandleScope scope;
	auto dest = context->Global();
	dest->Set(String::New("js_main_app_path"), String::New(getAppPath().c_str()));
	dest->Set(String::New("js_main_app_path_separator"), String::New((boost::format("%1%") % PATH_SEPARATOR).str().c_str()));
	dest->Set(String::New("js_main_log_separator"), String::New("--------------------------------------------------------------------------"));
}