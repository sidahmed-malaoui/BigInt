#include <iostream>
#include <string>
#include <vector>
#include <math.h>

#include "BigInt.h"
using namespace std;

/* méthodes ===================================================================================================================== */

BigInt::BigInt(string s_nombre) :
    mda_nombre(0), //Je crée un vecteur vide (Je vais ajouter des cases plus tard dans le constructeur).
    m_signe(1)
{
    /* Si le nombre est négative (la chaine «s_nombre» commence par un -). Alors on met notre attribut «m_signe» à -1, et on
       supprime le caractère '-' de la chaine «s_nombre». */
    if(s_nombre[0] == '-')
    {
        m_signe = -1;
        s_nombre.erase(s_nombre.begin()); //Cette istruction supprime le 1èr caractère.
    }
    /* On utilise cette boucle pour supprimer tous les zeros non significatif. */
    while(s_nombre[0] == '0')
        s_nombre.erase(s_nombre.begin());

    /* Si la chaine contenait 0 au début alors on met 0 dans notre tableau (pour que le tableau ne soit pas vide), et on met
       notre signe à 1 (car, ça n'a aucun sens de mettre un 0 négative). */
    if(s_nombre.size() == 0)
    {
        mda_nombre.push_back(0);
        m_signe = 1;
        return;
    }
    int i(s_nombre.size() - 1);
    while(i >= 0)
    {
        /* On converti chaque case de le chaine «s_nombre» en un nombre, et on le met dans le vecteur «mda_nombre».
           À la fin de la conversion, le case numero 0 du vecteur «mda_nombre» contiendra le chiffre du poids le plus faible.
           Et la dernière case contiendra le chiffre du poids le plus fort. */
        mda_nombre.push_back(s_nombre[i] - '0');
        --i;
    }
}


BigInt::BigInt(int nombre) :
    mda_nombre(0),
    m_signe(1)
{
    /* Si le nombre est nul alors on ajoute une seule case nule dans notre vecteur. */
    if(nombre == 0)
    {
        mda_nombre.push_back(0);
        return;
    }
    /* Si le nombre donnee en prm est négative, alors on l'invrse et on met l'attribut «m_signe» à -1. */
    else if(nombre < 0)
    {
        m_signe = -1;
        nombre = -nombre;
    }
    /* À chaque itération de la boucle on insére le nombre du poids le plus faible à la fin du vecteur. Alors à la fin de la boucle,
       La 1ère case du vecteur, contiendra le chiffre du poids le plus faible. */
    while(nombre > 0)
    {
        mda_nombre.push_back(nombre % 10);
        nombre /= 10;
    }
}


void BigInt::afficher(ostream &flux) const
{
    if(m_signe == -1)
        flux << '-';
    for(int i(mda_nombre.size() - 1); i >= 0; i--)
    {
        flux << mda_nombre[i];
        if(i % 3 == 0 && i != 0)
            flux << " ";
    }
}

void BigInt::simplifie()
{
    int retenue(0);

    retenue = mda_nombre[0] / 10;
    mda_nombre[0] %= 10;
    for(unsigned int i(1); i < mda_nombre.size(); i++)
    {
        mda_nombre[i] += retenue;
        retenue = mda_nombre[i] / 10;
        mda_nombre[i] %= 10;
    }
    while(retenue != 0)
    {
        mda_nombre.push_back(retenue % 10);
        retenue /= 10;
    }
    /* Cette boucle est utiliser pour supprimer tous les 0 non significatif dans notre vecteur nombre. */
    for(int i(mda_nombre.size() - 1); mda_nombre[i] == 0 && i > 1; i--)
        mda_nombre.pop_back();
}

