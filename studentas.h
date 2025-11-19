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
    Studentas() : egzaminas_(0), vidurkis_(0), mediana_(0) {}

    Studentas(const std::string& vard, const std::string& pav)
        : vardas_(vard), pavarde_(pav), egzaminas_(0), vidurkis_(0), mediana_(0) {
    }

    Studentas(const std::string& vard, const std::string& pav,
        const std::vector<int>& nd, int egz)
        : vardas_(vard), pavarde_(pav), nd_(nd), egzaminas_(egz) {
        skaiciuokVidurkiMediana();
    }

    Studentas(std::istream& is) { readStudent(is); }

    // --- RULE OF THREE ---
    // --- Copy konstruktorius ---
    Studentas(const Studentas& other)
        : vardas_(other.vardas_),
        pavarde_(other.pavarde_),
        nd_(other.nd_),
        egzaminas_(other.egzaminas_),
        vidurkis_(other.vidurkis_),
        mediana_(other.mediana_) {
    }

    // --- Copy assignment operatorius ---
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

    // --- Destructor ---
    ~Studentas() {
        vardas_.clear();
        pavarde_.clear();
        nd_.clear();
        egzaminas_ = 0;
        vidurkis_ = 0;
        mediana_ = 0;
    }

    // --- GETTERIAI ---
    inline const std::string& getVardas() const { return vardas_; }
    inline const std::string& getPavarde() const { return pavarde_; }
    inline const std::vector<int>& getPazymiai() const { return nd_; }
    inline int getEgzaminas() const { return egzaminas_; }
    inline double getGalutinisVid() const { return vidurkis_; }
    inline double getGalutinisMed() const { return mediana_; }

    inline void pridetiPazymi(int paz) { nd_.push_back(paz); }
    void skaiciuokVidurkiMediana();
    std::istream& readStudent(std::istream&);

    static double median(std::vector<int> v);

    // --- PALYGINIMAI ---
    friend bool comparePagalVarda(const Studentas& a, const Studentas& b);
    friend bool comparePagalPavarde(const Studentas& a, const Studentas& b);
    friend bool comparePagalGalutiniVid(const Studentas& a, const Studentas& b);
    friend bool comparePagalGalutiniMed(const Studentas& a, const Studentas& b);

    // --- I/O OPERATORIAI ---
    friend std::istream& operator>>(std::istream& is, Studentas& s); // *** PRIDĖTA ***
    friend std::ostream& operator<<(std::ostream& os, const Studentas& s); // *** PRIDĖTA ***
};

#endif

