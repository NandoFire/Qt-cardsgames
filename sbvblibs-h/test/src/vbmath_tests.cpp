// vbmath_tests.cpp
#include <iostream>
using namespace std;

#define _VBLIB_H_GLOBAL_NOT_AGAIN_
#include "VBLib/VBLib.h"
using namespace br::com::sbVB::VBLib;


#include "VBMath/VBMath.h"
using namespace br::com::sbVB::VBMath;

void testVBMathException() {
    cout << "=== testVBMathException" << endl;
    try {
        throw VBMathException("VBMathException explanation");
    } catch (const VBMathException & e) {
        VBString explanation = e.getExplanation();
        VBAssert(explanation == "VBMathException explanation");
    }
}

void testNearEqual() {
    cout << "=== testNearEqual" << endl;
    // these tests are run only because of VBLib
    double eps = 1e-8;
    double d1, d2;
    d1 = 1.;
    d2 = 1. + eps;
    VBAssert(nearEqual(d1, d2, eps), "d1 not near equal to d2");
    d2 = 1. + 2 * eps;
    VBAssert(!nearEqual(d1, d2, eps), "d1 is near equal to d2");
    d2 = -1. - eps;
    VBAssert(!nearEqual(d1, d2, eps), "d1 is near equal to d2");

    d1 = 1e8;
    d2 = 1e8 + 2 * eps; // still no underflow truncation
    VBAssert(!nearEqual(d1, d2, eps), "d1 is near equal to d2");

    d1 = 1e9;
    d2 = 1e9 + 2 * eps; // underflow truncation
    VBAssert(nearEqual(d1, d2, eps), "d1 not near equal to d2");

}

void testCheckAMatrix() {
    cout << "=== testCheckAMatrix" << endl;
    /*=============================================
    a =
    1	2
    3	4
            =============================================*/
    VBMatrix_D myMatrix(2, 2);
    myMatrix(0, 0) = 1;
    myMatrix(0, 1) = 2;
    myMatrix(1, 0) = 3;
    myMatrix(1, 1) = 4;
    // cout << "DEBUG:" << endl << myMatrix << endl;

    VBMatrix_D expectedAnswer(2, 2);
    expectedAnswer(0, 0) = 1;
    expectedAnswer(0, 1) = 2;
    expectedAnswer(1, 0) = 3;
    expectedAnswer(1, 1) = 4;

    double eps = 1e-8;
    VBAssert(nearEqualMatrix(myMatrix, expectedAnswer, eps), "matrices are different");
}

void test_rmult() {
    cout << "=== test_rmult" << endl;
    VBMatrix_D oneMatrix(2, 2);
    oneMatrix(0, 0) = 1;
    oneMatrix(0, 1) = 2;
    oneMatrix(1, 0) = -1;
    oneMatrix(1, 1) = 2;

    // each element is muitiplied by 1.1;
    VBMatrix_D myAnswer = rmult<double>(oneMatrix, 1.1);

    VBMatrix_D expectedAnswer(2, 2);
    expectedAnswer(0, 0) = 1.1;
    expectedAnswer(0, 1) = 2.2;
    expectedAnswer(1, 0) = -1.1;
    expectedAnswer(1, 1) = 2.2;

    double eps = 1e-8;
    VBAssert(nearEqualMatrix(myAnswer, expectedAnswer, eps), "matrices are different");
}

void testInvertMatrix() {
    cout << "=== testInvertMatrix" << endl;
    /*=============================================
    a = [
    1	2
    -1	2
    ]
    inv(a)
    ans =
    0.5		-0.5
    0.25	0.25
            =============================================*/
    VBMatrix_D myMatrix(2, 2);
    myMatrix(0, 0) = 1;
    myMatrix(0, 1) = 2;
    myMatrix(1, 0) = -1;
    myMatrix(1, 1) = 2;
    // cout << "DEBUG: myMatrix=" << myMatrix << endl;

    VBMatrix_D myAnswer = myMatrix.inv();
    // cout << "DEBUG:" << endl << invMat << endl;
    // a = b*c+d*e;

    VBMatrix_D expectedAnswer(2, 2);
    expectedAnswer(0, 0) = 0.5;
    expectedAnswer(0, 1) = -0.5;
    expectedAnswer(1, 0) = 0.25;
    expectedAnswer(1, 1) = 0.25;

    double eps = 1e-8;
    VBAssert(nearEqualMatrix(myAnswer, expectedAnswer, eps), "matrice inverse error");
}

