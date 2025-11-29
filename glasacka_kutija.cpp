#include <iostream>
#include <fstream>
#include <string>
#include <thread> 
#include <chrono>
#include <ctime>
using namespace std;

class vsu {
    public:
    string ime;
    string lt;
    string cy;
    int prisutnost;
    string glasovi;
};
class rez {
    public:
    string labela;
    int rezultat;
    int za;
    int protiv;
    int uzdrzani;
};

string error1 = "\nGreska, uneti ponovo: ";
string error2 = "\nGreska pri unosu\n";

string DATUM() {
    time_t now = time(0); 
    struct tm *local_time = localtime(&now);
    char* date_time_str = asctime(local_time);
    int dan = local_time->tm_mday;
    int mesec = (local_time->tm_mon + 1);
    string day, month;
    if (dan < 10) {
        day = "0" + to_string(dan);
    }
    else {
        day = to_string(dan);
    }
    if (mesec < 10) {
        month = "0" + to_string(mesec);
    }
    else {
        month = to_string(mesec);
    }
    string datum = day + month;
    return datum;
}

void LABELE(rez* danas_rez, string datum) {

    int i;
    string ime_fajla = "labele" + datum + ".txt";
    int br_labela = 0;

    for (i=0; i<64; i++) danas_rez[i].labela = "";

    ifstream fajl;
    fajl.open(ime_fajla);
    if (fajl.is_open()) {
        while (getline(fajl, danas_rez[br_labela].labela)) {
        br_labela++;
        }
    }
}

bool UNOS_LISTE_VSU(vsu* lista_vsu) {
    int i;
    ifstream fajl;
    fajl.open("spisak.txt");

    if (!fajl.is_open()) {
        cout << "Lista vsu nije pronadjena!" << endl;
        return 0;
    }
    for (i=0; i<52; i++) {
        getline(fajl, lista_vsu[i].ime);
    }
    for (i=0; i<52; i++) {
        getline(fajl, lista_vsu[i].lt);
    }
    for (i=0; i<52; i++) {
        getline(fajl, lista_vsu[i].cy);
    }
    return 1;
}

bool UCITAVANJE_PROSLIH_GLASANJA (vsu* juce_vsu, vsu* prekljuce_vsu, vsu* nakljuce_vsu, rez* juce_rez, string juce) {

    string bafer;
    int i;
    float vsu_za_kvorum = 52;
    int kvorum_danas;
    int kvorum_juce;
    int kvorum;
    float kvorum_float;
    

    string ime_fajla = "glasovi" + juce + ".txt";
    ifstream fajl;
    fajl.open(ime_fajla);

    if (!fajl.is_open()) {
        cout << "\nFajl nije pronadjen!\n";
        return 0;
    }
    
    getline(fajl, bafer);
    for (i=0; i<52; i++) {
        nakljuce_vsu[i].prisutnost = bafer[i] - '0';
    }
    getline(fajl, bafer);
    for (i=0; i<52; i++) {
        prekljuce_vsu[i].prisutnost = bafer[i] - '0';
    }
    getline(fajl, bafer);
    for (i=0; i<52; i++) {
        juce_vsu[i].prisutnost = bafer[i] - '0';
    }
    getline(fajl, bafer);

    cout << bafer << " " << bafer.size() << endl;

    for (i=0; i < bafer.size(); i++) {
        juce_rez[i].rezultat = bafer[i] - '0';
    }
    for (i=0; i<52; i++) {
        getline(fajl, bafer);
        juce_vsu[i].glasovi = bafer;
    }

    for (i=0; i<64; i++) {
        juce_rez[i].labela = "";
    }
    int br_labela = 0;
    while (getline(fajl, juce_rez[br_labela].labela)) {
        br_labela++;
    }
    system("clear");
    cout << "Ucitavanje je uspesno odradjeno!";
    return 1;

}

string UNOS(string dozvoljene, int br_tacka) {
    int i, j;
    string ulaz;
    bool uspesno = 0;
    cin >> ulaz;
    if (ulaz == "izmeni") {
        return "8";
    }
    else if (ulaz == "izlaz") {
        return "A";
    }
    else {
        if (ulaz.size() != br_tacka) {
            return "9";
        }
        else {
            for (i=0; i<br_tacka; i++) {
                uspesno = 0;
                for (j=0; j<dozvoljene.size(); j++) {
                    if (ulaz[i] == dozvoljene[j]) {
                          uspesno = 1;
                          break;
                    }
                }
                if (!uspesno) {
                    return "9";
                }
            }
        }
    }
    return ulaz; 
}

