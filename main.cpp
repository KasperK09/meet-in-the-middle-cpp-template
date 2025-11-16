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
        cerr << "File could not be opened\n";
        return 1;
    }

    int count = 0;
    int temp;
    char comma;

    while (fin >> temp) {
        count++;
        fin >> comma;
    }

    if (count == 0) {
        cerr << "File is empty.\n";
        return 1;
    }

    int* data = new(nothrow) int[count];
    if (data == nullptr) {
        cerr << "Memory allocation failed.\n";
        return 1;
    }

    fin.clear();
    fin.seekg(0);

    int index = 0;
    while (fin >> temp) {
        data[index++] = temp;
        fin >> comma;
    }

    fin.close();

    double median = 0.0;

    if (count % 2 == 1) {
        median = data[count / 2];
    } else {
        int mid1 = data[(count / 2) - 1];
        int mid2 = data[count / 2];
        median = (mid1 + mid2) / 2.0;
    }

    cout << "The median of the dataset is " << median << endl;

    delete[] data;

    return 0;
}
