// VBLog.h


// depends on boost
// sudo apt-get install libboost-all-dev
#include <boost/iostreams/stream.hpp>
#include <boost/iostreams/tee.hpp>



// all entities in namespace br::com::sbVB::VBLib
namespace br {
    namespace com {
        namespace sbVB {
            namespace VBLib {

                struct VBLog {
                    typedef boost::iostreams::tee_device<std::ostream, std::ofstream> Tee;
                    typedef boost::iostreams::stream<Tee> TeeStream;

                    static std::ofstream outFile;
                    static Tee tee;
                    static TeeStream myout;

                    static void test() {
                        using namespace std;
                        cout << "== VBLog::test()" << endl;
                        VBLog::myout << "string to log" << endl;
                        VBLog::myout << "see file" << endl;
                    }
                    
                };



#ifndef _VBLIB_H_GLOBAL_NOT_AGAIN_

                // initialization of static attributes begin
                std::ofstream VBLog::outFile("/home/sbvb/VBLog.txt");
                VBLog::Tee VBLog::tee(std::cout, VBLog::outFile);
                VBLog::TeeStream VBLog::myout(VBLog::tee);
                // initialization of static attributes end

#endif

            }
        }
    }
} // close namespace ::br::com::sbVB::VBLib
