# Studentų duomenų apdorojimo ir analizės programa

Ši programa leidžia:
- įvesti, generuoti, nuskaityti ir apdoroti studentų pažymius,
- suskirstyti studentus į dvi grupes (vargsiukai ir galvociai),
- pasirinkti skirtingas vieną iš trijų strategijų duomenų apdorojimui,
- palyginti vector ir list konteinerių veikimo spartą ir atminties panaudojimą,
- matuoti skirtingų operacijų (nuskaitymo, įrašymo) laikus.

## Naudojimosi instrukcija

### Programos atsisiuntimas
1. Parsisiųsti cmake zip programą (ne ankstesnę, nei 3.25.0 versiją): https://cmake.org/download/
2. Zip failą išskleisti savo kompiuteryje. Rasti jame aplanką pavadinimu "bin" ir iš to aplanko išsisaugoti failą cmake.exe.
3. Atsisiųsti CMakeLists.txt, run.bat, .cpp ir .h failus iš GitHub.
4. Kompiuteryje sukurti aplanką pavadintą "cmaketest". Į jį įkelti CMakeLists.txt, run.bat, cmake.exe failus.
5. "cmaketest" aplanke sukurti du aplankus: "src", "include". Į "src" aplanką įkelti .cpp failus, o į "include" - .h failus.
6. Programą paleisti naudojant terminalą, įvedant komandas:
```
cmake .\CMakeLists.txt
```
```
cmake --build .
```
```
cd Debug
```
```
.\Studentu_rusiavimo_programa.exe
``` 

### Paleidimas
1. Atsidarykite projektą.  
2. Sukompiliuokite ir paleiskite failą v1.0.cpp.  
3. Pasirinkite vieną iš režimų:
```
1 - Iprastas programos veikimas
2 - Automatinis testavimas (vector vs list)
3 - Rule of three demonstracija
```

### Įprastas režimas
Leidžia įvesti studentus:
- rankiniu būdu,  
- automatiškai sugeneruoti,  
- nuskaityti iš failo.

Tada galima pasirinkti:
- su kokiu konteineriu rūšiuoti studentas (vector / list),
- pagal ką skaičiuoti galutinį pažymį (vidurkį / medianą / abu),
- pagal ką rikiuoti (vardą / pavardę / pažymį).

Rezultatai įrašomi į rezultatai.txt bei sugeneruojami du failai:
```
vargsiukai_*_strat1.txt
galvociai_*_strat1.txt
```

### Automatinis testavimas
Šiuo režimu programa automatiškai paleidžia našumo testus su skirtingais failais:
```
studentai1000.txt
studentai10000.txt
studentai100000.txt
studentai1000000.txt
studentai10000000.txt
```
Galima pasirinkti:
- pagal kokią strategiją vykdyti testavimą,
- pagal ką suskirstyti (vidurkį / medianą),
- pagal ką rikiuoti (vardą / pavardę / pažymį),

Rezultatai įrašomi į testavimorezultatai.txt.

### Rule of Three demonstracija
„Rule of Three“ principas teigia: jeigu klasė naudoja duomenis, kuriuos reikia valdyti rankiniu būdu, ji privalo turėti:
- Kopijavimo konstruktorių
- Priskyrimo operatorių
- Destruktorių

Šiuo režimu programa leidžia vartotojui įvesti studentus (s1 ir s2), o programa demonstruoja:
- Konstruktorių
- Kopijavimo konstruktorių
- Priskyrimo operatorių
- Savo paties priskyrimą
- Destruktorius

Demonstracija atliekama specialiame bloke { ... }, į kurį įdedami visi vartotojo sukurti objektai (s1, s2, s3). Pasibaigus blokui — iškviečiamas destruktorius ir visi objektai sunaikinami.

**Pavyzdys konsolėje:**
```
RULE OF THREE DEMONSTRACIJA
Iveskite studento duomenis (vardas, pavarde, pazymiai ir egzaminas):
Jonas Jonaitis 3 6 5 4 4 3 6
Originalus studentas (s1): Jonas Jonaitis Vid.: 5.27 Med.: 5.20
Po kopijavimo konstruktoriaus (s2 = s1): Jonas Jonaitis Vid.: 5.27 Med.: 5.20
Iveskite kita studenta (s3), kuris bus perrasytas s1 duomenimis:
Petras Petraitis  8 7 7 10
Pries priskyrima (s3): Petras Petraitis Vid.: 8.93 Med.: 8.80
Po priskyrimo operatoriaus (s3 = s1): Jonas Jonaitis Vid.: 5.27 Med.: 5.20
Po saves priskyrimo (s1 = s1): Jonas Jonaitis Vid.: 5.27 Med.: 5.20
Baigiame bloka. Dabar bus kvieciami destruktoriai s1, s2 ir s3.
Destruktorius kvieciamas studentui: Jonas Jonaitis
Destruktorius kvieciamas studentui: Jonas Jonaitis
Destruktorius kvieciamas studentui: Jonas Jonaitis
Blokas baigtas. Visi vartotojo ivesti studentai sunaikinti.
```

