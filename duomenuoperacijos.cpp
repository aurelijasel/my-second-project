#include "duomenuoperacijos.h"
#include "pagalbinesfunkcijos.h"
#include "laikas.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <vector>
#include <list>

using std::cout;
using std::endl;
using std::cin;

// --------------------- Nuskaitymas ---------------------
std::vector<Studentas> nuskaityti(std::string failas) {
    Laikmatis laikmatis_nuskaitymo;
    std::vector<Studentas> Grupe;
    std::ifstream fd(failas);
    if (!fd) {
        std::cout << "Nepavyko atidaryti failo: " << failas << std::endl;
        return Grupe;
    }
    std::string antraste;
    getline(fd, antraste);
    
    std::string eilute;
    while (getline(fd, eilute)) {
        std::istringstream ss(eilute);
        
        try {
            Studentas s(ss); // konstruktorius su istream jau kvie?ia readStudent()
            Grupe.push_back(s);
        }
        catch (const std::exception& e) {
            std::cerr << "Klaida skaitant studento eilut?: " << e.what() << std::endl;
            continue;
        }
    }
    std::cout << std::fixed << std::setprecision(6) << "Failo nuskaitymas uztruko: " << laikmatis_nuskaitymo.elapsed() << " s" << std::endl;
    return Grupe;
}

// --------------------- Failo generavimas ---------------------
void generuotitxt(const std::string& pavadinimas, int kiekis) {
    Laikmatis laikmatis_generavimo;
    std::ofstream fout(pavadinimas);
    if (!fout) {
        cout << "Nepavyko sukurti failo: " << pavadinimas << endl;
        return;
    }

    fout << "Vardas Pavarde ";
    for (int i = 1; i <= 5; i++) fout << "ND" << i << " ";
    fout << "Egzaminas\n";

    for (int i = 1; i <= kiekis; i++) {
        Studentas s = generuotistudenta(i, 5);
        fout << s.getVardas() << " " << s.getPavarde() << " ";
        for (int paz : s.getPazymiai()) fout << paz << " ";
        fout << s.getEgzaminas() << "\n";
    }

    fout.close();
    cout << "Failas " << pavadinimas << " sukurtas" << endl;
    cout << std::fixed << std::setprecision(6)
        << "Generavimas uztruko: " << laikmatis_generavimo.elapsed() << " s" << endl;
}

void suskirstyti(const std::vector<Studentas>& Grupe) {
    char pasirinkimas;
    while (true) {
        std::cout << "Pasirinkite pagal ka suskirstyti studentus:\n"
            << " a - pagal vidurki\n b - pagal mediana\n";
        std::cin >> pasirinkimas;
        if (pasirinkimas == 'a' || pasirinkimas == 'b') break;
        else std::cout << "Ivesta neteisingai. Bandykite dar karta." << std::endl;
    }

    std::vector<Studentas> vargsiukai;
    std::vector<Studentas> galvociai;

    for (auto& s : Grupe) {
        double galutinis = (pasirinkimas == 'a') ? s.getGalutinisVid() : s.getGalutinisMed();
        if (galutinis < 5.0) vargsiukai.push_back(s);
        else galvociai.push_back(s);
    }

    char rikiavimas_pasirinkimas;
    while (true) {
        std::cout << "Pagal ka rikiuoti studentus faile?\n"
            << " a - pagal pavarde\n b - pagal varda\n c - pagal galutini pazymi\n";
        std::cin >> rikiavimas_pasirinkimas;
        if (rikiavimas_pasirinkimas == 'a' || rikiavimas_pasirinkimas == 'b' || rikiavimas_pasirinkimas == 'c') break;
        else std::cout << "Ivesta neteisingai. Bandykite dar karta." << std::endl;
    }

    auto rikiavimas = [&](const Studentas& a, const Studentas& b) {
        if (rikiavimas_pasirinkimas == 'a') return a.getPavarde() < b.getPavarde();
        if (rikiavimas_pasirinkimas == 'b') return a.getVardas() < b.getVardas();
        double galA = (pasirinkimas == 'a') ? a.getGalutinisVid() : a.getGalutinisMed();
        double galB = (pasirinkimas == 'a') ? b.getGalutinisVid() : b.getGalutinisMed();
        return galA < galB;
        };

    std::sort(vargsiukai.begin(), vargsiukai.end(), rikiavimas);
    std::sort(galvociai.begin(), galvociai.end(), rikiavimas);

    rusiavimas_i_failus(vargsiukai, galvociai, pasirinkimas, "vargsiukai_vector_strat1.txt", "galvociai_vector_strat1.txt");
}

