import platform
import subprocess
import os

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
    
def get_vs11_dir():
    # todo: return dir properly
    return "C:\\Program Files (x86)\Microsoft Visual Studio 11.0"