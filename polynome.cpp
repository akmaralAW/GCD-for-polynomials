// DON'T MODIFY THE FILE

#include "polynome.hpp"

#include <assert.h>
#include <algorithm>
#include <math.h>

Polynome::Polynome()
  : m_coefficients(1, Rationnel(0))
{
  simplifier();
}

// Create a polynomial where the coefficient of x ^ i is coefficients [i]
//
// Complexity: Theta (n) or the size of the vector coefficients
Polynome::Polynome(const std::vector<Rationnel>& coefficients)
  : m_coefficients(coefficients)
{
  simplifier();
}

//
//Create the monomial: coefficient * x^degre
//
// Complexity: Theta(d) where d is the degree of the polynomial
Polynome::Polynome(const Rationnel& coefficient, unsigned int degre)
  : m_coefficients(degre + 1)
{
  m_coefficients[degre] = coefficient;
  simplifier();
}

// Copy builder
//
// Complexite: Theta(d) where d is the degree of the polynomial
Polynome::Polynome(const Polynome& polynome)
  : m_coefficients(polynome.m_coefficients)
{
}

void Polynome::simplifier() {
  unsigned int i = m_coefficients.size();
  while (i > 0 && m_coefficients[i - 1].numerateur() == 0) {
    i--;
  }
  m_coefficients.resize(i);
  assert(m_coefficients.empty() || m_coefficients.back().numerateur() != 0);
}

// Complexite: Theta(1)
int Polynome::degre() const {
  return m_coefficients.size() - 1;
}

//Returns the coefficient of the monomial x^degre.
//
// Complexity: Theta(1)
const Rationnel Polynome::coefficient(unsigned int degre) const {
  if (degre >= m_coefficients.size())
    return Rationnel(0);
  return m_coefficients.at(degre);
}

//
//Returns the product of the polynomial with the monomial coefficient_monome * x^degre_monome
//
// Complexite: Theta(n) where n is the degree of the returned polynomial
Polynome Polynome::multiplication_par_monome(const Rationnel& coefficient_monome, unsigned int degre_monome) const {
  std::vector<Rationnel> coefficients_produit(m_coefficients.size() + degre_monome, Rationnel(0));

  for (unsigned int i = 0; i < m_coefficients.size(); i++) {
    coefficients_produit[i + degre_monome] = m_coefficients[i] * coefficient_monome;
  }
  return Polynome(coefficients_produit);
}

// Interchange the content of the polynomial with p
//
// Complexite: Theta(1)
void Polynome::swap(Polynome& p) {
  m_coefficients.swap(p.m_coefficients);
}

//  Compare the degrees of polynomials. Attention, the polynomial p(x) = 0 a
// a degree of -1. This is certainly not true from a point of view
// math, but it simplifies many things on the algorithmic side.
// 
// Complexite:
//   Worst case:     Theta(1)
bool operator<(const Polynome& a, const Polynome& b) {
  return a.degre() < b.degre();
}

// Complexite:
//    Worst case : Theta(d) where d is the degree of the polynomials
//    Best case : Theta(1)   (if the polynomials do not have the same degree)
bool operator==(const Polynome& a, const Polynome& b) {
  return a.m_coefficients == b.m_coefficients;
}

// Complexite: Theta(degre_a + degre_b) where degree_a and degree_b are the degrees of polynomials a and b
Polynome operator+(const Polynome& a, const Polynome& b) {
  std::vector<Rationnel> coefficients(std::max(a.degre(), b.degre()) + 1);
  for (unsigned int i = 0; i < coefficients.size(); i++) {
    coefficients[i] = a.coefficient(i) + b.coefficient(i);
  }
  return Polynome(coefficients);
}

// Complexity: Theta(degre_a + degre_b) where degree_a and degree_b are the degrees of polynomials a and b
Polynome operator-(const Polynome& a, const Polynome& b) {
  std::vector<Rationnel> coefficients(std::max(a.degre(), b.degre()) + 1);
  for (unsigned int i = 0; i < coefficients.size(); i++) {
    coefficients[i] = a.coefficient(i) - b.coefficient(i);
  }

  return Polynome(coefficients);
}

// Complexite: Theta(d^2) where d is the greatest degree between polynomials a and b
Polynome operator*(const Polynome& a, const Polynome& b) {
  std::vector<Rationnel> coefficients(a.degre() + b.degre() + 1, Rationnel(0));
  for (unsigned int i = 0; i < coefficients.size(); i++) {
    for (unsigned int j = 0; j <= i; j++) {
      coefficients[i] = coefficients[i] + a.coefficient(j) * b.coefficient(i - j);
    }
  }
  return Polynome(coefficients);
}

// Complexite: O(d) where d is the degree of the polynomial
std::ostream& operator<<(std::ostream& os, const Polynome& a) {
  if (a.degre() < 0) {
    return os << "0";
  }

  Rationnel un(1, 1);

  if (a.coefficient(a.degre()) != un || a.degre() == 0) {
    os << a.coefficient(a.degre());
  }
  
  if (a.degre() > 0) {
    os << "x";
    if (a.degre() > 1) {
      os << "^" << a.degre();
    }
  }
  
  for (int i = a.degre() - 1; i >= 0; i--) {
    if (a.coefficient(i).numerateur() != 0) {
      os << " + ";
      if (a.coefficient(i) != un || i == 0) {
	os << a.coefficient(i);
      }
      if (i > 0) {
	os << "x";
	if (i > 1) {
	  os << "^" << i;
	}
      }
    }
  }
  return os;
}
