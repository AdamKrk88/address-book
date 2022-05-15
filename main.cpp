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
    int idKontaktu, idUzytkownika;
    string imie, nazwisko, numerTelefonu, email, adres;
};


struct Uzytkownik {
    int id;
    string nazwa;
    string haslo;
};


void wyczyscCinZBledu () {
    while (cin.fail()) {
        cin.clear();
        cin.ignore(100,'\n');
    }
}


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


int zwrocIndeksdlaPodanegoIdUzytkownika (vector <Uzytkownik> &uzytkownicy, int idUzytkownika) {
    for (int i = 0; i < uzytkownicy.size(); i++) {
        if (uzytkownicy[i].id == idUzytkownika) return i;
    }
    return -1;
}


int zwrocIndeksdlaPodanegoIdKontaktu (vector <Kontakt> &kontakty, int id) {
    for (int i = 0; i < kontakty.size(); i++) {
        if (kontakty[i].idKontaktu == id) return i;
    }
    return -1;
}


string wydzielInformacjeZJednejLiniiPliku (string liniaZPliku, int numerElementuZeStringa) {
    string wydzielonaCzescNapisu;
    int dlugoscLiniiZPliku;
    int dlugoscWydzielonejCzesciNapisu;
    size_t pozycjaPowtarzajacegoSieElementu;
    for (int i = 0; i < numerElementuZeStringa; i++) {
        dlugoscLiniiZPliku = liniaZPliku.length();
        pozycjaPowtarzajacegoSieElementu = liniaZPliku.find("|");
        wydzielonaCzescNapisu = liniaZPliku.substr(0,pozycjaPowtarzajacegoSieElementu);
        dlugoscWydzielonejCzesciNapisu = wydzielonaCzescNapisu.length();

        if (dlugoscWydzielonejCzesciNapisu + 1 < dlugoscLiniiZPliku) liniaZPliku = liniaZPliku.substr(pozycjaPowtarzajacegoSieElementu+1);
    }
    return wydzielonaCzescNapisu;
}


string wydzielCzescPlikuPoPierwszyStalymElemencie (string liniaZPliku) {
    size_t pozycjaPowtarzajacegoSieElementu;
    int dlugoscLiniiZPliku = liniaZPliku.length();
    string pierwszyCzlon;
    string czescPlikuPoPierwszymStalymElemencie = "";
    int dlugoscPierwszegoCzlonu;
    pozycjaPowtarzajacegoSieElementu = liniaZPliku.find("|");
    pierwszyCzlon = liniaZPliku.substr(0,pozycjaPowtarzajacegoSieElementu + 1);
    dlugoscPierwszegoCzlonu = pierwszyCzlon.length();
    if (dlugoscLiniiZPliku > dlugoscPierwszegoCzlonu) czescPlikuPoPierwszymStalymElemencie = liniaZPliku.substr(pozycjaPowtarzajacegoSieElementu + 1);
    return czescPlikuPoPierwszymStalymElemencie;
}


