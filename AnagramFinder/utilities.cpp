
#include <algorithm>
#include <stdlib.h>  // for exit, size_t, EXIT_FAILURE
#include <cctype>    // for isalpha
#include <iostream>  // for operator<<, basic_ostream, endl, ostream, cerr
#include <string>    // for string, char_traits
#include <getopt.h>   // for getopt, optarg, opterr
//TODO: change to QT program args parsing

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

    if(str.length() < min_input_word_length) {
        cerr << "\nInput word must contain at least" << min_input_word_length << "characters\n" << endl;
        return false;
    } else if(str.length() > max_input_word_length) {
        cerr << "\nInput word must contain not more than" << max_input_word_length << "characters\n" << endl;
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



void print_help(  char *argv[])
{
    cout << "\nUsage: "  << argv[0]  << " [-h help] [-w word] \n"<< endl;
    cout << "\nFor example :\n" << endl;
    cout <<  argv[0] << "\n -w read \n\n"  << endl;
    exit(EXIT_FAILURE);
}




//--------------------------------IN PROGRESS--------------------------------------




//TODO: test
//function checks if the strings contain the same chars
bool char_compare( const string &str1, const string &str2){

    if (str1.length() != str2.length()){
        cerr << "ERROR: string  lengths must be equal" << endl;
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



//TODO: test
void print_multimap(string_multimap &mm){

    std::pair<string_multimap::iterator, string_multimap::iterator> mm_iter;

    for(string_multimap::iterator iter = mm.begin(); iter != mm.end(); ++iter){

        mm_iter = mm.equal_range(iter->first);

        if( std::distance(mm_iter.first,mm_iter.second) > 1){
            //several values under one key, each value is

            for (string_multimap::iterator it = mm_iter.first; it != mm_iter.second;

                 ++it)
            {
                cout << "  [" << (*it).first << ", " << (*it).second << "]" << endl;
            }
        }
    }

}




