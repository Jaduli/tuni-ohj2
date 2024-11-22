#include "hospital.hh"
#include "utils.hh"
#include <iostream>
#include <string>

Hospital::Hospital()
{
}

Hospital::~Hospital()
{
    // Vapautetaan henkilökunta
    for (std::map<std::string, Person*>::iterator
         iter = staff_.begin();
         iter != staff_.end();
         ++iter)
    {
        delete iter->second;
    }
    // Vapautetaan asiakkaat
    for (std::map<std::string, Person*>::iterator
         iter = all_patients_.begin();
         iter != all_patients_.end();
         ++iter)
    {
        delete iter->second;
    }

    // Vapautetaan hoitojaksot
    for (CarePeriod* period : care_periods_) {
        delete period;
    }
}

void Hospital::set_date(Params params)
{
    std::string day = params.at(0);
    std::string month = params.at(1);
    std::string year = params.at(2);
    if( not utils::is_numeric(day, false) or
        not utils::is_numeric(month, false) or
        not utils::is_numeric(year, false) )
    {
        std::cout << NOT_NUMERIC << std::endl;
        return;
    }
    utils::today.set(stoi(day), stoi(month), stoi(year));
    std::cout << "Date has been set to ";
    utils::today.print();
    std::cout << std::endl;
}

void Hospital::advance_date(Params params)
{
    std::string amount = params.at(0);
    if( not utils::is_numeric(amount, true) )
    {
        std::cout << NOT_NUMERIC << std::endl;
        return;
    }
    utils::today.advance(stoi(amount));
    std::cout << "New date is ";
    utils::today.print();
    std::cout << std::endl;
}

void Hospital::recruit(Params params)
{
    std::string specialist_id = params.at(0);
    if( staff_.find(specialist_id) != staff_.end() )
    {
        std::cout << ALREADY_EXISTS << specialist_id << std::endl;
        return;
    }
    Person* new_specialist = new Person(specialist_id);
    staff_.insert({specialist_id, new_specialist});
    std::cout << STAFF_RECRUITED << std::endl;
}

void Hospital::print_all_staff(Params)
{
    if( staff_.empty() )
    {
        std::cout << "None" << std::endl;
        return;
    }
    for( std::map<std::string, Person*>::const_iterator iter
         = staff_.begin();
         iter != staff_.end();
         ++iter )
    {
        std::cout << iter->first << std::endl;
    }
}

void Hospital::add_medicine(Params params)
{
    std::string medicine = params.at(0);
    std::string strength = params.at(1);
    std::string dosage = params.at(2);
    std::string patient = params.at(3);
    if( not utils::is_numeric(strength, true) or
        not utils::is_numeric(dosage, true) )
    {
        std::cout << NOT_NUMERIC << std::endl;
        return;
    }
    std::map<std::string, Person*>::const_iterator
            patient_iter = current_patients_.find(patient);
    if( patient_iter == current_patients_.end() )
    {
        std::cout << CANT_FIND << patient << std::endl;
        return;
    }
    patient_iter->second->add_medicine(medicine, stoi(strength), stoi(dosage));
    std::cout << MEDICINE_ADDED << patient << std::endl;
}

void Hospital::remove_medicine(Params params)
{
    std::string medicine = params.at(0);
    std::string patient = params.at(1);
    std::map<std::string, Person*>::const_iterator
            patient_iter = current_patients_.find(patient);
    if( patient_iter == current_patients_.end() )
    {
        std::cout << CANT_FIND << patient << std::endl;
        return;
    }
    patient_iter->second->remove_medicine(medicine);
    std::cout << MEDICINE_REMOVED << patient << std::endl;
}

void Hospital::enter(Params params)
{
    std::string patient = params.at(0);
    std::map<std::string, Person*>::const_iterator
            current_iter = current_patients_.find(patient);

    // Tarkistetaan, onko henkilö jo potilaana
    if( current_iter != current_patients_.end() )
    {
        std::cout << ALREADY_EXISTS << patient << std::endl;
        return;
    }

    Person* new_patient;

    // Jos henkilö on ollut potilaana aikaisemmin, palautetaan
    // hänen tiedot. Muuten lisätään uusi potilas.
    std::map<std::string, Person*>::const_iterator
            all_iter = all_patients_.find(patient);

    if (all_iter != all_patients_.end()) {
        new_patient = all_iter->second;
        current_patients_.insert({patient, new_patient});
    }
    else {
        new_patient = new Person(patient);
        current_patients_.insert({patient, new_patient});
        all_patients_.insert({patient, new_patient});
    }
    std::cout << PATIENT_ENTERED << std::endl;

    // Luodaan uusi hoitojakso
    CarePeriod* new_care_period = new CarePeriod(utils::today, new_patient);

    care_periods_.push_back(new_care_period);
}

void Hospital::leave(Params params)
{
    std::string patient = params.at(0);

    // Tarkistetaan, onko potilas sairaalassa
    std::map<std::string, Person*>::const_iterator
            patient_iter = current_patients_.find(patient);

    if( patient_iter == current_patients_.end() )
    {
        std::cout << CANT_FIND << patient << std::endl;
        return;
    }

    current_patients_.erase(patient_iter);

    // Lopetetaan nykyinen hoitojakso
    for (auto it = care_periods_.rbegin(); it != care_periods_.rend(); ++it) {
        CarePeriod* period = *it;

        if (period->return_patient()->get_id() == patient) {
            std::cout << PATIENT_LEFT << std::endl;
            period->end_period(utils::today);
            return;
        }
    }
}

