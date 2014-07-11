import platform
import subprocess
import os
import sys
import shutil
import pickle
import pprint
from datetime import datetime

def get_build_variations(tool):
    tool_platforms = {
        "linux-g++" : ["linux"],
        "msvc-11" : ["windows"],
    };

    tool_compilers = {
        "linux-g++" : ["gcc"],
        "msvc-11" : ["vc110"],
    };

    tool_configurations = {
        "linux-g++" : False, # False means no subdir for configuration
        "msvc-11" : ["Debug", "Release"],
    };

    tool_architectures = {};
   
    current_architecture = platform.architecture()[0]
    if tool == 'linux-g++':
        arch_name = False
        if current_architecture == '32bit':
            arch_name = 'x86'
        elif current_architecture == '64bit':
            arch_name = 'x64'
        if arch_name != False:
            tool_architectures[tool] = [arch_name]
        else:
            tool_architectures[tool] = []
    elif tool == 'msvc-11':
        tool_architectures[tool] = ["x86", "x64"]
    
    can_build = 4
    
    if not tool_architectures.has_key(tool) or len(tool_architectures[tool]) == 0:
        print "Tool %s has no architectures to build for..." % tool
        can_build -= 1
    
    if not tool_platforms.has_key(tool) or len(tool_platforms[tool]) == 0:
        print "Tool %s has no platforms to build for..." % tool
        can_build -= 1
        
    if not tool_compilers.has_key(tool) or len(tool_compilers[tool]) == 0:
        print "Tool %s has no compilers to build on..." % tool
        can_build -= 1
        
    if not tool_configurations.has_key(tool) or tool_configurations[tool] != False and len(tool_configurations[tool]) == 0:
        print "Tool %s has no build configurations..." % tool
        can_build -= 1
    
    if can_build == 0:
        print "Tool %s has no friends and no life." % tool
        
    if can_build < 4:
        return False
    
    variations = []
    
    for arch in tool_architectures[tool]:
        for tool_platform in tool_platforms[tool]:
            for compiler in tool_compilers[tool]:
                if tool_configurations[tool] == False:
                    variations.append({
                        'arch' : arch,
                        'platform' : tool_platform,
                        'compiler' : compiler,
                        'configuration' : False,
                    })
                else:
                    for configuration in tool_configurations[tool]:
                            variations.append({
                            'arch' : arch,
                            'platform' : tool_platform,
                            'compiler' : compiler,
                            'configuration' : configuration,
                        })
                        
    return variations

def str_to_file(file, str):
    try:
        f = open(file, 'w')
        f.write(str)
        f.close()
    except:
        print "Failed to write to file \"" + previous_commit_file + "\". Make sure you fix this."
    
def file_as_str(file):
    try:
        f = open(file, 'r')
        str = f.read()
        f.close()
        return str
    except:
        return False
        
def ensure_subdir(root, subdir):
    dir = os.path.join(root, subdir)
    dir_exists = os.path.isdir(dir)
    if not dir_exists:
        try:
            os.makedirs(dir)
        except:
            pass
            
        dir_exists = os.path.isdir(dir)
        
        if not dir_exists:
            print "Failed to create directory at " + dir + ". Make sure you have right permissions to do that."
            print "See you later."
            exit()
    
    return dir  
	
def get_stdout(line):
	pipe = subprocess.Popen(line, stdout=subprocess.PIPE, stderr=subprocess.PIPE, shell=True)
	return pipe.stdout.read()
	
def get_variation_build_dir(root_build_dir, variation):
	path = root_build_dir
	if variation.has_key("platform") and variation["platform"] != False:
		path = os.path.join(path, variation["platform"])
	compiler = False
	if variation.has_key("arch") and variation["arch"] != False:
		compiler = variation["arch"]
	if variation.has_key("compiler") and variation["compiler"] != False:
		if compiler == False:
			compiler = variation["compiler"]
		else:
			compiler += "-" + variation["compiler"]
	if compiler != False:
		path = os.path.join(path, compiler)
	if variation.has_key("configuration") and variation["configuration"] != False:
		path = os.path.join(path, variation["configuration"])
	return path
    
