// projet_graph.cpp : définit le point d'entrée pour l'application console.
//


#include "stdafx.h"
#include "Fichiers.h"
#include "time.h" 
#include "Initialisation.h"
#include "Metaheuristiques.h"
#include "Solution.h"
#include <thread>

using namespace std;

int main()
{
	int choix = 0;
	/*choix par défaut du fichier*/
	string nameFichier="data9";
	/*le pourcentage nous sert à déterminer le nbr de sommet dans le ring*/
	float pourcentage = 1;
	/*temps d'exécution*/
	time_t depart, arrivee;
	
	//cout << "--------------------------------------------------------------------------------" << endl;
	//-----------------------------------------------------------------------------------------------
	      //NO=0;N=1;NE=2;O=3;E=4;SO=5;S=6;SE=7

	do {
		system("cls");
		cout << "---------- Metaheuristique Groupe 1 ----------" << endl;
		cout << endl;
		cout << "1) Entrer le nom du fichier" << endl;
		cout << "2) Calculer la Metaheuristique" << endl;
		cout << "3) Quitter" << endl;
		cout << endl;
		cout << "Choix: ";
		cin >> choix;
		switch(choix)
		{
		case 1:
			system("cls");
			cout << "---------- Metaheuristique Groupe 1 ----------" << endl;
			cout << endl;
			cout << "Entrer le nom du fichier: ";
			cin >> nameFichier;
			break;
		case 3:
			quick_exit(EXIT_SUCCESS);
			break;
		default:
			break;

		
		}

		if (choix != 1)
		{
			system("cls");
			cout << "---------- Metaheuristique Groupe 1 ----------" << endl;
			cout << endl;
			cout << "Calcul de la Metaheuristique en cours ..." << endl;
			time(&depart);

			string url = "../" + nameFichier + ".dat";//emplacement du fichier
			//ouverture du fichier
			Fichiers data(url);

			//cout << data.getnbrColonnes() << endl; //0-50  //1-51
			//cout << data.getnbrLignes() << endl; //0-101   //1-102
			//cout << data.getElement(101, 0) << endl;

			Solution solutionOptimale(Metaheuristiques::RechercheLocale(data));
			Solution solutionBis(Metaheuristiques::RechercheLocale(data, 0.5), data);
			//on compare la solution entre 50% du ring et 100% du ring
			if (solutionOptimale.getCout() <= solutionBis.getCout()) {
				// si 100% est <= à 50% du ring alors on va calculer pour 75% du ring
				pourcentage = solutionOptimale.getAnneau().getPourcentage() - (solutionOptimale.getAnneau().getPourcentage() - solutionBis.getAnneau().getPourcentage()) / 2;
				solutionBis = Solution(Metaheuristiques::RechercheLocale(data, pourcentage), data); // cette solution sera donc pour 75% du ring

				if (solutionOptimale.getCout() <= solutionBis.getCout()) {
					// si 100% est <= à 75% du ring alors on va caculer pour 87.5% du ring
					pourcentage = solutionOptimale.getAnneau().getPourcentage() - (solutionOptimale.getAnneau().getPourcentage() - solutionBis.getAnneau().getPourcentage()) / 2;
					solutionBis = Solution(Metaheuristiques::RechercheLocale(data, pourcentage), data);// cette solution sera donc pour 87.5% du ring

					if (solutionOptimale.getCout() > solutionBis.getCout()) {
						solutionOptimale.setSolution(solutionBis); //la solution optimale est 87.5 si le coût total est plus petit que 100% du ring
					}
				}
				else {
					// si 100% est > à 75% du ring alors on va caculer pour 62.5% du ring
					pourcentage = solutionBis.getAnneau().getPourcentage() - (solutionOptimale.getAnneau().getPourcentage() - solutionBis.getAnneau().getPourcentage()) / 2;
					solutionOptimale.setSolution(solutionBis); // on donne la solution optimale pour 75%  du ring
					solutionBis = Solution(Metaheuristiques::RechercheLocale(data, pourcentage), data);

					if (solutionOptimale.getCout() > solutionBis.getCout()) {
						solutionOptimale.setSolution(solutionBis); //la solution optimale est 62.5 si le coût total est plus petit que 75% du ring
					}
				}
			}
			else {
			// si 100% est > que 50% du ring alors on va calculer pour 25% du ring
				pourcentage = solutionBis.getAnneau().getPourcentage() - (solutionOptimale.getAnneau().getPourcentage() - solutionBis.getAnneau().getPourcentage()) / 2;
				solutionOptimale.setSolution(solutionBis); // selection optimale = 50% du ring
				solutionBis = Solution(Metaheuristiques::RechercheLocale(data, pourcentage), data);// cette solution sera donc pour 25% du ring

				if (solutionOptimale.getCout() <= solutionBis.getCout()) {
					// si 50% est <= à 25% du ring alors on va caculer pour 37.5% du ring
					pourcentage = solutionOptimale.getAnneau().getPourcentage() - (solutionOptimale.getAnneau().getPourcentage() - solutionBis.getAnneau().getPourcentage()) / 2;
					solutionBis = Solution(Metaheuristiques::RechercheLocale(data, pourcentage), data);// cette solution sera donc pour 37.5

					if (solutionOptimale.getCout() > solutionBis.getCout()) {
						solutionOptimale.setSolution(solutionBis);//la solution optimale est 37.5 si le coût total est plus petit que 50%
					}
				}
				else {
						// si 50% est > à 25% du ring alors on va caculer pour 12.5% du ring
					pourcentage = solutionBis.getAnneau().getPourcentage() - (solutionOptimale.getAnneau().getPourcentage() - solutionBis.getAnneau().getPourcentage()) / 2;
					solutionOptimale.setSolution(solutionBis);// on donne la solution optimale pour 25%  du ring
					solutionBis = Solution(Metaheuristiques::RechercheLocale(data, pourcentage), data);

					if (solutionOptimale.getCout() > solutionBis.getCout()) {
						solutionOptimale.setSolution(solutionBis);//la solution optimale est 12.5 si le coût total est plus petit que 25%
					}
				}
			}
			//on écrit la solution dans le fichier
			solutionOptimale.afficher();

			system("cls");
			cout << "---------- Metaheuristique Groupe 1 ----------" << endl;
			cout << endl;
			cout << "Calcul effectue avec succes et fichier cree" << endl;
			cout << endl;
			time(&arrivee);
			//on affiche le temps de calcul
			cout << "Temps de calcul: " << difftime(arrivee, depart) << " seconde(s)" << endl;
			cout << endl;
			cout << "Appuyer sur une touche pour ouvrir le fichier et retourner au menu" << endl;
			cout << endl;
			system("pause >NUL");
			system("start ..\\Sortie_Metaheuristique.txt");
		}

	} while (choix != 4);

	//-----------------------------------------------------------------------------------------------------
	//system("pause >NUL"); //met le programme en pause sans le "Appuyer sur une touche pour continuer"
}

