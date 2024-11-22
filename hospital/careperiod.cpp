#include "careperiod.hh"
#include "utils.hh"
#include <iostream>

CarePeriod::CarePeriod(const std::string& start, Person* patient):
    patient_(patient), start_(start)
{
}

CarePeriod::CarePeriod(const Date &start, Person* patient):
    patient_(patient), start_(start)
{
}

CarePeriod::~CarePeriod()
{
}

void CarePeriod::start_period()
{
    start_ = utils::today;
}

void CarePeriod::end_period(Date day)
{
    end_ = day;
}

void CarePeriod::print_care_period(const std::string begin_text)
{
    std::cout << begin_text;
    start_.print();
    std::cout << " - ";

    // Tulostetaan loppupäivämäärä, jos hoitojakso on päättynyt
    if (!end_.is_default()) {
        end_.print();
    }
    std::cout << std::endl;
}

void CarePeriod::print_assigned_staff(const std::string begin_text)
{
    std::cout << begin_text << "Staff: ";
    if (assigned_staff_.empty())
    {
        std::cout << "None" << std::endl;
        return;
    }

    for(const auto& staff : assigned_staff_)
    {
        staff->print_id();
        std::cout << " ";
    }
    std::cout << std::endl;
}

void CarePeriod::assign_new_staff(Person* new_staff)
{
    assigned_staff_.insert(new_staff);
}

std::set<Person*> CarePeriod::return_staff()
{
    return assigned_staff_;
}

Person* CarePeriod::return_patient()
{
    return patient_;
}




