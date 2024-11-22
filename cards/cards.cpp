#include "cards.hh"

using namespace std;

Cards::Cards(): top_(nullptr) {
}

void Cards::add(int id) {
    Card_data* new_card = new Card_data{id, nullptr};

    if (top_ == nullptr) {
        top_ = new_card;
    }
    else {
        new_card->next = top_;
        top_ = new_card;
    }
}

Card_data* Cards::get_topmost() {
    return top_;
}

void Cards::print_from_top_to_bottom(ostream& s) {
    Card_data* card_to_be_printed = top_;
    int running_number = 1;

    while ( card_to_be_printed != nullptr ) {
       s << running_number << ": " << card_to_be_printed->data << endl;
       ++running_number;
       card_to_be_printed = card_to_be_printed->next;
    }
}

bool Cards::remove(int &id) {
    if (top_ == nullptr) {
        return false;
    }

    Card_data* card_to_remove = top_;

    id = card_to_remove->data;

    if ( top_ != nullptr ) {
       top_ = top_->next;
    }

    delete card_to_remove;

    return true;
}

bool Cards::bottom_to_top() {
    if (top_ == nullptr or top_->next == nullptr) {
        return false;
    }

    Card_data* current = top_;
    Card_data* previous = nullptr;

    while (current->next != nullptr) {
        previous = current; // 2. viimeinen
        current = current->next; // viimeinen
    }

    previous->next = nullptr;

    current->next = top_;
    top_ = current;

    return true;
}

bool Cards::top_to_bottom() {
    if (top_ == nullptr or top_->next == nullptr) {
        return false;
    }

    Card_data* current = top_;
    Card_data* second = top_->next;

    while (current->next != nullptr) {
        current = current->next; // viimeinen
    }

    current->next = top_;
    top_->next = nullptr;
    top_ = second;

    return true;
}

void Cards::print_from_bottom_to_top(std::ostream& s) {  
    Card_data* current = top_;
    Card_data* previous = nullptr;
    Card_data* next = nullptr;

    while (current != nullptr) {
        next = current->next;
        current->next = previous;
        previous = current;
        current = next;
    }

    int i = 1;

    top_ = previous;

    while (previous != nullptr) {
        s << i << ": " << previous->data << endl;

        ++i;
        previous = previous->next;
    }
}

Cards::~Cards() {
    while(top_ != nullptr) {
        Card_data* card_to_delete = top_;

        top_ = top_->next;
        delete card_to_delete;
    }
}
