/**
 *	Oblig 1 - Objektorientert programmering
 */

#include <iostream>   //cout og cin
#include <vector>     //vector
#include <string>     //string
#include "LesData2.h" //Inkluderer lesdata fil
using namespace std;

const int ANTSTOPP = 11; ///<Totalt antall ulike busstopp

struct Rute
{
    vector<string> stopp; //Rutens ulike stoppesteder.
    int ruteNr,           //Reelt ruteNr,
        totMin;           //Totalt antall minutter å kjøre på ruten
};                        // (Fra første til siste stopsted)

vector<Rute *> gRuter;

const vector<string> gBusstopp = ///< Navn på alle busstopp.
    {"Skysstasjonen", "Fahlstroms plass", "Sykehuset",
     "Gjovik stadion", "Bergslia", "Overby", "Nybrua",
     "NTNU", "Kallerud", "Hunndalen", "Mustad fabrikker"};

const int gMinutter[ANTSTOPP][ANTSTOPP] = ///< Min.mellom stoppesteder
    {{0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0},   // Skysstasjonen = 0
     {3, 0, 3, 0, 0, 0, 3, 0, 0, 0, 4},   // Fahlstrøms plass = 1
     {0, 3, 0, 1, 0, 0, 0, 0, 0, 0, 0},   // Sykehuset = 2
     {0, 0, 1, 0, 3, 0, 0, 0, 0, 0, 0},   // Gjøvik stadion = 3
     {0, 0, 0, 3, 0, 2, 0, 0, 0, 0, 0},   // Bergslia = 4
     {0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0},   // Øverby = 5
     {0, 3, 0, 0, 0, 0, 0, 2, 0, 0, 2},   // Nybrua = 6
     {0, 0, 0, 0, 0, 0, 2, 0, 0, 4, 0},   // NTNU = 7
     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},   // Kallerud = 8
     {0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 2},   // Hunndalen = 9
     {0, 4, 0, 0, 0, 0, 2, 0, 0, 2, 0}};  // Mustad fabrikker = 10

/**
 *	Alle funksjoner
 */
void skrivMeny();
void skrivStopp();
void skrivRuter();
void ruteSkrivData(const Rute rute);
void skrivNesteStoppesteder(const int stopp);
void nyRute();
bool ruteLesData(Rute &rute);
void slettRuter();
void slett();
void slett(const int nr);

/**
 *	Hoved programmet
 */
int main()
{

    char kommando; // Kontroll variabel

    skrivMeny();                   //Skriver meny
    kommando = lesChar("\nOnske"); //Spør hvilken kommando

    while (kommando != 'Q')
    { //Runner så lenge ikke 'Q'
        switch (kommando)
        { //Alle muligheter vises under
        case 'N':   nyRute();       break;
        case 'S':   slettRuter();   break;
        case 'A':   skrivRuter();   break;
        case 'B':   skrivStopp();   break;
        default:    skrivMeny();
        }
        skrivMeny();
        kommando = lesChar("\nOnske");
    }
    return 0;
}
/**
 *	Funksjon som skriver meny for switchen
 */
void skrivMeny()
{
    cout << "Folgende kommandoer er lovlig!: " << "\n";
    cout << "\tN = Ny Rute" << "\n";
    cout << "\tS = Slett Rute" << "\n";
    cout << "\tA = Skriv Alle Ruter" << "\n";
    cout << "\tB = Skriv alle busstopp" << "\n";
    cout << "\tQ = Avslutt programmet" << "\n";
};

/**
 * Funksjon som skriver ALLE busstopper
 * i Gjøvik
 */
void skrivStopp()
{
    cout << "\tAlle busstopp\n";
    for (int i = 0; i < gBusstopp.size(); i++)
    {                                        // Looper gBusstopp.size()
        cout << "\tBusstopp nr." << i + 1 << // Antall ganger
            " = " << gBusstopp[i] << "\n";   // Skriver ut busstopp
    }
    cout << "\n";
};

/**
 * Funksjon som skriver all buss ruter.
 * vidre sender informasjon til funksjonen
 * ruteSKrivData for å skrive ut rutenes data
 */
void skrivRuter()
{
    for (int i = 0; i < gRuter.size(); i++) { //Looper gRuter.size() antall
        cout << "\tRute indeks: " << i + 1    //Skriver rute indeks
             << "\n";
        ruteSkrivData(*gRuter[i]); //Vidresender til neste funksjon
    }
};

/**
 *	Skriver ut all data for hver eneste-
 *	Bussrute
 *	 - RuteNummer
 *	 - Busstopp
 *	 - Total Reise tid i minutter
 */
void ruteSkrivData(const Rute rute)
{
    cout << "\tRutenummer: " << rute.ruteNr << "\n";
    cout << "\tBusstopp:  ";
    for (int i = 0; i < rute.stopp.size(); i++)
    {                                 //Looper gjennom
        cout << rute.stopp[i] << " "; //Skriver ut
        if (i < rute.stopp.size() - 1)
        {                    //sørger for at det ikke blir for
            cout << " --> "; //mange piler '-->'
        }
    }
    cout << "\n\tTotal reisetid: " << rute.totMin << //SKriver reisetid
        ".min\n\n";
};

/**
 *	Skriver alle aktuelle stopp for ett busstopp
 */
