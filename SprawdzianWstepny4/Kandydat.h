#ifndef KANDYDAT_H
#define KANDYDAT_H

#include "Osoba.h"
#include <string>

class Kandydat : public Osoba {
private:
    std::string szkola;
    double oplata;

public:
    Kandydat();

    void odczytaj() override;
    void wyswietl() const override;
    double koszt() const override;
};

#endif