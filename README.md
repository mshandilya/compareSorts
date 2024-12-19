# A Comparative Study of Merge Sort and Quick Sort

This repository consists of the supplementary material for the report by the same title. While the source files are well-commented and self-explanatory, we shall cover a few key aspects of the programs which were useful for the purposes of our experimentation and also discuss the steps to execute the experiments should one aim to reproduce the results.

## Preprocessor Macros support for different experiment configurations

We perform experiments to:
 1. Record the execution time of each of the methods
 2. Record the number of comparisons for each of the methods

While both of these goals seem independent and thus could be performed simultaneously, keeping track of the number of comparisons might ever so slightly impact the execution time of the methods. Therefore, we introduce two experiment configurations, one for each of the goals. These configurations are set as preprocessor macros in order to not affect the execution time of the methods. There are specifically three preprocessor macros dependent on preprocessor macro `exp_time` denoting the first configuration when it is set to `1` and the second configuration when set to `0`:
 - `INC(x)`: This macro expands to literally nothing when running the first configuration and to `x++` when running the second configuration.
 - `out_file`: This macro expands to the correct output file destination depending on the experiment configuration.
 - `LOG_RESULT`: This macro logs the desired value (depending on the experiment configuration) to the `out_file`.

## Reproduction of the results using the files

 1. Begin by first generating the experiment inputs. Use the `generate_tests.cpp` file to generate the inputs in the "appropriate file", of "appropriate size", and "appropriate number of times" as decided by the user.
 2. Next, run the file `msort.cpp` on the corresponding inputs twice, once with the macro `exp_time` set to `1` and another time with it set to `0`.
 3. Similarly, run the file `qsort.cpp` on the corresponding inputs twice, once with the macro `exp_time` set to `1` and another time with it set to `0`.

One can then use the results as per their liking to perform some analysis.
