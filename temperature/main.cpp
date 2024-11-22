#include <iostream>
#include <string>

using namespace std;

int main()
{
    cout << "Enter a temperature: ";
    float temperature = 0;

    cin >> temperature;

    cout << temperature << " degrees Celsius is " << 1.8 * temperature + 32 << " degrees Fahrenheit" << endl;
    cout << temperature << " degrees Fahrenheit is " << (temperature - 32)/1.8 << " degrees Celsius" << endl;

}
