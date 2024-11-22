#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
    string input_file;
    cout << "Input file: ";
    getline(cin, input_file);

    string output_file;
    cout << "Output file: ";
    getline(cin, output_file);

    ifstream input_object(input_file);

    if (not input_object) {
        cout << "Error! The file " << input_file << " cannot be opened." << endl;
        return EXIT_FAILURE;
    }
    else {
        ofstream output_object(output_file);
        int count = 1;
        string row;
        while (getline(input_object, row)) {
            output_object << count << " " << row << endl;
            ++count;
        }
        input_object.close();
        output_object.close();
        return EXIT_SUCCESS;
    }
}
