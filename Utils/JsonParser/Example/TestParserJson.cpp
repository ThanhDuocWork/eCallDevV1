#include"../Inc/JsonParser.h"
#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

int main()
{
  
  string json_string = "{ \"name\": \"Nguyen\", \"age\": 24 }"; 
  JsonParser json_parse;
  
  // ifstream file("/home/dangmh/json-c/tests/json_file.json");
  // string name_to_file = json_parse.read_json_to_file(file, "name");
  // cout << name_to_file << endl;
  // string age_to_file = json_parse.read_json_to_file(file, "age");
  // cout << age_to_file << endl;

  string name = json_parse.read_json(json_string, "name");
  string age = json_parse.read_json(json_string, "age");
  cout << name << endl;
  cout << age <<endl;

  string name_json_string = json_parse.write_json(json_string, "name", "Binh");
  cout << name_json_string << endl;
  json_parse.write_json_to_file(name_json_string,"json_parse.json");

	return 0;
}