#include <iostream>
#include <limits>
#include "BazaOsob.h"
#include "Pracownik.h"
#include "Klient.h"
#include "Dostawca.h"

void wyczyscStrumien() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    BazaOsob baza;
    int wybor = 0;

    do {
        std::cout << "\n============================================\n"
            << "  SYSTEM OBSLUGI DOCHODU PRZEDSIEBIORSTWA   \n"
            << "============================================\n"
            << "1. Dodaj osobe do bazy\n"
            << "2. Usun osobe z bazy\n"
            << "3. Wyswietl wszystkie osoby\n"
            << "4. Oblicz sumaryczny dochod przedsiebiorstwa\n"
            << "5. Wyczysc baze\n"
            << "0. Zakoncz program\n"
            << "Wybierz opcje: ";

        if (!(std::cin >> wybor)) {
            std::cout << "Blad: nalezy podac liczbe calkowita.\n";
            wyczyscStrumien();
            continue;
        }

        switch (wybor) {
        case 1: {
            std::cout << "\nWybierz rodzaj podmiotu:\n"
                << "  1 - Pracownik\n"
                << "  2 - Klient\n"
                << "  3 - Dostawca\n"
                << "Wybor: ";
            int typ = 0;
            if (!(std::cin >> typ)) {
                std::cout << "Niepoprawny wybor.\n";
                wyczyscStrumien();
                break;
            }

            Osoba* nowaOsoba = nullptr;
            if (typ == 1) {
                nowaOsoba = new Pracownik();
            }
            else if (typ == 2) {
                nowaOsoba = new Klient();
            }
            else if (typ == 3) {
                nowaOsoba = new Dostawca();
            }
            else {
                std::cout << "Nieznany typ osoby.\n";
                break;
            }

            std::cout << "\n--- Wprowadzanie danych ---\n";
            nowaOsoba->odczytaj();
            baza.dodaj(nowaOsoba);
            std::cout << "Obiekt zostal pomyslnie dodany do bazy.\n";
            break;
        }

        case 2: {
            if (baza.pobierzRozmiar() == 0) {
                std::cout << "Baza jest pusta, brak elementow do usuniecia.\n";
                break;
            }
            std::cout << "Podaj numer pozycji do usuniecia (0 do "
                << baza.pobierzRozmiar() - 1 << "): ";
            int indeks = -1;
            if (!(std::cin >> indeks)) {
                std::cout << "Bledny indeks.\n";
                wyczyscStrumien();
                break;
            }
            if (baza.usun(indeks)) {
                std::cout << "Obiekt o indeksie " << indeks << " zostal usuniety.\n";
            }
            else {
                std::cout << "Nie znaleziono obiektu o podanym indeksie.\n";
            }
            break;
        }

        case 3:
            std::cout << "\n=== ZAWARTOSC BAZY OSOB ===";
            baza.wyswietlWszystkie();
            break;

        case 4: {
            double suma = baza.obliczCalkowityDochod();
            std::cout << "\n>>> Sumaryczny dochod przedsiebiorstwa w biezacym miesiacu: "
                << suma << " PLN <<<\n";
            break;
        }

        case 5:
            baza.wyczysc();
            std::cout << "Cala zawartosc bazy zostala wyczyszczona.\n";
            break;

        case 0:
            std::cout << "Konczenie programu i zwalnianie pamieci...\n";
            break;

        default:
            std::cout << "Nieznana opcja menu. Sprobuj ponownie.\n";
            break;
        }

    } while (wybor != 0);

    return 0;
}