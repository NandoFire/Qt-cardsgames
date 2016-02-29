// Rascunho do Baralho

#include <iostream>
#include <string>
#include <vector>
using namespace std;

/**
 * representa o local onde uma carta pode estar
 */
struct LocalCarta {
    string nome;

    LocalCarta(string n) : nome(n) {
    };
};

enum Naipe {
    Paus, Espadas, Copas, Ouros
};

enum CartaValor {
    A, _2, _3, _4, _5, _6, _7, _8, _9, _10, J, Q, K
};

struct Carta {
    int local;
    Naipe naipe;
    CartaValor valor;

    Carta(Naipe n, CartaValor v) : naipe(n), valor(v), local(-1) {
    }

    friend ostream & operator<<(ostream & out, Carta & carta) {
        string naipeStr = "empty";
        string valorStr = "empty";
        switch (carta.naipe) {
            case Paus:
                naipeStr = "Paus";
                break;
            case Espadas:
                naipeStr = "Espadas";
                break;
            case Copas:
                naipeStr = "Copas";
                break;
            case Ouros:
                naipeStr = "Ouros";
                break;
        }
        out << naipeStr << ":" << carta.valor << "[" << carta.local << "]";
        return out;
    }

    static void testMe() {
        cout << "Carta::testMe()" << endl;
        Carta carta(Copas, A);
        cout << carta << endl;
    }
};

struct Baralho {
    vector<Carta> m_cartas;

public:

    void preencherDeFormaPadrao() {
        m_cartas.push_back(Carta(Paus, A));
        m_cartas.push_back(Carta(Paus, _2));
        m_cartas.push_back(Carta(Paus, _3));
        m_cartas.push_back(Carta(Paus, _4));
        m_cartas.push_back(Carta(Paus, _5));
        m_cartas.push_back(Carta(Paus, _6));
        m_cartas.push_back(Carta(Paus, _7));
        m_cartas.push_back(Carta(Paus, _8));
        m_cartas.push_back(Carta(Paus, _9));
        m_cartas.push_back(Carta(Paus, _10));
        m_cartas.push_back(Carta(Paus, J));
        m_cartas.push_back(Carta(Paus, Q));
        m_cartas.push_back(Carta(Paus, K));
        m_cartas.push_back(Carta(Espadas, A));
        m_cartas.push_back(Carta(Espadas, _2));
        m_cartas.push_back(Carta(Espadas, _3));
        m_cartas.push_back(Carta(Espadas, _4));
        m_cartas.push_back(Carta(Espadas, _5));
        m_cartas.push_back(Carta(Espadas, _6));
        m_cartas.push_back(Carta(Espadas, _7));
        m_cartas.push_back(Carta(Espadas, _8));
        m_cartas.push_back(Carta(Espadas, _9));
        m_cartas.push_back(Carta(Espadas, _10));
        m_cartas.push_back(Carta(Espadas, J));
        m_cartas.push_back(Carta(Espadas, Q));
        m_cartas.push_back(Carta(Espadas, K));
        m_cartas.push_back(Carta(Copas, A));
        m_cartas.push_back(Carta(Copas, _2));
        m_cartas.push_back(Carta(Copas, _3));
        m_cartas.push_back(Carta(Copas, _4));
        m_cartas.push_back(Carta(Copas, _5));
        m_cartas.push_back(Carta(Copas, _6));
        m_cartas.push_back(Carta(Copas, _7));
        m_cartas.push_back(Carta(Copas, _8));
        m_cartas.push_back(Carta(Copas, _9));
        m_cartas.push_back(Carta(Copas, _10));
        m_cartas.push_back(Carta(Copas, J));
        m_cartas.push_back(Carta(Copas, Q));
        m_cartas.push_back(Carta(Copas, K));
        m_cartas.push_back(Carta(Ouros, A));
        m_cartas.push_back(Carta(Ouros, _2));
        m_cartas.push_back(Carta(Ouros, _3));
        m_cartas.push_back(Carta(Ouros, _4));
        m_cartas.push_back(Carta(Ouros, _5));
        m_cartas.push_back(Carta(Ouros, _6));
        m_cartas.push_back(Carta(Ouros, _7));
        m_cartas.push_back(Carta(Ouros, _8));
        m_cartas.push_back(Carta(Ouros, _9));
        m_cartas.push_back(Carta(Ouros, _10));
        m_cartas.push_back(Carta(Ouros, J));
        m_cartas.push_back(Carta(Ouros, Q));
        m_cartas.push_back(Carta(Ouros, K));
    }

