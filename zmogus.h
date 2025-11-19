#ifndef ZMOGUS_H
#define ZMOGUS_H

#include <string>

// ABSTRAKTI BAZINĖ KLASĖ

class Zmogus {
protected:
    std::string vardas_;
    std::string pavarde_;

public:
    Zmogus() = default;
    Zmogus(const std::string& vard, const std::string& pav) : vardas_(vard), pavarde_(pav) {}

    virtual ~Zmogus() = default;

    // --- GETTERIAI ---
    virtual const std::string& getVardas() const = 0;
    virtual const std::string& getPavarde() const = 0;
};

#endif