void testRegression() {
    cout << "=== testRegression" << endl;
    // y=[1 3 4 7 9 0.1];
    VBMatrix_D y(6, 1);
    y(0, 0) = 1;
    y(1, 0) = 3;
    y(2, 0) = 4;
    y(3, 0) = 7;
    y(4, 0) = 9;
    y(5, 0) = 0.1;
    // cout << "DEBUG y=" << y << endl;

    // x=[2 3 5 9 10 0.3];
    VBMatrix_D x(6, 1);
    x(0, 0) = 2;
    x(1, 0) = 3;
    x(2, 0) = 5;
    x(3, 0) = 9;
    x(4, 0) = 10;
    x(5, 0) = 0.3;
    // cout << "DEBUG x=" << x << endl;

    unsigned g = 2;
    VBMatrix_D A = polinomialRegressionMatrix(x, 2);
    // cout << "DEBUG A=" << A << endl;
    // cout << "pinv A=" << A.pinv() << endl;
    // cout << "y=" << y << endl;

    VBMatrix_D myAnswer = A.pinv() * y;
    // cout << "DEBUG a=" << a << endl;

    VBMatrix_D expectedAnswer(g, 1);
    expectedAnswer(0, 0) = -0.24560903409714;
    expectedAnswer(1, 0) = 0.87282096261375;
    // cout << "DEBUG expectedAnswer=" << expectedAnswer << endl;

    double eps = 1e-8;
    VBAssert(nearEqualMatrix(myAnswer, expectedAnswer, eps), "matrices are different");
}

void testGenericComplex() {
    cout << "=== testGenericComplex" << endl;
    complex<double> a(1.0, 1.0), b(2.0, -2.0);
    // b > a => gt(b,a)
    VBAssert(genGT(b, a));
    VBAssert(genGE(b, a));
    VBAssert(genGE(a, a));
    VBAssert(genGE(b, b));
}

