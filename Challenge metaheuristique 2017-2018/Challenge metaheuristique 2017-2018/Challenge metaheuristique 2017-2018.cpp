// Challenge metaheuristique 2017-2018.cpp : Defines the entry point for the console application.
//
#include <stdio.h>
#include <stdlib.h>
#include "stdafx.h""
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main()
{
	int nbrLignes = 0;
	int nbrColonnes=0;
	string fichier = "D:/Users/Nicolas/Desktop/data1.dat";//emplacement du fichier


	ifstream monFluxRead(fichier);
	if (monFluxRead)
	{
		string liste;

		monFluxRead >> nbrColonnes; // récupère le nombre de colonnes
		
		while (getline(monFluxRead, liste)) //récupère le nombre de ligne dans le tableau
		{
			nbrLignes++;
		}		
		monFluxRead.close();
	}
	else
	{
		cout << "ERREUR: Impossible d'ouvrir le fichier en lecture" << endl;
	}


	vector<vector<int>> tabMatrice(nbrLignes-1, vector<int>(nbrColonnes)); //déclaration du vecteur 2D


	monFluxRead.open(fichier);
	if (monFluxRead)
	{
		int nombre;
		int i=-1;
		int j=0;
		bool passage_first = false;

		while (monFluxRead>>nombre) //récupère les nombres sauf le premier (nbrColonnes) et écris les valeurs dans un vecteur 2D
		{
			if (nombre == nbrColonnes && passage_first ==false)
			{
				passage_first = true;
			}
			else
			{
				i++;
				if (i < nbrColonnes - 1)
				{
					tabMatrice[j][i] = nombre;
				}
				else
				{
					i = -1;
					j++;
				}
			}			
		}
		monFluxRead.close();
	}
	else
	{
		cout << "ERREUR: Impossible d'ouvrir le fichier en lecture" << endl;
	}


	system("pause >NUL"); //met le programme en pause sans le "Appuyer sur une touche pour continuer"
}

