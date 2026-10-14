#include "Klient.h"

Klient::Klient() : Osoba(), pesel(""), naleznosc(0.0) {}

Klient::~Klient() {}

void Klient::odczytaj() {
    Osoba::odczytaj();
    std::cout << "Podaj PESEL klienta: ";
    std::getline(std::cin >> std::ws, pesel);
    std::cout << "Podaj laczna naleznosc za zakupiony towar: ";
    std::cin >> naleznosc;
}

void Klient::wyswietl() const {
    std::cout << "[Typ: Klient]\n";
    Osoba::wyswietl();
    std::cout << "PESEL:           " << pesel << "\n"
        << "Naleznosc:       " << naleznosc << " PLN\n";
}

double Klient::dochod() const {
    // Naleznosc za towar to przychod/dochod przedsiebiorstwa
    return naleznosc;
}