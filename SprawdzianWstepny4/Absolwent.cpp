#include "Absolwent.h"
#include <iostream>

Absolwent::Absolwent() : Osoba(), dyplom(""), wplata(0.0) {}

void Absolwent::odczytaj() {
    Osoba::odczytaj();
    std::cout << "Podaj numer dyplomu: ";
    std::getline(std::cin >> std::ws, dyplom);
    std::cout << "Podaj wplate za egzamin koncowy: ";
    std::cin >> wplata;
}

void Absolwent::wyswietl() const {
    std::cout << "[Typ: Absolwent]\n";
    Osoba::wyswietl();
    std::cout << "Nr dyplomu:      " << dyplom << "\n"
        << "Wplata za egz.:  " << wplata << " PLN\n"
        << "Koszt wydzialu:  " << koszt() << " PLN\n";
}

double Absolwent::koszt() const {
    return -wplata; // Przychod wydzialu - koszt ujemny
}