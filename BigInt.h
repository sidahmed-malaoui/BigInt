#ifndef DEF_BIGINT
#define DEF_BIGINT

#include <iostream>
#include <string>
#include <vector>

/* classes ======================================================================================================================= */

class BigInt
{
    public:

    BigInt(int nombre = 0);
    BigInt(std::string nombre);

    void afficher(std::ostream &flux) const;
    void simplifie();
    BigInt abs() const; //Cette méthode retourne la valeur absolue du BigInt actuel.
    /* Cette méthode permet de récuperer un chiffre de notre nombre. */
    short int operator[](unsigned int i) const;

    /* Operators Logique ============================================================== */

    /* Cette méthode renvoi true si l'objet actuel est égale à «b». */
    bool equal(BigInt const &b) const;
    /* Cette méthode renvoie true si l'objet actuel est inférieur à b. */
    bool lower(BigInt const &b) const;

    /* Operators Arithmétique ========================================================= */

    BigInt &operator+=(BigInt const &b);
    BigInt &operator++(int); //J'ai mis «int» car la fonction operator++() doit avoir un prm.
    BigInt &operator-=(BigInt const &b);
    BigInt &operator--(int);
    BigInt &operator*=(BigInt const &b);
    BigInt &operator/=(BigInt const &b);
    BigInt &operator%=(BigInt const &b);
    BigInt &operator^=(BigInt const &b);

    protected:

    /* chaque case de ce vecteur contiendra un chiffre de notre nombre. La case numero 0 contiendra le chiffre du poids le plus
       faible. Et la dernière case contiendra le chiffre de poids le plus fort. */
    std::vector<short int > mda_nombre; //"mda" veut dire "Member Dynamic Array".
    /* Cette variable représente le signe. Elle vaut -1 si le nombre est négative. Et elle vaut 1 si le nombre est positive. */
    int m_signe;
};

/* operators =================================================================================================================== */

std::ostream &operator<<(std::ostream &flux, BigInt const &n);
std::istream &operator>>(std::istream &flux, BigInt &n);

/* Operators Arithmétique ============================================================== */

BigInt operator+(BigInt const &a, BigInt const &b);
BigInt operator-(BigInt const &a, BigInt const &b);
BigInt operator-(BigInt const &b); //C'est l'opérateur - unaire.
BigInt operator*(BigInt const &a, BigInt const &b);
BigInt operator/(BigInt const &a, BigInt const &b);
BigInt operator%(BigInt const &a, BigInt const &b);
BigInt operator^(BigInt const &a, BigInt const &b);

/* Operators Logique =================================================================== */

bool operator==(BigInt const &a, BigInt const &b);
bool operator<(BigInt const &a, BigInt const &b);
bool operator<=(BigInt const &a, BigInt const &b);
bool operator>(BigInt const &a, BigInt const &b);
bool operator>=(BigInt const &a, BigInt const &b);
bool operator!=(BigInt const &a, BigInt const &b);

/* functions =================================================================================================================== */

#endif
