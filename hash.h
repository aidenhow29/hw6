#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
      unsigned long long w[5] = {0,0,0,0,0}; // starts off empty ofc

      int len = static_cast<int>(k.length());
      int group = 4; 

      for(int i = len - 1; i >= 0 && group >= 0; --group){
        unsigned long long value = 0;
        unsigned long long power = 1;

        for(int j = 0; j < 6 && i >= 0; ++j, --i){
          char c = k[i];
          HASH_INDEX_T num = letterDigitToNumber(c);
          value += num * power;
          power *= 36; // base 36
        }

        w[group] = value;

      }

      unsigned long long finalHash = 0;
      for(int i = 0; i < 5; ++i){
        finalHash += rValues[i] * w[i];
      }

      return finalHash;

    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        if(letter >= 'A' && letter <= 'Z'){ // upper case
          letter = letter - 'A' + 'a'; // to lowercase
        }
        if(letter >= 'a' && letter <= 'z'){ // is it a letter
          return letter - 'a';
        }
        else if(letter >= '0' && letter <= '9'){ //handles numbers
          return 26 + (letter - '0');
        }
        return 0;
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
