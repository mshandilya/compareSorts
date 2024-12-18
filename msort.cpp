//required macros and template
#include <bits/stdc++.h>

#define t0 std::chrono::high_resolution_clock::from_time_t(0)-std::chrono::high_resolution_clock::from_time_t(0) // denotes time zero
#define LOG(x) fout<<x<<"\n" // function for logging x to the output file

// macros for different preprocessor configurations
#define exp_time 0

// configuration 1: experimenting for number of comparisons results
#if exp_time == 0
#define INC(x) x++ // the increment function takes increments the value of the argument by 1
#define LOG_RESULT LOG(comparisons_count) // logs the number of comparisons to the output file
#define out_file "msort_comp_results.txt" // defines the output file to be the one containing the number of comparisons

// configuration 2: experimenting for execution time results
#elif exp_time == 1
#define INC(x) // the increment function is simply removed (replaced by nothing)
#define LOG_RESULT LOG(execution_time) // logs the execution time to the output file
#define out_file "msort_time_results.txt" // defines the output file to be the one containing execution times
#endif


// Merges two subarrays of an array represented by the pointers [begin, mid) and [mid, end)
// into the auxiliary array represented by the pointer aux_begin
void merge(const unsigned long long int* begin,
           const unsigned long long int* mid,
           const unsigned long long int* end,
           unsigned long long int* aux_begin,
           long long int& comparisons_count) {

    unsigned long long int merged_index = 0, left_index = 0, right_index = 0;

    // if there is nothing to merge
    if(end-begin < 1) {
        return;
    }

    // if the sequence is already sorted
    if(mid==end or *(mid-1) <= *mid) {
        if(mid!=end)
            INC(comparisons_count); // the elements at mid-1 and mid have been compared
        while ((begin + merged_index) != end)
            *(aux_begin + merged_index) = *(begin + merged_index++); // copying the elements
        return;
    }
    INC(comparisons_count); // the elements at mid-1 and mid have been compared

    // merging is required --> positions of the first unprocessed elements are denoted by left_index and right_index
    while((begin + left_index) != mid and (mid + right_index) != end) {
        // choosing the smaller element and placing it next in the auxiliary array
        if(*(begin + left_index) < *(mid + right_index))
            *(aux_begin + merged_index++) = *(begin + left_index++);
        else
            *(aux_begin + merged_index++) = *(mid + right_index++);
        INC(comparisons_count); // the elements at begin+left_index and mid+right_index are compared
    }
    // adding the remaining elements from either subarray (only one of the subarrays is not fully processed)
    while((begin + left_index) != mid)
        *(aux_begin + merged_index++) = *(begin + left_index++); // copying the elements
    while((mid + right_index) != end)
        *(aux_begin + merged_index++) = *(mid + right_index++); // copying the elements
}


// Iterative Merge Sort function to sort array[0...n-1]
void msort(std::vector<unsigned long long int>& array,
           long long int& comparisons_count) {

    unsigned long long int size = (unsigned long long int) array.size(), current_size = 1, iterations = 0, left, mid, right;
    std::vector<unsigned long long int> auxiliary_array(size);

    // merge subarrays in a bottom-up manner.
    // current_size denotes the current size of sorted subarrays.
    for (; current_size < size; current_size = 2 * current_size) {
        // left denotes the starting point of the newly merged subarray.
        for (left = 0; left < size; left += 2 * current_size) {
            // mid and end denote the middle point and the ending point of the newly merged subarray, respectively.
            mid = std::min(left + current_size, size);
            right = std::min(left + 2 * current_size, size);
            // merging into either the original array or the auxiliary array depending on the currently sorted array.
            if(iterations&1) // if it is an odd iteration (the sorted array is in the auxiliary array)
                merge(&auxiliary_array[left], &auxiliary_array[mid], &auxiliary_array[right], &array[left], comparisons_count);
            else
                merge(&array[left], &array[mid], &array[right], &auxiliary_array[left], comparisons_count);
        }
        // iterations help keep track of the currently sorted array.
        iterations++;
    }

    // if the currently sorted array is the auxiliary array, copy its contents to the original array.
    if(iterations&1)
        for(unsigned long long int ind = 0; ind<size; ind++)
            array[ind] = auxiliary_array[ind];
}


// main method
int main() {
    // defining input & output streams
    std::ifstream fin("arrays_1e6_e.txt");
    std::ofstream fout(out_file, std::ios::app);

    std::chrono::time_point<std::chrono::high_resolution_clock> start, stop; // beginning and ending time points of the sort function call
    std::chrono::duration<long long int, std::ratio<1, (long long int) 1e9>> execution_time = t0, total_time = t0; // initialized with time zero
    std::vector<unsigned long long int> array(1000000); // array storing the array to be sorted
    long long int trial = 0, max_trials = 200, comparisons_count, total_comp_count = 0;
    while(trial++ < max_trials) {
        // loading the array from the input data file
        for (int i = 0; i < 1000000; i++)
            fin >> array[i];
        // resetting comparisons_count
        comparisons_count = 0;
        start = std::chrono::high_resolution_clock::now(); // recording time before function call
        msort(array, comparisons_count);
        stop = std::chrono::high_resolution_clock::now(); // recording time after function call
        execution_time = stop - start; // calculating net execution time
        // correctness check
        if(!is_sorted(array.begin(), array.end())) {
            std::cout << "Incorrect result on iteration " << trial << std::endl;
            exit(0);
        }
        LOG_RESULT; // logging the appropriate result to the output file
        total_comp_count += comparisons_count; 
        total_time += execution_time;
    }
    std::cout << "Mean comparisons performed:  " << ((long double)total_comp_count) / max_trials << std::endl;
    std::cout << "Mean time taken per sorting: " << total_time / ((long double)max_trials) << std::endl;
    return 0;
}