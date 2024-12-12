#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "JsonParser.h"

#include "json_object.h"
#include "json_object_iterator.h"
#include "json_tokener.h"
#include "json_util.h"

//***************************************************************//
// read json string
std::string JsonParser::read_json(const std::string &json_string, const std::string &key)
{
    json = json_tokener_parse(json_string.c_str());
    const char* value = json_object_get_string(json_object_object_get(json, key.c_str()));
    return value;
}

// write json string
std::string JsonParser::write_json(const std::string &json_string, const std::string &key, const std::string &value)
{
    json = json_tokener_parse(json_string.c_str());
    json_object_set_string(json_object_object_get(json,key.c_str()), value.c_str());
    const char* json_string_new = json_object_to_json_string(json); 
    return json_string_new;        
}

// write json to file
void JsonParser::write_json_to_file(std::string &json_string, const std::string &filename)
{
    std::ofstream file(filename);
    file << json_string;
    file.close();
}   

// read json to file
std::string JsonParser::read_json_to_file(std::ifstream &filename, const std::string &key)
{
    std::string json_string;
    getline(filename, json_string);
    json = json_tokener_parse(json_string.c_str());
    const char* value = json_object_get_string(json_object_object_get(json, key.c_str()));
    return value;
}
