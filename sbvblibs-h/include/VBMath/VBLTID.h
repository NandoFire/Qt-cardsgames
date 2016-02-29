// VBLTID.H

namespace br {
namespace com {
namespace sbVB {
namespace VBMath {


////////////////////////////////////////////////////////////////////
//
// class VBLTID - Linear Time Invariant Discrete
//
/////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////
// definitions for debug and memory chech



/* Villas-Boas class for LTI (Linear Time Invariant) 
 Discrete (and SISO - Single Input Single Output)

         b0 z^-(kd) + b1 z^-(1+kd) + ... +  b(nb-1) z^-(2+kd+nb-1)
 g(z) = --------------------------------------------------------------
             1 + a0 z^-1 + a1 z^-2 + ... +  a(na-1) z^-(na-1)

 Example: let the LTI continuous system below

              s + 1
 g(s) = ------------------
         s^2 + 4 s + 5

 if the LTI above is discretized with sampling rate of h=0.1,
 that produces the LTID (Discrete) as below
 kd=1, nb=2, na=2

          0.086113911125402 z^-1 -0.077906105739797 z^-2 
 g(z) = -------------------------------------------------
         1 -1.629281019107614 z^-1 + 0.670320046035640 z^-2

*/

template <class T>
class VBLTID 
{
	VBMatrix<T> m_num, m_den, m_inputHistory, m_outputHistory;
	unsigned m_kd;    // discrete dead time
	unsigned m_ca, m_cb; // rotating counter for 
	bool m_initialized; // stores whether the system is initialized or not
	
	// zero value for all coefitients
	//void zeroValue() {
	//	for (unsigned i=0 ; i < m_dim ; i++) {
	//		m_num[i] = m_den[i] =
	//			m_outputHistory[i] = m_inputHistory[i] = 0;
	//	}
	//}
	
	void showHistory() {
		using namespace std;
		//		cout << "%%%%%=in=" << endl << m_inputHistory << endl;
		//		cout << "%%%%%=out=" << endl << m_outputHistory << endl;
		cout << "m_ca=" << m_ca << " ; m_cb=" << m_cb << endl;
		cout << m_inputHistory << endl;
		cout << m_outputHistory << endl;
	}
	
	void privateConstructor() {
		m_initialized = false;
		m_ca = 0; 
		m_cb = 0;
	}
	
public:
	
	VBLTID () { // default constructor
		privateConstructor();
	}
	
	VBLTID (const VBLTID<T> & obj) { // copy constructor
		privateConstructor();
		m_ca = obj.m_ca; 
		m_cb = obj.m_cb; 
		m_initialized = obj.m_initialized;
		m_kd = obj.m_kd;
		m_num = obj.m_num;
		m_den = obj.m_den;
		m_inputHistory = obj.m_inputHistory;
		m_outputHistory = obj.m_outputHistory;
	}
	
	void operator=(const VBLTID<T> & obj) { // operator=
		m_ca = obj.m_ca; 
		m_cb = obj.m_cb; 
		m_initialized = obj.m_initialized;
		m_kd = obj.m_kd;
		m_num = obj.m_num;
		m_den = obj.m_den;
		m_inputHistory = obj.m_inputHistory;
		m_outputHistory = obj.m_outputHistory;
	}
	
	void setDim(unsigned na,unsigned nb,unsigned kd) {
		m_kd = kd;
		m_cb = kd;
		m_num.redim(nb);
		m_den.redim(na);
		m_inputHistory.redim(nb+kd);
		m_outputHistory.redim(na);
		m_initialized = true;
	}
	
	unsigned getNa() {
		return m_den.getRows();
	}
	
	unsigned getNb() {
		return m_num.getRows();
	}
	
	unsigned getKd() {
		return m_kd;
	}
	
	// enter numerator constants. If pos too big or not initialized, do nothing
	void setNum(unsigned pos, T value) {
		if (m_initialized && pos < m_num.getRows()) 
			m_num[pos] = value;
	}
	
	// enter denominator constants. If pos too big or not initialized, do nothing
	void setDen(unsigned pos, T value) {
		if (m_initialized && pos < m_den.getRows()) 
			m_den[pos] = value;
	}
	
