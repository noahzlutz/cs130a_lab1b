#include "dictionary.h"

Dictionary::Dictionary(string fname, string paramFileName){
    
    set_primes_and_primArraySize(paramFileName);

    h1 = set_hash24(prime_a, prime_b, prime_c);
    
    h1.dump();

    collisiontable(fname);

    cout<< "Make hash function array:"<<endl;
    make_hash_func_arr();

    cout<< "Make primary array:"<<endl;
    createPrimaryArr(fname);

    cout<< "Make correct array:"<<endl;
    find_correct_hashes();

}

Dictionary::~Dictionary(){}

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

int Dictionary::get_input_size(){
    return input_size;
}

int Dictionary::get_primary_arr_size(){
    return primary_array_size;
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
        int indx = h1.hash(line);
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
    cout<< "Main array made" <<endl;
    cout<< "Starting secondary tables:" <<endl;


    string line;
    ifstream inF;
    inF.open(inFile.c_str());

    //makes tmp array store words 
    words_in_table = 0;
    while(getline(inF,line)){
        //bool chk = check_key_exist(line);

        int key = (h1.hash(line) % primary_array_size);
        string* itr  = hash_table[key];
            for(int i = 0; i < collision_ptr[key]; i++){
                if(hash_Main_Arr[key][i] == ""){
                    hash_Main_Arr[key][i] = line;
                    break;
                }
            }
            words_in_table += 1;

        /*
        if(chk == false){
            //cout<< line << " is " << key <<endl;
            string* itr  = hash_Main_Arr[key];
            for(int i = 0; i < collision_ptr[key]; i++){
                if(hash_Main_Arr[key][i] == ""){
                    hash_Main_Arr[key][i] = line;
                    break;
                }
            }
            words_in_table += 1;
        }else{
            string* tmp  = hash_Main_Arr[key];
            hash_Main_Arr[key] = new string [collision_ptr[key]-1];
            for(int i =0; i < collision_ptr[key]-1; i++){
                hash_Main_Arr[key][i] = tmp[i];
            }
            collision_ptr[key]  -=1;
        }*/
    }
    inF.close();
    cout<< "Secondary tables made" <<endl;

}

void Dictionary::make_hash_func_arr(){
    hash_func_arr = new Hash24*[primary_array_size];
}


void Dictionary::find_correct_hashes(){
    
    for (int j = 0; j < primary_array_size; j++){
        if(hash_table[j] != NULL){
            bool corr = false;
            Hash24* h_corr;
            string* corr_ptr;
            while(!corr){
                string* tmp_ptr = new string[collision_ptr[j]*collision_ptr[j]];
                Hash24* h2 = new Hash24(prime_a, prime_b, prime_c);
                bool corr2 = true;
                for(int k = 0; k < collision_ptr[j]; k++){
                    size_t key = (*h2).hash(hash_table[j][k])%collision_ptr[j];
                    if(tmp_ptr[key] != ""){
                        corr2 =false;
                        delete[] h2;
                        break;
                    }
                }
                if(corr2 == true){
                    corr = true;
                    h_corr = h2;
                    corr_ptr = tmp_ptr;
                }
            }
            delete[] hash_table[j];
            hash_func_arr[j] = h_corr;
            hash_table[j] = corr_ptr;
        }
        
    }
}


int Dictionary::max_num_collision(){
    int max  = collision_ptr[0];
    for (int i = 0; i < primary_array_size; i++){
        if(collision_ptr[i] > max){
            max = collision_ptr[i];
            most_pop_bucket_idx = i;
        }
    }
    if(max > 0){
        max = max-1;
    }
    return max;
}
