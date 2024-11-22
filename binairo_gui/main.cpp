/* Cat & Dog Binairo
 *
 * Binairo-peli kissan ja koiran kuvilla.
 *
 * Säännöt: Täytä lauta niin, että samalla rivillä on sama määrä kissoja ja
 * koiria. Pysty- tai vaakarivillä ei saa olla kahta enemäpää samaa eläintä
 * peräkkäin.
 *
 * Aktiivista eläintä voi vaihtaa ylhäällä vasemmalla olevasta painikkeesta.
 * Pelissä on myös hard mode, joka keskeyttää pelin epäsopivan painikkeen
 * painamisesta. Pelin tilan voi tarkistaa painamalla "game info"-painiketta.
 *
 * Laudan voit täyttää siemenluvulla (esim. 3, 7 tai 77) tai syötteellä
 * (1 = koira, 0 = kissa, välilyönti = tyhjä). Syötteen ympärillä tulee olla
 * ""-merkit.
 *
 * Esimerkkisyötteitä koon 3 (6x6) laudalle:
 * "   1       0    0 0  00   1  1      "
 * "   11  00   00          1  0       1"
 *
 * Laudan kokoa voi muuttaa spinboxilla (peruskoot 1-5). Laudan sivun pituus
 * on kaksi kertaan koon arvo. Pelilaudan yläpuolella on infolaatikko, joka
 * kertoo pelin tietoja ja pelitilanteen.
 *
 * Pelilaudan voi resetoida "reset"-painikkeella. Resetoinnin jälkeen
 * pelilaudan kokoa ja vaikeustilaa voi muuttaa.
 *
 * Pelissä on pisteytys, joka määräytyy laudan koon ja käytetyn ajan
 * perusteella. Jos hard mode on päällä, saa 50% enemmän pisteitä.
 * Pisteet = 5 * 10 ^ (laudan koko) / käytetty aika (* 3/2).
 * Parhaan pistemäärän näkee "game info"-painikkeen avulla.
 *
 * Ohjelman kirjoittaja
 * Nimi: Jade Pitkänen
 * Opiskelijanumero: 151842146
 * Käyttäjätunnus: kcjapi
 * Sähköposti: jade.pitkanen@tuni.fi
 *
 * Huomioita:
 * Yksi commit laudan koon muuttamisesta unohtui tekemättä, joten commit
 * hard moden lisäyksestä on suurempi kuin pitäisi olla. Pelin kuvat ovat
 * itsetehtyjä. En alkusi tajunnut, miten väärän lisäyksen kanssa kuuluu
 * toimia (peliähän ei voi voitaa väärällä lisäyksellä), niin jätin
 * pelin päättämisen väärän lisäyksen tehdessä ylimääräiseksi
 * lisäominaisuudeksi (hard mode, ei tosin tuo lisäpisteitä). Hard mode on
 * myös pisteidenlaskun ominaisuus.
*/



#include "mainwindow.hh"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
