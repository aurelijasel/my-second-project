#include "pch.h"
#include "gtest/gtest.h"
#include "studentas.h"
#include "pagalbinesfunkcijos.h"
#include <vector>
#include <sstream>

/**
 * Testai Studentas klasei
 */

// Testas konstruktoriui su vardu ir pavarde
TEST(StudentasTest, Konstruktoriai) {
    Studentas s1;
    EXPECT_EQ(s1.getVardas(), "");
    EXPECT_EQ(s1.getPavarde(), "");

    Studentas s2("Jonas", "Jonaitis");
    EXPECT_EQ(s2.getVardas(), "Jonas");
    EXPECT_EQ(s2.getPavarde(), "Jonaitis");

    std::vector<int> nd = { 8, 9, 10 };
    Studentas s3("Petras", "Petraitis", nd, 9);
    EXPECT_EQ(s3.getEgzaminas(), 9);
    EXPECT_EQ(s3.getPazymiai().size(), 3);
}

// Testas prideti pazymi
TEST(StudentasTest, PridetiPazymi) {
    Studentas s("Ana", "Anait?");
    s.pridetiPazymi(10);

    EXPECT_EQ(s.getPazymiai().size(), 1);
    EXPECT_EQ(s.getPazymiai()[0], 10);
}

// Testas vidurkio ir medianos skaiciavimui
TEST(StudentasTest, SkaiciuokVidurkiMediana) {
    std::vector<int> nd = { 5, 7, 9 };
    Studentas s("Tomas", "Tomaitis", nd, 8);

    s.skaiciuokVidurkiMediana();

    double nd_vid = (5 + 7 + 9) / 3.0;
    double nd_med = 7.0; // median

    EXPECT_NEAR(s.getGalutinisVid(), nd_vid * 0.4 + 8 * 0.6, 1e-5);
    EXPECT_NEAR(s.getGalutinisMed(), nd_med * 0.4 + 8 * 0.6, 1e-5);
}

// Testas nuskaitymui is srauto
TEST(StudentasTest, ReadStudent) {
    std::istringstream input("Jonas Jonaitis 5 7 9 8\n");
    Studentas s(input);

    EXPECT_EQ(s.getVardas(), "Jonas");
    EXPECT_EQ(s.getPavarde(), "Jonaitis");
    EXPECT_EQ(s.getPazymiai().size(), 3);
    EXPECT_EQ(s.getEgzaminas(), 8);
}

// Testas median funkcijai (static)
TEST(StudentasTest, MedianStatic) {
    std::vector<int> v1 = { 1, 3, 2 };
    std::vector<int> v2 = { 1, 2, 3, 4 };

    EXPECT_EQ(Studentas::median(v1), 2);
    EXPECT_EQ(Studentas::median(v2), 2.5);
}

// Testas pagalbines funkcijos generuoti
TEST(PagalbinesFunkcijosTest, GeneruotiStudentas) {
    Studentas s = generuoti("Vardas", "Pavarde", 5);

    EXPECT_EQ(s.getPazymiai().size(), 5);
    EXPECT_GE(s.getEgzaminas(), 1);
    EXPECT_LE(s.getEgzaminas(), 10);
}