**Įvesties ir išvesties operatoriai**

1. **Įvesties operatorius (>>)**  
   Leidžia įvesti:
   - vardą
   - pavardę
   - namų darbų pažymius
   - egzamino pažymį
   
   ```
   Studentas s;
   cin >> s; // Įvedimas iš konsolės arba failo
   ```

   **Formatas:**
   ```
   Vardas Pavarde nd1 nd2 nd3 ... egzaminas
   ```

2. **Išvesties operatorius (<<)**  
   Leidžia tvarkingai spausdinti studento duomenis į ekraną ar failą:
   ```
   cout << s;
   ```
   **Pavyzdys konsolėje:**
   ```
   Vardas1 Pavarde1 Vid.: 7.40 Med.: 7.20
   ```

Perdengti operatoriai >> ir << leidžia studentų duomenis skaityti ir išvesti vienodu formatu tiek į ekraną, tiek į failus.

## Strategijų aprašymas

| Strategija | Aprašymas |
|-------------|------------|
| **1** | Sukuriami du nauji konteineriai: vienas vargšiukams, kitas galvočiams. |
| **2** | Sukuriamas tik vienas naujas konteineris. Vargšiukai ištrinami iš bendro sąrašo. |
| **3** | Optimizuota versija – naudojami STL algoritmai ir efektyvus konteinerių tvarkymas. |

## Testavimo aplinka

**Testavimo sistema:**
```
CPU: Intel(R) Core(TM) i7-8650U CPU @ 1.90GHz 2.11 GHz
RAM: 16,0 GB (15,9 GB usable)
HDD: 238 GB SSD SAMSUNG MZVLW256HEHP-000L7
```

**Testuoti failai:**
```
studentai1000.txt
studentai10000.txt
studentai100000.txt
studentai1000000.txt
studentai10000000.txt
```

**Strategija 1 – Du nauji konteineriai**

| Konteineris | Failas | Nuskaitymas (s) | Rūšiavimas (s) | Įrašymas (s) | Bendras (s) | Atmintis (B) |
|--------------|---------|----------------|----------------|--------------|--------------|--------------|
| vector | studentai1000.txt | 0.015827 | 0.013010 | 0.004352 | 0.033189 | 188412 |
| list | studentai1000.txt | 0.016332 | 0.015271 | 0.004227 | 0.035830 | 87256 |
| vector | studentai10000.txt | 0.126357 | 0.058128 | 0.031747 | 0.216232 | 1998444 |
| list | studentai10000.txt | 0.126573 | 0.062002 | 0.032832 | 0.221407 | 832056 |
| vector | studentai100000.txt | 0.957551 | 0.415778 | 0.328320 | 1.701649 | 21620012 |
| list | studentai100000.txt | 0.942920 | 0.501871 | 0.340209 | 1.785000 | 8182204 |
| vector | studentai1000000.txt | 6.804002 | 1.842711 | 1.954002 | 10.600715 | 216012312 |
| list | studentai1000000.txt | 6.201284 | 2.701446 | 2.874028 | 11.776758 | 81817132 |
| vector | studentai10000000.txt | 54.182993 | 19.913085 | 20.829315 | 94.925393 | 2160000120 |
| list | studentai10000000.txt | 53.942888 | 30.774006 | 30.003270 | 114.720164 | 818177624 |

**Strategija 2 – Vienas naujas konteineris**

| Konteineris | Failas | Nuskaitymas (s) | Įrašymas (s) | Bendras (s) | Atmintis (B) |
|--------------|---------|----------------|--------------|--------------|--------------|
| vector | studentai1000.txt | 0.008800 | 0.007686 | 0.016487 | 186652 |
| list | studentai1000.txt | 0.009662 | 0.004400 | 0.014062 | 85556 |
| vector | studentai10000.txt | 0.078292 | 0.419455 | 0.497747 | 1999556 |
| list | studentai10000.txt | 0.100894 | 0.043024 | 0.143919 | 832316 |
| vector | studentai100000.txt | 0.955422 | 65.289058 | 66.244481 | 21625972 |
| list | studentai100000.txt | 1.414147 | 0.436104 | 1.850251 | 8182596 |
| vector | studentai1000000.txt | 7.382457 | 90.734936 | 98.117393 | 123318640 |
| list | studentai1000000.txt | 6.611306 | 8.723771 | 15.335077 | 82075436 |
| vector | studentai10000000.txt | 66.730549 | 140.426712 | 207.157261 | 2483700352 |
| list | studentai10000000.txt | 69.522376 | 69.699507 | 139.221883 | 821451136 |

