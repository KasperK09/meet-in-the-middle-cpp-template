#include <iostream>
#include <fstream>

using namespace std;

int main() 
{
    string filename;
    cout << "Enter the filename: ";
    cin >> filename;

    ifstream fin(filename);
    if (!fin.is_open()) {
        cerr << "Error: Could not open file.\n";
        return 1;
    }

    // ---- First pass: count how many integers are in the CSV ----
    int count = 0;
    int temp;
    char comma;

    while (fin >> temp) {
        count++;
        fin >> comma;  // Try to read a comma (fails on last entry, but that's ok)
    }

    if (count == 0) {
        cerr << "Error: File is empty.\n";
        return 1;
    }

    // ---- Allocate dynamic array ----
    int* data = new(nothrow) int[count];
    if (data == nullptr) {
        cerr << "Error: Memory allocation failed.\n";
        return 1;
    }

    // ---- Second pass: load data ----
    fin.clear();        // Reset stream state
    fin.seekg(0);       // Rewind to file beginning

    int index = 0;
    while (fin >> temp) {
        data[index++] = temp;
        fin >> comma;
    }

    fin.close();

    // ---- Compute the median ----
    double median = 0.0;

    if (count % 2 == 1) {
        // Odd number of elements
        median = data[count / 2];
    } else {
        // Even: average of two middle elements
        int mid1 = data[(count / 2) - 1];
        int mid2 = data[count / 2];
        median = (mid1 + mid2) / 2.0;
    }

    // ---- Output result ----
    cout << "The median of the dataset is " << median << endl;

    // ---- Clean up ----
    delete[] data;

    return 0;
}