int REDNI_BROJ(vsu* lista_vsu) {
    int i;
    string lt;
    cout << "\nUneti sifru vsu za koju se menja unos: ";
    cin >> lt;
    for (i=0; i<52; i++) {
        if (lt == lista_vsu[i].lt) {
            return i;
        }
    }
    return 99;
}

bool POCETNA_PRISUTNOST(vsu* lista_vsu) {

    string ulaz;
    int ulaz1, ulaz2;
    int i, j;
    int br_prisutnih = 0;

    cout << "\n--------------------------\n";
    cout << "Unosenje pocetog prisustva";
    cout << "\n--------------------------\n\n";

    for (i=0; i<52; i++) {
        cout << lista_vsu[i].ime << ": ";
        ulaz = UNOS("012", 1);
        ulaz1 = ulaz[0] - '0';
        if (ulaz1 == 8) {
            cout << "\n-----IZMENA GLASA-------\n";
            j = REDNI_BROJ(lista_vsu);
            if (j < i) {
                cout << "Uneti prisustvo: ";
                ulaz = UNOS("012", 1);
                ulaz2 = ulaz[0] - '0';
                if (ulaz2 < 3) {
                    lista_vsu[j].prisutnost = ulaz2;
                    cout << endl;
                }
                else {
                    cout << error2;
                }
            }
            else {
                cout << error2;
            }
            i--;
        }
        else if (ulaz1 == 9) {
            cout << error2;
            i--;
        }
        else if (ulaz1 == 17) {
            cout << "\nIzlazak iz petlje\n";
            return 0;
        }
        else {
            lista_vsu[i].prisutnost = ulaz1;
            if (ulaz1 == 1 || ulaz1 == 2) br_prisutnih ++;
        }
    }
    cout << "\n-------------------------------------------------\n";
    cout << "Broj prisutnih je: " << br_prisutnih;
    cout << "\n-------------------------------------------------\n";
    return 1;
}

void ISPIS_FAJLA(vsu* danas_vsu, vsu* juce_vsu, vsu* prekljuce_vsu, rez* rezultati, string datum) {

    int i,j;
    int ukupan_broj_tacaka = danas_vsu[0].glasovi.size();
    cout << "UKUPAN BROJ TACAKA JE: " << ukupan_broj_tacaka << endl;

    string ime_fajla;
    ime_fajla = "glasovi" + datum + ".txt";

    ofstream fajl;
    fajl.open(ime_fajla);
    fajl << "";
    fajl.close();
    fajl.open(ime_fajla, ios::app);

    for (i=0; i<52; i++) {
        fajl << prekljuce_vsu[i].prisutnost;
    }
    fajl << endl;
    for (i=0; i<52; i++) {
        fajl << juce_vsu[i].prisutnost;
    }
    fajl << endl;
    for (i=0; i<52; i++) {
        fajl << danas_vsu[i].prisutnost;
    }
    fajl << endl;
    for (i=0; i<ukupan_broj_tacaka; i++) {
        fajl << rezultati[i].rezultat;
    }
    fajl << endl;
    for (i=0; i<52; i++) {
        fajl << danas_vsu[i].glasovi << endl;
    }
    cout << "KRAJ ISPISA\n";
}

int KVORUM(vsu* danas_vsu, vsu* juce_vsu, vsu* prekljuce_vsu, bool ucitan_fajl) {

    int kvorum= 0;
    string ulaz;
    bool uspesno = 0;
    float vsu_za_kvorum = 52;
    float kvorum_float;

    if (ucitan_fajl) {
        for (int i=0; i<52; i++) {
            if ((danas_vsu[i].prisutnost == 0) && (juce_vsu[i].prisutnost == 0) && (prekljuce_vsu[i].prisutnost == 0)) {
                vsu_za_kvorum--;
            }
        }
        kvorum = vsu_za_kvorum / 2;
        kvorum_float = vsu_za_kvorum / 2;
        if (kvorum_float > kvorum) kvorum++;
    }
    else {
        cout << "Fajl nije ucitan, uneti kvorum: ";
        while (!uspesno) {
            cin >> ulaz;
            if ((ulaz.size() == 1) && ((ulaz[0] - '0') < 10)) {
                kvorum = ulaz[0] - '0';
                uspesno = 1;
            }
            else if (ulaz.size() == 2) {
                if ((ulaz[0] - '0' > 2) || (ulaz[1] - '0' > 9)) {
                    cout << error1;
                }
                else {
                    kvorum = (ulaz[0] - '0')*10 + (ulaz[1] - '0');
                    if (kvorum > 27) {
                        kvorum = 0;
                        cout << error1;
                    }
                    else {
                        uspesno = 1;
                    }
                }
            }
            else {
                cout << error1;
            }
        }  
    }
    return kvorum;
}

