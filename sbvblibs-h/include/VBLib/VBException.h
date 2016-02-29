// VBException.h

// all entities in namespace br::com::sbVB::VBLib
namespace br {
    namespace com {
        namespace sbVB {
            namespace VBLib {

                class VBException : public std::exception {
                    br::com::sbVB::VBLib::VBString m_message;
                public:

                    VBException(const char* message = "not defined")
                    : m_message(message) {
                    }
                    
                    virtual ~VBException() throw() {}

                    VBString getExplanation() const {
                        return m_message;
                    }

                    virtual const char *what() const throw() {
                        return m_message.c_str();
                    }

                    static void test() {
                        std::cout << "== VBException::test()" << std::endl;

                        try {
                            throw VBException("my message");
                        } catch (int i) {
                            VBAssert(false); // does not execute this line
                        } catch (const VBException & e) {
                            // cout << e.getExplanation() << endl;
                            VBAssert(e.getExplanation() == "my message", "exception");
                        }

                        
                        try {
                            throw VBException("my message");
                        } catch (int i) {
                            VBAssert(false); // does not execute this line
                        } catch (const exception & e) {
                            VBAssert(VBString(e.what()) == "my message", "exception");
                        }

                    }

                }; // end of class VBExcption

            }
        }
    }
} // close namespace ::br::com::sbVB::VBLib

#define VB_CUSTOM_EXCEPTION(X) \
struct X : public br::com::sbVB::VBLib::VBException { \
  X(const char *m) : VBException(m) {}; \
};
// VB_CUSTOM_EXCEPTION(ABCControlException)

