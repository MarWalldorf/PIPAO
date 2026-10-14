#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstring>

// ============================================================================
// Klasa Haslo
// ============================================================================
class Haslo {
    char termin_[50];   // naglowkowy termin
    int nterm_;         // liczba znakow terminu
    char tekst_[500];   // tekst objasniajacy
    int ntek_;          // liczba znakow tekstu

public:
    // Tworzy haslo zerowe
    Haslo() {
        termin_[0] = '\0';
        nterm_ = 0;
        tekst_[0] = '\0';
        ntek_ = 0;
    }

    // Tworzy puste haslo dla podanego terminu
    Haslo(const char* x) {
        if (x != nullptr) {
            strncpy(termin_, x, sizeof(termin_) - 1);
            termin_[sizeof(termin_) - 1] = '\0';
            nterm_ = (int)strlen(termin_);
        }
        else {
            termin_[0] = '\0';
            nterm_ = 0;
        }
        tekst_[0] = '\0';
        ntek_ = 0;
    }

    // Tworzy haslo bedace kopia podanego hasla
    Haslo(const Haslo& H) {
        strcpy(termin_, H.termin_);
        nterm_ = H.nterm_;
        strcpy(tekst_, H.tekst_);
        ntek_ = H.ntek_;
    }

    // Kopiuje podane haslo
    void operator=(const Haslo& H) {
        if (this != &H) {
            strcpy(termin_, H.termin_);
            nterm_ = H.nterm_;
            strcpy(tekst_, H.tekst_);
            ntek_ = H.ntek_;
        }
    }

    // Niszczy zasoby obiektu (np. pamiec dynamiczna)
    ~Haslo() {
        // Brak dynamicznie alokowanej pamieci do zwolnienia
    }

    // Zwraca laczna liczbe znakow hasla
    int Objetosc() const {
        return nterm_ + ntek_;
    }

    // Zwraca tekst hasla
    const char* Tresc() const {
        return tekst_;
    }

    // Porownuje terminy (zwraca true, gdy terminy sa identyczne)
    bool Porownaj(const Haslo& H) const {
        return strcmp(termin_, H.termin_) == 0;
    }

    // Edytuje tekst hasla w konsoli
    void Edytuj() {
        printf("Podaj nowy tekst dla hasla \"%s\": ", termin_);
        // Wczytanie linii tekstu (do znaku nowej linii)
        // Format %[^\n] wczytuje spacje, spacja przed % usuwa biale znaki z bufora
        if (scanf(" %499[^\n]", tekst_) == 1) {
            ntek_ = (int)strlen(tekst_);
        }
    }

    // Drukuje termin i tekst hasla na ekranie
    void Drukuj() const {
        printf("Termin : %s\n", termin_);
        printf("Tekst  : %s\n", tekst_);
        printf("Dlugosc: %d znakow (termin: %d, tresc: %d)\n", Objetosc(), nterm_, ntek_);
    }
};

// ============================================================================
// Klasa Leksykon
// ============================================================================
class Leksykon {
    Haslo tab_[1000];   // tablica obiektow klasy Haslo
    int num_;           // liczba dolaczonych do tablicy hasel

public:
    // Tworzy leksykon w postaci pustej tablicy
    Leksykon() {
        num_ = 0;
    }

    // Tworzy kopie podanego leksykonu (optymalizacja kopiowania: kopiuje tylko istniejace hasla)
    Leksykon(const Leksykon& L) {
        num_ = L.num_;
        for (int i = 0; i < num_; ++i) {
            tab_[i] = L.tab_[i];
        }
    }

    // Kopiuje podany leksykon (optymalizacja kopiowania: kopiuje tylko istniejace hasla)
    void operator=(const Leksykon& L) {
        if (this != &L) {
            num_ = L.num_;
            for (int i = 0; i < num_; ++i) {
                tab_[i] = L.tab_[i];
            }
        }
    }

    // Dolacza podane haslo do leksykonu
    void Dolacz(const Haslo& H) {
        if (num_ < 1000) {
            tab_[num_] = H;
            num_++;
        }
        else {
            printf("Blad: Leksykon jest pelny (maks. 1000 hasel).\n");
        }
    }

    // Zwraca liczbe hasel w leksykonie
    int LiczbaHasel() const {
        return num_;
    }

    // Zwraca laczna liczbe znakow w leksykonie
    int LiczbaZnakow() const {
        int suma = 0;
        for (int i = 0; i < num_; ++i) {
            suma += tab_[i].Objetosc();
        }
        return suma;
    }

    // Zwraca tresc szukanego hasla (lub nullptr, jesli haslo nie istnieje)
    const char* Szukaj(const Haslo& H) const {
        for (int i = 0; i < num_; ++i) {
            if (tab_[i].Porownaj(H)) {
                return tab_[i].Tresc();
            }
        }
        return nullptr;
    }

    // Drukuje zawartosc leksykonu na ekranie
    void Drukuj() const {
        printf("===== LEKSYKON (%d hasel, %d znakow) =====\n", num_, LiczbaZnakow());
        for (int i = 0; i < num_; ++i) {
            printf("[%d] ", i + 1);
            tab_[i].Drukuj();
            printf("-------------------------------------------\n");
        }
    }
};

// ============================================================================
// c) Kod glowny programu
// ============================================================================
int main() {
    printf("=== Tworzenie i edycja hasel ===\n");
    Haslo h1("Algorytm");
    Haslo h2("Polimorfizm");
    Haslo h3("Hermetyzacja");

    h1.Edytuj();
    h2.Edytuj();
    h3.Edytuj();

    printf("\n=== Podglad pojedynczego hasla ===\n");
    h1.Drukuj();

    printf("\n=== Tworzenie leksykonu i dodawanie hasel ===\n");
    static Leksykon lek; // 'static' przenosi obiekt ze stosu do segmentu danych
    lek.Dolacz(h1);
    lek.Dolacz(h2);
    lek.Dolacz(h3);

    lek.Drukuj();

    printf("\n=== Wyszukiwanie hasla w leksykonie ===\n");
    Haslo szukane("Polimorfizm");
    const char* wynik = lek.Szukaj(szukane);
    if (wynik != nullptr) {
        printf("Znaleziono haslo. Tresc: %s\n", wynik);
    }
    else {
        printf("Nie znaleziono hasla w leksykonie.\n");
    }

    Haslo nieistniejace("Rekurencja");
    const char* brak = lek.Szukaj(nieistniejace);
    if (brak == nullptr) {
        printf("Haslo \"%s\" nie wystepuje w leksykonie.\n", "Rekurencja");
    }

    printf("\n=== Kopiowanie leksykonu ===\n");
    static Leksykon kopiaLeksykonu = lek; // static
    printf("Liczba hasel w skopiowanym leksykonie: %d\n", kopiaLeksykonu.LiczbaHasel());

    static Leksykon innyLek; // static
    innyLek = lek;
    printf("Liczba znakow w przypisanym leksykonie: %d\n", innyLek.LiczbaZnakow());

    return 0;
}