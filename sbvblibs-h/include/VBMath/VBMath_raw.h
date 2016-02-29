/*///////////////////////////////////////////////////////////////////
VBMath_raw.h
VBMath - The Villas-Boas library for mathematics in C++ cross platform
LGPL licenced
VBMath is part of sbvblibs

Download sbvblibs from link below
http://code.google.com/p/sbvblibs/

http://www.sbvb.com.br 
by Sergio B. Villas-Boas (sbvb@poli.ufrj.br)
///////////////////////////////////////////////////////////////////*/

#ifndef __VBATH_H
#define __VBATH_H


////////////////////////////////////////////////////////////////////
// integer math global functions
/////////////////////////////////////////////////////////////////////

namespace br {
    namespace com {
        namespace sbVB {
            namespace VBMath {

                // return true if double or float is NaN

                template <typename T>
                bool sbVB_isnan(T var) {
                    volatile double d = var;
                    return d != d;
                };

                template <typename IntType, typename Container>
                void createPrimesContainer(Container & primesContainer,
                        IntType limit) {
                    typename Container::iterator it;
                    primesContainer.push_back(2); // first hardcoded prime
                    primesContainer.push_back(3); // second hardcoded prime
                    IntType currNumber = 3;
                    if (limit > 3) {
                        // add primes until limit
                        while (currNumber <= limit) {
                            bool currNumberIsPrime = true;
                            for (it = primesContainer.begin(); it != primesContainer.end(); it++) {
                                if (currNumber % *it == 0) {
                                    currNumberIsPrime = false;
                                    break; // noo need to keep searching for currNumber
                                }
                            }
                            if (currNumberIsPrime) {
                                primesContainer.push_back(currNumber);
                                // cout << "DEBUG: added prime: " << currNumber << endl;
                            }
                            currNumber += 2;
                        }
                    }
                };

                template <typename IntType, typename Container>
                void createPrimesFile(IntType limit, const char *fileName) {
                    Container primesContainer; // list of primes in memory
                    typename Container::iterator it;
                    createPrimesContainer(primesContainer, limit);

                    // save primes to file
                    std::ofstream primesFile;
                    primesFile.open(fileName);
                    if (!primesFile)
                        throw VBMathException(br::com::sbVB::VBLib::VBString("could not open file ") + br::com::sbVB::VBLib::VBString(fileName));
                    for (it = primesContainer.begin(); it != primesContainer.end(); it++) {
                        primesFile << *it << std::endl;
                    }
                };

                template <typename IntType, typename Container>
                void loadPrimesFile(const char *fileName, Container & primesContainer) {
                    primesContainer.clear();
                    std::ifstream primesFile;
                    primesFile.open(fileName);
                    if (!primesFile)
                        throw VBMathException(br::com::sbVB::VBLib::VBString("could not open file ")
                            + br::com::sbVB::VBLib::VBString(fileName));
                    IntType currPrime;
                    while (true) {
                        primesFile >> currPrime;
                        if (primesFile.eof()) break;
                        primesContainer.push_back(currPrime);
                    }
                };

                static void VBMath_static_functions_test() {
                    using namespace std;
                    using namespace br::com::sbVB::VBLib;
                    cout << "== VBMath_static_functions_test()" << endl;
                    int limitPrimes = 100;
                    deque<int> primesContainer;
                    createPrimesContainer<int, deque<int> >
                            (primesContainer, limitPrimes);
                    deque<int>::iterator it;
                    int firstPrimes[] = {
                        2, 3, 5, 7, 11, 13, 17, 19,
                        23, 29, 31, 37, 41, 43, 47,
                        53, 59, 61, 67, 71, 73, 79,
                        83, 89, 97
                    };
                    int nprimes = sizeof (firstPrimes) / sizeof (int);
                    int i = 0;
                    for (it = primesContainer.begin();
                            it != primesContainer.end(); it++, i++) {
                        // cout << *it << endl;
                        VBAssert(firstPrimes[i] == primesContainer[i]);
                    }

                    const char *primesFile = "first100primes.txt";
                    createPrimesFile<int, std::deque<int> >
                            (limitPrimes, primesFile);


                    std::deque<int> primesContainer2;
                    loadPrimesFile<int, std::deque<int> >
                            (primesFile, primesContainer2);
                    i = 0;
                    for (it = primesContainer.begin();
                            it != primesContainer.end(); it++, i++) {
                        // cout << *it << endl;
                        VBAssert(firstPrimes[i] == primesContainer2[i]);
                    }
                }

                static void test() {
                    using namespace std;
                    using namespace br::com::sbVB::VBLib;
                    std::cout << "=== VBMath_test()" << std::endl;
                    VBMath_static_functions_test();
                    VBMatrix<float>::test();
                    VBMatrix<double>::test();
                    VBMatrix<long double>::test();

                }


            }
        }
    }
} // close namespace ::br::com::sbVB::VBMath

#endif // __VBMATH_H






