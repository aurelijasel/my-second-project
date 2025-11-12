#ifndef STUDENTAS_H
#define STUDENTAS_H

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

class Studentas {
private:
    std::string vardas_;
    std::string pavarde_;
    std::vector<int> nd_;
    int egzaminas_;
    float vidurkis_;
    float mediana_;

public:
    // --- KONSTRUKTORIAI ---
    Studentas() : egzaminas_(0), vidurkis_(0), mediana_(0) {}  // default konstruktorius
    Studentas(const std::string& vard, const std::string& pav) : vardas_(vard), pavarde_(pav), egzaminas_(0), vidurkis_(0), mediana_(0) {}
    Studentas(std::istream& is) { readStudent(is); }

    // Getteriai pagal dabartin? kod?
    inline const std::string& getVardas() const { return vardas_; }
    inline const std::string& getPavarde() const { return pavarde_; }
    inline const std::vector<int>& getPazymiai() const { return nd_; }
    inline int getEgzaminas() const { return egzaminas_; }
    inline double getGalutinisVid() const { return vidurkis_; }
    inline double getGalutinisMed() const { return mediana_; }

    // --- SKAI?IAVIMO FUNKCIJOS ---
    void skaiciuokVidurkiMediana(); // apskai?iuoja abu rezultatus

    // --- DUOMEN? NUSKAITYMAS ---
    std::istream& readStudent(std::istream&);

    // --- PAGALBIN?S FUNKCIJOS ---
    static double median(std::vector<int> v);

    // --- PALYGINIMO FUNKCIJOS ---
    friend bool comparePagalVarda(const Studentas& a, const Studentas& b);
    friend bool comparePagalPavarde(const Studentas& a, const Studentas& b);
    friend bool comparePagalEgzamina(const Studentas& a, const Studentas& b);
};

#endif
