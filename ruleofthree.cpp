#include "ruleofthree.h"
#include "studentas.h"
#include <iostream>
#include <vector>

using std::cout;
using std::endl;

void demonstruotiruleofthree() {
    cout << "\nRULE OF THREE DEMONSTRACIJA\n";

    // 1. Konstruktorius
    Studentas s1("Vardas1", "Pavarde1", { 7, 8, 9 }, 7);
    cout << "Originalus studentas (s1): " << s1 << endl;

    // 2. Kopijavimo konstruktorius
    Studentas s2 = s1;
    cout << "Po kopijavimo konstruktoriaus (s2 = s1): " << s2 << endl;

    // 3. Priskyrimo operatorius
    Studentas s3("Vardas2", "Pavarde2", { 5, 6, 7 }, 5);
    cout << "Pries priskyrima (s3): " << s3 << endl;

    s3 = s1;
    cout << "Po priskyrimo operatoriaus (s3 = s1): " << s3 << endl;

    // 4. Sav?s priskyrimas (edge case)
    s1 = s1;
    cout << "Po saves priskyrimo (s1 = s1): " << s1 << endl;
}