bool BigInt::equal(const BigInt &b) const
{
    /* Si les tailles de nos deux nombres sont différentse, ou l'un des chiffres est différents, ou ils ont des signes différents,
       alors on renvoie false. */
    if(m_signe != b.m_signe || mda_nombre.size() != b.mda_nombre.size())
        return false;
    for(unsigned int i(0); i < mda_nombre.size(); i++)
        if(mda_nombre[i] != b.mda_nombre[i])
            return false;
    /* Si on arrive à la fin de la fonction sans détecter une différence alors on renvoie «true» (car les deux nombres sont égaux). */
    return true;
}

bool BigInt::lower(const BigInt &b) const
{
    /* J'ai utilisé la conversion, car j'ai un problème en utilisant le test sans la conversion. Le problème est que la variabe
       «m_signe» est un int, alors que «mda_nombre.size()» est d'un autre type. Alors pour que la multiplication passe sans
       problème, il faut convertir. (Je ne comprends pas vraiment comment ce problème est entrer dedans, j'ai juste testé dans le
       main et la multiplication marche à merveille, WTF) */
    if(m_signe * (int) mda_nombre.size() > b.m_signe * (int) b.mda_nombre.size())
        return false;
    else if(m_signe * (int) mda_nombre.size() < b.m_signe * (int) b.mda_nombre.size())
        return true;
    for(int i(mda_nombre.size() - 1); i >= 0; i--)
    {
        if(m_signe * mda_nombre[i] > b.m_signe * b.mda_nombre[i])
            return false;
        else if(m_signe * mda_nombre[i] < b.m_signe * b.mda_nombre[i])
            return true;
    }
    /* Si on arrive à ce retourne, alors nos nombres sont égaux, alors on renvoie false. */
    return false;
}

BigInt BigInt::abs() const
{
    BigInt resultat(*this);

    resultat.m_signe = 1;
    return resultat;
}

short int BigInt::operator[](unsigned int i) const
{
    /* Si l'indice du chiffre, que l'utilisateur veut récuperer, est supérieur à notre nombre, alors on retourne -1. En faisant cela
       l'utilisateur comprendra que la position qu'il souhaite récuperer n'existe pas (car il n'y a pas de nombre négative dans
       notre vecteur). */
    if(i >= mda_nombre.size())
        return -1;
    else
        return mda_nombre[i];
}

/* operators affichage =========================================================================================================== */

ostream &operator<<(ostream &flux, BigInt const &n)
{
    n.afficher(flux);
    return flux;
}

istream &operator>>(istream &flux, BigInt &n)
{
    string s_nombre;

    flux >> s_nombre;
    n = s_nombre;
    return flux;
}

/* operators Logique ======================================================================================================= */

bool operator==(BigInt const &a, BigInt const &b)
{
    return a.equal(b);
}

bool operator<(BigInt const &a, BigInt const &b)
{
    return a.lower(b);
}

bool operator<=(BigInt const &a, BigInt const &b)
{
    return (a < b || a == b);
}

bool operator>(BigInt const &a, BigInt const &b)
{
    return !(a <= b);
}

bool operator>=(BigInt const &a, BigInt const &b)
{
    return !(a < b);
}

bool operator!=(BigInt const &a, BigInt const &b)
{
    return !(a == b);
}

/* operators arithmétique ======================================================================================================= */

