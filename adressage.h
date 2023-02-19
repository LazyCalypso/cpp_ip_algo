//
// Created by enzbonolis@uimm-sn.fc on 27/01/23.
//
#include <iostream>
#include <string>
#include <bitset>
#include <typeinfo>

using namespace std;

#ifndef IP_ALGO_IPPOINTEE_H
#define IP_ALGO_IPPOINTEE_H

#define IP_NOT_IN_RANGE "Erreur : la valeur doit être comprise entre 0 et 255"

// Adresses IP
string ippointee();
string getClasse(int first_ip_num = 0);

// Masque réseau
string masqueCIDR(int cidr = 0);
string ipReseau(string ip = "", string masque = "");

// Adresses machines
string numMachine(string ip = "", string reseau = "");
string ipPremiere(string ip = "", string masque = "");
string ipDerniere(string ip = "", string masque = "");
string ipBroadcast(string ip = "", string masque = "");

// Outils
int convertToInt(const string& v);
string saisirValeur(const string& description);
bool isInRange(int v);
int* decomposeIP(string ip);
int bitsDeReseau(string masque = "");

#endif //IP_ALGO_IPPOINTEE_H