void testInvertComplexMatrix() {
    cout << "=== testInvertComplexMatrix" << endl;
    /*=============================================
    format long
    a = [ (1+3j) (2+5j) ;
    (5-2j)  (-1+4j)]
    inv(a)
    ans =
    -0.03156480859637 - 0.10208193418402i  0.11148421759570 + 0.08394895903291i
    0.08394895903291 - 0.11148421759570i -0.06245802552048 - 0.05305574210880i
            =============================================*/

    VBMatrix_CD myMatrix(2, 2);
    myMatrix(0, 0) = VBComplex_D(1, 3);
    myMatrix(0, 1) = VBComplex_D(2, 5);
    myMatrix(1, 0) = VBComplex_D(5, -2);
    myMatrix(1, 1) = VBComplex_D(-1, 4);

    VBMatrix_CD myAnswer = myMatrix.inv();
    // cout << "DEBUG:" << endl << myAnswer << endl;

    VBMatrix_CD expectedAnswer(2, 2);
    expectedAnswer(0, 0) = VBComplex_D(-0.03156480859637, -0.10208193418402);
    expectedAnswer(0, 1) = VBComplex_D(0.11148421759570, 0.08394895903291);
    expectedAnswer(1, 0) = VBComplex_D(0.08394895903291, -0.11148421759570);
    expectedAnswer(1, 1) = VBComplex_D(-0.06245802552048, -0.05305574210880);

    double eps = 1e-8;
    VBAssert(nearEqualMatrix(myAnswer, expectedAnswer, eps), "matrices are different 2x2");

    /*=============================================
    format long
    a = [ (1+j) (-2+3j) (1-j);
    (2-4j) (2-j) (-1+4j)
    (3-3j) (-1-j) (2+j)];
    inv(a)
    ans =
	
      Columns 1 through 2 
	  
            -0.01040763226366 - 0.04293148308760i -0.05767562879445 + 0.07458803122290i
            -0.08716392020815 - 0.29705117085863i -0.04553339115351 - 0.12532523850824i
            0.09063313096271 - 0.18863833477884i -0.10190806591500 - 0.23287077189939i
		
              Column 3 
		  
                    0.18516912402428 + 0.07632263660017i
                    -0.01170858629662 + 0.13920208152645i
                    0.11665221162186 + 0.16869037294016i
    =============================================*/
    myMatrix.redim(3, 3);
    myMatrix(0, 0) = VBComplex_D(1, 1);
    myMatrix(0, 1) = VBComplex_D(-2, 3);
    myMatrix(0, 2) = VBComplex_D(1, -1);

    myMatrix(1, 0) = VBComplex_D(2, -4);
    myMatrix(1, 1) = VBComplex_D(2, -1);
    myMatrix(1, 2) = VBComplex_D(-1, 4);

    myMatrix(2, 0) = VBComplex_D(3, -3);
    myMatrix(2, 1) = VBComplex_D(-1, -1);
    myMatrix(2, 2) = VBComplex_D(2, 1);

    myAnswer = myMatrix.inv();
    // cout << "DEBUG:" << endl << myAnswer << endl;

    expectedAnswer.redim(3, 3);
    expectedAnswer(0, 0) = VBComplex_D(-0.01040763226366, -0.04293148308760);
    expectedAnswer(0, 1) = VBComplex_D(-0.05767562879445, 0.07458803122290);
    expectedAnswer(0, 2) = VBComplex_D(0.18516912402428, 0.07632263660017);

    expectedAnswer(1, 0) = VBComplex_D(-0.08716392020815, -0.29705117085863);
    expectedAnswer(1, 1) = VBComplex_D(-0.04553339115351, -0.12532523850824);
    expectedAnswer(1, 2) = VBComplex_D(-0.01170858629662, 0.13920208152645);

    expectedAnswer(2, 0) = VBComplex_D(0.09063313096271, -0.18863833477884);
    expectedAnswer(2, 1) = VBComplex_D(-0.10190806591500, -0.23287077189939);
    expectedAnswer(2, 2) = VBComplex_D(0.11665221162186, 0.16869037294016);

    VBAssert(nearEqualMatrix(myAnswer, expectedAnswer, eps), "matrices are different 3x3");
}

void checkStrings(VBString & answer, VBString & expectedAnswer) {
    cout << "answer length = " << answer.getLength() << endl;
    cout << "expected answer length = " << expectedAnswer.getLength() << endl;
    for (unsigned i = 0; i < answer.getLength(); i++) {
        int ai = answer[i];
        int eai = expectedAnswer[i];
        cout << answer[i] << " - (" << ai << ") [" << eai << "]" << endl;
    }
}

void testStreams() {
    cout << "=== testStreams" << endl;
    VBMatrix_D y(4, 1);
    y(0, 0) = 1.1;
    y(1, 0) = 3.1;
    y(2, 0) = 4.1;
    y(3, 0) = 7.1;
    // cout << y << endl;
    ostringstream oss;
    oss << y << endl;
    VBString answer = oss.str().c_str();
    const char ret[] = {(char) 10, 0};
    VBString retChar = ret;
    VBString expectedAnswer = "(4,1)" + retChar +
            "+1.1000 " + retChar +
            "+3.1000 " + retChar +
            "+4.1000 " + retChar +
            "+7.1000 " + retChar;
    VBAssert(answer == expectedAnswer);
    // checkStrings(answer,expectedAnswer);

    VBMatrix_CD myMatrix(2, 2);
    myMatrix(0, 0) = VBComplex_D(1, 3);
    myMatrix(0, 1) = VBComplex_D(2, 5);
    myMatrix(1, 0) = VBComplex_D(5, -2);
    myMatrix(1, 1) = VBComplex_D(-1, 4);
    oss.str(""); // clear
    // cout << myMatrix << endl;
    oss << myMatrix << endl;
    answer = oss.str().c_str();
    expectedAnswer = "(2,2)" + retChar +
            "(+1.0000,+3.0000) (+2.0000,+5.0000) " + retChar +
            "(+5.0000,-2.0000) (-1.0000,+4.0000) " + retChar;
    VBAssert(answer == expectedAnswer);
    // checkStrings(answer,expectedAnswer);
}

