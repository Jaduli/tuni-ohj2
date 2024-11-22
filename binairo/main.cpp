/* Binairo
 *
 * Kuvaus:
 *   Ohjelma toteuttaa Binairo-pelin. Pelissä on peliruudukko kooltaan 6 x 6.
 * Kukin ruutu sisältää nollan, ykkösen tai tyhjän. Tarkoituksena on lisätä
 * tyhjiin ruutuihin nollia ja ykkösiä seuraavien sääntöjen mukaisesti:
 * - kullakin vaaka- ja pystyrivillä saa olla korkeintaan kolme samaa lukua
 * - kullakin vaaka- ja pystyrivillä saa olla peräkkäin korkeintaan kaksi
 *   samaa lukua.
 *   Aluksi käyttäjältä kysytään, täytetäänkö peliruudukko satunnaisesti
 * arvottavilla merkeillä vai käyttäjän valitsemilla 36 merkillä.
 * Ensimmäisessä vaihtoehdossa käyttäjältä kysytään satunnaisluku-
 * generaattorin siemenlukua ja jälkimmäisessä häntä pyydetään syöttämään
 * 36 merkkiä, joiden oikeellisuus tarkistetaan.
 *   Joka kierroksella käyttäjältä kysytään lisättävän merkin koordinaatteja
 * sekä lisättävää merkkiä eli kolmea merkkiä. Peli päättyy pelaajan voittoon,
 * jos peliruudukko on saatu täytettyä e.m. sääntöjen mukaisesti. Ohjelma ei
 * salli tehdä lisäyksiä, jotka rikkovat e.m. sääntöjä, mutta on mahdollista
 * päätyä tilanteeseen, jossa mikään lisäys ei ole enää mahdollinen.
 *   Ohjelma tarkistaa annetut syötteet. Lisättävän merkin pitää olla nolla
 * tai ykkönen. Koordinaattien pitää olla peliruudukon sisällä, ja niiden
 * osoittaman ruudun pitää olla tyhjä.
 *
 * Ohjelman kirjoittaja
 * Nimi: Jade Pitkänen
 * Opiskelijanumero: 151842146
 * Käyttäjätunnus: kcjapi
 * E-Mail: jade.pitkanen@tuni.fi
 */

#include "gameboard.hh"
#include <iostream>
#include <random>

using namespace std;

// Tulosteet
const string QUIT = "Quitting ...";
const string OUT_OF_BOARD = "Out of board";
const string INVALID_INPUT = "Invalid input";
const string CANT_ADD = "Can't add";
const string WIN = "You won!";
const string BAD_SEED = "Bad seed";
const string WRONG_SIZE = "Wrong size of input";
const string WRONG_CHAR = "Wrong character";

// Tarkastaa, onko syöte Binario-peliin sopiva.
bool check_input(string input) {
    for (string::size_type i=0; i < input.length(); ++i) {
        if (input.at(i) != '1' and input.at(i) != '0' and input.at(i) != ' ') {
            return false;
        }
    }
    return true;
}

// Muuttaa numeerisen merkkijonon vastaavaksi kokonaisluvuksi
// (kutsumalla stoi-funktiota) ja palauttaa tämän kokonaisluvun.
// Jos annettu merkkijono ei ollut numeerinen, palauttaa nollan.
unsigned int stoi_with_check(const string& str)
{
    bool is_numeric = true;
    for(unsigned int i = 0; i < str.length(); ++i)
    {
        if(not isdigit(str.at(i)))
        {
            is_numeric = false;
            break;
        }
    }
    if(is_numeric)
    {
        return stoi(str);
    }
    else
    {
        return 0;
    }
}

// Poistaa tyhjät merkit (kuten ' ') annetusta merkkijonosta.
// Palauttaa toden, jos annetussa merkkijonossa on täsmälleen yksi ei-tyhjä
// merkki, joka on '0' tai '1', muussa tapauksessa palauttaa epätoden.
bool find_fill_symbol(string& str)
{
    string fill_str = "";
    for(unsigned int i = 0; i < str.size(); ++i)
    {
        if(not isspace(str.at(i)))
        {
            fill_str += str.at(i);
        }
    }
    str = fill_str;
    return (fill_str.size() == 1 and
           (fill_str.at(0) == '0' or fill_str.at(0) == '1'));
}

