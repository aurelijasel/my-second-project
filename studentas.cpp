#include "studentas.h"
#include <numeric>
#include <stdexcept>
#include <iomanip>
#include <sstream>

// --- OPERATORIUS >> ---
std::istream& operator>>(std::istream& is, Studentas& s) {
    return s.readStudent(is);
}

// --- OPERATORIUS << ---
std::ostream& operator<<(std::ostream& os, const Studentas& s) {
    os << s.vardas_ << " " << s.pavarde_
        << " Vid.: " << std::fixed << std::setprecision(2) << s.vidurkis_
        << " Med.: " << std::fixed << std::setprecision(2) << s.mediana_;
    return os;
}

std::istream& Studentas::readStudent(std::istream& is) {
    std::string line;
    if (!std::getline(is, line)) {
        return is;
    }

    if (line.empty()) {
        return is;
    }

    std::istringstream ss(line);
    ss >> vardas_ >> pavarde_;
    nd_.clear();

    int paz;
    std::vector<int> laikini;
    while (ss >> paz) {
        laikini.push_back(paz);
    }

    if (laikini.empty()) {
        is.setstate(std::ios::failbit);
        return is;
    }

    egzaminas_ = laikini.back();
    laikini.pop_back();
    nd_ = laikini;

    skaiciuokVidurkiMediana();
    return is;
}

void Studentas::skaiciuokVidurkiMediana() {
    if (nd_.empty()) {
        vidurkis_ = egzaminas_ * 0.6f;
        mediana_ = egzaminas_ * 0.6f;
        return;
    }

    double suma = std::accumulate(nd_.begin(), nd_.end(), 0.0);
    double ndvid = suma / nd_.size();

    vidurkis_ = static_cast<float>(egzaminas_ * 0.6 + ndvid * 0.4);
    mediana_ = static_cast<float>(egzaminas_ * 0.6 + median(nd_) * 0.4);
}

double Studentas::median(std::vector<int> v) {
    std::sort(v.begin(), v.end());
    size_t n = v.size();
    if (n == 0) return 0;
    if (n % 2 == 0)
        return (v[n / 2 - 1] + v[n / 2]) / 2.0;
    else
        return v[n / 2];
}

// --- Palyginimai ---
bool comparePagalVarda(const Studentas& a, const Studentas& b) {
    return a.vardas_ < b.vardas_;
}
bool comparePagalPavarde(const Studentas& a, const Studentas& b) {
    return a.pavarde_ < b.pavarde_;
}
bool comparePagalGalutiniVid(const Studentas& a, const Studentas& b) {
    return a.getGalutinisVid() < b.getGalutinisVid();
}
bool comparePagalGalutiniMed(const Studentas& a, const Studentas& b) {
    return a.getGalutinisMed() < b.getGalutinisMed();
}
