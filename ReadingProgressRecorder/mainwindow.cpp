#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //laczenie sygnalu textChanged z motoda do filtracji, tekstu ktory moze byc wprowadzany w LIneEdit
    connect(ui->title, &QLineEdit::textChanged, this, &MainWindow::filterSrednik);
    connect(ui->author, &QLineEdit::textChanged, this, &MainWindow::filterSrednik);
    connect(ui->pages, &QLineEdit::textChanged, this, &MainWindow::filterLineEditInput);

    //wczytanie pliku z danymi

    //create variable with file name
    QString filename = "books.txt";
    //tworzenie obiektu typu QFile oraz wywolanie konstruktora z parametrem
    QFile file(filename);

    //proba otwarcia pliku w trybie czytania
    if(!file.open(QFile::ReadOnly |
                   QFile::Text))
    {
        //skoncz wykonanie metody
        return;
    }
    //create an object to read data from the file using the QTextStream functions
    QTextStream in(&file);
    //wczytanie calego pliku
    QString myText = in.readAll();
    //dzielenie wczytanego tekstu po srednikach
    QStringList parts = myText.split(";");

    QString tytul="", autor="", pages="", currentP="";

    //iteracja po liscie sworzonej poprzez podzial wczytanego z pliku tekstu
    for (int i=0; i<parts.size(); i++) {
        //przypisanie wartosci zmiennym w zaleznosci od nuumeru i
        if (i%4==0) tytul=parts[i];
        else if (i%4==1) autor=parts[i];
        else if (i%4==2) pages=parts[i];
        else if (i%4==3) {
            currentP=parts[i];
            //wywolanie metody ktora doda nowa strone z wczytana ksiazka
            addBook(tytul, autor, pages, currentP);
        }
    }
    //zamkniecie pliku
    file.close();
}

MainWindow::~MainWindow()
{
    //usuniecie wskazika na okno programu
    delete ui;
}

//defiicja metody do aktualizacji postepu czytania
void MainWindow::aktualizujPostep()
{
    // Pobierz indeks biezacej zakładki
    int tabIndex = ui->booksTab->currentIndex();

    // Sprawdź, czy indeks jest prawidłowy
    if (tabIndex >= 0 && tabIndex < ui->booksTab->count()) {
        // Pobierz wskaźnik do zakładki
        QWidget* tabWidget = ui->booksTab->widget(tabIndex);

        // Wyszukaj obiekt wewnątrz zakładki po jego objectName i stworz wskaznik na niego
        QLabel* label = tabWidget->findChild<QLabel*>("pages");
        QProgressBar* bar = tabWidget->findChild<QProgressBar*>("readingProgress");
        QLineEdit* currentPage = tabWidget->findChild<QLineEdit*>("currentPage");
        QLabel* curP = tabWidget->findChild<QLabel*>("curP");

        // Sprawdź, czy wszystkie obiekty udalo sie znalezc
        if (label && bar && currentPage && curP) {
            //pobierz ilosc stron, ktora zaczyna sie od 14 znaku QLabel pages
            int totalPages = label->text().mid(14).toInt();
            //sprawdz czy zostala podana liczba w QLineEdit
            if (currentPage->text()=="") {
                //wyswietl odpowiedni komunikat
                QMessageBox::warning(this,"Nie pelne dane","Liczba przeczytanych stron nie jest podana.");
                //skoncz wykonanie metody
                return;
            //sprawdz czy podana w QLineEdit liczba nie jest wieksza od calkowitej liczby stron
            } else if (currentPage->text().toInt()>totalPages)
            {
                //wyswietl odpowiedni komunikat
                QMessageBox::warning(this,"Za duza liczba","Podana liczba przeczytanych stron jest wieksza od calkowitej liczby stron.");
                //wyczysc QLineEdit do podania liczby przeczytanych stron
                currentPage->clear();
                //skoncz wykonanie metody
                return;
            }
            //obliczenie nowego postepu czytania w procentach
            int progress = (currentPage->text().toInt()*100)/totalPages;
            //ustawianie nowej liczby w QProgressBar
            bar->setValue(progress);
            //ustawianie nowej biezacej strony w QLabel
            curP->setText("Biezaca strona: "+currentPage->text());
            // Clear QLineEdit
            currentPage->clear();
        }
    }
}

