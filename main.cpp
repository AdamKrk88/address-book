#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <stdio.h>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>


using namespace std;


struct Kontakt {
    int id;
    string imie, nazwisko, numerTelefonu, email, adres;
};


string usunSpacjeNaKoncu (string napis) {
    string napisPomocniczy ="";
    int liczbaSpacjiNaKoncu = 0;

    int i = napis.length() - 1;
    while (napis[i] == 32) {
        liczbaSpacjiNaKoncu++;
        i--;
    }

    for (int j = 0; j < napis.length() - liczbaSpacjiNaKoncu; j++) {
        napisPomocniczy = napisPomocniczy + napis[j];
    }

    return napisPomocniczy;
}


void pobierzDaneZPliku(vector<Kontakt> &kontakty) {
    fstream bazaDanych;
    string liniaZPliku;
    int numerWskazujacyDaneKontaktu = 1;
    int numerKontaktu = 0;
    bazaDanych.open("ksiazka.txt",ios::in);

    if (bazaDanych.good()) {
        while (getline(bazaDanych,liniaZPliku,'|') && liniaZPliku != "\n") {
            if (numerWskazujacyDaneKontaktu == 1) kontakty.push_back(Kontakt ());
            switch(numerWskazujacyDaneKontaktu) {
            case 1:
                kontakty[numerKontaktu].id = atoi(liniaZPliku.c_str());
                break;
            case 2:
                kontakty[numerKontaktu].imie = usunSpacjeNaKoncu(liniaZPliku);
                break;
            case 3:
                kontakty[numerKontaktu].nazwisko = usunSpacjeNaKoncu(liniaZPliku);
                break;
            case 4:
                kontakty[numerKontaktu].numerTelefonu = liniaZPliku;
                break;
            case 5:
                kontakty[numerKontaktu].email = liniaZPliku;
                break;
            case 6:
                kontakty[numerKontaktu].adres = liniaZPliku;
                break;
            }

            if (numerWskazujacyDaneKontaktu == 6) {
                numerWskazujacyDaneKontaktu = 0;
                numerKontaktu++;
            }
            numerWskazujacyDaneKontaktu++;
        }
        bazaDanych.close();
    }

    else {
        cout << "Nie odczytano zadnego pliku" << endl;
    }
}


void wyswietlImie (vector<Kontakt> &kontakty) {
    int liczbaKontakow = kontakty.size();
    string imie;
    cout << "Podaj imie: ";
    cin >> imie;
    cout << endl;

    transform(imie.begin(),imie.end(),imie.begin(),::tolower);

    string imieZKsiazkiMale = "";

    int liczbaOsobODanymImieniu = 0;

    for (int i = 0; i < liczbaKontakow; i++) {
        imieZKsiazkiMale = kontakty[i].imie;
        transform(imieZKsiazkiMale.begin(),imieZKsiazkiMale.end(),imieZKsiazkiMale.begin(),::tolower);

        if (imieZKsiazkiMale == imie) {
            cout << "ID osoby: " << kontakty[i].id << endl;
            cout << kontakty[i].imie << " " << kontakty[i].nazwisko << endl;
            cout << "Numer telefonu: " << kontakty[i].numerTelefonu << "\t";
            cout << "Email: " << kontakty[i].email << endl;
            cout << "Adres: " << kontakty[i].adres << endl;
            cout << "***********************************************************" << endl;
            liczbaOsobODanymImieniu ++;
        }
    }

    if (liczbaOsobODanymImieniu == 0) cout << "Brak osob o tym imieniu";

    cout << endl;
    cout << "Nacisnij enter, aby powrocic do menu glownego" << endl;
    cin.sync();
    getchar();
}


void wyswietlNazwisko (vector<Kontakt> &kontakty) {
    int liczbaKontakow = kontakty.size();
    string nazwisko;
    cout << "Podaj nazwisko: ";
    cin >> nazwisko;
    cout << endl;

    transform(nazwisko.begin(),nazwisko.end(),nazwisko.begin(),::tolower);

    string nazwiskoZKsiazkiMale = "";
    int liczbaOsobODanymNazwisku = 0;

    for (int i = 0; i < liczbaKontakow; i++) {
        nazwiskoZKsiazkiMale = kontakty[i].nazwisko;
        transform(nazwiskoZKsiazkiMale.begin(),nazwiskoZKsiazkiMale.end(),nazwiskoZKsiazkiMale.begin(),::tolower);
        if (nazwiskoZKsiazkiMale == nazwisko) {
            cout << "ID osoby: " << kontakty[i].id << endl;
            cout << kontakty[i].imie << " " << kontakty[i].nazwisko << endl;
            cout << "Numer telefonu: " << kontakty[i].numerTelefonu << "\t";
            cout << "Email: " << kontakty[i].email << endl;
            cout << "Adres: " << kontakty[i].adres << endl;
            cout << "***********************************************************" << endl;
            liczbaOsobODanymNazwisku ++;
        }
    }

    if (liczbaOsobODanymNazwisku == 0) cout << "Brak osob o tym nazwisku";

    cout << endl;
    cout << "Nacisnij enter, aby powrocic do menu glownego" << endl;
    cin.sync();
    getchar();
}


