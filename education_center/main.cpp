/* Projekti: Kansalaisopisto
 *
 * Ohjelma, joka lukee annetun kurssitietoja sisältävän tekstitiedoston ja
 * tallentaa tiedostossa olevien tietojen perusteella kurssien tiedot,
 * eli paikkakunnan, teeman, nimen sekä osallistujamäärän.
 *
 * Annetun tiedoston tiedot tulee olla rivittäin muodossa
 * paikkakunta;teema;nimi;osallistujamäärä
 *
 * Tallennetut tiedot voidaan tulostaa seuraavia komentoja käyttäen:
 *
 * locations
 * - tulostaa kaikki tallennetut paikkakunnat.
 *
 * available
 * - tulostaa kaikilta paikkakunnilta kurssit, jotka eivät ole täynnä,
 * ja niiden teemat.
 *
 * courses (paikkakunta) (teema)
 * - tulostaa annetun paikkakunnan teemaan kuuluvat kurssit sekä niiden
 * osallistujamäärän.
 *
 * themes_in_location (paikkakunta)
 * - tulostaa kaikki teemat annetussa paikkakunnassa.
 *
 * courses_in_theme
 * - tulostaa kaikilta paikkakunnilta annettuun teemaan kuuluvat kurssit.
 *
 * favorite_theme
 * - tulostaa kaikkien kurssien perusteella suosituimman teeman ja sen
 * osallistujamäärän.
 *
 * Ohjelman kirjoittaja
 * Nimi: Jade Pitkänen
 * Opiskelijanumero: 151842146
 * Käyttäjätunnus: kcjapi
 * E-Mail: jade.pitkanen@tuni.fi
 */

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <algorithm>

// Tietovarastossa käytettävä struct
struct Course {
    std::string name;
    std::string theme;
    int enrollments;
};

// Ohjelman komennot
const std::vector<std::string> commands = {"themes_in_location",
            "courses_in_theme", "quit", "locations", "courses",
                                     "available", "favorite_theme"};

// Yksittäiseen kurssiin ilmoittautuneiden maksimimäärä.
const int max_enrollment = 50;

// Tarkastaa, onko syöte ohjelmaan sopiva.
bool input_check(std::map<std::string, std::vector<Course>>& database,
                 std::vector<std::string>& input_vector) {

    std::string command = input_vector.at(0);

    // Tarkastatetaan, onko komento olemassa.
    if (std::find(commands.begin(), commands.end(), command)
            == commands.end()) {
        std::cout << "Error: Unknown command: " <<
                     input_vector.at(0) << std::endl;
        return false;
    }

    // Seuraaville komennoille ei tarvitse lisäarvoja
    if (command == "locations" or command == "quit" or
                command == "available" or command == "favorite_theme") {
            return true;
    }

    // Käytetään check-nimistä totuusarvoa muiden komentojen tarkistuksessa.
    bool check = false;

    // themes_in_location -komennolle tulee olla annettuna paikka.
    if (command == "themes_in_location") {
        if (size(input_vector) != 2) {
            std::cout << "Error: error in command themes_in_location"
             << std::endl;
            return false;
        }

        for (auto data : database) {
            // Jos annettu paikka löytyy tietovarastosta, komento on
            // validi.
            if (input_vector.at(1) == data.first) {
                check = true;
            }
        }
        if (!check) {
            std::cout << "Error: unknown location" << std::endl;
        }
    }

    // courses_in_theme -komennolle tulee olla annettuna teema.
    else if (command == "courses_in_theme") {
        if (size(input_vector) != 2) {
            std::cout << "Error: error in command courses_in_theme"
             << std::endl;
            return false;
        }

        for (auto data : database) {
            for (auto course : data.second) {
                if (input_vector.at(1) == course.theme) {
                    // Jos annettu teema löytyy tietovarastosta,
                    // komento on validi.
                    check = true;
                }
            }
        }
        if (!check) {
            std::cout << "Error: unknown theme" << std::endl;
        }
    }

    // courses-komennolle tulee olla annettuna paikka sekä teema.
    else if(command == "courses") {
        if (size(input_vector) != 3) {
            std::cout << "Error: error in command courses" << std::endl;
            return false;
        }
        // Tarkastetaan annettu paikka.
        for (auto data : database) {
            if (input_vector.at(1) == data.first) {
                check = true;
            }
        }
        if (!check) {
            std::cout << "Error: unknown location name" << std::endl;
            return false;
        }

        // Resetoidaan check teeman tarkistamista varten.
        check = false;

        for (auto data : database) {
            for (auto course : data.second) {
                if (input_vector.at(2) == course.theme) {
                    check = true;
                }
            }
        }
        if (!check) {
            std::cout << "Error: unknown theme" << std::endl;
        }
    }
    return check;
}

// Tulostaa tietovaraston paikkakunnat.
void print_locations(std::map<std::string, std::vector<Course>>& database) {

    for (auto data : database) {
        std::cout << data.first << std::endl;
    }
}