bool NEODRADJENA_PRISUTNOST(vsu* lista_vsu) {

    string ulaz;
    int unos;
    bool izlaz;
    cout << "Pocetna prisutnost nije odradjena\n";
    cout << "Da li zelite da je odradite?\n1(DA), 0(NE): ";
    ulaz = UNOS("01", 1);
    unos = ulaz[0] - '0';
    if (unos == 1) {
        izlaz = POCETNA_PRISUTNOST(lista_vsu);
    }
    else {
        izlaz = 0;
        cout << "\nOpcija se ne moze odraditi pre unosa pocetne prisutnosti\n";
    }
    return izlaz;
}

void IZMENA_PRISUSTVA(vsu* lista_vsu) {
    int i;
    string ulaz;
    bool uspesno = 0;
    while (!uspesno) {
        i = REDNI_BROJ(lista_vsu);
        if (i < 52) {
            cout << "Uneti izmenjeni glas: ";
            ulaz = UNOS("012", 1);
            if (ulaz[0] == '8' || ulaz[0] == '9') {
                cout << error2;
            }
            else if (ulaz[0] == 'A') {
                cout << "\nIzlaz iz petlje\n";
                return;
            }
            else {
                lista_vsu[i].prisutnost = ulaz[0] -'0';
                uspesno = 1;
                cout << "\n-------------------------------------------------\n";
                cout << "Izmena prisustva odradjena uspesno!";
                cout << "\n-------------------------------------------------\n";
            }            
        }
        else {
            cout << error2;
        }
    }
    
}

void OBRADA_GLASOVA(int br_tacaka, int odradjene_tacke, string* glasovi, rez* rezultati, int kvorum) {

    int i,j;
    float za=0;   float protiv=0;   float uzdrzani=0;
    int status;

    for (j=0; j<br_tacaka; j++) {
        for (i=0; i<52; i++) {
            if (glasovi[i][j] == '0') uzdrzani++;
            else if (glasovi[i][j] == '1') za++;
            else if (glasovi[i][j] == '2') protiv++;
        }
        if (za+protiv+uzdrzani >= kvorum) {
            if (za > (2 * protiv)) {
                status = 1;
            }
            else {
                status = 2;
            }
        }
        else {
            status = 3;
        }
        rezultati[j+odradjene_tacke].rezultat = status;
        rezultati[j+odradjene_tacke].za = za;  za = 0;
        rezultati[j+odradjene_tacke].protiv = protiv;  protiv = 0;
        rezultati[j+odradjene_tacke].uzdrzani = uzdrzani;  uzdrzani = 0;
    }

}

void ISPIS_GLASOVA(int br_tacaka, string* glasovi, rez* rezultati, vsu* lista_vsu, int kvorum) {
    int i,j;
    cout << "REZULTATI\n";
    cout << "Kvorum je: " << kvorum << endl << endl;
    //cout << labela;
    for (j=0; j<br_tacaka; j++) {
        if (rezultati[j].labela.empty()) {
            cout << "Tacka broj: " << j+1 << endl;
        }
        else {
            cout << rezultati[j].labela << " (tacka " << j+1 << ") ";
        }
        if (rezultati[j].rezultat == 1) cout << " je izglasana ZA\n";
        else if (rezultati[j].rezultat == 2) cout << " je izglasana PROTIV\n";
        else cout << " se vraca na DOGLASAVANJE\n";
        cout << endl;
        cout << "za: " << rezultati[j].za << "    protiv: " << rezultati[j].protiv << "    uzdrzani: " << rezultati[j].uzdrzani;
        cout << "     neizjasnjeni: " << 52 - rezultati[j].za - rezultati[j].protiv - rezultati[j].uzdrzani << endl << endl;

        cout <<"ZA      |";
        for (i=0; i<52; i++) {
            if (glasovi[i][j] == '1') {
                cout << lista_vsu[i].cy;
                if (lista_vsu[i].prisutnost == 2) cout << "* ";
                else cout << " ";
            }
        }
        cout << endl;

        cout <<"PROTIV  |";
        for (i=0; i<52; i++) {
            if (glasovi[i][j] == '2') {
                cout << lista_vsu[i].cy;
                if (lista_vsu[i].prisutnost == 2) cout << "* ";
                else cout << " ";
            }
        }
        cout << endl;

        cout <<"UZDRZANI|";
        for (i=0; i<52; i++) {
            if (glasovi[i][j] == '0') {
                cout << lista_vsu[i].cy;
                if (lista_vsu[i].prisutnost == 2) cout << "* ";
                else cout << " ";
            }
        }
        cout << endl;
        cout << "\n----------------------------------------------------\n";
    }
/*
    for (i=0; i<52; i++) {
        lista_vsu[i].glasovi += glasovi[i];
    }
        */
    cout << "\n----------------------------------------------------\n";
    cout << "kraj ispisa";
    cout << "\n----------------------------------------------------\n";
}

