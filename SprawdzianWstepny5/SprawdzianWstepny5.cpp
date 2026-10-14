#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <clocale>
using namespace std;

// --- PUNKT A: KLASA WYRAZ ---
class Wyraz {
    char* str_; // wskaźnik do dynamicznego łańcucha
    int len_;   // długość łańcucha

public:
    // Tworzy wyraz w postaci łańcucha pustego
    Wyraz() {
        len_ = 0;
        str_ = (char*)malloc(sizeof(char) * (len_ + 1));
        if (str_ != nullptr) {
            str_[0] = '\0';
        }
    }

    // Tworzy wyraz zawierający podany łańcuch
    Wyraz(const char* s) {
        if (s != nullptr) {
            len_ = (int)strlen(s);
            str_ = (char*)malloc(sizeof(char) * (len_ + 1));
            if (str_ != nullptr) {
                strcpy(str_, s);
            }
        }
        else {
            len_ = 0;
            str_ = (char*)malloc(sizeof(char) * 1);
            if (str_ != nullptr) {
                str_[0] = '\0';
            }
        }
    }

    // Konstruktor kopiujący (głęboka kopia)
    Wyraz(const Wyraz& W) {
        len_ = W.len_;
        str_ = (char*)malloc(sizeof(char) * (len_ + 1));
        if (str_ != nullptr && W.str_ != nullptr) {
            strcpy(str_, W.str_);
        }
    }

    // Operator przypisania
    void operator=(const Wyraz& W) {
        if (this == &W) {
            return;
        }

        if (str_ != nullptr) {
            free(str_);
        }

        len_ = W.len_;
        str_ = (char*)malloc(sizeof(char) * (len_ + 1));
        if (str_ != nullptr && W.str_ != nullptr) {
            strcpy(str_, W.str_);
        }
    }

    // Destruktor
    ~Wyraz() {
        if (str_ != nullptr) {
            free(str_);
            str_ = nullptr;
        }
        len_ = 0;
    }

    // Zwraca długość łańcucha znaków
    int Dlugosc() const {
        return len_;
    }

    // Porównuje łańcuchy (true, jeśli identyczne)
    bool Porownaj(const Wyraz& W) const {
        if (str_ == nullptr || W.str_ == nullptr) {
            return str_ == W.str_;
        }
        return strcmp(str_, W.str_) == 0;
    }

    // Drukuje łańcuch na ekranie
    void Drukuj() const {
        if (str_ != nullptr) {
            printf("%s", str_);
        }
    }
};

// --- PUNKT B: KLASA TEKST ---
class Tekst {
    Wyraz tab_[1000]; // tablica obiektów klasy Wyraz
    int num_;         // liczba dołączonych do tablicy wyrazów

public:
    // Tworzy tekst w postaci pustej tablicy
    Tekst() {
        num_ = 0;
    }

    // Konstruktor kopiujący (kopiuje tylko faktycznie dodane elementy)
    Tekst(const Tekst& T) {
        num_ = T.num_;
        for (int i = 0; i < num_; ++i) {
            tab_[i] = T.tab_[i];
        }
    }

    // Operator przypisania
    void operator=(const Tekst& T) {
        if (this == &T) {
            return;
        }

        num_ = T.num_;
        for (int i = 0; i < num_; ++i) {
            tab_[i] = T.tab_[i];
        }
    }

    // Dołącza podany wyraz do tablicy
    void Dolacz(const Wyraz& W) {
        if (num_ < 1000) {
            tab_[num_] = W;
            num_++;
        }
    }

    // Zwraca liczbę wyrazów w tekście
    int LiczbaWyrazow() const {
        return num_;
    }

    // Zwraca łączną liczbę znaków we wszystkich wyrazach
    int LiczbaZnakow() const {
        int suma = 0;
        for (int i = 0; i < num_; ++i) {
            suma += tab_[i].Dlugosc();
        }
        return suma;
    }

    // Zwraca krotność wystąpienia podanego wyrazu
    int Szukaj(const Wyraz& W) const {
        int licznik = 0;
        for (int i = 0; i < num_; ++i) {
            if (tab_[i].Porownaj(W)) {
                licznik++;
            }
        }
        return licznik;
    }