// Tulostaa kaikki kurssit, jotka ovat vapaana, eli ilmoittautuneita
// on alle maksimin.
void available(std::map<std::string, std::vector<Course>>& database) {
    for (auto data : database) {
        for (auto course : data.second) {
            if (course.enrollments < max_enrollment) {
                std::cout << data.first << " : " << course.theme
                          << " : " << course.name << std::endl;
            }
        }
    }
}

// Tulostaa kaikki teemat, jotka löytyvät annetusta paikkakunnasta.
void themes_in_location(std::map<std::string, std::vector<Course>>& database,
                        std::string& location) {
    // Luodaan vektori jo tulostetuille teemoille.
    std::vector<std::string> printed_themes;

    for (auto data : database) {
        for (auto course : data.second) {
            // Luodaan totuusarvo, jolla vältetään saman teeman
            // uudelleentulostus.
            bool print = true;

            if (data.first == location) {
                for (std::string themes : printed_themes) {
                    if (themes == course.theme) {
                        print = false;
                    }
                }
                if (print) {
                    std::cout << course.theme << std::endl;
                    printed_themes.push_back(course.theme);
                }
            }
        }
    }
}

// Tulostaa kaikkien paikkakuntien kursseilta löytyvät teemat.
void courses_in_theme(std::map<std::string,
                      std::vector<Course>>& database, std::string& theme) {
    // Luodaan vektori kursseille.
    std::vector<std::string> found_courses;

    for (auto data : database) {
        for (auto course : data.second) {
            // Sama teema lisätään vain kerran found_courses vektoriin.
            bool add_course = true;

            if (course.theme == theme) {
                for (std::string existing_course : found_courses) {
                    if (existing_course == course.name) {
                        add_course = false;
                    }
                }
                if (add_course) {
                    found_courses.push_back(course.name);
                }
            }
        }
    }
    // Tulostetaan teemat.
    std::sort(found_courses.begin(), found_courses.end());
    for (std::string course_in : found_courses) {
        std::cout << course_in << std::endl;
    }
}

// Tulostaa kaikkien kurssien perusteella suosituimman teeman ja sen
// osallistujamäärän.
void favorite_theme(std::map<std::string, std::vector<Course>>& database) {
    // Luodaan map, jota käytetään teemojen osallistujamäärän laskemiseen,
    // sekä vektori, joka sisältää suosituimman kurssin tai kurssit.
    std::map<std::string, int> enrollment_counter;
    std::vector<std::string> popular_courses;

    for (auto data : database) {
        for (auto course : data.second) {
            enrollment_counter[course.theme] += course.enrollments;
        }
    }

    // Luodaan laskuri suurimmalle osallistujamäärälle.
    int most_enrollments = 0;

    for (auto data : enrollment_counter) {
        // Jos kyseisellä teemalla on sama osallistujamäärä kuin
        // suositummalla, molemmat tallennetaan suosituimmiksi.
        if (data.second == most_enrollments) {
            popular_courses.push_back(data.first);
        }
        // Jos osallistujia on kyseisellä teemalla enemmän kuin aikasemmin
        // suosituimmalla, tallennetaan vain kyseinen teema suosituimmaksi.
        else if (data.second > most_enrollments) {
            most_enrollments = data.second;
            popular_courses.clear();
            popular_courses.push_back(data.first);
        }

    }
    // Jos osallistujia on, tulostetaan suosituin kurssi tai kurssit.
    if (most_enrollments == 0) {
        std::cout << "No enrollments" << std::endl;
    }
    else {
        std::cout << most_enrollments << " enrollments in themes" << std::endl;
        for (std::string themes : popular_courses) {
            std::cout << "--- " << themes << std::endl;
        }
    }
}

// Tulostaa annetun paikkakunnan ja teeman kurssit sekä niiden
// osallistujamäärän.
void courses(std::map<std::string, std::vector<Course>>& database,
             std::string& location, std::string& theme) {
    // Luodaan map-rakenne tulostettaville kursseille ja osallistujamäärille.
    std::map<std::string, int> courses;

    for (auto data : database) {
        for (auto course : data.second) {
            if (data.first == location and course.theme == theme) {
                courses[course.name] = course.enrollments;
            }
        }
    }

    // Tulostetaan kurssit ja osallistujamäärät.
    for (auto data : courses) {
        // Jos kurssi on täynnä, tulostuu "full".
        if (data.second == max_enrollment) {
            std::cout << data.first << " --- full" << std::endl;
        }
        else {
            std::cout << data.first << " --- " << data.second
                      << " enrollments" << std::endl;
        }
    }
}

// Jakaa merkkijonon annetun jakomerkin perusteella vektoriksi.
std::vector<std::string> split(std::string line, char separator) {
    std::vector<std::string> new_vector;

    size_t i = 0;
    while (i < line.length()) {
        if (line.at(i) == separator) {
            std::string new_line = line.substr(0, i);

            if (!new_line.empty()) {
                new_vector.push_back(new_line);
            }

            line = line.substr(i + 1);
            i = 0;
        } else {
            ++i;
        }
    }

    // Lisätään vielä jäljelle jäänyt merkkijono.
    if (!line.empty()) {
        new_vector.push_back(line);
    }

    return new_vector;
}

