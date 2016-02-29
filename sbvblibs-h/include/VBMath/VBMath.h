// VBMath.h
#ifndef __VBMATH__
#define __VBMATH__


////////////////////////////////////////////////////////////////////
// VBMath precious includes
/////////////////////////////////////////////////////////////////////

#include <complex> // namespace version of header
#include <cmath> // fabs
#include <cfloat> // EPSILON
#include <algorithm> // sort 
#include <deque> 
#include <fstream> 
#include <typeinfo>

////////////////////////////////////////////////////////////////////
// VBMath classes
/////////////////////////////////////////////////////////////////////

#include "VBMath/VBMathException.h"
#include "VBMath/VBNumTrait.h" // before VBMatrix
#include "VBMath/VBMatrix.h" // requires VBNumTrait
#include "VBMath/VBLTID.h" // VBMatrix.h must be included before
#include "VBMath/VBParser.h" 
#include "VBMath/VBPrimesFactorList.h" 
#include "VBMath/VBDebugDouble.h" 
#include "VBMath/VBMath_raw.h"


// experimental classes begin
// #include "VBMath/VBIntBCD.h" 
// #include "VBMath/VBInt.h" // VBIntBCD.h must be included before
// #include "VBMath/VBDouble.h" // VBInt.h must be included before
// #include "VBMath/VBDoubleBCD.h" // VBInt.h must be included before
// experimental classes end

#endif // __VBMATH__

