#include "KsiazkaPapierowa.h"

KsiazkaPapierowa::KsiazkaPapierowa(const std::string& t, const std::string& a, const std::string& w,
    const std::string& m, int r, const std::string& i, int s, double c,
    const std::string& fm, const std::string& ok, int kr, double ms)
    : Ksiazka(t, a, w, m, r, i, s, c),
    format(fm), okladka(ok), kartki(kr), masa(ms) {}

void KsiazkaPapierowa::OpisTechniczny(std::ostream& wyjscie) const {
    wyjscie << "  format papieru: " << format << "\n";
    wyjscie << "  rodzaj okladki: " << okladka << "\n";
    wyjscie << "  liczba kartek: " << kartki << "\n";
    wyjscie << "  masa ksiazki: " << masa << " g\n";
}