    // Drukuje tekst na ekranie
    void Drukuj() const {
        for (int i = 0; i < num_; ++i) {
            tab_[i].Drukuj();
            if (i < num_ - 1) {
                printf(" ");
            }
        }
    }
};

// --- PUNKT C: PROGRAM GŁÓWNY ---
int main() {
    setlocale(LC_ALL, "");
    printf("=== 1. TEST KLASY WYRAZ ===\n");
    Wyraz w1("Programowanie");
    Wyraz w2 = w1;                  // Test konstruktora kopiującego
    Wyraz w3;                       // Test konstruktora domyślnego
    w3 = Wyraz("obiektowe");        // Test operatora przypisania

    printf("w1: "); w1.Drukuj(); printf(" (dlugosc: %d)\n", w1.Dlugosc());
    printf("w2: "); w2.Drukuj(); printf(" (kopia w1)\n");
    printf("w3: "); w3.Drukuj(); printf(" (przypisanie)\n");
    printf("Porownanie w1 i w2: %s\n", w1.Porownaj(w2) ? "Zgodne" : "Rozne");
    printf("Porownanie w1 i w3: %s\n\n", w1.Porownaj(w3) ? "Zgodne" : "Rozne");

    printf("=== 2. TEST PRZETWARZANIA NIESFORMATOWANEGO TEKSTU ===\n");
    // Przykładowy surowy tekst z nieregularnymi białymi znakami (spacje, tabulatory, entery, interpunkcja)
    char zrodlo[] = "Niektórzy – czyli nie wszyscy.\n"
        "Nawet nie większość wszystkich, ale mniejszość.\n"
        "Nie licząc szkół, gdzie się musi,\n"
        "i samych poetów,\n"
        "będzie tych osób chyba dwie na tysiąc.\n"

        "Lubią –\n"
        "ale lubi się także rosół z makaronem,\n"
        "lubi się komplementy i kolor niebieski,\n"
        "lubi się stary szalik,\n"
        "lubi się stawiać na swoim,\n"
        "lubi się głaskać psa.\n"

        "Poezję –\n"
        "tylko co to takiego poezja.\n"
        "Niejedna chwiejna odpowiedź\n"
        "na to pytanie już padła.\n"
        "A ja nie wiem i nie wiem i trzymam się tego\n"
        "jak zbawiennej poręczy.\n";

    printf("Niesformatowany tekst wejsciowy:\n\"%s\"\n\n", zrodlo);

    Tekst tekstGlowny;

    // Podział łańcucha na pojedyncze wyrazy za pomocą strtok
    const char* separatory = " \t\n,.;:!?\"()";
    char* token = strtok(zrodlo, separatory);

    while (token != nullptr) {
        Wyraz w(token);
        tekstGlowny.Dolacz(w);
        token = strtok(nullptr, separatory);
    }

    printf("Wynik po wczytaniu do klasy Tekst:\n");
    tekstGlowny.Drukuj();
    printf("\n\n");

    printf("Statystyki tekstu:\n");
    printf("- Liczba wyrazow: %d\n", tekstGlowny.LiczbaWyrazow());
    printf("- Sumaryczna liczba znakow: %d\n\n", tekstGlowny.LiczbaZnakow());

    printf("=== 3. TEST WYSZUKIWANIA KROTNOŚCI WYRAZÓW ===\n");
    Wyraz szukany1("lubi");
    Wyraz szukany2("się");
    Wyraz szukany3("nie");

    printf("Wystapienia slowa \"lubi\": %d\n", tekstGlowny.Szukaj(szukany1));
    printf("Wystapienia slowa \"się\":  %d\n", tekstGlowny.Szukaj(szukany2));
    printf("Wystapienia slowa \"nie\":  %d\n\n", tekstGlowny.Szukaj(szukany3));

    printf("=== 4. TEST KOPIOWANIA OBIEKTU KLASY TEKST ===\n");
    Tekst kopiaTekstu = tekstGlowny; // Konstruktor kopiujący klasy Tekst
    Tekst przypisanyTekst;
    przypisanyTekst = tekstGlowny;   // Operator przypisania klasy Tekst

    printf("Kopia tekstu (Liczba wyrazow: %d): ", kopiaTekstu.LiczbaWyrazow());
    kopiaTekstu.Drukuj();
    printf("\n");

    return 0;
}