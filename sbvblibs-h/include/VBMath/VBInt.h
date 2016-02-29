// VBInt.h
namespace br {
namespace com {
namespace sbVB {
namespace VBMath {

union VBIntUnion
{
	VBIntUnion(int iValue=0)
	{
		this->i = iValue;
	}

	int i;
	struct {
		byte b[4]; // double uses 4 bytes
		// b[0] = LSB, b[3] = MSB
	};
	br::com::sbVB::VBLib::VBString getInnerValue() const
	{
		br::com::sbVB::VBLib::VBBinaryData bd;
		bd.setData(b,4);
		return bd.getStringInHex();
	}
};


template <unsigned size>
class VBInt
{
	byte m_mant[size]; // mantissa
	// m_mant[0] = LSB. m_mant[mantSize-1] = MSB
public:
	VBInt(int i=0);
	VBInt(const char *);
	void setZero();
	br::com::sbVB::VBLib::VBString getValueAsString() const;
	int getInt() const;
	void setInt(int i);
	VBInt<size> operator+(const VBInt<size> & obj) const;
	VBInt<size> operator-(const VBInt<size> & obj) const;
	VBInt<size> operator*(const VBInt<size> & obj) const;
	VBInt<size> operator/(const VBInt<size> & obj) const;

	void operator+=(const VBInt<size> & obj);
	void operator-=(const VBInt<size> & obj);
	void operator*=(const VBInt<size> & obj);
	void operator/=(const VBInt<size> & obj);

	void operator=(int i);
	void operator=(const char *str);
	// void operator=(const VBInt<size> & i);  // no need, because this one is received free
	bool operator==(const VBInt<size> & obj) const;
	bool operator==(const char *) const;
	bool isNonNegative() const; // positive or zero
	byte & operator[](int i);
	byte operator()(int i) const;
	bool operator>(const VBInt<size> & obj) const;
	
	void setMantissa(byte b, int position);
	br::com::sbVB::VBLib::VBString getInnerValue() const;

