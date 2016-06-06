#pragma once

#include <string>
#include <map>
#include <vector>

using std::string;
typedef std::multimap<string, string> string_multimap_t;
typedef std::vector <string_multimap_t> map_vector_t;

bool validate_input(const string &str);

string parse_program_args(int argc, char *argv[]);

void print_help( char *argv[]);

void print_multimap(string_multimap_t &mm);

void print_map_vector(map_vector_t &mv);







