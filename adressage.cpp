#include "adressage.h"

using namespace std;

int convertToInt(string v) {
    try {
        return stoi(v);
    } catch (exception& e) {
		cout << "Erreur lors de la conversion : type invalide. Attendait une valeur numérique, reçu : " << v << endl;
    }
    return 1;
}

bool isInRange(int v) {
    if (v >= 0 && v <= 255) { return true; } else { return false; }
}

string getClasse(int first_ip_num) {
    if (first_ip_num >= 10 && first_ip_num <= 127) {
        return "La classe est A";
    } else if (first_ip_num >= 128 && first_ip_num <= 191) {
        return "La classe est B";
    } else if (first_ip_num >= 192) {
        return "La classe est C";
    } else {
        return "Classe inconnue";
    }
}

string ippointee() {
    string w, x, y, z;
    string delim = ".";
    cout << "L'adresse IP sera de la forme W.X.Y.Z" << endl;
    cout << "Saisir la valeur de W : ";
    cin >> w;
    if (!isInRange(convertToInt(w))) {
        cout << IP_NOT_IN_RANGE << endl;
		ippointee();
    }
    cout << endl;
    cout << "Saisir la valeur de X : ";
    cin >> x;
    if (!isInRange(convertToInt(x))) {
        cout << IP_NOT_IN_RANGE << endl;
		ippointee();
    }
    cout << endl;
    cout << "Saisir la valeur de Y : ";
    cin >> y;
    if (!isInRange(convertToInt(y))) {
        cout << IP_NOT_IN_RANGE << endl;
		ippointee();
    }
    cout << endl;
    cout << "Saisir la valeur de Z : ";
    cin >> z;
    if (!isInRange(convertToInt(z))) {
        cout << IP_NOT_IN_RANGE << endl;
		ippointee();
    }
    cout << endl;

	return w + delim + x + delim + y + delim + z;
}

string masqueCIDR() {
    cout << "Masque sous forme CIDR : /masque" << endl;
    
    // Tableau contenant un masque par défaut nul, c'est-à-dire
	// que tous les bits sont à 0.
    bitset<8> ip[4] = { bitset<8>(0), bitset<8>(0), bitset<8>(0), bitset<8>(0) };
	
	// Notation CIDR
    int cidr;
	cout << "Saisir la notation CIDR : ";
	cin >> cidr;
    
	// Set les bits correspondants au CIDR à 1
	// NOTE : On commence par le bit de poids fort, donc on commence par le bit 7
	// et on descend jusqu'à 0 (de gauche à droite).
	for (int i = 0; i < cidr; i++) {
		ip[i / 8].set(static_cast<size_t>(7) - (i % 8));	// NOTE : static_cast<size_t> pour éviter le dépassement opérateur
	}

	// Transformation du masque en string (mais toujours en binaire)
	// afin de vérifier que le masque est bien correct.
	string maskStr = "";
	for (int i = 0; i < 4; i++) {
		maskStr += ip[i].to_string();
		if (i != 3) {
			maskStr += ".";
		}
	}

    // Transformation du masque en IP lisible (en décimal)
	string mask = "";
	for (int i = 0; i < 4; i++) {
		mask += to_string(ip[i].to_ulong());
		if (i != 3) {
			mask += ".";
		}
	}

    return mask;
}

/* Fonction pour décomposer le string de l'IP/Masque
	Ex: ippointee retourne "192.168.10.200"
	Décomposition en 4 parties : "192", "168", "10", "200"
	Conversion en int
	Retourne un tableau
*/
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

string ipReseau(string ip, string mask) {
	// SI PAS DE PARAMETRES, ALORS ON APPELLE LES FONCTIONS
	// SINON, ON UTILISE LES PARAMETRES
	if (ip == "") { ip = ippointee(); }
	if (mask == "") { mask = masqueCIDR(); }
	
	// Décomposition du string de l'IP via la fonction "decomposeIP"
	// qui retourne un pointeur vers un tableau de int
	int* ipDecompose = decomposeIP(ip);
	
	// Décomposition du string du masque
	int* maskDecompose = decomposeIP(mask);

	// Tableau contenant le résultat de l'opération ET logique
	int* result = new int[4];
	
	// Opération ET logique
	for (int i = 0; i < 4; i++) {
		result[i] = ipDecompose[i] & maskDecompose[i];
	}

	// Transformation du résultat en string
	string resultStr = "";
	for (int i = 0; i < 4; i++) {
		resultStr += to_string(result[i]);
		if (i != 3) {
			resultStr += ".";
		}
	}

	return resultStr;
}