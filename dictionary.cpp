#include "dictionary.h"

Dictionary::Dictionary(string fname, string paramFileName){
    
    set_primes_and_primArraySize(paramFileName);

    h1 = set_hash24(prime_a, prime_b, prime_c);
    
    h1.dump();
    
}


void Dictionary::set_primes_and_primArraySize(string cfile){
    string line;
    ifstream cF;
    cF.open(cfile.c_str());
    cF >> primary_array_size >> prime_a >> prime_b >> prime_c;
    cF.close();
}

Hash24 Dictionary::set_hash24(unsigned long a,unsigned long b,unsigned long c){
    return Hash24(a, b, c);
}

void Dictionary::collisiontable(string inFile){
    int *collisionarr = new int[primary_array_size];
    string line;
    ifstream inF;
    inF.open(inFile.c_str());
    for(int i = 0; i < primary_array_size; i++){
        collisionarr[i] = 0;
    }
    input_size  = 0;
    while(getline(inF,line)){
        size_t indx = h1.hash(line);
        collisionarr[indx] += 1;
        input_size +=1;
        
    }
    inF.close();
    
    collision_ptr = collisionarr;
}

void Dictionary::createPrimaryArr(string inFile){
    string** hash_Main_Arr = new string* [primary_array_size];
    hash_table = hash_Main_Arr;
    for (int i = 0; i < primary_array_size; i++){
        if (collision_ptr[i]== 0){
            hash_Main_Arr[i] = NULL;
        }else{
            hash_Main_Arr[i] = new string [collision_ptr[i]];
        }
    }
}