void testWithOutput() {
    cout << "=== testWithOutput" << endl;
    VBMatrix_D M(2, 2);
    M(0, 0) = 1;
    M(0, 1) = 2;
    M(1, 0) = 3;
    M(1, 1) = 4;
    VBMatrix_D J(2, 1);
    M(0, 0) = 10;
    M(1, 0) = 30;
    cout << "M=" << M << endl;
    VBMatrix_D N = M*J;
    cout << "N=" << N << endl;
}

VB_CUSTOM_EXCEPTION(ABCControlException);

void calculateControlMatrix(const VBMatrix_D & a, const VBMatrix_D & b, VBMatrix_D & c)
throw (ABCControlException) {
    try {
        c = a*b;
    } catch (const VBMathException & e) {
        throw ABCControlException(e.getExplanation());
    }
}

void testWithOutputException() {
    cout << "=== testWithOutputException" << endl;
    try {
        VBMatrix_D A(2, 2);
        A(0, 0) = 1;
        A(0, 1) = 2;
        A(1, 0) = 3;
        A(1, 1) = 4;
        VBMatrix_D B(2, 1);
        B(0, 0) = 10;
        B(1, 0) = 30;
        // B = B.transpose();
        VBMatrix_D C;

        calculateControlMatrix(A, B, C);

        cout << "A=" << A << endl;
        cout << "B=" << B << endl;
        cout << "C=" << C << endl;
    } catch (const ABCControlException & e) {
        cout << "ABCControlException: " << e.getExplanation() << endl;
    }

}

void testLTID() {
    cout << "=== testLTID" << endl;

    // Villas-Boas class for LTI (Linear Time Invariant) 
    // Discrete (and SISO - Single Input Single Output)
    //
    //         b0 z^-(kd) + b1 z^-(1+kd) + ... +  b(nb-1) z^-(2+kd+nb-1)
    // g(z) = --------------------------------------------------------------
    //             1 + a0 z^-1 + a1 z^-2 + ... +  a(na-1) z^-(na-1)



    VBLTID_D lti;
    lti.setDim(2, 2, 1);
    lti.setNum(0, 0.086113911125402);
    lti.setNum(1, -0.077906105739797);
    lti.setDen(0, -1.629281019107614);
    lti.setDen(1, 0.670320046035640);
    double u[] = {
        1.1,
        1.2,
        1.3,
        -1.1,
        -1.2,
        -1.3
    };
    unsigned size_u = sizeof (u) / sizeof (double);
    VBAssert(size_u == 6);
    // creating vector to store the processed output of LTID
    double * y = new double [size_u];

    // processing the output of LTID
    for (unsigned i = 0; i < size_u; i++) {
        y[i] = lti.process(u[i]);
        // y[i] = lti.processFast(u[i]);
    }

    // confirming that the output of LTID was as expected
    double eps = 1e-10;
    double * y_expected = new double [size_u];
    /*
    script matlab used to confirm results
    % arbitrary input vector
    N=6;
    u = ones(1,N); % alloc space for u
    u(1) = 1.1;
    u(2) = 1.2;
    u(3) = 1.3;
    u(4) = -1.1;
    u(5) = -1.2;
    u(6) = -1.3;

    numz =[0   0.086113911125402  -0.077906105739797];
    denz =[1.000000000000000  -1.629281019107614   0.670320046035640];

    y=filter(numz,denz,u);

    format long
    y'
     */

    y_expected[0] = 0;
    y_expected[1] = 0.094725302237943;
    y_expected[2] = 0.171974114002218;
    y_expected[3] = 0.235158648340051;
    y_expected[4] = 0.071858586504864;
    y_expected[5] = -0.058193701965411;

    for (unsigned i = 0; i < size_u; i++) {
        // cout << y[i] << " | " << y_expected[i] << endl;
        VBAssert(nearEqual(y[i], y_expected[i], eps));
    }
}

template <typename IntType>
VBString primesString(IntType number, deque<IntType> & primesContainer) {
    VBPrimesFactorList<IntType> primesFactorList;
    factorInteger<unsigned>(number, primesFactorList, primesContainer);
    return primesFactorList.getString();
};

