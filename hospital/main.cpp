/* Sairaala
 *
 * Kuvaus:
 * Ohjelma toimii tietovarastona sairaalalle. Tietovarastoon voi säilöä
 * potilaat, henkilökunnan ja hoitojaksot.
 *
 * Käyttöliittymään voi antaa komentoja käyttäen _-merkkiä välilyöntinä
 * tai käyttämällä lyhenteitä. Komennot voi myös syöttää tekstitiedostona.
 * Ei ole väliä, kirjoitetaanko komennot isoilla vai pienillä kirjaimilla.
 *
 * "Help"-komento tulostaa käytettävissä olevat komennot lyhenteineen.
 *
 * Potilaita voi lisätä ja poistaa sairaalasta tarpeen mukaan.
 * Potilaille asetetaan hoitojaksoja. Hoitojaksoon kuuluu alku- ja
 * lopetuspäivämäärä. Hoitojaksolle voi asettaa henkilökuntaa.
 * Asiakkaalle voi myös asettaa lääkekuureja joihin kuuluu lääkkeen nimi,
 * vahvuus ja annostus.
 *
 * Ohjelman kirjoittaja
 * Nimi: Jade Pitkänen
 * Opiskelijanumero: 151842146
 * Käyttäjätunnus: kcjapi
 * S-posti: jade.pitkanen@tuni.fi
 */

#include "cli.hh"
#include "hospital.hh"
#include <string>

const std::string PROMPT = "Hosp> ";


int main()
{
    Hospital* hospital = new Hospital();
    Cli cli(hospital, PROMPT);
    while ( cli.exec() ){}

    delete hospital;
    return EXIT_SUCCESS;
}
