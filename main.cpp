#include <iostream>
#include <vector>
#include <string>
#include "adressage.h"

#define MSG_BIENVENUE "Bonjour, bienvenue dans l'application de calcul d'adresses IP"

using namespace std;

int main() {
	cout << MSG_BIENVENUE << endl;
	int choix = 0;
	string masque;
	while (choix != 9) {
		cout << "1. Afficher une adresse IP" << endl;
		cout << "2. Afficher la classe d'une adresse IP" << endl;
		cout << "3. Calculer le masque d'un r�seau via CIDR" << endl;
		cout << "4. Afficher l'IP r�seau via une IP et un masque" << endl;
		cout << "5. Calculer le num�ro de machine via une IP et une IP r�seau" << endl;
		cout << "6. Calculer les bits de r�seau via un masque" << endl;
		cout << "7. Calculer l'adresse de la premi�re machine d'un r�seau" << endl;
		cout << "8. Calculer l'adresse de la derni�re machine d'un r�seau" << endl;
		cout << "9. Quitter" << endl;
		cout << "Votre choix : ";
		cin >> choix;
		cout << endl;

		switch (choix) {
		case 1:
			cout << ippointee() << endl;
			break;
		case 2:
			cout << getClasse() << endl;
			break;
		case 3:
			cout << masqueCIDR() << endl;
			break;
		case 4:
			cout << ipReseau() << endl;
			break;
		case 5:
			cout << numMachine() << endl;
			break;
		case 6:
			cout << "Masque : ";
			cin >> masque;
			cout << bitsDeReseau(masque) << endl;
			break;
		case 7:
			cout << ipPremiere() << endl;
			break;
		case 8:
			cout << ipDerniere() << endl;
			break;
		case 9:
			cout << "Au revoir !" << endl;
			exit(0);
		default:
			cout << "Choix invalide !" << endl;
			break;
		}
		cout << endl;
	}
	
    return 0;
}
