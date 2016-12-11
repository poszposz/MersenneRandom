//
//  main.cpp
//  MersenneRandom
//
//  Created by Jan Posz on 11.12.2016.
//  Copyright © 2016 agh. All rights reserved.
//

#include <iostream>
#include "MersenneRandomGenerator.hpp"

int main(int argc, const char * argv[]) {
    
    uint32_t seed = 50;
    MersenneGeneratorConfiguration *configuration = new MersenneGeneratorConfiguration();
    MersenneGenerator *generator = new MersenneGenerator(configuration, seed);
    
    std::cout << "Random 1: " << generator->mersenneRandomGeneratedNumberWithUpperBound(10) << std::endl;
    std::cout << "Random 2: " << generator->mersenneRandomGeneratedNumberWithUpperBound(10) << std::endl;
    std::cout << "Random 3: " << generator->mersenneRandomGeneratedNumberWithUpperBound(10) << std::endl;
    std::cout << "Random 4: " << generator->mersenneRandomGeneratedNumberWithUpperBound(10) << std::endl;
    std::cout << "Random 5: " << generator->mersenneRandomGeneratedNumberWithUpperBound(10) << std::endl;
    std::cout << "Random 6: " << generator->mersenneRandomGeneratedNumberWithUpperBound(10) << std::endl;
    
    return 0;
}
