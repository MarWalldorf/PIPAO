#include "Pracownik.h"

Pracownik::Pracownik() : Osoba(), indeks(0), pensja(0.0) {}

Pracownik::~Pracownik() {}

void Pracownik::odczytaj() {
    Osoba::odczytaj();
    std::cout << "Podaj numer indeksu/identyfikatora pracownika: ";
    std::cin >> indeks;
    std::cout << "Podaj zarobiona pensje pracownika: ";
    std::cin >> pensja;
}

void Pracownik::wyswietl() const {
    std::cout << "[Typ: Pracownik]\n";
    Osoba::wyswietl();
    std::cout << "Indeks:          " << indeks << "\n"
        << "Pensja:          " << pensja << " PLN\n";
}

double Pracownik::dochod() const {
    // Pensja pracownika stanowi koszt przedsiebiorstwa (dochod ujemny)
    return -pensja;
}