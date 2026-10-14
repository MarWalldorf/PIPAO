#include "ksiegarnia.h"
#include <iomanip>

// --- Ksiazka ---
Ksiazka::Ksiazka(std::string t, std::string a, std::string w, std::string m, int r, std::string i, int s, double c)
    : tytul(t), autor(a), wydawnictwo(w), miejsce(m), rok(r), ISBN(i), strony(s), cena(c) {}

void Ksiazka::DrukujDane(std::ostream& wyjscie) {
    wyjscie << tytul << " , " << autor << " , " << wydawnictwo << ", " << miejsce << " " << rok << "\n\n";
    wyjscie << "  ISBN: " << ISBN << "\n";
    wyjscie << "  liczba stron: " << strony << "\n";
    wyjscie << "  cena detaliczna: " << cena << " zl\n\n";
    OpisTechniczny(wyjscie);
}

// --- KsiazkaPapierowa ---
KsiazkaPapierowa::KsiazkaPapierowa(std::string t, std::string a, std::string w, std::string m, int r, std::string i, int s, double c,
    std::string fm, std::string ok, int kr, double ms)
    : Ksiazka(t, a, w, m, r, i, s, c), format(fm), okladka(ok), kartki(kr), masa(ms) {}

void KsiazkaPapierowa::OpisTechniczny(std::ostream& wyjscie) {
    wyjscie << "  format papieru: " << format << "\n";
    wyjscie << "  rodzaj okladki: " << okladka << "\n";
    wyjscie << "  liczba kartek: " << kartki << "\n";
    wyjscie << "  masa ksiazki: " << masa << " g\n";
}

// --- KsiazkaElektroniczna ---
KsiazkaElektroniczna::KsiazkaElektroniczna(std::string t, std::string a, std::string w, std::string m, int r, std::string i, int s, double c,
    std::string fm, int pl, int pj)
    : Ksiazka(t, a, w, m, r, i, s, c), format(fm), pliki(pl), pojemnosc(pj) {}

void KsiazkaElektroniczna::OpisTechniczny(std::ostream& wyjscie) {
    wyjscie << "  format pliku: " << format << "\n";
    wyjscie << "  liczba plikow: " << pliki << "\n";
    wyjscie << "  pojemnosc ksiazki: " << pojemnosc << " kB\n";
}

// --- Koszyk ---
Koszyk::Koszyk() : ilosc_(0), cena_(0.0) {
    for (int i = 0; i < maxilosc; ++i) {
        ksiazki_[i] = nullptr;
    }
}

void Koszyk::Dodaj(Ksiazka& x) {
    if (ilosc_ < maxilosc) {
        ksiazki_[ilosc_] = &x;
        ilosc_++;
        cena_ += x.cena;
    }
}

void Koszyk::DrukujListe(std::ostream& wyjscie) {
    wyjscie << "W twoim koszyku masz ksiazki:\n\n";
    for (int i = 0; i < ilosc_; ++i) {
        wyjscie << (i + 1) << ") ";
        ksiazki_[i]->DrukujDane(wyjscie);
        wyjscie << "\n";
    }
}

void Koszyk::DrukujFakture(std::ostream& wyjscie) {
    wyjscie << "Faktura na zakupione ksiazki:\n\n";

    // 1. Pozioma linia ramki
    // Szerokości komórek z marginesem: 35 znaków + 22 znaki + 12 znaków
    const std::string ramka = " +------------------------------------+-----------------------+------------+\n";

    wyjscie << ramka;

    // 2. Nagłówki kolumn
    wyjscie << " |" << std::setw(35) << "Ksiazka" << " |"
        << std::setw(22) << "ISBN" << " |"
        << std::setw(11) << "Cena zl" << " |\n";

    wyjscie << ramka;

    // 3. Pozycje książek (wiersz 1: tytuł + ISBN + cena, wiersz 2: autor)
    for (int i = 0; i < ilosc_; ++i) {
        wyjscie << " |" << std::setw(35) << ksiazki_[i]->tytul << " |"
            << std::setw(22) << ksiazki_[i]->ISBN << " |"
            << std::setw(11) << ksiazki_[i]->cena << " |\n";

        wyjscie << " |" << std::setw(35) << ksiazki_[i]->autor << " |"
            << std::setw(22) << "" << " |"
            << std::setw(11) << "" << " |\n";

        wyjscie << ramka;
    }

    // 4. Podsumowanie (połączone pierwsze dwie kolumny: 35 + 1 + 22 = 58 znaków)
    wyjscie << " |" << std::setw(56) << "Razem:" << "    |"
        << std::setw(11) << cena_ << " |\n";

    wyjscie << ramka << "\n";
}