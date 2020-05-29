#Komanda - "Harambedid911"
## Nariai ##
- Justas Radkevičius, IFF-7/9 gr.
- Marijus Jenulis, IFF-7/3 gr.
- Gintautas Lasevičius, IFF-7/6 gr.

## Reikalavimai ##
- Ubuntu 20.04 (Windows netestuota)
- cmake 3.17.3
- GNU Make 4.2.1 
- Flex 2.6.4
- Bison 3.5.1
- LLVM 10.0
- build-essentials
- zlib1g-dev

## Kompiliavimas
1. Klonuoti šia repositoriją.
```
https://bitbucket.org/ktu_pkt/projektas2020/src/Harambedid911/
```
2. Atidaryti terminalą pagrindiniame kataloge "harambe"
2. Sukurti "build" katalogą
```
mkdir build
```
3. Įeiti į build katalogą
```
cd build
```
4. paleisti sugeneruoti Makefile failą
```
cmake ..
```

5. Paleisti make
```
make
```
6. Viskas. build kataloge turėtų būti harambe.exe failas

## Testavimas
### Fibonacci sekos skaičiavimas
1. Sukompiluoti projektą (kaip tai padaryti yra 
pateikta aukščiau)
2. Iš "build katalogo įvykdyti komandą:"
```
./harambe ../test/fibonacci.harambe -q
```
3. Rezultatai spausdinami į terminalą ir į failą ```fib.txt``` esantį ```build``` kataloge

![image of results1](https://github.com/marjen0/harambe/pictures/Screenshot from 2020-05-29 13-21-23.png)
![Image of results2](https://github.com/marjen0/harambe/pictures/Screenshot from 2020-05-29 13-20-05.png)


