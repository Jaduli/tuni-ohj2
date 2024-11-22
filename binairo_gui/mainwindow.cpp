/* Ohjelman kirjoittaja
* Nimi: Jade Pitkänen
* Opiskelijanumero: 151842146
* Käyttäjätunnus: kcjapi
* Sähköposti: jade.pitkanen@tuni.fi
* */

#include "mainwindow.hh"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    game_images_ = create_images();

    // Asetetaan laudan alkukooksi 3 (6x6)
    game_board_ = new GameBoard(3);

    board_size_ = 3;

    draw_ui();
    draw_empty_board();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete game_board_;
}

void MainWindow::handle_board_clicks()
{
    for (auto& imaged_button : buttons_)
    {
        if (imaged_button.button == sender())
        {
            // Jos symboli on sopiva, lisätään se lautaan
            if (game_board_->add_symbol(imaged_button.x, imaged_button.y,
                                       active_number_)) {
                if (active_number_ == '1') {
                    info_label_->setText("Doggy added");
                    update_board();
                }
                else {
                    info_label_->setText("Kitty added");
                    update_board();
                }
                // Jos peli on voitettu, päätetään peli
                if (game_board_->is_game_over()) {
                    game_won();
                }
            }
            else {
                // Epäsopivan painauksen tapauksessa peli päättyy, jos
                // hard mode on päällä.
                if (hard_mode_) {
                    game_lost(imaged_button);
                }
                else {
                    // Epäsopiva lisäys näytetään punaisella
                    if (imaged_button.empty) {
                        // Päivitetään lauta vanhojen epäsopivien lisäyksien
                        // poistamiseksi
                        update_board();

                        imaged_button.button
                                ->setStyleSheet("background-color: red");

                        if (active_number_ == '1') {
                            imaged_button.button->setIcon(game_images_.at(1));
                        }
                        else {
                            imaged_button.button->setIcon(game_images_.at(0));
                        }
                    }
                    info_label_->setText("Can't add pet");
                }
            }
        }
    }
}

void MainWindow::reset_board()
{
    // Poistetaan käyttöliittymän taustaväri
    this->setStyleSheet("");

    // Poistetaan vanha pelilauta ja luodaan uusi
    delete game_board_;
    game_board_ = new GameBoard(board_size_);

    // Poistetaan napit ja luodaan uusi tyhjä lauta
    for (ImagedButton button : buttons_) {
        delete button.button;
    }
    buttons_.clear();

    draw_empty_board();

    info_label_->setText("Create board from seed or input");

    // Resetoidaan ajastin
    keep_timer_active_ = false;

    sec_ = 0;
    min_ = 0;

    lcdNumberSec_->display(sec_);
    lcdNumberMin_->display(min_);
    pause_button_->setDisabled(true);

    // Aktivoidaan pelin muutosnapit
    size_edit_->setDisabled(false);
    mode_button_->setDisabled(false);
}

void MainWindow::fill_random()
{
    // Poistetaan taustaväri
    this->setStyleSheet("");

    // Muutetaan käyttäjän syöte numeroksi, jos mahdollista
    QString input = user_input_->toPlainText();
    unsigned int value = input.toInt();

    if (value > 0) {
        // Luodaan lauta, jos siemenluku kelpaa
        if (game_board_->fill_randomly(value)) {
            update_board();
            info_label_->setText("Board created");

            for (ImagedButton button : buttons_) {
                button.button->setDisabled(false);
            }

            sec_ = 0;
            min_ = 0;

            lcdNumberSec_->display(sec_);
            lcdNumberMin_->display(min_);

            keep_timer_active_ = true;
            pause_button_->setDisabled(false);
            pause_button_->setText("pause");

            size_edit_->setDisabled(true);
            mode_button_->setDisabled(true);
        }
        else {
            info_label_->setText("Bad seed value");
        }
    }
    else {
        info_label_->setText("Invalid input");
    }
}

void MainWindow::fill_input()
{
    this->setStyleSheet("");

    // Luodaan lauta käyttäjän syötteen perusteella
    QString input = user_input_->toPlainText();

    std::string str_input = input.toStdString();

    if (game_board_->fill_from_input(str_input)) {
        update_board();
        info_label_->setText("Board created");

        for (ImagedButton button : buttons_) {
            button.button->setDisabled(false);
        }

        sec_ = 0;
        min_ = 0;

        lcdNumberSec_->display(sec_);
        lcdNumberMin_->display(min_);

        keep_timer_active_ = true;
        pause_button_->setDisabled(false);
        pause_button_->setText("pause");

        size_edit_->setDisabled(true);
        mode_button_->setDisabled(true);
    }
    else {
        info_label_->setText("Invalid input");
    }
}