BigInt &BigInt::operator+=(BigInt const &n)
{
    unsigned int i(0);

    /* Si nos deux nombres ont le même signe, alors on utilise ce block pour faire l'addition. */
    if(m_signe == n.m_signe)
    {
        /* On fait la somme de tous les cases des deux vecteurs grace à ces deux boucles. */
        for(i = 0; i < mda_nombre.size() && i < n.mda_nombre.size(); i++)
            mda_nombre[i] += n.mda_nombre[i];
        while(i < n.mda_nombre.size())
        {
            mda_nombre.push_back(n.mda_nombre[i]);
            i++;
        }
        /* On regle notre vecteur, pour que chaque case contiendra un seul chiffre. */
        simplifie();
    }
    /* Sinon, si nos deux vecteurs ont des signes différents, alors on utilise ce block pour faire l'addition. */
    else if(m_signe != n.m_signe)
    {
        BigInt resultat;

        resultat.mda_nombre.pop_back();
        /* Si le nombre actuel est négative, alors on utilise ce block pour faire la somme (c'est un peut dur à expliquer la méthode). */
        if(m_signe == -1)
        {
            m_signe = 1;
            if(*this > n)
            {
                resultat.m_signe = -1;
                for(i = 0; i < n.mda_nombre.size(); i++)
                    resultat.mda_nombre.push_back(mda_nombre[i] - n.mda_nombre[i]);
                while(i < mda_nombre.size())
                {
                    resultat.mda_nombre.push_back(mda_nombre[i]);
                    i++;
                }
            }
            else
            {
                resultat.m_signe = 1;
                for(i = 0; i < mda_nombre.size(); i++)
                    resultat.mda_nombre.push_back(n.mda_nombre[i] - mda_nombre[i]);
                while(i < n.mda_nombre.size())
                {
                    resultat.mda_nombre.push_back(n.mda_nombre[i]);
                    i++;
                }
            }
        }
        /* Si le nombre donnée en prm qui est négative, alors on utilise ce block pour faire la somme (c'est un peu dur à expliquer la méthode). */
        else if(n.m_signe == -1)
        {
            m_signe = -1;
            if(*this > n)
            {
                resultat.m_signe = -1;
                for(i = 0; i < mda_nombre.size(); i++)
                    resultat.mda_nombre.push_back(n.mda_nombre[i] - mda_nombre[i]);
                while(i < n.mda_nombre.size())
                {
                    resultat.mda_nombre.push_back(n.mda_nombre[i]);
                    i++;
                }
            }
            else
            {
                resultat.m_signe = 1;
                for(i = 0; i < n.mda_nombre.size(); i++)
                    resultat.mda_nombre.push_back(mda_nombre[i] - n.mda_nombre[i]);
                while(i < mda_nombre.size())
                {
                    resultat.mda_nombre.push_back(mda_nombre[i]);
                    i++;
                }
            }
        }
        /* On régle notre résultat grace à cette boucle. En cas ou il y a des cases qui contient des nombres négatives. */
        int retenue(0);
        for(i = 0; i < resultat.mda_nombre.size(); i++)
        {
            resultat.mda_nombre[i] += retenue;
            retenue = 0;
            if(resultat.mda_nombre[i] < 0)
            {
                resultat.mda_nombre[i] += 10;
                retenue = -1;
            }
        }
        /* On enleve tous les 0 non significatif avec cette boucle. */
        while(resultat.mda_nombre[resultat.mda_nombre.size() - 1] == 0 && resultat.mda_nombre.size() > 1)
            resultat.mda_nombre.pop_back();
        *this = resultat;
    }

    return *this;
}

BigInt &BigInt::operator++(int)
{
    return (*this += 1);
}

BigInt operator+(BigInt const &a, BigInt const &b)
{
    BigInt resultat(a);

    resultat += b;
    return resultat;
}

BigInt &BigInt::operator-=(BigInt const &b)
{
    BigInt copy(b);

    copy.m_signe = -copy.m_signe;
    *this += copy;
    return *this;
}

BigInt &BigInt::operator--(int)
{
    return (*this -= 1);
}

BigInt operator-(BigInt const &a, BigInt const &b)
{
    BigInt resultat(a);

    resultat -= b;
    return resultat;
}

BigInt operator-(BigInt const &b)
{
    return (0 - b);
}

