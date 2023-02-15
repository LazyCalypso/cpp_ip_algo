#include <iostream>
#include <vector>
#include <string>
#include "adressage.h"

#define MSG_BIENVENUE "Bonjour, bienvenue dans l'application de calcul d'adresses IP"

using namespace std;

int main() {
	// Message de bienvenue
	cout << MSG_BIENVENUE << endl;
	
	// Demande à l'utilisateur une adresse IP et un masque CIDR
	string ip = ippointee();
	int cidr = 0;
	cout << "Saisir le masque CIDR : ";
	cin >> cidr;

	// Variable qui contiendra le masque réseau
	string masque = masqueCIDR(cidr);

	// Séparateur
	cout << "----------------------------------------" << endl;
	
	// Affichage des résultats de chaque fonction (séparés et regroupés selon la spécifité)
	cout << "\n[SPECIFICITE : IP]" << endl;
	cout << "IP : " << ip << endl;
	cout << "Classe : " << getClasse(convertToInt(ip.substr(0, ip.find(".")))) << endl;

	cout << "\n[SPECIFICITE : RESEAU]" << endl;
	cout << "Masque Réseau : " << masque << endl;
	cout << "Bits de réseau (CIDR) : " << bitsDeReseau(masque) << endl;
	cout << "IP réseau : " << ipReseau(ip, masque) << endl;

	cout << "\n[SPECIFICITE : MACHINE]" << endl;
	cout << "Numéro de machine : " << numMachine(ip, ipReseau(ip, masque)) << endl;
	cout << "Première machine : " << ipPremiere(ip, masque) << endl;
	cout << "Dernière machine : " << ipDerniere(ip, masque) << endl;
	cout << "IP broadcast : " << ipBroadcast(ip, masque) << endl;
	
    return 0;
}
