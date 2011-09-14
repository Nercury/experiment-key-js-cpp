#pragma once

#include <string>

#include <key-common/app.h>
#include <key-v8/SubsystemBase.hpp>

namespace key {

	class SsJsonConfig
		: public key::SubsystemBase
	{
	private:
		std::string main_configuration_contents;
		bool configuration_is_valid;
	public:
		SsJsonConfig(std::string main_config_filename);
		virtual ~SsJsonConfig();
		virtual void initCore(v8::Handle<v8::Object> & dest);

		std::string js_root_dir;
		std::string js_main_file;
	};

}