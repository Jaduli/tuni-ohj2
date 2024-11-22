#include <iostream>

using namespace std;

int main()
{
    cout << "Enter a number: ";

    int number = 0;
    cin >> number;

    int power3 = number * number * number;

    if ( power3 / number / number != number ) {
        cout << "Error! The cube of " << number << " is not " << power3 << endl;
    }
    else {
        cout << "The cube of " << number << " is " << power3 << "." << endl;
    }

}
