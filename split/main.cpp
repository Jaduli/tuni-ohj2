#include <iostream>
#include <string>
#include <vector>



std::vector<std::string> split(std::string line, char separator, bool remove_empty = false) {
    std::vector<std::string> new_vector;

    if (remove_empty) {
        int i = 0;
        while (line.find(separator) != std::string::npos) {
            if (line.at(i) == separator) {
                std::string new_line = line.substr(0,i);

                if (!new_line.empty()){
                    new_vector.push_back(new_line);
                }

                line = line.substr(i+1);
                i = 0;
            }
            else {
                ++i;
            }
        }
        if (!line.empty()) {
            new_vector.push_back(line);
        }
    }

    else {
        int i = 0;
        while (line.find(separator) != std::string::npos) {
            if (line.at(i) == separator) {
                std::string new_line = line.substr(0,i);

                new_vector.push_back(new_line);
                line = line.substr(i+1);

                i = 0;
            }
            else {
                ++i;
            }
        }
        new_vector.push_back(line);
    }
    return new_vector;
}


int main()
{
    std::string line = "";
    std::cout << "Enter a string: ";
    getline(std::cin, line);
    std::cout << "Enter the separator character: ";
    char separator = getchar();

    std::vector< std::string > parts  = split(line, separator);
    std::cout << "Splitted string including empty parts: " << std::endl;
    for( auto part : parts ) {
        std::cout << part << std::endl;
    }

    std::vector< std::string > parts_no_empty  = split(line, separator, true);
    std::cout << "Splitted string ignoring empty parts: " << std::endl;
    for( auto part : parts_no_empty ) {
        std::cout << part << std::endl;
    }
}