bool IZMENE_PROSLOG_GLASANJA(vsu* juce_vsu, vsu* danas_vsu, string* glasovi) {

    int broj_glasova = juce_vsu[0].glasovi.size();
    int redni_broj;
    bool gotov_unos = 0;
    bool b = 0;
    string unos;

    while (!gotov_unos) {
        cout << "Da li neko menja glas od prosle sednice?" << endl << "1(DA), 0(NE): ";
        unos = UNOS("01", 1);
        if (unos[0] == '1') {
            redni_broj = REDNI_BROJ(juce_vsu);
            if (redni_broj > 51) {
                cout << error2;
            }
            else {
                if (danas_vsu[redni_broj].prisutnost == 1) {
                    cout << "Stari glasovi: " << juce_vsu[redni_broj].glasovi << endl;
                    cout << "Uneti promenjene glasove: ";
                    unos = UNOS("0123", broj_glasova);
                    if (unos[0] == 'A') {
                        cout << "\nIzlaz iz petlje\n";
                        return 0;
                    }
                    else if (unos[0] == '8' || unos[0] == '9') {
                        cout << error2;
                    }
                    else {
                        juce_vsu[redni_broj].glasovi = unos;
                        glasovi[redni_broj] = unos;
                        juce_vsu[redni_broj].prisutnost = 1;
                        b = 1;
                    }
                }
                else {
                    cout << "Izabrana vsu nije prisutna danas!" << endl;
                }
            }
        }
        else if (unos[0] == '0') {
            gotov_unos = 1;
        }
        else {
            cout << error2;
        }
    }
    return b;
}

void POTVRDJIVANJE(vsu* juce_vsu, vsu* danas_vsu, rez* rezultati, string juce, vsu* prekljuce_vsu, vsu* nakljuce_vsu, int kvorum) {

    int i, j;
    int br_potvrdjivaca = 0;
    int lista_potvrdjivaca[52];
    int broj_tacaka = juce_vsu[38].glasovi.size();
    string ulaz;
    string glas;
    string glasovi[52];
    bool uspesno = 0;
    bool promena1 = 0;
    bool promena2 = 0;

    for (i=0; i<52; i++) {
        if (juce_vsu[i].prisutnost == 2) {
            lista_potvrdjivaca[br_potvrdjivaca] = i;
            br_potvrdjivaca++;
        }
    }
    if (br_potvrdjivaca == 0) {
        cout << "\nNiko ne mora da potvrdi glas sa prosle sednice!\n\n";
    }
    else {
        promena1 = 1;
        cout << "VSU koje moraju potvrditi glas:";
        for (i=0; i<br_potvrdjivaca; i++) {
            cout << " " << juce_vsu[lista_potvrdjivaca[i]].cy;
        }
        cout << endl << "Pojedinacno potvrdjivanje:" << endl;
        for (i=0; i<br_potvrdjivaca; i++) {
            cout << juce_vsu[lista_potvrdjivaca[i]].cy;
            if (danas_vsu[lista_potvrdjivaca[i]].prisutnost == 1) {
                cout << "\n1(DA), 0(NE): ";
                uspesno = 0;
                while (!uspesno) {
                    ulaz = UNOS("01", 1);
                    if (ulaz[0] == '0') {
                        glas = "";
                        for (j=0; j<broj_tacaka; j++) glas += "3";
                        juce_vsu[lista_potvrdjivaca[i]].glasovi = glas;
                        juce_vsu[lista_potvrdjivaca[i]].prisutnost = 0;
                        uspesno = 1;
                    }
                    else if (ulaz[0] == '1') {
                        juce_vsu[lista_potvrdjivaca[i]].prisutnost = 1;
                        uspesno = 1;
                    }
                    else if (ulaz[0] == 'A') {
                        cout << "\nIzlaz iz petlje\n";
                        return;
                    }
                    else {
                        cout << error2;
                    }
                }
            }
            else {
               cout << "nije prisutan\n\n";
               glas = "";
               for (j=0; j<broj_tacaka; j++) glas += "3";
               juce_vsu[lista_potvrdjivaca[i]].glasovi = glas;
               juce_vsu[lista_potvrdjivaca[i]].prisutnost = 0;
            }
        } 
    }
    for (i=0; i<52; i++) {
            glasovi[i] = juce_vsu[i].glasovi;
    }
    promena2 = IZMENE_PROSLOG_GLASANJA(juce_vsu, danas_vsu, glasovi);

    if (promena1 || promena2) {
        OBRADA_GLASOVA(broj_tacaka, 0, glasovi, rezultati, kvorum);
        ISPIS_GLASOVA(broj_tacaka, glasovi, rezultati, juce_vsu, kvorum);
    }
    else {
        system("clear");
        cout << "\nGlasovi od proslog sastanka ostaju isti\n";
    } 
}

