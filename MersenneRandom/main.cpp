//
//  main.cpp
//  MersenneRandom
//
//  Created by Jan Posz on 11.12.2016.
//  Copyright © 2016 agh. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "MersenneRandomGenerator.hpp"
#include <time.h>
#include <string>
#include <random>
#include <sstream>

typedef enum {
    Mersenne,
    minSTD,
    Knuth
} RandomGenerationMethod;

static std::string alfabet_5[5] = {"a","b","c","d","e"};
static std::string alfabet_10[10] = {"a","b","c","d","e","f","g","h","i","j"};
static std::string alfabet_15[15] = {"a","b","c","d","e","f","g","h","i","j","k","l","m","n","o"};
static std::string alfabet_20[20] = {"a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t"};
static std::string alfabet_62[62] = {"a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","y","x","z", "A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","R","S","T","U","W","X","Y","Z","0","1","2","3","4","5","6","7","8","9"};

void generateMersenneFiles(int sequenceLength, int alphabetLength, std::string alphabet[], std::string resultFileName) {
    
    uint32_t seed = time(NULL);
    MersenneGeneratorConfiguration *configuration = new MersenneGeneratorConfiguration();
    MersenneGenerator *generator = new MersenneGenerator(configuration, seed);
    std::fstream myfile;
    myfile.open(resultFileName, std::fstream::binary | std::fstream::in | std::fstream::out | std::fstream::trunc);
    myfile.flush();
    for(int i=0 ;i<sequenceLength;i++) {
        std::string rand = alphabet[generator->mersenneRandomGeneratedNumberWithUpperBound(alphabetLength)];
        myfile << rand;
    }
    myfile.close();
}

////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

void generateMinSTDRandom(int sequenceLength, int alphabetLength, std::string alphabet[], std::string resultFileName) {
    
    uint32_t seed = time(NULL);
    std::fstream myfile;
    myfile.open(resultFileName, std::fstream::binary | std::fstream::in | std::fstream::out | std::fstream::trunc);
    myfile.flush();
    std::minstd_rand0 gen(seed);
    std::uniform_int_distribution<> distr(2, alphabetLength);
    for(int i=0 ;i<sequenceLength;i++) {
        std::string rand = alphabet[distr(gen)];
        myfile << rand;
    }
    myfile.close();
}

////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

void generateKnuthRandom(int sequenceLength, int alphabetLength, std::string alphabet[], std::string resultFileName) {
    
    uint32_t seed = time(NULL);
    std::knuth_b knuth(seed);
    std::fstream myfile;
    myfile.open(resultFileName, std::fstream::binary | std::fstream::in | std::fstream::out | std::fstream::trunc);
    for(int i=0 ;i<sequenceLength;i++) {
        std::string rand = alphabet[knuth() % alphabetLength];
        myfile << rand;
    }
    myfile.close();
}


////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

int main(int argc, const char * argv[]) {
    
    // must pass sequence length
    // must pass alphabet 5, 10, 15, 20 or 62
    // must pass method: mer, min or knu
    // must pass result file name

    if (argc != 5) {
        std::cout << "Error: you should pass exactly 5 parameters" << std::endl;
        std::cout << "Example usage: ./mers_rand 56 5 mer mersenne.txt" << std::endl;
        std::cout << "56 is sequence length." << std::endl;
        std::cout << "5 is alphabet length. Available legths: 5, 10, 15, 20, 62." << std::endl;
        std::cout << "mer is generation method. Available methods: mer, min, knu." << std::endl;
        std::cout << "mersenne.txt is name of output file." << std::endl;
        return 1;
    }
    int times = atoi(argv[1]);
    int alphabetLength = atoi(argv[2]);
    std::string generationMethod = argv[3];
    std::string resultFileName = argv[4];
    
    RandomGenerationMethod method;
    if (generationMethod == "mer") {
        method = Mersenne;
    }
    else if (generationMethod == "min") {
        method = minSTD;
    }
    else if (generationMethod == "knu") {
        method = Knuth;
    }
    else {
        std::cout << "Unknown generation method" << std::endl;
        return 2;
    }
    
    std::string *desiredAlphabet = new std::string[alphabetLength];
    if (alphabetLength == 5) {
        desiredAlphabet = alfabet_5;
    }
    else if (alphabetLength == 10) {
        desiredAlphabet = alfabet_10;
    }
    else if (alphabetLength == 15) {
        desiredAlphabet = alfabet_15;
    }
    else if (alphabetLength == 20) {
        desiredAlphabet = alfabet_20;
    }
    else if (alphabetLength == 62) {
        desiredAlphabet = alfabet_62;
    }
    else {
        std::cout << "Unsupported alphabet length" << std::endl;
        return 3;
    }
    
    switch (method) {
        case Mersenne:
            generateMersenneFiles(times, alphabetLength, desiredAlphabet, resultFileName);
            break;
        case minSTD:
            generateMinSTDRandom(times, alphabetLength, desiredAlphabet, resultFileName);
            break;
        case Knuth:
            generateKnuthRandom(times, alphabetLength, desiredAlphabet, resultFileName);
            break;
        default:
            break;
    }
    std::cout << "Generated with success to file: " << resultFileName << std::endl;
    return 0;
}



