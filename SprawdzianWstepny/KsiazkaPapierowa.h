#ifndef KSIAZKAPAPIEROWA_H
#define KSIAZKAPAPIEROWA_H

#include "Ksiazka.h"

class KsiazkaPapierowa : public Ksiazka {
private:
    std::string format;
    std::string okladka;
    int kartki;
    double masa;

public:
    KsiazkaPapierowa(const std::string& t, const std::string& a, const std::string& w,
        const std::string& m, int r, const std::string& i, int s, double c,
        const std::string& fm, const std::string& ok, int kr, double ms);

    void OpisTechniczny(std::ostream& wyjscie) const override;
};

#endif // KSIAZKAPAPIEROWA_H