#ifndef OSOBA_H
#define OSOBA_H

#include <string>
#include <iostream>

class Osoba {
private:
    std::string nazwisko;
    std::string imie;
    std::string adres;

public:
    Osoba();
    virtual ~Osoba();

    virtual void odczytaj();
    virtual void wyswietl() const;
    virtual double dochod() const = 0; // Czysta funkcja wirtualna
};

#endif