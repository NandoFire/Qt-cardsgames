// To use clock_gettime you need to include time.h and to link to librt.a. 
// If you use gcc just make sure you add -lrt to your list of arguments.

#include "VBLib/VBLib.h"
using namespace br::com::sbVB::VBLib;
using namespace std;

#include "VBMath/VBMath.h"
using namespace br::com::sbVB::VBMath;

#include "VBMcgi/VBMcgi.h"
using namespace br::com::sbVB::VBMcgi;

int main() {
    using namespace std;
    cout << "====== test of sbvblibs-h, by sbVB" << endl;
    
    
    br::com::sbVB::VBLib::test();
    br::com::sbVB::VBMath::test();
    br::com::sbVB::VBMcgi::test();
    
    return 0;
}




///////////////////////////////
//
//void splash() {
//    cout << "usage: deamon_loop \"<command> <parameters>\"" << endl;
//    cout << "example: deamon_loop \"chmod 755 *\"" << endl;
//}
//
//int main(int argc, char **argv) {
//    cout << "//////////////////////////////////////////////" << endl;
//    cout << "====== deamon_loop, by sbVB (www.sbvb.com.br)" << endl;
//    cout << "====== build date 2012_06_30" << endl;
//    cout << "//////////////////////////////////////////////" << endl;
//
//
//    VBString execStr = "chmod 755 *";
//    int sleep_sec = 2; // 1 second
//
//    bool debug = true;
//    if (!debug) {
//
//        if (argc == 1) { // no arguments
//            splash();
//            return 0;
//        }
//
//        if (argc > 1) {
//            execStr = argv[1];
//        }
//
//        if (argc > 2) {
//            sleep_sec = atoi(argv[2]) / 1000;
//        }
//    }
//
//    cout << "//////////////////////////////////////////////" << endl;
//    cout << "exec= '" << execStr << "'" << endl;
//    cout << "//////////////////////////////////////////////" << endl;
//
//    // endless execute loop
//    while (true) {
//        cout << ".";
//        cout.flush();
//        int ret = system(execStr.c_str());
//        VBClock::sleepMS(sleep_sec * 1000);
//    }
//
//
//    return 0;
//}
//
