// VBClock.h

// #include <conio.h>

// all entities in namespace br::com::sbVB::VBLib
namespace br {
    namespace com {
        namespace sbVB {
            namespace VBLib {

                /////////////////////////////////////////////////////////////////////
                //
                // VBClock
                // a class make a clock
                //
                /////////////////////////////////////////////////////////////////////

                class VBClock {
                    unsigned long m_start, m_finish;
                    double m_duration; // seconds

                    void checkDiffTime() {
                        //                        m_finish = clock();
                        //                        m_duration = (double) (m_finish - m_start) / CLOCKS_PER_SEC;
                        m_finish = getTimeMs();
                        m_duration = (double) (m_finish - m_start) / 1000.0;
                    }


#ifndef _MSC_VER  
// linux only
                    static void myNanoSleep(const timespec *requested,
                            timespec *remaining) {
                        timespec remaining_aux;
                        if (nanosleep(requested, remaining) == -1) // system's nanosleep
                            myNanoSleep(remaining, &remaining_aux);
                    }
#endif

                public:

                    /* Returns the amount of milliseconds elapsed since the UNIX epoch. Works on both
                     * windows and linux. */
                    // http://stackoverflow.com/questions/1861294/how-to-calculate-execution-time-of-a-code-snippet-in-c

                    static unsigned long getTimeMs() {
                        // #ifdef WIN32
#ifdef _MSC_VER  // Visual C++ only !!!
                        ///* Windows */
                        //FILETIME ft;
                        //LARGE_INTEGER li;

                        ///* Get the amount of 100 nano seconds intervals elapsed since January 1, 1601 (UTC) and copy it
                        // * to a LARGE_INTEGER structure. */
                        //GetSystemTimeAsFileTime(&ft);
                        //li.LowPart = ft.dwLowDateTime;
                        //li.HighPart = ft.dwHighDateTime;

                        //uint64 ret = li.QuadPart;
                        //ret -= 116444736000000000LL; /* Convert from file time to UNIX epoch time. */
                        //ret /= 10000; /* From 100 nano seconds (10^-7) to 1 millisecond (10^-3) intervals */

                        //return ret;
						return 0;
#else
                        /* Linux */
                        struct timeval tv;

                        gettimeofday(&tv, NULL);

                        unsigned long ret = tv.tv_usec;
                        /* Convert from micro seconds (10^-6) to milliseconds (10^-3) */
                        ret /= 1000;

                        /* Adds the seconds (10^0) after converting them to milliseconds (10^-3) */
                        ret += (tv.tv_sec * 1000);

                        return ret;
#endif
                    }

#ifndef _MSC_VER  // not for Visual C++
					static void sleepMS(unsigned long milisec) {
                        timespec req = {0}, rem = {0};
                        time_t sec = (int) (milisec / 1000);
                        milisec = milisec - (sec * 1000);
                        req.tv_sec = sec;
                        req.tv_nsec = milisec * 1000 * 1000;
                        myNanoSleep(&req, &rem);
                    }
#endif
                    void markTime() {
                        // m_start = clock();
                        m_start = getTimeMs();
                    }

                    // constructor

                    VBClock() {
                        markTime();
                    }

                    double getDiffTime() {
                        checkDiffTime();
                        return m_duration;
                    }

                    void printDiffTime(std::ostream & out = std::cout) {
                        checkDiffTime();
                        out.precision(2);
                        out << "Elapsed time (in seconds) is " << getDiffTime() << ::std::endl;
                        // myCout << "Elapsed time (in seconds) is " << ::std::endl;
                    }

                    static void test() {
                        std::cout << "== VBClock::test()" << std::endl;

                        // mark execution time
                        VBClock clk;
                       
                        int milisec = 234; // an arbitrary delay
                        double eps = 1e-8;

#ifndef _MSC_VER  // not for Visual C++
                        VBClock::sleepMS(milisec);
#endif
                        double dt = clk.getDiffTime();
                        // clk.printDiffTime();
                        
                        // the time spent is confirmed to be as expected
                        VBAssert(nearEqual(dt,milisec/1000.0,eps));
                    }

                }; // end of class VBClock


            }
        }
    }
} // close namespace ::br::com::sbVB::VBLib