// Järjestää annetun tietovaraston aakkosjärjestykseen sort-komentoa
// hyödyntäen.
void sort_database(std::map<std::string, std::vector<Course>>& database) {
    for (auto& center : database) {
        std::sort(center.second.begin(), center.second.end(),
            [](const Course& a, const Course& b) {

            if (a.theme != b.theme) {
                return a.theme < b.theme;
            }
            if (a.name != b.name) {
                return a.name < b.name;
            }
            return false;
        });
    }

}

// Luo tietovaraston tekstitiedoston perusteella.
std::pair<bool, std::map<std::string, std::vector<Course>>> create_database() {

    std::map<std::string, std::vector<Course>> center_data;

    // Luetaan tiedosto ja muodostetaan siitä tietovarasto.
    std::string file_name;

    std::cout << "Input file: ";
    std::getline(std::cin, file_name);

    std::ifstream input_file(file_name);

    if (not input_file) {
        std::cout << "Error: the input file cannot be opened" << std::endl;
        return {false, center_data};
    }

    std::string row;

    while (getline(input_file, row)) {

        std::vector<std::string> line = split(row, ';');

        // Jos tiedoston rivissä ei ole tarpeeksi tietoja,
        // tietovarastoa ei voida luoda.
        if (size(line) != 4) {
            std::cout << "Error: empty field" << std::endl;
            return {false, center_data};
        }

        std::string location = line.at(0);
        std::string theme = line.at(1);
        std::string name = line.at(2);
        std::string enrollment = line.at(3);

        if (enrollment == "full") {
            enrollment = std::to_string(max_enrollment);
        }

        Course course_info = {name, theme, stoi(enrollment)};

        // Jos kurssin paikka, nimi ja teema ovat samoja, vain olemassa
        // olevan kurssin kävijämäärää muokataan. Muuten kurssi lisätään
        // tietovarastoon.
        bool added_check = false;

        auto find_location = center_data.find(location);

        if (find_location != center_data.end()) {
            for (auto& data : center_data) {
                if (data.first == location) {
                    for (auto& course : data.second) {
                        if (course.theme == theme and course.name == name) {
                            course.enrollments = stoi(enrollment);
                            added_check = true;
                        }
                    }
                }
            }
        }
        if (!added_check) {
            center_data[location].push_back(course_info);
        }
    }
    return {true, center_data};
}

// Muokkaa input-vektorin teeman yhdeksi alkioksi.
void input_theme(std::vector<std::string>& input_vector) {
    std::string theme = input_vector.at(2);

    // Teema voi koostua useammasta sanasta.
    for (size_t i = 3; i < input_vector.size(); ++i) {
        theme += " " + input_vector.at(i);
    }

    // Poistetaan mahdolliset lainausmerkit teemasta.
    std::string new_theme;
    for (char c : theme) {
        if (c != '\"') {
            new_theme += c;
        }
    }

    input_vector.at(2) = new_theme;

    // Poistetaan ylimääräiset alkiot vektorista. Saatu vektori
    // sisältää komennon (0), paikan (1) ja teeman (2).
    input_vector.erase(input_vector.begin() + 3, input_vector.end());
}

int main()
{
    // Käytettävä tietovarasto on map.
    std::pair<bool, std::map<std::string, std::vector<Course>>>
            created_data = create_database();

    // Jos tietovarastoa ei saatu luotua, ohjelman suoritus loppuu.
    if (created_data.first == false) {
        return EXIT_FAILURE;
    }

    std::map<std::string, std::vector<Course>> center_data
            = created_data.second;

    // Järjestetään tietovarasto aakkosjärjestykseen.
    sort_database(center_data);

    // Käyttöliittymä.
    while (true) {
        std::cout << "> ";

        std::string user_input;
        std::getline(std::cin, user_input);

        std::vector<std::string> input_vector = split(user_input, ' ');

        // Komento on ensimmäinen syötteen sana.
        std::string command = input_vector.at(0);

        // Teeman nimessa voi esiintyä välilyönti. Tehdään siitä yksi
        // alkio.
        if (size(input_vector) > 2) {
            input_theme(input_vector);
        }

        // Komennot
        if (input_check(center_data, input_vector)) {
            if (command == "quit") {
                return EXIT_SUCCESS;
            }
            else if (command == "locations") {
                print_locations(center_data);
            }
            else if (command == "available") {
                available(center_data);
            }
            else if (command == "themes_in_location") {
                themes_in_location(center_data, input_vector.at(1));
            }
            else if (command == "courses_in_theme") {
                courses_in_theme(center_data, input_vector.at(1));
            }
            else if (command == "favorite_theme") {
                favorite_theme(center_data);
            }
            else if (command == "courses") {
                courses(center_data, input_vector.at(1), input_vector.at(2));
            }
        }
    }
}
