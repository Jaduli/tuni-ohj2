#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

const std::string HELP_TEXT = "S = store id1 i2\nP = print id\n"
                              "C = count id\nD = depth id\n";


std::vector<std::string> split(const std::string& s,
                               const char delimiter,
                               bool ignore_empty = false)
{
    std::vector<std::string> result;
    std::string tmp = s;

    while(tmp.find(delimiter) != std::string::npos)
    {
        std::string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter) + 1, tmp.size());
        if(not (ignore_empty and new_part.empty()))
        {
            result.push_back(new_part);
        }
    }
    if(not (ignore_empty and tmp.empty()))
    {
        result.push_back(tmp);
    }
    return result;
}

void print_network(std::multimap<std::string, std::string> network, std::string name, int depth) {

    if (depth == 0) {
        std::cout << name << std::endl;
        depth = 2;
    }

    for (const auto& pair : network) {

        if (pair.first == name) {
            for (int i=0; i < depth; ++i) {
                std::cout << ".";
            }
            std::cout << pair.second << std::endl;
            print_network(network, pair.second, depth + 2);
        }
    }
}

int network_size(std::multimap<std::string, std::string> network, std::string name, int count) {
    for (const auto& pair : network) {
        if (pair.first == name) {
            ++count;
            count = count + network_size(network, pair.second, 0);
        }
    }
    return count;
}

int network_depth(std::multimap<std::string, std::string> network, std::string name, int count) {
    int max_depth = 0;

    for (const auto& pair : network) {
        if (pair.first == name) {
            ++count;
            count = count + network_depth(network, pair.second, 0);
        }
        if (count > max_depth) {
            max_depth = count;
        }
        count = 0;
    }
    return max_depth;
}

int main()
{
    // TODO: Implement the datastructure here

    std::multimap<std::string, std::string> network;


    while(true)
    {
        std::string line;
        std::cout << "> ";
        getline(std::cin, line);
        std::vector<std::string> parts = split(line, ' ', true);

        // Allowing empty inputs
        if(parts.size() == 0)
        {
            continue;
        }

        std::string command = parts.at(0);

        if(command == "S" or command == "s")
        {
            if(parts.size() != 3)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id1 = parts.at(1);
            std::string id2 = parts.at(2);

            // TODO: Implement the command here!

            network.insert({id1, id2});



        }
        else if(command == "P" or command == "p")
        {
            if(parts.size() != 2)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            // TODO: Implement the command here!

            print_network(network, id, 0);

        }
        else if(command == "C" or command == "c")
        {
            if(parts.size() != 2)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            // TODO: Implement the command here!

            int size = network_size(network, id, 0);

            std::cout << size << std::endl;

        }
        else if(command == "D" or command == "d")
        {
            if(parts.size() != 2)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            // TODO: Implement the command here!

            int depth = network_depth(network, id, 0);

            std::cout << depth + 1 << std::endl;



        }
        else if(command == "Q" or command == "q")
        {
           return EXIT_SUCCESS;
        }
        else
        {
            std::cout << "Erroneous command!" << std::endl << HELP_TEXT;
        }
    }
}