    void embaralhar() {
    }

    void dumpCartas() {
        vector<Carta>::iterator it;
        // a loop to scan the STL container
        for (it = m_cartas.begin();
                it != m_cartas.end();
                it++) {
            cout << *it << endl;
        }
    }

    static void testMe() {
        cout << "Baralho::testMe()" << endl;

        Baralho baralho;

        baralho.preencherDeFormaPadrao();

        baralho.embaralhar();
        baralho.dumpCartas();

    }
};

struct Jogo {
    Baralho m_baralho;
    vector<LocalCarta> m_locais;
    
    Jogo() {
        m_baralho.preencherDeFormaPadrao();
    }

    void algunsJogadores() {
        m_locais.push_back(LocalCarta("Jogador")); // 0
        m_locais.push_back(LocalCarta("Mesa")); // 1
    }

    /**
     * @param local onde a carta pode estar
     * @return id do local
     */
    int getId(string local) {
        int i = 0;
        vector<LocalCarta>::iterator it;
        for (it = m_locais.begin();
                it != m_locais.end();
                it++) {
//            cout << "DEBUG:" << it->nome << ":" << i << endl;
            if (it->nome == local)
                return i;
            i++;
        }
    }

    /**
     * faz todas as cartas irem para a mesa
     */
    void cartasNaMesa() {
        vector<Carta>::iterator it;
        for (it = m_baralho.m_cartas.begin();
                it != m_baralho.m_cartas.end();
                it++) {
            int i = getId("Mesa");
//            cout << "DEBUG: i=" << i << endl;
            it->local = i;
        }
    }

    static void testMe() {
        cout << "Jogo::testMe()" << endl;
        Jogo jogo;
        jogo.algunsJogadores();
//        cout << jogo.getId("Mesa") << endl;
        jogo.m_baralho.dumpCartas();
        jogo.cartasNaMesa();
        jogo.m_baralho.dumpCartas();
        

    }


};

int main() {
    cout << "hello" << endl;
    Jogo::testMe();
//    Carta::testMe();
//    Baralho::testMe();


    return 0;
}


///////////////////////////////////////////////////
//
//#include <cmath>
//#include <iostream>
//using namespace std;
//
//template <typename T>
//void selection_sort(T* array, unsigned size,
//        bool (*compare)(const T &, const T &)) {
//    for (unsigned i = 0; i < size; i++)
//        for (unsigned j = i + 1; j < size; j++)
//            if (compare(array[i], array[j])) { // swap (array[i], array[j])
//                T temp = array[i];
//                array[i] = array[j];
//                array[j] = temp;
//            }
//};
//
//bool floatCompare(const float & x, const float & y) {
//    return x < y;
//}
//
//
//struct Abacaxi {
//    float _tamanho;
//    float _peso;
//    Abacaxi(float tamanho=0, float peso=0) 
//            : _peso(peso), _tamanho(tamanho) {        
//    }
//    
//    friend ostream & operator<< (ostream & x, const Abacaxi & y) {
//        x << "peso=" << y._peso << ", tamanho=" << y._tamanho;
//        return x;
//    }
//    
//    static void testMe() {
//        Abacaxi abacaxi(1.1,2.2);
//        cout << "abacaxi=" << abacaxi << endl;
//    }
//    
//};
//
//bool AbacaxiComparePeso(const Abacaxi & x, const Abacaxi & y) {
//    return x._peso < y._peso;
//}
//
//bool AbacaxiCompareTamanho(const Abacaxi & x, const Abacaxi & y) {
//    return x._tamanho < y._tamanho;
//}
//
//int main() {
//    cout << "hello" << endl;
//    
////    Abacaxi::testMe();    
////    return 0;
//        
//
//    const unsigned N = 10;
//    Abacaxi array[N];
//    int i;
//    // load random data and show
//    cout << "=== Before sort" << endl;
//    for (i = 0; i < N; i++) {
//        array[i]._peso = 10 * sin(40.0f * (i+1));
//        array[i]._tamanho = 10 * sin(50.0f * (i+1));
//        cout << array[i] << endl;
//    }
//    
//    
//    // sort with selection sort
//    selection_sort<Abacaxi>(array, N, AbacaxiComparePeso);
//    cout << "=== After sort" << endl;
//    for (i = 0; i < N; i++) {
//        cout << array[i] << endl;
//    }
//
//    return 0;
//}

//////////////////////////////////////////

