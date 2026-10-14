#include "Student.h"
#include <iostream>

Student::Student() : Osoba(), album(""), stypendium(0.0) {}

void Student::odczytaj() {
    Osoba::odczytaj();
    std::cout << "Podaj numer albumu: ";
    std::getline(std::cin >> std::ws, album);
    std::cout << "Podaj kwote stypendium naukowego: ";
    std::cin >> stypendium;
}

void Student::wyswietl() const {
    std::cout << "[Typ: Student]\n";
    Osoba::wyswietl();
    std::cout << "Nr albumu:       " << album << "\n"
        << "Stypendium:      " << stypendium << " PLN\n"
        << "Koszt wydzialu:  " << koszt() << " PLN\n";
}

double Student::koszt() const {
    return stypendium; // Wydatek uczelni - koszt dodatni
}