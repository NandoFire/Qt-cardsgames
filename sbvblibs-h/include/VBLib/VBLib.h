// VBLib.h 
#ifndef _VBLIB_H_
#define _VBLIB_H_

/**************************************************************** 
VBLib stands for "Villas-Boas Library"
by sbVB: Sergio Barbosa Villas-Boas (sbvb@sbvb.com.br)
sbVB home page: http://www.sbvb.com.br
All Cross-platforms C++ header-only libraries by sbVB
http://code.google.com/p/sbvblibs-h/
 ****************************************************************/

/////////////////////////////////////////////////////////////////////
//
// includes of VBLib
//
/////////////////////////////////////////////////////////////////////



#include <typeinfo> // typeid
#include <limits.h>
#include <exception>
#include <map>
#include <deque>
#include <complex> 
#include <iostream>
#include <iomanip>
#include <sstream> 
#include <fstream>
#include <string>
#include <cmath>  // fabs
#include <ctime>  // time
#include <cfloat> // DBL_EPSILON

#ifdef _MSC_VER  
// Visual C++ (windows) only begin
//	#include <crtdbg.h> // include necessary to handle memory leak debug (win32 only)
// line below removed to avoid bug with some compilers
//	#include <atlbase.h> // BSTR
#include <windows.h> // for sys info
//	#include <wincon.h> // to use wincon, link project with netapi32.lib
#include <stdint.h> // uint64_t
#pragma warning(disable:4290)
#pragma warning(disable:4018)
#pragma warning(disable:4244)
#pragma warning(disable:4800)
#pragma warning(disable:4101)
#pragma warning(disable:4996)
#pragma warning(disable:4305)
#pragma warning(disable:4309)
#pragma warning(disable:4700)

#else 
// unix only begin
#include <sys/stat.h> // struct stat, S_ISDIR
#include <dirent.h> // DIR
#include <unistd.h>
#include <sys/time.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
// unix only end
#endif

/////////////////////////////////////////////////////////////////////
//
// defines of VBLib
//
/////////////////////////////////////////////////////////////////////

// typedef complex<float> fcomplex;
// typedef complex<double> dcomplex;
// typedef complex<long double> dlcomplex;


// #define VB_SHOW(x) cout  << "DEBUG: " #x "=" << setprecision(20) << x << endl;
#define VB_SAFEDELETE(x) {if (x) {delete x; x=0;} }
#define VB_SAFEDELETE_A(x) {if (x) {delete [] x; x=0;} }
#ifndef NULL
#define NULL 0
#endif
#ifndef VB_SHOW
//#error "VB_SHOW to be defined"
#define VB_SHOW(x) std::cout  << "DEBUG: " #x "=" << std::setprecision(20) << x << std::endl;
#define VB_SHOW2(n,x) std::cout  << "DEBUG: " #n "=" << n << ", " #x "=" << std::setprecision(20) << x << std::endl;
#define VB_SHOW3(n1,n2,x) std::cout  << "DEBUG: " #n1 "=" << n1 << ", " #n2 "=" << n2 << ", " #x "=" << std::setprecision(20) << x << std::endl;
#define VB_SHOWT(x) br::com::sbVB::VBLib::VBLog::myout  << "DEBUG: " #x "=" << std::setprecision(20) << x << std::endl;
#define VB_SHOWT2(n,x) br::com::sbVB::VBLib::VBLog::myout  << "DEBUG: " #n "=" << n << ", " #x "=" << std::setprecision(20) << x << std::endl;
#define VB_SHOWT3(n1,n2,x) br::com::sbVB::VBLib::VBLog::myout  << "DEBUG: " #n1 "=" << n1 << ", " #n2 "=" << n2 << ", " #x "=" << std::setprecision(20) << x << std::endl;
#define VB_SHOW_P(x) std::cout << "DEBUG: " #x "=" \
<< "0x" << hex<< noshowbase << setw(16) << setfill('0')  << (long)x << std::endl;
#endif

