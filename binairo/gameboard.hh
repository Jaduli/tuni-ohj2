/* Ohjelman kirjoittaja
* Nimi: Jade Pitkänen
* Opiskelijanumero: 151842146
* Käyttäjätunnus: kcjapi
* E-Mail: jade.pitkanen@tuni.fi
*/

#ifndef GAMEBOARD_HH
#define GAMEBOARD_HH

#include <vector>
#include <string>

// Pelilaudan alkioiden tyyppi.
enum Element_type {ZERO, ONE, EMPTY};

// Vakiot pelilaudan koon määrittelemiseen.
const int NUMBER_OF_SYMBOLS = 3;
const int SIZE = 2 * NUMBER_OF_SYMBOLS;

// Vakio todennäköisyysjakauman ylärajaa varten.
// Nollilla ja ykkösillä on sama todennäköisyys, vaikkapa x, ja tyhjien
// todennäköisyyden voidaan arvioida olevan 6x, jolloin jakaumassa
// on yhteensä kahdeksan pistettä (lukua), joten sopiva väli on esim. [0..7].
const int DISTR_UPPER_BOUND = 7;

// Vasemmanpuoleisimman sarakkeen koko, tarvitaan pelilaudan tulostamisessa.
const unsigned int LEFT_COLUMN_WIDTH = 5;


class GameBoard
{
public:
    // Rakentaja.
    GameBoard(std::vector<std::vector<Element_type>> board);

    // Tulostaa pelilaudan.
    void print() const;

    // Palauttaa kyseisessä laudan kohdassa olevan elementin.
    char get_element(int i, int j);

    // Lisää kohtaan annetun merkin.
    void add_element(int i, int j, char number);

    // Tarkastaa, onko peli voitettu, eli onko lauta täynnä.
    bool is_game_over();

    // Luo tyhjän pelilaudan.
    void create_empty_board();

    // Tarkastaa, onko annettu siemenluku peliin sopiva.
    bool check_seed(int number);

    // Tarkastaa, onko laudan vaaka- ja pystysuorilla riveillä
    // liikaa samoja numeroita.
    bool check_if_same_amount(int i, int j);

    // Tarkastaa, onko samalla vaaka- tai pystyrivillä liikaa
    // samoja numeroita peräkkäin.
    bool check_in_a_row(int i, int j);

private:
    // Lauta on vektori, joka sisältää rivimäärän verran muita vektoreita.
    std::vector<std::vector<Element_type>> board;

    // Tulostaa annetun pituisen rivin annettua merkkiä.
    void print_line(unsigned int length, char fill_character) const;

    // Ratkaisemattoman pelilaudan tuottavat siemenluvut väliltä [1..50].
    const std::vector<unsigned int> BAD_SEEDS = { 2, 8, 12, 13, 16, 20, 21, 23,
                                                  26, 29, 31, 32, 34, 41, 42,
                                                  43, 44, 46 };

    // Muuntaa annetun elementin merkkityyppiseksi.
    char element_to_char(Element_type element) const;

    // Muuntaa annetun merkin elementiksi.
    Element_type char_to_element(char character) const;
};

#endif // GAMEBOARD_HH
