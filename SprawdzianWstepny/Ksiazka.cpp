#include "Ksiazka.h"

Ksiazka::Ksiazka(const std::string& t, const std::string& a, const std::string& w,
    const std::string& m, int r, const std::string& i, int s, double c)
    : tytul(t), autor(a), wydawnictwo(w), miejsce(m),
    rok(r), ISBN(i), strony(s), cena(c) {}

void Ksiazka::DrukujDane(std::ostream& wyjscie) const {
    wyjscie << tytul << " , " << autor << " , " << wydawnictwo << ", "
        << miejsce << " " << rok << "\n\n";
    wyjscie << "  ISBN: " << ISBN << "\n";
    wyjscie << "  liczba stron: " << strony << "\n";
    wyjscie << "  cena detaliczna: " << cena << " zl\n\n";

    // Polimorficzne wywołanie opisu technicznego
    OpisTechniczny(wyjscie);
    wyjscie << "\n";
}