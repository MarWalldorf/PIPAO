#include <iostream>
#include <cmath>
using namespace std;

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

int main()
{
    int maksilosc;
    cout << "Podaj maksymalna ilosc figur: ";
    cin >> maksilosc;

    typedef Figura* WFigura;
    WFigura* figury = new WFigura[maksilosc];

    int ilosc = 0;
    while (ilosc < maksilosc) {
        cout << "\nMenu figur do wyboru:" << endl;
        cout << "[1] Prostokat" << endl;
        cout << "[2] Trojkat" << endl;
        cout << "[3] Kolo" << endl;

        int wybor;
        cout << "Podaj numer figury lub -1, aby zakonczyc: ";
        cin >> wybor;
        if (wybor < 0) break;

        switch (wybor) {
        case 1: {
            int wys, szer;
            cout << "Podaj wysokosc prostokata: ";
            cin >> wys;
            cout << "Podaj szerokosc prostokata: ";
            cin >> szer;
            figury[ilosc++] = new Prostokat(wys, szer);
            break;
        }
        case 2: {
            int podst;
            cout << "Podaj podstawe trojkata: ";
            cin >> podst;
            figury[ilosc++] = new Trojkat(podst);
            break;
        }
        case 3: {
            int prom;
            cout << "Podaj promien kola: ";
            cin >> prom;
            figury[ilosc++] = new Kolo(prom);
            break;
        }
        default:
            cout << "Niepoprawny wybor!" << endl;
            continue;
        }
    }

    int max_linie;
    cout << "\nPodaj maksymalna liczbe linii na ekranie: ";
    cin >> max_linie;

    // Rysowanie w zwyk³ym porz¹dku
    cout << "\n==========================================" << endl;
    cout << "RYSOWANIE W ZWYKLYM PORZADKU" << endl;
    cout << "==========================================" << endl;
    int linie = 0;
    for (int i = 0; i < ilosc; i++) {
        int wys_figury = figury[i]->daj_rozmiar() + 1; // wysokoœæ figury + linijka odstêpu
        if (linie + wys_figury > max_linie) {
            cout << "\n[Przerwano: osiagnieto limit linii (" << linie << "/" << max_linie << ")]" << endl;
            break;
        }
        figury[i]->rysuj();
        cout << endl;
        linie += wys_figury;
    }

    // Rysowanie w porz¹dku odwrotnym
    cout << "\n==========================================" << endl;
    cout << "RYSOWANIE W PORZADKU ODWROTNYM" << endl;
    cout << "==========================================" << endl;
    linie = 0;
    for (int i = ilosc - 1; i >= 0; i--) {
        int wys_figury = figury[i]->daj_rozmiar() + 1;
        if (linie + wys_figury > max_linie) {
            cout << "\n[Przerwano: osiagnieto limit linii (" << linie << "/" << max_linie << ")]" << endl;
            break;
        }
        figury[i]->rysuj();
        cout << endl;
        linie += wys_figury;
    }

    // Zwolnienie pamiêci
    for (int i = 0; i < ilosc; i++) {
        delete figury[i];
    }
    delete[] figury;

    cout << "\nNacisnij Enter, aby zakonczyc...";
    cin.ignore();
    cin.get();

    return 0;
}