#include "app.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

char * app_path = NULL;

void setAppPath(char p[])
{
	app_path = &p[0];
}

string getAppPath()
{
	if (app_path == NULL)
		return "";
	string s(app_path);
	if (s.find(PATH_SEPARATOR) != string::npos)
	{
		return s.substr(0, s.rfind(PATH_SEPARATOR));
	}
	else
	{
		return "";
	}
	return string(app_path);
}

string joinPath(const string& root, const string& file)
{
	if (root.size() == 0)
		return file;
	if (file.size() == 0)
		return root;
	if (root[root.size() - 1] == PATH_SEPARATOR)
	{
		if (file[0] == PATH_SEPARATOR)
			return root + file.substr(1, file.size() - 1);
		else
			return root + file;
	}
	else
	{
		if (file[0] == PATH_SEPARATOR)
			return root + file;
		else
			return root + PATH_SEPARATOR + file;
	}
}

void search_and_replace(std::string& value, std::string const& search,std::string const& replace)
{
    std::string::size_type  next;

    for(next = value.find(search);        // Try and find the first match
        next != std::string::npos;        // next is npos if nothing was found
        next = value.find(search,next)    // search for the next match starting after
                                          // the last match that was found.
       )
    {
        // Inside the loop. So we found a match.
        value.replace(next,search.length(),replace);   // Do the replacement.
        next += replace.length();                      // Move to just after the replace
                                                       // This is the point were we start
                                                       // the next search from. 
    }
}

string fullPathTo(const string& file)
{
	string p = getAppPath();
	if (p == "")
		return file;
#if PATH_SEPARATOR == '\\'
	string winfile = file;
	search_and_replace(winfile, "/", "\\");
	return joinPath(p, winfile);
#else
	return joinPath(p, file);
#endif
}

bool stringFromFile(std::string & output, const string& filename) {
	ifstream ifs(filename);
	if (!ifs)
		return false;

	ifs.seekg(0, std::ios::end);
	output.reserve(ifs.tellg());
	ifs.seekg(0, std::ios::beg);

	output.assign((std::istreambuf_iterator<char>(ifs)),
				std::istreambuf_iterator<char>());

	return true;
}