//#include <iostream>
//using namespace std;
//
//struct Vertebrate {
//};
//
//struct Mammal : public Vertebrate {
//};
//
//struct Cat : public Mammal {
//};
//
//struct Dog : public Mammal {
//};
//
//int main() {
//    cout << "hello" << endl;
//
//    try {
//        throw Cat();
//        throw 1;
//        throw "lixo";
//    } catch (const char *e) {
//        cout << "Exception:" << e << endl;
//    } catch (double e) {
//        cout << "Exception:" << e << endl;
////    } catch (Cat e) {
////        cout << "Exception Cat"  << endl;
////    } catch (Mammal e) {
////        cout << "Exception Mammal"  << endl;
////    } catch (Vertebrate e) {
////        cout << "Exception Vertebrate"  << endl;
//    } catch (...) {
//        cout << "Exception ..."  << endl;
//    }
//
//    cout << "hello2" << endl;
//
//    return 0;
//}


////////////////////////////////////////////

//#include <fstream>
//#include <iostream>
//#include <stdlib.h>
//#include <string>
//#include <sstream>
//using namespace std;
//
//void VBAssert(bool b, const char *msg = "") {
//    if (!b) {
//        cout << "VBAssert fail:" << msg << endl;
//    }
//}
//
///**
// * convert input parameter to string
// * @param i
// * @return 
// */
//string myitoa(int i) {
//    string ret;
//    ostringstream oss;
//    oss << i;
//    ret = oss.str();
//    return ret;
//}
//
//void test() {
//    string s = "33"; // const char *
//
//    // convert string to integer
//    int i = atoi(s.c_str());
//    VBAssert(i == 33);
//
//    // convert integer to string
//    s = myitoa(i);
//    VBAssert(s == "33");
//}
//
//#define FOLDER "/home/sbvb/zzz6/"
//
//void writeFileTabuada(int tab) {
//    cout << "=== writeFileTabuada " << tab << endl;
//    string fileName = FOLDER"tabuada_" + myitoa(tab) + ".txt";
//    ofstream outFile;
//    outFile.open(fileName.c_str());
//    if (!outFile) {
//        cout << "File " << fileName << " not open" << endl;
//    } else {
//        for (int i=1; i<=10;i++) {
//            outFile << i << " * " << tab << " = " << i*tab << endl;
//        }
//    }
//    
//}
//
//int main() {
//
//    int tab;
//    ifstream myFile;
//    const char* fname = FOLDER"tabuadas.txt";
//    myFile.open(fname);
//    if (!myFile) {
//        cout << "File " << fname << " not open" << endl;
//    } else {
//        // loop to read entire file
//        while (true) {
//            myFile >> tab; 
//            if (myFile.eof()) break;
//            // cout << tab << endl;
//            writeFileTabuada(tab);
//        }
//    }
//
//    return 0;
//}


///////////////////////////////////////////////////////


//class Base {
//    // add code here 
//public:
//    int m_i;
//    friend ostream & operator<<(ostream & s, const Base & z) {
//        s << z.m_i; // s.operator<<(z.m_i);
//        return s;
//    }
//};
//
//class Derived : public Base {
//public:
//    void operator=(int i) {
//        m_i = i;
//    }
//};
//
//int main() {
//    Derived a;
//    a = 3;
//    cout << a << endl;
//    return 0;
//}


///////////////////////////////////////////////////////


