#ifndef KSIAZKAELEKTRONICZNA_H
#define KSIAZKAELEKTRONICZNA_H

#include "Ksiazka.h"

class KsiazkaElektroniczna : public Ksiazka {
private:
    std::string format;
    int pliki;
    int pojemnosc;

public:
    KsiazkaElektroniczna(const std::string& t, const std::string& a, const std::string& w,
        const std::string& m, int r, const std::string& i, int s, double c,
        const std::string& fm, int pl, int pj);

    void OpisTechniczny(std::ostream& wyjscie) const override;
};

#endif // KSIAZKAELEKTRONICZNA_H