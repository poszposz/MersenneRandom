//
//  MersenneRandomGenerator.cpp
//  MersenneRandom
//
//  Created by Jan Posz on 11.12.2016.
//  Copyright © 2016 agh. All rights reserved.
//
/*
 - upewnić się co do alfebetu danego generatora
 - ustalic 4 generatory, ktore maja takie same alfabety
 - porównać wartości pomiędzy nimi
 - porownac ich wartości z naszym algorytmem.
 - dla roznych dlugoci sekwencji
 - brać dla róznych dlugosci znaków. Dla malych ilosci znaków przykładowo jeśli jeden znak powtorzy sie 3 razy, jest zle. Dla dużych ilosci znaków nie.
 - analiza błędu, wwartość średnia
 - przyjrzeć się ENT i znaleźć metryki do wyznaczania jakości.
 -
 
 Drugie zajecia notatki:
 - zrobić wyniki dla 1000 obliczeń enta (moze nie tysiaca, ale sporo)
 - na dzisiaj raport tego kto nad czym pracowal
 -
*/

#include "MersenneRandomGenerator.hpp"

static const uint32_t UINT32MAX = 0xFFFFFFFF;

#pragma mark - random generator cofiguration

MersenneGeneratorConfiguration::MersenneGeneratorConfiguration() {
    this->N = 624;
    this->M = 397;
    this->R = 31;
    this->A = 0x9908B0DF;
    this->F = 1812433253;
    this->U = 11;
    this->S = 7;
    this->B = 0x9D2C5680;
    this->T = 15;
    this->C = 0xEFC60000;
    this->L = 18;
    this->lowerMask = (1ull << R) - 1;
    this->upperMask = (1ull << R);
}

#pragma mark - random number generation

MersenneGenerator::MersenneGenerator(MersenneGeneratorConfiguration *configuration, uint32_t seed) {
    this->currentConfiguration = configuration;
    mt = new uint32_t[configuration->N];
    this->initialize(seed);
}

void MersenneGenerator::initialize(uint32_t seed) {
    *mt = seed;
    for (int i = 1; i < currentConfiguration->N; i++) {
        *(mt + i + 1) = currentConfiguration->F * (*(mt + i - 1) ^ (*(mt + i - 1) >> 30)) + i;
    }
    currentIndex = currentConfiguration->N;
}

void MersenneGenerator::twist() {
    uint32_t x;
    uint32_t xA;
    for (int i = 0; i < currentConfiguration->N; i++) {
        x = (*(mt + i + 1) & currentConfiguration->upperMask) +
            (*(mt + (i + 1) % currentConfiguration->N) & currentConfiguration->lowerMask);
        xA = x >> 1;
        if (x & 0x1) {
            xA ^= currentConfiguration->A;
        }
        *(mt + i) = *(mt + (i + currentConfiguration->M) % currentConfiguration->N)^xA;
    }
    currentIndex = 0;
}

uint32_t MersenneGenerator::mersenneRandomGeneratedNumber() {
    uint32_t randomNumber = 0;
    int i = currentIndex;
    if (currentIndex >= currentConfiguration->N) {
        this->twist();
        i = currentIndex;
    }
    
    randomNumber = *(mt + i);
    currentIndex = i + 1;
    randomNumber ^= *(mt + i) >> currentConfiguration->U;
    randomNumber ^= (randomNumber << currentConfiguration->S) & currentConfiguration->B;
    randomNumber ^= (randomNumber << currentConfiguration->T) & currentConfiguration->C;
    randomNumber ^= (randomNumber >> currentConfiguration->L);
    return randomNumber;
}

uint32_t MersenneGenerator::mersenneRandomGeneratedNumberWithUpperBound(uint32_t bound) {
    uint32_t randomNumber = this->mersenneRandomGeneratedNumber();
    double percentage = (double)randomNumber / (double)UINT32MAX;
    randomNumber = percentage * (double)bound;
    return randomNumber;
}







