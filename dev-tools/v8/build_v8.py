import os
import sys
import platform
import imp
import shutil

tools = imp.load_source('key_build_tools', os.path.abspath(os.path.join(os.path.dirname(__file__), "..", "tools.py")))

def init():
    if len(sys.argv) <= 3:
        print "Your argument is not good enough!"
        exit()

    what = "v8"
        
    build_dir = sys.argv[1]
    cache_dir = os.path.join(sys.argv[2], what)
    tool = sys.argv[3]
    
    if not os.path.isdir(cache_dir):
        print "Directory \"" + cache_dir + "\" does not exist. Can not build anything."
        print "See you later when you fix that."
        exit()
        
    source_dir = os.path.join(cache_dir, "git-source")
    if not os.path.isdir(source_dir):
        print "Directory \"" + source_dir + "\" does not exist. Can not build anything."
        print "See you later when you fix that."
        exit()    
    
    os.chdir(source_dir)
    
    previous_commit_file = os.path.join(cache_dir, 'built_at_commit.txt')
    latest_commit = tools.get_stdout("git log --no-decorate --format=oneline -n 1")
    previous_latest_commit = tools.file_as_str(previous_commit_file)
    
    if previous_latest_commit == latest_commit:
        print "Libraries are up-to-date."
        exit()

    variations = tools.get_build_variations(tool)
    
    if variations == False:
        print "Can not build anything with build tool " + tool + ". I will see you later after you fix that."
        exit()
        
    if os.system("scons --version") != 0:
        print "You need to install SCons build tool to build v8. And SCons must be available in your PATH/ENV."
        exit()
        
    for variation in variations:
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
            
            batch_build_file = os.path.join(cache_dir, "build_env_" + variation["arch"] + "_" + variation["configuration"] + ".bat")
            tools.str_to_file(batch_build_file, build_str)
            os.system(batch_build_file)
            
            lib_out_dir = tools.ensure_subdir(output_dir, what)
            if debug:
                shutil.move(os.path.join(source_dir, "vc110.pdb"), os.path.join(lib_out_dir, "vc110.pdb"))
                shutil.move(os.path.join(source_dir, "vc110.idb"), os.path.join(lib_out_dir, "vc110.idb"))
                shutil.move(os.path.join(source_dir, "v8_g.lib"), os.path.join(lib_out_dir, "v8.lib"))
                shutil.move(os.path.join(source_dir, "v8preparser_g.lib"), os.path.join(lib_out_dir, "v8preparser.lib"))
            else:
                shutil.move(os.path.join(source_dir, "v8.lib"), os.path.join(lib_out_dir, "v8.lib"))
                shutil.move(os.path.join(source_dir, "v8preparser.lib"), os.path.join(lib_out_dir, "v8preparser.lib"))
    
    tools.str_to_file(previous_commit_file, latest_commit)
    
init()