void skrivNesteStoppesteder(const int stopp)
{
    cout << "\nAlle aktuelle stoppestder: \n";

    for (int i = 0; i < ANTSTOPP; i++)
    {
        if (gMinutter[stopp][i] != 0 && stopp != i)
        {
            cout << "\tStopp nr." << i + 1 << " = " << gBusstopp[i] << "\n";
        }
    }
};

/**
 *	Funksjon som opretter en ny rute, får all dens date innles av 
 *  ruteSkrivData().
 */
void nyRute()
{
    Rute *nyRute = new Rute; //Allokere plass i memory til ny rute

    if (ruteLesData(*nyRute))
    {                             //Hvis returnerer ture
        gRuter.push_back(nyRute); //Pusher bakerst i vector
        ruteSkrivData(*nyRute);   //Skriver all data
        cout << "\tAntall ruter lagt til: " << gRuter.size() << "\n\n";
    }
    //Hvis ruteLesData ikke rturnerer true
    else
    {
        cout << "\tRuten din var for kort! :D\n";
        delete nyRute;
        cout << "\tAntall ruter lagt til: "
             << gRuter.size();             //Sjekker vektor size
        cout << "\tKapasitet i vektor: "   //Sjekker at det ikke ligger igjen
             << gRuter.capacity() << "\n\n"; //random "søppel"
    }
};

/**
 * Funksjon som leser inn all data for nylig opprettet rute
 * Hvis innlesningen gikk bra (antall Busstopp > 1) returnerer true
 * Hvis ikke returnerer false 
 */
bool ruteLesData(Rute & rute)
{
    int x = 0; //Hjelpe variabel (Kolonne x-akse)
    int y = 0; //Hjelpe variabel (Rad y-akse)

    rute.ruteNr = lesInt("Rute Nummer:", 0, 500); //Rutenummer skrives inn

    skrivStopp();                               //Skriver alle stopp
    y = lesInt("Velg start (0 = quit)", 0, 11); //Velger startsted.
	if (y == 0) {						//Hvis bruker skriver 0 med engang
		return false;
	}
	rute.totMin = 0;	//Nullstiller totalt minutter!
    while (y != 0)
    {                                           //Looper så lenge ikke 0
        rute.stopp.push_back(gBusstopp[y - 1]); //Legger inn start bakerst
        rute.totMin += gMinutter[x][y - 1];     //Legger til totmin
        x = (y - 1);                            //går til riktig rad
        skrivNesteStoppesteder(x);              //Skriver mulige neste stopp

        //Looper så lenge gMinutter[x][y] = 0 og y
        do
        {
            y = lesInt("Velg start (0 = quit)", 0, 11); //Velger startsted.
        } while (gMinutter[x][y - 1] == 0 && y != 0);
    }
    //Hvis det er lagt til flere enn en rute return true
    //ellers false. og fjerner plassen i rute.stopp vektor

    if (rute.stopp.size() > 1)
    {
        return true;
    }

    else
    {
        rute.stopp.pop_back();
        return false;
    }
};

/**w
 * Kontroll funksjon for å slette riktig rute(r)
 */
void slettRuter()
{
    int svar; //Svar variabel

    if (gRuter.size() == 0)
    { //Hvis det ikke finnes noen ruter
        cout << "Ingen ruter :( \n";
    }
    else
    { //Ellers skjer dette
        skrivRuter();
        cout << "\tHva vil du slette?\n";
        cout << "\t'0' = ingenting\n";
        cout << "\t'-1' = slett alt\n";
        cout << "\tEllers spesifiser indeks: \n";
        svar = lesInt("Onske: ", -1, 11);

        if (svar == -1)
        {
            slett();
        } //Hvis '-1' slettes alt
        else if (svar == 0)
        { //Hvis '0' Slettes ingen ting
            cout << "\tIngen ting slettes\n";
        }
        else
        {                //Ellers sendes spesifik rute til
            slett(svar-1); //slett hvor den slettes
        }
    }
};

/**
 * Funksjon som itererer gjennom hele gRuter-vektoren
 * Sletter rute og pop_backer. Fortsetter til vektoren er tom
 * Sletter absolutt alt.
 */
void slett()
{
    cout << "\tSletter alle ruter\n";
    while (!gRuter.empty())
    {                                     //Looper så lenge den ikke er tom
        delete gRuter[gRuter.size() - 1]; //Frigjør memory
        gRuter.pop_back();                //Pop_backer bakerst i vektor

        cout << "Antall ruter: " //Hvor mange ruter er igjen
             << gRuter.size() << "\n";
        cout << "Kapasitet i vektor"       //Kapasitet for å sjekke om det
             << gRuter.capacity() << "\n"; //Ligger igjen søppel
    }
};

/**
 * Funksjon som sletter spesifik ønsket rute.
 */
void slett(const int nr)
{ //Looper nr antall ganger
    cout << "\tSletter rute nummer: " << nr << "\n";
    delete gRuter[nr];                  //Frigjør memory
    gRuter[nr] = gRuter[gRuter.size()-1];
	gRuter.pop_back();                  //Fjærner bakerste rute

    cout << "Antall ruter: " //Hvor mange ruter er igjen
         << gRuter.size() << "\n";
    cout << "Kapasitet i vektor"       //Kapasitet for å sjekke om det
         << gRuter.capacity() << "\n"; //Ligger igjen søppel
};