// Mahdollistaa pelin pelaamisen eli kysyy toistuvasti lisättävää merkkiä
// ja sen sijaintia, kunnes peli päättyy.
void play_game(GameBoard& board)
{
    board.print();
    while(not board.is_game_over())
    {
        string x_str = "";
        string y_str = "";
        string rest_input = "";
        cout << "Enter two coordinates and a fill symbol, or q to quit: ";

        // Luetaan x-koordinaatti merkkijonona ja tarkistetaan, oliko kyseessä
        // lopetuskomento
        cin >> x_str;
        if(x_str.at(0) == 'q' or x_str.at(0) == 'Q')
        {
            cout << QUIT << endl;
            return;
        }

        // Luetaan y-koordinaatti
        cin >> y_str;

        // Muutetaan koordinaatit merkkijonoista kokonaisluvuiksi ja
        // tarkistetaan, ovatko ne pelilaudan sisällä
        unsigned int x = stoi_with_check(x_str);
        unsigned int y = stoi_with_check(y_str);
        if(not (1 <= x and x <= SIZE and 1 <= y and y <= SIZE))
        {
            cout << OUT_OF_BOARD << endl;
            getline(cin, rest_input);
            continue;
        }

        // Luetaan loppusyöte, joka sisältää täyttömerkin, ja tarkistetaan,
        // koostuuko loppusyöte täsmälleen yhdestä merkistä '0' tai '1'
        getline(cin, rest_input);
        if(not find_fill_symbol(rest_input))
        {
            cout << INVALID_INPUT << endl;
            continue;
        }

        char number_input = rest_input.at(0);

        // Tässä kohdassa tiedetään, että syöte oli hyväksyttävä, mutta ei
        // ole varmaa, voidaanko annettu merkki lisätä annettuun kohtaan

        // Tarkastetaan, onko kohta tyhjä ja sopiiko siihen laittaa annettu
        // numero. Numero lisätään lautaan, jos se on kohtaan sopiva.

        if (board.get_element(x-1, y-1) == EMPTY) {

            board.add_element(x-1, y-1, number_input);

            if (!board.check_if_same_amount(x-1, y-1)
                    or !board.check_in_a_row(x-1, y-1)) {
                cout << CANT_ADD << endl;
                board.add_element(x-1, y-1, ' ');
                continue;
            }

        }
        else {
            cout << CANT_ADD << endl;
            continue;
        }
        // Jos annettu merkki voitiin lisätä, tulostetaan muuttunut pelilauta
        board.print();
    }
    // Jos peli päättyy täyteen pelilautaan, pelaaja voitti
    cout << WIN << endl;
}

// Kysyy käyttäjältä pelilaudan täyttötapaa.
// Palauttaa toden, jos pelilaudan täyttäminen onnistui,
// muuten palauttaa epätoden.
bool select_start(GameBoard& board)
{

    string choice = "";
    cout << "Select start (R for random, I for input): ";
    getline(cin, choice);
    if(choice != "R" and choice != "r" and choice != "I" and choice != "i")
    {
        return false;
    }
    else if(choice == "R" or choice == "r")
    {
        string seed_string = "";
        cout << "Enter a seed value: ";
        getline(cin, seed_string);

        // Täytetään pelilauta annetun siemenluvun avulla ja
        // palautetaan tieto täytön onnistumisesta.
        int seed = stoi(seed_string);


        if (board.check_seed(seed) == true) {
            default_random_engine gen(seed);

            char upper_value = '0' + DISTR_UPPER_BOUND;

            uniform_int_distribution<char> distr('0', upper_value);

            board.create_empty_board();

            for (int i=0; i < SIZE; ++i) {
                for (int j=0; j < SIZE; ++j) {

                    char number = distr(gen);
                    board.add_element(j, i, number);
                }
            }
        }
        else {
            cout << BAD_SEED << endl;
            return false;
        }
        return true;
    }

    else // jos (choice == "I" tai choice == "i")
    {
        string input = "";
        cout << "Input: ";
        getline(cin, input);

        // (Huomaa, että tässä vaiheessa input sisältää vielä lainausmerkit tms.)
        // Täytetään pelilauta annetun merkkijonon perusteella
        // ja palautetaan tieto täytön onnistumisesta.

        // Poistetaan ensin lainausmerkit tms.
        input = input.substr(1, input.length()-2);

        if (input.length() != SIZE*SIZE) {
            cout << WRONG_SIZE << endl;
            return false;
        }
        else if (!check_input(input)) {
            cout << WRONG_CHAR << endl;
            return false;
        }
        else {
            board.create_empty_board();

            for (int i=0; i < SIZE; ++i) {
                for (int j=0; j < SIZE; ++j) {
                    board.add_element(j, i, char(input.at(0)));
                    input = input.substr(1);
                }
            }
        }

        return true;
    }
}

// Lyhyt ja yksinkertainen pääohjelma.
int main()
{
    vector<vector<Element_type>> new_board;

    GameBoard board(new_board);
    while(not select_start(board)); // ei toistettavaa koodia

    play_game(board);
    return 0;
}
