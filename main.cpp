#include <iostream>
#include <vector>
#include <string>
#include "adressage.h"

#define MSG_BIENVENUE "Bonjour, bienvenue dans l'application de calcul d'adresses IP"

using namespace std;

int main() {
	// Message de bienvenue
	cout << MSG_BIENVENUE << endl;
	
	// Demande � l'utilisateur une adresse IP et un masque CIDR
	string ip = ippointee();
	int cidr = 0;
	cout << "Saisir le masque CIDR : ";
	cin >> cidr;

	// Variable qui contiendra le masque r�seau
	string masque = masqueCIDR(cidr);

	// S�parateur
	cout << "----------------------------------------" << endl;
	
	// Affichage des r�sultats de chaque fonction (s�par�s et regroup�s selon la sp�cifit�)
	cout << "\n[SPECIFICITE : IP]" << endl;
	cout << "IP : " << ip << endl;
	cout << "Classe : " << getClasse(convertToInt(ip.substr(0, ip.find(".")))) << endl;

	cout << "\n[SPECIFICITE : RESEAU]" << endl;
	cout << "Masque R�seau : " << masque << endl;
	cout << "Bits de r�seau (CIDR) : " << bitsDeReseau(masque) << endl;
	cout << "IP r�seau : " << ipReseau(ip, masque) << endl;

	cout << "\n[SPECIFICITE : MACHINE]" << endl;
	cout << "Num�ro de machine : " << numMachine(ip, ipReseau(ip, masque)) << endl;
	cout << "Premi�re machine : " << ipPremiere(ip, masque) << endl;
	cout << "Derni�re machine : " << ipDerniere(ip, masque) << endl;
	cout << "IP broadcast : " << ipBroadcast(ip, masque) << endl;
	
    return 0;
}
