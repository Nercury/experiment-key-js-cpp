#include "exception.h"

static const char* ToCString(const v8::String::Utf8Value& value) {return*value ?*value : "<string conversion failed>";}

void report_exception(v8::TryCatch* try_catch) {
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