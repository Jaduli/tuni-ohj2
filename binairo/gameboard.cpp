/* Ohjelman kirjoittaja
* Nimi: Jade Pitkänen
* Opiskelijanumero: 151842146
* Käyttäjätunnus: kcjapi
* E-Mail: jade.pitkanen@tuni.fi
*/

#include "gameboard.hh"
#include <iostream>
#include <random>
#include <algorithm>

GameBoard::GameBoard(std::vector<std::vector<Element_type>> initialBoard)
    : board(initialBoard)
{  
}

void GameBoard::print() const
{
    // Tulostetaan yläreuna
    print_line(LEFT_COLUMN_WIDTH + 1 + 2 * SIZE + 1, '=');

    // Tulostetaan otsikkorivi
    std::cout << "|   | ";
    for(unsigned int i = 0; i < SIZE; ++i)
    {
        std::cout << i + 1 << " ";
    }
    std::cout << "|" << std::endl;

    // Tulostetaan viiva otsikkorivin alle
    print_line(LEFT_COLUMN_WIDTH + 1 + 2 * SIZE + 1, '-');

    // Tulostetaan pelilaudan varsinainen sisältö
    for(unsigned int i = 0; i < SIZE; ++i)
    {
        std::cout << "| " << i + 1 << " | ";
        for(unsigned int j = 0; j < SIZE; ++j)
        {

            // Tulostaa pelilaudan alkion (i, j)

            Element_type element = board.at(i).at(j);
            std::cout << element_to_char(element) << " ";
        }
        std::cout << "|" << std::endl;
    }

    // Tulostetaan alareuna
    print_line(LEFT_COLUMN_WIDTH + 1 + 2 * SIZE + 1, '=');
}

void GameBoard::print_line(unsigned int length, char fill_character) const
{
    for(unsigned int i = 0; i < length; ++i)
    {
        std::cout << fill_character;
    }
    std::cout << std::endl;
}

bool GameBoard::is_game_over() {
    // Peli on ohi, jos laudassa ei ole tyhjiä elementtejä.

    for (int i=0; i < SIZE; ++i) {
        for (int j=0; j < SIZE; ++j) {
            Element_type element = board.at(i).at(j);
            if (element == EMPTY){
                return false;
            }
        }
    }
    return true;
}

void GameBoard::create_empty_board() {
    // Lauta on vektori, joka sisältää toisia vektoreita,
    // jotka toimivat riveinä.

    for (int i = 0; i < SIZE; ++i) {
        board.push_back(std::vector<Element_type>(SIZE, EMPTY));
    }
}

void GameBoard::add_element(int i, int j, char number) {

    board.at(j).at(i) = char_to_element(number);
}

char GameBoard::element_to_char(Element_type element) const {
    if (element == ZERO) {
        return '0';
    }
    else if (element == ONE) {
        return '1';
    }
    else {
        return ' ';
    }
}

Element_type GameBoard::char_to_element(char character) const {
    if (character == '0') {
        return ZERO;
    }
    else if (character == '1') {
        return ONE;
    }
    else {
        return EMPTY;
    }
}

char GameBoard::get_element(int i, int j) {
    return board.at(j).at(i);
}

bool GameBoard::check_seed(int number) {
    if (std::find(BAD_SEEDS.begin(), BAD_SEEDS.end(), number) == BAD_SEEDS.end()) {
        return true;
    }
    else {
        return false;
    }

}

bool GameBoard::check_if_same_amount(int x, int y) {
    // Vaaka- tai pystyrivillä ei saa olla yli puolet samaa numeroa.

    int x_counter = 0;
    int y_counter = 0;

    Element_type element = board.at(y).at(x);

    for (int j=0; j < SIZE; ++j) {
        Element_type x_element = board.at(j).at(x);

        if (x_element == element) {
            ++x_counter;

            if (x_counter > SIZE/2) {
                return false;


            }
        }
    }

    for (int i=0; i < SIZE; ++i) {
        Element_type y_element = board.at(y).at(i);

        if (y_element == element) {
            ++y_counter;

            if (y_counter > SIZE/2) {
                return false;



            }
        }
    }

    return true;
}

bool GameBoard::check_in_a_row(int x, int y) {
    // Vaaka- tai pystyrivillä ei saa olla kahta enempää samaa merkkiä peräkkäin.

    for (int j=0; j < SIZE-2; ++j) {

        Element_type x_element = board.at(j).at(x);

        if (x_element != EMPTY) {
            Element_type next_x_element = board.at(j+1).at(x);
            Element_type third_x_element = board.at(j+2).at(x);

            if (next_x_element == x_element and next_x_element == third_x_element) {
                return false;

            }
        }
    }

    for (int i=0; i < SIZE-2; ++i) {
        Element_type y_element = board.at(y).at(i);

        if (y_element != EMPTY) {
            Element_type next_y_element = board.at(y).at(i+1);
            Element_type third_y_element = board.at(y).at(i+2);


            if (next_y_element == y_element and next_y_element == third_y_element) {
                return false;

            }
        }
    }

    return true;
}
