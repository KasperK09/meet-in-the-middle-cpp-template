#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <fstream>
#include <string>

// -------------------------------------------------------------
// Helper: write file contents easily for each test
// -------------------------------------------------------------
void writeFile(const std::string& filename, const std::string& contents) {
    std::ofstream fout(filename);
    fout << contents;
}

// -------------------------------------------------------------
// Prototype of the student's function
// Change this if your function name differs
// -------------------------------------------------------------
double findMedianFromFile(const std::string& filename);

// -------------------------------------------------------------
// Z — Zero Case
// -------------------------------------------------------------
TEST_CASE("Zero items (empty file)") {
    writeFile("data_empty.csv", "");

    REQUIRE_THROWS_AS(findMedianFromFile("data_empty.csv"), std::runtime_error);
}

// -------------------------------------------------------------
// O — One Item
// -------------------------------------------------------------
TEST_CASE("One item") {
    writeFile("data_one.csv", "42");

    REQUIRE(findMedianFromFile("data_one.csv") == Approx(42.0));
}

// -------------------------------------------------------------
// M — Many Items
// -------------------------------------------------------------
TEST_CASE("Odd count") {
    writeFile("data_odd.csv", "1,3,5,7,9");

    REQUIRE(findMedianFromFile("data_odd.csv") == Approx(5.0));
}

TEST_CASE("Even count") {
    writeFile("data_even.csv", "10,20,30,40");

    REQUIRE(findMedianFromFile("data_even.csv") == Approx(25.0));
}

TEST_CASE("Larger even") {
    writeFile("data_large.csv", "1,2,3,4,5,6,7,8,9,10");

    REQUIRE(findMedianFromFile("data_large.csv") == Approx(5.5));
}

// -------------------------------------------------------------
// B — Boundary Conditions
// -------------------------------------------------------------
TEST_CASE("Negative numbers") {
    writeFile("data_neg.csv", "-10,-5,0,5,10");

    REQUIRE(findMedianFromFile("data_neg.csv") == Approx(0.0));
}

TEST_CASE("Identical values") {
    writeFile("data_same.csv", "8,8,8,8,8,8");

    REQUIRE(findMedianFromFile("data_same.csv") == Approx(8.0));
}

// -------------------------------------------------------------
// I — Interface / file issues
// -------------------------------------------------------------
TEST_CASE("File does not exist") {
    REQUIRE_THROWS_AS(findMedianFromFile("no_such_file.csv"), std::runtime_error);
}

TEST_CASE("Trailing comma") {
    writeFile("data_trailing.csv", "1,2,3,4,");

    REQUIRE(findMedianFromFile("data_trailing.csv") == Approx(2.5));
}

// -------------------------------------------------------------
// E — Exception Behavior
// -------------------------------------------------------------
TEST_CASE("Malformed CSV") {
    writeFile("data_bad.csv", "1,2,x,4,5");

    REQUIRE_THROWS_AS(findMedianFromFile("data_bad.csv"), std::runtime_error);
}

// -------------------------------------------------------------
// S — Simple Scenario (given example)
// -------------------------------------------------------------
TEST_CASE("Example from instructions") {
    writeFile("data_example.csv",
        "1,2,6,8,9,11,27,45,71,90,104"
    );

    REQUIRE(findMedianFromFile("data_example.csv") == Approx(11.0));
}