////////////////////////////////////////////////////////////////////
//
// Definition of complex types
//
/////////////////////////////////////////////////////////////////////

typedef std::complex<float> VBComplex_F;
typedef std::complex<double> VBComplex_D;
typedef std::complex<long double> VBComplex_LD;


/////////////////////////////////////////////////////////////////////
//
// include modules of VBLib
//
/////////////////////////////////////////////////////////////////////

// all entities in namespace br::com::sbVB::VBLib
namespace br {
    namespace com {
        namespace sbVB {
            namespace VBLib {

                /////////////////////////////////////////////////////////////////////
                //
                // global functions
                //
                /////////////////////////////////////////////////////////////////////

#ifndef _VBLIB_H_GLOBAL_NOT_AGAIN_

                ////////////////////////////////////////////////////////////////////
                // functions from CXL

                char *strinc(const char *str1, char *str2) {
                    register unsigned max;
                    char *p;

                    max = strlen(str1);

                    for (p = str2; *p; p++) {
                        if (!strncmp(str1, p, max)) return (p);
                    }
                    return (NULL); /* string1 not found in string2 */
                }

                char *strins(const char *instr, char *str, unsigned st_pos) {
                    register unsigned i, leninstr;

                    /* get length of string to insert */
                    leninstr = strlen(instr);

                    /* shift affected portion of str text to the right */
                    for (i = strlen(str); i >= st_pos; i--) *(str + leninstr + i) = *(str + i);

                    /* insert instr text */
                    for (i = 0; i < leninstr; i++) *(str + st_pos + i) = *(instr + i);

                    /* return address of modified string */
                    return (str);
                }

                char *strdel(const char *substr, char *str) {
                    char *src, *dest;

                    dest = strinc(substr, str);
                    if (!dest) return (NULL);
                    src = dest + strlen(substr);
                    strcpy(dest, src);
                    return (str);
                }

                char *strsrep(char *str, const char *search, const char *replace) {
                    char *p;

                    if ((p = strinc(search, str)) != NULL) {
                        ::br::com::sbVB::VBLib::strdel(search, str);
                        ::br::com::sbVB::VBLib::strins(replace, str, (int) ((unsigned long) p - (unsigned long) str));
                        p = str;
                    }

                    return (p);
                }

                char *strschg(char *str, const char *find, const char *replace) {
                    register unsigned count = 0;
                    register char *p;

                    p = str;
                    while ((p = ::br::com::sbVB::VBLib::strinc(find, p)) != NULL) {
                        ::br::com::sbVB::VBLib::strsrep(p, find, replace);
                        // included by sbVB begin
                        p += (int) strlen(replace);
                        // included by sbVB end
                        count++;
                    }

                    if (count) return (str);
                    else return (NULL);
                    //    return(count?str:NULL);
                }



                // global variable to point to custom assert function

                void VBAssert(bool b, const char * message = "(undefined)") {
                    using namespace std;
                    if (!b) {
                        cout << "==========================================" << endl;
                        cout << "VBAssert fail: " << message << endl;
                        cout << "==========================================" << endl;
                    }
                }

                //  DWORD CPU_info();
                //  VBString getSystemHash();

                ////////////////////////////////////////////////////////////////////
                // other global functions

                bool nearEqual(double x, double y, double eps) {
                    return fabs(x - y) < eps;
                }




#else
                char *strinc(const char *str1, char *str2);
                char *strins(const char *instr, char *str, unsigned st_pos);
                char *strdel(const char *substr, char *str);
                char *strsrep(char *str, const char *search, const char *replace);
                char *strschg(char *str, const char *find, const char *replace);

                // global variable to point to custom assert function

                void VBAssert(bool b, const char * message = "(undefined)");
                bool nearEqual(double x, double y, double eps);

#endif

                template <typename T>
                T VBmin(T x, T y) {
                    if (x < y)
                        return x;
                    return y;
                };

                template <typename T>
                T VBmax(T x, T y) {
                    if (x > y)
                        return x;
                    return y;
                };

            }
        }
    }
} // close namespace ::br::com::sbVB::VBLib


