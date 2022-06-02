#include <iostream>
#include <windows.h>
#include <vector>
#include "ksiazkaAdresowa.h"


using namespace std;


int main() {
    vector <Kontakt> kontakty;
    vector <UzytkownikKsiazki> uzytkownicy;
    pobierzDaneZPlikuUzytkownicy(uzytkownicy);
    int pozycjaUzytkownikaWWektorze = -1;
    int idZalogowanegoUzytkownika = -1;
    int wybranaOpcja = 0;
    int idOstatniegoAdresataZPlikuJakoInt;
    bool czyOstatniKontaktZPlikuZostalUsuniety = false;

    while(idZalogowanegoUzytkownika == -1) {
        if (wybranaOpcja != 0) system("cls");
        cout << "Ksiazka adresowa. Wybierz jedna opcje podajac jej numer" << endl;
        cout << "***********************************************************" << endl;
        cout << "1. Logowanie" << endl;
        cout << "2. Rejestracja" << endl;
        cout << "3. Zamknij program" << endl;
        cout << "***********************************************************" << endl;
        cout << "Twoj wybor to: ";
        cin >> wybranaOpcja;
        wyczyscCinZBledu();

        switch (wybranaOpcja) {
        case 1: {
            pozycjaUzytkownikaWWektorze = sprawdzCzyUzytkownikJestZarejestrowany(uzytkownicy);

            if (pozycjaUzytkownikaWWektorze >= 0) {
                idZalogowanegoUzytkownika = uzytkownicy[pozycjaUzytkownikaWWektorze].zalogujUzytkownika(pozycjaUzytkownikaWWektorze);
            }

            if (idZalogowanegoUzytkownika > 0) {
                idOstatniegoAdresataZPlikuJakoInt = pobierzDaneZPlikuAdresaci(kontakty,uzytkownicy,idZalogowanegoUzytkownika);
            }

            while(idZalogowanegoUzytkownika > 0) {
                system("cls");
                cout << "1. Dodaj adresata" << endl;
                cout << "2. Wyszukaj po imieniu" << endl;
                cout << "3. Wyszukaj po nazwisku" << endl;
                cout << "4. Wyswietl wszystkich adresatow" << endl;
                cout << "5. Usun adresata" << endl;
                cout << "6. Edytuj adresata" << endl;
                cout << "7. Zmien haslo" << endl;
                cout << "8. Wyloguj sie" << endl;
                cin.sync();
                cout << "Twoj wybor: ";
                cin >> wybranaOpcja;

                if (cin.fail()) {
                    wyczyscCinZBledu ();
                }

                switch (wybranaOpcja) {
                case 1:
                    system("cls");
                    dodajPrzyjaciela(kontakty, idZalogowanegoUzytkownika, idOstatniegoAdresataZPlikuJakoInt);
                    idOstatniegoAdresataZPlikuJakoInt++;
                    break;

                case 2:
                    system("cls");
                    wyswietlImie(kontakty);
                    break;

                case 3:
                    system("cls");
                    wyswietlNazwisko(kontakty);
                    break;

                case 4:
                    system("cls");
                    wyswietlWszyscy(kontakty);
                    break;

                case 5:
                    czyOstatniKontaktZPlikuZostalUsuniety = usunKontakt(kontakty, idOstatniegoAdresataZPlikuJakoInt);
                    if (czyOstatniKontaktZPlikuZostalUsuniety == true) idOstatniegoAdresataZPlikuJakoInt = aktualizacjaIdOstatnegoAdresataZPliku();
                    break;

                case 6:
                    edytujKontakt(kontakty);
                    break;

                case 7:
                    zmienHasloUzytkownika(uzytkownicy,idZalogowanegoUzytkownika);
                    aktualizujPlikZUzytkownikami(uzytkownicy);
                    break;

                case 8:
                    wylogujUzytkownika(idZalogowanegoUzytkownika,kontakty);
                    break;

                default:
                    cout << "Taka opcja jest niedostepna. Sprobuj jeszcze raz. Podaj numer" << endl << endl;
                    wybranaOpcja = 0;
                    break;
                }
            }
        }
        break;

        case 2: {
            UzytkownikKsiazki nowyUzytkownik;
            nowyUzytkownik.zarejestrujUzytkownika(uzytkownicy);
            aktualizujPlikZUzytkownikami(uzytkownicy);
        }
        break;

        case 3: {
            exit(0);
        }
        break;

        default: {
            cout << "Wybierz jedna z dostepnych opcji" << endl << endl;
            Sleep(1000);
        }
        break;

        }
    }
}

