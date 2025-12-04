#ifndef STUDENTAS_H
#define STUDENTAS_H

#include "zmogus.h"
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

/**
 * @class Studentas
 * @brief Klase, aprasanti studento duomenis ir skaiciavimus.
 *
 * Paveldi @c Zmogus klase ir papildomai saugo:
 * - namu darbu pazymius,
 * - egzamino ivertinima,
 * - galutini bala pagal vidurki,
 * - galutini bala pagal mediana.
 */
class Studentas : public Zmogus {
private:
    std::vector<int> nd_;      /**< Studentu namu darbu pazymiai */
    int egzaminas_;            /**< Egzamino pazymys */
    float vidurkis_;           /**< Galutinis balas pagal vidurki */
    float mediana_;            /**< Galutinis balas pagal mediana */

public:

    // --- KONSTRUKTORIAI ---

    /**
     * @brief Numatytais reiksmemis sukuriamas studentas.
     */
    Studentas()
        : Zmogus("", ""), egzaminas_(0), vidurkis_(0), mediana_(0) {
    }

    /**
     * @brief Sukuria studenta pagal varda ir pavarde.
     * @param vard Vardas
     * @param pav Pavarde
     */
    Studentas(const std::string& vard, const std::string& pav)
        : Zmogus(vard, pav), egzaminas_(0), vidurkis_(0), mediana_(0) {
    }

    /**
     * @brief Sukuria studenta su duomenimis.
     * @param vard Studentas vardas
     * @param pav Studentas pavarde
     * @param nd Namu darbu pazymiai
     * @param egz Egzamino rezultatas
     */
    Studentas(const std::string& vard, const std::string& pav,
        const std::vector<int>& nd, int egz)
        : Zmogus(vard, pav), nd_(nd), egzaminas_(egz) {
        skaiciuokVidurkiMediana();
    }

    /**
     * @brief Studentas sukuriamas nuskaitant is srauto.
     * @param is ivesties srautas
     */
    Studentas(std::istream& is) { readStudent(is); }

    /**
     * @brief Kopijavimo konstruktorius.
     * @param other Kitas studentas
     */
    Studentas(const Studentas& other)
        : Zmogus(other.vardas_, other.pavarde_),
        nd_(other.nd_),
        egzaminas_(other.egzaminas_),
        vidurkis_(other.vidurkis_),
        mediana_(other.mediana_) {
    }

    /**
     * @brief Kopijavimo priskyrimo operatorius.
     * @param other Objektas, is kurio kopijuojama
     * @return Nuoroda i *this
     */
    Studentas& operator=(const Studentas& other) {
        if (this != &other) {
            vardas_ = other.vardas_;
            pavarde_ = other.pavarde_;
            nd_ = other.nd_;
            egzaminas_ = other.egzaminas_;
            vidurkis_ = other.vidurkis_;
            mediana_ = other.mediana_;
        }
        return *this;
    }

    /**
     * @brief Studentas destruktorius.
     */
    ~Studentas() override {
        vardas_.clear();
        pavarde_.clear();
        nd_.clear();
        egzaminas_ = 0;
        vidurkis_ = 0;
        mediana_ = 0;
    }

    // --- GETTERIAI ---

    /**
     * @brief Grazina studento varda.
     */
    const std::string& getVardas() const override { return vardas_; }

    /**
     * @brief Grazina studento pavarde.
     */
    const std::string& getPavarde() const override { return pavarde_; }

    /**
     * @brief Grazina namu darbu pazymius.
     */
    inline const std::vector<int>& getPazymiai() const { return nd_; }

    /**
     * @brief Grazina egzamino rezultata.
     */
    inline int getEgzaminas() const { return egzaminas_; }

    /**
     * @brief Grazina galutini bala pagal vidurki.
     */
    inline double getGalutinisVid() const { return vidurkis_; }

    /**
     * @brief Grazina galutini bala pagal mediana.
     */
    inline double getGalutinisMed() const { return mediana_; }

    /**
     * @brief Prideda nauja pazymi.
     * @param paz Pažymys
     */
    inline void pridetiPazymi(int paz) { nd_.push_back(paz); }

    /**
     * @brief Apskaiciuoja vidurki ir mediana pagal turimus pazymius.
     */
    void skaiciuokVidurkiMediana();

    /**
     * @brief Perskaito studento duomenis is srauto.
     * @param is ivesties srautas
     * @return Tas pats srautas
     */
    std::istream& readStudent(std::istream& is);

    /**
     * @brief Apskaiciuoja mediana is pateikto pazymiu vektoriaus.
     * @param v Pazymiai
     * @return Mediana
     */
    static double median(std::vector<int> v);

    // --- FRIEND FUNKCIJOS ---

    /**
     * @brief Lygina du studentus pagal varda.
     */
    friend bool comparePagalVarda(const Studentas& a, const Studentas& b);

    /**
     * @brief Lygina du studentus pagal pavarde.
     */
    friend bool comparePagalPavarde(const Studentas& a, const Studentas& b);

    /**
     * @brief Lygina du studentus pagal galutini bala (vidurki).
     */
    friend bool comparePagalGalutiniVid(const Studentas& a, const Studentas& b);

    /**
     * @brief Lygina du studentus pagal galutini bala (mediana).
     */
    friend bool comparePagalGalutiniMed(const Studentas& a, const Studentas& b);

    /**
     * @brief Nuskaitymo operatorius.
     */
    friend std::istream& operator>>(std::istream& is, Studentas& s);

    /**
     * @brief Spausdinimo operatorius.
     */
    friend std::ostream& operator<<(std::ostream& os, const Studentas& s);
};

#endif
