
#include "testAnagramFinder.h"

//using ::testing::Return;

AnagramFinderTest::AnagramFinderTest() {

}

AnagramFinderTest::~AnagramFinderTest() {
}

void AnagramFinderTest::SetUp() {
    //pass incorrect data and expect errors
    //too long, too short, big file, 0, empty file, empty string,
    string input_string = "abcdef";
    anagramFinder = new AnagramFinder(input_string);
}

void AnagramFinderTest::TearDown() {
    delete anagramFinder;
}

TEST(AnagramFinderTest, ProgramArgumentParserTest) {

    //pass incorrect data and expect errors for argv
    //too long, too short, big file, 0, empty string,

    // string input_string = parse_program_args(argc,argv);
}

TEST_F(AnagramFinderTest, FileReaderTest) {
    //pass incorrect data and expect errors
    //empty file, too long string, too short, big file, 0, empty string,
}


TEST_F(AnagramFinderTest, AnagramFinderFunctionTest) {
    //pass incorrect data and expect errors
    //too long, too short, big file, 0, empty file, empty string,


    //construct an anagramFinder mock to test the function
   // anagramFinder->find_longest_derivation(input_string);

    //check that the result is always correct
}


