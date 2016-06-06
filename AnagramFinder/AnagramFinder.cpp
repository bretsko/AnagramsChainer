#include "AnagramFinder.h"

#include <stdlib.h>   // for size_t
#include <algorithm>  // for transform
#include <cctype>     // for tolower
#include <iostream>   // for operator<<, basic_ostream, cout, endl, ostream
#include <memory>     // for allocator
#include <utility>    // for pair
#include <vector>     // for vector
#include "config.h"   // for MAX_DIC_WORD_LENGTH
#include <fstream>    // for ifstream
#include <map>

using std::cout;
using std::cerr;
using std::endl;


AnagramFinder::AnagramFinder(const string &word):input_string(word)
{
    //the dictionary with 99172 words is taken from Linux /usr/share/dict/words
    parse_file_to_map("linux.dic");
}


bool AnagramFinder::validate_string(const string &str){

    if(str.length() < input_string.length() || str.length() > k_max_input_word_length) {
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
    for (; str_size < k_max_dic_word_size; str_size++ ){

        if (result_list.back().length() != str_size - 1 ){
            break; //Finish program
        }

        //iterate over anagram list and find keys of given length
        for (auto it = anagram_vector.begin(); it != anagram_vector.end(); ++it)
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


bool AnagramFinder::parse_file_to_vector(const string &filename){

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

bool AnagramFinder::anagram_compare( const string &bigger_str, const string &smaller_str){

    if (bigger_str.length() == 0)
        return false;

    if (bigger_str.length() != smaller_str.length() + 1){
        cerr << "ERROR:smaller_str must have length: str1.length = smaller_str.length + 1" << endl;
        cerr << " bigger_str: "<< bigger_str.length() << "smaller_str: " << smaller_str.length()<< endl;
        return false;
    }

    string bigger_str_copy(bigger_str);
    string smaller_str_copy(smaller_str);

    std::sort(bigger_str_copy.begin(), bigger_str_copy.end());
    std::sort(smaller_str_copy.begin(), smaller_str_copy.end());

    //normalizing string
    std::transform(bigger_str_copy.begin(), bigger_str_copy.end(), bigger_str_copy.begin(), ::tolower);
    std::transform(smaller_str_copy.begin(), smaller_str_copy.end(), smaller_str_copy.begin(), ::tolower);

    //searching for similar characters in two strings and deleting one char at a time until empty, at the end all characters in the smaller string should be erased
    while(bigger_str_copy.size() != 0){

        char ch = bigger_str_copy.back();
        bigger_str_copy.pop_back();

        for (size_t i = 0 ; i <= smaller_str_copy.length(); i++){

            if (ch == smaller_str_copy[i]){
                smaller_str_copy.erase(i, 1);
                break;
            }
        }

        if (smaller_str_copy.size() == 0)
            return true;
    }

    return false;
}


//finds several (all) anagram variants for given word at each step, resulting in a list of tuples
bool AnagramFinder::find_longest_derivation_map(const string &str){

    string key(str);
    string_to_key(key);

    string_map_t anagram_map_init;
    anagram_map_init.insert(std::make_pair(key, str));
    result_map_vector.push_back(anagram_map_init);

    size_t str_size = str.length()+1;

    //looking for a matching anagram with a size one character longer than the previous, starting with a length one char longer than input word
    for (; str_size < k_max_dic_word_size; str_size++ ){

        if (result_map_vector.back().begin()->first.size() != str_size - 1 ){
            break; //Finish program
        }

        //iterate over anagram list and find keys of a given length
        for (auto iter : dic_anagram_map)
        {
            if(iter.first.length() == str_size ){

                //compare by characters, only one character must differ
                if( anagram_compare(iter.first, result_map_vector.back().begin()->first)  == true){

                    //if the key is anagram add the key with values

                    //extract all values for given key
                    auto range_iters = dic_anagram_map.equal_range(iter.first);

                    if( std::distance(range_iters.first,range_iters.second) > 1){

                        string_map_t anagram_map;
                        for (auto it = range_iters.first; it != range_iters.second; ++it)
                        {
                            anagram_map.insert(*it);
                        }

                        result_map_vector.push_back(anagram_map);
                    }else{

                        string_map_t anagram_map;
                        anagram_map.insert(iter);
                        result_map_vector.push_back(anagram_map);
                    }

                    break; //step to next size
                }
            }
        }
    }

    cout << "\n\nAnagram derivation result:\n" << endl;

    print_map_vector(result_map_vector);

    return true;

}


//parses the dictionary file into a multimap - anagram_map, where
//the keys are sorted strings (by characters) and the corresponding values are original words
//each unique key holds several anagrams
bool AnagramFinder::parse_file_to_map(const string &filename){

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

        string key(str);
        string_to_key(key); //sorted lowercase string

        auto iter = dic_anagram_map.find(key);

        if(iter == dic_anagram_map.end()){

            dic_anagram_map.insert(std::make_pair(key,str));

        }else{
            //if found get all values
            auto range_iters = dic_anagram_map.equal_range(key);

            if( std::distance(range_iters.first,range_iters.second) > 1){

                bool found = false;
                for (auto it = range_iters.first; it != range_iters.second; ++it)
                {
                    if(str == it->second ){
                        found = true;
                    }
                }

                if(found){
                    continue;
                }else{// next word

                    //value is unique
                    dic_anagram_map.insert(std::make_pair(key,str));
                }

            }else {
                if(str != iter->second ){
                   //single unique value
                    dic_anagram_map.insert(std::make_pair(key,str));

                }
            }

        }
    }
    return true;
}

void AnagramFinder::string_to_key(string &str){
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    std::sort(str.begin(), str.end());
}



