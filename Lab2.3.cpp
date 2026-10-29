#include <iostream>
#include <fstream>
#include <vector>
#include <string>

// ============================================================================
// Klasa bazowa: Figura
// ============================================================================
class Figura {
private:
    int rozmiar_;

public:
    Figura(int rozmiar) : rozmiar_(rozmiar) {
        std::cout << "  [Konstruktor Figura] utworzono figure o rozmiarze: " << rozmiar_ << std::endl;
    }

    virtual ~Figura() {
        std::cout << "  [Destruktor Figura] zniszczono figure o rozmiarze: " << rozmiar_ << std::endl;
    }

    // Czysta metoda wirtualna (abstract) z parametrem std::ostream&
    virtual void Rysuj(std::ostream& wyjscie) = 0;

    // Metoda polimorficzna powiekszajaca ogolny rozmiar
    virtual void Powieksz(int skok) {
        rozmiar_ += skok;
    }

    int Rozmiar() const {
        return rozmiar_;
    }
};

// ============================================================================
// Klasa pochodna: Trojkat
// ============================================================================
class Trojkat : public Figura {
private:
    int podstawa_;

public:
    Trojkat(int podstawa) : Figura(podstawa), podstawa_(podstawa) {
        std::cout << "  [Konstruktor Trojkat] podstawa = " << podstawa_ << std::endl;
    }

    ~Trojkat() override {
        std::cout << "  [Destruktor Trojkat] podstawa = " << podstawa_ << std::endl;
    }

    void Rysuj(std::ostream& wyjscie) override {
        for (int i = 1; i <= podstawa_; ++i) {
            for (int j = 0; j < i; ++j) {
                wyjscie << "*";
            }
            wyjscie << "\n";
        }
    }

    void Powieksz(int skok) override {
        Figura::Powieksz(skok);
        podstawa_ += skok;
        if (podstawa_ < 1) podstawa_ = 1;
    }
};

// ============================================================================
// Klasa pochodna: Prostokat
// ============================================================================
class Prostokat : public Figura {
private:
    int wysokosc_;
    int szerokosc_;

public:
    Prostokat(int wysokosc, int szerokosc)
        : Figura(wysokosc), wysokosc_(wysokosc), szerokosc_(szerokosc) {
        std::cout << "  [Konstruktor Prostokat] " << wysokosc_ << "x" << szerokosc_ << std::endl;
    }

    ~Prostokat() override {
        std::cout << "  [Destruktor Prostokat] " << wysokosc_ << "x" << szerokosc_ << std::endl;
    }

    void Rysuj(std::ostream& wyjscie) override {
        for (int i = 0; i < wysokosc_; ++i) {
            for (int j = 0; j < szerokosc_; ++j) {
                wyjscie << "*";
            }
            wyjscie << "\n";
        }
    }

    void Powieksz(int skok) override {
        Figura::Powieksz(skok);
        wysokosc_ += skok;
        szerokosc_ += skok;
        if (wysokosc_ < 1) wysokosc_ = 1;
        if (szerokosc_ < 1) szerokosc_ = 1;
    }
};

// ============================================================================
// Klasa pochodna: Kolo
// ============================================================================
class Kolo : public Figura {
private:
    int promien_;

public:
    // Rozmiar w pionie to 2 * prom + 1 wierszy
    Kolo(int promien)
        : Figura(2 * promien + 1), promien_(promien) {
        std::cout << "  [Konstruktor Kolo] promien = " << promien_ << std::endl;
    }

    ~Kolo() override {
        std::cout << "  [Destruktor Kolo] promien = " << promien_ << std::endl;
    }

    void Rysuj(std::ostream& wyjscie) override {
        for (int y = -promien_; y <= promien_; ++y) {
            for (int x = -promien_; x <= promien_; ++x) {
                if (x * x + y * y <= promien_ * promien_) {
                    wyjscie << "*";
                }
                else {
                    wyjscie << " ";
                }
            }
            wyjscie << "\n";
        }
    }

    void Powieksz(int skok) override {
        Figura::Powieksz(2 * skok);
        promien_ += skok;
        if (promien_ < 1) promien_ = 1;
    }
};

// ============================================================================
// Klasa agregujaca: Rysunek
// ============================================================================
class Rysunek {
private:
    std::string nazwa_;
    int limit_;
    std::vector<Figura*> sklad_; // Relacja agregacji "sklad_" 0..*

public:
    Rysunek(std::string nazwa, int limit) : nazwa_(nazwa), limit_(limit) {
        std::cout << "[Konstruktor Rysunek] Nazwa: \"" << nazwa_
            << "\", limit linii: " << limit_ << std::endl;
    }

