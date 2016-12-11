//
//  MersenneRandomGenerator.hpp
//  MersenneRandom
//
//  Created by Jan Posz on 11.12.2016.
//  Copyright © 2016 agh. All rights reserved.
//

#ifndef MersenneRandomGenerator_hpp
#define MersenneRandomGenerator_hpp

#include <stdio.h>
#include <stdint.h>

class MersenneGeneratorConfiguration {
public:
    MersenneGeneratorConfiguration();
    uint32_t N;
    uint32_t M;
    uint32_t R;
    uint32_t A;
    uint32_t F;
    uint32_t U;
    uint32_t S;
    uint32_t B;
    uint32_t T;
    uint32_t C;
    uint32_t L;
    unsigned long long lowerMask;
    unsigned long long upperMask;
};

class MersenneGenerator {
public:
    MersenneGenerator(MersenneGeneratorConfiguration *configuration, uint32_t seed);
    uint32_t mersenneRandomGeneratedNumber();
    uint32_t mersenneRandomGeneratedNumberWithUpperBound(uint32_t bound);
    uint32_t *mt;
    uint16_t currentIndex;
private:
    MersenneGeneratorConfiguration *currentConfiguration;
    void initialize(uint32_t seed);
    void twist();
};

#endif /* MersenneRandomGenerator_hpp */
