#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <sstream>
using namespace std;

// ============================================================================
// a) i b) Deklaracja klasy Ksiazka
// ============================================================================
class Ksiazka {
private:
    string tytul;
    string autor;
    string wydawnictwo;
    string miejsce;
    int rok;
    string ISBN;
    string format;
    int strony;
    string okladka;
    double cena;

public:
    // a) Konstruktory i metody przetwarzania
    Ksiazka();
    Ksiazka(string t, string a, string w, string m,
        int r, string i, string f, int s, string o, double c);

    void Drukuj() const;
    void Skanuj();

    // b) Publiczne metody dostępowe (gettery)
    string PobierzTytul() const;
    string PobierzAutora() const;
    string PobierzWydawnictwo() const;
    string PobierzMiejsce() const;
    int PobierzRok() const;
    string PobierzISBN() const;
    string PobierzFormat() const;
    int PobierzStrony() const;
    string PobierzOkladke() const;
    double PobierzCene() const;
};

// ============================================================================
// a) Definicje metod klasy poza jej deklaracją
// ============================================================================

// Konstruktor bezargumentowy
Ksiazka::Ksiazka()
    : tytul("Brak tytulu"), autor("Brak autora"), wydawnictwo("Nieznane"),
    miejsce("Nieznane"), rok(2000), ISBN("000-00-0000-000-0"),
    format("A5"), strony(100), okladka("miekka"), cena(0.0) {}

// Konstruktor argumentowy
Ksiazka::Ksiazka(string t, string a, string w, string m,
    int r, string i, string f, int s, string o, double c)
    : tytul(t), autor(a), wydawnictwo(w), miejsce(m),
    rok(r), ISBN(i), format(f), strony(s), okladka(o), cena(c) {}

// b) Definicje metod dostępowych
string Ksiazka::PobierzTytul() const { return tytul; }
string Ksiazka::PobierzAutora() const { return autor; }
string Ksiazka::PobierzWydawnictwo() const { return wydawnictwo; }
string Ksiazka::PobierzMiejsce() const { return miejsce; }
int Ksiazka::PobierzRok() const { return rok; }
string Ksiazka::PobierzISBN() const { return ISBN; }
string Ksiazka::PobierzFormat() const { return format; }
int Ksiazka::PobierzStrony() const { return strony; }
string Ksiazka::PobierzOkladke() const { return okladka; }
double Ksiazka::PobierzCene() const { return cena; }

// Metoda wyświetlająca dane z użyciem znaków graficznych
void Ksiazka::Drukuj() const {
    cout << "+--------------------------------------------------------------+\n";
    cout << "| " << left << setw(60) << ("TYTUL:       " + tytul) << " |\n";
    cout << "| " << left << setw(60) << ("AUTOR:       " + autor) << " |\n";
    cout << "| " << left << setw(60) << ("WYDAWNICTWO: " + wydawnictwo + " (" + miejsce + ", " + to_string(rok) + ")") << " |\n";
    cout << "| " << left << setw(60) << ("ISBN:        " + ISBN) << " |\n";
    cout << "| " << left << setw(60) << ("FORMAT:      " + format + " | STRONY: " + to_string(strony)) << " |\n";
    cout << "| " << left << setw(60) << ("OKLADKA:     " + okladka) << " |\n";

    ostringstream cenaStr;
    cenaStr << fixed << setprecision(2) << cena << " PLN";
    cout << "| " << left << setw(60) << ("CENA:        " + cenaStr.str()) << " |\n";
    cout << "+--------------------------------------------------------------+\n";
}

// Pomocnicza funkcja do usuwania spacji z początku i końca tekstu
static string Przytnij(const string& str) {
    size_t start = str.find_first_not_of(" \t\r\n");
    if (start == string::npos) return "";
    size_t end = str.find_last_not_of(" \t\r\n");
    return str.substr(start, end - start + 1);
}

// Metoda wczytująca dane w postaci par "nazwa pola: wartość"
void Ksiazka::Skanuj() {
    cout << "\nWprowadz dane ksiazki w formacie 'nazwa pola: wartosc'.\n"
        << "Dostepne pola: tytul, autor, wydawnictwo, miejsce, rok, ISBN, format, strony, okladka, cena.\n"
        << "Wpisz 'koniec', aby zakonczyc wprowadzanie dla tej ksiazki.\n";

    string linia;
    while (getline(cin, linia)) {
        string trimmed = Przytnij(linia);
        if (trimmed == "koniec" || trimmed == "KONIEC") {
            break;
        }
        if (trimmed.empty()) continue;

        size_t dwukropek = trimmed.find(':');
        if (dwukropek == string::npos) {
            cout << " [Blad] Niepoprawny format. Uzyj: nazwa pola: wartosc\n";
            continue;
        }

        string klucz = Przytnij(trimmed.substr(0, dwukropek));
        string wartosc = Przytnij(trimmed.substr(dwukropek + 1));

        if (klucz == "tytul") tytul = wartosc;
        else if (klucz == "autor") autor = wartosc;
        else if (klucz == "wydawnictwo") wydawnictwo = wartosc;
        else if (klucz == "miejsce") miejsce = wartosc;
        else if (klucz == "rok") {
            try { rok = stoi(wartosc); }
            catch (...) { cout << " [Blad] Niepoprawny rok.\n"; }
        }
        else if (klucz == "ISBN" || klucz == "isbn") ISBN = wartosc;
        else if (klucz == "format") format = wartosc;
        else if (klucz == "strony") {
            try { strony = stoi(wartosc); }
            catch (...) { cout << " [Blad] Niepoprawna liczba stron.\n"; }
        }
        else if (klucz == "okladka") okladka = wartosc;
        else if (klucz == "cena") {
            try { cena = stod(wartosc); }
            catch (...) { cout << " [Blad] Niepoprawna cena.\n"; }
        }
        else {
            cout << " [Blad] Nieznana nazwa pola: '" << klucz << "'\n";
        }
    }
}