void MainWindow::update_active()
{
    if (active_number_ == '1') {
        active_number_ = '0';
        edit_active_->setIcon(game_images_.at(0));
        info_label_->setText("Changed to kitty");
    }
    else {
        active_number_ = '1';
        edit_active_->setIcon(game_images_.at(1));
        info_label_->setText("Changed to doggy");
    }
}

void MainWindow::on_timer_timeout() {
    if (keep_timer_active_) {
        sec_ += 1;

        // 60 sekuntia = 1 minuutti
        if (sec_ == 60) {
            min_ += 1;
            sec_ = 0;
        }
        lcdNumberSec_->display(sec_);
        lcdNumberMin_->display(min_);
    }
}

void MainWindow::pause_game()
{
    if (keep_timer_active_) {
        keep_timer_active_ = false;
        pause_button_->setText("resume");

        info_label_->setText("Game is paused");

        // Pause tilassa pelin napit ovat deaktivoituja
        for (ImagedButton button : buttons_) {
            button.button->setDisabled(true);
        }
    }
    else {
        keep_timer_active_ = true;
        pause_button_->setText("pause");

        info_label_->setText("Game resumed");

        for (ImagedButton button : buttons_) {
            button.button->setDisabled(false);
        }
    }
}

void MainWindow::show_game_info()
{
    QString mode_info;

    if (hard_mode_) {
        mode_info = "Hard mode is on. ";
    }
    else {
        mode_info = "Hard mode is off. ";
    }

    // Jos peliä ei ole vielä pelattu, näytetään parhaan tuloksen sijaan
    // pelin tiedot
    if (best_time_ == 0) {
        info_label_->setText("Rules of binairo but with doggies and kitties. "
                            + mode_info);
        return;
    }

    int minutes = best_time_ / 60;
    int seconds = best_time_ % 60;

    QString str_minutes = QString::number(minutes);
    QString str_seconds = QString::number(seconds);

    if (seconds < 10) {
        str_seconds = "0" + str_seconds;
    }

    QString best_time = str_minutes + ":" + str_seconds;

    QString points = QString::number(points_);

    info_label_->setText(mode_info + "Time: " + best_time +
                         ", Board size: " + QString::number(best_size_)
                         + " -> Best points: " + points);
}

void MainWindow::change_board_size()
{
    // Haetaan arvo käyttöliittymän spinboxista
    unsigned int value = size_edit_->value();

    // Asetetaan laudan koko
    game_board_->set_size(value);
    board_size_ = value;

    // Resetoidaan lauta uudella koolla
    reset_board();
}

void MainWindow::toggle_hard_mode()
{
    if (hard_mode_) {
        hard_mode_ = false;
        info_label_->setText("Hard mode disabled");
    }
    else {
        hard_mode_ = true;
        info_label_->setText("Hard mode enabled");
    }
}

