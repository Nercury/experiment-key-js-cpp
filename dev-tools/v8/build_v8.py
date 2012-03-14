import os
import commands
import sys
import platform
import imp

tools = imp.load_source('key_build_tools', os.path.abspath(os.path.join(os.path.dirname(__file__), "..", "tools.py")))

def init():
    if len(sys.argv) <= 3:
        print "Your argument is not good enough!"
        exit()

    build_dir = sys.argv[1]
    cache_dir = os.path.join(sys.argv[2], "v8")
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
    latest_commit = commands.getoutput("git log --no-decorate --format=oneline -n 1")
    previous_latest_commit = tools.file_as_str(previous_commit_file)
    
    if previous_latest_commit == latest_commit:
        print "Libraries are up-to-date."
        exit()

    variations = tools.get_build_variations(tool)
    
    if variations == False:
        print "Can not build anything with build tool " + tool + ". I will see you later after you fix that."
        exit()
        
    for variation in variations:
        print(variation)
    
    exit()
    
    tools.str_to_file(previous_commit_file, latest_commit)
    
init()