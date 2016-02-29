// VBPrimesFactorList.h

#include<deque>

namespace br {
namespace com {
namespace sbVB {
namespace VBMath {


template <typename IntType>
class VBPrimesFactorList
{
	struct PrimeFactor
	{
		IntType m_prime;
		IntType m_power;
		PrimeFactor(IntType prime, IntType power)
		: m_prime(prime), m_power(power)
		{}
		bool operator<(const PrimeFactor & ob) const
		{
			return m_prime < ob.m_prime;
		}
	};

public:

	std::deque<PrimeFactor> m_primeFactorContainer;

	typedef typename std::deque<PrimeFactor>::iterator iterator;

	// these friend functions are defined here
	// to allow the global function below to access private attributes of 
	// VBPrimesFactorList
	// GCD = GreatestCommonDivisor (MDC Maximo Divisor Comum)
	// LCM = Least Common Multiple (MMC Mínimo Múltiplo Comum)
	//friend void GCD(IntType n1, IntType n2, const std::deque<IntType> & primesContainer,
	//	VBPrimesFactorList<IntType> & ret, bool debug);
	//friend void GCD(IntType n1, IntType n2, const std::deque<IntType> & primesContainer,
	//	VBPrimesFactorList<IntType> & ret);
	//friend void LCM(IntType n1, IntType n2, const std::deque<IntType> & primesContainer,
	//	VBPrimesFactorList<IntType> & ret, bool debug);
	//friend void LCM(IntType n1, IntType n2, const std::deque<IntType> & primesContainer,
	//	VBPrimesFactorList<IntType> & ret);


	void sort()
	{
		// STL sort
		::std::sort(m_primeFactorContainer.begin(),m_primeFactorContainer.end());
	}

	void clear()
	{
		m_primeFactorContainer.clear();
	}

	void addPrimeFactor(IntType prime, IntType power)
	{
		m_primeFactorContainer.push_back(PrimeFactor(prime,power));
	}

	::br::com::sbVB::VBLib::VBString getString() const
	{
		::br::com::sbVB::VBLib::VBString ret;
		typename std::deque< PrimeFactor >::const_iterator it;
		for (it = m_primeFactorContainer.begin(); 
			it != m_primeFactorContainer.end(); it++)
		{
			if (it != m_primeFactorContainer.begin())
				ret += " * ";
			ret += it->m_prime;
			ret += "^";
			ret += it->m_power;
		}
		
		// and empty primes list should be set to 1
		if (ret=="")
			ret = "1";

		return ret;
	}

