# leaktest

This package exists solely to demonstrate 'possible' memory leaks resulting from the use of RcppParallel::parallelFor. These are currently believed to be valgrind false positives (https://github.com/RcppCore/RcppParallel/issues/175). The C++ code is simplified from code in the package 'secr'.

`testfn` calls the C++ code and returns a numeric value. The original code pre-computed a set of distance-dependent capture probabilities, but in this function the inputs are arbitrary and fixed,
and the output is not interpretable (it remains constant at 237.7695).

From linux command prompt:
```
R -e "devtools::install_github('MurrayEfford/leaktest')"
R -d "valgrind --tool=memcheck --track-origins=yes --leak-check=full" --vanilla -e "leaktest::testfn()"
```