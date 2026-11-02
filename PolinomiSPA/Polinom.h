#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include "Delioci.h"
using namespace std;

/**
 * Klasa za rad sa polinomima
 * Polja polinoma su:</br>
 *  * n - stepen polinoma</br>
 *  * koeficijenti - niz double vrednosti koji predstavljaju koeficijente clanova, koeficijenti[0] pripada clanu x^0, koeficijenti[n] pripada clanu x^n</br>
 *  * nule - Array lista Double vrednosti, na inicijalizaciji je prazna, popunjava se funkcijom pronadjiNule i sadrzi Nule jednog objekta Polinom</br>
 *  * provereneNule - bool vrednost, pomocno polje, sluzi da se izbegne ponovno pretrazivanje nula ili slicno</br>
 *  </br>
 * Metode za rad sa polinomima su:</br>
 *  *saberi - staticka, sabira dva polinoma</br>
 *  *oduzmi - staticka, sabira jedan polinom sa drugim polinomom, gde je drugi pomnozen sa -1</br>
 *  *pomnozi - mnozi dva polinoma ili polinom sa konstantom</br>
 *  *hornerovaSema - deli polinom pomocu hornerove seme</br>
 *  *pronadjiNule - pronalazi sve realne nule polinoma</br>
 *  *ispraviStepen - ispravlja stepen lose formatiranog polinoma</br>
 */
class Polinom
{
private:
	int n;//Stepen
	vector<int> koeficijenti; //koef[0] = x^0, koef[n] = x^n
	vector<double> nule;
	bool provereneNule;

	/**
	 * Metod koji ispravlja stepen polinoma na poslednju vrednost koja nije nula
	 * Ukoliko je polinom stepena 6 a koeficijenti su mu 1,2,0,0,0,0,0
	 * Nule ce se izignorisati a polinom ce postati stepena 1 kao sto i jeste 1,2
	 * @author Luka Petroviæ
	 *
	 */
	void ispraviStepen() {
		for (int i = n; i >= 0; i--) {
			if (!(koeficijenti.at(i) == 0)) {
				n = i;
				return;
			}
		}
	}
public:
	Polinom() :n(0), koeficijenti(n + 1), provereneNule(false), nule() {}

	/**
	 * Inicijalizuje Polinom stepena n tako da mu svi koeficijenti budu 0
	 * @param n stepen polinoma
	 * @exception RuntimeException baca exception kada je stepen manji od 0
	 * @author Luka Petroviæ
	 *
	 */
	Polinom(int stepen):n(stepen),koeficijenti(stepen+1), provereneNule(false), nule(){
		if (n < 0)
		{
			throw exception("Stepen polinoma ne sme biti manji od 0");
		}
	}
	/**
	 * Inicijalizuje Polinom pomocu niza koeficijenata, stepen se postavlja na broj elemenata tog niza, a zatim smanjuje ako je format bio los
	 * @param koef niz koeficijenata
	 * @exception RuntimeException baca exception ukoliko je poslat prazan niz koeficijenata
	 * @author Luka Petroviæ
	 *
	 */
	Polinom(vector<int> koef):n(koef.size()-1),koeficijenti(n+1), provereneNule(false), nule(){
		if (n < 0)
		{
			throw exception("Niz koeficijenata ne sme biti prazan ukoliko je to jedini izvor podataka za kreaciju polinoma");
		}
		for (int i = 0; i <= n; i++) {
			this->koeficijenti.at(i) = koef.at(i);
		}
		ispraviStepen();

		
	}
	/**
	 * Inicijalizuje polinom i pomocu stepena n i pomocu niza koeficijenata</br>
	 * Broj elemenata u nizu koeficijenata nije bitan dokle god je stepen n veci ili jednak 0
	 * </br>
	 * Ukoliko je stepen manji od broja elemenata, visak se ignorise
	 * @param n stepen
	 * @param koef niz koeficijenata
	 * @exception RuntimeException baca exception kada je stepen manji od 0
	 * @author Luka Petroviæ
	 *
	 */
	Polinom(int stepen, vector<int> koef) :n(stepen), koeficijenti(stepen + 1), provereneNule(false), nule(){
		if (n < 0)
		{
			throw exception("Stepen polinoma ne sme biti manji od 0");

		}
		for (int i = 0; i <= n; i++) {
			if (i < koef.size()) {
				this->koeficijenti.at(i) = koef.at(i);
			}
			else {
				this->koeficijenti.at(i) = 0;
			}
		}
		ispraviStepen();
	}
	/**
	 * Operator+ za sabiranje dva polinoma, odredjuje veci stepen na osnovu dva parametra,
	 * i kreira niz koeficijenata duzine tog veceg stepena,
	 * zatim se na indekse sabiraju vrednosti koeficijenata parametara kroz dve odvojene for petlje
	 *
	 * @param levi sabirak
	 * @param desni sabirak
	 * @return novi objekat polinoma sastavljen od novog stepena i novih koeficijenata
	 * @author Luka Petroviæ
	 *
	 */
	friend Polinom operator+(const Polinom& levi, const Polinom& desni) {
		int zbirN = max(levi.n, desni.n);
		vector<int> koef = vector<int>(zbirN + 1);
		for (int i = 0; i <= levi.n; i++) {
			koef.at(i) += levi.koeficijenti.at(i);
		}
		for (int i = 0; i <= desni.n; i++) {
			koef.at(i) += desni.koeficijenti.at(i);
		}

		return Polinom(zbirN, koef);
	}
	/**
	 * Operator* za mnozenje dva polinoma,
	 * odredjuje novi stepen koji je jednak zbiru stepena levog i desnog parametra i rezervise dovoljno mesta u nizu</br>
	 * Vrsi se mnozenje svaki sa svakim elementom, gde su i,j njihovi indeksi, taj proizvod se zatim dodaje na i+j mesto u rezervisanom nizu
	 * @param levi cinilac
	 * @param desni cinilac
	 * @return proizvod
	 * @author Luka Petroviæ
	 *
	 */
	friend Polinom operator*(const Polinom& levi, const Polinom& desni) {
		int proizvodN = levi.n + desni.n;
		vector<int> koef = vector<int>(proizvodN + 1);
		for (int i = 0; i <= levi.n; i++) {
			for (int j = 0; j <= desni.n; j++) {
				koef.at(i+j) += levi.koeficijenti.at(i) * desni.koeficijenti.at(j);
			}
		}
		return Polinom(proizvodN, koef);
	}

