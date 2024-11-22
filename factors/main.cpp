#include <iostream>
#include <string>

using namespace std;

int main()
{
    cout << "Enter a positive number: ";

    int number = 0;
    cin >> number;

    int factor1 = 1;
    int factor2 = number;

    if ( number > 0 ) {
        for ( int i = 2; i <= number / 2; ++i ) {
            if ( number % i == 0 ) {
                if ( abs(number / i - i) < abs(factor2 - factor1) ) {
                    factor1 = i;
                    factor2 = number / i;
                }
            }
        }
        cout << number << " = " << factor1 << " * " << factor2 << endl;
    }
    else {
        cout << "Only positive numbers accepted" << endl;
    }

    return 0;
}
