#include <iostream>

using namespace std;

unsigned long int factorial(int number) {
    unsigned long int value = 1;

    for (int i=1; i <= number; ++i) {
        value *= i;
    }
    return value;
}

unsigned long int lotteryAmount(unsigned long int total, unsigned long int drawn) {
    unsigned long int amount = factorial(total) / ( factorial(total-drawn) * factorial(drawn) );

    return amount;
}

int main()
{
    cout << "Enter the total number of lottery balls: ";

    int total = 0;
    cin >> total;

    cout << "Enter the number of drawn balls: ";

    int drawn = 0;
    cin >> drawn;

    if ( total <= 0 or drawn <= 0 ) {
        cout << "The number of balls must be a positive number." << endl;
    }
    else if ( total < drawn ) {
        cout << "The maximum number of drawn balls is the total amount of balls." << endl;
    }
    else {
        cout << "The probability of guessing all " << drawn << " balls correctly is 1/" << lotteryAmount(total, drawn) << endl;
    }
}
