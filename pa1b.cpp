#include "hash24.h"
#include "dictionary.h"
using namespace std;

int main( int argc, char** argv ){

    Dictionary dict = Dictionary(argv[2], argv[1]);

    
    cout<< "Number of words = " << dict.get_input_size() << endl;
    cout<< "Table size = " << dict.get_primary_arr_size() << endl;
    cout<< "Max collisions = " << dict.max_num_collision() << endl;
    dict.print_primary_slots();
    dict.most_pop_bucket_words();

}