#include "VBLib/VBString.h" // before VBMD5, before VBException, because it uses VBString
#include "VBLib/VBException.h" // before the others, to allow derived classes


// prototypes after the inclusion of VBString
namespace br {
    namespace com {
        namespace sbVB {
            namespace VBLib {

#ifndef _VBLIB_H_GLOBAL_NOT_AGAIN_

                // Example: in = 15, return 'F'
                // Example: in = 3, return = '3'
                // p_ToAscii, p_ToAsciiReverse

                unsigned char charInt2ascii(unsigned char in) {
                    unsigned char z = toupper(in);
                    if (z < 10)
                        z += '0';
                    else
                        z += 'A' - 10;
                    return z;
                }

                // Example: in = 'F', return = 15
                // Example: in = '3', return = 3
                // p_ToAscii, p_ToAsciiReverse

                unsigned char charInt2asciiReverse(unsigned char in) {
                    unsigned char z = toupper(in);
                    if (z >= '0' && z <= '9')
                        z -= '0';
                    if (z >= 'A' && z <= 'F')
                        z -= 'A' - 10;
                    return z;
                }


                // Example: in = 15, return "0F" 
                // p_byteToAscii

                VBString charInt2asciiString(unsigned char in) {
                    const char chars[] = "0123456789ABCDEF";
                    ::br::com::sbVB::VBLib::VBString ret;
                    unsigned char msb;
                    msb = (in & 0xf0) / 16;
                    ret += chars[msb];
                    unsigned char lsb;
                    lsb = (in & 0x0f);
                    ret += chars[lsb];
                    return ret;
                }

                // Example: in = "0F", return 15
                // Example: in = "1F", return 31

                unsigned char asciiString2charInt(::br::com::sbVB::VBLib::VBString in) {
                    unsigned char ret = charInt2asciiReverse(in[0]) * 16 +
                            charInt2asciiReverse(in[1]);
                    return ret;
                }

                // Example: in = 'A',  out = "41"
                // p_toHex

                VBString ascii2charIntString(unsigned char in) {
                    ::br::com::sbVB::VBLib::VBString ret;
                    unsigned char a;
                    a = (in & 0xf0) / 16;
                    ret += ::br::com::sbVB::VBLib::charInt2ascii(a);
                    ; // MSB
                    a = (in & 0x0f);
                    ret += ::br::com::sbVB::VBLib::charInt2ascii(a); // LSB
                    return ret;
                }

                // Example: in = "41",  return = 'A'
                // p_toHexReverse

                unsigned char charIntString2ascii(::br::com::sbVB::VBLib::VBString in) {
                    unsigned char ret;
                    int msb, lsb;
                    msb = ::br::com::sbVB::VBLib::charInt2ascii(in[0]);
                    lsb = ::br::com::sbVB::VBLib::charInt2ascii(in[1]);
                    ret = lsb + msb * 16;
                    return ret;
                }

                bool fileExist(const char *fileName) {
                    std::ifstream testFile;
                    testFile.open(fileName);
                    if (!testFile)
                        return false;
                    else {
                        testFile.close();
                        return true;
                    }
                }

                void getFileContentsToString(const char *fileName, VBString & contents)
                throw (::br::com::sbVB::VBLib::VBException) {
                    std::ifstream textFile;
                    textFile.open(fileName);
                    if (!textFile) {
                        VBString message = "could not open file ";
                        message += fileName;
                        throw VBException(message);
                    }

                    contents = "";
                    VBString aux;

                    while (true) {
                        textFile >> aux;
                        if (textFile.eof() && aux.IsEmpty()) break;
                        contents += aux + "\n";
                    }

                }

                bool isSpaceChar(char c) {
                    char spaceChars[] = {' ', '\t', '\n', '\b', 0};
                    unsigned len = sizeof (spaceChars) / sizeof (char);

                    for (unsigned i = 0; i < len; i++) {
                        if (c == spaceChars[i])
                            return true;
                    }
                    return false;
                }

