import os
import sys
import shutil
import imp

tools = imp.load_source('key_build_tools', os.path.abspath(os.path.join(os.path.dirname(__file__), "..", "tools.py")))

def init():
    if len(sys.argv) <= 2:
        print "Your argument is not good enough!"
        exit()
    
    what = "json"
    
    include_dir = sys.argv[1]
    root_cache_dir = sys.argv[2]
    cache_dir = tools.ensure_subdir(root_cache_dir, what)
    
    if tools.get_stdout("svn --version")[:3] != "svn":
        print "You need to install subversion and make it available in your environment as \"svn\" command to update " + what + " repository."
        print "So, again, see you later :P"
        exit()
    
    source_dir = os.path.join(cache_dir, "svn-source")
    source_dir_exists = os.path.isdir(source_dir)
    
    if not source_dir_exists:
        os.system("svn co https://jsoncpp.svn.sourceforge.net/svnroot/jsoncpp/trunk \"" + source_dir + "\"")
    else:
        os.chdir(source_dir)
        os.system("svn cleanup")
        os.system("svn update")
        
    upstream_include_files = os.path.join(source_dir, "jsoncpp", "include", "json")
    tools.assert_dir(upstream_include_files, "Path \"" + upstream_include_files + "\" was not found. Maybe something has changed?")
    
    os.chdir(source_dir)
    
    previous_commit_file = os.path.join(cache_dir, 'includes_at_commit.txt')
    latest_commit = tools.get_stdout("svn info")
    previous_latest_commit = tools.file_as_str(previous_commit_file)
    
    if previous_latest_commit == latest_commit:
        print "Include files are up-to-date."
        exit()
    
    include_dir_what = os.path.join(include_dir, what)
    if os.path.isdir(include_dir_what):
        shutil.rmtree(include_dir_what)
        
    shutil.copytree(upstream_include_files, include_dir_what)
    
    tools.str_to_file(previous_commit_file, latest_commit)
    
init()