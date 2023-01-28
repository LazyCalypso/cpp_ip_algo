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
string classe(int first_ip_num);

// Masque réseau
string masqueCIDR();

// ET LOGIQUE
string ipReseau(string ip, string mask);

// Outils
int convertToInt(string v);
bool isInRange(int v);
int* decomposeIP(string ip);

#endif //IP_ALGO_IPPOINTEE_H