//metoda sprawdajaca poprawosc wprowadzonych danych
//przed dodaniem nowej ksiazki
void MainWindow::on_addBook_clicked()
{
    //sprawdz czy jest wprowadony ->
    //tytul
    if (ui->title->text()=="")
    {
        //wyswietl odpowiedni komunikat
        QMessageBox::warning(this,"Nie pelne dane","Tytul nie jest podany.");
        //skoncz wykonanie metody
        return;
    //autor
    } else if (ui->author->text()=="") {
        //wyswietl odpowiedni komunikat
        QMessageBox::warning(this,"Nie pelne dane","Autor nie jest podany.");
        //skoncz wykonanie metody
        return;
    //ilosc stron
    } else if (ui->pages->text()=="") {
        //wyswietl odpowiedni komunikat
        QMessageBox::warning(this,"Nie pelne dane","Liczba stron nie jest podana.");
        //skoncz wykonanie metody
        return;
    }
    //wywolanie metody do dodania nowej strony z podana ksiazka
    addBook(ui->title->text(), ui->author->text(), ui->pages->text(), "0");

    //wyczysc QLineEdit-y do podania danych
    ui->title->clear();
    ui->author->clear();
    ui->pages->clear();
}

//metoda tworzaca i dodajaca nowa strone z podana ksiazka do QTabWidget
void MainWindow::addBook(QString tytul, QString autor, QString strony, QString currentP)
{
    //Kopiowanie czcianki z obiektu
    QFont font = ui->Ltitle->font();

    // Create and add elements to the newTab widget
    QWidget *newTab = new QWidget(ui->booksTab);

    //stworz containerWidget i dodaj do niego elementy
    QWidget* progressContainer = new QWidget(newTab);
    QLabel* progressLabel = new QLabel("Postep w czytaniu: ", progressContainer);
    QProgressBar* progressBar = new QProgressBar(progressContainer);

    //stworz containerLayout i umiesc elementy
    QHBoxLayout* progressLayout = new QHBoxLayout(progressContainer);
    progressLayout->addWidget(progressLabel);
    progressLayout->addWidget(progressBar);
    //ustaw odstep
    progressLayout->setSpacing(10);
    //ustaw marginesy
    progressLayout->setContentsMargins(0, 0, 0, 0);

    //utworz QLabel-y z informacja o ksiazce
    QLabel* title = new QLabel("Tytul: "+tytul, newTab);
    QLabel* author = new QLabel("Autor: "+autor, newTab);
    QLabel* pages = new QLabel("Liczba stron: "+strony, newTab);
    QLabel* currentPage = new QLabel("Bieząca strona: "+currentP, newTab);

    //utworz kontener i dodaj do niego obiekty
    QWidget* pageContainer = new QWidget(newTab);
    QLabel* podajCur = new QLabel("Podaj biezaca strone:", pageContainer);
    // utworz lineEdit do wprowadzania biezacej strony
    QLineEdit* lineEdit = new QLineEdit(pageContainer);
    //polac lineEdit z funkcja do filtrowania wprowadzanego tekstu
    connect(lineEdit, &QLineEdit::textChanged, this, &MainWindow::filterLineEditInput);

    //utworz nowy uklad i uloz obiekty w kontenerze
    QHBoxLayout* pageLayout = new QHBoxLayout(pageContainer);
    pageLayout->addWidget(podajCur);
    pageLayout->addWidget(lineEdit);
    //ustaw odstepy
    pageLayout->setSpacing(10);
    //ustaw marginesy
    pageLayout->setContentsMargins(0, 0, 0, 0);

    //Utworz przycisk i polacz go z metoda do aktualizacji postepu czytania
    QPushButton* button = new QPushButton("  Zaktualizuj postęp czytania  ", newTab);
    connect(button, &QPushButton::clicked, this, &MainWindow::aktualizujPostep);

    //ustaw imienia obiektom, po ktorych bedzie mozna je wyszukac
    author->setObjectName("author");
    title->setObjectName("title");
    lineEdit->setObjectName("currentPage");
    pages->setObjectName("pages");
    currentPage->setObjectName("curP");
    progressBar->setObjectName("readingProgress");

    //policz postep czytania na podstawie przekazanych do funkcji argumentow
    int k = (currentP.toInt()*100)/strony.toInt();
    //ustawianie wartosci w QProgressBar
    progressBar->setValue(k);

    //ustaw czcionke
    author->setFont(font);
    title->setFont(font);
    pages->setFont(font);
    currentPage->setFont(font);
    progressLabel->setFont(font);
    podajCur->setFont(font);
    button->setFont(font);

    // Create a layout grid for the newTab widget
    QGridLayout* layout = new QGridLayout(newTab);
    // Set spacing and margins
    layout->setSpacing(15);
    layout->setContentsMargins(30, 20, 25, 30);

    // Add widgets to specific grid positions
    layout->addWidget(title, 0, 0, 1, 1);
    layout->addWidget(author, 1, 0, 1, 1);
    layout->addWidget(pages, 2, 0, 1, 1);
    layout->addWidget(currentPage, 3, 0, 1, 1);
    layout->addWidget(progressContainer, 4, 0);
    layout->addWidget(pageContainer, 5, 0);
    layout->addWidget(button, 6, 0);

    // Adjust the alignment of the objects within the layout
    layout->setAlignment(Qt::AlignTop);

    // Set the layout for the newTab widget
    newTab->setLayout(layout);

    //dodaj nowa strone do QTabWidget
    ui->booksTab->addTab(newTab, tytul);
}

