#include "adressage.h"

using namespace std;

// Conversion d'un string vers un int
int convertToInt(const string& v) {
    try {
        return stoi(v);
    } catch (exception& e) {
		cout << "Erreur lors de la conversion : type invalide. Attendait une valeur numérique, reçu : " << v << endl;
    }
    return -1;
}

// Conversion d'un tableau d'entiers vers un string
string convertArrayToString(int* array) {
	string resultStr = "";
	for (int i = 0; i < 4; i++) {
		resultStr += to_string(array[i]);
		if (i != 3) {
			resultStr += ".";
		}
	}
	return resultStr;
}

// Vérifie que la valeur est comprise entre 0 et 255
bool isInRange(int v) {
	return v >= 0 && v <= 255;
}

// Saisie de valeur
string saisirValeur(const string& description) {
	string v;
	cout << "Saisir la valeur de " << description << " : ";
	cin >> v;
	while (!isInRange(convertToInt(v))) {
		cout << IP_NOT_IN_RANGE << endl;
		cout << "Resaissez la valeur : ";
		cin >> v;
	}
	return v;
}

// Get Classe IP
string getClasse(int first_ip_num) {
	if (first_ip_num == 0) {
		cout << "Entrez la première valeur de l'adresse IP : ";
		cin >> first_ip_num;
	}
	
	if (first_ip_num >= 10 && first_ip_num <= 127) {
        return "A";
    } else if (first_ip_num >= 128 && first_ip_num <= 191) {
        return "B";
    } else if (first_ip_num >= 192) {
        return "C";
    } else {
        return "Classe inconnue";
    }
}

// IP Pointee
string ippointee() {
    string w, x, y, z;
    string delim = ".";
    cout << "L'adresse IP sera de la forme W.X.Y.Z" << endl;
    
	// Saisir chaque valeur de l'adresse IP
	w = saisirValeur("W");
	x = saisirValeur("X");
	y = saisirValeur("Y");
	z = saisirValeur("Z");

	return w + delim + x + delim + y + delim + z;
}

// Masque réseau via CIDR
string masqueCIDR(int cidr) {
    // Tableau contenant un masque par défaut nul, c'est-à-dire
	// que tous les bits sont à 0.
    bitset<8> ip[4] = { bitset<8>(0), bitset<8>(0), bitset<8>(0), bitset<8>(0) };
	
	// Si le CIDR n'est pas renseigné en paramètres, le demander
	if (cidr == 0) {
		cout << "Masque sous forme CIDR : /masque" << endl;
		cin >> cidr;
	}
    
	// Set les bits correspondants au CIDR à 1
	// NOTE : On commence par le bit de poids fort, donc on commence par le bit 7
	// et on descend jusqu'à 0 (de gauche à droite).
	for (int i = 0; i < cidr; i++) {
		ip[i / 8].set(static_cast<size_t>(7) - (i % 8));	// NOTE : static_cast<size_t> pour éviter le dépassement opérateur
	}

    // Création d'un tableau contenant une conversion en int
	int* ipInt = new int[4];
	for (int i = 0; i < 4; i++) {
		ipInt[i] = static_cast<int>(ip[i].to_ulong());
	}

	// Conversion du tableau en string
	return convertArrayToString(ipInt);
}

// Fonction pour décomposer le string de l'IP/Masque
int* decomposeIP(string ip) {
	// Délimiteur
	string delim = ".";
	
	/* Récupère la partie W, X, Y, Z, les stock dans un string
	puis supprime la partie correspondante du string */
	string w = ip.substr(0, ip.find(delim));
	ip.erase(0, ip.find(delim) + delim.length());
	string x = ip.substr(0, ip.find(delim));
	ip.erase(0, ip.find(delim) + delim.length());
	string y = ip.substr(0, ip.find(delim));
	ip.erase(0, ip.find(delim) + delim.length());
	string z = ip.substr(0, ip.find(delim));
	ip.erase(0, ip.find(delim) + delim.length());

	// Conversion en int
	int wInt = convertToInt(w);
	int xInt = convertToInt(x);
	int yInt = convertToInt(y);
	int zInt = convertToInt(z);

	// Création du tableau
	int* ipArray = new int[4];
	ipArray[0] = wInt;
	ipArray[1] = xInt;
	ipArray[2] = yInt;
	ipArray[3] = zInt;

	return ipArray;
}

// IP Réseau
string ipReseau(string ip, string masque) {
	// Si pas de paramètres, on appelle les fonctions
	if (ip == "") { ip = ippointee(); }
	if (masque == "") { masque = masqueCIDR(); }
	
	// Décomposition du string de l'IP via la fonction "decomposeIP"
	// qui retourne un tableau de int contenant les valeurs de W, X, Y, Z
	int* ipDecompose = decomposeIP(ip);
	
	// Décomposition du string du masque
	int* masqueDecompose = decomposeIP(masque);

	// Tableau contenant le résultat de l'opération ET logique
	int* result = new int[4];
	
	// Opération ET logique
	for (int i = 0; i < 4; i++) {
		result[i] = ipDecompose[i] & masqueDecompose[i];
	}

	// Transformation du résultat en string

	return convertArrayToString(result);
}

