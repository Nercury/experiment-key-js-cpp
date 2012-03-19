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

    what = "json"
        
    build_dir = sys.argv[1]
    cache_dir = os.path.join(sys.argv[2], what)
    tool = sys.argv[3]
    
    if not os.path.isdir(cache_dir):
        print "Directory \"" + cache_dir + "\" does not exist. Can not build anything."
        print "See you later when you fix that."
        exit()
        
    source_dir = os.path.join(cache_dir, "svn-source")
    if not os.path.isdir(source_dir):
        print "Directory \"" + source_dir + "\" does not exist. Can not build anything."
        print "See you later when you fix that."
        exit()
    
    os.chdir(source_dir)
    
    previous_commit_file = os.path.join(cache_dir, 'built_at_commit.txt')
    latest_commit = tools.get_stdout("svn info")
    previous_latest_commit = tools.file_as_str(previous_commit_file)
    
    if previous_latest_commit == latest_commit:
        print "Libraries are up-to-date."
        exit()

    variations = tools.get_build_variations(tool)
    
    if variations == False:
        print "Can not build anything with build tool " + tool + ". I will see you later after you fix that."
        exit()
       
    lib_json_vs_project_dir = os.path.join(source_dir, "jsoncpp", "makefiles", "vs71")
    lib_json_vs_project_file = os.path.join(lib_json_vs_project_dir, "lib_json.vcproj")
    lib_json_vs_solution_file = os.path.join(lib_json_vs_project_dir, "jsoncpp.sln")
    if not os.path.isdir(lib_json_vs_project_dir) or not os.path.isfile(lib_json_vs_project_file) or not os.path.isfile(lib_json_vs_solution_file):
        print "Expected project file \"" + lib_json_vs_project_file + "\" does not exist. Maybe something has changed in lib_json project source?"
        print "See you later when you fix build process."
        exit()
        
    vs_dir = tools.get_vs11_dir()
    lib_json_vsx_project_file = os.path.join(lib_json_vs_project_dir, "lib_json.vcxproj")
    if not os.path.isfile(lib_json_vsx_project_file):
        sln_upgrade_str = r'call "' + vs_dir + r'\VC\bin\"vcvars32.bat' + "\n" + \
                    r'cd "' + lib_json_vs_project_dir + r'"' + "\n" + \
                    r'devenv ' + lib_json_vs_solution_file + r' /upgrade'
        batch_upgrade_file = os.path.join(cache_dir, "vcxupgrade.bat")
        tools.str_to_file(batch_upgrade_file, sln_upgrade_str)
        os.system(batch_upgrade_file)
        if not os.path.isfile(lib_json_vsx_project_file):
            print "Failed to upgrade \"" + lib_json_vs_solution_file + "\" solution?"
            print "See you later when you fix this."
            exit()
        
        project_file_str = tools.file_as_str(lib_json_vsx_project_file)
        # remove assembler output from project file... wtf...
        project_file_str = project_file_str.replace("<AssemblerOutput>AssemblyAndSourceCode</AssemblerOutput>", "")
        tools.str_to_file(lib_json_vsx_project_file, project_file_str)
        
        print ""
        print "Your action is required!"
        print "........................"
        print ""
        
        print "Please open \"" + lib_json_vs_solution_file + "\" solution file in Visual Studio 11 and " + \
            "create a build configuration for X64. Then press any key to continue."
        raw_input()
            
    for variation in variations:
        output_dir = tools.get_variation_build_dir(build_dir, variation)
        tools.print_variation_build_message(variation, what)
        
        if tool == "linux-g++":
            pass
        elif tool == "msvc-11":
            vs_dir = tools.get_vs11_dir()
            
            debug = variation["configuration"] == "Debug"
            
            configuration_str = "/p:configuration=release"
            if debug:
                configuration_str = "/p:configuration=debug"
            
            if variation["arch"] == 'x64':
                build_str = r'call "' + vs_dir + r'\VC\bin\amd64\"vcvars64.bat' + "\n" + \
                    r'msbuild "' + lib_json_vs_solution_file + r'" /t:clean /p:UseEnv=true ' + configuration_str + "\n" + \
                    r'msbuild "' + lib_json_vs_solution_file + r'" /p:PlatformToolset=v110 /p:UseEnv=true ' + configuration_str
            else:
                build_str = r'call "' + vs_dir + r'\VC\bin\"vcvars32.bat' + "\n" + \
                    r'msbuild "' + lib_json_vs_solution_file + r'" /t:clean /p:UseEnv=true ' + configuration_str + "\n" + \
                    r'msbuild "' + lib_json_vs_solution_file + r'" /p:PlatformToolset=v110 /p:UseEnv=true ' + configuration_str + r' /m'

            batch_build_file = os.path.join(cache_dir, "build_env_" + variation["arch"] + "_" + variation["configuration"] + ".bat")
            tools.str_to_file(batch_build_file, build_str)
            time.sleep(1)
            os.system(batch_build_file)
            
            try:
                lib_out_dir = tools.ensure_subdir(output_dir, what)
                if variation["arch"] == 'x64':
                    if debug:
                        path = os.path.join(source_dir, "jsoncpp", "makefiles", "vs71", "x64", "Debug")
                        shutil.move(os.path.join(path, "json_vc71_libmtd.lib"), os.path.join(lib_out_dir, "json_vc71.lib"))
                        shutil.move(os.path.join(path, "vc110.pdb"), os.path.join(lib_out_dir, "vc110.pdb"))
                    else:
                        path = os.path.join(source_dir, "jsoncpp", "makefiles", "vs71", "x64", "Release")
                        shutil.move(os.path.join(path, "json_vc71_libmt.lib"), os.path.join(lib_out_dir, "json_vc71.lib"))
                else:
                    if debug:
                        path = os.path.join(source_dir, "jsoncpp", "build", "vs71", "debug", "lib_json")
                        shutil.move(os.path.join(path, "json_vc71_libmtd.lib"), os.path.join(lib_out_dir, "json_vc71.lib"))
                        shutil.move(os.path.join(path, "vc110.idb"), os.path.join(lib_out_dir, "vc110.idb"))
                        shutil.move(os.path.join(path, "vc110.pdb"), os.path.join(lib_out_dir, "vc110.pdb"))
                    else:
                        path = os.path.join(source_dir, "jsoncpp", "build", "vs71", "release", "lib_json")
                        shutil.move(os.path.join(path, "json_vc71_libmt.lib"), os.path.join(lib_out_dir, "json_vc71.lib"))
            except:
                print ""
                print traceback.print_exc(file=sys.stdout)
                print ""
                print "Error while copying output library files! Will ignore that. Will continue in 8 seconds..."
                print ""
                time.sleep(8)

    tools.str_to_file(previous_commit_file, latest_commit)
    
init()