                void VBLib_static_functions_test() {
                    using namespace std;
                    std::cout << "== VBLib_static_functions_test()" << std::endl;

                    VBAssert(isSpaceChar(' '));
                    VBAssert(isSpaceChar('\t'));
                    VBAssert(isSpaceChar('\b'));
                    VBAssert(isSpaceChar('\n'));
                    VBAssert(!isSpaceChar('_'));

                    //VBAssert(charIntString2ascii("41")=='A');
                    //cout << ascii2charIntString('A') << endl;
                    // cout << charIntString2ascii("41") << endl;

                    VBAssert(charInt2asciiString(1) == "01");
                    VBAssert(charInt2asciiString(5) == "05");
                    VBAssert(charInt2asciiString(10) == "0A");
                    VBAssert(charInt2asciiString(12) == "0C");
                    VBAssert(charInt2asciiString(15) == "0F");

                    VBAssert(asciiString2charInt("01") == 1);
                    VBAssert(asciiString2charInt("05") == 5);
                    VBAssert(asciiString2charInt("0A") == 10);
                    VBAssert(asciiString2charInt("0F") == 15);

                    VBAssert(charInt2ascii(1) == '1');
                    VBAssert(charInt2ascii(10) == 'A');

                    const char *fileName = "__VBLib_test.txt";
                    std::ofstream outTestFile;
                    outTestFile.open(fileName);
                    outTestFile << "111" << endl;
                    outTestFile << "222" << endl;
                    outTestFile << "333" << endl;
                    outTestFile << "444" << endl;
                    outTestFile.close();
                    VBAssert(fileExist(fileName));

                    VBString allFileContents;
                    getFileContentsToString(fileName, allFileContents);
                    // cout << allFileContents << endl;
                    VBAssert(allFileContents == "111\n222\n333\n444\n");

                }
#else
                unsigned char charInt2ascii(unsigned char in);
                unsigned char charInt2asciiReverse(unsigned char in);
                VBString charInt2asciiString(unsigned char in);
                unsigned char asciiString2charInt(::br::com::sbVB::VBLib::VBString in);
                VBString ascii2charIntString(unsigned char in);
                unsigned char charIntString2ascii(::br::com::sbVB::VBLib::VBString in);
                bool fileExist(const char *fileName);
                void getFileContentsToString(const char *fileName, VBString & contents)
                throw (::br::com::sbVB::VBLib::VBException);
                bool isSpaceChar(char c);
                void VBLib_static_functions_test();
#endif
            }
        }
    }
} // close namespace ::br::com::sbVB::VBLib



#include "VBLib/VBClock.h"
#include "VBLib/VBList.h" // deprecated, use stl list instead
#include "VBLib/VBShowSTLContainer.h"
#include "VBLib/VBBinaryData.h" // before VBMD5
#include "VBLib/VBMD5.h"
#include "VBLib/VBDate.h"
#include "VBLib/VBFileDirectory.h"
#include "VBLib/VBCrossDLL.h"
#include "VBLib/VBLog.h"
#include "VBLib/VBDataRange.h"
// #include "VBLib/VBProcessArgs.h"



// prototypes after the inclusion of VBString and VBException
namespace br {
    namespace com {
        namespace sbVB {
            namespace VBLib {

                static void test() {
                    std::cout << "=== VBLib_test()" << std::endl;
                    //                    VBLib_static_functions_test();
                    //                    VBString::test();
                    //                    VBException::test();
                    //                    VBClock::test();
                    //                    VBList<double>::test();
                    //                    VBList<VBString>::test();
                    //                    VBBinaryData::test();
                    //                    VBMD5::test();
                    //                    VBDate::test();
                    //                    // VBDateTime::test();
                    //                    VBLog::test();
                    //                    VBDataRange<double>::testMe();
                    //                    VBDataRangeContainer<double>::testMe();
                    VBSolutionContainer<double>::testMe();
                }

            }
        }
    }
} // close namespace ::br::com::sbVB::VBLib



#endif	// _VBLIB_H_