void suskirstyti(const std::list<Studentas>& Grupe) {
    char pasirinkimas;
    while (true) {
        std::cout << "Pasirinkite pagal ka suskirstyti studentus:\n"
            << " a - pagal vidurki\n b - pagal mediana\n";
        std::cin >> pasirinkimas;
        if (pasirinkimas == 'a' || pasirinkimas == 'b') break;
        else std::cout << "Ivesta neteisingai. Bandykite dar karta." << std::endl;
    }

    std::list<Studentas> vargsiukai, galvociai;
    for (auto& s : Grupe) {
        double galutinis = (pasirinkimas == 'a') ? s.getGalutinisVid() : s.getGalutinisMed();
        if (galutinis < 5.0) vargsiukai.push_back(s);
        else galvociai.push_back(s);
    }

    char rikiavimas_pasirinkimas;
    while (true) {
        std::cout << "Pagal ka rikiuoti studentus faile?\n"
            << " a - pagal pavarde\n b - pagal varda\n c - pagal galutini pazymi\n";
        std::cin >> rikiavimas_pasirinkimas;
        if (rikiavimas_pasirinkimas == 'a' || rikiavimas_pasirinkimas == 'b' || rikiavimas_pasirinkimas == 'c') break;
        else std::cout << "Ivesta neteisingai. Bandykite dar karta." << std::endl;
    }

    auto rikiavimas = [&](const Studentas& a, const Studentas& b) {
        if (rikiavimas_pasirinkimas == 'a') return a.getPavarde() < b.getPavarde();
        if (rikiavimas_pasirinkimas == 'b') return a.getVardas() < b.getVardas();
        double galA = (pasirinkimas == 'a') ? a.getGalutinisVid() : a.getGalutinisMed();
        double galB = (pasirinkimas == 'a') ? b.getGalutinisVid() : b.getGalutinisMed();
        return galA < galB;
        };

    vargsiukai.sort(rikiavimas);
    galvociai.sort(rikiavimas);

    rusiavimas_i_failus(vargsiukai, galvociai, pasirinkimas, "vargsiukai_list_strat1.txt", "galvociai_list_strat1.txt");
}


// --------------------- Pagal strategijas suskirstyti - Vector ---------------------
void suskirstyti(std::vector<Studentas>& grupe, char pagalkaskirstyti, char pagalkarikiuoti, int strategija);

// --------------------- Pagal strategijas suskirstyti - List ---------------------
void suskirstyti(std::list<Studentas>& grupe, char pagalkaskirstyti, char pagalkarikiuoti, int strategija);

// --------------------- Pagalba rusiavimui ---------------------

// --------------------- Vector suskirstyti strategija 1 ---------------------
void suskirstyti(std::vector<Studentas>& grupe, char pagalkaskirstyti, char pagalkarikiuoti) {
    std::vector<Studentas> vargsiukai, galvociai;

    auto gauti_galutini = [&](const Studentas& s) {
        return (pagalkaskirstyti == 'a') ? s.getGalutinisVid() : s.getGalutinisMed();
        };

    for (auto& s : grupe) {
        if (gauti_galutini(s) < 5.0) vargsiukai.push_back(s);
        else galvociai.push_back(s);
    }

    auto rikiavimas = [&](const Studentas& a, const Studentas& b) {
        if (pagalkarikiuoti == 'a') return a.getPavarde() < b.getPavarde();
        if (pagalkarikiuoti == 'b') return a.getVardas() < b.getVardas();
        return gauti_galutini(a) < gauti_galutini(b);
        };

    std::sort(vargsiukai.begin(), vargsiukai.end(), rikiavimas);
    std::sort(galvociai.begin(), galvociai.end(), rikiavimas);

    rusiavimas_i_failus(vargsiukai, galvociai, pagalkaskirstyti, "vargsiukai_vector_strat1.txt", "galvociai_vector_strat1.txt");
}