void MainWindow::draw_ui()
{
    // Luodaan käyttöliittymässä tarvittavat painikkeet ja asetellaan ne
    // käyttöliittymään sopivasti. Yhdistetään painikkeet tarvittaessa
    // slotteihin.

    info_label_ = new QLabel("Create board from seed or input", this);
    info_label_->setGeometry(SIDE_MARGIN + MARGIN, TOP_MARGIN / 2,
                            20 * BUTTON_SIZE, BUTTON_SIZE);

    QLabel* active_laber = new QLabel("Pet:", this);
    active_laber->setGeometry(SIDE_MARGIN / 2 - BUTTON_SIZE,
                              TOP_MARGIN / 2,
                              BUTTON_SIZE, BUTTON_SIZE);

    edit_active_ = new QPushButton(this);
    edit_active_->setGeometry(SIDE_MARGIN / 2, TOP_MARGIN / 2,
                              IMAGE_SIZE, IMAGE_SIZE);
    edit_active_->setIconSize(QSize(IMAGE_SIZE, IMAGE_SIZE));
    edit_active_->setIcon(game_images_.at(1));
    connect(edit_active_, &QPushButton::clicked,
            this, &MainWindow::update_active);

    info_button_ = new QPushButton("game info", this);
    info_button_->setGeometry(MARGIN,
                            TOP_MARGIN + BUTTON_SIZE + MARGIN,
                            3 * BUTTON_SIZE, BUTTON_SIZE);
    connect(info_button_, &QPushButton::clicked,
            this, &MainWindow::show_game_info);

    QLabel* size_laber = new QLabel("Board size:", this);
    size_laber->setGeometry(MARGIN, TOP_MARGIN + 2 * BUTTON_SIZE + MARGIN,
                            3 * BUTTON_SIZE, BUTTON_SIZE);

    size_edit_ = new QSpinBox(this);
    size_edit_->setRange(1, MAX_BOARD_SIZE);
    size_edit_->setValue(3);
    size_edit_->setGeometry(MARGIN + 3 * BUTTON_SIZE - 10,
                            TOP_MARGIN + 2 * BUTTON_SIZE + MARGIN,
                            BUTTON_SIZE + 10, BUTTON_SIZE);
    connect(size_edit_, &QSpinBox::valueChanged, this,
            &MainWindow::change_board_size);

    QPushButton* fill_random_button = new QPushButton("fill random", this);
    fill_random_button->setGeometry(MARGIN,
                                    TOP_MARGIN + 3 * BUTTON_SIZE + MARGIN,
                                    3 * BUTTON_SIZE, BUTTON_SIZE);
    connect(fill_random_button, &QPushButton::clicked,
            this, &MainWindow::fill_random);

    QPushButton* fill_input_button = new QPushButton("fill input", this);
    fill_input_button->setGeometry(MARGIN,
                                   TOP_MARGIN + 4 * BUTTON_SIZE + MARGIN,
                                   3 * BUTTON_SIZE, BUTTON_SIZE);
    connect(fill_input_button, &QPushButton::clicked,
            this, &MainWindow::fill_input);

    user_input_ = new QTextEdit("Input values",this);
    user_input_->setGeometry(MARGIN,
                             TOP_MARGIN + 5 * BUTTON_SIZE + MARGIN,
                             SIDE_MARGIN - MARGIN, 3 * BUTTON_SIZE);

    timer_  = new QTimer(this);
    connect(timer_, &QTimer::timeout, this, &MainWindow::on_timer_timeout);
    timer_->start(1000);

    QLabel* min_laber = new QLabel("Min", this);
    min_laber->setGeometry(MARGIN,
                           TOP_MARGIN + 8 * BUTTON_SIZE + MARGIN,
                           2 * BUTTON_SIZE, 2 * BUTTON_SIZE);

    lcdNumberMin_->setGeometry(SIDE_MARGIN - 2 * BUTTON_SIZE,
                               TOP_MARGIN + 8 * BUTTON_SIZE + MARGIN,
                               2 * BUTTON_SIZE, 2 * BUTTON_SIZE);
    lcdNumberMin_->setStyleSheet("background-color: lightgreen; color: black;");

    QLabel* sec_laber = new QLabel("Sec", this);
    sec_laber->setGeometry(MARGIN,
                            TOP_MARGIN + 10 * BUTTON_SIZE + MARGIN,
                            2 * BUTTON_SIZE, 2 * BUTTON_SIZE);

    lcdNumberSec_->setGeometry(SIDE_MARGIN - 2 * BUTTON_SIZE,
                               TOP_MARGIN + 10 * BUTTON_SIZE + MARGIN,
                               2 * BUTTON_SIZE, 2 * BUTTON_SIZE);
    lcdNumberSec_->setStyleSheet("background-color: lightblue; color: black;");

    pause_button_ = new QPushButton("pause", this);
    pause_button_->setGeometry(MARGIN,
                            TOP_MARGIN + 12 * BUTTON_SIZE + MARGIN,
                            3 *BUTTON_SIZE, BUTTON_SIZE);
    connect(pause_button_, &QPushButton::clicked, this,
            &MainWindow::pause_game);
    pause_button_->setDisabled(true);

    mode_button_ = new QPushButton("hard mode", this);
    mode_button_->setGeometry(MARGIN,
                            TOP_MARGIN + 13 * BUTTON_SIZE + MARGIN,
                            3 *BUTTON_SIZE, BUTTON_SIZE);
    connect(mode_button_, &QPushButton::clicked, this,
            &MainWindow::toggle_hard_mode);

    QPushButton* reset_button = new QPushButton("reset", this);
    reset_button->setGeometry(MARGIN,
                              TOP_MARGIN + 14 * BUTTON_SIZE + MARGIN,
                              3 * BUTTON_SIZE, BUTTON_SIZE);
    connect(reset_button, &QPushButton::clicked,
            this, &MainWindow::reset_board);

    QPushButton* quit_button = new QPushButton("quit", this);
    quit_button->setGeometry(MARGIN,
                            TOP_MARGIN + 15 * BUTTON_SIZE + MARGIN,
                            3 * BUTTON_SIZE, BUTTON_SIZE);
    connect(quit_button, &QPushButton::clicked, this, &QApplication::quit);
}

std::vector<QPixmap> MainWindow::create_images()
{
    // Luodaan vektori kuville
    std::vector<QPixmap> pixmaps;

    for (QString image_name : IMAGES) {
        QString filename = ":/" + image_name + ".png";

        QPixmap pix(filename);
        // Skaalataan kuva
        pix.scaled(IMAGE_SIZE, IMAGE_SIZE);

        pixmaps.push_back(pix);
    }
    return pixmaps;
}