BigInt &BigInt::operator*=(BigInt const &b)
{
    unsigned int i = 0, j = 0;
    int sauvSigne = m_signe; //Je sauvegarde le signe initiale de mon objet actuel avec cette variable.
    unsigned int taille(b.mda_nombre.size());
    BigInt resultat[taille];

    for(i = 0; i < taille; i++)
    {
        /* Pour vider le vecteur «mda_nombre» correspondant, avant de le remplire dans la boucle suivante. Si je ne fais pas ça,
           alors chaque vecteur aura un 0 de plus au début, car le constructeur par défault pour le BigInt donne un vecteur
           «mda_nombre» avec une case qui contient 0. */
        resultat[i].mda_nombre.pop_back();
        for(j = 0; j < mda_nombre.size(); j++)
            resultat[i].mda_nombre.push_back(b.mda_nombre[i] * mda_nombre[j]);
    }
    /* On simplifie chaque BigInt. Car on a ajouté des cases au vecteurs «mda_nombre» de BigInt dans la boucle précédent. */
    for(i = 0; i < taille; i++)
        resultat[i].simplifie();
    /* On multiplie chaque BigInt par pow(10, i), dont i représente sa position - 1 dans la multiplication. */
    for(i = 0; i < taille; i++)
        for(j = 0; j < i; j++)
            resultat[i].mda_nombre.insert(resultat[i].mda_nombre.begin(), 0);
    /* J'utilise cette boucle pour supprimer tous les 0 non significatifs des vecteurs. */
    for(i = 0; i < taille; i++)
        resultat[i].simplifie();
    /* Je fais la somme de tous les BigInt du vecteur «resultat». */
    *this = 0;
    for(i = 0; i < taille; i++)
        *this += resultat[i];

    m_signe = sauvSigne * b.m_signe;
    return *this;
}

BigInt operator*(BigInt const &a, BigInt const &b)
{
    BigInt resultat(a);

    resultat *= b;
    return resultat;
}

BigInt &BigInt::operator/=(BigInt const &b)
{
    BigInt resultat, reste, diviseur(b.abs());
    int i = mda_nombre.size() - 1, tmp = 0;

    resultat.mda_nombre.pop_back();
    reste.mda_nombre.pop_back();

    /* J'utilise cette boucle et les 2 instructions qui suivent pour composer pour la 1ère fois mon reste. */
    while(reste < diviseur && i >= 0)
    {
        reste.mda_nombre.insert(reste.mda_nombre.begin(), this->mda_nombre[i]);
        i--;
    }
    i++;
    reste.mda_nombre.erase(reste.mda_nombre.begin());
    while(i >= 0)
    {
        if(reste == 0)
            reste.mda_nombre.pop_back();
        reste.mda_nombre.insert(reste.mda_nombre.begin(), this->mda_nombre[i]);
        i--;
        for(tmp = 1; (diviseur * tmp) <= reste; tmp++);
        resultat = resultat * 10 + (tmp - 1);
        reste -= (tmp - 1) * diviseur;
    }

    resultat.m_signe = m_signe * b.m_signe;
    *this = resultat;
    return *this;
}

BigInt operator/(BigInt const &a, BigInt const &b)
{
    if(b == 0)
        return 0;
    BigInt resultat(a);

    resultat /= b;
    return resultat;
}

BigInt &BigInt::operator%=(BigInt const &b)
{
    *this = this->abs() - (this->abs() / b.abs()) * b.abs();
    return *this;
}

BigInt operator%(BigInt const &a, BigInt const &b)
{
    BigInt resultat(a);

    resultat %= b;
    return resultat;
}

BigInt &BigInt::operator^=(BigInt const &b)
{
    if(b == 0 || *this == 1)
        return *this = 1; //J'affecte 1 à l'objet actuel, et je le retourne.

    BigInt resultat(1);
    for(int i(0); i < b; i++) //Cette boucle sert à faire la puissance.
        resultat *= *this;
    return *this = resultat; //J'affecte resultat à l'objet actuel, et je le retourne.
}


BigInt operator^(BigInt const &a, BigInt const &b)
{
    BigInt resultat(a);

    resultat ^= b;
    return resultat;
}

/* functions ==================================================================================================================== */
