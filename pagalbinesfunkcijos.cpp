#include "pagalbinesfunkcijos.h"
#include <iostream>
#include <algorithm>
#include <cstdlib>

using std::cout;
using std::cin;
using std::endl;

Studentas ivesk(std::string vard, std::string pav) {
    std::vector<int> nd;
    int m;
    std::string ats;

    while (true) {
        cout << "Iveskite pazymi: ";
        cin >> m;
        if (!cin || m < 1 || m > 10) {
            cout << "Ivesta neteisingai. Bandykite dar karta." << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }
        nd.push_back(m);
        cout << "Ar norite ivesti dar viena pazymi? (taip/ne): ";
        cin >> ats;
        if (ats == "ne") break;
    }

    int egz;
    while (true) {
        cout << "Iveskite egzamina: ";
        cin >> egz;
        if (!cin || egz < 1 || egz > 10) {
            cout << "Ivesta neteisingai. Bandykite dar karta." << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }
        break;
    }

    Studentas s(vard, pav, nd, egz);
    return s;
}

double median(std::vector<int> v) { return Studentas::median(v); }

Studentas generuoti(std::string vard, std::string pav, int ndskaicius) {
    std::vector<int> nd;
    for (int i = 0; i < ndskaicius; i++)
        nd.push_back(rand() % 10 + 1);
    int egz = rand() % 10 + 1;

    Studentas s(vard, pav, nd, egz);
    return s;
}

Studentas generuotistudenta(int id, int ndskaicius) {
    std::vector<int> nd;
    for (int i = 0; i < ndskaicius; i++)
        nd.push_back(rand() % 10 + 1);
    int egz = rand() % 10 + 1;

    Studentas s("Vardas" + std::to_string(id),
        "Pavarde" + std::to_string(id),
        nd, egz);
    return s;
}
