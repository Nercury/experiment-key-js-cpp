#pragma once

#include <string>
#include <map>

#include <key-v8/expose_headers.hpp>
#include <cvv8/properties.hpp>

#define FLECT_PROP_ND(class_definition, property_name, cpp_type) \
		proto->SetAccessor(JSTR(#property_name), \
			cvv8::MemberToGetter< ## class_definition ## , cpp_type,& ## class_definition ## :: ## property_name ## >::Get, \
			cvv8::MemberToSetter< ## class_definition ## , cpp_type, & ## class_definition ## :: ## property_name ## >::Set \
		);

#define FLECT_GS_ND(class_definition, property_name, get_accessor, get_definition, get_field, set_accessor, set_definition, set_field) \
		proto->SetAccessor(JSTR(#property_name), \
			cvv8:: ## get_accessor ## ToGetter< ## class_definition ## , ## get_definition ##,& ## class_definition ## :: ## get_field ## >::Get, \
			cvv8:: ## set_accessor ## ToSetter< ## class_definition ## , ## set_definition ##, & ## class_definition ## :: ## set_field ## >::Set \
		); \

#define FLECT_G_ND(class_definition, property_name, get_accessor, get_definition, get_field) \
		proto->SetAccessor(JSTR(#property_name), \
			cvv8:: ## get_accessor ## ToGetter< ## class_definition ## , ## get_definition ##,& ## class_definition ## :: ## get_field ## >::Get \
		);

#define FLECT_ST_GS_ND(class_definition, property_name, get_definition, get_field, set_definition, set_field) \
		cc.CtorFunction()->SetAccessor(JSTR(#property_name), \
			cvv8::FunctionToGetter< get_definition , & ## class_definition ## :: ## get_field ## >::Get, \
			cvv8::FunctionToSetter< set_definition , & ## class_definition ## :: ## set_field ## >::Set \
		); \

#define FLECT_ST_G_ND(class_definition, property_name, get_definition, get_field) \
		cc.CtorFunction()->SetAccessor(JSTR(#property_name), \
			cvv8::FunctionToGetter< get_definition, & ## class_definition ## :: ## get_field ## >::Get \
		);

/** define getter and setter for class */
#define FLECT_GS(class_definition, property_name, get_accessor, get_definition, get_field, set_accessor, set_definition, set_field, doc_type_name, doc_text) \
	static void __reflect_ ## property_name ## (cvv8::ClassCreator<class_definition> & cc, v8::Handle<v8::ObjectTemplate> proto, bool for_static) { \
		if (!for_static) { FLECT_GS_ND(class_definition, property_name, get_accessor, get_definition, get_field, set_accessor, set_definition, set_field) } \
		if (for_static) { \
			cc.CtorFunction()->SetAccessor(JSTR(#property_name), \
				cvv8::FunctionToGetter< std::map<std::string,std::string> (), & ## class_definition ## :: ## __get_ ## property_name ## _reflection ## >::Get \
			); \
		} \
	} \
	static std::map<std::string,std::string> __get_ ## property_name ## _reflection() { \
		std::map<std::string, std::string> info; \
		info.insert(std::pair<std::string, std::string>("field", "property")); \
		info.insert(std::pair<std::string, std::string>("type", doc_type_name)); \
		info.insert(std::pair<std::string, std::string>("doc", doc_text)); \
		info.insert(std::pair<std::string, std::string>("read_only", "0")); \
		return info; \
	}

/** define getter only for class */
#define FLECT_G(class_definition, property_name, get_accessor, get_definition, get_field, doc_type_name, doc_text) \
	static void __reflect_ ## property_name ## (cvv8::ClassCreator<class_definition> & cc, v8::Handle<v8::ObjectTemplate> proto, bool for_static) { \
		if (!for_static) { FLECT_G_ND(class_definition, property_name, get_accessor, get_definition, get_field) } \
		if (for_static) { \
			cc.CtorFunction()->SetAccessor(JSTR(#property_name), \
				cvv8::FunctionToGetter< std::map<std::string,std::string> (), & ## class_definition ## :: ## __get_ ## property_name ## _reflection ## >::Get \
			); \
		} \
	} \
	static std::map<std::string,std::string> __get_ ## property_name ## _reflection() { \
		std::map<std::string, std::string> info; \
		info.insert(std::pair<std::string, std::string>("field", "property")); \
		info.insert(std::pair<std::string, std::string>("type", doc_type_name)); \
		info.insert(std::pair<std::string, std::string>("doc", doc_text)); \
		info.insert(std::pair<std::string, std::string>("read_only", "1")); \
		return info; \
	}

/** define field for class (automatic property) */
#define FLECT_PROP(class_definition, property_name, cpp_type, doc_type_name, doc_text) \
	static void __reflect_ ## property_name ## (cvv8::ClassCreator<class_definition> & cc, v8::Handle<v8::ObjectTemplate> proto, bool for_static) { \
		if (!for_static) { FLECT_PROP_ND(class_definition, property_name, cpp_type) } \
		if (for_static) { \
			cc.CtorFunction()->SetAccessor(JSTR(#property_name), \
				cvv8::FunctionToGetter< std::map<std::string,std::string> (), & ## class_definition ## :: ## __get_ ## property_name ## _reflection ## >::Get \
			); \
		} \
	} \
	static std::map<std::string,std::string> __get_ ## property_name ## _reflection() { \
		std::map<std::string, std::string> info; \
		info.insert(std::pair<std::string, std::string>("field", "property")); \
		info.insert(std::pair<std::string, std::string>("type", doc_type_name)); \
		info.insert(std::pair<std::string, std::string>("doc", doc_text)); \
		info.insert(std::pair<std::string, std::string>("read_only", "0")); \
		return info; \
	}

#define FLECT_M(class_definition, method_name, method_definition, return_type_name, parameters_text, doc_text) \
	static void __reflect_ ## method_name ## (cvv8::ClassCreator<class_definition> & cc, v8::Handle<v8::ObjectTemplate> proto, bool for_static) { \
		if (!for_static) { \
			cc(#method_name, cvv8::MethodToInCa<class_definition, method_definition, & ## class_definition ## :: ## method_name ## >::Call); \
		} \
		if (for_static) { \
			cc.CtorFunction()->SetAccessor(JSTR(#method_name), \
				cvv8::FunctionToGetter< std::map<std::string,std::string> (), & ## class_definition ## :: ## __get_ ## method_name ## _reflection ## >::Get \
			); \
		} \
	} \
	static std::map<std::string,std::string> __get_ ## method_name ## _reflection() { \
		std::map<std::string, std::string> info; \
		info.insert(std::pair<std::string, std::string>("field", "method")); \
		info.insert(std::pair<std::string, std::string>("return_type", return_type_name)); \
		info.insert(std::pair<std::string, std::string>("doc", doc_text)); \
		info.insert(std::pair<std::string, std::string>("parameters", parameters_text)); \
		return info; \
	}

#define REFLECT(name) __reflect_ ## name(cc, proto, for_static); \
	if (for_static) items.push_back(#name);