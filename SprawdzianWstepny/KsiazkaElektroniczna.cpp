#include "KsiazkaElektroniczna.h"

KsiazkaElektroniczna::KsiazkaElektroniczna(const std::string& t, const std::string& a, const std::string& w,
    const std::string& m, int r, const std::string& i, int s, double c,
    const std::string& fm, int pl, int pj)
    : Ksiazka(t, a, w, m, r, i, s, c),
    format(fm), pliki(pl), pojemnosc(pj) {}

void KsiazkaElektroniczna::OpisTechniczny(std::ostream& wyjscie) const {
    wyjscie << "  format pliku: " << format << "\n";
    wyjscie << "  liczba plikow: " << pliki << "\n";
    wyjscie << "  pojemnosc ksiazki: " << pojemnosc << " kB\n";
}