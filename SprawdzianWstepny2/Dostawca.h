#ifndef DOSTAWCA_H
#define DOSTAWCA_H

#include "Osoba.h"
#include <string>

class Dostawca : public Osoba {
private:
    std::string hurtownia;
    double wydatek;

public:
    Dostawca();
    virtual ~Dostawca() override;

    virtual void odczytaj() override;
    virtual void wyswietl() const override;
    virtual double dochod() const override;
};

#endif