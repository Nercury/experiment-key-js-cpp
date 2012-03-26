#!/usr/bin/env python

"""

This thing gets and builds <other> libraries.
Author: Nerijus Arlauskas

"""

import os
import commands
import sys
import platform
import imp

requires = {
    "v8" : {
        "update" : "v8/update_v8.py",
        "build" : "v8/build_v8.py"
    },
    "json" : {
        "update" : "json/update_json.py",
        "build" : "json/build_json.py"
    },
}

build_tool = False

tools = imp.load_source('key_build_tools', os.path.abspath(os.path.join(os.path.dirname(__file__), "tools.py")))

def init():
    dir = os.path.dirname(__file__)

    # determine build-tool
    # build tool is very simple concept here: it is an enviroinment (os)
    # and a compiler which you run in that environment
    
    # build tool can be specific compiler configuration in such environment,
    # like gnu-c++-in-old-gentoo-with-screwed-up-linux-kernel
    # just make sure to go over all build scripts and make them work
    # with that :)
    
    # determine default build tool in simpliest case
    
    global build_tool
    
    if platform.system() == "Linux":
        build_tool = 'linux-g++'
    elif platform.system() == 'Windows':
        build_tool = 'msvc-11'

    # todo: choose user-configured build tool (if you are reading this,
    # this "todo" is for you)

    if build_tool != False:
        print "Build tool is " + build_tool + "."

    # now make sure our directories to build in are available and nice

    # we will put includes here (and make sure cmake can find them here)
    include_dir = os.path.join(dir, '..', '..', 'third-party-include')
    # built libs here (and make sure cmake can find them here)
    lib_dir = os.path.join(dir, '..', '..', 'third-party-lib')
    # this will be used for downloaded third-party libs and building them
    cache_dir = os.path.join(dir, '..', '..', 'third-party-cache')

    abs_include_dir = os.path.abspath(include_dir)
    abs_lib_dir = os.path.abspath(lib_dir)
    abs_cache_dir = os.path.abspath(cache_dir)

    include_dir_exists = os.path.isdir(abs_include_dir)
    lib_dir_exists = os.path.isdir(abs_lib_dir)
    cache_dir_exists = os.path.isdir(abs_cache_dir)

    # scare the user

    if not include_dir_exists and not lib_dir_exists and not cache_dir_exists:
        print ""
        print "ATTENTION. Please read the text bellow."
        print ""
        print "Development file structure should follow this scheme:"
        print "  <root>"
        print "      /your_build_directory_X    <-- makefiles, your favourite IDE files, etc."
        print "      /project"
        print "          /source                <-- versioned source files, shared with other"
        print "                                     devs. Keep your own files out of this!"
        print "                                     This directory IS GIT ROOT for the project."
        print "          /third-party-include   <-- include files in case your system does not"
        print "                                     have them globally (i.e, windows)."
        print "          /third-party-lib       <-- compiled library files for your favourite"
        print "                                     tools."
        print "          /third-party-cache     <-- thats where third party libs get built"
        print ""
        print "Based on this scheme, "
        
    if not include_dir_exists or not lib_dir_exists or not cache_dir_exists:
        print "this tool will try to create following directories up "
        print "in the directory tree:"
        print ""
        
        if not include_dir_exists:
            print abs_include_dir
            
        if not lib_dir_exists:
            print abs_lib_dir
            
        if not cache_dir_exists:
            print abs_cache_dir
            
        if (tools.query_yes_no("Allow to do that?")):
            
            try:
                if not include_dir_exists:
                    os.makedirs(abs_include_dir)
                    
                if not lib_dir_exists:
                    os.makedirs(abs_lib_dir)
                    
                if not cache_dir_exists:
                    os.makedirs(abs_cache_dir)
            except:
                pass
                
            include_dir_exists = os.path.isdir(abs_include_dir)
            lib_dir_exists = os.path.isdir(abs_lib_dir)
            cache_dir_exists = os.path.isdir(abs_cache_dir)
                
            if not include_dir_exists or not lib_dir_exists or not cache_dir_exists:
                print "It does not look like any directories were created. Maybe you don't have permissions to create them in previously mentioned locations."
                print abort_text
                exit()
        else:
            print abort_text
            exit()
          
    # everything is good, can run scripts
    
    update(abs_include_dir, abs_lib_dir, abs_cache_dir, os.path.abspath(dir))
    
def update(abs_include_dir, abs_lib_dir, abs_cache_dir, abs_update_scripts_dir):
    
    # iterate over what is required for this project
    
    specific_items = False
    
    if len(sys.argv) > 1:
        specific_items = {}
        for i in range(1, len(sys.argv)):
            specific_items[sys.argv[i]] = True

    tools.begin_update(abs_cache_dir)      
        
    for item in requires:
        if specific_items != False:
            if not specific_items.has_key(item):
                continue
                
        info = requires[item]
        print "Processing " + item + "..."
        
        update_script = False
        if info["update"] != False:
            update_script = os.path.join(abs_update_scripts_dir, info["update"])
            
        build_script = False
        if info["build"] != False:
            build_script = os.path.join(abs_update_scripts_dir, info["build"])
            
        # download stuff and update include files
            
        if update_script != False:
            os.system("python " + update_script + " \"" + abs_include_dir + "\" \"" + abs_cache_dir + "\"")
       
        # build downloaded stuff
        
        if build_tool == False:
            print "Skip building " + item + " because build tool was not determined for you platform."
        else:
            if build_script != False:
                os.system("python " + build_script + " \"" + abs_lib_dir + "\" \"" + abs_cache_dir + "\" " + build_tool)

    tools.end_update_and_print_stats(abs_cache_dir)
       
abort_text = "In that case, see you later.";
    
init()