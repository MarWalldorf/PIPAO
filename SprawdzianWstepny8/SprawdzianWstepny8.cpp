#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <cmath>

using namespace std;

class Monitor {
private:
    string producent;
    int gwarancja;        // okres w miesiącach
    double przekatna;     // w calach
    int pion;             // rozdzielczość pionowa w px
    int poziom;           // rozdzielczość pozioma w px
    int rok;              // rok produkcji
    string technologia;   // np. LCD, LED, OLED, QLED
    int gniazda;          // liczba gniazd wyjściowych/wejściowych
    bool glosniki;        // flaga posiadania głośników
    double cena;          // cena detaliczna w PLN

public:
    // a) Konstruktory
    Monitor();
    Monitor(string pr, int gw, double pk, int pn, int pz,
        int rk, string tc, int gn, bool gl, double cn);

    // a) Metody operacyjne
    void Wyswietl() const;
    void Odczytaj();

    // b) Metody dostępowe (gettery)
    string PobierzProducenta() const;
    int PobierzGwarancje() const;
    double PobierzPrzekatna() const;
    int PobierzPion() const;
    int PobierzPoziom() const;
    int PobierzRok() const;
    string PobierzTechnologie() const;
    int PobierzGniazda() const;
    bool PobierzGlosniki() const;
    double PobierzCene() const;
};

// ==========================================================
// DEFINICJE METOD KLASY MONITOR POZA KLASĄ
// ==========================================================

// Konstruktor bezargumentowy
Monitor::Monitor()
    : producent("Nieznany"), gwarancja(24), przekatna(24.0), pion(1080),
    poziom(1920), rok(2024), technologia("LED"), gniazda(2),
    glosniki(false), cena(500.0) {}

// Konstruktor z parametrami
Monitor::Monitor(string pr, int gw, double pk, int pn, int pz,
    int rk, string tc, int gn, bool gl, double cn)
    : producent(pr), gwarancja(gw), przekatna(pk), pion(pn),
    poziom(pz), rok(rk), technologia(tc), gniazda(gn),
    glosniki(gl), cena(cn) {}

// Metoda wyświetlająca dane w sformatowanej ramce ze znakami graficznymi
void Monitor::Wyswietl() const {
    cout << "+---------------------------------------------------+\n";
    cout << "| " << left << setw(20) << "Model / Producent:" << setw(29) << producent << " |\n";
    cout << "| " << left << setw(20) << "Przekatna:" << setw(25) << przekatna << " cali|\n";
    cout << "| " << left << setw(20) << "Rozdzielczosc:" << setw(29) << (to_string(poziom) + " x " + to_string(pion)) << " |\n";
    cout << "| " << left << setw(20) << "Technologia:" << setw(29) << technologia << " |\n";
    cout << "| " << left << setw(20) << "Gwarancja:" << setw(23) << gwarancja << " mies. |\n";
    cout << "| " << left << setw(20) << "Gniazda:" << setw(29) << gniazda << " |\n";
    cout << "| " << left << setw(20) << "Glosniki:" << setw(29) << (glosniki ? "TAK" : "NIE") << " |\n";
    cout << "| " << left << setw(20) << "Rok produkcji:" << setw(29) << rok << " |\n";
    cout << "| " << left << setw(20) << "Cena:" << fixed << setprecision(2) << setw(25) << cena << " PLN |\n";
    cout << "+---------------------------------------------------+\n";
}

// Pomocnicza funkcja czyszcząca spacje z początku i końca tekstu
static string Przytnij(const string& str) {
    size_t start = str.find_first_not_of(" \t\r\n");
    if (start == string::npos) return "";
    size_t end = str.find_last_not_of(" \t\r\n");
    return str.substr(start, end - start + 1);
}

