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
#define out_file "qsort_comp_results.txt" // defines the output file to be the one containing the number of comparisons

// configuration 2: experimenting for execution time results
#elif exp_time == 1
#define INC(x) // the increment function is simply removed (replaced by nothing)
#define LOG_RESULT LOG(execution_time) // logs the execution time to the output file
#define out_file "qsort_time_results.txt" // defines the output file to be the one containing execution times
#endif


// Recursive Quick Sort partitions the elements taking the first element as pivot
// and makes subsequent quicksort calls on the partitioned parts.
void qsort(unsigned long long int* begin,
           unsigned long long int* end,
           long long int& comparisons_count) {

    // invariant: elements in [begin, begin+left_pointer), [begin+left_pointer, begin+middle_pointer) are less than
    // the pivot and equal to the pivot, respectively. elements in [begin+right_pointer, end) are greater than the pivot.
    long long int size = end - begin, left_pointer = 0, middle_pointer = 1, right_pointer = size;

    // if there is nothing to sort
    if(size <= 1)
        return;

    // otherwise, the array is partitioned into three parts (less than pivot, equal to pivot, and greater than pivot).
    unsigned long long int pivot = *begin, current_element;
    // the invariant above is satisfied: loop ends when middle_pointer = right_pointer
    while(middle_pointer < right_pointer) {
        current_element = *(begin + middle_pointer); // element to be inserted into the correct partition
        INC(comparisons_count); // a comparison of pivot and current element occurs
        if(current_element < pivot) {
            // current_element is placed in the first partition and both left_pointer and middle_pointer increment
            *(begin + middle_pointer++) = *(begin + left_pointer);
            *(begin + left_pointer++) = current_element;
        }
        else if(current_element == pivot)
            // current_element is already placed in the correct partition, middle_pointer increments
            middle_pointer++;
        else {
            // current_element > pivot, belongs in the third partition
            while (middle_pointer<right_pointer and *(begin+(--right_pointer)) > pivot) // find the first element from the right not greater than the pivot
                INC(comparisons_count); // *(begin+right_pointer) and pivot is compared
            if(middle_pointer<right_pointer) {
                INC(comparisons_count); // the last comparison in the while loop is counted here and the same comparison follows
                if(*(begin+right_pointer) == pivot) {
                    // *(begin+right_pointer) belongs in the second partition
                    *(begin + middle_pointer++) = *(begin + right_pointer);
                    *(begin + right_pointer) = current_element;
                }
                else {
                    // *(begin+right_pointer) belongs in the first partition
                    *(begin + middle_pointer++) = *(begin + left_pointer);
                    *(begin + left_pointer++) = *(begin + right_pointer);
                    *(begin + right_pointer) = current_element;
                }
            }
            // else, if middle_pointer = right_pointer, the array has been partitioned.
        }
    }
    // successive calls
    qsort(begin, (begin+(left_pointer)), comparisons_count);
    qsort((begin+right_pointer), end, comparisons_count);
}


//main method
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
        qsort(&array[0], &array[1e6], comparisons_count);
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