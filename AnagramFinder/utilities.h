#pragma once

#include <string>
#include <map>

using std::string;
typedef std::multimap<string, string> string_multimap;

bool validate_input(const string &str);

string parse_program_args(int argc, char *argv[]);

void print_help( char *argv[]);

//per-char comparison of strings of the same size
bool char_compare( const string &str1, const string &str2);

void print_multimap(string_multimap &mm);
