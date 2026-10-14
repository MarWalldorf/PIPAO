#include <iostream>
#include "KsiazkaPapierowa.h"
#include "KsiazkaElektroniczna.h"

using namespace std;

int main() {
    KsiazkaPapierowa a("Sezon na winobranie", "Patricia Atkinson",
        "Wydawnictwo Literackie", "Krakow", 2011,
        "978-83-08-04793-4", 228, 34.90,
        "A5", "klejona miekka ze skrzydelkami", 114, 290.0);

    KsiazkaPapierowa b("Jezdzac po cytrynach. Optymista w Andaluzji", "Chris Stewart",
        "Wydawnictwo AA", "Krakow", 2007,
        "978-83-89368-94-2", 254, 39.00,
        "B6", "klejona miekka", 127, 310.5);

    KsiazkaElektroniczna c("Jeszcze raz Prowansja", "Peter Mayle",
        "Proszynski i S-ka", "Warszawa", 2010,
        "978-83-7469-238-0", 168, 24.90,
        "EPUB", 1, 2850);

    cout << "W twoim koszyku masz ksiazki:\n\n";

    cout << "1) "; a.DrukujDane(cout);
    cout << "2) "; b.DrukujDane(cout);
    cout << "3) "; c.DrukujDane(cout);

    return 0;
}