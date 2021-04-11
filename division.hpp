// NE PAS MODIFIER CE FICHIER

#ifndef DIVISION
#define DIVISION

#include "polynome.hpp"
void division(const Polynome& dividende, // The polynomial that is divided
	      const Polynome& diviseur,  // The polynomial that divides
	      Polynome& quotient,	   // Output parameter: the result of the division
	      Polynome& reste);	   // Output parameter: the rest of the division

Polynome plus_grand_commun_diviseur(const Polynome& a, const Polynome& b);

#endif
