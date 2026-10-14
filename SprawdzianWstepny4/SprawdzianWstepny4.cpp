#include <iostream>
#include <limits>
#include "Osoba.h"
#include "Kandydat.h"
#include "Student.h"
#include "Absolwent.h"

void zwolnijOsoby(Osoba**& baza, int& rozmiar) {
    for (int i = 0; i < rozmiar; ++i) {
        delete baza[i];
    }
    rozmiar = 0;
}

void dodajDoBazy(Osoba**& baza, int& rozmiar, int& pojemnosc, Osoba* nowaOsoba) {
    if (rozmiar >= pojemnosc) {
        int nowaPojemnosc = (pojemnosc == 0) ? 2 : pojemnosc * 2;
        Osoba** nowaBaza = new Osoba * [nowaPojemnosc];
        for (int i = 0; i < rozmiar; ++i) {
            nowaBaza[i] = baza[i];
        }
        delete[] baza;
        baza = nowaBaza;
        pojemnosc = nowaPojemnosc;
    }
    baza[rozmiar++] = nowaOsoba;
}

void usunZBazy(Osoba** baza, int& rozmiar, int indeks) {
    if (indeks < 0 || indeks >= rozmiar) {
        std::cout << "Niepoprawny indeks obiektu w bazie!\n";
        return;
    }
    delete baza[indeks];
    for (int i = indeks; i < rozmiar - 1; ++i) {
        baza[i] = baza[i + 1];
    }
    --rozmiar;
    std::cout << "Obiekt usuniety pomyslnie.\n";
}

int main() {
    int pojemnosc = 4;
    int rozmiar = 0;
    Osoba** baza = new Osoba * [pojemnosc];

    int wybor = 0;

    do {
        std::cout << "\n============================================\n"
            << "  SYSTEM OBSLUGI KOSZTOW WYDZIALU UCZELNI   \n"
            << "============================================\n"
            << "1. Dodaj osobe do bazy\n"
            << "2. Usun osobe z bazy\n"
            << "3. Wyswietl wszystkie osoby w bazie\n"
            << "4. Oblicz sumaryczny koszt wydzialu\n"
            << "5. Wyczysc baze (usun wszystkie obiekty)\n"
            << "0. Zakoncz program\n"
            << "Wybierz opcje: ";

        if (!(std::cin >> wybor)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Niepoprawny format danych!\n";
            continue;
        }

        switch (wybor) {
        case 1: {
            int podTyp = 0;
            std::cout << "\nWybierz grupe:\n"
                << "  1 - Kandydat\n"
                << "  2 - Student\n"
                << "  3 - Absolwent\n"
                << "Wybor: ";
            std::cin >> podTyp;

            Osoba* nowy = nullptr;
            if (podTyp == 1) {
                nowy = new Kandydat();
            }
            else if (podTyp == 2) {
                nowy = new Student();
            }
            else if (podTyp == 3) {
                nowy = new Absolwent();
            }
            else {
                std::cout << "Nieznany typ osoby!\n";
                break;
            }

            dodajDoBazy(baza, rozmiar, pojemnosc, nowy);
            std::cout << "\nWprowadz dane:\n";
            nowy->odczytaj();
            std::cout << "Osoba dodana pomyslnie.\n";
            break;
        }
        case 2: {
            if (rozmiar == 0) {
                std::cout << "Baza jest pusta.\n";
                break;
            }
            int idx = 0;
            std::cout << "Podaj numer obiektu do usuniecia (0 do " << rozmiar - 1 << "): ";
            std::cin >> idx;
            usunZBazy(baza, rozmiar, idx);
            break;
        }
        case 3: {
            if (rozmiar == 0) {
                std::cout << "Baza jest pusta.\n";
                break;
            }
            std::cout << "\n--- LISTA OSOB W BAZIE (" << rozmiar << ") ---\n";
            for (int i = 0; i < rozmiar; ++i) {
                std::cout << "\n[" << i << "] ";
                baza[i]->wyswietl();
            }
            break;
        }
        case 4: {
            double suma = 0.0;
            for (int i = 0; i < rozmiar; ++i) {
                suma += baza[i]->koszt();
            }
            std::cout << "\n>>> Laczny bilans kosztow wydzialu: " << suma << " PLN <<<\n";
            if (suma < 0.0) {
                std::cout << "(Wydzial wygenerowal czysty zysk/przychod w biezacym miesiacu)\n";
            }
            else if (suma > 0.0) {
                std::cout << "(Wydzial poniosl wydatki przewyzszajace wplywy)\n";
            }
            break;
        }
        case 5: {
            zwolnijOsoby(baza, rozmiar);
            std::cout << "Wszystkie obiekty zostaly usuniete z bazy.\n";
            break;
        }
        case 0:
            std::cout << "Zamykanie programu...\n";
            break;
        default:
            std::cout << "Nieznana opcja menu!\n";
            break;
        }
    } while (wybor != 0);

    // Sprzatanie zasobow dynamicznych
    zwolnijOsoby(baza, rozmiar);
    delete[] baza;
    baza = nullptr;

    return 0;
}