#ifndef KSIAZKA_H
#define KSIAZKA_H

#include <iostream>
#include <string>

class Ksiazka {
private:
    std::string tytul;
    std::string autor;
    std::string wydawnictwo;
    std::string miejsce;
    int rok;
    std::string ISBN;
    int strony;
    double cena;

public:
    Ksiazka(const std::string& t, const std::string& a, const std::string& w,
        const std::string& m, int r, const std::string& i, int s, double c);
    virtual ~Ksiazka() = default;

    void DrukujDane(std::ostream& wyjscie) const;
    virtual void OpisTechniczny(std::ostream& wyjscie) const = 0;
};

#endif // KSIAZKA_H