def print_variation_build_message(variation, what):
    print ""
    message = "Building " + what + " on " + variation["platform"] + " with " + variation["arch"] + "-" + variation["compiler"] + " compiler"
    if variation.has_key("configuration") and variation["configuration"] != False:
        message += " in " + variation["configuration"] + " mode"
    print message
    print "..." * 25
    print ""
   
def begin_update(root_cache_dir):
    update_dir = ensure_subdir(root_cache_dir, "_stats")
    assert_dir(update_dir, "Could not create directory \"" + update_dir + "\" for tracking update process.")
    print "Begin update..."
   
def end_update_and_print_stats(root_cache_dir):
    print "Finished."
   
def get_status_file_name(root_cache_dir, what):
    return os.path.join(root_cache_dir, "_stats", 'st_' + what + '.txt')
    
def get_variation_id(variation):
    if isinstance(variation, str):
        return 'v-' + variation
    else:
        stri = 'v'
        if variation.has_key("platform") and variation["platform"] != False:
            stri += "-" + variation["platform"]
        if variation.has_key("arch") and variation["arch"] != False:
            stri += "-" + variation["arch"]
        if variation.has_key("compiler") and variation["compiler"] != False:
            stri += "-" + variation["compiler"]
        if variation.has_key("configuration") and variation["configuration"] != False:
            stri += "-" + variation["configuration"]
        return stri

def read_stat(file):
    if os.path.isfile(file):
        pkl_file = open(file, 'rb')
        data = pickle.load(pkl_file)
        return data
    return {}
    
def save_stat(file, stat):
    pkl_file = open(file, 'wb')
    pickle.dump(stat, pkl_file, -1)
        
def needs_update(root_cache_dir, what, variation, latest_commit_str):
    stat_file = get_status_file_name(root_cache_dir, what)
    stat = read_stat(stat_file)
    var_id = get_variation_id(variation)
    if not stat.has_key(var_id):
        var_data = {}
    else:
        var_data = stat[var_id]

    result = False
        
    var_data['last_check_time'] = datetime.now()
        
    if not var_data.has_key("latest_commit_str") or latest_commit_str != var_data['latest_commit_str']:
        result = True
        var_data['latest_commit_str'] = latest_commit_str
        var_data['update_running'] = True
        
        var_data['last_start_time'] = datetime.now()
        var_data['result'] = None
        var_data['result_failures'] = None
    else:
        var_data['result'] = 'up-to-date'
        
    stat[var_id] = var_data
    save_stat(stat_file, stat)
    exit()
    return result

def log_variation_updated(root_cache_dir, what, variation):
    pass
    
def log_update_failed(root_cache_dir, what, variation, failures):
    pass
    
def destructive_move(files):
    return { ok : False, failures : [] }
    
def assert_dir(dir, message = None):
    if not os.path.isdir(dir):
        if message != None:
            print message
        else:
            print "Directory \"" + dir + "\" does not exist. Can not continue."
        print "See you later when you fix that."
        exit()
    
def query_yes_no(question, default="yes"):
    """Ask a yes/no question via raw_input() and return their answer.

    "question" is a string that is presented to the user.
    "default" is the presumed answer if the user just hits <Enter>.
        It must be "yes" (the default), "no" or None (meaning
        an answer is required of the user).

    The "answer" return value is one of "yes" or "no".
    """
    valid = {"yes":True,   "y":True,  "ye":True,
             "no":False,     "n":False}
    if default == None:
        prompt = " [y/n] "
    elif default == "yes":
        prompt = " [Y/n] "
    elif default == "no":
        prompt = " [y/N] "
    else:
        raise ValueError("invalid default answer: '%s'" % default)

    while True:
        sys.stdout.write(question + prompt)
        choice = raw_input().lower()
        if default is not None and choice == '':
            return valid[default]
        elif choice in valid:
            return valid[choice]
        else:
            sys.stdout.write("Please respond with 'yes' or 'no' "\
                             "(or 'y' or 'n').\n")
    
def get_vs11_dir():
    # todo: return dir properly
    return "C:\\Program Files (x86)\Microsoft Visual Studio 11.0"