int GLASANJE(vsu* lista_vsu, rez* rezultati, int odradjene_tacke, int kvorum) {
    
    string labela;
    string br_str;
    int br_tacaka;
    string glasovi[52];
    int i, j;
    string ulaz;
    int status;

    //cout << "Uneti labelu: ";
    //cin >> labela;
    cout << "Uneti broj tacaka za glasanje: ";
//-----------------------------UNOS BROJA TACAKA--------------------------------
    bool uspesno = 0;
    while (!uspesno) {
        cin >> br_str;
        if (br_str.size() == 1) {
            if (br_str[0] - '0' > 9) {
                cout << error2;
            }
            else {
                br_tacaka = br_str[0] - '0';
                uspesno = 1;
            }
        }
        else if (br_str.size() == 2) {
            if ((br_str[0]-'0')>9 || (br_str[1]-'0')>9) {
                cout << error2;
            }
            else {
                br_tacaka = 10 * (br_str[0]-'0') + (br_str[1]-'0');
                uspesno = 1;
            }
        }
        else {
            cout << error2;
        }
    }
//-------------------------------UNOS GLASOVA------------------------------------
    cout << "Unos glasova vsu\n";
    cout << "1(ZA), 2(PROTIV), 0(UZDRZANI), 3(NEIZJASNJENI)\n";
    for (i=0; i<52; i++) {
        if (lista_vsu[i].prisutnost == 0) {
            ulaz = "";
            for (j=0; j<br_tacaka; j++) {
                ulaz += "3";
                glasovi[i] = ulaz;
            }
        }
        else {
            cout << lista_vsu[i].ime << ": ";
            ulaz = UNOS("0123", br_tacaka);
            if (ulaz[0] == '8') {
                cout << "\n-------IZMENA GLASOVA-------\n";
                j = REDNI_BROJ(lista_vsu);
                if (j < i) {
                    cout << "Uneti glasove: ";
                    ulaz = UNOS("0123", br_tacaka);
                    if (ulaz[0] == '8' || ulaz[0] == '9') {
                        cout << error2;
                    }
                    else if (ulaz[0] == 'A') {
                        cout << "\nIzlaz iz petlje\n";
                        return 0;
                    }
                    else {
                        glasovi[j] = ulaz;
                    }
                }
                else {
                    cout << error2;
                }
                i--;
            }
            else if (ulaz[0] == '9') {
                cout << error2;
                i--;
            }
            else if (ulaz[0] == 'A') {
                cout << "\nIzlaz iz petlje\n";
                return 0;
            }
            else {
                glasovi[i] = ulaz;
            }
        }
    }
    for (i=0; i<52; i++) {
        lista_vsu[i].glasovi += glasovi[i];
    }
//-------------------------------OBRADA I ISPIS-------------------------------------
    OBRADA_GLASOVA(br_tacaka, odradjene_tacke, glasovi, rezultati, kvorum);
    ISPIS_GLASOVA(br_tacaka, glasovi, rezultati, lista_vsu, kvorum);
    return br_tacaka;
}

