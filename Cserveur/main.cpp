#include <iostream>
#include "serveur.h"

using namespace std;

int main() {
    cout << "------------ Debut du programme ------------" << endl;

    Serveur *s = new Serveur(80);
    s->init();
    s->start();
    s->stop();
    delete s;

    cout << "------------ Fin du programme ------------" << endl;

    return 0;
}

