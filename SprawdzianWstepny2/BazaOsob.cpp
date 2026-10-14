#include "BazaOsob.h"
#include <iomanip>

BazaOsob::BazaOsob(int poczatkowaPojemnosc)
    : rozmiar(0), pojemnosc(poczatkowaPojemnosc > 0 ? poczatkowaPojemnosc : 4) {
    tablica = new Osoba * [pojemnosc];
    for (int i = 0; i < pojemnosc; ++i) {
        tablica[i] = nullptr;
    }
}

BazaOsob::~BazaOsob() {
    wyczysc();
    delete[] tablica;
    tablica = nullptr;
}

void BazaOsob::zmienRozmiar(int nowaPojemnosc) {
    Osoba** nowaTablica = new Osoba * [nowaPojemnosc];
    for (int i = 0; i < rozmiar; ++i) {
        nowaTablica[i] = tablica[i];
    }
    for (int i = rozmiar; i < nowaPojemnosc; ++i) {
        nowaTablica[i] = nullptr;
    }
    delete[] tablica;
    tablica = nowaTablica;
    pojemnosc = nowaPojemnosc;
}

void BazaOsob::dodaj(Osoba* nowaOsoba) {
    if (rozmiar == pojemnosc) {
        zmienRozmiar(pojemnosc * 2);
    }
    tablica[rozmiar++] = nowaOsoba;
}

bool BazaOsob::usun(int indeks) {
    if (indeks < 0 || indeks >= rozmiar) {
        return false;
    }
    delete tablica[indeks];
    for (int i = indeks; i < rozmiar - 1; ++i) {
        tablica[i] = tablica[i + 1];
    }
    tablica[rozmiar - 1] = nullptr;
    --rozmiar;
    return true;
}

void BazaOsob::wyswietlWszystkie() const {
    if (rozmiar == 0) {
        std::cout << "Baza jest pusta.\n";
        return;
    }
    for (int i = 0; i < rozmiar; ++i) {
        std::cout << "\n---------------- [Pozycja " << i << "] ----------------\n";
        tablica[i]->wyswietl();
        std::cout << "Czastkowy wplyw na dochod: " << tablica[i]->dochod() << " PLN\n";
    }
}

double BazaOsob::obliczCalkowityDochod() const {
    double suma = 0.0;
    for (int i = 0; i < rozmiar; ++i) {
        suma += tablica[i]->dochod();
    }
    return suma;
}

void BazaOsob::wyczysc() {
    for (int i = 0; i < rozmiar; ++i) {
        delete tablica[i];
        tablica[i] = nullptr;
    }
    rozmiar = 0;
}

int BazaOsob::pobierzRozmiar() const {
    return rozmiar;
}