	/**
	 * Operator* za mnozenje polinoma konstantom, overloadovana verzija pomnozi metoda,
	 * mnozi svaki element niza koeficijenata konstantom iz parametra
	 * @param levi polinom
	 * @param konstanta uneta konstanta
	 * @return rezultat
	 * @author Luka Petroviæ
	 *
	 */
	friend Polinom operator*(const Polinom& levi, const int konstanta) {
		Polinom rezultat = Polinom(levi.n, levi.koeficijenti);
		for (int i = 0; i <= levi.n; i++) {
			rezultat.koeficijenti[i] *= konstanta;
		}
		return rezultat;
	}
	/**
	 * Operator- za oduzimanje implementira dve funkcije,
	 * funkciju pomnozi koja desni parametar mnozi konstantom -1, a zatim sabira tako izmenjen polinom sa levim parametrom
	 * @param levi umanjenik
	 * @param desni umanjilac
	 * @return razlika
	 * @author Luka Petroviæ
	 *
	 */
	friend Polinom operator-(const Polinom& levi, const Polinom& desni) {
		return levi + (desni * (-1));
	}

	/**
	 *Staticki metod koji deli polinom pomocu hornerove seme,
	 * najpre se kreiraju dva Polinoma, kolicnik, stepena n-1 i ostatak, stepena 0, gde je n stepen polinoma koji delimo.</br>
	 * Hornerova sema nalaze da koeficijent uz clan najviseg stepena pocetnog polinoma prepisemo u koeficijent najviseg stepena polinoma kolicnik</br>
	 * Dalje iterativno idemo unazad kroz kolicnik od najviseg stepena do stepena 1.
	 * U niz koeficijenata polinoma kolicnik na i-1 mesto postavljamo proizvod parametra potencijalneNula i kolicnik.koeficijenti[i]
	 * i uz to saberemo vrednost i-tog koeficijenta polinoma koji delimo.
	 *
	 * @param polinom polinom koji zelimo da podelimo
	 * @param potencijalnaNula double konstanta iz bezuovog stava (x-a), potencijalna nula je a
	 * @return Polinom[2], gde je prvi element kolicnik, a drugi ostatak pri deljenju
	 * @author Luka Petroviæ
	 *
	 */
	static vector<Polinom*> hornerovaSema(const Polinom& polinom, const double potencijalnaNula) {
		Polinom* kolicnik = new  Polinom(polinom.n - 1);
		Polinom* ostatak = new Polinom(0);
		kolicnik->koeficijenti.at(kolicnik->n) = polinom.koeficijenti.at(polinom.n);
		for (int i = kolicnik->n; i >= 1; i--) {
			kolicnik->koeficijenti.at(i-1) = kolicnik->koeficijenti.at(i) * potencijalnaNula + polinom.koeficijenti.at(i);
		}
		ostatak->koeficijenti.at(0) = kolicnik->koeficijenti.at(0) * potencijalnaNula + polinom.koeficijenti.at(0);

		vector<Polinom*> rezultat =  vector<Polinom*>(2);
		rezultat.at(0) = kolicnik;
		rezultat.at(1) = ostatak;
		return rezultat;

	}