	T process(T in) {
		// showHistory(); // for debug only
		T ret;
		if (!m_initialized) return 0;
		unsigned i, na, nbkd;
		
		nbkd = m_num.getRows() + m_kd;
		na = m_den.getRows();
		
		// place new input to stored state
		m_inputHistory[0] = in; 
		
		// process new output
		ret = 0;
		// numerator
		for (i=0 ; i < m_num.getRows() ; i++) {
			// cout << "DBnum-w: " << m_inputHistory[i+m_kd] << " * " << m_num[i] << endl;
			ret += m_inputHistory[i+m_kd]*m_num[i];
		}
		// denominator
		for (i=0 ; i < na ; i++) {
			// cout << "DBden-w: " << m_outputHistory[i] << " * " << m_den[i] << endl;
			ret -= m_outputHistory[i]*m_den[i];;
		}
		
		// adjust LTI's stored state for next process
		// numerator
		for (i=nbkd-1 ; i > 0 ; i--) {
			m_inputHistory[i] = m_inputHistory[i-1];
		}
		// denominator
		for (i=na-1 ; i > 0 ; i--) {
			m_outputHistory[i] = m_outputHistory[i-1];
		}
		
		// place calculated output to stored state
		m_outputHistory[0] = ret;
		
		return ret;
	}
	
	T processFast (T in) {
		T ret;
		if (!m_initialized) return 0;
		unsigned i, control, na, nb, nbkd;
		
		nb = m_num.getRows();
		nbkd = nb + m_kd;
		na = m_den.getRows();
		
		// converting to long to be able to handle negative 
		long cb_aux = (long) m_cb - (long) m_kd; 
		// I should change this for a solution without a loop
		while (cb_aux < 0)
			cb_aux += nbkd;
		
		// place new input to stored state
		m_inputHistory[cb_aux] = in; 
		
		// showHistory(); // for debug only
		
		// process new output
		ret = 0;
		unsigned aux = nb+m_kd-m_cb;
		// numerator
		for (control=0, i=m_cb ; i < nbkd ; i++, control++) {
			if (control >= nb) break;
			// cout << "DBnum: " << m_inputHistory[i] << " * " << m_num[i-m_cb] << "" << endl;
			ret += m_inputHistory[i]*m_num[i-m_cb];
		}
		for (i=0 ; control < nb; i++, control++) {
			// cout << "DBnum2: " << m_inputHistory[i] << " * " << m_num[i+aux] << "" << endl;
			ret += m_inputHistory[i]*m_num[i+aux];
		}
		// denominator
		for (i=m_ca+1 ; i < na ; i++) {
			// cout << "DBden: " << m_outputHistory[i] << " * " << m_den[i-m_ca-1] << endl;
			ret -= m_outputHistory[i]*m_den[i-m_ca-1];
		}
		for (i=0 ; i <= m_ca; i++) {
			// cout << "DBden2: " << m_outputHistory[i] << " * " << m_den[i+na-m_ca-1] << endl;
			ret -= m_outputHistory[i]*m_den[i+na-m_ca-1];
		}
		
		// place calculated output to stored state
		m_outputHistory[m_ca] = ret;
		
		// adjust m_ca and m_cb for next iteration
		if (m_cb == 0)
			m_cb = nb+m_kd-1;
		else
			m_cb--;
		if (m_ca == 0)
			m_ca = na-1;
		else
			m_ca--;
		
		
#if 0
		m_ca++;
		if (m_ca >= na)
			m_ca = 0;
		m_cb++;
		if (m_cb >= (nb+m_kd) )
			m_cb = 0;
		
		if (m_cb == 0)
			m_cb = nb+m_kd-1;
		else
			m_cb--;
		if (m_ca == 0)
			m_ca = na-1;
		else
			m_ca--;
		
#endif
		
		return ret;
	}
}; // end of class VBLTID

////////////////////////////////////////////////////////////////////
// Definition of types based on generic class VBLTID
/////////////////////////////////////////////////////////////////////

typedef VBLTID<float> VBLTID_F;
typedef VBLTID<double> VBLTID_D;
typedef VBLTID<long double> VBLTID_LD;

}}}} // close namespace ::br::com::sbVB::VBMath
