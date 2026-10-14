#include <iostream>
#include "ksiegarnia.h"

using namespace std;

int main() {
    Koszyk koszyk;

    // 1. Ksiazka papierowa: Historia literatury angielskiej - Przemyslaw Mroczkowski
    KsiazkaPapierowa a("Historia literatury angielskiej", "Przemyslaw Mroczkowski",
        "Ossolineum", "Wroclaw", 1986,
        "83-04-00784-3", 648, 85.0,
        "B5", "szyta twarda", 324, 920.0);

    // 2. Ksiazka papierowa: Historia literatury wloskiej - Jozef Heistein
    KsiazkaPapierowa b("Historia literatury wloskiej", "Jozef Heistein",
        "Ossolineum", "Wroclaw", 1994,
        "83-04-03777-7", 340, 55.5,
        "A5", "klejona miekka", 170, 410.0);

    // 3. Ksiazka elektroniczna (e-book): Historia literatury francuskiej - Jerzy Adamski
    KsiazkaElektroniczna c("Historia literatury francuskiej", "Jerzy Adamski",
        "Ossolineum", "Wroclaw", 2005,
        "83-04-04712-8", 412, 49.9,
        "PDF", 1, 8420);

    // Dodanie ksiazek do koszyka
    koszyk.Dodaj(a);
    koszyk.Dodaj(b);
    koszyk.Dodaj(c);

    // Wyswietlenie listy oraz faktury
    koszyk.DrukujListe(cout);
    koszyk.DrukujFakture(cout);

    return 0;
}