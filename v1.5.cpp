#include "studentas.h"
#include "pagalbinesfunkcijos.h"
#include "duomenuoperacijos.h"
#include "laikas.h"
#include "ruleofthree.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>
#include <utility>
#include <list>
#include <chrono>

using std::cout;
using std::cin;
using std::endl;
using std::setw;
using std::left;

int main() {
    srand(time(0));
    std::string veiksmas;
    std::cout << "Pasirinkite rezima:\n"
        << "1 - Iprastas programos veikimas\n"
        << "2 - Automatinis testavimas (vector vs list)\n"
        << "3 - Rule of three demonstracija\n"
        << "4 - Abstrakcios klases Zmogus demonstracija\n";
    std::cin >> veiksmas;

    if (veiksmas == "3") {
        demonstruotiruleofthree();
        return 0;
    }
    else if (veiksmas == "4") {
        std::cout << "\nBandoma sukurti Zmogus objekta...\n";

        // Ši eilutė turėtų sugeneruoti klaidą kompiliuojant, nes Zmogus yra abstrakti
        // Zmogus z; // <-- PAKOMENTUOTA, nes kompiliavimo metu duos klaidą

        std::cout << "Negalima sukurti abstrakcios klases Zmogus objektu." << std::endl;
        std::cout << "Bandymas atkomentuoti 'Zmogus z;' duos kompiliavimo klaida." << std::endl;

        return 0;
    }

    if (veiksmas == "2") {
        std::vector<std::string> test_failai = {
            //"studentai1000.txt",
            //"studentai10000.txt",
            "studentai100000.txt",
            "studentai1000000.txt",
            //"studentai10000000.txt"
        };

        std::ofstream fout("testavimorezultatai.txt");
        if (!fout) {
            cout << "Nepavyko sukurti testavimorezultatai.txt" << endl;
            return 1;
        }

        char pagalkaskirstyti, pagalkarikiuoti;
        int strategija;
        cout << "Pasirinkite pagal ka suskirstyti studentus:\n"
            << "a - pagal vidurki\n"
            << "b - pagal mediana\n";
        cin >> pagalkaskirstyti;

        cout << "\nPagal ka rikiuoti studentus faile?\n"
            << "a - pagal pavarde\n"
            << "b - pagal varda\n"
            << "c - pagal galutini pazymi\n";
        cin >> pagalkarikiuoti;

        cout << "\nPasirinkite strategija:\n"
            << "1 - Du nauji konteineriai (vargsiukams ir galvociams)\n"
            << "2 - Vienas naujas konteineris (vargsiukai traukiami ir trinami is bendro)\n"
            << "3 - Optimizuota (naudojami darbo su konteineriais algoritmai)\n";
        cin >> strategija;

        fout << "Naudota STRATEGIJA " << strategija << "\n";
        fout << left << setw(13) << "Konteineris" << setw(23) << "Failas"
            << setw(18) << "Nuskaitymas (s)" << setw(14) << "Irasymas (s)"
            << setw(13) << "Bendras (s)" << setw(15) << "Atmintis (B)" << "\n";
        fout << std::string(93, '-') << "\n";

        for (auto& failopavadinimas : test_failai) {
            cout << "\nTestuojamas failas: " << failopavadinimas << endl;

            // ----- Vector testas -----
            {
                Laikmatis bendra, t1;
                std::vector<Studentas> grupe = nuskaityti(failopavadinimas);
                double t_nuskaitymas = t1.elapsed();

                t1.reset();
                Laikmatis t_irasyti_timer;

                if (strategija == 3)
                    suskirstyti_optimizuota(grupe, pagalkaskirstyti, pagalkarikiuoti);
                else
                    suskirstyti(grupe, pagalkaskirstyti, pagalkarikiuoti, strategija);

                double t_irasyti = t_irasyti_timer.elapsed();
                double t_bendras = bendra.elapsed();

                size_t atminties_vector = sizeof(grupe) + grupe.capacity() * sizeof(Studentas);
                cout << "Vector (strategija " << strategija
                    << ") atminties uzimtis: " << atminties_vector << " baitai" << endl;

                fout << left << setw(13) << "vector" << setw(23) << failopavadinimas
                    << setw(18) << std::fixed << std::setprecision(6) << t_nuskaitymas
                    << setw(14) << t_irasyti << setw(13) << t_bendras
                    << setw(15) << atminties_vector << "\n";
            }

            // ----- List testas -----
            {
                Laikmatis bendra, t1;
                std::vector<Studentas> laikini = nuskaityti(failopavadinimas);
                std::list<Studentas> grupe(laikini.begin(), laikini.end());
                double t_nuskaitymas = t1.elapsed();

                t1.reset();
                Laikmatis t_irasyti_timer;

                if (strategija == 3)
                    suskirstyti_optimizuota(grupe, pagalkaskirstyti, pagalkarikiuoti);
                else
                    suskirstyti(grupe, pagalkaskirstyti, pagalkarikiuoti, strategija);

                double t_irasyti = t_irasyti_timer.elapsed();
                double t_bendras = bendra.elapsed();

                size_t atminties_list = sizeof(grupe); // pats list objektas
                for (auto& s : grupe) {
                    atminties_list += sizeof(Studentas) + 2 * sizeof(void*); // node
                    atminties_list += s.getPazymiai().capacity() * sizeof(double); // vector viduje
                }
                cout << "List (strategija " << strategija
                    << ") atminties uzimtis: " << atminties_list << " baitai" << endl;

                fout << left << setw(13) << "list" << setw(23) << failopavadinimas
                    << setw(18) << std::fixed << std::setprecision(6) << t_nuskaitymas
                    << setw(14) << t_irasyti << setw(13) << t_bendras
                    << setw(15) << atminties_list << "\n";
            }
        }
        fout.close();
        return 0;
    }

    // ----- Iprastas veikimas -----
    std::string konteineriotipas;
    bool naudotivector = true;
    while (true) {
        cout << "Pasirinkite konteinerio tipa (vector/list): ";
        cin >> konteineriotipas;
        if (konteineriotipas == "vector") { naudotivector = true; break; }
        else if (konteineriotipas == "list") { naudotivector = false; break; }
        else cout << "Neteisingas pasirinkimas. Bandykite dar karta.\n";
    }

    std::vector<Studentas> GrupeVector;
    std::list<Studentas> GrupeList;
    std::string pasirinkimas2;
    char pasirinkimas;

    std::ofstream fout("rezultatai.txt");
    if (!fout) {
        cout << "Nepavyko sukurti rezultatu failo" << endl;
        return 1;
    }

    while (true) {
        cout << "Ar norite duomenis ivesti ranka, generuoti ar nuskaityti is failo? (ranka/generuoti/failas): ";
        cin >> pasirinkimas2;
        if (pasirinkimas2 == "ranka" || pasirinkimas2 == "generuoti" || pasirinkimas2 == "failas") break;
        else cout << "Ivesta neteisingai. Bandykite dar karta." << endl;
    }

    if (pasirinkimas2 == "failas") {
        std::string failopavadinimas;
        cout << "Iveskite failo pavadinima: ";
        cin >> failopavadinimas;

        if (naudotivector)
            GrupeVector = nuskaityti(failopavadinimas);
        else {
            auto laikinas = nuskaityti(failopavadinimas);
            GrupeList.assign(laikinas.begin(), laikinas.end());
        }
    }

    else {
        int kiekis;
        cout << "Kiek studentu norite prideti? ";
        cin >> kiekis;

        for (int j = 0; j < kiekis; j++) {
            std::string vard, pav;
            cout << "Iveskite pavarde: "; cin >> pav;
            cout << "Iveskite varda: "; cin >> vard;

            if (pasirinkimas2 == "ranka") {
                if (naudotivector) GrupeVector.push_back(ivesk(vard, pav));
                else GrupeList.push_back(ivesk(vard, pav));
            }
            else if (pasirinkimas2 == "generuoti") {
                int ndskaicius = 5;
                if (naudotivector) GrupeVector.push_back(generuoti(vard, pav, ndskaicius));
                else GrupeList.push_back(generuoti(vard, pav, ndskaicius));
            }
        }
    }

    while (true) {
        cout << "Pasirinkite koki galutini pazymi rodyti:\n"
            << "a - tik vidurki\n"
            << "b - tik mediana\n"
            << "c - vidurki ir mediana\n";
        cin >> pasirinkimas;
        if (pasirinkimas == 'a' || pasirinkimas == 'b' || pasirinkimas == 'c') break;
        else cout << "Ivesta neteisingai. Bandykite dar karta." << endl;
    }

    Laikmatis laikmatis_rezultatu_rasymo;
    fout << setw(15) << left << "Pavarde" << setw(15) << left << "Vardas";

    if (pasirinkimas == 'a') {
        fout << setw(15) << left << "Galutinis (Vid.)" << endl;
        fout << "------------------------------------------------------" << endl;
        if (naudotivector)
            for (auto& s : GrupeVector)
                fout << setw(15) << s.getPavarde() << setw(15) << s.getVardas()
                << setw(15) << std::fixed << std::setprecision(2) << s.getGalutinisVid() << endl;
        else
            for (auto& s : GrupeList)
                fout << setw(15) << s.getPavarde() << setw(15) << s.getVardas()
                << setw(15) << std::fixed << std::setprecision(2) << s.getGalutinisVid() << endl;
    }
    else if (pasirinkimas == 'b') {
        fout << setw(15) << left << "Galutinis (Med.)" << endl;
        fout << "------------------------------------------------------" << endl;
        if (naudotivector)
            for (auto& s : GrupeVector)
                fout << setw(15) << s.getPavarde() << setw(15) << s.getVardas()
                << setw(15) << std::fixed << std::setprecision(2) << s.getGalutinisMed() << endl;
        else
            for (auto& s : GrupeList)
                fout << setw(15) << s.getPavarde() << setw(15) << s.getVardas()
                << setw(15) << std::fixed << std::setprecision(2) << s.getGalutinisMed() << endl;
    }
    else {
        fout << setw(20) << left << "Galutinis (Vid.)" << setw(15) << left << "Galutinis (Med.)" << endl;
        fout << "----------------------------------------------------------------" << endl;
        if (naudotivector)
            for (auto& s : GrupeVector)
                fout << setw(15) << s.getPavarde() << setw(15) << s.getVardas()
                << setw(20) << std::fixed << std::setprecision(2) << s.getGalutinisVid()
                << setw(15) << std::fixed << std::setprecision(2) << s.getGalutinisMed() << endl;
        else
            for (auto& s : GrupeList)
                fout << setw(15) << s.getPavarde() << setw(15) << s.getVardas()
                << setw(20) << std::fixed << std::setprecision(2) << s.getGalutinisVid()
                << setw(15) << std::fixed << std::setprecision(2) << s.getGalutinisMed() << endl;
    }

    cout << "Irasymas i rezultatu faila truko: "
        << std::fixed << std::setprecision(6) << laikmatis_rezultatu_rasymo.elapsed() << " s" << endl;

    if (naudotivector) suskirstyti(GrupeVector);
    else suskirstyti(GrupeList);
}
