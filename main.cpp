#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

string wczytajLinie()
{
    string wejscie = "";

    cin.sync();
    getline(cin, wejscie);

    return wejscie;
}

char wczytajZnak()
{
    string wejscie = "";
    char znak = {0};

    while (true)
    {
        cin.sync();
        getline(cin, wejscie);

        if (wejscie.length() == 1)
        {
            znak = wejscie[0];
            break;
        }
        cout << " To nie jest pojedynczy znak. Wpisz ponownie.";
    }
    return znak;
}

struct osoba
{
    int id;
    string imie, nazwisko, numer, email, adres;

};



void dodajAdresata(vector<osoba> &adresat)
{
    osoba dodany;
    osoba ostatni;
    int i;
    if (adresat.size() > 0 )
    {
        ostatni=adresat.back();
        i = ostatni.id;
    }
    else
        i = 0;

    dodany.id = i+ 1;

    cout << "Podaj imie: ";
    dodany.imie = wczytajLinie();

    cout << "Podaj nazwisko: ";
    dodany.nazwisko = wczytajLinie();

    cout << "Podaj numer telefonu: ";
    dodany.numer = wczytajLinie();

    cout << "Podaj email: ";
    dodany.email = wczytajLinie();

    cout << "Podaj adres: ";
    dodany.adres = wczytajLinie();

    adresat.push_back(dodany);

    fstream plik;
    plik.open("ksiazka.txt",ios::out | ios::app);

    plik << dodany.id <<"|";
    plik << dodany.imie << "|";
    plik << dodany.nazwisko << "|";
    plik << dodany.numer << "|";
    plik << dodany.email << "|";
    plik << dodany.adres << "|" << endl;

    plik.close();

    cout << "Osoba dodana do ksiazki." <<endl;

    system("pause");
}

void wczytajadresatZPliku(vector<osoba> &adresat)
{
    string linia;
    string wycinek;

    osoba dodany;

    fstream plik;
    plik.open("ksiazka.txt", ios::app);

    plik.close();


    plik.open("ksiazka.txt", ios::in);


    while(getline(plik, linia))
    {
        istringstream iss(linia);

        getline(iss,wycinek, '|');
        dodany.id = atoi(wycinek.c_str());
        getline(iss, dodany.imie, '|');
        getline(iss, dodany.nazwisko, '|');
        getline(iss, dodany.numer, '|');
        getline(iss, dodany.email, '|');
        getline(iss, dodany.adres, '|');

        adresat.push_back(dodany);
    }
    plik.close();

}

void pokazListe(vector<osoba> adresat)
{
    system("cls");

    cout << "---- LISTA ADRESATOW ----" << endl << endl;

    for (osoba dodany : adresat)
    {
        cout << "Id " << dodany.id << endl;
        cout << "Imie:     " << dodany.imie << endl;
        cout << "Nazwisko: " << dodany.nazwisko << endl;
        cout << "Telefon:  " << dodany.numer << endl;
        cout << "E-mail:   " << dodany.email << endl;
        cout << "Adres:    " << dodany.adres << endl;
        cout << ".........................." << endl;

    }

    system("pause");
}

void wyszukajPoImieniu(vector<osoba> adresat)
{
    string imie;
    int licznik = 0;

    cout << "Podaj imie: ";
    cin >> imie;
    system("cls");

    for (size_t i = 0; i < adresat.size(); i++)
    {
        if(adresat[i].imie == imie)
        {
            licznik++;

            if (licznik == 1)
                cout << "Znalezione adresat o imieniu " << imie <<": " << endl << endl;

            cout << "----------------------------" << endl;
            cout << "Id " << adresat[i].id << endl;
            cout << "Imie:     " << adresat[i].imie << endl;
            cout << "Nazwisko: " << adresat[i].nazwisko << endl;
            cout << "Telefon:  " << adresat[i].numer << endl;
            cout << "E-mail:   " << adresat[i].email << endl;
            cout << "Adres:    " << adresat[i].adres << endl;
            cout << "----------------------------" << endl;
            licznik++;
        }
    }

    if (licznik == 0)
        cout << "Nie ma uzytkownikow z takim imieniem!" << endl;

    system("pause");


}


void wyszukajPoNazwisku(vector<osoba> adresat)
{
    string nazwisko;
    int licznik= 0;


    cout << "Podaj nazwisko: ";
    cin >> nazwisko;
    system("cls");

    for (size_t i = 0; i < adresat.size(); i++)
    {

        if(adresat[i].nazwisko == nazwisko)
        {
            licznik++;

            if (licznik == 1)
                cout << "Znalezione adresat o nazwisku " << nazwisko << ": " << endl << endl;

            cout << "----------------------------" << endl;
            cout << "Id " << adresat[i].id << endl;
            cout << "Imie:     " << adresat[i].imie << endl;
            cout << "Nazwisko: " << adresat[i].nazwisko << endl;
            cout << "Telefon:  " << adresat[i].numer << endl;
            cout << "E-mail:   " << adresat[i].email << endl;
            cout << "Adres:    " << adresat[i].adres << endl;
            cout << "----------------------------" << endl;
            licznik ++;
        }
    }

    if (licznik == 0)
        cout << "Nie ma uzytkownikow z takim nazwiskiem!" << endl;

    system("pause");

}

