#include "queue.hh"
#include <iostream>

using namespace std;

// Implement the member functions of Queue here

Queue::Queue(unsigned int cycle): first_(nullptr), last_(nullptr) {
    cycle_ = cycle;
}

void Queue::enqueue(string const& reg) {
    Vehicle* new_vehicle = new Vehicle{reg, nullptr};

    if (is_green_) {
        cout << "GREEN: The vehicle " << new_vehicle->reg_num << " need not stop to wait" << endl;
        delete new_vehicle;
    }
    else if (first_ == nullptr) {
        first_ = new_vehicle;
        last_ = new_vehicle;
    }
    else {
        last_->next = new_vehicle;
        last_ = new_vehicle;
    }
}

bool Queue::dequeue() {
    if (first_ == nullptr) {
        return false;
    }
    Vehicle* to_remove = first_;

    if (first_ == last_) {
        first_ = nullptr;
        last_ = nullptr;
    }
    else {
        first_ = first_->next;
    }

    delete to_remove;

    return true;
}

void Queue::print() const {
    Vehicle* print_car = first_;
    if (is_green_) {
        cout << "GREEN: ";
        if (first_ == nullptr) {
            cout << "No vehicles waiting in traffic lights" << endl;
        }

        else {
            cout << "Vehicle(s) ";
            unsigned int count = 1;
            while (print_car != nullptr && count <= cycle_) {
                cout << print_car->reg_num << " ";
                print_car = print_car->next;
                ++count;
            }
            cout << "can go on" << endl;
        }
    }
    else {
        cout << "RED: ";
        if (first_ == nullptr) {
            cout << "No vehicles waiting in traffic lights" << endl;
        }
        else {
            cout << "Vehicle(s) ";
            while (print_car != nullptr) {
                cout << print_car->reg_num << " ";
                print_car = print_car->next;
            }
            cout << "waiting in traffic lights" << endl;
        }
    }
}

void Queue::switch_light() {

    if (is_green_) {
        is_green_ = false;
        print();

    }
    else {
        is_green_ = true;
        print();

        if (first_ != nullptr) {
            unsigned int count = 0;

            while (count < cycle_) {
                if (dequeue()) {
                    is_green_ = false;
                }
                ++count;
            }
        }
    }
}

void Queue::reset_cycle(unsigned int cycle) {
    cycle_ = cycle;
}

Queue::~Queue() {
    while (first_ != nullptr) {
        Vehicle* removing = first_;

        first_ = first_->next;

        delete removing;
    }
}