// ============================================================================
// c) Funkcja porównująca dwie książki pod kątem opłacalności
// ============================================================================
int Porownaj(const Ksiazka& X, const Ksiazka& Y) {
    auto ObliczWartoscPunktowa = [](const Ksiazka& k) -> double {
        double mnoznikFormatu = 1.0;
        string f = k.PobierzFormat();
        if (f == "A4" || f == "C3") mnoznikFormatu = 1.5;
        else if (f == "A5" || f == "B5") mnoznikFormatu = 1.0;
        else if (f == "A6" || f == "B6") mnoznikFormatu = 0.8;

        double mnoznikOkladki = 1.0;
        string o = k.PobierzOkladke();
        if (o.find("twarda") != string::npos || o.find("szyta") != string::npos) {
            mnoznikOkladki = 1.3;
        }
        else if (o.find("bindowana") != string::npos) {
            mnoznikOkladki = 0.9;
        }

        double wartoscMaterialu = k.PobierzStrony() * mnoznikFormatu * mnoznikOkladki;
        if (wartoscMaterialu <= 0.0) wartoscMaterialu = 1.0;

        return (k.PobierzCene() / wartoscMaterialu) * 100.0;
        };

    double kosztJednostkowyX = ObliczWartoscPunktowa(X);
    double kosztJednostkowyY = ObliczWartoscPunktowa(Y);

    const double EPS = 0.0001;
    if (kosztJednostkowyX < kosztJednostkowyY - EPS) return -1;
    if (kosztJednostkowyX > kosztJednostkowyY + EPS) return 1;
    return 0;
}

// ============================================================================
// d) i e) Funkcja główna testująca klasę i wyszukująca najkorzystniejszą książkę
// ============================================================================
int main() {
    cout << "==============================================================\n";
    cout << "     SYSTEM ZARZADZANIA INFORMACJA O KSIAZKACH W KSIEGARNI     \n";
    cout << "==============================================================\n\n";

    // d) Utworzenie tablicy obiektów przy użyciu konstruktora wieloargumentowego
    const int ROZMIAR = 3;
    Ksiazka magazyn[ROZMIAR] = {
        Ksiazka("Sezon na winobranie", "Patricia Atkinson", "Wydawnictwo Literackie", "Krakow",
                2007, "978-83-08-03975-5", "A5", 348, "miekka ze skrzydelkami", 39.90),
        Ksiazka("Jezdzac po cytrynach. Optymista w Andaluzji", "Chris Stewart", "Pascal", "Bielsko-Biala",
                2005, "978-83-7304-453-1", "A5", 288, "miekka", 34.50),
        Ksiazka("Jeszcze raz Prowansja", "Peter Mayle", "Prószyński i S-ka", "Warszawa",
                2002, "978-83-7255-098-9", "A5", 240, "szyta twarda", 44.00)
    };

    cout << "Zainicjalizowano " << ROZMIAR << " domyslne obiekty ksiazek.\n";
    cout << "Czy chcesz zaktualizowac dane ksiazki z klawiatury metoda Skanuj()? (t/n): ";
    char odp;
    if (cin >> odp && (odp == 't' || odp == 'T')) {
        cin.ignore(1000, '\n');
        cout << "Wybierz indeks ksiazki do aktualizacji (0, 1 lub 2): ";
        int idx;
        if (cin >> idx && idx >= 0 && idx < ROZMIAR) {
            cin.ignore(1000, '\n');
            magazyn[idx].Skanuj();
        }
        else {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Niepoprawny indeks. Pomijam wprowadzanie.\n";
        }
    }
    else {
        cin.ignore(1000, '\n');
    }

    // Wyświetlenie wszystkich książek za pomocą Drukuj()
    cout << "\n================ KATALOG KSIAZEK W BAZIE ================\n";
    for (int i = 0; i < ROZMIAR; ++i) {
        cout << "\n[Pozycja #" << (i + 1) << "]\n";
        magazyn[i].Drukuj();
    }

    // e) Algorytm wyboru najbardziej opłacalnej książki z użyciem Porownaj()
    int indeksNajlepszej = 0;
    for (int i = 1; i < ROZMIAR; ++i) {
        if (Porownaj(magazyn[i], magazyn[indeksNajlepszej]) < 0) {
            indeksNajlepszej = i;
        }
    }

    // Wyświetlenie podstawowych danych za pomocą metod dostępowych
    cout << "\n================ NAJBARDZIEJ OPLACALNA KSIAZKA ================\n";
    const Ksiazka& najlepsza = magazyn[indeksNajlepszej];
    cout << "Algorytm (uwzgledniajacy cene, liczbe stron, format i typ okladki)\n"
        << "wybral nastepujaca pozycje jako najbardziej ekonomiczny zakup:\n\n";
    cout << "  * Tytul:       " << najlepsza.PobierzTytul() << "\n"
        << "  * Autor:       " << najlepsza.PobierzAutora() << "\n"
        << "  * Format:      " << najlepsza.PobierzFormat() << "\n"
        << "  * Strony:      " << najlepsza.PobierzStrony() << "\n"
        << "  * Okladka:     " << najlepsza.PobierzOkladke() << "\n"
        << "  * Cena:        " << fixed << setprecision(2)
        << najlepsza.PobierzCene() << " PLN\n";
    cout << "================================================================\n";

    return 0;
}