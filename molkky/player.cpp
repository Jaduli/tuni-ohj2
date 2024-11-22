#include "player.hh"
#include <string>
#include <iostream>

Player::Player(const std::string& name):
    name_(name){

}

std::string Player::get_name() const {
    return name_;
}

int Player::get_points() const {
    return points_;
}

bool Player::has_won() const {
    return points_ == 50;
}

void Player::add_points(int amount) {
    points_ += amount;

    if (points_ > 50) {
        points_ = 25;
        std::cout << name_ << " gets penalty points!" << std::endl;
    }
}