void wyswietlWszyscy (vector<Kontakt> &kontakty) {
    int liczbaKontakow = kontakty.size();

    for (int i = 0; i < liczbaKontakow; i++) {
        cout << "ID osoby: " << kontakty[i].id << endl;
        cout << kontakty[i].imie << " " << kontakty[i].nazwisko << endl;
        cout << "Numer telefonu: " << kontakty[i].numerTelefonu << "\t";
        cout << "Email: " << kontakty[i].email << endl;
        cout << "Adres: " << kontakty[i].adres << endl;
        cout << "***********************************************************" << endl;
    }

    if (liczbaKontakow == 0) cout << "Twoja ksiazka adresowa jest pusta";

    cout << endl;
    cout << "Nacisnij enter aby powrocic do menu glownego" << endl;
    getchar();
    getchar();
}


void dodajPrzyjaciela(vector<Kontakt> &kontakty) {
    int liczbaKontaktow = kontakty.size();
    int dostepneID;
    if (liczbaKontaktow == 0) dostepneID = 1;
    else dostepneID = kontakty[liczbaKontaktow-1].id + 1;
    kontakty.push_back(Kontakt ());
    kontakty[liczbaKontaktow].id = dostepneID;

    cout << "Podaj imie nowego Kontaktu: ";
    cin >> kontakty[liczbaKontaktow].imie;

    cout << "Podaj nazwisko nowego Kontaktu: ";
    cin >> kontakty[liczbaKontaktow].nazwisko;

    cin.sync();
    cout << "Podaj numer telefonu nowego Kontaktu: ";
    getline(cin, kontakty[liczbaKontaktow].numerTelefonu);

    cout << "Podaj email nowego Kontaktu: ";
    cin >> kontakty[liczbaKontaktow].email;

    cin.sync();
    cout << "Podaj adres nowego Kontaktu: ";
    getline(cin, kontakty[liczbaKontaktow].adres);

    fstream bazaDanych;

    bazaDanych.open("ksiazka.txt",ios::out | ios::app);

    if (bazaDanych.good()) {
        bazaDanych << kontakty[liczbaKontaktow].id << "|";
        bazaDanych << kontakty[liczbaKontaktow].imie << "|";
        bazaDanych << kontakty[liczbaKontaktow].nazwisko << "|";
        bazaDanych << kontakty[liczbaKontaktow].numerTelefonu << "|";
        bazaDanych << kontakty[liczbaKontaktow].email << "|";
        bazaDanych << kontakty[liczbaKontaktow].adres << "|";
        bazaDanych << endl;
        bazaDanych.close();
    }

    else {
        cout << "Zapis do pliku sie nie powiodl. Brak dostepu" << endl;
        Sleep(3000);
    }
}


int sprawdzCzyIdIstnieje (vector <Kontakt> &kontakty, int id) {
    for (int i = 0; i < kontakty.size(); i++) {
        if (kontakty[i].id == id) return i;
    }

    return -1;
}


void edytujKontakt (vector <Kontakt> &kontakty, int wybranaOpcja, int elementWektoraOdpowiadajacyKontaktowiDoEdycji) {
    string zmienianePole;
    cout << endl;
    switch (wybranaOpcja) {
    case 1:
        cout << "Podaj nowe imie: ";
        cin >> zmienianePole;
        kontakty[elementWektoraOdpowiadajacyKontaktowiDoEdycji].imie = zmienianePole;
        break;
    case 2:
        cout << "Podaj nowe nazwisko: ";
        cin >> zmienianePole;
        kontakty[elementWektoraOdpowiadajacyKontaktowiDoEdycji].nazwisko = zmienianePole;
        break;
    case 3:
        cout << "Podaj nowy numer telefonu: ";
        cin >> zmienianePole;
        kontakty[elementWektoraOdpowiadajacyKontaktowiDoEdycji].numerTelefonu = zmienianePole;
        break;
    case 4:
        cout << "Podaj nowy email: ";
        cin >> zmienianePole;
        kontakty[elementWektoraOdpowiadajacyKontaktowiDoEdycji].email = zmienianePole;
        break;
    case 5:
        cout << "Podaj nowe adres: ";
        cin.sync();
        getline(cin,zmienianePole);
        kontakty[elementWektoraOdpowiadajacyKontaktowiDoEdycji].adres = zmienianePole;
        break;
    case 6:
        cout << "Powrot do menu";
        Sleep(3000);
        break;
    }
}


void aktualizujPlikTekstowy (vector <Kontakt> kontakty) {
    fstream bazaDanychUpdate;
    bazaDanychUpdate.open("ksiazka.txt",ios::out);
    for (int i = 0; i < kontakty.size(); i++) {
        bazaDanychUpdate << kontakty[i].id << "|";
        bazaDanychUpdate << kontakty[i].imie << "|";
        bazaDanychUpdate << kontakty[i].nazwisko << "|";
        bazaDanychUpdate << kontakty[i].numerTelefonu << "|";
        bazaDanychUpdate << kontakty[i].email << "|";
        bazaDanychUpdate << kontakty[i].adres << "|" << endl;
    }
    bazaDanychUpdate.close();
}


