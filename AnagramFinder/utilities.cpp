
#include <algorithm>
#include <stdlib.h>  // for exit, size_t, EXIT_FAILURE
#include <cctype>    // for isalpha
#include <iostream>  // for operator<<, basic_ostream, endl, ostream, cerr
#include <string>    // for string, char_traits
#include <getopt.h>   // for getopt, optarg, opterr

#include <vector>

#include "utilities.h"
#include "config.h"

using std::cout;
using std::cerr;
using std::endl;

string parse_program_args(int argc, char *argv[])
{
    int c = 0;
    opterr = 0;
    if (argc == 3) {

        while ((c = getopt (argc, argv, "h:w:")) != -1) {
            switch (c) {
            case 'h': {
                if (optarg) {
                    cerr << "\nhelp does not accept any arguments\n" << endl;
                    print_help(argv);
                } else {
                    print_help(argv);
                }
            }
            case 'w': {

                if (validate_input(optarg) ==true){

                    return string(optarg);
                }
            }
            case '?': {
                cerr << "\nError: wrong argument supplied\n" << endl;
                print_help(argv);
            }
            }
        }
    } else if (argc == 2) {
        while ((c = getopt (argc, argv, "hr")) != -1) {
            switch (c) {
            case 'h': {
                print_help(argv);
            }
            case 'r': {
                cerr << "\nPlease provide a word\n" << endl;
                print_help(argv);
            }
            }
        }
        cerr << "\nError: wrong argument supplied\n" << endl;
        print_help(argv);
    } else {
        cerr << "\nError: no arguments supplied\n" << endl;
        print_help(argv);
    }
    return nullptr;
}


bool validate_input(const string &str){

    if(str.length() < k_min_input_word_length) {
        cerr << "\nInput word must contain at least" << k_min_input_word_length << "characters\n" << endl;
        return false;
    } else if(str.length() > k_max_input_word_length) {
        cerr << "\nInput word must contain not more than" << k_max_input_word_length << "characters\n" << endl;
        return false;
    }

    for (size_t i = 0 ; i < str.length(); i++){

        if (!isalpha( str.at(i))){
            cerr << "Input word can only contain ASCII alphanumeric values" << endl;
            return false;
        }
    }

    return true;
}



void print_help( char *argv[])
{
    cout << "\nUsage: "  << argv[0]  << "[-h help] [-w word] \n"<< endl;
    cout << "\nFor example :\n" << endl;
    cout <<  argv[0] << "\n -w read \n\n"  << endl;
    exit(EXIT_FAILURE);
}


void print_multimap(string_multimap_t &mm){
    int count = 0;
    for(auto iter = mm.begin(); iter != mm.end(); ++iter){
        cout << "  [" << iter->first << ", " << iter->second << "]" << endl;
        count++;
    }
    cout << "  Total: " << count << endl;
}



void print_map_vector(map_vector_t &mv){
    int count = 0, cnt = 0;
    string prev_key, prev_value;

    for(auto map_iter : mv){
        for(auto iter : map_iter){
            count++;
        }
    }

    cout << "Found " << count << " anagrams: \n" << endl;

    for(auto map_iter : mv){  //vector of maps

        for(auto iter : map_iter){

            if(prev_value.empty()){
                prev_key = iter.first;
                prev_value = iter.second;
                cnt++;
                continue;
            }

            if(iter.first == prev_key){

                if(cnt == count - 1){
                    cout << prev_value << ", " << iter.second << "\n\n" << endl;
                }else{
                    cout <<  prev_value << ", " ;
                    cnt++;
                }
            }   else{
                if(cnt == count - 1){
                    cout << prev_value << " -> " << iter.second << "\n\n" << endl;
                }else{
                    cout <<  prev_value << " -> " ;
                    cnt++;
                }
            }

            prev_key = iter.first;
            prev_value = iter.second;

        }
    }
}




//multimap extension to extract pair of key-values for given key from one multimap and insert into another
void multimap_transfer_values_for_key(string_multimap_t &mm_from,string_multimap_t &mm_to, const string &key){


    auto range_iters = mm_from.equal_range(key);

    if( std::distance(range_iters.first,range_iters.second) > 1){

        cout << "Found several solutions" << endl;

        for (auto it = range_iters.first; it != range_iters.second; ++it)
        {


            mm_to.insert(*it);
        }

    }else {
        mm_to.insert(*range_iters.first);
    }
}


