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


//--------------------------ALGORITHM----------------------------
/*

Input: given a word of length n

Task: construct a sorted string

The first solution is based on an accumulating vector, which takes the first anagram it finds in the dictionary and continues immediately to the next step (length + 1).

1) Parse the input file to a string vector

2) Add the input string to the vector, which will store the resulting string list.

3) First iteration: find strings in the vector of length equall to the length of input string + 1

4) Compare each string's set of characters. If it differs exactly by one character add the string (an anagram) to the resulting vector.

5) Next iteration: increase the length by one and filter out the strings by this value. Again repreat the procedure as in step 4.

6) Continue until the strings filtered out by size do not contain any anagrams.


The second solution is based on an accumulating multimap, which finds all the anagrams in the given size range and stores them under unique keys. The keys are strings with unique sets of characters, sorted alphabatically. This constitutes an effective rule to sort out the anagrams in separate buckets.

*/


//----------------------LIMITATIONS-------------------------
/*

Currently only ASCII alphanumeric values are supported.

*/


//Note: it's possible to construct several solutions using multimap
typedef std::multimap<string, string> string_multimap;

class AnagramFinder
{
public:
    AnagramFinder(const string &word);

    //main user function
    bool find_longest_derivation(const string &str);

    //TODO: refactor into separate class
    bool find_longest_derivation_map(const string &str);
private:

    const size_t input_word_length;

    vector<string> anagram_vector;

    bool validate_string(const string &str);

    //reads a file and extracts words into the dictionary (anagram_map)
    bool parse_file(const string &filename);

    bool anagram_compare( const string &str1, const string &str2);

    //------------------------------------IN PROGRESS----------------------------

    string_multimap anagram_map;

    string_multimap anagram_result_map;

    string *find_map_key( const string &str);

    bool find_map_value_for_key( const string &key);

    void string_to_key(string &str);

    //TODO: combine parse_file into one function, add options to getopt to differentiate
    bool parse_file_map(const string &filename);
};
