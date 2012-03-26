import os
import sys
import platform
import imp
import shutil
import time
import traceback

tools = imp.load_source('key_build_tools', os.path.abspath(os.path.join(os.path.dirname(__file__), "..", "tools.py")))

def init():
    if len(sys.argv) <= 3:
        print "Your argument is not good enough!"
        exit()

    what = "v8"
        
    build_dir = sys.argv[1]
    root_cache_dir = sys.argv[2]
    cache_dir = os.path.join(root_cache_dir, what)
    tool = sys.argv[3]
    
    tools.assert_dir(cache_dir)
       
    source_dir = os.path.join(cache_dir, "git-source")
    tools.assert_dir(source_dir)    
    os.chdir(source_dir)
    
    variations = tools.get_build_variations(tool)
    
    if variations == False:
        print "Can not build anything with build tool " + tool + ". I will see you later after you fix that."
        exit()
        
    if os.system("scons --version") != 0:
        print "You need to install SCons build tool to build v8. And SCons must be available in your PATH/ENV."
        exit()
        
    latest_commit_str = tools.get_stdout("git log --no-decorate --format=oneline -n 1")
        
    for variation in variations:
        if not tools.needs_update(root_cache_dir, what, variation, latest_commit_str):
            continue
    
        output_dir = tools.get_variation_build_dir(build_dir, variation)
        tools.print_variation_build_message(variation, what)
        
        if tool == "linux-g++":
            pass
        elif tool == "msvc-11":
            vs_dir = tools.get_vs11_dir()
            
            debug = variation["configuration"] == "Debug"
            
            if variation["arch"] == 'x64':
                build_str = r'call "' + vs_dir + r'\VC\bin\amd64\"vcvars64.bat' + "\n" + \
                    r'scons env="PATH:%PATH%,INCLUDE:%INCLUDE%,LIB:%LIB%" -j4 arch=x64'
            else:
                build_str = r'call "' + vs_dir + r'\VC\bin\"vcvars32.bat' + "\n" + \
                    r'scons env="PATH:%PATH%,INCLUDE:%INCLUDE%,LIB:%LIB%"'
                
            if debug:
                build_str += " mode=debug"
            else:
                build_str += " mode=release"
            
            batch_build_file = os.path.join(root_cache_dir, "build_env_" + variation["arch"] + "_" + variation["configuration"] + ".bat")
            tools.str_to_file(batch_build_file, build_str)
            os.system(batch_build_file)
            
            lib_out_dir = tools.ensure_subdir(output_dir, what)

            if debug:
                move_files = [
                    [os.path.join(source_dir, "vc110.pdb"), os.path.join(lib_out_dir, "vc110.pdb")]
                    [os.path.join(source_dir, "vc110.idb"), os.path.join(lib_out_dir, "vc110.idb")]
                    [os.path.join(source_dir, "v8_g.lib"), os.path.join(lib_out_dir, "v8.lib")]
                    [os.path.join(source_dir, "v8preparser_g.lib"), os.path.join(lib_out_dir, "v8preparser.lib")]
                ]
                #shutil.move(os.path.join(source_dir, "vc110.pdb"), os.path.join(lib_out_dir, "vc110.pdb"))
                #shutil.move(os.path.join(source_dir, "vc110.idb"), os.path.join(lib_out_dir, "vc110.idb"))
                #shutil.move(os.path.join(source_dir, "v8_g.lib"), os.path.join(lib_out_dir, "v8.lib"))
                #shutil.move(os.path.join(source_dir, "v8preparser_g.lib"), os.path.join(lib_out_dir, "v8preparser.lib"))
            else:
                move_files = [
                    [os.path.join(source_dir, "v8.lib"), os.path.join(lib_out_dir, "v8.lib")]
                    [os.path.join(source_dir, "v8preparser.lib"), os.path.join(lib_out_dir, "v8preparser.lib")]
                ]
                #shutil.move(os.path.join(source_dir, "v8.lib"), os.path.join(lib_out_dir, "v8.lib"))
                #shutil.move(os.path.join(source_dir, "v8preparser.lib"), os.path.join(lib_out_dir, "v8preparser.lib"))
            
            result = tools.destructive_move(move_files)
            if result.ok:
                tools.log_variation_updated(root_cache_dir, what, variation)
            else:
                tools.log_update_failed(root_cache_dir, what, variation, move_result.failures)
    
init()