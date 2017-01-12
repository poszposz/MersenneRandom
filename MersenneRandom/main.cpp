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

static int alfabet_length[5] = {5,10,15,20,26};
static std::string alfabet_1[5] = {"a","b","c","d","e"};
__unused std::string alfabet_2[10] = {"a","b","c","d","e","f","g","h","i","j"};
static std::string alfabet_3[15] = {"a","b","c","d","e","f","g","h","i","j","k","l","m","n","o"};
static std::string alfabet_4[20] = {"a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t"};
static std::string alfabet_5[26] = {"a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","y","x","z"};
int times = 50;
static std::string *tab[5] = {alfabet_1,alfabet_4,alfabet_3,alfabet_4,alfabet_5};

void generateMersenneFiles() {
    
    uint32_t seed = time(NULL);
    const char* files[5] = {"/Users/Janek/Documents/Studia/TiK/MersenneRandomGenerator/MersenneRandom/MersenneRandom/mt_1.txt","/Users/Janek/Documents/Studia/TiK/MersenneRandomGenerator/MersenneRandom/MersenneRandom/mt_2.txt","/Users/Janek/Documents/Studia/TiK/MersenneRandomGenerator/MersenneRandom/MersenneRandom/mt_3.txt","/Users/Janek/Documents/Studia/TiK/MersenneRandomGenerator/MersenneRandom/MersenneRandom/mt_4.txt","/Users/Janek/Documents/Studia/TiK/MersenneRandomGenerator/MersenneRandom/MersenneRandom/mt_5.txt"};
    
    MersenneGeneratorConfiguration *configuration = new MersenneGeneratorConfiguration();
    MersenneGenerator *generator = new MersenneGenerator(configuration, seed);
    
    std::fstream myfile;
    
    for(int j=0 ;j<5;j++) {
        myfile.open(files[j], std::fstream::binary | std::fstream::in | std::fstream::out | std::fstream::trunc);
        myfile.flush();
        for(int i=0 ;i<times;i++) {
            std::string rand = tab[j][generator->mersenneRandomGeneratedNumberWithUpperBound(alfabet_length[j])];
            std::cout << &myfile;
            myfile << rand << std::endl;
        }
        myfile.close();
    }
}

////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

void generateMinSTDRandom() {
    
    uint32_t seed = time(NULL);
    
    const char* files[5] = {"/Users/Janek/Documents/Studia/TiK/MersenneRandomGenerator/MersenneRandom/MersenneRandom/minSTD_1.txt","/Users/Janek/Documents/Studia/TiK/MersenneRandomGenerator/MersenneRandom/MersenneRandom/minSTD_2.txt","/Users/Janek/Documents/Studia/TiK/MersenneRandomGenerator/MersenneRandom/MersenneRandom/minSTD_3.txt","/Users/Janek/Documents/Studia/TiK/MersenneRandomGenerator/MersenneRandom/MersenneRandom/minSTD_4.txt","/Users/Janek/Documents/Studia/TiK/MersenneRandomGenerator/MersenneRandom/MersenneRandom/minSTD_5.txt"};
    
    std::fstream myfile;
    
    for(int j=0 ;j<5;j++) {
        myfile.open(files[j], std::fstream::binary | std::fstream::in | std::fstream::out | std::fstream::trunc);
        myfile.flush();
        std::minstd_rand gen(seed);
        std::uniform_int_distribution<> distr(0, alfabet_length[j]);
        for(int i=0 ;i<times;i++) {
            std::string rand = tab[j][distr(gen)];
            std::cout << rand << std::endl;
            myfile << rand << std::endl;
        }
        myfile.close();
    }
}

////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

void generateKnuthRandom() {
    uint32_t seed = time(NULL);
    
    const char* files[5] = {"/Users/Janek/Documents/Studia/TiK/MersenneRandomGenerator/MersenneRandom/MersenneRandom/knuth_1.txt","/Users/Janek/Documents/Studia/TiK/MersenneRandomGenerator/MersenneRandom/MersenneRandom/knuth_2.txt","/Users/Janek/Documents/Studia/TiK/MersenneRandomGenerator/MersenneRandom/MersenneRandom/knuth_3.txt","/Users/Janek/Documents/Studia/TiK/MersenneRandomGenerator/MersenneRandom/MersenneRandom/knuth_4.txt","/Users/Janek/Documents/Studia/TiK/MersenneRandomGenerator/MersenneRandom/MersenneRandom/knuth_5.txt"};
    
    std::knuth_b knuth(seed);
    std::fstream myfile;
    
    for(int j=0 ;j<5;j++) {
        myfile.open(files[j], std::fstream::binary | std::fstream::in | std::fstream::out | std::fstream::trunc);
        int alphabetLength = alfabet_length[j];
        for(int i=0 ;i<times;i++) {
            std::string rand = tab[j][knuth() % alphabetLength];
            myfile << rand << std::endl;
        }
        myfile.close();
    }
}


////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

int main(int argc, const char * argv[]) {
    
//    generateMersenneFiles();
//    generateMinSTDRandom();
    generateKnuthRandom();
   
    return 0;
}



