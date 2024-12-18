/* Ohjelman kirjoittaja
 * Pohjakoodi: TUNI COMP.CS.110
 * Kevät 2024
 *
 * Nimi: Jade Pitkänen
 * Opiskelijanumero: 151842146
 * Käyttäjätunnus: kcjapi
 * Sähköposti: jade.pitkanen@tuni.fi
 */

#include "gameboard.hh"
#include <iostream>
#include <random>

GameBoard::GameBoard() {
    init();
}

GameBoard::GameBoard(unsigned int symbols)
{
    set_size(symbols);
    init();
}

void GameBoard::set_size(unsigned int symbols)
{
    number_of_symbols_ = symbols;
    size_ = number_of_symbols_ * 2;
}

unsigned int GameBoard::get_size()
{
    return size_;
}

bool GameBoard::fill_randomly(unsigned int seed)
{
    // Checking the validity of the given seed
    for(unsigned int bad_seed : BAD_SEEDS)
    {
        if(seed == bad_seed)
        {
            std::cout << "Bad seed" << std::endl;
            return false;
        }
    }

    // Constructing a string with random symbols
    std::default_random_engine eng(seed);
    std::uniform_int_distribution<unsigned int> distr(0, DISTR_UPPER_BOUND);
    std::string input = "";

    for(unsigned int i = 0; i < size_ * size_; ++i)
    {
        switch(distr(eng))
        {
        case 0: input += '0'; break;
        case 1: input += '1'; break;
        default: input += ' '; break;
        }
    }

    // Calling fill_from_input with the constructed string (enclosed with quote
    // marks), whereupon the return value of fill_from_input will be true
    return fill_from_input('"' + input + '"');
}

bool GameBoard::fill_from_input(const std::string &input)
{
    // Checking the size_ (assuming that input is enclosed with quote marks)
    if(input.size() != size_ * size_ + 2)
    {
        std::cout << "Wrong size_ of input" << std::endl;
        return false;
    }

    // Removing quote marks
    std::string actual_input = input.substr(1, size_ * size_);

    // Checking the content and moving each element on the gameboard
    for(unsigned int i = 0; i < size_ * size_; ++i)
    {
        Element_type current_element = EMPTY;
        switch(actual_input.at(i))
        {
        case '0': current_element = ZERO; break;
        case '1': current_element = ONE; break;
        case ' ': current_element = EMPTY; break;
        default: std::cout << "Wrong character" << std::endl; return false;
        }

        board_.at(i / size_).at(i % size_ ) = current_element;
    }
    if(ok_adjacent_symbols() and ok_amount_of_symbols())
    {
        return true;
    }
    else
    {
        std::cout << "Bad input" << std::endl;
        return false;
    }
}

bool GameBoard::ok_adjacent_symbols() const
{
    return ok_adjacent_syms_in_rows(ZERO) and
           ok_adjacent_syms_in_rows(ONE) and
           ok_adjacent_syms_in_columns(ZERO) and
           ok_adjacent_syms_in_columns(ONE);
}

bool GameBoard::ok_amount_of_symbols() const
{
    unsigned int zeros_in_row = 0;
    unsigned int ones_in_row = 0;
    unsigned int zeros_in_column = 0;
    unsigned int ones_in_column = 0;

    for(unsigned int i = 0; i < board_.size(); ++i)
    {
        for(unsigned int j = 0; j < board_.at(i).size(); ++j)
        {
            if(board_.at(i).at(j) == ZERO)
            {
                ++zeros_in_row;
            }
            else if(board_.at(i).at(j) == ONE)
            {
                ++ones_in_row;
            }
            if(board_.at(j).at(i) == ZERO)
            {
                ++zeros_in_column;
            }
            else if(board_.at(j).at(i) == ONE)
            {
                ++ones_in_column;
            }
        }
        if(zeros_in_row > number_of_symbols_ or
           ones_in_row > number_of_symbols_ or
           zeros_in_column > number_of_symbols_ or
           ones_in_column > number_of_symbols_)
        {
            return false;
        }
        zeros_in_row = ones_in_row = zeros_in_column = ones_in_column = 0;
    }
    return true;
}

