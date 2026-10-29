#include <iostream>
#include <cmath>
using namespace std;

/* ...wstawic kod klasy bazowej... */

class Figura {
private:
    int rozmiar_;

public:
    Figura(int x) : rozmiar_(x) {}

    virtual ~Figura() {}

    virtual void rysuj() = 0;

    virtual void powieksz(int dx) {
        rozmiar_ += dx;
    }

    int daj_rozmiar() {
        return rozmiar_;
    }
};

void rysuj_obrazek(Figura* fig)
{
    int linie;
    cout << "*******************" << endl;
    linie = 0;
    while (linie < 20) {
        fig->rysuj();
        linie += fig->daj_rozmiar();
        cout << endl;
        fig->powieksz(2);
    }
    linie = 0;
    while (linie < 20) {
        fig->rysuj();
        linie += fig->daj_rozmiar();
        cout << endl;
        fig->powieksz(-2);
    }
    cout << "*******************" << endl;
}

/* ...wstawic kod klas pochodnych... */

class Trojkat : public Figura {
private:
    int podstawa_;

public:
    Trojkat(int podst) : Figura(podst), podstawa_(podst) {}

    void rysuj() {
        for (int i = 1; i <= podstawa_; ++i) {
            for (int j = 0; j < i; ++j) {
                cout << "*";
            }
            cout << endl;
        }
    }

    void powieksz(int dx) {
        Figura::powieksz(dx);
        podstawa_ += dx;
    }
};

class Prostokat : public Figura {
private:
    int wysokosc_;
    int szerokosc_;

public:
    Prostokat(int wys, int szer) : Figura(wys), wysokosc_(wys), szerokosc_(szer) {}

    void rysuj() {
        for (int i = 0; i < wysokosc_; ++i) {
            for (int j = 0; j < szerokosc_; ++j) {
                cout << "*";
            }
            cout << endl;
        }
    }

    void powieksz(int dx) {
        Figura::powieksz(dx);
        wysokosc_ += dx;
        szerokosc_ += dx;
    }
};

class Kolo : public Figura {
private:
    int promien_;

public:
    Kolo(int prom) : Figura(2 * prom + 1), promien_(prom) {}

    void rysuj() {
        for (int y = -promien_; y <= promien_; ++y) {
            for (int x = -promien_; x <= promien_; ++x) {
                if (x * x + y * y <= promien_ * promien_) {
                    cout << "*";
                }
                else {
                    cout << " ";
                }
            }
            cout << endl;
        }
    }

    void powieksz(int dx) {
        Figura::powieksz(dx);
        promien_ += dx;
    }
};

void main()
{
    Prostokat f1(3, 6);
    rysuj_obrazek(&f1);
    cin.ignore(2);
    Trojkat f2(5);
    rysuj_obrazek(&f2);
    cin.ignore(2);
    Kolo f3(4);
    rysuj_obrazek(&f3);
    cin.ignore(2);
}