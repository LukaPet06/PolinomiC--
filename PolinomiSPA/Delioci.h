#pragma once
#include <set>
#include <math.h>
using namespace std;
/**
 * Pomocna klasa koja pronalazi delioce odredjenog koeficijenta
 */
class Delioci
{
public:
    /**
     * Najpre se odredjuje granica, odnosno koliko brojeva treba proveriti</br>
     * U skup se dodaju brojevi u parovima, odnosno ukoliko broj bez ostatka deli koeficijent, dodaju se i taj broj i njihov kolicnik</br>
     * Primer za 35 se u parovima dodaju 1,35 i 5,7
     * @param koeficijent broj
     * @return jedinstvene vrednosti, brojeva koji bez ostatka dele poslati parametar
     */
	static set<int> deliociBroja(int koeficijent) {
        int granica = (int)(sqrt(abs(koeficijent))) + 1;
        set<int> deliociSet = set<int>();
        deliociSet.insert(1);
        deliociSet.insert(-1);
        deliociSet.insert(koeficijent);
        deliociSet.insert(-koeficijent);
        for (int i = 2; i <= granica; i++) {
            if (koeficijent % i == 0) {
                deliociSet.insert((double)i);
                deliociSet.insert((double)-i);
                deliociSet.insert(koeficijent / i);
                deliociSet.insert(-koeficijent / i);
            }
        }
        return deliociSet;
	}
};