// Numéro de machine
/* EXEMPLES
* IP => 192.168.10.200/28
* N° MACHINE => 0.0.0.8
* -----------------------
* IP => 10.200.11.12/12
* N° MACHINE => 0.8.11.12
*/
string numMachine(string ip, string reseau) {
	if (ip == "") { ip = ippointee(); }
	if (reseau == "") { reseau = ipReseau(ip); }

	// Décomposition du string de l'IP
	int* ipDecomposee = decomposeIP(ip);
	
	// Décomposition du string du réseau
	int* reseauDecomposee = decomposeIP(reseau);

	// Tableau contenant le résultat de l'opération OU exclusif
	int* result = new int[4];

	// Opération OU exclusif
	for (int i = 0; i < 4; i++) {
		result[i] = ipDecomposee[i] ^ reseauDecomposee[i];
	}

	// Transformation du résultat en string
	return convertArrayToString(result);
}

// Bits de réseau (inverse de masqueCIDR)
/* EXEMPLES 
* MASQUE => 255.255.255.240
* BITS DE RESEAU (= CIDR) => 28
* -----------------------------
* MASQUE => 255.240.0.0
* BITS DE RESEAU (= CIDR) => 12
*/
int bitsDeReseau(string masque) {
	if (masque == "") { masque = masqueCIDR(); }

	// Décomposition du masque
	int* masqueDecompose = decomposeIP(masque);
	
	// Calcul du nombre de bits à 1
	int bits = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 8; j++) {
			if (masqueDecompose[i] & (1 << j)) {
				bits++;
			}
		}
	}
	
	return bits;
}

// Adresse première machine
/* EXEMPLES
* IP => 192.168.10.200/28
* PREMIERE MACHINE => 192.168.10.193
* ----------------------------------
* IP => 10.200.11.12/12
* PREMIERE MACHINE => 10.192.0.1
*/
string ipPremiere(string ip, string masque) {
	if (ip == "") { ip = ippointee(); }
	if (masque == "") { masque = masqueCIDR(); }

	// Calcul de l'IP réseau
	string reseau = ipReseau(ip, masque);

	// Décomposition du réseau
	int* reseauDecompose = decomposeIP(reseau);

	// Ajout de l'offset de la première machine (0.0.0.1)
	reseauDecompose[3] += 1;
	
	// Transformation du résultat en string
	return convertArrayToString(reseauDecompose);
}

// Adresse dernière machine
/* EXEMPLES
* IP => 192.168.10.200/28
* DERNIERE MACHINE => 192.168.10.206
* ----------------------------------
* IP => 10.200.11.12/12
* DERNIERE MACHINE => 10.207.255.254
*/
string ipDerniere(string ip, string masque) {
	if (ip == "") { ip = ippointee(); }
	if (masque == "") { masque = masqueCIDR(); }

	// Calcul de l'IP réseau
	string reseau = ipReseau(ip, masque);

	// Décomposition du réseau
	int* reseauDecompose = decomposeIP(reseau);

	// Calcul du nombre de bits de réseau
	int bits = bitsDeReseau(masque);
	int offset = pow(2, 32 - bits) - 2;

	// Ajout de l'offset de la dernière machine grâce au nombre de bits de réseau
	for (int i = 3; i >= 0; i--) {
		reseauDecompose[i] += offset;
		if (reseauDecompose[i] > 255) {
			offset = reseauDecompose[i] / 256;
			reseauDecompose[i] = reseauDecompose[i] % 256;
		}
		else {
			offset = 0;
		}
	}

	// Transformation du résultat en string
	return convertArrayToString(reseauDecompose);
}

// Adresse de diffusion
/* EXEMPLES
* IP => 192.168.10.200/28
* BROADCAST => 192.168.10.207
* ---------------------------
* IP => 10.200.11.12/12
* BROADCAST => 10.207.255.255
*/
string ipBroadcast(string ip, string masque) {
	if (ip == "") { ip = ippointee(); }
	if (masque == "") { masque = masqueCIDR(); }

	// Calcul de l'IP de la dernière machine
	string derniereMachine = ipDerniere(ip, masque);
	
	// Décomposition de l'IP
	int* derniereMachineDecompose = decomposeIP(derniereMachine);

	// Ajout de 1 au dernier octet
	derniereMachineDecompose[3]++;

	// Transformation du résultat en string
	return convertArrayToString(derniereMachineDecompose);
}