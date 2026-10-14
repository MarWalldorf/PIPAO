#ifndef ABSOLWENT_H
#define ABSOLWENT_H

#include "Osoba.h"
#include <string>

class Absolwent : public Osoba {
private:
    std::string dyplom;
    double wplata;

public:
    Absolwent();

    void odczytaj() override;
    void wyswietl() const override;
    double koszt() const override;
};

#endif