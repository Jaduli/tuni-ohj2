/* Ohjelman kirjoittaja
* Nimi: Jade Pitkänen
* Opiskelijanumero: 151842146
* Käyttäjätunnus: kcjapi
* Sähköposti: jade.pitkanen@tuni.fi
* */

#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QSpinBox>
#include <QTextEdit>
#include <QLCDNumber>
#include <QTimer>
#include <string>
#include <gameboard.hh>

// Pelissä käytettävien kuvien nimet
const std::vector<QString> IMAGES = {"kitty", "doggy",
                                     "empty", "skull"};

// Pelilaudan maksimikoko (sivun pituus = 2 * koko)
const int MAX_BOARD_SIZE = 5;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // Päivittää laudan painikkeiden painausten jälkeen
    void handle_board_clicks();

    // Resetoi laudan
    void reset_board();

    // Täyttää laudan satunnaisesti siemenluvun perusteella
    void fill_random();

    // Täyttää laudan käyttäjän syötteen perusteella
    void fill_input();

    // Vaihtaa aktiivista pelimerkkiä (kissa/koira)
    void update_active();

    // Päivittää ajastimen sekunnit ja minuutit
    void on_timer_timeout();

    // Keskeyttää pelin (tai jatkaa peliä)
    void pause_game();

    // Näyttää pelin tiedot (hard moden tila ja kuvaus tai paras pistemäärä)
    void show_game_info();

    // Vaihtaa pelilaudan kokoa
    void change_board_size();

    // Laittaa hard moden päälle (tai pois päältä)
    void toggle_hard_mode();

private:
    Ui::MainWindow *ui;

    // Pelin painikkeiden asetteluun käytettävät arvot
    const int MARGIN = 5;
    const int SIDE_MARGIN = 130;
    const int TOP_MARGIN = 50;
    const int IMAGE_SIZE = 50;
    const int BUTTON_SIZE = 30;

    // Pelilaudan koon arvo
    unsigned int board_size_;

    // Luo käyttöliittymän painikkeet, labelit ja ajastimen
    void draw_ui();

    // Piirtää tyhjän laudan
    void draw_empty_board();

    // Luo peliin tarvittavat kuvan niiden nimien perusteella
    std::vector<QPixmap> create_images();

    // Päivittää laudan painikkeet pelilaudan tilanteen perusteella
    void update_board();

    // Struct pelilaudan napeille (nappi, sijainti, tyhjyysarvo)
    struct ImagedButton
    {
        QPushButton* button;
        unsigned int x;
        unsigned int y;
        bool empty;
    };
    // Vektori napeille
    std::vector<ImagedButton> buttons_;

    // Lisää vektoriin pelilaudan painikkeen kuvan, sijainnin ja
    // tiedon, onko kohta tyhjä vai ei
    void add_imaged_button(QPixmap& image, unsigned int x,
                           unsigned int y, bool empty);

    // Pelin voitettua laskee pisteet, muuntaa taustavärin ja
    // deaktivio laudan painikkeet.
    void game_won();

    // Pelin hävittyä hard modessa peli keskeytyy
    void game_lost(ImagedButton imaged_button);

    // Painike aktiivisen pelimerkin vaihtoon
    QPushButton* edit_active_;

    // Pelin alussa aktiivisena on 1 eli koira
    char active_number_ = '1';

    // Pelilauta
    GameBoard* game_board_;

    // Vektori pelin kuville (0 = kissa, 1 = koira, 2 = tyhjä, 3 = pääkallo)
    std::vector<QPixmap> game_images_;

    // Info nappi joka näyttää pelin tiedot tai parhaan tuloksen
    QPushButton* info_button_;

    // Muokkaa laudan kokoa
    QSpinBox* size_edit_;

    // Tekstikenttä käyttäjän arvoille laudan luomista varten
    QTextEdit* user_input_;

    // Etiketti, joka kertoo pelin tilanteen tai kertoo tietoa pelistä
    QLabel* info_label_;

    // Ajastin
    QTimer* timer_;

    // Ajastimen käyttöön tarvittavat arvot ja totuusarvo
    int min_ = 0;
    int sec_ = 0;
    bool keep_timer_active_ = false;

    // LCD-näytöt ajan näyttämiseen
    QLCDNumber* lcdNumberSec_ = new QLCDNumber(this);
    QLCDNumber* lcdNumberMin_ = new QLCDNumber(this);

    // Painike, jolla ajastin voidaan pysäyttää
    QPushButton* pause_button_;

    // Pelaajan parhaiden pisteiden tuottaman pelin tiedot
    int best_time_ = 0;
    int best_size_ = 0;
    int points_ = 0;

    // Hard modeen käytettävä totuusarvo ja nappi
    bool hard_mode_ = false;
    QPushButton* mode_button_;
};
#endif // MAINWINDOW_HH