void usunAdresata(vector <osoba> &adresat)
{
    int id;
    osoba dodany;
    string potw;
    vector <osoba> :: iterator itr = adresat.begin();
    cout << "Podaj ID adresata do usuniecia " << endl;
    cin >> id;

    for (size_t i = 0; i < adresat.size(); i++)
    {
        itr++;
        if(adresat[i].id == id)
        {
            cout << "Potwierdz usuniecie osoby wpisujac t lub anuluj wpisujac n "<< endl;
            cin >> potw;
            cout << endl;
            if(potw == "t")
            {
                adresat.erase(itr-1);
                ofstream plik;
                plik.open("ksiazka.txt",ios::out | ios::trunc);

                for ( size_t i = 0; i < adresat.size(); i++)
                {
                    plik << adresat[i].id <<"|";
                    plik << adresat[i].imie << "|";
                    plik << adresat[i].nazwisko << "|";
                    plik << adresat[i].numer << "|";
                    plik << adresat[i].email << "|";
                    plik << adresat[i].adres << "|" << endl;
                }
                plik.close();
                cout << "Osoba zostala usunieta z ksiazki ";
            }
            else
                cout << "Operacja przerwana" << endl;
        }
    }


    system ("pause");

}

void edytujDane(vector <osoba> &adresat)
{
    int id, opcja;
    string zmiana;

    cout << "Podaj ID adresata do edycji " << endl;
    cin >> id;

    for (size_t i = 0; i < adresat.size(); i++)
    {
        if(adresat[i].id == id)
        {
            cout << "Wybierz dane do edycji: " << endl;
            cout << "1. Imie " <<endl;
            cout << "2. Nazwisko " << endl;
            cout << "3. Telefon " << endl;
            cout << "4. E- mail " << endl;
            cout << "5. Adresa" << endl;
            cin >> opcja ;

            cout << "Podaj nowe dane "<< endl;
            cin >> zmiana;

            switch(opcja)
            {
            case 1:
                adresat[i].imie=zmiana;
                break;
            case 2:
                adresat[i].nazwisko = zmiana;
                break;
            case 3:
                adresat[i].numer = zmiana;
                break;
            case 4:
                adresat[i].email = zmiana;
                break;
            case 5:
                adresat[i].adres = zmiana;
                break;
            }
        }

        ofstream plik;
        plik.open("ksiazka.txt",ios::out | ios::trunc);

        for ( size_t i = 0; i < adresat.size(); i++)
        {
            plik << adresat[i].id <<"|";
            plik << adresat[i].imie << "|";
            plik << adresat[i].nazwisko << "|";
            plik << adresat[i].numer << "|";
            plik << adresat[i].email << "|";
            plik << adresat[i].adres << "|" << endl;
        }

        plik.close();
    }
    cout << "Dane zostaly zmienione" << endl;
    system("pause");
}


int main()
{
    vector<osoba> adresat;
    char wybor;

    wczytajadresatZPliku(adresat);

    while (true)
    {
        system("cls");
        cout << "Witaj w ksiazce adresowej" << endl << endl;
        cout << "Wybierz, co chcesz zrobic: " << endl;
        cout << "1. Dodaj adresata" << endl;
        cout << "2. Wyszukaj po imieniu" << endl;
        cout << "3. Wyszukaj po nazwisku" << endl;
        cout << "4. Wyswietl wszystkich adresatow" << endl;
        cout << "5. Usun adresata" << endl;
        cout << "6. Edytuj adresata" << endl;
        cout << "9. Zakoncz program" << endl;
        cout << endl;
        cout << "Podaj numer opcji z listy" << endl;
        wybor = wczytajZnak();
        system("cls");

        switch(wybor)
        {
        case '1':
            dodajAdresata(adresat);
            break;
        case '2':
            wyszukajPoImieniu(adresat);
            break;
        case '3':
            wyszukajPoNazwisku(adresat);
            break;
        case '4':
            pokazListe(adresat);
            break;
        case '5':
            usunAdresata(adresat);
            break;
        case '6':
            edytujDane(adresat);
            break;
        case '9':
            cout << "Program zakonczyl dzialanie" << endl;
            exit(0);
        }
    }

    return 0;
}
