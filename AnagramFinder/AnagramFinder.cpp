#include "AnagramFinder.h"

#include <algorithm>  // for transform, sort
#include <cctype>     // for isalpha, tolower
#include <iostream>   // for operator<<, basic_ostream, endl, ostream, cout
#include <iterator>   // for distance
#include <map>        // for _Rb_tree_iterator, multimap<>::iterator
#include <memory>     // for allocator
#include <utility>    // for pair
#include <vector>     // for vector, vector<>::iterator
#include <fstream>    // for ifstream
#include "config.h"   // for max_dic_word_size, max_input_word_length


using std::cout;
using std::cerr;
using std::endl;


AnagramFinder::AnagramFinder(const string &word):input_word_length(word.length())
{
    //the dictionary with 99172 words is taken from Linux /usr/share/dict/words
    parse_file("linux.dic");

    //under development
    //parse_file_map("linux.dic");
}


bool AnagramFinder::validate_string(const string &str){

    if(str.length() < input_word_length || str.length() > max_input_word_length) {
        return false;
    }

    for (size_t i = 0 ; i < str.length(); i++){

        //Input word can only contain ASCII alphanumeric values
        if (!isalpha(str.at(i))){
            return false;
        }
    }
    return true;
}

bool AnagramFinder::find_longest_derivation(const string &str){

    vector<string> result_list;
    result_list.push_back(str);

    //string size in current iteration
    size_t str_size = str.length()+1;

    //looking for a matching anagram with a size one character more than the previous, starting with a length one char greater than input word
    for (; str_size < max_dic_word_size; str_size++ ){

        if (result_list.back().length() != str_size - 1 ){
            break; //Finish program
        }

        //iterate over anagram list and find keys of given length
        for (std::vector<string>::iterator it = anagram_vector.begin(); it != anagram_vector.end(); ++it)
        {

            if(it->length() == str_size  ){

                if( anagram_compare((*it), result_list.back() ) ){

                    result_list.push_back((*it));

                    break; //next size
                }
            }

        }
    }

    cout << "\n\nAnagram derivation result:\n" << endl;

    for ( size_t i = 0; i < result_list.size()-1; i++ ){
        cout << result_list.at(i) << " -> ";
    }

    cout << result_list.back() <<  endl << endl; //last element

    return true;

}


bool AnagramFinder::parse_file(const string &filename){

    std::ifstream file(filename);
    string str;

    if (!file.is_open())
    {
        cerr << "Unable to open file" << "\n";
        std::exit(-1);
    }

    while (std::getline(file, str))
    {
        if(!validate_string(str)){ //skipping non-valid strings
            continue;
        }

        anagram_vector.push_back(str);
    }

    return true;
}




//function takes 2 strings and checks if all the characters in the first string are contained in the second, second string must be 1 char greater than the first string
bool AnagramFinder::anagram_compare( const string &str1, const string &str2){

    if (str1.length() != str2.length()+1){
        cerr << "ERROR:str2 must have length: str1.length = str2.length + 1" << endl;
        cerr << " str1: "<< str1.length() << "str2: " << str2.length()<< endl;
        return false;
    }

    string str1_copy(str1);
    string str2_copy(str2);

    //normalizing string
    std::transform(str1_copy.begin(), str1_copy.end(), str1_copy.begin(), ::tolower);
    std::transform(str2_copy.begin(), str2_copy.end(), str2_copy.begin(), ::tolower);

    while(str1_copy.size() != 0){

        char ch = str1_copy.back();
        str1_copy.pop_back();

        for (size_t i = 0 ; i <= str2_copy.length(); i++){

            if (ch == str2_copy[i]){

                str2_copy.erase(i, 1);

                break;
            }
        }
    }

    if (str2_copy.length() == 0)

        return true;

    else return false;
}












//--------------------------------IN PROGRESS--------------------------------------







