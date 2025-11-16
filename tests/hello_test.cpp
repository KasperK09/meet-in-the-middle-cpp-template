#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

using Catch::Approx;

#include <fstream>
#include <string>

//
void make_csv_file(const std::string& filename, const std::string& contents) {
    std::ofstream fout(filename);
    fout << contents;
}

double findMedianFromFile(const std::string& filename);

TEST_CASE("Empty file throws") {
    make_csv_file("data_empty.csv", "");

    REQUIRE_THROWS_AS(findMedianFromFile("data_empty.csv"), std::runtime_error);
}

TEST_CASE("One number") {
    make_csv_file("data_one.csv", "42");

    REQUIRE(findMedianFromFile("data_one.csv") == Approx(42.0));
}

TEST_CASE("Odd count") {
    make_csv_file("data_odd.csv", "1,3,5,7,9");

    REQUIRE(findMedianFromFile("data_odd.csv") == Approx(5.0));
}

TEST_CASE("Even count") {
    make_csv_file("data_even.csv", "10,20,30,40");

    REQUIRE(findMedianFromFile("data_even.csv") == Approx(25.0));
}

TEST_CASE("Large even") {
    make_csv_file("data_large.csv", "1,2,3,4,5,6,7,8,9,10");

    REQUIRE(findMedianFromFile("data_large.csv") == Approx(5.5));
}


TEST_CASE("Negative numbers") {
    make_csv_file("data_neg.csv", "-10,-5,0,5,10");

    REQUIRE(findMedianFromFile("data_neg.csv") == Approx(0.0));
}

TEST_CASE("Identical values") {
    make_csv_file("data_same.csv", "8,8,8,8,8,8");

    REQUIRE(findMedianFromFile("data_same.csv") == Approx(8.0));
}

// -------------------------------------------------------------
// I — Interface
// -------------------------------------------------------------
TEST_CASE("File missing") {
    REQUIRE_THROWS_AS(findMedianFromFile("nope.csv"), std::runtime_error);
}

TEST_CASE("Trailing comma handled") {
    make_csv_file("data_trailing.csv", "1,2,3,4,");

    REQUIRE(findMedianFromFile("data_trailing.csv") == Approx(2.5));
}

// -------------------------------------------------------------
// E — Exceptions
// -------------------------------------------------------------
TEST_CASE("Malformed CSV throws") {
    make_csv_file("data_bad.csv", "1,2,x,4");

    REQUIRE_THROWS_AS(findMedianFromFile("data_bad.csv"), std::runtime_error);
}

// -------------------------------------------------------------
// S — Simple Example
// -------------------------------------------------------------
TEST_CASE("Given example") {
    make_csv_file("data_example.csv",
        "1,2,6,8,9,11,27,45,71,90,104");

    REQUIRE(findMedianFromFile("data_example.csv") == Approx(11.0));
}