//struct AsteroidCluster;
//
//struct Asteroid {
//    double m_mass;
//    double m_x, m_y;
//
//    int setAC(AsteroidCluster *ac, int pos);
//
//    void show() {
//        cout << "Asteroid.show()" << endl;
//        cout << "Asteroid com massa " << m_mass <<
//                " está na posição x=" << m_x <<
//                " e y=" << m_y << endl;
//
//    };
//};
//
//struct AsteroidCluster {
//    static const int max = 4;
//    Asteroid * m_list[max];
//
//    void show() {
//        cout << "AsteroidCluster.show()" << endl;
//        for (int i = 0; i < max; i++) {
//            m_list[i]->show();
//        }
//    }
//
//    // add code here
//
//    static void testMe() {
//        cout << "=== AsteroidCluster::testMe()" << endl;
//        Asteroid a1, a2, a3, a4;
//        a1.m_mass = 1.1;
//        a1.m_x = 10.1;
//        a1.m_y = 20.1;
//        a2.m_mass = 1.2;
//        a2.m_x = 10.2;
//        a2.m_y = 20.2;
//        a3.m_mass = 1.3;
//        a3.m_x = 10.3;
//        a3.m_y = 20.3;
//        a4.m_mass = 1.4;
//        a4.m_x = 10.4;
//        a4.m_y = 20.4;
//
//        AsteroidCluster ac;
//        a1.setAC(&ac, 0);
//        a2.setAC(&ac, 1);
//        a3.setAC(&ac, 2);
//        a4.setAC(&ac, 3);
//
//        ac.show();
//    }
//};
//
//int Asteroid::setAC(AsteroidCluster *ac, int pos)
//{
//    ac->m_list[pos] = this;
//}
//
//int main() {
//    AsteroidCluster::testMe();
//
//    return 0;
//}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//#include <ctime>
//#include <iostream>
//#include <cmath>
//#include <string>
//using namespace std;
//
//bool nearEqual(double x, double y, double eps) {
//    return fabs(x - y) < eps;
//}
//
//void VBAssert(bool b, const char *msg = "") {
//    if (!b) {
//        cout << "myAssert fail:" << msg << endl;
//    }
//}
//
//double mean(const double *data, int n) {
//    double ret = 0.0;
//    for (int i = 0; i < n; i++) {
//        ret += data[i];
//    }
//    return ret / n;
//}
//
//double sdev(const double *data, int n) {
//    double m = mean(data, n);
//    double sum2 = 0.0;
//    for (int i = 0; i < n; i++) {
//        // sum2 += data[i]*data[i];
//        sum2 += pow(data[i] - m, 2.0);
//    }
//    return sqrt(sum2 / (n - 1));
//
//    //    cout << "DEBUG: sum2=" << sum2 << endl; 
//    //    double m = mean(data,n);
//    //    cout << "DEBUG: m=" << m << endl; 
//    //    double m2 = m * m;
//    //    cout << "DEBUG: sqrt(sum2/n - m2)=" << sqrt(sum2/n - m2) << endl; 
//    //    return sqrt(sum2/n - m2);
//}
//
//void t2() {
//
//    double *pd = new double;
//    delete pd;
//
//
//
//    double eps = 1e-8;
//    double data[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
//    VBAssert(nearEqual(mean(data, 6), 3.5, eps));
//    VBAssert(nearEqual(sdev(data, 6), 1.870828693386971, eps));
//    double data2[] = {10.0, 20.0, 30.0, 40.0, 50.0, 60.0};
//    VBAssert(nearEqual(mean(data2, 6), 35.0, eps));
//    VBAssert(nearEqual(sdev(data2, 6), 18.708286933869708, eps));
//    double data3[] = {10.0, 20.0};
//    VBAssert(nearEqual(mean(data3, 2), 15.0, eps));
//    VBAssert(nearEqual(sdev(data3, 2), 7.071067811865476, eps));
//}
//
//struct Jorge {
//    string name;
//    int yearOfBirth;
//    double weight;
//    int gradeLingProg;
//    string comment;
//    // ...
//};
//
//Jorge getJorge() {
//    Jorge ret;
//
//    ret.gradeLingProg = 2;
//    ret.name = "Jorge Name";
//    ret.weight = 75.3;
//    ret.yearOfBirth = 2002;
//
//    return ret;
//}
//
//// add surname to name
//
//Jorge addSurname(Jorge jin, string surname) {
//    //    cout << "DEBUG: name=" << jin.name << endl;
//
//    jin.name += surname;
//
//    return jin;
//
//}
//
//void testJorge() {
//    cout << "=== testJorge()" << endl;
//    double eps = 1e-8;
//    Jorge jorge = getJorge();
//    VBAssert(jorge.name == "Jorge Name");
//    VBAssert(jorge.yearOfBirth == 2002);
//    VBAssert(jorge.gradeLingProg == 2);
//    VBAssert(nearEqual(jorge.weight, 75.3, eps));
//
//    Jorge jorge2 = addSurname(jorge, " Silva");
//    VBAssert(jorge2.name == "Jorge Name Silva");
//
//    cout << "DEBUG: name=" << jorge2.name << endl;
//}
//
//bool is13(const tm & t) {
//    return t.tm_mday == 13;
//}
//
//bool isFriday(const tm & t) {
//    return t.tm_wday == 5;
//}
//
//bool isFriday13(const tm & t) {
//    return t.tm_mday == 13 && t.tm_wday == 5;
//    //    return is13(t) && isFriday(t);
//}
//
//void test_tm() {
//    cout << "=== test_tm()" << endl;
//    tm t;
//    t.tm_year = 110; // 2010 
//    t.tm_mon = 7; // August 
//    t.tm_mday = 13;
//    t.tm_wday = 5; // friday 
//    VBAssert(isFriday13(t));
//
//    //    time_t ltime;
//    //    tm *now;
//    //    time(&ltime); // get time and date 
//    //    now = localtime(&ltime); // convert to struct tm 
//    //    VBAssert(!isFriday13(*now));
//}

