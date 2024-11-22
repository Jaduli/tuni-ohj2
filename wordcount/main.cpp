#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

using MapType = map<string, string>;

int main()
{
    string input_file;
    cout << "Input file: ";
    getline(cin, input_file);

    ifstream input_object(input_file);

    if (not input_object) {
        cout << "Error! The file " << input_file << " cannot be opened." << endl;
        return EXIT_FAILURE;
    }

    MapType info;

    int row_index = 1;

    string row;
    while (getline(input_object, row)) {

        row = row + " ";

        size_t index = row.find(" ");

        while (index != string::npos) {

            string word = row.substr(0,index);
            row = row.substr(index+1);

            if (info.find(word) == info.end()) {
                info[word] = to_string(row_index);
            }
            else {
                bool checker = true;
                    for (char character : info[word]) {
                        if (character == char(row_index + '0')) {
                            checker = false;
                    }
                }
                if (checker == true) {
                    info[word] += ", ";
                    info[word] += to_string(row_index);
                }
            }

            index = row.find(" ");

        }
        ++row_index;
    }
    for (auto pair1 : info) {
        int number_count = 0;
        for (char character : pair1.second) {
            if (isdigit(character)) {
                ++number_count;
            }
        }
        cout << pair1.first << " " << number_count << ": " << pair1.second << endl;

    }
}
