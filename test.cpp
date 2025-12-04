#include "pch.h"
#include "gtest/gtest.h"
#include "studentas.h"
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
