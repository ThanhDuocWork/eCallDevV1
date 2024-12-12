#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"

class JsonParser
{
public:
    JsonParser() {}
    ~JsonParser() {}
    std::string read_json(const std::string &json_string, const std::string &key);
    std::string write_json(const std::string &json_string, const std::string &key, const std::string &value);
    void write_json_to_file(std::string &json_string, const std::string &filename);
    std::string read_json_to_file(std::ifstream &filename, const std::string &key);

private:
    struct json_object *json;
};