void wyczyscCinZBledu () {
    while (cin.fail()) {
        cin.clear();
        cin.ignore(100,'\n');
    }
}


int main() {
    vector <Kontakt> kontakty;
    pobierzDaneZPliku(kontakty);
    int wybranaOpcja = 0;
    cout << "Ksiazka adresowa. Wybierz jedna opcje podajac jej numer" << endl;

    while (1) {
        if (wybranaOpcja != 0) system("cls");
        cout << "1. Dodaj adresata" << endl;
        cout << "2. Wyszukaj po imieniu" << endl;
        cout << "3. Wyszukaj po nazwisku" << endl;
        cout << "4. Wyswietl wszystkich adresatow" << endl;
        cout << "5. Usun adresata" << endl;
        cout << "6. Edytuj adresata" << endl;
        cout << "9. Zakoncz program" << endl;
        cin.sync();
        cout << "Twoj wybor: ";
        cin >> wybranaOpcja;
        if (cin.fail()) wyczyscCinZBledu ();

        if (wybranaOpcja == 1) {
            system("cls");
            dodajPrzyjaciela(kontakty);
        }

        else if (wybranaOpcja == 2) {
            system("cls");
            wyswietlImie(kontakty);
        }

        else if (wybranaOpcja == 3) {
            system("cls");
            wyswietlNazwisko(kontakty);
        }

        else if (wybranaOpcja == 4) {
            system("cls");
            wyswietlWszyscy(kontakty);
        }

        else if (wybranaOpcja == 5) {
            string potwierdzenieUsuniecia;
            int idKontaktu;
            int elementWektoraOdpowiadajacyKontaktowiDoEdycji;
            system("cls");
            cout << "Podaj ID osoby, ktora chcesz usunac z ksiazki adresowej: ";
            cin >> idKontaktu;
            if (cin.fail()) wyczyscCinZBledu ();
            elementWektoraOdpowiadajacyKontaktowiDoEdycji = sprawdzCzyIdIstnieje(kontakty,idKontaktu);
            if (elementWektoraOdpowiadajacyKontaktowiDoEdycji >=0) {
                cout << "Czy na pewno chcesz usunac kontakt o id " << idKontaktu << " : ";
                cin >> potwierdzenieUsuniecia;
                if (potwierdzenieUsuniecia =="t") {
                    kontakty.erase(kontakty.begin() + elementWektoraOdpowiadajacyKontaktowiDoEdycji);
                    aktualizujPlikTekstowy(kontakty);
                } else {
                    cout << "Wpisz \"t\" jesli chcesz usunac. Kontakt nie zostal usuniety. Powrot do menu glownego";
                    Sleep(3000);
                }
            } else {
                cout << "Nie ma takiego ID. Powrot do menu glownego";
                Sleep(3000);
            }
        }

        else if (wybranaOpcja == 6) {
            int idKontaktu;
            int elementWektoraOdpowiadajacyKontaktowiDoEdycji;
            system("cls");
            cout << "Podaj ID kontaktu: ";
            cin >> idKontaktu;
            if (cin.fail()) wyczyscCinZBledu ();
            elementWektoraOdpowiadajacyKontaktowiDoEdycji = sprawdzCzyIdIstnieje(kontakty,idKontaktu);
            if (elementWektoraOdpowiadajacyKontaktowiDoEdycji >= 0) {
                cout << endl;
                cout << "Edycja danych dla osoby o id: " << idKontaktu <<endl;
                cout << "Jest to: " << kontakty[elementWektoraOdpowiadajacyKontaktowiDoEdycji].imie << " ";
                cout << kontakty[elementWektoraOdpowiadajacyKontaktowiDoEdycji].nazwisko << endl << endl;
                cout << "1. Imie" << endl;
                cout << "2. Nazwisko" << endl;
                cout << "3. Numer telefonu" << endl;
                cout << "4. Email" << endl;
                cout << "5. Adres" << endl;
                cout << "6. Powrot do menu" << endl;
                cin >> wybranaOpcja;
                edytujKontakt(kontakty,wybranaOpcja,elementWektoraOdpowiadajacyKontaktowiDoEdycji);
                if (wybranaOpcja > 0 && wybranaOpcja < 6) aktualizujPlikTekstowy(kontakty);
            } else {
                cout << "Takiego ID nie ma w ksiazce adresowej. Powrot do menu glownego";
                Sleep(3000);
            }
        }

        else if (wybranaOpcja == 9) exit(0);

        else {
            cout << "Taka opcja jest niedostepna. Sprobuj jeszcze raz. Podaj numer" << endl << endl;
            wybranaOpcja = 0;
        }
    }
    return 0;
}