bool GameBoard::add_symbol(unsigned int x, unsigned int y, char symbol_char)
{
    if(board_.at(y).at(x) != EMPTY)
    {
        //std::cout << "Not empty: ";
        return false;
    }

    Element_type elem = EMPTY;
    switch(symbol_char)
    {
    case '0': elem = ZERO; break;
    case '1': elem = ONE; break;
    default: return false; // This should never happen, checked in main.cpp
    }

    // Adding the symbol and checking if everything is still fine
    board_.at(y).at(x) = elem;
    if(ok_adjacent_symbols() and
       ok_amount_of_symbols())
    {
        return true;
    }
    // If all was not fine after adding, making the index empty again
    else
    {
        board_.at(y).at(x) = EMPTY;
        return false;
    }
}

bool GameBoard::is_game_over() const
{
    for(unsigned int i = 0; i < board_.size(); ++i)
    {
        for(unsigned int j = 0; j < board_.at(i).size(); ++j)
        {
            if(board_.at(i).at(j) == EMPTY)
            {
                return false;
            }
        }
    }
    return true;
}

void GameBoard::print() const
{
    // Tulostetaan yläreuna
    // Printing upper border
    print_line(LEFT_COLUMN_WIDTH + 1 + 2 * size_ + 1, '=');

    // Tulostetaan otsikkorivi
    // Printing title row
    std::cout << "|   | ";
    for(unsigned int i = 0; i < size_; ++i)
    {
        std::cout << i + 1 << " ";
    }
    std::cout << "|" << std::endl;

    // Tulostetaan viiva otsikkorivin alle
    // Printing line after the title row
    print_line(LEFT_COLUMN_WIDTH + 1 + 2 * size_ + 1, '-');

    // Tulostetaan pelilaudan varsinainen sisältö
    // Printing the actual content of the gameboard
    for(unsigned int i = 0; i < size_; ++i)
    {
        std::cout << "| " << i + 1 << " | ";
        for(unsigned int j = 0; j < size_; ++j)
        {
            switch(board_.at(i).at(j))
            {
            case ZERO: std::cout << "0 "; break;
            case ONE: std::cout << "1 "; break;
            case EMPTY: std::cout << "  "; break;
            }
        }
        std::cout << "|" << std::endl;
    }

    // Tulostetaan alareuna
    // Printing lower border
    print_line(LEFT_COLUMN_WIDTH + 1 + 2 * size_ + 1, '=');
}

std::vector<std::vector<Element_type> > GameBoard::get_board()
{
    return board_;
}

void GameBoard::init()
{
    std::vector<Element_type> row(size_, EMPTY);
    for(unsigned int i = 0; i < size_; ++i)
    {
        board_.push_back(row);
    }
}

void GameBoard::print_line(unsigned int length, char fill_character) const
{
    for(unsigned int i = 0; i < length; ++i)
    {
        std::cout << fill_character;
    }
    std::cout << std::endl;
}

bool GameBoard::ok_adjacent_syms_in_rows(Element_type elem) const
{
    for(unsigned int i = 0; i < board_.size(); ++i)
    {
        for(unsigned int j = 0; j < board_.at(i).size() - 2; ++j)
        {
            if(board_.at(i).at(j) == elem and
               board_.at(i).at(j + 1) == elem and
               board_.at(i).at(j + 2) == elem)
            {
                return false;
            }
        }
    }
    return true;
}

bool GameBoard::ok_adjacent_syms_in_columns(Element_type elem) const
{
    for(unsigned int i = 0; i < board_.size() - 2; ++i)
    {
        for(unsigned int j = 0; j < board_.at(i).size(); ++j)
        {
            if(board_.at(i).at(j) == elem and
               board_.at(i + 1).at(j) == elem and
               board_.at(i + 2).at(j) == elem)
            {
                return false;
            }
        }
    }
    return true;
}
