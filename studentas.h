#ifndef STUDENTAS_H
#define STUDENTAS_H

#include "zmogus.h"
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

class Studentas : public Zmogus {
private:
    std::vector<int> nd_;
    int egzaminas_;
    float vidurkis_;
    float mediana_;

public:

    // --- KONSTRUKTORIAI ---
    Studentas()
        : Zmogus("", ""), egzaminas_(0), vidurkis_(0), mediana_(0) {
    }

    Studentas(const std::string& vard, const std::string& pav)
        : Zmogus(vard, pav), egzaminas_(0), vidurkis_(0), mediana_(0) {
    }

    Studentas(const std::string& vard, const std::string& pav,
        const std::vector<int>& nd, int egz)
        : Zmogus(vard, pav), nd_(nd), egzaminas_(egz) {
        skaiciuokVidurkiMediana();
    }

    Studentas(std::istream& is) { readStudent(is); }

    // --- COPY KONSTRUKTORIUS ---
    Studentas(const Studentas& other)
        : Zmogus(other.vardas_, other.pavarde_),
        nd_(other.nd_),
        egzaminas_(other.egzaminas_),
        vidurkis_(other.vidurkis_),
        mediana_(other.mediana_) {
    }

    // --- COPY ASSIGNMENT ---
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

    // --- TAVO DESTRUKTORIUS ---
    ~Studentas() override {
        //std::cout << "Destruktorius kvieciamas studentui: "
            //<< vardas_ << " " << pavarde_ << std::endl;

        vardas_.clear();
        pavarde_.clear();
        nd_.clear();
        egzaminas_ = 0;
        vidurkis_ = 0;
        mediana_ = 0;
    }

    // --- GETTERIAI ---
    const std::string& getVardas() const override { return vardas_; }
    const std::string& getPavarde() const override { return pavarde_; }

    inline const std::vector<int>& getPazymiai() const { return nd_; }
    inline int getEgzaminas() const { return egzaminas_; }
    inline double getGalutinisVid() const { return vidurkis_; }
    inline double getGalutinisMed() const { return mediana_; }

    inline void pridetiPazymi(int paz) { nd_.push_back(paz); }

    void skaiciuokVidurkiMediana();
    std::istream& readStudent(std::istream&);
    static double median(std::vector<int> v);

    // --- FRIEND FUNKCIJOS ---
    friend bool comparePagalVarda(const Studentas& a, const Studentas& b);
    friend bool comparePagalPavarde(const Studentas& a, const Studentas& b);
    friend bool comparePagalGalutiniVid(const Studentas& a, const Studentas& b);
    friend bool comparePagalGalutiniMed(const Studentas& a, const Studentas& b);

    friend std::istream& operator>>(std::istream& is, Studentas& s);
    friend std::ostream& operator<<(std::ostream& os, const Studentas& s);
};

#endif