//metoda do usuwania strony z ksiazka
void MainWindow::on_deleteBook_clicked()
{
    //sprawdzenie mozliwosci usuniecia ksiazki
    if (ui->booksTab->count()==0)
    {
        //wyswietlenie odpowiednego komuniatu
        QMessageBox::information(this,"Probujesz usunac ksiazke","Nie ma dostepnych do usuniecia ksiazek");
    }
    else {
        //tworzenie obiektu typu QMessage Box
        QMessageBox msgBox;
        //ustawienie tytulu wiadomosci
        msgBox.setWindowTitle("Probujesz usunac ksiazke");
        //ustawienie tresci wiadomosci
        msgBox.setText("Czy na pewno chcesz usunac wybrana ksiazke?");
        //ustawienie icony wiadomosci
        msgBox.setIcon(QMessageBox::Question);
        //ustawienie tekstu z dodatkowymi szegolami
        msgBox.setDetailedText("Tytul: " + ui->booksTab->tabText(ui->booksTab->currentIndex())
                               +"\n"+ui->booksTab->widget(ui->booksTab->currentIndex())->findChild<QLabel*>("author")->text()
                               +"\n"+ui->booksTab->widget(ui->booksTab->currentIndex())->findChild<QLabel*>("pages")->text()
                               +"\n"+ui->booksTab->widget(ui->booksTab->currentIndex())->findChild<QLabel*>("curP")->text()
                               +"\nPostep w czytaniu: "+QString::number(ui->booksTab->widget(ui->booksTab->currentIndex())->findChild<QProgressBar*>("readingProgress")->value())+"%");
        //ustawienie przyciskow standartowych
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        //ustawienie wybranego przycisku
        msgBox.setDefaultButton(QMessageBox::Yes);
        //wyswietlenie wiadomosci oraz pobranie jaki przycisk nacisnal uzytownik
        int ret = msgBox.exec();
        //sprawdzenie czy uzytkownik nacisnal "Tak"
        if (ret==QMessageBox::Yes) {
            // Get the current index of the QTabWidget
            int currentIndex = ui->booksTab->currentIndex();
            // Remove the tab at the current index
            ui->booksTab->removeTab(currentIndex);
        }
    }
}

