import os
import commands
import sys
import shutil
import imp

tools = imp.load_source('key_build_tools', os.path.abspath(os.path.join(os.path.dirname(__file__), "..", "tools.py")))

def init():
    if len(sys.argv) <= 2:
        print "Your argument is not good enough!"
        exit()
        
    include_dir = sys.argv[1]
    cache_dir = tools.ensure_subdir(sys.argv[2], "v8")
    
    if commands.getoutput("git --version")[:3] != "git":
        print "You need to install git and make it available in your environment as \"git\" command to update v8 repository."
        print "So, again, see you later :P"
        exit()
    
    source_dir = os.path.join(cache_dir, "git-source")
    source_dir_exists = os.path.isdir(source_dir)
    
    if not source_dir_exists:
        os.system("git clone git://github.com/v8/v8.git \"" + source_dir + "\"")
    else:
        os.chdir(source_dir)
        os.system("git reset --hard")
        os.system("git clean -d -x -n")
        os.system("git pull")
        
    v8_include_files = os.path.join(source_dir, "include")
    if not os.path.isdir(v8_include_files):
        print "Path \"" + v8_include_files + "\" was not found. Maybe something has changed?"
        print "In that case, see you later."
        exit()
    
    os.chdir(source_dir)
    
    previous_commit_file = os.path.join(cache_dir, 'includes_at_commit.txt')
    latest_commit = commands.getoutput("git log --no-decorate --format=oneline -n 1")
    previous_latest_commit = tools.file_as_str(previous_commit_file)
    
    if previous_latest_commit == latest_commit:
        print "Include files are up-to-date."
        exit()
    
    include_dir_v8 = os.path.join(include_dir, "v8")
    if os.path.isdir(include_dir_v8):
        shutil.rmtree(include_dir_v8)
        
    shutil.copytree(v8_include_files, include_dir_v8)
    
    tools.str_to_file(previous_commit_file, latest_commit)
    
init()