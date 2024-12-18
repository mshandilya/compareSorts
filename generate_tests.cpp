//required macros and template
#include <bits/stdc++.h>

//main method
int main() {
    std::mt19937_64 rng; //random number generator
    std::ifstream fin("seed.txt");
    fin>>rng; // loading the last saved state of the random number generator
    std::ofstream fout_1e6("arrays_1e6.txt"); // file for storing the input data
    long long int max_iter = 2000, // number of trials
    size = 1e6;
    for(long long int iter = 0; iter<max_iter; iter++) {
        for(int index = 0; index<size; index++)
            fout_1e6<<rng()<<" "; // storing the numbers in the file
        fout_1e6<<"\n";
    }
    std::ofstream fout("seed.txt");
    fout<<rng; // saving the state of the random number generator
    return 0;
}