	IntType getInt() const
	{
		IntType ret = 1;
		typename std::deque< PrimeFactor >::const_iterator it;
		for (it = m_primeFactorContainer.begin(); 
			it != m_primeFactorContainer.end(); it++)
		{
			ret *= (IntType) pow((double)it->m_prime,(double)it->m_power);
		}
		
		return ret;
	}
};

template <typename IntType>
void factorInteger(IntType number, 
				   VBPrimesFactorList<IntType> & primesFactorList, 
				   const std::deque<IntType> & primesContainer)
{
	IntType numberOriginal = number;
	primesFactorList.clear();
	typename std::deque<IntType>::const_iterator it;

	bool containCurrPrime;
	IntType currPrimeCounter;

	// for each prime in primesContainer
	for (it = primesContainer.begin(); it != primesContainer.end(); it++)
	{
		containCurrPrime = false;
		currPrimeCounter = 0;

		// cout << "DEBUG: prime=" << *it << endl;
		while (number % *it == 0) // number contain currPrime
		{
			currPrimeCounter++;
			containCurrPrime = true;
			number /= *it; // remove currPrime from number
		}

		// if currPrime is a component of number, add it to primesFactorList
		if (containCurrPrime)
		{
			primesFactorList.addPrimeFactor(*it,currPrimeCounter);
			// cout << "DEBUG: added prime=" << *it << ", power=" << currPrimeCounter << endl;
		}

		// if the factor is already ended, no need to keep searching
		if (number==1) 
			break; 

	} // end of for primesContainer

	if (number!=1)
	{
		br::com::sbVB::VBLib::VBString message = "number ";
		message += numberOriginal;
		message += " requires to be factored requires prime greater than ";
		IntType lastPrime = primesContainer[primesContainer.size()-1];
		message += lastPrime;
		throw VBMathException(message);
	}

	
};

template <typename IntType>
void GCD(IntType n1, IntType n2, 
		 const std::deque<IntType> & primesContainer,
		 VBPrimesFactorList<IntType> & ret)
{
	GCD(n1, n2, primesContainer, ret, false);
};

template <typename IntType>
void GCD(IntType n1, IntType n2, 
		 const std::deque<IntType> & primesContainer,
		 VBPrimesFactorList<IntType> & ret, 
		 bool debug)
{
	using namespace std;
	ret.clear(); // prepare return variable

	VBPrimesFactorList<IntType> primesFactorList_1,primesFactorList_2;
	
	// factor n1
	factorInteger<IntType>(n1, primesFactorList_1, primesContainer);
	if (debug)
		cout << "DEBUG: " << n1 << " factor=" << primesFactorList_1.getString() << endl;
	
	// factor n2
	factorInteger<IntType>(n2, primesFactorList_2, primesContainer);
	if (debug)
		cout << "DEBUG: " << n2 << " factor=" << primesFactorList_2.getString() << endl;

	typename VBPrimesFactorList<IntType>::iterator it_1, it_2;
	for (it_1 = primesFactorList_1.m_primeFactorContainer.begin();
		it_1 != primesFactorList_1.m_primeFactorContainer.end(); it_1++)
	{
		if (debug)
			cout << "DEBUG: _1 prime=" << it_1->m_prime << ", pow=" << it_1->m_power << endl;
		for (it_2 = primesFactorList_2.m_primeFactorContainer.begin();
			it_2 != primesFactorList_2.m_primeFactorContainer.end(); it_2++)
		{
			if (debug)
				cout << "DEBUG: _2 prime=" << it_2->m_prime << ", pow=" << it_2->m_power << endl;
			if (it_1->m_prime == it_2->m_prime)
			{
				IntType minPower = min(it_1->m_power,it_2->m_power);
				ret.addPrimeFactor(it_1->m_prime,minPower);
				if (debug)
					cout << "DEBUG: added prime=" << it_2->m_prime << ", pow=" << minPower << endl;
			}
		}
	}

	ret.sort();
}

template <typename IntType>
void LCM(IntType n1, IntType n2, const std::deque<IntType> & primesContainer,
	VBPrimesFactorList<IntType> & ret)
{
	LCM(n1, n2, primesContainer, ret, false);
};

template <typename IntType>
void LCM(IntType n1, IntType n2, const std::deque<IntType> & primesContainer,
	VBPrimesFactorList<IntType> & ret, bool debug)
{
	using namespace std;
	ret.clear(); // prepare return variable

	VBPrimesFactorList<IntType> primesFactorList_1,primesFactorList_2;
	
	// factor n1
	factorInteger<IntType>(n1, primesFactorList_1, primesContainer);
	if (debug)
		cout << "DEBUG: " << n1 << " factor=" << primesFactorList_1.getString() << endl;
	
	// factor n2
	factorInteger<IntType>(n2, primesFactorList_2, primesContainer);
	if (debug)
		cout << "DEBUG: " << n2 << " factor=" << primesFactorList_2.getString() << endl;

	bool commonPrime;
	typename VBPrimesFactorList<IntType>::iterator it_1, it_2;
	for (it_1 = primesFactorList_1.m_primeFactorContainer.begin();
		it_1 != primesFactorList_1.m_primeFactorContainer.end(); it_1++)
	{
		commonPrime = false;
		if (debug)
			cout << "DEBUG: _1 prime=" << it_1->m_prime << ", pow=" << it_1->m_power << endl;
		for (it_2 = primesFactorList_2.m_primeFactorContainer.begin();
			it_2 != primesFactorList_2.m_primeFactorContainer.end(); it_2++)
		{
			if (debug)
				cout << "DEBUG: _2 prime=" << it_2->m_prime << ", pow=" << it_2->m_power << endl;
			if (it_1->m_prime == it_2->m_prime)
			{
				commonPrime = true;
				IntType maxPower = max(it_1->m_power,it_2->m_power);
				ret.addPrimeFactor(it_1->m_prime,maxPower);
				if (debug)
					cout << "DEBUG: added common prime=" << it_2->m_prime 
						<< ", pow=" << maxPower << endl;
			}
		}

		if (!commonPrime)
		{
			ret.addPrimeFactor(it_1->m_prime,it_1->m_power);
			if (debug)
				cout << "DEBUG: added n1 prime=" << it_1->m_prime 
					<< ", pow=" << it_1->m_power << endl;
		}
	}


	// at this point all primes of n1 and commom primes were added.
	// now non-commom primes of n2 will be added
	for (it_2 = primesFactorList_2.m_primeFactorContainer.begin();
		it_2 != primesFactorList_2.m_primeFactorContainer.end(); it_2++)
	{
		commonPrime = false;
		if (debug)
			cout << "DEBUG: _2 prime=" << it_2->m_prime << ", pow=" << it_2->m_power << endl;
		for (it_1 = primesFactorList_1.m_primeFactorContainer.begin();
			it_1 != primesFactorList_1.m_primeFactorContainer.end(); it_1++)
		{
			if (debug)
				cout << "DEBUG: _1 prime=" << it_1->m_prime << ", pow=" << it_1->m_power << endl;
			if (it_1->m_prime == it_2->m_prime)
			{
				commonPrime = true;
				break; 
				// if it's known that the prime is common, there's no need to
				// keep inner search
			}
		}

		if (!commonPrime)
		{
			ret.addPrimeFactor(it_2->m_prime,it_2->m_power);
			if (debug)
				cout << "DEBUG: added n2 prime=" << it_2->m_prime 
					<< ", pow=" << it_2->m_power << endl;
		}
	}

	ret.sort();
};



}}}} // close namespace ::br::com::sbVB::VBMath

