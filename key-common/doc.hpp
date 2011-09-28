#pragma once

#include <boost/assign/std/vector.hpp>

using namespace boost::assign;

#define DOC_PROPERTIES(PROP_ITEMS) std::vector<std::string> & getProperties() { \
	std::vector<std::string> items; \
	items += PROP_ITEMS; \
	return items; \
};

#define DOC_TEXT(FIELD_NAME, TEXT) std::string & get ## FIELD_NAME ## () { \
	return std::string(TEXT); \
};