void DOGLASAVANJE(vsu* danas_vsu, vsu* juce_vsu, vsu* doglasavanje_vsu, rez* rezultati_danas, rez* rezultati_juce, rez* rezultati_doglasavanje, int kvorum) {

    int i, j;
    int br_tacaka_juce = juce_vsu[38].glasovi.size();
    int indeks;
    bool uspesno;
    bool gotovo;
    string unos;

    for (i=0; i<52; i++) {
        doglasavanje_vsu[i].glasovi = "";
    }

    for (j=0; j<br_tacaka_juce; j++) {
        if (rezultati_juce[j].rezultat == 3) {
            for (i=0; i<52; i++) {
                doglasavanje_vsu[i].glasovi += juce_vsu[i].glasovi[j];
            }
        }
    }

    int br_doglasavanja = doglasavanje_vsu[38].glasovi.size();
    cout << endl << br_doglasavanja << endl;
    if (br_doglasavanja == 0) {
        cout << "\nSvi predlozi od prosle sednice su izglasani\n";
        return;
    }
    for (j=0; j<br_doglasavanja; j++) {
        cout << "VSU koje nisu donele glas za ovu tacku su:\n";
        for (i=0; i<52; i++) {
            if (doglasavanje_vsu[i].glasovi[j] == '3') {
                cout << " " << doglasavanje_vsu[i].cy;
            }
        }
        cout << endl;
        gotovo = 0;
        while (!gotovo) {
            indeks = REDNI_BROJ(doglasavanje_vsu);
            if (indeks > 51) {
                cout << error2;
            } 
            else {
                if (doglasavanje_vsu[indeks].glasovi[j] == '3') {
                    cout << "Uneti novi glas: ";
                    unos = UNOS("0123", 1);
                    if (unos[0] - '0' > 3) {
                        cout << error1;
                    }
                    else {
                        doglasavanje_vsu[indeks].glasovi[j] = unos[0];
                    }
                }
                else {
                    cout << "\nUneta vsu je vec donela glas za ovu tacku\n\n";
                }
            }
            cout << "Da li je jos neko doneo glas za ovu tacku?\n1(DA), 0(NE):  ";
            uspesno = 0;
            while (!uspesno) {
                unos = UNOS("01", 1);
                if (unos[0] - '0' > 1) {
                    cout << error1;
                }
                else {
                    uspesno = 1;
                    if (unos[0] == '0') gotovo = 1;
                    else gotovo = 0;
                }
            }  
        }
    }

    string glasovi[52];

    for (i=0; i<52; i++) {
        glasovi[i] = doglasavanje_vsu[i].glasovi;
    }
    int broj1 = danas_vsu[38].glasovi.size();
    for (i=0; i<52; i++) {
        danas_vsu[i].glasovi += doglasavanje_vsu[i].glasovi;
    }
    for (i=0; i<br_doglasavanja; i++) {
        rezultati_danas[i+broj1].protiv = rezultati_doglasavanje[i].protiv;
        rezultati_danas[i+broj1].za = rezultati_doglasavanje[i].za;
        rezultati_danas[i+broj1].uzdrzani = rezultati_doglasavanje[i].uzdrzani;
        rezultati_danas[i+broj1].rezultat = rezultati_doglasavanje[i].rezultat;
    }
    OBRADA_GLASOVA(br_doglasavanja, 0, glasovi, rezultati_doglasavanje, kvorum);
    ISPIS_GLASOVA(br_doglasavanja, glasovi, rezultati_doglasavanje, doglasavanje_vsu, kvorum);
}

void SMINKA(vsu* lista_vsu, rez* rezultati, int kvorum, string datum, bool prvi_ispis) {

    int i, j;
    int broj = lista_vsu[38].glasovi.size();
    ofstream fajl;

    string ime_fajla = "rezultati_glasanja" + datum + ".txt";
    if (prvi_ispis) {
        fajl.open(ime_fajla);
        fajl << "REZULTATI GLASANJA " << datum << ":\n\n\n";
        fajl.close();
        fajl.open(ime_fajla, ios::app);
        fajl << "\n---------------------------------------------------------------------\n";
        fajl << "PRISUTNI     |";
        for (i=0; i<52; i++) {
            if (lista_vsu[i].prisutnost == 1) {
                fajl << " " << lista_vsu[i].cy;
            }
            else if (lista_vsu[i].prisutnost == 2) {
                fajl << " " << lista_vsu[i].cy << "*";
            }
        }
        fajl << endl << "NISU PRISUTNI|";
        for (i=0; i<52; i++) {
            if (lista_vsu[i].prisutnost == 0) {
                fajl << " " << lista_vsu[i].cy;
            }
        }
        fajl << "\n---------------------------------------------------------------------\n";
        fajl.close();
    }
    fajl.open(ime_fajla, ios::app);
    if (!prvi_ispis) {
        fajl << "\n\nREZULTATI DOGLASAVANJA:\n(vsu sa * moraju potvrditi svoj glas na sledecoj sednici)\n\n\n";
    }

    for (j=0; j<broj; j++) {
        if (rezultati[j].labela.empty()) {
            fajl << "Tacka broj: " << j+1;
        }
        else {
            fajl << rezultati[j].labela << " (tacka " << j+1 << ") ";
        }
        if (rezultati[j].rezultat == 1) fajl << " je izglasana ZA\n";
        else if (rezultati[j].rezultat == 2) fajl << " je izglasana PROTIV\n";
        else fajl << " se vraca na DOGLASAVANJE\n";
        fajl << endl << endl;
        fajl << "  za: " << rezultati[j].za << "    protiv: " << rezultati[j].protiv << "    uzdrzani: " << rezultati[j].uzdrzani;
        fajl << "     neizjasnjeni: " << 52 - rezultati[j].za - rezultati[j].protiv - rezultati[j].uzdrzani << endl << endl;
    
        fajl <<"ZA      |";
        for (i=0; i<52; i++) {
            if (lista_vsu[i].glasovi[j] == '1') {
                fajl << lista_vsu[i].cy;
                if (lista_vsu[i].prisutnost == 2) fajl << "* ";
                else fajl << " ";
            }
        }
        fajl << endl;

        fajl <<"PROTIV  |";
        for (i=0; i<52; i++) {
            if (lista_vsu[i].glasovi[j] == '2') {
                fajl << lista_vsu[i].cy;
                if (lista_vsu[i].prisutnost == 2) fajl << "* ";
                else fajl << " ";
            }
        }
        fajl << endl;

        fajl <<"UZDRZANI|";
        for (i=0; i<52; i++) {
            if (lista_vsu[i].glasovi[j] == '0') {
                fajl << lista_vsu[i].cy;
                if (lista_vsu[i].prisutnost == 2) fajl << "* ";
                else fajl << " ";
            }
        }
        fajl << "\n\n---------------------------------------------------------------------\n\n";
    }
}