//int main() {
//    cout << "====== main" << endl;
//    //    testJorge();
//    test_tm();
//    return 0;
//}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////



//#include "VBLib/VBLib.h"
//using namespace br::com::sbVB::VBLib;
//#include <iostream> 
//using namespace std;

//class Sale {
//protected: // to permit acces to descendants 
//    float m_price;
//    float m_cost;
//public:
//
//    void setPrice(float price) {
//        m_price = price;
//    }
//
//    void setCost(float cost) {
//        m_cost = cost;
//    }
//    virtual string makeSale() = 0;
//    virtual float getProfit() = 0;
//    virtual void setNumberOfSaleProvisions(int nProvision) = 0;
//
//};
//
//class Cash : public Sale {
//public:
//
//    float getProfit() {
//        return m_price - m_cost;
//    }
//
//    string makeSale() {
//        string ret = string("sale in cash; price is ");
//        ret += m_price;
//        return ret;
//    }
//
////    void setNumberOfSaleProvisions(int nProvision) {
////    }
//
//};
//
//class Financed : public Sale {
//    int m_nProvision; // number of months of sale provision 
//    float m_factor; // to increase profit for finances dale 
//public:
//
//    Financed() { // constructor 
//        m_factor = 1.1f; // hard coded definition 
//
//    }
//
//    float getProfit() {
//        return m_price * m_factor - m_cost;
//    }
//
//    void setNumberOfSaleProvisions(int nProvision) {
//        m_nProvision = nProvision;
//    }
//
//    string makeSale() {
//        string ret = string("financed sale; price is ");
//        ret += m_price;
//        ret += ". Sale provision is ";
//        ret += m_price * m_factor / m_nProvision;
//        ret += ". n provisions is ";
//        ret += m_nProvision;
//        ret += ".";
//        return ret;
//    }
//};

//int main() {
//    Sale *s;
//    // test cash sale 
//    s = new Cash();
//    s->setCost(1500);
//    s->setPrice(2200);
//    VBAssert(s->makeSale() == "sale in cash; price is 2200.00");
//    delete s;
//
//    // test Financed sale 
//    s = new Financed();
//    s->setCost(1500);
//    s->setPrice(2200);
//    s->setNumberOfSaleProvisions(5);
//    VBAssert(s->makeSale() ==
//            "financed sale; price is 2200.00."
//            " Sale provision is 484.00. n provisions is 5.");
//    delete s;
//
//    return 0;
//} 
//

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//#include <iostream> 
//#include <string> 
//using namespace std;
//
//void VBAssert(bool b, const char *msg = "") {
//    if (!b) {
//        cout << "myAssert fail:" << msg << endl;
//    }
//}
//
//struct GenericCharacter {
//    string m_name;
//
//    virtual string getPower() {
//        return m_name + ", power Generic";
//    }
//    
//    virtual string getName() = 0;
//
//};
//
//struct WeakCharacter : public GenericCharacter {
//    string getName() {
//        return "(weak) " + m_name;
//    }
//};
//    
//struct StrongCharacter : public GenericCharacter {
//    string getName() {
//        return "(strong) " + m_name;
//    }
//};
//
//struct Character_A : public WeakCharacter {
//
//    string getPower() {
//        return getName() + ", power A";
//    }
//};
//
//struct Character_B : public StrongCharacter {
//
//    string getPower() {
//        return getName() + ", power B";
//    }
//};
//
//struct Character_C : public StrongCharacter {
//
//    string getPower() {
//        return getName() + ", power C";
//    }
//};
//
//int main() {
//
//    GenericCharacter *gc;
//    gc= new Character_A;
//    gc->m_name = "char A";
//    cout << gc->getPower() << endl;
////    VBAssert(gc->getPower()=="char A, power A");
//    delete gc;
//
//    gc = new Character_B;
//    gc->m_name = "char B";
//    cout << gc->getPower() << endl;
////    VBAssert(gc->getPower()=="char B, power B");
//    delete gc;
//
//    gc = new Character_C;
//    gc->m_name = "char C";
//    cout << gc->getPower() << endl;
////    VBAssert(gc->getPower()=="char C, power C");
//    delete gc;
//
//    return 0;
//}