//void testPrimes() {
//    cout << "=== testPrimes" << endl;
//    deque<unsigned> primesContainer;
//    deque<unsigned>::iterator it;
//    unsigned limit = 100; // maximum calculated prime
//    createPrimesContainer(primesContainer, limit);
//    unsigned initialPrimes[] = {
//        2, 3, 5, 7, 11, 13, 17,
//        19, 23, 29, 31, 37, 41,
//        43, 47, 53, 59, 61, 67,
//        71, 73, 79, 83, 89, 97
//    };
//    int i = 0;
//    for (it = primesContainer.begin();
//            it != primesContainer.end();
//            it++) {
//        VBAssert(*it == initialPrimes[i++]);
//    }
//
//    // create a file with the initial 1000 primes
//    createPrimesFile<unsigned>(1000, "primes_until_1K.txt");
//
//    // create a file with the initial 1000000 (1M) primes
//    // createPrimesFile<unsigned>(1000000,"primes_until_1M.txt");
//
//    try {
//        VBAssert(primesString<unsigned>(100, primesContainer) == "2^2 * 5^2");
//        VBAssert(primesString<unsigned>(125, primesContainer) == "5^3");
//        VBAssert(primesString<unsigned>(126, primesContainer) == "2^1 * 3^2 * 7^1");
//        VBAssert(primesString<unsigned>(333, primesContainer) == "3^2 * 37^1");
//        VBAssert(primesString<unsigned>(337, primesContainer) == "(produces exception)");
//    } catch (const VBMathException & e) {
//        VBString explanation = e.getExplanation();
//        // cout << explanation << endl;
//        VBAssert(explanation == "number 337 requires to be factored requires prime greater than 97");
//    }
//
//    // GCD = GreatestCommonDivisor (MDC Maximo Divisor Comum)
//
//    VBPrimesFactorList<unsigned> ret;
//    GCD<unsigned>(2, 10, primesContainer, ret);
//    VBAssert(ret.getString() == "2^1");
//    VBAssert(ret.getInt() == 2);
//
//    GCD<unsigned>(11, 33, primesContainer, ret);
//    VBAssert(ret.getString() == "11^1");
//    VBAssert(ret.getInt() == 11);
//
//    GCD<unsigned>(12, 34, primesContainer, ret);
//    VBAssert(ret.getString() == "2^1");
//    VBAssert(ret.getInt() == 2);
//
//    GCD<unsigned>(36, 18, primesContainer, ret);
//    VBAssert(ret.getString() == "2^1 * 3^2");
//    VBAssert(ret.getInt() == 18);
//
//    // LCM = Least Common Multiple (MMC Mínimo Múltiplo Comum)
//    LCM<unsigned>(36, 18, primesContainer, ret);
//    VBAssert(ret.getString() == "2^2 * 3^2");
//    VBAssert(ret.getInt() == 36);
//
//    LCM<unsigned>(45, 99, primesContainer, ret);
//    VBAssert(ret.getString() == "3^2 * 5^1 * 11^1");
//    VBAssert(ret.getInt() == 495);
//
//    LCM<unsigned>(11, 99, primesContainer, ret);
//    VBAssert(ret.getString() == "3^2 * 11^1");
//    VBAssert(ret.getInt() == 99);
//    // cout << ret.getString() << endl;
//    // cout << ret.getInt() << endl;
//}

