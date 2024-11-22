#include <iostream>
#include <string>


int main()
{
    std::cout << "How many numbers would you like to have? ";

    int numbers = 0;
    std::cin >> numbers;

    for ( int num = 1; num < numbers+1; ++num ) {
        if ( num % 3 == 0 and num % 7 == 0 ) {
            std::cout << "zip boing" << std::endl;
        }
        else if ( num % 3 == 0 ) {
            std::cout << "zip" << std::endl;
        }
        else if ( num % 7 == 0 ) {
            std::cout << "boing" << std::endl;
        }
        else {
            std::cout << num << std::endl;
        }
    }

    return 0;
}
