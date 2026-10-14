#ifndef STUDENT_H
#define STUDENT_H

#include "Osoba.h"
#include <string>

class Student : public Osoba {
private:
    std::string album;
    double stypendium;

public:
    Student();

    void odczytaj() override;
    void wyswietl() const override;
    double koszt() const override;
};

#endif