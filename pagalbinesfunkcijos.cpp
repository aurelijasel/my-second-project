#include "pagalbinesfunkcijos.h"
#include <iostream>
#include <algorithm>
#include <cstdlib>

using std::cout;
using std::cin;
using std::endl;

Studentas ivesk(std::string vard, std::string pav) {
    Studentas Laik;
    Laik.setVardas(vard);
    Laik.setPavarde(pav);
    int m;
    std::string ats;
    while (true) {
        while (true) {
            cout << "Iveskite pazymi: "; cin >> m;
            if (!cin || m < 1 || m > 10) {
                cout << "Ivesta neteisingai. Bandykite dar karta." << endl;
                cin.clear();
                cin.ignore(1000, '\n');
                continue;
            }
            break;
        }
        Laik.pridetiPazymi(m);
        cout << "Ar norite ivesti dar viena pazymi? (taip/ne): "; cin >> ats;
        if (ats == "ne") break;
    }
    while (true) {
        cout << "Iveskite egzamina: "; cin >> m;
        if (!cin || m < 1 || m > 10) {
            cout << "Ivesta neteisingai. Bandykite dar karta." << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }
        break;
    }
    Laik.setEgzaminas(m);
    Laik.skaiciuokVidurkiMediana(); // <-- prid?ta
    return Laik;
}

double median(std::vector<int> v) { return Studentas::median(v); }

Studentas generuoti(std::string vard, std::string pav, int ndskaicius) {
    Studentas s(vard, pav);
    for (int i = 0; i < ndskaicius; i++)
        s.pridetiPazymi(rand() % 10 + 1);
    s.setEgzaminas(rand() % 10 + 1);
    s.skaiciuokVidurkiMediana(); // <-- prid?ta
    return s;
}

Studentas generuotistudenta(int id, int ndskaicius) {
    Studentas s("Vardas" + std::to_string(id), "Pavarde" + std::to_string(id));
    for (int i = 0; i < ndskaicius; i++)
        s.pridetiPazymi(rand() % 10 + 1);
    s.setEgzaminas(rand() % 10 + 1);
    s.skaiciuokVidurkiMediana(); // <-- prid?ta
    return s;
}