int pobierzDaneZPlikuAdresaci(vector<Kontakt> &kontakty, vector<Uzytkownik> &uzytkownicy, int idUzytkownika) {
    fstream bazaDanych;
    string liniaZPliku;
    string idUzytkownikaWPlikuJakoString;
    int idUzytkownikaWPlikuJakoInt;
    string idOstatniegoAdresataZPlikuJakoString;
    int idOstatniegoAdresataZPlikuJakoInt = 0;
    int numerKontaktu = 0;
    bazaDanych.open("Adresaci.txt",ios::in);
    if (bazaDanych.good()) {
        while (getline(bazaDanych,liniaZPliku) && idUzytkownika > 0) {
            idUzytkownikaWPlikuJakoString = wydzielInformacjeZJednejLiniiPliku(liniaZPliku,2);
            idUzytkownikaWPlikuJakoInt = atoi(idUzytkownikaWPlikuJakoString.c_str());
            idOstatniegoAdresataZPlikuJakoString = wydzielInformacjeZJednejLiniiPliku(liniaZPliku,1);
            idOstatniegoAdresataZPlikuJakoInt = atoi(idOstatniegoAdresataZPlikuJakoString.c_str());
            if (idUzytkownika == idUzytkownikaWPlikuJakoInt) {
                kontakty.push_back(Kontakt ());
                if (kontakty.size() > 1) numerKontaktu++;
                kontakty[numerKontaktu].idKontaktu = atoi(wydzielInformacjeZJednejLiniiPliku(liniaZPliku,1).c_str());
                liniaZPliku = wydzielCzescPlikuPoPierwszyStalymElemencie(liniaZPliku);

                kontakty[numerKontaktu].idUzytkownika = idUzytkownikaWPlikuJakoInt;
                liniaZPliku = wydzielCzescPlikuPoPierwszyStalymElemencie(liniaZPliku);

                kontakty[numerKontaktu].imie = usunSpacjeNaKoncu(wydzielInformacjeZJednejLiniiPliku(liniaZPliku,1));
                liniaZPliku = wydzielCzescPlikuPoPierwszyStalymElemencie(liniaZPliku);

                kontakty[numerKontaktu].nazwisko = usunSpacjeNaKoncu(wydzielInformacjeZJednejLiniiPliku(liniaZPliku,1));
                liniaZPliku = wydzielCzescPlikuPoPierwszyStalymElemencie(liniaZPliku);

                kontakty[numerKontaktu].numerTelefonu = wydzielInformacjeZJednejLiniiPliku(liniaZPliku,1);
                liniaZPliku = wydzielCzescPlikuPoPierwszyStalymElemencie(liniaZPliku);

                kontakty[numerKontaktu].email = wydzielInformacjeZJednejLiniiPliku(liniaZPliku,1);
                liniaZPliku = wydzielCzescPlikuPoPierwszyStalymElemencie(liniaZPliku);

                kontakty[numerKontaktu].adres = wydzielInformacjeZJednejLiniiPliku(liniaZPliku,1);
                liniaZPliku = wydzielCzescPlikuPoPierwszyStalymElemencie(liniaZPliku);
            }
        }
        bazaDanych.close();
    } else {
        int indeksUzytkownika = zwrocIndeksdlaPodanegoIdUzytkownika(uzytkownicy, idUzytkownika);
        cout << endl;
        cout << "Brak dostepu do pliku Adresaci lub plik nie istnieje" << endl;
        cout << "Nacisnij enter aby przejsc do ksiazki adresowej Uzytkownika: " << uzytkownicy[indeksUzytkownika].nazwa << endl;
        getchar();
        getchar();
    }
    return idOstatniegoAdresataZPlikuJakoInt;
}


