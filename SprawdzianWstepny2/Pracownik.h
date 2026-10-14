#ifndef PRACOWNIK_H
#define PRACOWNIK_H

#include "Osoba.h"

class Pracownik : public Osoba {
private:
    int indeks;
    double pensja;

public:
    Pracownik();
    virtual ~Pracownik() override;

    virtual void odczytaj() override;
    virtual void wyswietl() const override;
    virtual double dochod() const override;
};

#endif