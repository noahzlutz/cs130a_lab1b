#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "hash24.h"

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Dictionary{

    public:
        Dictionary(string fname, string paramFileName);

        bool find(string word);

        ~Dictionary();

        int get_input_size(); //done

        int get_number_of_words();

        int get_primary_arr_size(); //done

        void print_hash_buckets();

        void check_queries(string Qfile);

        int max_num_collision(); //done

        void most_pop_bucket_words();

        void createPrimaryArr(string inFile);

    
    private:

        Hash24* h1;

        size_t primary_array_size; 

        unsigned long prime_a;
        
        unsigned long prime_b;

        unsigned long prime_c;

        int* collision_ptr;

        int input_size;

        int most_pop_bucket_idx;

        int words_in_table;

        string** hash_table;

        Hash24** hash_func_arr;

        void set_primes_and_primArraySize(string cfile); //done
        
        Hash24* set_hash24(unsigned long a,unsigned long b,unsigned long c); //done

        void collisiontable(string inFile); //done

        void hash_func_table();

        void make_hash_func_arr();

        void find_correct_hashes();



};


#endif