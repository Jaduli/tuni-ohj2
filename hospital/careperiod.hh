/* Luokka CarePeriod
 * ----------
 * COMP.CS.110 KEVÄT 2024
 * ----------
 * Luokka, joka sisältää tiedot potilaan hoitojaksosta.
 *
 * */
#ifndef CAREPERIOD_HH
#define CAREPERIOD_HH

#include "person.hh"
#include "date.hh"
#include <string>
#include <set>

class CarePeriod
{
public:
    /**
      * @brief CarePeriod
      * @param start date given as a string (ddmmyyyy)
      * @param patient whose care period will be created
      */
    CarePeriod(const std::string& start, Person* patient);

    /**
      * @brief CarePeriod
      * @param start date given as a Date object
      * @param patient whose care period will be created
      */
    CarePeriod(const Date& start, Person* patient);

    /**
      * @brief destructor
      */
    ~CarePeriod();

    // Aloittaa hoitojakson
    void start_period();

    // Päättää hoitojakson
    void end_period(Date day);

    // Tulostaa hoitojakson aloitus- ja lopetuspäivämäärän
    // @param begin_text tulostuu ennen päivämäärän tulostusta
    void print_care_period(const std::string begin_text);

    // Tulostaa hoitojaksolle määritetyn henkilökunnan
    // @param begin_text tulostuu ennen henkilökunnan luokittelua
    void print_assigned_staff(const std::string begin_text);

    // Asettaa henkilön osaksi hoitojakson henkilökuntaa
    // @param new_staff henkilö, joka tulee asetettaa
    void assign_new_staff(Person* new_staff);

    // Palautaa vektorin hoitojaksolle asetetusta henkilökunnasta
    std::set<Person*> return_staff();

    // Palauttaa hoitojaksolle asetetun potilaan
    Person* return_patient();

private:
    Person* patient_;
    Date start_;
    Date end_;

    std::set<Person*> assigned_staff_;
};

#endif // CAREPERIOD_HH
