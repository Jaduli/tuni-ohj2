#include <iostream>
#include <random>
#include <string>

using namespace std;

void produce_random_numbers(unsigned int lower, unsigned int upper, int seed, int count)
{
    default_random_engine gen(seed);
    uniform_int_distribution<unsigned int> distr(lower, upper);

    for (int i=0; i<=count; ++i) {
        unsigned int number = distr(gen);
        if (i==count) {
            cout << "Your drawn random number is " << number << endl;
        }
    }
}

int main()
{
    unsigned int lower_bound, upper_bound, seed;
    cout << "Enter a lower bound: ";
    cin >> lower_bound;
    cout << "Enter an upper bound: ";
    cin >> upper_bound;

    if(lower_bound >= upper_bound)
    {
        cout << "The upper bound must be strictly greater than the lower bound"
             << endl;
        return EXIT_FAILURE;
    }

    cout << "Enter a seed value: ";
    cin >> seed;

    bool cont = true;
    string input;
    int count = 0;

    while (cont){
        cout << endl;
        produce_random_numbers(lower_bound, upper_bound, seed, count);
        cout << "Press q to quit or any other key to continue: ";
        cin >> input;
        if ( input == "q" ) {
            cont = false;
        }
        ++count;
    }
    return EXIT_SUCCESS;
}
