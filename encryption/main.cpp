#include <iostream>
#include <string>
#include <cctype>

using namespace std;

int stringLength(string text) {
    string::size_type lgt = 0;
    lgt = text.length();

    return lgt;
}

bool checkForAlphabet(string word) {
    for(char letter = 'a'; letter <= 'z'; ++letter)
        if ( word.find(letter) == string::npos ) {
            return false;
        }
    return true;
}

bool checkIfLower(string word, int lgt) {
    string check = "";

    for (int i = 0; i < lgt; ++i) {
        if ( islower(word.at(i)) ) {
            check += word.at(i);
        }
    else {
            return false;
        }
    }
    return true;
}

string encryptText(string text, string key, int textlength) {
    string encrypted_message = "";

    for ( int i = 0; i < textlength; ++i ){
        char letter = text.at(i);
        int position = static_cast<int>(letter) - static_cast<int>('a');
        encrypted_message += static_cast<char>(key.at(position));
    }
    return encrypted_message;
}

int main()
{
    cout << "Enter the encryption key: ";

    string key = "";
    cin >> key;

    int keylength = stringLength(key);

    bool keylower = checkIfLower(key, keylength);
    bool keyalpha = checkForAlphabet(key);

    if ( keylength != 26 ) {
        cout << "Error! The encryption key must contain 26 characters." << endl;
        return EXIT_FAILURE;
    }
    else if ( not keylower ) {
        cout << "Error! The encryption key must contain only lower case characters." << endl;
        return EXIT_FAILURE;
    }
    else if ( not keyalpha ) {
        cout << "Error! The encryption key must contain all alphabets a-z." << endl;
        return EXIT_FAILURE;
    }

    cout << "Enter the text to be encrypted: ";

    string text = "";
    cin >> text;

    int textlenght = stringLength(text);

    bool textlower = checkIfLower(text, textlenght);
    if ( not textlower ) {
            cout << "Error! The text to be encrypted must contain only lower case characters." << endl;
            return EXIT_FAILURE;
    }
    string new_message = encryptText(text, key, textlenght);
    cout << "Encrypted text: " << new_message << endl;
}