void przepiszIAktualizujPlikZAdresatami (vector<Kontakt> kontakty, int idZmienianegoAdresata) {
    fstream plikOryginalny;
    fstream plikTymczasowy;
    string liniaZPliku;
    string nazwaPlikuOryginalnego = "Adresaci.txt.";
    string nazwaPlikuTymczasowego = "AdresaciTymczasowy.txt";
    int idAdresataZPlikuOryginalnego;
    int indeksZmienianegoAdresata = zwrocIndeksdlaPodanegoIdKontaktu(kontakty,idZmienianegoAdresata);
    plikOryginalny.open(nazwaPlikuOryginalnego.c_str(),ios::in);
    plikTymczasowy.open(nazwaPlikuTymczasowego.c_str(),ios::out);
    if (plikOryginalny.good() && plikTymczasowy.good()) {
        while (getline(plikOryginalny,liniaZPliku)) {
            idAdresataZPlikuOryginalnego = atoi(wydzielInformacjeZJednejLiniiPliku(liniaZPliku,1).c_str());
            if (idAdresataZPlikuOryginalnego != idZmienianegoAdresata) {
                plikTymczasowy << liniaZPliku << endl;
            } else if ((idAdresataZPlikuOryginalnego == idZmienianegoAdresata) && (indeksZmienianegoAdresata >=0)) {
                plikTymczasowy << kontakty[indeksZmienianegoAdresata].idKontaktu << "|";
                plikTymczasowy << kontakty[indeksZmienianegoAdresata].idUzytkownika << "|";
                plikTymczasowy << kontakty[indeksZmienianegoAdresata].imie << "|";
                plikTymczasowy << kontakty[indeksZmienianegoAdresata].nazwisko << "|";
                plikTymczasowy << kontakty[indeksZmienianegoAdresata].numerTelefonu << "|";
                plikTymczasowy << kontakty[indeksZmienianegoAdresata].email << "|";
                plikTymczasowy << kontakty[indeksZmienianegoAdresata].adres << "|";
                plikTymczasowy << endl;
            } else continue;
        }
        plikOryginalny.close();
        plikTymczasowy.close();
        remove(nazwaPlikuOryginalnego.c_str());
        rename(nazwaPlikuTymczasowego.c_str(),nazwaPlikuOryginalnego.c_str());
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
            cout << "ID osoby: " << kontakty[i].idKontaktu << endl;
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
            cout << "ID osoby: " << kontakty[i].idKontaktu << endl;
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
        cout << "ID osoby: " << kontakty[i].idKontaktu << endl;
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


void dodajPrzyjaciela(vector<Kontakt> &kontakty, int idUzytkownika, int idOstatniegoAdresataZPlikuJakoInt) {
    int liczbaKontaktowDanegoUzytkownika = kontakty.size();
    int dostepneID;
    if (idOstatniegoAdresataZPlikuJakoInt == 0) dostepneID = 1;
    else dostepneID = idOstatniegoAdresataZPlikuJakoInt + 1;
    kontakty.push_back(Kontakt ());
    kontakty[liczbaKontaktowDanegoUzytkownika].idKontaktu = dostepneID;
    kontakty[liczbaKontaktowDanegoUzytkownika].idUzytkownika = idUzytkownika;

    cout << "Podaj imie nowego Kontaktu: ";
    cin >> kontakty[liczbaKontaktowDanegoUzytkownika].imie;

    cout << "Podaj nazwisko nowego Kontaktu: ";
    cin >> kontakty[liczbaKontaktowDanegoUzytkownika].nazwisko;

    cin.sync();
    cout << "Podaj numer telefonu nowego Kontaktu: ";
    getline(cin, kontakty[liczbaKontaktowDanegoUzytkownika].numerTelefonu);

    cout << "Podaj email nowego Kontaktu: ";
    cin >> kontakty[liczbaKontaktowDanegoUzytkownika].email;

    cin.sync();
    cout << "Podaj adres nowego Kontaktu: ";
    getline(cin, kontakty[liczbaKontaktowDanegoUzytkownika].adres);

    fstream bazaDanych;
    bazaDanych.open("Adresaci.txt",ios::out | ios::app);
    if (bazaDanych.good()) {
        bazaDanych << kontakty[liczbaKontaktowDanegoUzytkownika].idKontaktu << "|";
        bazaDanych << kontakty[liczbaKontaktowDanegoUzytkownika].idUzytkownika << "|";
        bazaDanych << kontakty[liczbaKontaktowDanegoUzytkownika].imie << "|";
        bazaDanych << kontakty[liczbaKontaktowDanegoUzytkownika].nazwisko << "|";
        bazaDanych << kontakty[liczbaKontaktowDanegoUzytkownika].numerTelefonu << "|";
        bazaDanych << kontakty[liczbaKontaktowDanegoUzytkownika].email << "|";
        bazaDanych << kontakty[liczbaKontaktowDanegoUzytkownika].adres << "|";
        bazaDanych << endl;
        bazaDanych.close();
    } else {
        cout << "Zapis do pliku sie nie powiodl. Brak dostepu" << endl;
        Sleep(3000);
    }
}


void usunKontakt (vector<Kontakt> &kontakty) {
    string potwierdzenieUsuniecia;
    int idKontaktu;
    int elementWektoraOdpowiadajacyKontaktowiDoEdycji;
    system("cls");
    cout << "Podaj ID osoby, ktora chcesz usunac z ksiazki adresowej: ";
    cin >> idKontaktu;
    if (cin.fail()) wyczyscCinZBledu ();
    elementWektoraOdpowiadajacyKontaktowiDoEdycji = zwrocIndeksdlaPodanegoIdKontaktu(kontakty,idKontaktu);
    if (elementWektoraOdpowiadajacyKontaktowiDoEdycji >=0) {
        cout << "Czy na pewno chcesz usunac kontakt o id " << idKontaktu << "? Potwierdz wpisujac \"t\": ";
        cin >> potwierdzenieUsuniecia;
        if (potwierdzenieUsuniecia =="t") {
            kontakty.erase(kontakty.begin() + elementWektoraOdpowiadajacyKontaktowiDoEdycji);
            przepiszIAktualizujPlikZAdresatami(kontakty,idKontaktu);
        } else {
            cout << "Wpisz \"t\" jesli chcesz usunac. Kontakt nie zostal usuniety. Powrot do menu glownego";
            Sleep(3000);
        }
    } else {
        cout << "Nie ma takiego ID. Powrot do menu glownego";
        Sleep(3000);
    }
}





void zmienWybranePolePrzyEdycji (vector <Kontakt> &kontakty, int wybranaOpcja, int elementWektoraOdpowiadajacyKontaktowiDoEdycji) {
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


void edytujKontakt (vector<Kontakt> &kontakty) {
    int idKontaktu;
    int elementWektoraOdpowiadajacyKontaktowiDoEdycji;
    int wybranaOpcja;
    system("cls");
    cout << "Podaj ID kontaktu: ";
    cin >> idKontaktu;
    if (cin.fail()) wyczyscCinZBledu ();
    elementWektoraOdpowiadajacyKontaktowiDoEdycji = zwrocIndeksdlaPodanegoIdKontaktu(kontakty,idKontaktu);
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
        wyczyscCinZBledu();
        zmienWybranePolePrzyEdycji(kontakty,wybranaOpcja,elementWektoraOdpowiadajacyKontaktowiDoEdycji);
        if (wybranaOpcja > 0 && wybranaOpcja < 6) przepiszIAktualizujPlikZAdresatami(kontakty,idKontaktu);
    } else {
        cout << "Takiego ID nie ma w ksiazce adresowej. Powrot do menu glownego";
        Sleep(3000);
    }


}


void aktualizujPlikZUzytkownikami (vector<Uzytkownik> &uzytkownicy) {
    int iloscZarejestrowanychUzytkownikow = uzytkownicy.size();
    fstream plikZUzytkownikami;
    plikZUzytkownikami.open("Uzytkownicy.txt",ios::out);
    if (plikZUzytkownikami.good()) {
        for (int i = 0; i < iloscZarejestrowanychUzytkownikow; i++) {
            plikZUzytkownikami << uzytkownicy[i].id << "|";
            plikZUzytkownikami << uzytkownicy[i].nazwa << "|";
            plikZUzytkownikami << uzytkownicy[i].haslo;
            if (i != iloscZarejestrowanychUzytkownikow -1) plikZUzytkownikami << endl;
        }
        plikZUzytkownikami.close();
    } else {
        cout << "Nie zaktualizowano pliku Uzytkownicy. Brak dostepu";
    }
}


void zarejestrujUzytkownika (vector<Uzytkownik> &uzytkownicy) {
    system("cls");
    string nazwa, haslo;
    int liczbaUzytkownikow = uzytkownicy.size();
    int liczbaSprawdzonychUzytkownikow = 0;
    uzytkownicy.push_back(Uzytkownik());
    cout << "Podaj nazwe uzytkownika: ";
    cin.sync();
    getline(cin,nazwa);
    nazwa = usunSpacjeNaKoncu(nazwa);
    while (liczbaSprawdzonychUzytkownikow < liczbaUzytkownikow) {
        if (uzytkownicy[liczbaSprawdzonychUzytkownikow].nazwa == nazwa) {
            cout << "Taki uzytkownik juz istnieje. Sprobuj ponownie" << endl;
            cout << "Podaj nazwe uzytkownika: ";
            getline(cin,nazwa);
            nazwa = usunSpacjeNaKoncu(nazwa);

            liczbaSprawdzonychUzytkownikow = 0;
        } else liczbaSprawdzonychUzytkownikow++;
    }
    cout << "Podaj haslo: ";
    cin >> haslo;
    cout << "Uzytkownik " << nazwa << " zostal zarejestrowany";
    uzytkownicy[liczbaUzytkownikow].id = liczbaUzytkownikow + 1;
    uzytkownicy[liczbaUzytkownikow].nazwa = nazwa;
    uzytkownicy[liczbaUzytkownikow].haslo = haslo;
    Sleep(3000);
}


int zalogujUzytkownika (vector<Uzytkownik> &uzytkownicy) {
    system("cls");
    string loginUzytkownika;
    string haslo;
    int iloscZarejestrowanychUzytkownikow = uzytkownicy.size();
    int liczbaProbWpisaniaHasla;
    int idZalogowanegoUzytkownika = -1;
    int pozycjaUzytkownikaWWektorze = -1;
    cout << "Podaj login uzytkownika: ";
    cin.sync();
    getline(cin,loginUzytkownika);
    for (int i = 0; i < iloscZarejestrowanychUzytkownikow; i++) {
        if (uzytkownicy[i].nazwa == loginUzytkownika) {
            pozycjaUzytkownikaWWektorze = i;
            break;
        }
    }
    if (pozycjaUzytkownikaWWektorze >= 0) {
        for (int j = 0; j < 3; j++) {
            cout << "Podaj haslo: ";
            cin >> haslo;
            if (uzytkownicy[pozycjaUzytkownikaWWektorze].haslo == haslo) {
                cout << "Haslo poprawne. Uzytkownik " << uzytkownicy[pozycjaUzytkownikaWWektorze].nazwa << " zalogowany" << endl;
                idZalogowanegoUzytkownika = uzytkownicy[pozycjaUzytkownikaWWektorze].id;
                Sleep(3000);
                break;
            } else {
                liczbaProbWpisaniaHasla = 2-j;
                cout << "Haslo niepoprawne. Liczba prob: " << liczbaProbWpisaniaHasla << endl;
                if (liczbaProbWpisaniaHasla == 0) {
                    cout << "Wszystkie proby bledne. Powrot do menu glownego" << endl;
                    Sleep(3000);
                }
            }
        }
    } else {
        cout << "Nie ma takiego uzytkownika" << endl;
        Sleep(3000);
    }
    return idZalogowanegoUzytkownika;
}


void wylogujUzytkownika (int &idZalogowanegoUzytkownika, vector<Kontakt> &kontakty) {
    idZalogowanegoUzytkownika = -1;
    kontakty.erase(kontakty.begin(),kontakty.end());
}


void zmienHasloUzytkownika (vector<Uzytkownik> &uzytkownicy, int idZalogowanegoUzytkownika) {
    string noweHaslo;
    int indeksZalogowanegoUzytkownikaWWektorze = zwrocIndeksdlaPodanegoIdUzytkownika(uzytkownicy,idZalogowanegoUzytkownika);
    system("cls");
    cout << "Podaj nowe haslo dla Uzytkownika " << uzytkownicy[indeksZalogowanegoUzytkownikaWWektorze].nazwa << ": ";
    cin >> noweHaslo;
    uzytkownicy[indeksZalogowanegoUzytkownikaWWektorze].haslo = noweHaslo;
    cout << "Haslo zmienione";
    Sleep(3000);
}


void pobierzDaneZPlikuUzytkownicy (vector<Uzytkownik> &uzytkownicy) {
    fstream uzytkownicyZarejestrowani;
    string liniaZPliku;
    int numerWskazujacyDaneKontaktu = 1;
    int numerKontaktu = 0;
    size_t pozycja;
    uzytkownicyZarejestrowani.open("Uzytkownicy.txt",ios::in);
    if (uzytkownicyZarejestrowani.good()) {
        while (getline(uzytkownicyZarejestrowani,liniaZPliku,'|') && liniaZPliku != "\n") {
            if (numerWskazujacyDaneKontaktu == 1) uzytkownicy.push_back(Uzytkownik ());
            switch(numerWskazujacyDaneKontaktu) {
            case 1:
                uzytkownicy[numerKontaktu].id = atoi(liniaZPliku.c_str());
                break;
            case 2:
                uzytkownicy[numerKontaktu].nazwa = usunSpacjeNaKoncu(liniaZPliku);
                break;
            case 3:
                pozycja = liniaZPliku.find("\n");

                if ((pozycja!=string::npos) && (liniaZPliku.substr(0,pozycja + 1).size() < liniaZPliku.size())) {
                    uzytkownicy[numerKontaktu].haslo = liniaZPliku.substr(0,pozycja);
                    uzytkownicy.push_back(Uzytkownik());
                    numerKontaktu++;
                    uzytkownicy[numerKontaktu].id = atoi(liniaZPliku.substr(pozycja +1).c_str());
                    numerWskazujacyDaneKontaktu = 1;
                } else {
                    if (pozycja != string::npos) uzytkownicy[numerKontaktu].haslo = liniaZPliku.substr(0,pozycja);
                    else uzytkownicy[numerKontaktu].haslo = liniaZPliku;
                }
                break;
            }
            numerWskazujacyDaneKontaktu++;
        }
        uzytkownicyZarejestrowani.close();
    } else {
        cout << "! Nie odczytano pliku z Uzytkownikami !" << endl;
    }
}







int main() {
    vector <Kontakt> kontakty;
    vector <Uzytkownik> uzytkownicy;
    pobierzDaneZPlikuUzytkownicy(uzytkownicy);
    int idZalogowanegoUzytkownika = -1;
    int wybranaOpcja = 0;
    int idOstatniegoAdresataZPlikuJakoInt;

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
        case 1:
            idZalogowanegoUzytkownika = zalogujUzytkownika(uzytkownicy);
            if (idZalogowanegoUzytkownika > 0) idOstatniegoAdresataZPlikuJakoInt = pobierzDaneZPlikuAdresaci(kontakty,uzytkownicy,idZalogowanegoUzytkownika);

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
                if (cin.fail()) wyczyscCinZBledu ();

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
                    usunKontakt(kontakty);
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
            break;

        case 2:
            zarejestrujUzytkownika(uzytkownicy);
            aktualizujPlikZUzytkownikami(uzytkownicy);
            break;

        case 3:
            exit(0);
            break;

        default:
            cout << "Wybierz jedna z dostepnych opcji" << endl << endl;
            Sleep(3000);
            break;
        }
    }
}

