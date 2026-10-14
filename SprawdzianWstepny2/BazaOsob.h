#ifndef BAZAOSOB_H
#define BAZAOSOB_H

#include "Osoba.h"

class BazaOsob {
private:
    Osoba** tablica;
    int rozmiar;
    int pojemnosc;

    void zmienRozmiar(int nowaPojemnosc);

public:
    BazaOsob(int poczatkowaPojemnosc = 4);
    ~BazaOsob();

    // Zakaz kopiowania dla bezpiecznego zarzadzania pamiecia
    BazaOsob(const BazaOsob&) = delete;
    BazaOsob& operator=(const BazaOsob&) = delete;

    void dodaj(Osoba* nowaOsoba);
    bool usun(int indeks);
    void wyswietlWszystkie() const;
    double obliczCalkowityDochod() const;
    void wyczysc();
    int pobierzRozmiar() const;
};

#endif