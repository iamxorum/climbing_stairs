// ! ############################################################################################
// ! După o noapte de chef Cetăţeanul Turmentat se află în faţa unei mari probleme:
// ! trebuie să urce cele n trepte până la uşa casei sale. Din cauza stării de ebrietate avansate
// ! Cetăţeanul Turmentat nu poate să urce decât fie o treaptă, fie două. Ajutaţi-l,
// ! indicându-i  toate  modurile  în  care  el  poate  să  urce  cele  n  trepte,
// ! precum şi câte moduri are în total la dispoziţie.
// ! ############################################################################################

#include <iostream>
#include <stdlib.h>
#include <fstream>

using namespace std;

int nrSolutii = 0, lengthROS, trepte, *sol, *rangeOfStairs;

void bktCetTur(int k, int remainder, ostream &fout)
{

    int rez = 0;
    for (int i = 0; i < lengthROS; i++)
    {
        sol[k] = rangeOfStairs[i]; // * Se adauga in vectorul de solutii range-ul de trepte care poate fi urcat de o data
        rez = remainder - sol[k];  // * Se calculeaza scaderea intre Remainder
        if (rez >= 0)              // * Daca rezultatul este mai mare sau egal cu 0, mergem inauntru
        {
            if (rez == 0) // * Daca rezultatul este egal cu 0 intram asta inseamna ca am gasit o solutie
            {
                nrSolutii++; // * Se creste numarul de solutii
                fout << "|\t\t Nr. " << nrSolutii << "  \t\t | \t\t ";
                for (int j = 0; j <= k; j++)
                {
                    fout << sol[j] << " "; // * Se adagua in fisier solutia
                }
                fout << "\n";
            }
            else
            {
                bktCetTur(k + 1, rez, fout); // * Daca rezultatul nu este egal cu 0, atunci calculam pentru pozitia urmatoare din solutie
            }
        }
    }
}

int main()
{
    ifstream fin("Valoriile de input.txt"); // * Citeste din fisier
    if (!fin)
    {
        cerr << "INPUT INEXISTENT!!!!" << endl; // * Nu a reusit sa citeasca fisierul
        exit(-1);
    }

    ofstream fout("Rezultat.txt");

    // Primul rand este destinat cantitatea treptelor care Cetateanul Turmentat trebuie sa le urce
    fin >> trepte; // * Citeste treptele
    if (trepte <= 0)
    {
        if (trepte < 0)
        {
            cerr << "NUMAR DE TREPTE FOARTE MIC!" << endl; // * Treptele citite sun mai mici de 0
            exit(-1);
        }
        fout << "Rezultatul e imposibil de calculat pentru ca nu exista nicio TREAPTA!";
        return 1;
    }

    sol = new int[trepte];

    // Al doilea randa este destinat numarului care defineste marimea vectorului rangeOfStairs
    fin >> lengthROS; // * Citeste lungimea vectorului de trepte
    if (lengthROS < 1)
    {
        cerr << "MARIME VECTOR NEVALIDA!" << endl; // * Lungimea citita e nevalida
        exit(-3);
    }

    // Al treilea rand este destinat unui vector care contine posibilitatiile de a urca treptele
    //(adica, [1, 2] = poate urca 1 treapta sau 2 la fiecare pas...)
    rangeOfStairs = new int[lengthROS];
    for (int i = 0; i < lengthROS; i++)
    {
        fin >> rangeOfStairs[i];
    }

    fin.close();

    fout << "Cetateanul Turmentat, ca sa urce " << trepte << " trepte urcand, de fiecare data, trepte din range-ul asta { ";
    for (int i = 0; i < lengthROS - 1; i++)
    {
        fout << rangeOfStairs[i] << " | ";
    }
    fout << rangeOfStairs[lengthROS - 1] << " }, solutiile la dispozitie sunt urmatoarele:\n";
    fout << "------------------------------------------------------------------------------\n";
    fout << "|\t\t Solutii \t\t | \t\t Descriere Solutie\n";
    bktCetTur(0, trepte, fout);
    fout << "------------------------------------------------------------------------------\n";
    fout << "Numarul de moduri de a urca treptele este de: " << nrSolutii;
    cout << "Numarul de moduri de a urca " << trepte << " trepte este de: " << nrSolutii << endl;

    return 0;
}