//uses multimap to find several (all) anagrams for given word at each step, resulting in a list of tuples
bool AnagramFinder::find_longest_derivation_map(const string &str){

    //TODO: make function to transform string to key

    string key(str);
    string_to_key(key);

    anagram_result_map.insert(std::pair<string,string>(key, str));


    //string size in current iteration
    size_t str_size = str.length()+1;

    std::pair<string_multimap::iterator, string_multimap::iterator> range_iters;


    //looking for a matching anagram with a size one character longer than the previous, starting with a length one char longer than input word
    for (; str_size < max_dic_word_size; str_size++ ){

        if (anagram_result_map.size() != str_size - 1 ){
            break; //Finish program
        }

        // cout << "CURRENT str_size: " << str_size << endl;


        //    if (char_compare()){

        //        return true
        //    } else return false;


        //iterate over anagram list and find keys of given length
        for (string_multimap::iterator it = anagram_map.begin(); it != anagram_map.end(); ++it)
        {

            if((*it).first.length() == str_size  ){

                //TODO: test
                // string str = *(anagram_result_map.end().first);

                if( anagram_compare((*it).first, (anagram_result_map.end())->first) ){

                    //TODO: anagram_result_map.insert(std::pair<string,string>(key, str);

                    // WAS anagram_result_map.push_back((*it).second);

                    range_iters = anagram_map.equal_range((*it).first);

                    if( std::distance(range_iters.first,range_iters.second) > 1){

                        cout << "Found several solutions" << endl;

                        for (string_multimap::iterator it = range_iters.first; it != range_iters.second; ++it)
                        {

                            anagram_result_map.insert(std::pair<string,string>((*it).first,(*it).second));

                            cout << "  [" << (*it).first << ", " << (*it).second << "]" << endl;

                        }
                    }

                    break; //step to next size
                }
            }
        }
    }


    //TODO: anagram_result_map.insert(std::pair<string,string>(key, str);

    cout << "\n\nAnagram derivation result:\n" << endl;

    print_multimap(anagram_result_map);

    return true;

}







//parses the dictionary file into a multimap - anagram_map, where
//the keys are sorted strings (by characters) and the corresponding values are original words
//each unique key holds several anagrams
bool AnagramFinder::parse_file_map(const string &filename){

    std::ifstream file(filename);
    string str;

    if (!file.is_open())
    {
        cerr << "Unable to open file" << "\n";
        std::exit(-1);
    }

    while (std::getline(file, str))
    {
        if(!validate_string(str)){ //skipping non-valid strings
            continue;
        }

        string *key = nullptr;

        //the keys are equal if they contain the same set of chars
        key = find_map_key(str);

        if(key != nullptr) {
            // iterate over values from first until second and insert if unique

            if(find_map_value_for_key(*key)) {
                //the original word is saved by this key
                continue; //next word in a list
            }else{
                //  cout << " INSERT [" << (*it).first << ", " << (*it).second << "]" << endl;
                anagram_map.insert(std::pair<string, string>(*key,str));
            }

        }  else{

            string unique_key(str); // copy to save the original word, and sort the key



            anagram_map.insert(std::pair<string, string>(unique_key,str));
        }
    }
    return true;
}



bool AnagramFinder::find_map_value_for_key( const string &key){

    std::pair<string_multimap::iterator, string_multimap::iterator> range_iters;

    range_iters = anagram_map.equal_range(key);

    if( std::distance(range_iters.first,range_iters.second) > 1){

        for (string_multimap::iterator it = range_iters.first; it != range_iters.second; ++it)
        {
            if ((*it).second == key) {
                return true;
            }
            return false; //unique value
        }
    }
}


//TODO: find the key in the multimap with the same set of chars
string * AnagramFinder::find_map_key( const string &str){

    string sorted_string(str);

    string_to_key(sorted_string);

    string_multimap::iterator it = anagram_map.find(sorted_string);

    if(it != anagram_map.end()) {
        // cout << "Found [" << it->first << " : " << it->second << "] \n";

        return (string *) &(it->first);
        //TODO: test
    }

    return nullptr;
}


void AnagramFinder::string_to_key(string &str){
    std::sort(str.begin(), str.end());
}