	friend ::std::ostream & operator<<(::std::ostream & s, const VBInt<size> & obj);
};

template <unsigned size>
br::com::sbVB::VBLib::VBString 
VBInt<size>::getValueAsString() const
{
	VBIntBCD<3*size> bcd = 0;
	VBIntBCD<3*size> pow = 1;
	for (int i=0; i<size; i++)
	{
//		bcd += m_mant[i] * pow;
//		pow *= 256; // 256 is the relative weight of one byte
	}
	return bcd.getValueAsString();
}

template <unsigned size>
::std::ostream & operator<<(::std::ostream & s, const VBInt<size> & obj)
{
	s << obj.getValueAsString();
	return s; 
};

template <unsigned size>
void VBInt<size>::operator=(int i)
{
	setInt(i);
};

// this is a global funcion
template <unsigned sizeInt, unsigned sizeBCD>
VBInt<sizeInt> getVBIntFromVBIntBCD(const VBIntBCD<sizeBCD> & bcd)
{
	VBInt<sizeInt> ret;
	VBInt<sizeInt> pow = 1;

	for (int i=0; i<sizeBCD; i++) // for LSB to MSB
	{
		ret += pow * VBInt<sizeInt>(bcd(i));
		pow *= 256; // 256 is the relative value of one byte (8 bits)
	}

	return ret;
	// fixme (solve the negative number problem)
}

template <unsigned size>
void VBInt<size>::operator=(const char *str)
{
	// 3 * size for VBIntBCD is more than enough space size VBInt
	VBIntBCD<3*size> thisBCD(str); 
	*this = getVBIntFromVBIntBCD<size,3*size>(thisBCD);	
};

template <unsigned size>
VBInt<size>::VBInt(const char *value)
{
	*this = value;
}

template <unsigned size>
VBInt<size>::VBInt(int i)
{
	setInt(i);
};

template <unsigned size>
void VBInt<size>::setInt(int iValue)
{
	setZero();
	VBIntUnion iu(iValue);
	for (int i=0; i<4 /* sizeof(int) == 4 */ || i < size; i++)
		m_mant[i] = iu.b[i];

};

template <unsigned size>
void VBInt<size>::setZero()
{
	for (int i=0; i<size; i++)
		m_mant[i] = 0;
};

template <unsigned size>
int VBInt<size>::getInt() const
{
	using namespace std;
	VBIntUnion iu;
	int i;
	for (i=0; i < size || i < 4 /* 4 is the size of int */; i++)
	{
		iu.b[i]=m_mant[i];
		// cout << "DEBUG iu.b[i]=" << (int)iu.b[i] << endl;
	}

	return iu.i;
};

template <unsigned size>
bool VBInt<size>::isNonNegative() const // positive or zero
{
	return (m_mant[size-1] & 0x80) == 0;
};

void addOneByte(byte a, byte b, byte oneToNext, byte & added, byte & nextOneToNext)
{
	VBIntUnion iu;
	iu.i = a+b+oneToNext;
	if (iu.i > 255)
		nextOneToNext = 1;
	else
		nextOneToNext = 0;
	added = iu.b[0]; // LSB
	// std::cout << "DEBUG iu.i=" << (int)iu.i << std::endl;
	// std::cout << "DEBUG added=" << (int)added << std::endl;
	// std::cout << "DEBUG nextOneToNext=" << (int)nextOneToNext << std::endl;
};

template <unsigned size>
VBInt<size> VBInt<size>::operator+(const VBInt<size> & obj) const
{
	VBInt<size> ret;
	byte currOneToNext,nextOneToNext;
	ret.m_mant[size-1] = this->m_mant[size-1] + obj.m_mant[size-1];
	addOneByte(this->m_mant[0],obj.m_mant[0],0,ret.m_mant[0],nextOneToNext); // LSB
	currOneToNext = nextOneToNext;
	for (int i=1; i < size; i++) // for LSB to MSB
	{
		addOneByte(this->m_mant[i],obj.m_mant[i],currOneToNext,ret.m_mant[i],nextOneToNext);
		currOneToNext = nextOneToNext;
	}
	return ret;
};

void subtractOneByte(byte a, byte b, byte oneToNext, byte & subtracted, byte & nextOneToNext)
{
	VBIntUnion iu;
	iu.i = a-b-oneToNext;
	if (iu.i < 0)
		nextOneToNext = 1;
	else
		nextOneToNext = 0;
	subtracted = iu.b[0]; // LSB
	// std::cout << "DEBUG iu.i=" << (int)iu.i << std::endl;
	// std::cout << "DEBUG added=" << (int)added << std::endl;
	// std::cout << "DEBUG nextOneToNext=" << (int)nextOneToNext << std::endl;
};
template <unsigned size>
VBInt<size> VBInt<size>::operator-(const VBInt<size> & obj) const
{
	VBInt<size> ret;
	byte currOneToNext,nextOneToNext;
	ret.m_mant[size-1] = this->m_mant[size-1] + obj.m_mant[size-1];
	subtractOneByte(this->m_mant[0],obj.m_mant[0],0,ret.m_mant[0],nextOneToNext); // LSB
	currOneToNext = nextOneToNext;
	for (int i=1; i < size; i++) // for LSB to MSB
	{
		subtractOneByte(this->m_mant[i],obj.m_mant[i],currOneToNext,ret.m_mant[i],nextOneToNext);
		currOneToNext = nextOneToNext;
	}
	return ret;
};

template <unsigned size>
VBInt<size> VBInt<size>::operator*(const VBInt<size> & obj) const
{
	VBInt<size> ret;
	// fixme
	return ret;
};

template <unsigned size>
VBInt<size> VBInt<size>::operator/(const VBInt<size> & obj) const
{
	VBInt<size> ret;
	// fixme
	return ret;
};


template <unsigned size>
void VBInt<size>::operator+=(const VBInt<size> & obj)
{
	VBInt<size> t = this->operator+(obj);
};

template <unsigned size>
void VBInt<size>::operator-=(const VBInt<size> & obj)
{
	VBInt<size> t = this->operator-(obj);
};

template <unsigned size>
void VBInt<size>::operator*=(const VBInt<size> & obj)
{
	VBInt<size> t = this->operator*(obj);
};

template <unsigned size>
void VBInt<size>::operator/=(const VBInt<size> & obj)
{
	VBInt<size> t = this->operator/(obj);
};



template <unsigned size>
br::com::sbVB::VBLib::VBString 
VBInt<size>::getInnerValue() const
{
	VBBinaryData bd;
	bd.setData(m_mant,size);
	return bd.getStringInHex();

};

template <unsigned size>
byte & VBInt<size>::operator[](int i)
{
	return m_mant[i];
};

template <unsigned size>
byte VBInt<size>::operator()(int i) const
{
	return m_mant[i];
};

template <unsigned size>
bool VBInt<size>::operator>(const VBInt<size> & obj) const
{
	if (isNonNegative() && !obj.isNonNegative())
		return true; // this is nonNegative and obj is negative
	
	if (!isNonNegative() && obj.isNonNegative())
		return false; // this is negative and obj is nonNegative

	if ((m_mant[size-1] & 0x7f) > (obj.m_mant[size-1] & 0x7f))
		return true; // compare MSB excluding the sign bit
	else
		return false;

	// compare each byte
	for (int i = size-1; i>=0; i--)
	if (m_mant[i] > obj.m_mant[i] )
		return true; 
	else 
		return false;

	// if no tests return anything, these are equal, thus return false
	return false;


};

template <unsigned size>
bool VBInt<size>::operator==(const VBInt<size> & obj) const
{
	for (int i=0; i<size; i++)
		if (m_mant[i] != obj.m_mant[i])
			return false;
	return true;
}

template <unsigned size>
bool VBInt<size>::operator==(const char *value) const
{
	return *this==VBInt<size>(value);
}

}}}} // close namespace ::br::com::sbVB::VBMath