//void testIntegerMath() {
//    cout << "=== testIntegerMath" << endl;
//    deque<int> primesContainer;
//
//    createPrimesFile<unsigned>(10000, "primes_until_10K.txt");
//    loadPrimesFile("primes_until_10k.txt", primesContainer);
//    VBPrimesFactorList<int> primesFactorList;
//
//    int number = 100;
//    factorInteger<int>(number, primesFactorList, primesContainer);
//    VBAssert(primesFactorList.getString() == "2^2 * 5^2", "wrong factorization");
//
//    number = 1024;
//    factorInteger<int>(number, primesFactorList, primesContainer);
//    VBAssert(primesFactorList.getString() == "2^10", "wrong factorization");
//
//    number = 1343;
//    factorInteger<int>(number, primesFactorList, primesContainer);
//    VBAssert(primesFactorList.getString() == "17^1 * 79^1", "wrong factorization");
//
//    // number = 1343512; factorInteger<int>(number, primesFactorList, primesContainer);
//    // VBAssert(primesFactorList.getString()=="2^3 * 29^1 * 5791^1","wrong factorization");
//
//    number = 10;
//    factorInteger<int>(number, primesFactorList, primesContainer);
//    VBAssert(primesFactorList.getString() == "2^1 * 5^1", "wrong factorization");
//    // cout << "primes of " << number << "=" << primesFactorList.getString() << endl;
//
//    // GCD Greatest Common Divisor (MDC Maximo Divisor Comum)
//    VBPrimesFactorList<int> gcd;
//    GCD<int>(2, 4, primesContainer, gcd);
//    VBAssert(gcd.getString() == "2^1", "wrong gcd");
//    GCD<int>(2, 5, primesContainer, gcd);
//    VBAssert(gcd.getString() == "1", "wrong gcd");
//    GCD<int>(10, 5, primesContainer, gcd);
//    VBAssert(gcd.getInt() == 5, "wrong gcd");
//    GCD<int>(10, 10, primesContainer, gcd);
//    VBAssert(gcd.getInt() == 10, "wrong gcd");
//    GCD<int>(17, 10, primesContainer, gcd);
//    VBAssert(gcd.getInt() == 1, "wrong gcd");
//    GCD<int>(1024, 10, primesContainer, gcd);
//    VBAssert(gcd.getInt() == 2, "wrong gcd");
//    GCD<int>(36, 24, primesContainer, gcd);
//    VBAssert(gcd.getInt() == 12, "wrong gcd");
//    GCD<int>(144, 24, primesContainer, gcd);
//    VBAssert(gcd.getInt() == 24, "wrong gcd");
//    GCD<int>(144, 36, primesContainer, gcd);
//    VBAssert(gcd.getInt() == 36, "wrong gcd");
//    GCD<int>(10, 36, primesContainer, gcd);
//    VBAssert(gcd.getInt() == 2, "wrong gcd");
//    // cout << "gcd=" << gcd.getString() << "=" << gcd.getInt() << endl;
//
//    // LCM = Least Common Multiple (MMC Mínimo Múltiplo Comum)
//    VBPrimesFactorList<int> lcm;
//    LCM<int>(2, 4, primesContainer, lcm);
//    VBAssert(lcm.getInt() == 4, "wrong lcm");
//    LCM<int>(2, 5, primesContainer, lcm);
//    VBAssert(lcm.getInt() == 10, "wrong lcm");
//    LCM<int>(10, 10, primesContainer, lcm);
//    VBAssert(lcm.getInt() == 10, "wrong lcm");
//    LCM<int>(100, 100, primesContainer, lcm);
//    VBAssert(lcm.getInt() == 100, "wrong lcm");
//    LCM<int>(1024, 10, primesContainer, lcm);
//    VBAssert(lcm.getInt() == 5120, "wrong lcm");
//    // cout << "lcm=" << lcm.getString() << "=" << lcm.getInt() << endl;
//
//    // let n1 and n2 be any positive number 
//    // (so that n1*n2 generates no overflow)
//    int n1 = 143;
//    int n2 = 123987;
//    LCM<int>(n1, n2, primesContainer, lcm);
//    GCD<int>(n1, n2, primesContainer, gcd);
//    // cout << "DEBUG gcd=" << gcd.getString() << "=" << gcd.getInt() << endl;
//    // cout << "DEBUG lcm=" << lcm.getString() << "=" << lcm.getInt() << endl;
//    // cout << "DEBUG n1*n2=" << n1*n2 << endl;
//    VBAssert(n1 * n2 == lcm.getInt() * gcd.getInt(), "wrong lcm*gdc");
//}

// no warning in "a+b;" 
#pragma warning(disable:4552)

