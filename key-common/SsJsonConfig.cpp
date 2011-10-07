#include "SsJsonConfig.h"

using namespace std;
using namespace v8;

#include <iostream>
#include <fstream>

#include <key-common/app.h>

#include <json/reader.h>
#include <json/writer.h>
#include <json/value.h>

key::SsJsonConfig::SsJsonConfig(std::string main_config_filename) : configuration_is_valid(false) {
	bool could_read = false;
	
	std::string & full_config_filename = fullPathTo(main_config_filename);

	if (!stringFromFile(main_configuration_contents, full_config_filename)) {
		Json::Value root;
		root["js_root_dir"] = "js";
		root["js_main_file"] = "main.js";

		Json::StyledWriter writer;
		main_configuration_contents = writer.write( root );

		ofstream out(full_config_filename, ios::out | ios::binary);
		if (!out) {
			cout << "Cannot write default config to \"" << full_config_filename << "\"." << endl;
		} else {
			out << main_configuration_contents;
			out.close();
			could_read = true;
		}
	} else {
		could_read = true;
	}

	if (could_read) {
		Json::Value root;
		Json::Reader reader;

		if (!reader.parse(main_configuration_contents, root))
		{
			cout << "could not PARSE configuration file!" << endl; 
			cout << reader.getFormatedErrorMessages() << endl;
		} 
		else 
		{
			// read config
			js_root_dir = root.get("js_root_dir", "js").asString();
			js_main_file = root.get("js_main_file", "main.js").asString();

			configuration_is_valid = true;
		}
	} else {
		std::cout << "Failed to read configuration from \"" << fullPathTo(main_config_filename) << "\"." << std::endl;
	}
}

key::SsJsonConfig::~SsJsonConfig() {

}

void key::SsJsonConfig::initCore(v8::Handle<v8::Object> & dest) {
	dest->Set(String::New("js_main_config_contents"), String::New(main_configuration_contents.c_str()));
	dest->Set(String::New("js_main_app_path"), String::New(getAppPath().c_str()));
	string s;
	s.append(1, PATH_SEPARATOR);
	dest->Set(String::New("js_main_app_path_separator"), String::New(s.c_str()));
}