#include "division.hpp"

#include <assert.h>

void division(const Polynome& dividende, // The polynomial that is divided
	      const Polynome& diviseur,  // The polynomial that divides
	      Polynome& quotient,	   // Output parameter: the result of the division
	      Polynome& reste) {	   // Output parameter: the rest of the division
  assert(diviseur.degre() > 0 || diviseur.coefficient(0).numerateur() != 0); // No division by zero

    Polynome dividende_copy = dividende;
    std::vector<Rationnel> q_coefficients ((dividende.degre() - diviseur.degre()) + 1, Rationnel(0)) ;
    while(dividende_copy.degre() >= diviseur.degre()){
        Polynome d = diviseur.multiplication_par_monome(1, (dividende_copy.degre()-diviseur.degre()));
        Rationnel d_coefficient = dividende_copy.coefficient(dividende_copy.degre())/d.coefficient(d.degre());
        q_coefficients.at(dividende_copy.degre()-diviseur.degre()) = d_coefficient;
        d = d.multiplication_par_monome(d_coefficient,0);
        dividende_copy = dividende_copy - d;
    }
    reste = dividende_copy;
    quotient = Polynome (q_coefficients);
}

Polynome plus_grand_commun_diviseur(const Polynome& a, const Polynome& b) {
    assert(a >= b);
    assert(a.degre() > 0 || a.coefficient(0).numerateur() != 0);
    Polynome q;
    Polynome r;
    Polynome a_copy = a;
    Polynome b_copy = b;
    while (b_copy.degre() != 0 && b_copy.coefficient(0).numerateur() != 0) {
        division(a_copy, b_copy, q, r);
        if (r.degre() == 0){
            return Polynome(r);
        }
        else {
            a_copy.swap(b_copy);
            b_copy.swap(r);
        }
    }
    r.swap(a_copy);
    return Polynome(r);
}

