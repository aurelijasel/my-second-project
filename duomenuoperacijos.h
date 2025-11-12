#ifndef DUOMENUOPERACIJOS_H
#define DUOMENUOPERACIJOS_H

#include "studentas.h"
#include <string>
#include <vector>
#include <list>
#include <iomanip>

std::vector<Studentas> nuskaityti(std::string failas);
void generuotitxt(const std::string& pavadinimas, int kiekis);
void suskirstyti(const std::vector<Studentas>& Grupe);
void suskirstyti(const std::list<Studentas>& Grupe);
void suskirstyti(std::vector<Studentas>& grupe, char pagalkaskirstyti, char pagalkarikiuoti);
void suskirstyti(std::list<Studentas>& grupe, char pagalkaskirstyti, char pagalkarikiuoti);
void suskirstyti(std::vector<Studentas>& grupe, char pagalkaskirstyti, char pagalkarikiuoti, int strategija);
void suskirstyti(std::list<Studentas>& grupe, char pagalkaskirstyti, char pagalkarikiuoti, int strategija);
void suskirstyti_optimizuota(std::vector<Studentas>& grupe, char pagalkaskirstyti, char pagalkarikiuoti);
void suskirstyti_optimizuota(std::list<Studentas>& grupe, char pagalkaskirstyti, char pagalkarikiuoti);
void suskirstyti_optimizuota_pirma(std::vector<Studentas>& grupe, char pagalkaskirstyti, char pagalkarikiuoti);
void suskirstyti_stl_antros_logika(std::vector<Studentas>& grupe, char pagalkaskirstyti, char pagalkarikiuoti);

template <typename Container>
void rusiavimas_i_failus(const Container& vargsiukai, const Container& galvociai, char pagalkaskirstyti,
    const std::string& vardasFailoVargsiukai, const std::string& vardasFailoGalvociai) {

    if (vargsiukai.empty() && galvociai.empty()) {
        std::cout << "Nera studentu, failai nebus kuriami." << std::endl;
        return;
    }

    std::ofstream fv, fg;

    if (!vargsiukai.empty()) {
        fv.open(vardasFailoVargsiukai);
        if (!fv) { std::cout << "Nepavyko sukurti " << vardasFailoVargsiukai << std::endl; return; }
    }

    if (!galvociai.empty()) {
        fg.open(vardasFailoGalvociai);
        if (!fg) { std::cout << "Nepavyko sukurti " << vardasFailoGalvociai << std::endl; return; }
    }

    auto gauti_galutini = [&](const Studentas& s) {
        return (pagalkaskirstyti == 'a') ? s.getGalutinisVid() : s.getGalutinisMed();
        };

    for (auto& s : vargsiukai)
        fv << s.getPavarde() << " " << s.getVardas() << " Galutinis: "
        << std::fixed << std::setprecision(2) << gauti_galutini(s) << "\n";

    for (auto& s : galvociai)
        fg << s.getPavarde() << " " << s.getVardas() << " Galutinis: "
        << std::fixed << std::setprecision(2) << gauti_galutini(s) << "\n";
}

#endif
