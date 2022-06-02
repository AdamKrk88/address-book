#include <iostream>
#include <vector>

using namespace std;


string usunSpacjeNaKoncu (string napis);
void wyczyscCinZBledu ();


struct Kontakt {
    int idKontaktu, idUzytkownika;
    string imie, nazwisko, numerTelefonu, email, adres;
};


class UzytkownikKsiazki {

private:
    int id;
    string nazwa, haslo;

public:
    int zwrocId ();
    string zwrocNazwa ();
    string zwrocHaslo ();
    void zarejestrujUzytkownika (vector<UzytkownikKsiazki> &uzytkownicy);
    int zalogujUzytkownika (int pozycjaUzytkownikaWWektorze);

    UzytkownikKsiazki (int = 0, string = "Brak", string = "Brak");

    friend void pobierzDaneZPlikuUzytkownicy (vector<UzytkownikKsiazki> &uzytkownicy);
    friend void zmienHasloUzytkownika (vector<UzytkownikKsiazki> &uzytkownicy, int idZalogowanegoUzytkownika);
};

int sprawdzCzyUzytkownikJestZarejestrowany (vector<UzytkownikKsiazki> &uzytkownicy);
int zwrocIndeksdlaPodanegoIdUzytkownika (vector <UzytkownikKsiazki> &uzytkownicy, int idUzytkownika);
int zwrocIndeksdlaPodanegoIdKontaktu (vector <Kontakt> &kontakty, int id);
string wydzielInformacjeZJednejLiniiPliku (string liniaZPliku, int numerElementuZeStringa);
string wydzielCzescPlikuPoPierwszyStalymElemencie (string liniaZPliku);
int pobierzDaneZPlikuAdresaci(vector<Kontakt> &kontakty, vector<UzytkownikKsiazki> &uzytkownicy, int idUzytkownika);
void przepiszIAktualizujPlikZAdresatami (vector<Kontakt> kontakty, int idZmienianegoAdresata);
void wyswietlImie (vector<Kontakt> &kontakty);
void wyswietlNazwisko (vector<Kontakt> &kontakty);
void wyswietlWszyscy (vector<Kontakt> &kontakty);
void dodajPrzyjaciela(vector<Kontakt> &kontakty, int idUzytkownika, int idOstatniegoAdresataZPlikuJakoInt);
bool usunKontakt (vector<Kontakt> &kontakty, int idOstatniegoAdresataZPlikuJakoInt);
int aktualizacjaIdOstatnegoAdresataZPliku ();
void zmienWybranePolePrzyEdycji (vector <Kontakt> &kontakty, int wybranaOpcja, int elementWektoraOdpowiadajacyKontaktowiDoEdycji);
void edytujKontakt (vector<Kontakt> &kontakty);
void aktualizujPlikZUzytkownikami (vector<UzytkownikKsiazki> &uzytkownicy);
void wylogujUzytkownika (int &idZalogowanegoUzytkownika, vector<Kontakt> &kontakty);
void zmienHasloUzytkownika (vector<UzytkownikKsiazki> &uzytkownicy, int idZalogowanegoUzytkownika);
void pobierzDaneZPlikuUzytkownicy (vector<UzytkownikKsiazki> &uzytkownicy);