// --------------------- List suskirstyti strategija 1 ---------------------
void suskirstyti(std::list<Studentas>& grupe, char pagalkaskirstyti, char pagalkarikiuoti) {
    std::list<Studentas> vargsiukai, galvociai;

    auto gauti_galutini = [&](const Studentas& s) {
        return (pagalkaskirstyti == 'a') ? s.getGalutinisVid() : s.getGalutinisMed();
        };

    for (auto& s : grupe) {
        if (gauti_galutini(s) < 5.0) vargsiukai.push_back(s);
        else galvociai.push_back(s);
    }

    auto rikiavimas = [&](const Studentas& a, const Studentas& b) {
        if (pagalkarikiuoti == 'a') return a.getPavarde() < b.getPavarde();
        if (pagalkarikiuoti == 'b') return a.getVardas() < b.getVardas();
        return gauti_galutini(a) < gauti_galutini(b);
        };

    vargsiukai.sort(rikiavimas);
    galvociai.sort(rikiavimas);

    rusiavimas_i_failus(vargsiukai, galvociai, pagalkaskirstyti, "vargsiukai_list_strat1.txt", "galvociai_list_strat1.txt");
}

// --------------------- Strategija 2 Vector ---------------------
void suskirstyti(std::vector<Studentas>& grupe, char pagalkaskirstyti, char pagalkarikiuoti, int strategija) {
    if (strategija == 1) {
        suskirstyti(grupe, pagalkaskirstyti, pagalkarikiuoti);
        return;
    }

    std::vector<Studentas> vargsiukai;
    for (auto it = grupe.begin(); it != grupe.end();) {
        double galutinis = (pagalkaskirstyti == 'a') ? it->getGalutinisVid() : it->getGalutinisMed();
        if (galutinis < 5.0) {
            vargsiukai.push_back(*it);
            it = grupe.erase(it);
        }
        else ++it;
    }

    auto rikiavimas = [&](const Studentas& a, const Studentas& b) {
        if (pagalkarikiuoti == 'a') return a.getPavarde() < b.getPavarde();
        if (pagalkarikiuoti == 'b') return a.getVardas() < b.getVardas();
        double galA = (pagalkaskirstyti == 'a') ? a.getGalutinisVid() : a.getGalutinisMed();
        double galB = (pagalkaskirstyti == 'a') ? b.getGalutinisVid() : b.getGalutinisMed();
        return galA < galB;
        };

    std::sort(vargsiukai.begin(), vargsiukai.end(), rikiavimas);
    std::sort(grupe.begin(), grupe.end(), rikiavimas);

    rusiavimas_i_failus(vargsiukai, grupe, pagalkaskirstyti, "vargsiukai_vector_strat2.txt", "galvociai_vector_strat2.txt");
}

// --------------------- Strategija 2 List ---------------------
void suskirstyti(std::list<Studentas>& grupe, char pagalkaskirstyti, char pagalkarikiuoti, int strategija) {
    if (strategija == 1) {
        suskirstyti(grupe, pagalkaskirstyti, pagalkarikiuoti);
        return;
    }

    std::list<Studentas> vargsiukai;
    for (auto it = grupe.begin(); it != grupe.end();) {
        double galutinis = (pagalkaskirstyti == 'a') ? it->getGalutinisVid() : it->getGalutinisMed();
        if (galutinis < 5.0) {
            vargsiukai.push_back(*it);
            it = grupe.erase(it);
        }
        else ++it;
    }

    auto rikiavimas = [&](const Studentas& a, const Studentas& b) {
        if (pagalkarikiuoti == 'a') return a.getPavarde() < b.getPavarde();
        if (pagalkarikiuoti == 'b') return a.getVardas() < b.getVardas();
        double galA = (pagalkaskirstyti == 'a') ? a.getGalutinisVid() : a.getGalutinisMed();
        double galB = (pagalkaskirstyti == 'a') ? b.getGalutinisVid() : b.getGalutinisMed();
        return galA < galB;
        };

    vargsiukai.sort(rikiavimas);
    grupe.sort(rikiavimas);

    rusiavimas_i_failus(vargsiukai, grupe, pagalkaskirstyti, "vargsiukai_list_strat2.txt", "galvociai_list_strat2.txt");
}

// --- Vector versija (lygina STL variantus) ---
void suskirstyti_optimizuota(std::vector<Studentas>& grupe, char pagalkaskirstyti, char pagalkarikiuoti) {
    auto kopija1 = grupe;
    auto kopija2 = grupe;

    Laikmatis t1;
    suskirstyti_optimizuota_pirma(kopija1, pagalkaskirstyti, pagalkarikiuoti); // STL: remove_copy_if
    double laikas1 = t1.elapsed();

    Laikmatis t2;
    suskirstyti_stl_antros_logika(kopija2, pagalkaskirstyti, pagalkarikiuoti); // STL: partition
    double laikas2 = t2.elapsed();

    if (laikas1 <= laikas2)
        suskirstyti_optimizuota_pirma(grupe, pagalkaskirstyti, pagalkarikiuoti);
    else
        suskirstyti_stl_antros_logika(grupe, pagalkaskirstyti, pagalkarikiuoti);
}

