#include "Kandydat.h"
#include <iostream>

Kandydat::Kandydat() : Osoba(), szkola(""), oplata(0.0) {}

void Kandydat::odczytaj() {
    Osoba::odczytaj(); // Wywolanie aspektu metody z klasy bazowej
    std::cout << "Podaj ukonczona szkole srednia: ";
    std::getline(std::cin >> std::ws, szkola);
    std::cout << "Podaj oplate rekrutacyjna: ";
    std::cin >> oplata;
}

void Kandydat::wyswietl() const {
    std::cout << "[Typ: Kandydat]\n";
    Osoba::wyswietl(); // Wywolanie aspektu metody z klasy bazowej
    std::cout << "Szkola srednia:  " << szkola << "\n"
        << "Oplata rekrut.:  " << oplata << " PLN\n"
        << "Koszt wydzialu:  " << koszt() << " PLN\n";
}

double Kandydat::koszt() const {
    return -oplata; // Oplata to wplyw/przychod, wiec koszt ujemny
}