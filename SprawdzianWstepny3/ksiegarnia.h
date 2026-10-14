#ifndef KSIEGARNIA_H
#define KSIEGARNIA_H

#include <iostream>
#include <string>

// Klasa bazowa
class Ksiazka {
public:
    std::string tytul;
    std::string autor;
    std::string wydawnictwo;
    std::string miejsce;
    int rok;
    std::string ISBN;
    int strony;
    double cena;

    Ksiazka(std::string t, std::string a, std::string w, std::string m, int r, std::string i, int s, double c);
    virtual ~Ksiazka() = default;

    void DrukujDane(std::ostream& wyjscie);
    virtual void OpisTechniczny(std::ostream& wyjscie) = 0; // Czysto wirtualna
};

// Klasa pochodna - KsiazkaPapierowa
class KsiazkaPapierowa : public Ksiazka {
public:
    std::string format;
    std::string okladka;
    int kartki;
    double masa;

    KsiazkaPapierowa(std::string t, std::string a, std::string w, std::string m, int r, std::string i, int s, double c,
        std::string fm, std::string ok, int kr, double ms);

    void OpisTechniczny(std::ostream& wyjscie) override;
};

// Klasa pochodna - KsiazkaElektroniczna
class KsiazkaElektroniczna : public Ksiazka {
public:
    std::string format;
    int pliki;
    int pojemnosc;

    KsiazkaElektroniczna(std::string t, std::string a, std::string w, std::string m, int r, std::string i, int s, double c,
        std::string fm, int pl, int pj);

    void OpisTechniczny(std::ostream& wyjscie) override;
};

// Klasa Koszyk
class Koszyk {
public:
    enum { maxilosc = 100 };

private:
    Ksiazka* ksiazki_[maxilosc];
    int ilosc_;
    double cena_;

public:
    Koszyk();
    void Dodaj(Ksiazka& x);
    void DrukujListe(std::ostream& wyjscie);
    void DrukujFakture(std::ostream& wyjscie);
};

#endif // KSIEGARNIA_H