//metoda, ktora pozwoli wprowadzac w QLineEdit tylko liczby
//zostawiam tylko liczby, bo wartosc strony nie moze byc niczym innym
void MainWindow::filterLineEditInput(const QString& text)
{
    //tworzenie filtrowanego tekstu, ktory bedzie wyswietlany w QLineEdit
    QString filteredText;

    //iteracja po tekstu ktory uzytkownik probuje wprowadzic w QLineEdit
    for (const QChar& ch : text)
    {
        //sprawdzenie czy to, co probuje wprowadic uzytkownik jest liczba
        if (ch.isDigit())
        {
            //dodanie liczby do QString-a filtered Text
            filteredText.append(ch);
        }
    }
    //obtain a pointer to the QLineEdit object that emitted the signal within the slot function
    QLineEdit* lineEdit = qobject_cast<QLineEdit*>(sender());
    //check if cast was successful
    if (lineEdit)
    {
        //ustawienie odfiltrowanego tekstu w QLineEdit
        lineEdit->setText(filteredText);
    }
}

//metoda, ktora nie pozwoli wprowadzic w QLineEdit srednik
//nie pozwalam wprowadzic sredniki, dlatego ze sa one szegolnie wazne podczas
//wczytania pliku przy otworzeniu programu
void MainWindow::filterSrednik(const QString& text)
{
    QString filteredText;
    for (const QChar& ch : text)
    {
        //sprwawdzenie czy znak nie jest srednikiem
        if (ch!=';')
        {
            filteredText.append(ch);
        }
    }
    QLineEdit* lineEdit = qobject_cast<QLineEdit*>(sender());
    if (lineEdit)
    {
        lineEdit->setText(filteredText);
    }
}

//metoda do zapisania podanych ksziazek do pliku
//aby umozliwic otwieranie i modyfikacje tych ksiazek podczas nastepnego otwarcia programu
void MainWindow::on_save_clicked()
{
    QString filename = "books.txt";

    QFile file(filename);
    // Trying to open in WriteOnly and Text mode
    if(!file.open(QFile::WriteOnly |
                   QFile::Text))
    {
        //wyswietl odpowiedni debug message
        qDebug() << " Could not open file for writing";
        //wyswietlenie stosownego komunikatu
        QMessageBox::critical(this,"Zapisanie sie nie powiodlo","Twoje ksiazki nie sa zapisane");
        return;
    }

    QString wpis="";
    int totalIndex = ui->booksTab->count();

    //iteracja po stronach QTabWidzet
    for (int tabIndex=0; tabIndex<totalIndex; tabIndex++)
    {
        // Pobierz wskaźnik do zakładki
        QWidget* tabWidget = ui->booksTab->widget(tabIndex);

        // Poszukaj obiekty wewnątrz zakładki
        QLabel* pages = tabWidget->findChild<QLabel*>("pages");
        QLabel* title = tabWidget->findChild<QLabel*>("title");
        QLabel* author = tabWidget->findChild<QLabel*>("author");
        QLabel* curP = tabWidget->findChild<QLabel*>("curP");

        if (pages && title && author && curP) {
            //dodanie tytulu pobranego od 7. znaku tekstu w QLabel
            wpis+=title->text().mid(7);
            //dodanie srednika by oddzielic wartosci
            wpis+=";";
            wpis+=author->text().mid(7);
            wpis+=";";
            wpis+=pages->text().mid(14);
            wpis+=";";
            wpis+=curP->text().mid(16);
            wpis+=";";
        }

    }
    // To write text, we use operator<<(), which is overloaded to take
    // a QTextStream on the left and data types (including QString) on the right
    QTextStream out(&file);
    //zapisanie danych do pliku
    out<<wpis;
    file.flush();
    //zamkniecie pliku
    file.close();
    //wyswietlenie stosownego komunikatu
    QMessageBox::information(this,"Operacja udana","Twoje ksiazki sa poprawnie zapisane");
}
