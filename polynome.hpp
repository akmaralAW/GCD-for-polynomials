// NE PAS MODIFIER CE FICHIER

#ifndef POLYNOME
#define POLYNOME

#include <vector>
#include "rationnel.hpp"

class Polynome {
private:
  std::vector<Rationnel> m_coefficients;

  void simplifier();
public:
  Polynome();			//  Create the polynomial p(x) = 0
  Polynome(const std::vector<Rationnel>& coefficients); // Create a polynomial where the coefficient of x ^ i is coefficients [i]
  Polynome(const Rationnel& coefficient, unsigned int degre); // Create the monomial: coefficient * x ^ degree
  Polynome(const Polynome& polynome); // Copy builder

  int degre() const;
  const Rationnel coefficient(unsigned int degre) const;

  // Returns the product of the polynomial with the monomial coefficient_monomial * x ^ degre_monome
  Polynome multiplication_par_monome(const Rationnel& coefficent, unsigned int degre) const;

  void swap(Polynome& p); 	// Interchange the content of the polynomial with that of p

  friend bool operator<(const Polynome& a, const Polynome& b);
  friend bool operator==(const Polynome& a, const Polynome& b);
};

// Polynomial comparison operators
inline bool operator> (const Polynome& a, const Polynome& b){ return b < a; }
inline bool operator<=(const Polynome& a, const Polynome& b){ return !(a > b); }
inline bool operator>=(const Polynome& a, const Polynome& b){ return !(a < b); }  
inline bool operator!=(const Polynome& a, const Polynome& b){ return !(a == b); }

// Polynomial arithmetic operators
Polynome operator+(const Polynome& a, const Polynome& b);
Polynome operator-(const Polynome& a, const Polynome& b);
Polynome operator*(const Polynome& a, const Polynome& b);

std::ostream& operator<<(std::ostream& os, const Polynome& a);

#endif
