#include "studentas.h"
#include <numeric>
#include <stdexcept>
#include <iomanip>

std::istream& Studentas::readStudent(std::istream& is) {
    is >> vardas_ >> pavarde_;
    nd_.clear();
    int paz;
    std::vector<int> laikini;
    while (is >> paz) {
        laikini.push_back(paz);
    }
    if (laikini.empty()) throw std::runtime_error("Nera pazymiu.");
    egzaminas_ = laikini.back();
    laikini.pop_back();
    nd_ = laikini;
    skaiciuokVidurkiMediana();
    return is;
}

void Studentas::skaiciuokVidurkiMediana() {
    if (nd_.empty()) {
        vidurkis_ = egzaminas_ * 0.6;
        mediana_ = egzaminas_ * 0.6;
        return;
    }
    double suma = std::accumulate(nd_.begin(), nd_.end(), 0.0);
    double ndvid = suma / nd_.size();
    vidurkis_ = egzaminas_ * 0.6 + ndvid * 0.4;
    mediana_ = egzaminas_ * 0.6 + median(nd_) * 0.4;
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

// --- Palyginimo funkcijos ---
bool comparePagalVarda(const Studentas& a, const Studentas& b) {
    return a.vardas_ < b.vardas_;
}

bool comparePagalPavarde(const Studentas& a, const Studentas& b) {
    return a.pavarde_ < b.pavarde_;
}

bool comparePagalEgzamina(const Studentas& a, const Studentas& b) {
    return a.egzaminas_ < b.egzaminas_;
}