void MainWindow::draw_empty_board()
{
    // Haetaan laudan tiedot ja piirretään niiden perusteella tyhjä lauta
    std::vector<std::vector<Element_type>> board = game_board_->get_board();

    for (unsigned int i = 0; i < board.size(); ++i) {
        for (unsigned int j = 0; j < board.at(i).size(); ++j) {
            add_imaged_button(game_images_.at(2), j, i, true);
        }
    }
}

void MainWindow::add_imaged_button(QPixmap& image, unsigned int x,
                                   unsigned int y, bool empty)
{
    // Luodaan uusi nappi ja asetetaan sen tiedot
    QPushButton* button = new QPushButton(this);

    button->setGeometry(SIDE_MARGIN + MARGIN + x * (IMAGE_SIZE + MARGIN),
                        TOP_MARGIN + MARGIN + y * (IMAGE_SIZE + MARGIN),
                        IMAGE_SIZE + MARGIN, IMAGE_SIZE + MARGIN);

    button->setIcon(image);
    button->setIconSize(QSize(IMAGE_SIZE, IMAGE_SIZE));
    button->setDisabled(true);

    button->show();

    // Yhdistetään nappi slottiin
    connect(button, &QPushButton::clicked,
            this, &MainWindow::handle_board_clicks);

    // Luodaan uusi alkio nappien vektoriin
    ImagedButton imaged_button = {button, x, y, empty};
    buttons_.push_back(imaged_button);
}

void MainWindow::game_won()
{
    // Asetetaan käyttöliittymän taustaväri vaaleankeltaiseksi
    this->setStyleSheet("background-color: #FFFF99;");

    keep_timer_active_ = false;

    // Vältetään nollalla jakaminen sopimalla, että peliaika on aina
    // vähintään sekunnin
    if (sec_ == 0 and min_ == 0) {
        sec_ = 1;
    }

    QString minutes = QString::number(min_);
    QString seconds = QString::number(sec_);

    if (sec_ < 10){
        seconds = "0" + seconds;
    }

    int time = min_ * 60 + sec_;

    // Pohjapisteet määräytyvät laudan koon mukaan kaavalla
    // base = 5 * 10 ^ koko
    int base = 5;

    for (unsigned int i = 0; i < board_size_; ++i) {
        base = base * 10;
    }

    // Tulokseen vaikuttaa käytetty aika ja hard moden tila
    int score = base / time;

    if (hard_mode_) {
        score = score * 3/2;
    }

    // Tallennetaan tulos, jos se on pelaajan paras
    if (score > points_) {
        points_ = score;
        best_time_ = time;
        best_size_ = board_size_;
    }

    QString points = QString::number(score);

    info_label_->setText("You won! Used time: " + minutes + ":" + seconds
                         + ", Points: " + points);

    // Deaktivoidaan painikkeet lopuksi
    for (ImagedButton imaged_button : buttons_) {
        imaged_button.button->setDisabled(true);
    }
}

void MainWindow::game_lost(ImagedButton imaged_button)
{
    QString str_minutes = QString::number(min_);
    QString str_seconds = QString::number(sec_);

    if (sec_ < 10) {
        str_seconds = "0" + str_seconds;
    }

    info_label_->setText("Can't add. Game lost. Used time: "
                         + str_minutes + ":" + str_seconds);

    // Muutetaan häviön aiheuttanut ruutu pääkalloksi
    imaged_button.button->setIcon(game_images_.at(3));

    // Muutetaan käyttöliittymä punaiseksi
    this->setStyleSheet("background-color: #FF9999;");

    // Deaktivoidaan painikkeet
    for (ImagedButton button : buttons_) {
        button.button->setDisabled(true);
    }

    // Pysäytetään ajastin
    keep_timer_active_ = false;
    pause_button_->setDisabled(true);
}

void MainWindow::update_board()
{
    std::vector<std::vector<Element_type>> board = game_board_->get_board();

    // Käydään läpi laudan painikkeet
    for (ImagedButton& imaged_button : buttons_) {
        // Napin sijainti
        unsigned int i = imaged_button.y;
        unsigned int j = imaged_button.x;

        // Poistetaan mahdollinen taustaväri painikkeesta
        imaged_button.button->setStyleSheet("");

        // Asetetaan oikea kuva ja totuusarvo painikkeelle
        Element_type element = board.at(i).at(j);
        if (element == ONE) {
            imaged_button.button->setIcon(game_images_.at(1));
            imaged_button.empty = false;
        } else if (element == ZERO) {
            imaged_button.button->setIcon(game_images_.at(0));
            imaged_button.empty = false;
        } else {
            imaged_button.button->setIcon(game_images_.at(2));
            imaged_button.empty = true;
        }
    }
}


