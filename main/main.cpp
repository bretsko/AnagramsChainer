#include "AnagramFinder.h"

int main(int argc, char *argv[])
{
    string input_string = parse_program_args(argc,argv);

    AnagramFinder anagramFinder(input_string);

    anagramFinder.find_longest_derivation(input_string);

    //under development
    //anagramFinder.find_longest_derivation_map(input_string);

    exit(EXIT_SUCCESS);
}