// Metoda odczytująca dane w formacie poleceń: "nazwa pola: wartosc"
void Monitor::Odczytaj() {
    cout << "Wprowadz dane monitora linia po linii (format: 'pole: wartosc').\n";
    cout << "Dostepne pola: producent, gwarancja, przekatna, pion, poziom, rok, technologia, gniazda, glosniki, cena.\n";
    cout << "Wpisz 'koniec' lub nacisnij Enter w pustej linii, aby zakonczyc wprowadzanie:\n";

    string linia;
    while (getline(cin, linia)) {
        string oczyszczona = Przytnij(linia);
        if (oczyszczona.empty() || oczyszczona == "koniec" || oczyszczona == "exit") {
            break;
        }

        size_t dwukropek = oczyszczona.find(':');
        if (dwukropek == string::npos) {
            cout << "  [!] Niepoprawny format. Uzyj 'pole: wartosc'.\n";
            continue;
        }

        string pole = Przytnij(oczyszczona.substr(0, dwukropek));
        string wartosc = Przytnij(oczyszczona.substr(dwukropek + 1));
        transform(pole.begin(), pole.end(), pole.begin(), ::tolower);

        try {
            if (pole == "producent") {
                producent = wartosc;
            }
            else if (pole == "gwarancja") {
                gwarancja = stoi(wartosc);
            }
            else if (pole == "przekatna") {
                przekatna = stod(wartosc);
            }
            else if (pole == "pion") {
                pion = stoi(wartosc);
            }
            else if (pole == "poziom") {
                poziom = stoi(wartosc);
            }
            else if (pole == "rok") {
                rok = stoi(wartosc);
            }
            else if (pole == "technologia") {
                technologia = wartosc;
            }
            else if (pole == "gniazda") {
                gniazda = stoi(wartosc);
            }
            else if (pole == "glosniki") {
                string lowerVal = wartosc;
                transform(lowerVal.begin(), lowerVal.end(), lowerVal.begin(), ::tolower);
                glosniki = (lowerVal == "tak" || lowerVal == "true" || lowerVal == "1");
            }
            else if (pole == "cena") {
                cena = stod(wartosc);
            }
            else {
                cout << "  [!] Nieznane pole: " << pole << "\n";
            }
        }
        catch (...) {
            cout << "  [!] Blad parsowania wartosci dla pola: " << pole << "\n";
        }
    }
}

// Gettery (sekcja b)
string Monitor::PobierzProducenta() const { return producent; }
int Monitor::PobierzGwarancje() const { return gwarancja; }
double Monitor::PobierzPrzekatna() const { return przekatna; }
int Monitor::PobierzPion() const { return pion; }
int Monitor::PobierzPoziom() const { return poziom; }
int Monitor::PobierzRok() const { return rok; }
string Monitor::PobierzTechnologie() const { return technologia; }
int Monitor::PobierzGniazda() const { return gniazda; }
bool Monitor::PobierzGlosniki() const { return glosniki; }
double Monitor::PobierzCene() const { return cena; }

// ==========================================================
// c) FUNKCJA PORÓWNUJĄCA DWA MONITORY
// ==========================================================
int Porownaj(const Monitor& X, const Monitor& Y) {
    auto ObliczWskaznikJakosci = [](const Monitor& m) -> double {
        double punkty = 0.0;

        // Liczba pikseli w megapikselach
        double megapiksele = (static_cast<double>(m.PobierzPoziom()) * m.PobierzPion()) / 1000000.0;
        punkty += megapiksele * 30.0;

        // Gwarancja (3 pkt za każdy miesiąc)
        punkty += m.PobierzGwarancje() * 3.0;

        // Przekątna (5 pkt za cal)
        punkty += m.PobierzPrzekatna() * 5.0;

        // Porty (15 pkt za gniazdo)
        punkty += m.PobierzGniazda() * 15.0;

        // Głośniki (25 pkt bonusu)
        if (m.PobierzGlosniki()) punkty += 25.0;

        // Technologia matrycy
        string tech = m.PobierzTechnologie();
        transform(tech.begin(), tech.end(), tech.begin(), ::toupper);
        if (tech.find("OLED") != string::npos) {
            punkty += 150.0;
        }
        else if (tech.find("QLED") != string::npos) {
            punkty += 100.0;
        }
        else if (tech.find("IPS") != string::npos) {
            punkty += 60.0;
        }
        else if (tech.find("VA") != string::npos) {
            punkty += 40.0;
        }
        else {
            punkty += 20.0;
        }

        // Punkty na 1 PLN ceny
        if (m.PobierzCene() <= 0.0) return punkty;
        return punkty / m.PobierzCene();
        };

    double oplacalnoscX = ObliczWskaznikJakosci(X);
    double oplacalnoscY = ObliczWskaznikJakosci(Y);

    const double EPSILON = 0.0001;
    if (abs(oplacalnoscX - oplacalnoscY) < EPSILON) {
        return 0;
    }
    // Wartość ujemna oznacza, że X jest bardziej opłacalny
    return (oplacalnoscX > oplacalnoscY) ? -1 : 1;
}