// --- List versija (lygina be STL) ---
void suskirstyti_optimizuota(std::list<Studentas>& grupe, char pagalkaskirstyti, char pagalkarikiuoti) {
    auto kopija1 = grupe;
    auto kopija2 = grupe;

    Laikmatis t1;
    suskirstyti(kopija1, pagalkaskirstyti, pagalkarikiuoti, 1); // klasikin? (be STL)
    double laikas1 = t1.elapsed();

    Laikmatis t2;
    suskirstyti(kopija2, pagalkaskirstyti, pagalkarikiuoti, 2); // erase versija
    double laikas2 = t2.elapsed();

    if (laikas1 <= laikas2)
        suskirstyti(grupe, pagalkaskirstyti, pagalkarikiuoti, 1);
    else
        suskirstyti(grupe, pagalkaskirstyti, pagalkarikiuoti, 2);
}

// --------------------- Strategija 3 - pirma logika (vector) ---------------------
void suskirstyti_optimizuota_pirma(std::vector<Studentas>& grupe, char pagalkaskirstyti, char pagalkarikiuoti) {
    auto gauti_galutini = [&](const Studentas& s) {
        return (pagalkaskirstyti == 'a') ? s.getGalutinisVid() : s.getGalutinisMed();
        };
    auto yra_vargsiukas = [&](const Studentas& s) { return gauti_galutini(s) < 5.0; };

    std::vector<Studentas> vargsiukai;
    std::remove_copy_if(grupe.begin(), grupe.end(), std::back_inserter(vargsiukai),
        [&](const Studentas& s) { return !yra_vargsiukas(s); });

    std::vector<Studentas> galvociai;
    std::remove_copy_if(grupe.begin(), grupe.end(), std::back_inserter(galvociai),
        [&](const Studentas& s) { return yra_vargsiukas(s); });

    auto rikiavimas = [&](const Studentas& a, const Studentas& b) {
        if (pagalkarikiuoti == 'a') return a.getPavarde() < b.getPavarde();
        if (pagalkarikiuoti == 'b') return a.getVardas() < b.getVardas();
        return gauti_galutini(a) < gauti_galutini(b);
        };

    std::sort(vargsiukai.begin(), vargsiukai.end(), rikiavimas);
    std::sort(galvociai.begin(), galvociai.end(), rikiavimas);

    rusiavimas_i_failus(vargsiukai, galvociai, pagalkaskirstyti, "vargsiukai_vector_strat3.txt", "galvociai_vector_strat3.txt");
}

// --------------------- Strategija 3 - antra logika (vector) ---------------------
void suskirstyti_stl_antros_logika(std::vector<Studentas>& grupe, char pagalkaskirstyti, char pagalkarikiuoti) {
    auto gauti_galutini = [&](const Studentas& s) {
        return (pagalkaskirstyti == 'a') ? s.getGalutinisVid() : s.getGalutinisMed();
        };
    auto yra_vargsiukas = [&](const Studentas& s) { return gauti_galutini(s) < 5.0; };

    auto partition_point = std::partition(grupe.begin(), grupe.end(), yra_vargsiukas);

    std::vector<Studentas> vargsiukai(grupe.begin(), partition_point);
    std::vector<Studentas> galvociai(partition_point, grupe.end());

    auto rikiavimas = [&](const Studentas& a, const Studentas& b) {
        if (pagalkarikiuoti == 'a') return a.getPavarde() < b.getPavarde();
        if (pagalkarikiuoti == 'b') return a.getVardas() < b.getVardas();
        return gauti_galutini(a) < gauti_galutini(b);
        };

    std::sort(vargsiukai.begin(), vargsiukai.end(), rikiavimas);
    std::sort(galvociai.begin(), galvociai.end(), rikiavimas);

    rusiavimas_i_failus(vargsiukai, galvociai, pagalkaskirstyti, "vargsiukai_vector_strat3.txt", "galvociai_vector_strat3.txt");
}
