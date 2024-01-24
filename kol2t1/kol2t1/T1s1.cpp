#include <exception>
#include <iostream>
#include <cstring>
#include <cassert>
using namespace std;

enum class Dostepnosc {
	nieDostepny = 0,
	spodziewanaDostawa = 1,
	dostepny = 2,
};

struct Producent {
	char nazwa[500];
};

struct Towar
{
	char nazwa[1000];
	double cena;
	Dostepnosc dostepnosc;
	Producent* producent;
};

ostream& operator<<(ostream& co, Producent const& val) {
	co << val.nazwa;
	return co;
}

ostream& operator<<(ostream& co, Dostepnosc const& val) {
	constexpr size_t enum_size = 3;
	constexpr char dostepnosc[enum_size][20] = { "nieDostepny", "spodziewanaDostawa", "dostepny" };

	co << "dostepnosc:" << dostepnosc[(int)val] <<",";
	return co;
}

ostream& operator<<(ostream& co, Towar const& val) {
	co << "nazwa:" << val.nazwa<<",";
	co << " cena:" << val.cena << ", ";
	co << val.dostepnosc << endl;
	co << " producent:" << '"' << * val.producent << '"' << endl;

	return co;
}


int sredniaCena(Towar* dane, size_t towar_size, Producent* producent)
// Funkcja ma wczytać tablicę towarów i producenta
// a następnie zwrocić średnią cenę dostępnych u niego towarów.
{
	assert(producent != nullptr);
	assert(dane != nullptr);
	if (towar_size == 0) throw invalid_argument("rozmiar = 0");
	double suma = 0;
	int wyniki = 0;
	for (int i = 0; i < towar_size; i++){
		if (dane[i].producent == producent) {
			wyniki++;
			suma += dane[i].cena;
		}
	}
	if (wyniki == 0) throw domain_error("nie znaleziono instancji");


	return suma/wyniki;
}


Towar dodajTowar(const char* nazwa, double cena, Dostepnosc dostepnosc, Producent* producent){

	Towar nowyTowar{};
	strcpy_s(nowyTowar.nazwa, nazwa);
	nowyTowar.cena = cena;
	nowyTowar.dostepnosc = dostepnosc;
	nowyTowar.producent = producent;

	return nowyTowar;
}


void test1wynik() {
	cout << "Test wyniku";

	Producent producenci[] = {
		{"Sprytny Rybak"},
		{"Niesprytny Wedkarz"},
	};

	Towar towary[] = {
		{"Sledze",10.0,Dostepnosc::dostepny,&producenci[0]},
		{"Wegiel",200.0,Dostepnosc::dostepny,&producenci[1]},
		{"Morswin",50.0,Dostepnosc::dostepny,&producenci[0]},
		{"Korzen",200.0,Dostepnosc::dostepny,&producenci[1]},
	};
	try {
		double wynik = sredniaCena(towary, sizeof(towary) / sizeof(Towar), &producenci[1]);
		double oczekiwany_wynik = 200.0;

		if(wynik != oczekiwany_wynik) throw wynik;
		else {
			cout << " :OK!" << endl;
		}
	}
	catch (double w) {
		cout << " :BLAD!" << endl;
	}
	

}

void test2brak() {
	cout << "test braku instancji";

	Producent producenci[] = {
		{"Sprytny Rybak"},
		{"Niesprytny Wedkarz"},
	};

	Towar towary[] =
	{
		{"Sledze",100.0,Dostepnosc::dostepny,&producenci[0]},
		{"Morswiny",50.0,Dostepnosc::dostepny,&producenci[0]},
	};

	try {
		sredniaCena(towary, sizeof(towary)/sizeof(Towar), &producenci[1]);
		cout << " :OK!" << endl;
	}

	catch (domain_error) {
		cout << " :BLAD!" << endl;
	}

}


int main()
{
	Producent producenci[] = {
		{"Sprytny Rybak"},
		{"KWK Świderek"},
		{"Agencja T. Chryzantema"}
	};

	Towar towary[] =
	{
		{"Sledze",10.99,Dostepnosc::dostepny,&producenci[0]},
		{"Węgiel",1000.0,Dostepnosc::nieDostepny,&producenci[1]},
		{"Masaz",501.29,Dostepnosc::dostepny,&producenci[2]},
		// dodaj jeszcze prznajmniej 4 instancje
		dodajTowar("Rolki", 200, Dostepnosc::dostepny, &producenci[2]),
		dodajTowar("Wrotki", 189.99, Dostepnosc::spodziewanaDostawa, &producenci[2]),
		dodajTowar("Paraletki", 120, Dostepnosc::nieDostepny, &producenci[1]),
		dodajTowar("Kosa", 70.12, Dostepnosc::nieDostepny, &producenci[2]),
	};
	test1wynik();
	test2brak();
	cout << endl;
	for (int i = 0; i < 6; i++) {
		cout << towary[i] << endl;
	}


}