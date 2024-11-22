#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

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

    map<string, int> info;

    string row;
    while (getline(input_object, row)) {
        int iter = row.find(":");

        string name = row.substr(0,iter);
        int points = stoi(row.substr(iter+1));

        if (info.find(name) == info.end()) {
            info.insert(make_pair(name, points));
        }
        else {
            for (auto& pair : info) {
                if (pair.first == name) {
                    pair.second += points;
                }
            }
        }
    }
    cout << "Final scores:" << endl;
    for (auto pair : info) {
        cout << pair.first << ": " << pair.second << endl;
    }
}