**Strategija 3 – Optimizuota (naudojami STL algoritmai)**

| Konteineris | Failas | Nuskaitymas (s) | Įrašymas (s) | Bendras (s) | Atmintis (B) |
|--------------|---------|----------------|--------------|--------------|--------------|
| vector | studentai1000.txt | 0.009535 | 0.037019 | 0.046554 | 234888 |
| list | studentai1000.txt | 0.019894 | 0.054275 | 0.074170 | 85556 |
| vector | studentai10000.txt | 0.163339 | 0.153464 | 0.316804 | 2502376 |
| list | studentai10000.txt | 0.136406 | 0.170332 | 0.306738 | 832316 |
| vector | studentai100000.txt | 0.980177 | 1.228347 | 2.208524 | 26778544 |
| list | studentai100000.txt | 0.852115 | 1.642650 | 2.494766 | 14000016 |
| vector | studentai1000000.txt | 13.513278 | 12.871179 | 26.384458 | 233186400 |
| list | studentai1000000.txt | 16.078031 | 19.183705 | 35.261737 | 82075436 |
| vector | studentai10000000.txt | 146.382746 | 167.735478 | 314.118225 | 2483700352 |
| list | studentai10000000.txt | 154.682915 | 218.426093 | 373.109009 | 821451136 |

Dažniausiai buvo greičiau naudoti 2 strategiją.

**Išvados**

- Mažiems duomenų kiekiams (1000–10000) vector ir list veikimas trunka panašiai.  
- Didėjant įrašų kiekiui, vector tampa efektyvesnis – greitesnis bendras veikimo laikas.  
- Vector konteineris sunaudoja daugiau atminties.   
- 2 strategija labai neefektyvi su dideliais duomenų kiekiais (1000000 ir 10000000 įrašų), nes ji kiekvienam vargšiukui naudoja erase() funkciją vector konteineryje. Kiekvienas erase() kvietimas perstumia visus likusius elementus, todėl operacijos sudėtingumas tampa O(n²).


## Programos našumo analizė

**1. Palyginimas: struct vs class**

Testai atlikti su vector konteineriu, greičiausia strategija (1) ir 2 failų dydžiais:  
```
studentai100000.txt  
studentai1000000.txt
```

**Strategija 1 – Du nauji konteineriai (**su struct**)**

| Konteineris | Failas | Nuskaitymas (s) | Įrašymas (s) | Bendras (s) | Atmintis (B) |
|--------------|---------|----------------|--------------|--------------|--------------|
| vector | studentai100000.txt | 0.957551 | 0.328320 | 1.701649 | 21 620 012 |
| vector | studentai1000000.txt | 6.804002 | 1.954002 | 10.600715 | 216 012 312 | 

**Strategija 1 – Du nauji konteineriai (**su class**)**

| Konteineris | Failas | Nuskaitymas (s) | Įrašymas (s) | Bendras (s) | Atmintis (B) |
|--------------|---------|----------------|--------------|--------------|--------------|
| vector | studentai100000.txt | 0.408979 | 0.199345 | 0.608324 | 14 378 544 |
| vector | studentai1000000.txt | 4.397648 | 2.120036 | 6.517684 | 109 186 400 |

**Išvada:**  
- class versijos veikimas yra spartesnis ir atminties atžvilgiu efektyvesnis nei struct.

**2. Optimizavimo flag’ų analizė**

Analizuotas struct ir class variantas (strategija 1, vector, du failai: studentai100000.txt, studentai1000000.txt) su skirtingais kompiliatoriaus optimizavimo lygiais: O1, O2, O3.

**Struct analizė:**

**Optimizacija O1**

| Konteineris | Failas | Nuskaitymas (s) | Įrašymas (s) | Bendras (s) | Atmintis (B) |
|--------------|---------|----------------|--------------|--------------|--------------|
| vector | studentai100000.txt | 0.490824 | 0.198727 | 0.689551 | 26778544 |
| vector | studentai1000000.txt | 4.896540 | 2.102408 | 6.998948 | 233186400 |

**Optizimacija O2**