// ==========================================================
// d) i e) KOD GŁÓWNY PROGRAMU
// ==========================================================
int main() {
    cout << "=== SKLEP INTERNETOWY - BAZA MONITOROW ===\n\n";

    // d) Utworzenie tablicy obiektów przy użyciu konstruktora argumentowego
    const int ROZMIAR = 3;
    Monitor sklep[ROZMIAR] = {
        Monitor("Dell UltraSharp", 36, 27.0, 1440, 2560, 2024, "IPS", 4, false, 1499.00),
        Monitor("Samsung Odyssey", 24, 32.0, 2160, 3840, 2023, "OLED", 3, true, 3299.00),
        Monitor("LG UltraGear", 24, 24.0, 1080, 1920, 2022, "LED", 2, false, 999.00)
    };

    cout << "Domyslnie zainicjalizowano " << ROZMIAR << " monitory.\n";
    cout << "Czy chcesz zaktualizowac dane jednego z nich z klawiatury? (wpisz 0, 1, 2 lub -1 aby pominac): ";

    int indeks;
    if (cin >> indeks && indeks >= 0 && indeks < ROZMIAR) {
        string dummy;
        getline(cin, dummy); // czyszczenie bufora po cin >>
        cout << "\nAktualizacja danych dla monitora indeks [" << indeks << "]:\n";
        sklep[indeks].Odczytaj();
    }
    else {
        cin.clear();
        string dummy;
        getline(cin, dummy);
        cout << "Pominieto odczyt z klawiatury.\n";
    }

    // Wyświetlenie wszystkich obiektów
    cout << "\n=== LISTA DOSTEPNYCH MONITOROW ===\n";
    for (int i = 0; i < ROZMIAR; ++i) {
        cout << "\nMonitor #" << (i + 1) << ":\n";
        sklep[i].Wyswietl();
    }

    // e) Wyszukiwanie najbardziej opłacalnego monitora
    int najlepszyIndeks = 0;
    for (int i = 1; i < ROZMIAR; ++i) {
        if (Porownaj(sklep[i], sklep[najlepszyIndeks]) < 0) {
            najlepszyIndeks = i;
        }
    }

    // Prezentacja wybranego monitora
    cout << "\n===================================================\n";
    cout << "      NAJBARDZIEJ OPALACALNY ZAKUP W SKLEPIE       \n";
    cout << "===================================================\n";
    cout << "Producent:   " << sklep[najlepszyIndeks].PobierzProducenta() << "\n";
    cout << "Przekatna:   " << sklep[najlepszyIndeks].PobierzPrzekatna() << " cali\n";
    cout << "Cena:        " << fixed << setprecision(2) << sklep[najlepszyIndeks].PobierzCene() << " PLN\n";
    cout << "Gwarancja:   " << sklep[najlepszyIndeks].PobierzGwarancje() << " miesiecy\n";
    cout << "Matryca:     " << sklep[najlepszyIndeks].PobierzTechnologie() << "\n";
    cout << "---------------------------------------------------\n";

    return 0;
}