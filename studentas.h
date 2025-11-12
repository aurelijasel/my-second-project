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

    // Setteriai
    inline void setVardas(const std::string& vard) { vardas_ = vard; }
    inline void setPavarde(const std::string& pav) { pavarde_ = pav; }
    inline void setEgzaminas(int egz) { egzaminas_ = egz; }
    inline void setGalutinisVid(double v) { vidurkis_ = v; }
    inline void setGalutinisMed(double m) { mediana_ = m; }
    inline void pridetiPazymi(int paz) { nd_.push_back(paz); }
    inline void setPazymiai(const std::vector<int>& pazymiai) { nd_ = pazymiai; }

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

