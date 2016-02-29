// VBMathException.h

////////////////////////////////////////////////////////////////////
//
// VBMathException
//
/////////////////////////////////////////////////////////////////////

namespace br {
namespace com {
namespace sbVB {
namespace VBMath {

class VBMathException : public ::br::com::sbVB::VBLib::VBException
{
public:
	VBMathException (const char *m) : VBException(m) {};
};

}}}} // close namespace ::br::com::sbVB::VBMath
