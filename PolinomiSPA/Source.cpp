#pragma once
#include "Polinom.h"
using namespace std;
int main() {
    cout<<"ISPIS EXCEPTION GRESAKA:\n";
    try {
        Polinom stepenManjiOd0(-1);
    }
    catch (exception e) {
        cout<<e.what()<<"\n";//Stepen polinoma ne sme biti manji od 0
    }
    try {
        Polinom prazanNizKoef(vector<int>{});
    }
    catch (exception e) {
        cout<<e.what() << "\n";//Niz koeficijenata ne sme biti prazan ukoliko je to jedini izvor podataka za kreaciju polinoma
    }
    try {
        Polinom kombinacija(-1, vector<int>{});
    }
    catch (exception e) {
        cout<<e.what() << "\n";//Stepen polinoma ne sme biti manji od 0
    }
    try {
        Polinom kombinacijaSaPraznimKoef(0, vector<int>{});
        cout<<"\nKombinacija konstruktora, stepen 0, prazan niz: \n" << kombinacijaSaPraznimKoef << "\n";
        //Kombinacija konstruktora, stepen 0, prazan niz:
        //P(0):0,00
        //Nule nisu ispitane, iskoristite funkciju pronadjiNule()
    }
    catch (exception e) {
        cout<<e.what() << "\n";
    }



    cout<<"\n\nPRIMERI POLINOMA I OSNOVNIH FUNKCIJA";

    try {
        Polinom primer(3, vector<int>{2, -7, 6, 1});
        cout<<"\nPrimer polinoma:\n" <<primer << "\n";
        //Primer polinoma:
        //P(3):1,00x^3 + 6,00x^2 - 7,00x + 2,00
        //Nule nisu ispitane, iskoristite funkciju pronadjiNule()
    }
    catch (exception e) {
        cout<<e.what() << "\n";
    }
    try {
        Polinom p1(5, vector<int>{1, 2, 1});
        Polinom p2(3, vector<int>{1, 1});
        cout << "\np1: " << p1;
        cout << "\np2: " << p2;
        
        cout<<"\np1+p2=" <<(p1+p2);
        cout<<"\np1-p2=" <<(p1-p2);
        cout<<"\np1*p2=" <<(p1*p2);
        //p1+p2=P(2):1,00x^2 + 3,00x + 2,00
        //Nule nisu ispitane, iskoristite funkciju pronadjiNule()
        //
        //p1-p2=P(2):1,00x^2 + 1,00x
        //Nule nisu ispitane, iskoristite funkciju pronadjiNule()
        //
        //p1*p2=P(3):1,00x^3 + 3,00x^2 + 3,00x + 1,00
        //Nule nisu ispitane, iskoristite funkciju pronadjiNule()
    }
    catch (exception e) {
        cout<<e.what() << "\n";
    }



    cout<<"\n\nPRIMERI HORNEROVA SEMA";
    try {
        Polinom p1(6, vector<int>{-30, -4, 47, 6, -18, -2, 1});
        auto rezulat = Polinom::hornerovaSema(p1, 5);
        cout<<"\nKolicnik pri deljenju p1 i (x-5): \n" << *rezulat.at(0);
        cout<<"Ostatak pri deljenju p1 i (x-5): \n" << *rezulat.at(1);
        //Kolicnik pri deljenju p1 i (x-5):
        //P(5):1,00x^5 + 3,00x^4 - 3,00x^3 - 9,00x^2 + 2,00x + 6,00
        //Nule nisu ispitane, iskoristite funkciju pronadjiNule()
        //Ostatak pri deljenju p1 i (x-5):
        //P(0):0,00
        //Nule nisu ispitane, iskoristite funkciju pronadjiNule()

        rezulat = Polinom::hornerovaSema(p1, -13);
        cout<<"\nKolicnik pri deljenju p1 i (x+13): \n" << *rezulat.at(0);
        cout<<"Ostatak pri deljenju p1 i (x+13): \n" << *rezulat.at(1);
        //Kolicnik pri deljenju p1 i (x+13):
        //P(5):1,00x^5 - 15,00x^4 + 177,00x^3 - 2295,00x^2 + 29882,00x - 388470,00
        //Nule nisu ispitane, iskoristite funkciju pronadjiNule()
        //Ostatak pri deljenju p1 i (x+13):
        //P(0):5050080,00
        //Nule nisu ispitane, iskoristite funkciju pronadjiNule()
    }
    catch (exception e) {
        cout<<e.what() << "\n";
    }
    cout<<"\n\nPRIMERI PRONALAZENJE NULA";
    try {
        Polinom p1(2, vector<int>{1, 2, 1});
        p1.pronadjiNule();
        cout<<p1;
        //P(2):1,00x^2 + 2,00x + 1,00
        //Nule polinoma: -1.0, -1.0,

        Polinom p2(0, vector<int>{1});
        p2.pronadjiNule();
        cout<<p2;
        //P(0):1,00
        //Ovaj polinom nema realne nule

        Polinom p3(0, vector<int>{0});
        p3.pronadjiNule();
        cout<<p3;
        //P(0):0,00
        //Ovaj polinom ima beskonacno mnogo nula

        Polinom p4(6, vector<int>{-30, -4, 47, 6, -18, -2, 1});
        p4.pronadjiNule();
        cout<<p4;
        //P(6):1,00x^6 - 2,00x^5 - 18,00x^4 + 6,00x^3 + 47,00x^2 - 4,00x - 30,00
        //Nule polinoma: 5.0, -3.0, 1.0, -1.0
    }
    catch (exception e) {
        cout<<e.what() << "\n";
    }
    return 0;
}
	