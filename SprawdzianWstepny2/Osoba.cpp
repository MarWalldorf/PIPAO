#include "Osoba.h"
#include <limits>

Osoba::Osoba() : nazwisko(""), imie(""), adres("") {}

Osoba::~Osoba() {}

void Osoba::odczytaj() {
    std::cout << "Podaj nazwisko: ";
    std::getline(std::cin >> std::ws, nazwisko);
    std::cout << "Podaj imie: ";
    std::getline(std::cin >> std::ws, imie);
    std::cout << "Podaj adres: ";
    std::getline(std::cin >> std::ws, adres);
}

void Osoba::wyswietl() const {
    std::cout << "Imie i nazwisko: " << imie << " " << nazwisko << "\n"
        << "Adres:           " << adres << "\n";
}