template <typename Real>
void testFormula(Real eps) {
    VBString realStr = typeid (Real).name();
    // cout << realStr << endl;
    // cout << "eps=" << eps << endl;
    Real a, b, c;
    b = 1.1;
    c = 2.2;
    a = b;
    VBAssert(nearEqual(a, 1.1, eps));
    a = b + c;
    VBAssert(nearEqual(a, 3.3, eps));
    a = b - c;
    VBAssert(nearEqual(a, -1.1, eps));
    a = b*c;
    VBAssert(nearEqual(a, 2.42, eps));
    a = b / c;
    VBAssert(nearEqual(a, 0.5, eps));
    a = 1;
    a += 1.1;
    VBAssert(nearEqual(a, 2.1, eps));
    a = 1;
    a -= 1.1;
    VBAssert(nearEqual(a, -0.1, eps));
    a = 1;
    a *= 1.1;
    VBAssert(nearEqual(a, 1.1, eps));
    a = 1;
    a /= 1.1;
    VBAssert(nearEqual(a, 0.909090909090909090909090, eps));

    // report only in case of VBDebugFloat<double>
    //cout << typeid(a).name() << endl;
    //cout << typeid(VBDebugFloat<double>()).name() << endl;
    if (realStr == "class br::com::sbVB::VBMath::VBDebugFloat<double>") {
        VBDebugFloatReport & report = VBDebugFloat<double>::m_report;
        ostringstream oss;
        oss << report;
        VBString reportStr = oss.str().c_str();
        VBAssert(reportStr == "1,1,1,1 | 1,1,1,1 | 11,18,5,18");
        // cout << reportStr << endl;
        // cout << VBDebugFloat<double>::m_report << endl;

        // after clear
        report.clear();
        oss.str("");
        oss << report;
        reportStr = oss.str().c_str();
        // cout << reportStr << endl;
        VBAssert(reportStr == "0,0,0,0 | 0,0,0,0 | 0,0,0,0");
        a + b; // one operation +, one default constructor, one copy constructor
        oss.str("");
        oss << report;
        reportStr = oss.str().c_str();
        // cout << reportStr << endl;
        VBAssert(reportStr == "1,0,0,0 | 0,0,0,0 | 0,1,1,0");
    }
};

void testDebugFloat() {
    cout << "=== testDebugFloat" << endl;
    testFormula<float>(1e-6);
    testFormula< VBDebugFloat<float> >(1e-6);
    testFormula<double>(1e-15);
    testFormula< VBDebugFloat<double> >(1e-15);
}

double doParser(const char *expression) {
    VBParser_D parser; // VBParser<double> parser;
    return parser.eval_exp(expression);
}

void testParser() {
    cout << "=== testParser" << endl;
    double eps = 1e-10;
    VBParser_D parser; // VBParser<double> parser;
    double val = parser.eval_exp("1.1 + 2.2");
    VBAssert(nearEqual(val, 3.3, eps));
    val = parser.eval_exp("2.1^4.3");
    VBAssert(nearEqual(val, 24.2964580955070747, eps));
    VBAssert(nearEqual(parser.eval_exp("2^4"), 16.0, eps));
    VBAssert(nearEqual(doParser("2^4 + 1.1*2"), 18.2, eps));
}

void VBMath_tests() {
    cout << "=== VBMath_tests" << endl;

    try {
        ///////////////////////////////////////////////////////
        // non automatic tests (produce output)
        ///////////////////////////////////////////////////////

        // testWithOutput();
        // testWithOutputException();

        ///////////////////////////////////////////////////////
        // automatic tests (produce no output)
        ///////////////////////////////////////////////////////

        testVBMathException();
        testNearEqual();
        testCheckAMatrix();
        test_rmult();
        testInvertMatrix();
        testRegression();
        testGenericComplex();
        testInvertComplexMatrix();
        testStreams();
        testLTID();
//        testPrimes();
        // testIntegerMath(); // this one takes long
        testDebugFloat();
        testParser();


        // test of experimental classes begin
        // VBIntBCDTest();
        // VBIntTest();
        // innerValueTest();
        // VBDoubleTest();
        // VBUnsigned_test();
        // test of experimental classes end
    } catch (const VBMathException & e) {
        cout << "VBMathException: " << e.getExplanation() << endl;
    } catch (...) {
        cout << "Unknown exception" << endl;
    }

}