int main() {

    bool postoji_fajl_liste_vsu = 0;
    bool ucitan_jucerasnji_fajl = 0;
    bool uspesno = 0;
    bool odradjena_prisutnost = 0;

    vsu danas_vsu[52];
    vsu juce_vsu[52];
    vsu prekljuce_vsu[52];
    vsu nakljuce_vsu[52];
    vsu doglasavanje_vsu[52];
    rez danas_rez[64];
    rez juce_rez[64];
    rez doglasavanje_rez[64];

    int unos;
    int i;
    int kvorum_danas = 0;
    int kvorum_juce = 0;
    int odradjene_tacke = 0;

    string datum = DATUM();
    string juce = "";
    string ulaz;

    for (i=0; i<52; i++) {
        danas_vsu[i].glasovi = "";
        juce_vsu[i].glasovi = "";
        doglasavanje_vsu[i].glasovi = "";
    }

    LABELE(danas_rez, datum);
    UNOS_LISTE_VSU(doglasavanje_vsu);
    UNOS_LISTE_VSU(danas_vsu);
    UNOS_LISTE_VSU(juce_vsu);
    UNOS_LISTE_VSU(prekljuce_vsu);
    postoji_fajl_liste_vsu = UNOS_LISTE_VSU(nakljuce_vsu);
    if (postoji_fajl_liste_vsu) {
        unos = 10;
    }
    else {
        unos = 0;
    }
    cout << "------------------------------------------------------------------------\n";
    cout << "glasacka_kutija by djo-sta";
    cout << "\n------------------------------------------------------------------------\n";
    while (unos != 0) {
        this_thread::sleep_for(chrono::milliseconds(100));
        cout << "\n\nPOCETNI MENI\n\n";
        this_thread::sleep_for(chrono::milliseconds(100));
        cout << "Ucitavanje proslog glasanja: 1\n";
        this_thread::sleep_for(chrono::milliseconds(100));
        cout << "Prisutnost:                  2\n";
        this_thread::sleep_for(chrono::milliseconds(100));
        cout << "Izmena prisutnosti:          3\n";
        this_thread::sleep_for(chrono::milliseconds(100));
        cout << "Potvrda/izmena glasova:      4\n";
        this_thread::sleep_for(chrono::milliseconds(100));
        cout << "Glasanje:                    5\n";
        this_thread::sleep_for(chrono::milliseconds(100));
        cout << "Doglasavanje:                6\n";
        this_thread::sleep_for(chrono::milliseconds(100));
        cout << "Izlaz:                       0\n\n";
        this_thread::sleep_for(chrono::milliseconds(100));
        cout << "izbor opcije: ";
//--------------------------------IZBOR OPCIJE--------------------------------
        uspesno = 0;
        while (!uspesno) {
            ulaz = UNOS("0123456", 1);
            unos = ulaz[0] - '0';
            if (unos > 9) {
                cout << error1;
            }
            else {
                uspesno = 1;
            }
        }
        switch (unos) {
//-----------------------UCITAVANJE JUCERASNJEG FAJLA---------------------------
        case 1:
            if (ucitan_jucerasnji_fajl) {
                cout << "Fajl je vec ucitan\n";
            }
            else {
                cout << "Uneti datum poslednjeg odrzanog VSD u obliku ddmm gde je dd: dan, a mm: mesec" << endl;
                cout << "(primer: 4.Novembar => 0411, 30.Januar => 3001):  ";
                cin >> juce;
                ucitan_jucerasnji_fajl = UCITAVANJE_PROSLIH_GLASANJA(juce_vsu, prekljuce_vsu, nakljuce_vsu, juce_rez, juce);
            }
            break;
//---------------------------INICIJALNO PRISUSTVO-------------------------------
        case 2:
            if (odradjena_prisutnost) {
                cout << "Pocetna prisutnost je vec odradjena\n";
            }
            else {
                odradjena_prisutnost = POCETNA_PRISUTNOST(danas_vsu);      
            }
            cout << endl;
            for (i=0;i<52;i++) cout << danas_vsu[i].prisutnost;
            cout << endl;
            break;
//-----------------------------IZMENA PRISUSTVA---------------------------------
        case 3:
            if (odradjena_prisutnost) {
                IZMENA_PRISUSTVA(danas_vsu);
            }
            else {
                odradjena_prisutnost = NEODRADJENA_PRISUTNOST(danas_vsu);
            }
            cout << endl;
            for (i=0;i<52;i++) cout << danas_vsu[i].prisutnost;
            cout << endl;
            break;             
//---------------------------POTVRDJIVANJE GLASOVA------------------------------
        case 4:
            if (ucitan_jucerasnji_fajl) {
                if (odradjena_prisutnost) {
                    if (kvorum_juce == 0) {
                        kvorum_juce = KVORUM(juce_vsu, prekljuce_vsu, nakljuce_vsu, ucitan_jucerasnji_fajl);
                    }
                    POTVRDJIVANJE(juce_vsu, danas_vsu, juce_rez, juce, prekljuce_vsu, nakljuce_vsu, kvorum_juce);
                    ISPIS_FAJLA(juce_vsu, prekljuce_vsu, nakljuce_vsu, juce_rez, juce);
                    SMINKA(juce_vsu, juce_rez, kvorum_juce, juce, 1);
                }
                else {
                    odradjena_prisutnost = NEODRADJENA_PRISUTNOST(danas_vsu);
                }
            }
            else {
                cout << "\nOva opcija nije moguca bez ucitanog odgovarajuceg fajla\n";
            }             
            break;
//--------------------------------GLASANJE--------------------------------------
        case 5:
            if (odradjena_prisutnost) {
                if (kvorum_danas == 0) {
                        kvorum_danas = KVORUM(danas_vsu, juce_vsu, prekljuce_vsu, ucitan_jucerasnji_fajl);
                }
                odradjene_tacke += GLASANJE(danas_vsu, danas_rez, odradjene_tacke, kvorum_danas);
                ISPIS_FAJLA(danas_vsu, juce_vsu, prekljuce_vsu, danas_rez, datum);
                SMINKA(danas_vsu, danas_rez, kvorum_danas, datum, 1); 
            }
            else {
                odradjena_prisutnost = NEODRADJENA_PRISUTNOST(danas_vsu);
            }             
            break;
//-------------------------------DOGLASAVANJE-----------------------------------
        case 6:
            if (ucitan_jucerasnji_fajl) {
                if (odradjena_prisutnost) {
                    if (kvorum_danas == 0) {
                        kvorum_danas = KVORUM(danas_vsu, juce_vsu, prekljuce_vsu, ucitan_jucerasnji_fajl);
                    }
                    DOGLASAVANJE(danas_vsu, juce_vsu, doglasavanje_vsu, danas_rez, juce_rez, doglasavanje_rez, kvorum_danas);
                    ISPIS_FAJLA(danas_vsu, juce_vsu, prekljuce_vsu, danas_rez, datum);
                    SMINKA(doglasavanje_vsu, doglasavanje_rez, kvorum_danas, datum, 0);
                }
                else {
                    odradjena_prisutnost = NEODRADJENA_PRISUTNOST(danas_vsu);
                }
            }
            else {
                cout << "\nOva opcija nije moguca bez ucitanog odgovarajuceg fajla\n";
            }                  
            break;
//--------------------------------------IZLAZ-----------------------------------
        case 0:  
                cout << "\n-----------------------------------------------------------\n";
                cout << "kraj programa";
                cout << "\n-----------------------------------------------------------\n";
            break;      
        }    
}
return 0;
}