    ~Rysunek() {
        std::cout << "\n[Destruktor Rysunek] Czyszczenie skladowych figur..." << std::endl;
        for (Figura* fig : sklad_) {
            delete fig;
        }
        sklad_.clear();
        std::cout << "[Destruktor Rysunek] Rysunek \"" << nazwa_ << "\" zostal zniszczony." << std::endl;
    }

    void Wstaw(Figura* skladnik) {
        if (skladnik != nullptr) {
            sklad_.push_back(skladnik);
            std::cout << "  -> Dodano figure do rysunku \"" << nazwa_ << "\"." << std::endl;
        }
    }

    std::string Nazwa() const {
        return nazwa_;
    }

    int Limit() const {
        return limit_;
    }

    void Wyswietl() {
        std::cout << "\n============================================\n";
        std::cout << "WYDRUK RYSUNKU: " << nazwa_ << " (Ekran)\n";
        std::cout << "============================================\n";

        int linie = 0;
        for (size_t i = 0; i < sklad_.size(); ++i) {
            int linie_figury = sklad_[i]->Rozmiar() + 1; // rozmiar figury + odstep
            if (linie + linie_figury > limit_) {
                std::cout << "\n[Osiagnieto limit linii (" << linie << "/" << limit_
                    << "). Przerwano wyswietlanie dalszych figur.]\n";
                break;
            }
            sklad_[i]->Rysuj(std::cout);
            std::cout << "\n";
            linie += linie_figury;
        }
    }

    void Zapamietaj() {
        std::string pelna_nazwa = nazwa_ + ".txt";
        std::ofstream plik(pelna_nazwa.c_str());

        if (!plik.is_open()) {
            std::cerr << "Blad podczas zapisu pliku: " << pelna_nazwa << std::endl;
            return;
        }

        std::cout << "\n[Zapamietywanie] Zapisywanie rysunku do pliku: " << pelna_nazwa << "..." << std::endl;
        plik << "RYSUNEK: " << nazwa_ << "\n";
        plik << "============================================\n";

        int linie = 0;
        for (size_t i = 0; i < sklad_.size(); ++i) {
            int linie_figury = sklad_[i]->Rozmiar() + 1;
            if (linie + linie_figury > limit_) {
                plik << "\n[Przerwano zapis: osiagnieto limit linii]\n";
                break;
            }
            sklad_[i]->Rysuj(plik);
            plik << "\n";
            linie += linie_figury;
        }

        plik.close();
        std::cout << "[Zapamietywanie] Pomyslnie zapisano do: " << pelna_nazwa << std::endl;
    }
};

// ============================================================================
// Program glowny
// ============================================================================
int main() {
    std::string nazwa;
    int limit;

    std::cout << "Podaj nazwe rysunku: ";
    std::cin >> nazwa;
    std::cout << "Podaj limit linii dla rysunku: ";
    std::cin >> limit;

    // Tworzenie obiektu rysunku przed interakcja
    Rysunek rysunek(nazwa, limit);

    while (true) {
        std::cout << "\n--- MENU FIGUR ---\n";
        std::cout << "[1] Trojkat\n";
        std::cout << "[2] Prostokat\n";
        std::cout << "[3] Kolo\n";
        std::cout << "[-1] Zakoncz wprowadzanie\n";
        std::cout << "Wybor: ";

        int opcja;
        std::cin >> opcja;

        if (opcja < 0) {
            break;
        }

        Figura* nowa_figura = nullptr;

        switch (opcja) {
        case 1: {
            int podstawa;
            std::cout << "Podaj dlugosc podstawy trojkata: ";
            std::cin >> podstawa;
            nowa_figura = new Trojkat(podstawa);
            break;
        }
        case 2: {
            int wys, szer;
            std::cout << "Podaj wysokosc prostokata: ";
            std::cin >> wys;
            std::cout << "Podaj szerokosc prostokata: ";
            std::cin >> szer;
            nowa_figura = new Prostokat(wys, szer);
            break;
        }
        case 3: {
            int prom;
            std::cout << "Podaj promien kola: ";
            std::cin >> prom;
            nowa_figura = new Kolo(prom);
            break;
        }
        default:
            std::cout << "Niepoprawna opcja! Sprobuj ponownie.\n";
            continue;
        }

        if (nowa_figura != nullptr) {
            rysunek.Wstaw(nowa_figura);
        }
    }

    // Wyswietlenie rysunku na ekranie
    rysunek.Wyswietl();

    // Zapamietanie rysunku w pliku tekstowym o nazwie rysunku
    rysunek.Zapamietaj();

    std::cout << "\nNacisnij Enter, aby zakonczyc program i wywolac destruktory...";
    std::cin.ignore();
    std::cin.get();

    return 0;
}