void Hospital::assign_staff(Params params)
{
    std::string staff = params.at(0);
    std::string patient = params.at(1);

    // Tarkistetaan, onko henkilökunta ja potilas olemassa
    auto find_staff = staff_.find(staff);
    auto find_patient = current_patients_.find(patient);

    if (find_staff == staff_.end()) {
        std::cout << CANT_FIND << staff << std::endl;
        return;
    }
    else if (find_patient == current_patients_.end()) {
        std::cout << CANT_FIND << patient << std::endl;
        return;
    }
    // Käydään hoitojaksovektori takaperin läpi, jotta löydetään nykyinen
    // eli viimeisin hoitojakso
    for (auto it = care_periods_.rbegin(); it != care_periods_.rend(); ++it) {
        CarePeriod* period = *it;

        if (period->return_patient()->get_id() == patient) {
            // Asetetaan henkilökunta potilaan nykyiselle hoitojaksolle
            period->assign_new_staff(find_staff->second);

            std::cout << STAFF_ASSIGNED << patient << std::endl;
            return;
        }
    }
}

void Hospital::print_patient_info(Params params)
{
    std::string patient = params.at(0);

    auto patient_iter = all_patients_.find(patient);

    if (patient_iter == all_patients_.end()) {
        std::cout << CANT_FIND << patient << std::endl;
        return;
    }

    // Tulostetaan hoitojaksojen ajankohdat ja asetettu henkilökunta
    for (CarePeriod* period : care_periods_) {
        if (period->return_patient()->get_id() == patient) {
            period->print_care_period("* Care period: ");
            period->print_assigned_staff("  - ");
        }
    }

    // Tulostetaan asiakkaan lääkkeet
    std::cout << "* Medicines:";
    patient_iter->second->print_medicines("  - ");
}


void Hospital::print_care_periods(Params params)
{
    std::string staff = params.at(0);

    auto staff_iter = staff_.find(staff);

    if (staff_iter == staff_.end()) {
        std::cout << CANT_FIND << staff << std::endl;
        return;
    }
    // Asetetaan totuusarvo sille, löytyikö henkilökunnalle asetettuja
    // potilaita
    bool found_patient = false;

    // Tutkitaan läpi henkilökuntavektori jokaiselle potilaalle
    for (CarePeriod* period : care_periods_) {
        std::set<Person*> period_staff = period->return_staff();

        for (Person* staff_member : period_staff) {
            if (staff_member->get_id() == staff) {
                std::string patient = period->return_patient()->get_id();

                period->print_care_period("");
                std::cout << "* Patient: " << patient << std::endl;

                found_patient = true;
            }
        }
    }
    if (!found_patient) {
        std::cout << "None" << std::endl;
    }
}

void Hospital::print_all_medicines(Params)
{
    std::map<std::string, std::vector<std::string>> prescriptions;

    if (care_periods_.empty()) {
        std::cout << "None" << std::endl;
        return;
    }

    // Käydään läpi kaikille asiakkaille lisätyt lääkkeet
    for (std::map<std::string, Person*>::const_iterator iter
        = all_patients_.begin();
        iter != all_patients_.end();
        ++iter) {
        Person* patient = iter->second;

        std::vector<std::string> patient_medicines = patient->get_medicines();

        for (std::string medicine : patient_medicines) {
            if (prescriptions.find(medicine) != prescriptions.end()) {
                prescriptions.at(medicine).push_back(patient->get_id());
            }
            else {
                prescriptions.insert(std::make_pair(medicine,
                              std::vector<std::string> {patient->get_id()}));
            }
        }
    }
    if (prescriptions.empty()) {
        std::cout << "None" << std::endl;
        return;
    }

    for (const auto& pair : prescriptions) {
        std::cout << pair.first << " prescribed for" << std::endl;
        for(std::string name : pair.second) {
            std::cout << "* " << name << std::endl;
        }
    }
}

void Hospital::print_all_patients(Params)
{
    if (all_patients_.empty())
    {
        std::cout << "None" << std::endl;
        return;
    }
    for (std::map<std::string, Person*>::const_iterator iter
        = all_patients_.begin();
        iter != all_patients_.end();
        ++iter) {
        std::cout << iter->first << std::endl;

        std::vector<std::string> patient_info;
        patient_info.push_back(iter->first);

        print_patient_info(patient_info);
    }
}

void Hospital::print_current_patients(Params)
{
    if( current_patients_.empty() )
    {
        std::cout << "None" << std::endl;
        return;
    }
    for (std::map<std::string, Person*>::const_iterator iter
         = current_patients_.begin();
         iter != current_patients_.end();
         ++iter ) {

        std::string patient = iter->first;

        std::cout << patient << std::endl;

        std::vector<std::string> patient_info;
        patient_info.push_back(patient);

        print_patient_info(patient_info);
    }
}