	/**
	 * Metod koji za objekat Polinoma pronalazi realne nule</br></br>
	 *
	 * Za pocetak ukoliko su nule vec proverene, proces se ne ponavlja jer je "skup"</br>
	 * Promenljiva polinom inicijalizovana je vrednoscu objekta, takodje uvodimo pocetnu promenljivu zavrsenaProvera</br>
	 *
	 * Algoritam se ponavlja sve dok se ne provere sve moguce potencijalne nule. </br>
	 * Realne potencijalne nule se mogu predstaviti pomocu razlomka p/q, </br>
	 * gde je p delilac koeficijenta uz slobodni clan, a q delilac koeficijenta uz najvisi stepen,</br>
	 * a sve takve delioce cuvamo u TreeSet strukturama, koje cuvaju samo unique sortirane vrednosti</br>
	 * </br>
	 * Zatim sledi ugnjezdena petlja koja ispituje sve moguce kombinacije elemenata iz deliociSlobodanClan i deliociNajvisiStepen kroz hornerovu semu.</br>
	 * Ukoliko neka provera vrati rezultat u kojoj je ostatak 0, znaci da smo pronasli nulu, nula se dodaje u atribut objekta,</br>
	 * a na polinom se stavlja nova vrednost, odnosno kolicnik</br>
	 * Algoritam se ponavlja, ponovo se traze delioci za novi polinom, pa opet svi idu kroz hornerovu semu itd..</br></br>
	 * Kada se prodje kroz sve potencijalne nule, a nula se ne pronadje ili kada polinom koji delimo bude stepena 0, funkcija se prekida
	 *
	 *
	 * </br></br></br>
	 * Trenutni propust je da se nule mogu pronaci samo za celobrojne koeficijente
	 * U suprtnom pisace da polinom nema realne nule
	 *
	 * @author Luka Petroviæ
	 */
	void pronadjiNule() {
		if (this->provereneNule || this->n == 0) {
			this->provereneNule = true;
			return;
		}
		else {
			this->provereneNule = true;
		}
		Polinom* polinom = this;
		bool zavrsenaProvera = false;

		while (!zavrsenaProvera) {
			bool pronadjenaNula = false;
			set<int> deliociSlobodanClan = Delioci::deliociBroja(polinom->koeficijenti[0]);
			set<int> deliociNajvisiStepen = Delioci::deliociBroja(polinom->koeficijenti[polinom->n]);
			for (int p : deliociSlobodanClan) {
				if (zavrsenaProvera || pronadjenaNula) {
					break;
				}

				for (int q : deliociNajvisiStepen) {
					vector<Polinom*> rezultat = Polinom::hornerovaSema(*polinom,(double) p / q);
					if (rezultat.at(1)->koeficijenti.at(0) == 0) {
						this->nule.push_back((double)p / q);
						pronadjenaNula = true;
						polinom = rezultat.at(0);
						if (polinom->n == 0) {
							zavrsenaProvera = true;

						}
						break;
					}
				}

			}
			if (!pronadjenaNula) {
				zavrsenaProvera = true;

			}
		}

	}
	
	/**
	 *
	 * Vraca opis polinoma u dva reda u formatu:</br>
	 *      * P(n): .2fx^n + .2fx^n-1 + ...+ .2fx^1 + .2f</br>
	 *      * Nule: nula1, nula2, nula3, ...</br>
	 *       gde je n stepen polinoma, .2f koeficijent clana
	 *       Nula moze i ne mora biti
	 *      </br
	 *      *Ukoliko je koeficijent 0 taj clan se ne ispisuje, osim ako je polinom stepena 0
	 * @return opis polinoma
	 * @author Luka Petroviæ
	 *
	 */
	string to_string() const{
		
		string opis = "P(" + std::to_string(n) + "):";
		for (int i = n;i > 0;i--) {
			if (koeficijenti[i] == 0) continue;
			if (koeficijenti[i] != 1) {
				opis += std::to_string(abs(koeficijenti[i]));
			}
			opis += "x";
			
			if (i > 1) {
				opis+= "^" + std::to_string(i);
				if (koeficijenti.at(i-1)>=0){
					opis += " + ";
				}
				else {
					opis += " - ";

				}
			}
		}
		if (koeficijenti.size() > 1 && koeficijenti.at(0) != 0) {
			if (koeficijenti.at(0) >= 0) {
				opis += " + ";
			}
			else {
				opis += " - ";

			}
			opis += std::to_string(abs(koeficijenti.at(0)));
		}
		else if (koeficijenti.size() == 1) {
			if (koeficijenti.at(0) < 0) {
				opis += " - ";
			}
			opis += std::to_string(koeficijenti.at(0));
		}

		if (!this->provereneNule) {
			opis += "\nNule nisu ispitane, iskoristite funkciju pronadjiNule()\n\n";
		}
		else if (n == 0 && koeficijenti.at(0) == 0) {
			opis += "\nOvaj polinom ima beskonacno mnogo nula\n\n";
		}
		else if (nule.empty()) {
			opis += "\nOvaj polinom nema realne nule\n\n";
		}
		else {
			opis += "\nNule polinoma: ";
			
			for (int i = 0; i < nule.size(); i++)
			{
				opis += std::to_string(nule.at(i));
				if (i<nule.size()-1) {
					opis += ", ";
				}
				else {
					opis += "\n";
				}
			}
		}
		return opis;
	}
	friend ostream& operator<<(ostream& os,const Polinom& zaOpis) {
		os << zaOpis.to_string();
		return os;
	}

};

