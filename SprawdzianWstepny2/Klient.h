#ifndef KLIENT_H
#define KLIENT_H

#include "Osoba.h"
#include <string>

class Klient : public Osoba {
private:
    std::string pesel;
    double naleznosc;

public:
    Klient();
    virtual ~Klient() override;

    virtual void odczytaj() override;
    virtual void wyswietl() const override;
    virtual double dochod() const override;
};

#endif