#include "ruleofthree.h"
#include "studentas.h"
#include <iostream>
#include <vector>
#include <limits>

using std::cout;
using std::endl;
using std::cin;

void demonstruotiruleofthree() {
    cout << "\nRULE OF THREE DEMONSTRACIJA\n";

    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // 1. Vartotojo įvestas studentas
    Studentas s1;
    cout << "Iveskite studento duomenis (vardas, pavarde, pazymiai ir egzaminas):\n";
    cin >> s1;
    cout << "Originalus studentas (s1): " << s1 << endl;

    // 2. Kopijavimo konstruktorius
    Studentas s2 = s1;
    cout << "Po kopijavimo konstruktoriaus (s2 = s1): " << s2 << endl;

    // 3. Priskyrimo operatorius
    Studentas s3;
    cout << "Iveskite kita studenta (s3), kuris bus perrasytas s1 duomenimis:\n";
    cin >> s3;
    cout << "Pries priskyrima(s3): " << s3 << endl;

    s3 = s1;
    cout << "Po priskyrimo operatoriaus (s3 = s1): " << s3 << endl;

    // 4. Savęs priskyrimas
    s1 = s1;
    cout << "Po saves priskyrimo (s1 = s1): " << s1 << endl;
}

