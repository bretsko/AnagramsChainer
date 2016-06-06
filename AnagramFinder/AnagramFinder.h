#pragma once

#include <map>
#include <vector>
#include <memory>
#include <string>

#include "config.h"
#include "utilities.h"

using std::string;
using std::vector;

// Example: ail + s = sail + n = nails + e = aliens
// Input: text file where each line is another word

typedef std::multimap<string, string> string_multimap_t;
typedef std::multimap<string, string> string_map_t;
typedef std::vector <string_map_t> map_vector_t;

class AnagramFinder
{
public:
    AnagramFinder(const string &word);

    bool find_longest_derivation(const string &str);
    bool find_longest_derivation_map(const string &str);

private:

    const string input_string;

    vector<string> anagram_vector;
    string_multimap_t dic_anagram_map;
    map_vector_t result_map_vector;

    bool validate_string(const string &str);

    //reads a file and extracts words into the dictionary (anagram_map)
    bool parse_file_to_vector(const string &filename);
    bool parse_file_to_map(const string &filename);

    bool anagram_compare( const string &str1, const string &str2);

    void string_to_key(string &str);

};
