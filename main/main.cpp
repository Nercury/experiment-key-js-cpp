#include <memory>
#include <iostream>
#include <list>

#include <key-common/app.h>
#include <key-v8/BootStrapV8.h>

#include <key-window/SsWindow.hpp>
#include <key-common/SsJsonConfig.h>

#include <json/reader.h>
#include <json/value.h>

//#include <boost/thread.hpp>


//#include <memory>
//#include <vector>

/*#include <btBulletDynamicsCommon.h>
#include <LinearMath/btHashMap.h>
#include <LinearMath/btAlignedObjectArray.h>

#include <AL/alc.h>
#include <AL/al.h>
#include <AL/alext.h>*/

using namespace std;
using namespace key;

int main(int argc, char* argv[])
{
	setAppPath(*argv);

	list<shared_ptr<SubsystemBase>> subsystems;

	auto ss_json_config = make_shared<SsJsonConfig>("config.js");
	subsystems.push_back(ss_json_config);

	auto ss_window = make_shared<SsWindow>();
	subsystems.push_back(ss_window);

	std::string js_dir(joinPath(getAppPath(), ss_json_config->js_root_dir));

	BootStrapV8::run(subsystems, js_dir, ss_json_config->js_main_file);

	//cout << "Using V8 " << v8_engine->getVersion() << " Javascript Engine" << endl;

	//string main_file = "js/engine/main.js";

	//v8_engine->addScriptingSubsystem(v8_engine);

	/*if (!v8_engine->runFile(fullPathTo(main_file), main_file)) {
		cout << "Failed to run " << main_file << endl;
	} else {
		cout << "Done." << endl;
	}*/

	/*btAlignedObjectArray<btCollisionShape*>	m_collisionShapes;

	std::ostringstream ss;
	cout << "Using V8 " << v8::V8::GetVersion() << " Javascript Engine" << endl;
	cout << "Using Bullet Physics Engine" << endl;
	
	ALCdevice *device;
    ALCcontext *context;
	device = alcOpenDevice(NULL);
    if(!device)
    {
        printf("\n!!! Failed to open %s !!!\n\n", ((argc>1) ? argv[1] : "default device"));
        return 1;
    }
	context = alcCreateContext(device, NULL);
	if(!context || alcMakeContextCurrent(context) == ALC_FALSE)
    {
        if(context)
            alcDestroyContext(context);
        alcCloseDevice(device);
        printf("\n!!! Failed to set a context !!!\n\n");
        return 1;
    }

	const ALchar* version_char = alGetString(AL_VERSION);

	string version(version_char);
	cout << "Using OpenAL " << version << " Audio" << endl;

	alcMakeContextCurrent(NULL);
    alcDestroyContext(context);
    alcCloseDevice(device);*/

#ifdef WIN32
	system("PAUSE");
#endif

	return 0;
}
