// VBDebugFloat.h
// based on IEEE Standard for Floating-Point Arithmetic (IEEE 754)

namespace br {
namespace com {
namespace sbVB {
namespace VBMath {

struct VBDebugFloatReport {
	unsigned m_plus;
	unsigned m_minus;
	unsigned m_multiply;
	unsigned m_divide;

	unsigned m_plusEqual;
	unsigned m_minusEqual;
	unsigned m_multiplyEqual;
	unsigned m_divideEqual;

	unsigned m_equal;
	unsigned m_defaultConstructor;
	unsigned m_copyConstructor;
	unsigned m_cast;

	VBDebugFloatReport(
		unsigned plus=0,
		unsigned minus=0,
		unsigned multiply=0,
		unsigned divide=0,

		unsigned plusEqual=0,
		unsigned minusEqual=0,
		unsigned multiplyEqual=0,
		unsigned divideEqual=0,

		unsigned equal=0,
		unsigned defaultConstructor=0,
		unsigned copyConstructor=0,
		unsigned cast=0
		) :
	m_plus(plus),
	m_minus(minus),
	m_multiply(multiply),
	m_divide(divide),

	m_plusEqual(plusEqual),
	m_minusEqual(minusEqual),
	m_multiplyEqual(multiplyEqual),
	m_divideEqual(divideEqual),
	
	m_equal(equal),
	m_defaultConstructor(defaultConstructor),
	m_copyConstructor(copyConstructor),
	m_cast(cast)
	{
	}

	friend std::ostream & operator<<(std::ostream & s, 
		const VBDebugFloatReport & r) {
			s << r.m_plus << "," << 
				r.m_minus << "," << 
				r.m_multiply << "," << 
				r.m_divide << " | " << 

				r.m_plusEqual << "," << 
				r.m_minusEqual << "," << 
				r.m_multiplyEqual << "," << 
				r.m_divideEqual << " | " << 
	
				r.m_equal << "," << 
				r.m_defaultConstructor << "," << 
				r.m_copyConstructor << "," << 
				r.m_cast;
		return s;
	}

	void clear() {
		m_plus=0;
		m_minus=0;
		m_multiply=0;
		m_divide=0;

		m_plusEqual=0;
		m_minusEqual=0;
		m_multiplyEqual=0;
		m_divideEqual=0;
		
		m_equal=0;
		m_defaultConstructor=0;
		m_copyConstructor=0;
		m_cast=0;
	}
};

// no warning in conversion of double to float 
#pragma warning(disable:4305)

template <typename T>
class VBDebugFloat
{
	T m_data;
public:
	static VBDebugFloatReport m_report;

	VBDebugFloat(T data=0) 
		: m_data(data)
	{
		m_report.m_defaultConstructor++;
	}

	VBDebugFloat(const VBDebugFloat<T> & obj)
	{
		m_report.m_copyConstructor++;
		m_data = obj.m_data;
	}

	void operator=(VBDebugFloat<T> obj) {
		m_report.m_equal++;
		m_data = obj.m_data;
	}

	// cast to T 
	operator T() {
		m_report.m_cast++;
		return m_data;
	}

	void operator+=(VBDebugFloat<T> obj) {
		m_report.m_plusEqual++;
		m_data += obj.m_data;
	}

	void operator-=(VBDebugFloat<T> obj) {
		m_report.m_minusEqual++;
		m_data -= obj.m_data;
	}

	void operator*=(VBDebugFloat<T> obj) {
		m_report.m_multiplyEqual++;
		m_data *= obj.m_data;
	}

	void operator/=(VBDebugFloat<T> obj) {
		m_report.m_divideEqual++;
		m_data /= obj.m_data;
	}

	VBDebugFloat<T> operator+(VBDebugFloat<T> obj) {
		m_report.m_plus++;
		return VBDebugFloat<T>(m_data + obj.m_data);
	}

	VBDebugFloat<T> operator-(VBDebugFloat<T> obj) {
		m_report.m_minus++;
		return VBDebugFloat<T>(m_data - obj.m_data);
	}

	VBDebugFloat<T> operator*(VBDebugFloat<T> obj) {
		m_report.m_multiply++;
		return VBDebugFloat<T>(m_data * obj.m_data);
	}

	VBDebugFloat<T> operator/(VBDebugFloat<T> obj) {
		m_report.m_divide++;
		return VBDebugFloat<T>(m_data / obj.m_data);
	}

	T getDouble() const {
		return m_data;
	}

};

template <typename T>
VBDebugFloatReport VBDebugFloat<T>::m_report = 
  VBDebugFloatReport(0,0,0,0,0,0,0,0,0,0,0,0);


typedef VBDebugFloat<double> VBDoubleDebug;

}}}} // close namespace ::br::com::sbVB::VBMath