| Konteineris | Failas | Nuskaitymas (s) | Įrašymas (s) | Bendras (s) | Atmintis (B) |
|--------------|---------|----------------|--------------|--------------|--------------|
| vector | studentai100000.txt | 0.957551 | 0.328320 | 1.701649 | 21620012 |
| vector | studentai1000000.txt | 6.804002 | 1.954002 | 10.600715 | 216012312 | 

**Optimizacija O3**

| Konteineris | Failas | Nuskaitymas (s) | Įrašymas (s) | Bendras (s) | Atmintis (B) |
|--------------|---------|----------------|--------------|--------------|--------------|
| vector | studentai100000.txt | 0.672783 | 0.253848 | 0.926631 | 26778544 |
| vector | studentai1000000.txt | 7.709458 | 3.816911 | 11.526369 | 233186400 |

**Class analizė:**

**Optimizacija O1**

| Konteineris | Failas | Nuskaitymas (s) | Įrašymas (s) | Bendras (s) | Atmintis (B) |
|--------------|---------|----------------|--------------|--------------|--------------|
| vector | studentai100000.txt | 0.404711 | 0.228556 | 0.633267 | 14 378 544 |
| vector | studentai1000000.txt | 4.559094 | 2.033421 | 6.592515 | 109 186 400 |

**Optimizacija O2**

| Konteineris | Failas | Nuskaitymas (s) | Įrašymas (s) | Bendras (s) | Atmintis (B) |
|--------------|---------|----------------|--------------|--------------|--------------|
| vector | studentai100000.txt | 0.408979 | 0.199345 | 0.608324 | 14 378 544 |
| vector | studentai1000000.txt | 4.397648 | 2.120036 | 6.517684 | 109 186 400 |

**Optimizacija O3**

| Konteineris | Failas | Nuskaitymas (s) | Įrašymas (s) | Bendras (s) | Atmintis (B) |
|--------------|---------|----------------|--------------|--------------|--------------|
| vector | studentai100000.txt | 0.422925 | 0.216015 | 0.638940 | 14 378 544 |
| vector | studentai1000000.txt | 5.140793 | 2.245802 | 7.386596 | 109 186 400 |

**Išvados:**

- O1 yra stabiliausias ir greičiausias optimizacijos pasirinkimas dirbant su struct.
- O2 yra stabiliausias ir greičiausias optimizacijos pasirinkimas dirbant su class.

**3. EXE failų dydžių palyginimas po optimizavimo**

| Tipas | O1 dydis | O2 dydis | O3 dydis |
|--------|-----------|-----------|-----------|
| struct | 86 KB | 97 KB | 104 KB |
| class | 78 KB | 93 KB | 95 KB |

**Išvada:**

- class versijos exe failai yra mažesni už struct visuose optimizavimo lygiuose.  
- class struktūra leidžia kompiliatoriui efektyviau optimizuoti kodą.

## Rankinis įvedimas

Įvedus studento duomenis rankiniu būdu, ekrane matomas objekto saugojimo atminties adresas:

**Vector atveju:**
```
Iveskite 1 studenta
Iveskite pavarde: Jonaitis
Iveskite varda: Jonas
Iveskite pazymi: 6
Ar norite ivesti dar viena pazymi? (taip/ne): ne
Iveskite egzamina: 7
Studento objektas saugomas adresu: 000002AF25106120
```

**List atveju:**
```
Iveskite 1 studenta
Iveskite pavarde: Jonaitis
Iveskite varda: Jonas
Iveskite pazymi: 6
Ar norite ivesti dar viena pazymi? (taip/ne): ne
Iveskite egzamina: 7
Studento objektas saugomas adresu: 0000022402A862D0
```

## Release istorija

| Versija | Aprašymas |
|----------|------------|
| v.pradinė | Programa leidžia įvesti studentų duomenis, apskaičiuoti galutinį balą pagal vidurkį, medianą arba abu. |
| v0.1 | Pridėta duomenų nuskaitymo iš failo galimybė ir išvedimo formatavimas. |
| v0.2 | Pridėta atsitiktinė duomenų failų generacija ir veikimo trukmės (failų kūrimo, skaitymo, rūšiavimo) matavimas. |
| v0.3 | Pridėtas konteinerių (vector ir list) veikimo trukmės palyginimas. |
| v1.0 | Pridėtas 3 strategijų (rūšiavimo metodų) palyginimas tiek vector, tiek list. |
| v1.1 | Pakeista struct į class duomenų struktūrų apibrėžimuose, išlaikant tą patį programos veikimą. |
| v1.2 | Pridėta Rule of Three demonstracija, perdengti >> / << operatoriai darbui su ekrano ir failo įvestimi/išvestimi. |
