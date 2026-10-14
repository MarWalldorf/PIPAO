#include "Dostawca.h"

Dostawca::Dostawca() : Osoba(), hurtownia(""), wydatek(0.0) {}

Dostawca::~Dostawca() {}

void Dostawca::odczytaj() {
    Osoba::odczytaj();
    std::cout << "Podaj nazwe hurtowni: ";
    std::getline(std::cin >> std::ws, hurtownia);
    std::cout << "Podaj laczny wydatek za dostarczony towar: ";
    std::cin >> wydatek;
}

void Dostawca::wyswietl() const {
    std::cout << "[Typ: Dostawca]\n";
    Osoba::wyswietl();
    std::cout << "Hurtownia:       " << hurtownia << "\n"
        << "Wydatek:         " << wydatek << " PLN\n";
}

double Dostawca::dochod() const {
    // Koszt zakupu towarow od dostawcy (dochod ujemny)
    return -wydatek;
}