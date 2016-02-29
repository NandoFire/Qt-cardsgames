// VBDouble.h


// based on IEEE Standard for Floating-Point Arithmetic (IEEE 754)

namespace br {
namespace com {
namespace sbVB {
namespace VBMath {


union VBDoubleUnion
{
public:
	VBDoubleUnion(double d=0)
	{
		this->d = d;
	}
	double d;
	struct {
		byte b[8]; // double uses 8 bytes
	};
	bool isNonNegative() const // positive or zero
	{
		return (b[7] & 0x80) == 0;
	}
	int getExp() const
	{
		// 11 bits of exp, so shift of 5 bits from 16 bits od 3 bytes
		byte hi = (b[7] & 0x7f) >> 5;

		// int ret = (hi & 0x0f) * 16 + (hi & 0xf0) + (b[6] & 0x0f) * 16 + b[6] & 0xf0;
		int ret = (hi & 0x0f);
		ret += (hi & 0xf0) * 16;
		ret += (b[6] & 0x0f);
		ret += b[6] & 0xf0  * 16;
		return ret;
	}
	int getMantLo() const
	{
		VBIntUnion ret;
		ret.b[0] = b[0];
		ret.b[1] = b[1];
		ret.b[2] = b[2];
		ret.b[3] = b[3];
		return ret.i;

	}
	int getMantHi() const
	{
		VBIntUnion ret;
		ret.b[0] = b[5];
		ret.b[1] = b[4];
		ret.b[2] = 0;
		ret.b[3] = 0;
		return ret.i;
	}
	br::com::sbVB::VBLib::VBString getInnerValue() const
	{
		br::com::sbVB::VBLib::VBBinaryData bd;
		bd.setData(b,8);
		return bd.getStringInHex();
	}
};

#if 0
template <unsigned mantSize, unsigned expSize>
class VBDouble
{
	VBInt<mantSize> m_mant;   // mantissa
	VBInt<expSize>  m_exp;	  // exponential
public:
	VBDouble(double d=0);
	double getDouble() const;
	void setDouble(double d);
	VBDouble<mantSize,expSize> operator+(const VBDouble<mantSize,expSize> & obj) const;
	VBDouble<mantSize,expSize> operator-(const VBDouble<mantSize,expSize> & obj) const;
	VBDouble<mantSize,expSize> operator*(const VBDouble<mantSize,expSize> & obj) const;
	VBDouble<mantSize,expSize> operator/(const VBDouble<mantSize,expSize> & obj) const;
	void operator=(double d);
	
	bool nearEqual(const VBDouble<mantSize,expSize> & obj,
		const VBDouble<mantSize,expSize> & eps) const;

	void setMantissa(byte b, int position);
	void setExp(byte b, int position);
	br::com::sbVB::VBLib::VBString getInnerValue() const;
};

template <unsigned mantSize, unsigned expSize>
void VBDouble<mantSize,expSize>::operator=(double d)
{
	setDouble(d);
}


template <unsigned mantSize, unsigned expSize>
VBDouble<mantSize,expSize>::VBDouble(double d)
{
	setDouble(d);
}

template <unsigned mantSize, unsigned expSize>
double VBDouble<mantSize,expSize>::getDouble() const
{
	VBDoubleUnion du;
	int i;
	for (i=0; i < expSize || i < 2 /* 2 is the size of double exp */; i++)
		du.b[i]=m_exp(i);
	for (i=0; i < mantSize || i < 6 /* 6 is the size of double mantissa */; i++)
		du.b[i+2]=m_mant(i);
	return du.d; 
}

template <unsigned mantSize, unsigned expSize>
void VBDouble<mantSize,expSize>::setDouble(double d)
{
	// fixme
}

template <unsigned mantSize, unsigned expSize>
VBDouble<mantSize,expSize> 
VBDouble<mantSize,expSize>::operator+(const VBDouble<mantSize,expSize> & obj) const
{
	return VBDouble(2.2); // fixme
}

template <unsigned mantSize, unsigned expSize>
VBDouble<mantSize,expSize> 
VBDouble<mantSize,expSize>::operator-(const VBDouble<mantSize,expSize> & obj) const
{
	return VBDouble(3.3); // fixme
}

template <unsigned mantSize, unsigned expSize>
VBDouble<mantSize,expSize> 
VBDouble<mantSize,expSize>::operator*(const VBDouble<mantSize,expSize> & obj) const
{
	return VBDouble(4.4); // fixme
}

template <unsigned mantSize, unsigned expSize>
VBDouble<mantSize,expSize> 
VBDouble<mantSize,expSize>::operator/(const VBDouble<mantSize,expSize> & obj) const
{
	return VBDouble(5.5); // fixme
}

template <unsigned mantSize, unsigned expSize>
bool VBDouble<mantSize,expSize>::nearEqual(const VBDouble<mantSize,expSize> & obj,
										   const VBDouble<mantSize,expSize> & eps) const
{
	if (this->m_exp > obj.m_exp)
	{
	}
	else
	{
	}
	
	// at this point, this.exp and obj.exp must be the same, so comparison
	// can be done only by comparing the mantissa
	
	// byte diffMant[mantSize];
	
	return true; // fixme
}

template <unsigned mantSize, unsigned expSize>
void VBDouble<mantSize,expSize>::setMantissa(byte b, int position)
{
	m_mant[position] = b;
}

template <unsigned mantSize, unsigned expSize>
void VBDouble<mantSize,expSize>::setExp(byte b, int position)
{
	m_exp[position] = b;
}

template <unsigned mantSize, unsigned expSize>
br::com::sbVB::VBLib::VBString 
VBDouble<mantSize,expSize>::getInnerValue() const
{
	VBBinaryData bd;
	VBString ret;

	bd.setData(m_exp,expSize);
	ret += bd.getStringInHex();
	ret += "|";
	bd.setData(m_mant,mantSize);
	ret += bd.getStringInHex();

	return ret;
}
#endif

}}}} // close namespace ::br::com::sbVB::VBMath
