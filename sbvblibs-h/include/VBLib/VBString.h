// VBString.h

// all entities in namespace br::com::sbVB::VBLib
namespace br {
    namespace com {
        namespace sbVB {
            namespace VBLib {

                class VBString {
                    unsigned m_size; // number of char inside the string
                    char *m_str; // the pointer to the string data
                    
                    static const char *m_chgHiCaps; // = "�����������������������Ǫ�";
                    static const char *m_chgLoCaps; // = "�����������������������窺";
                    static const char *m_chgHiCapsSafe; // = "AEIOUAEIOUAEIOUAEIOUAONCAO";
                    static const char *m_chgLoCapsSafe; // = "aeiouaeiouaeiouaeiouaoncao";

                    void allocStr(unsigned size_in) // redim
                    {
                        // m_size = abs(size_in); // not necessary
                        m_size = size_in;
                        if (m_str) delete [] m_str;
                        if (m_size >= 0) {
                            m_str = new char [m_size + 1];
                            m_str[0] = 0; // terminate string
                        } else {
                            m_str = NULL;
                        }
                    }

                    void privateConstructor() {
                        m_str = NULL; // indispensable
                    }


                public:

                    // default constructor

                    VBString(const char* s = "") {
                        privateConstructor();
                        if (!s)
                            s = "";
                        int len = strlen(s);
                        allocStr(len);
                        strcpy(m_str, s);
                    }

                    // copy constructor

                    VBString(const VBString & s) {
                        privateConstructor();
                        allocStr(s.m_size);
                        if (s.m_size) strcpy(m_str, s.m_str);
                    }

                    // destructor

                    virtual ~VBString() {
                        myDelete();
                    }

                    VBString getFileExtension() {
                        char tok = '.';
                        return strtok(tok, tokCount(tok));
                    }

                    void replace(const char *find, const char *replaceStr) {
                        strschg(find, replaceStr);
                    }; // alternative name for strschg


                    // basic utilities

                    unsigned getLength() const {
                        return m_size;
                    }; // get the string length (number of chars)

                    unsigned length() const {
                        return m_size;
                    }; // get the string length (number of chars)

                    unsigned size() const {
                        return m_size;
                    }; // get the string length (number of chars)

                    //                    bool IsEmpty() const; // true if zero length
                    //                    void Empty(); // clear contents to empty
                    //                    void myDelete(); // release memory used by object

                    operator const char*() const {
                        return m_str;
                    }; // VBString type cast for "const char*"

                    const char *getStr() const {
                        return m_str;
                    };

                    const char *c_str() const {
                        return m_str;
                    };

                    bool existSubstring
                    (const char* subStr, bool caseSens = true) const {
                        bool ret;
                        afterFind(subStr, ret, caseSens);

                        // old code
                        // bool ret = (bool) (::strstr((*this).getStr(), subStr) != 0); 
                        // ::strstr is the global strstr, 
                        return ret;
                    }

                    VBString strAfterPosition(const unsigned pos) const {
                        return strAfter(pos);
                    };

                    VBString strUntilPosition(const unsigned pos) const {
                        return strBefore(pos + 1);
                    };

                    VBString strInside(unsigned from, unsigned to) const {
                        return this->strAfterPosition(from).strUntilPosition(to - from);
                    }

                    bool validEmail() const {
                        const char *validChars = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!#$&*-_";
                        const char *validSymbols = ".@";
                        const char *at = "@";
                        if (!validHelper(validChars, validSymbols, 3)) return false;
                        // there must be somethig after "@"
                        br::com::sbVB::VBLib::VBString aux = afterFind(at);
                        if (aux.length() == 0) return false;
                        // no @ after the first @
                        if (aux.existSubstring(at)) return false;
                        // there must be something before "@"
                        aux = beforeFind(at);
                        if (aux.length() == 0) return false;
                        return true;
                    }

                    bool validAddress() const {
                        const char *validChars =
                                "0123456789abcdefghijklmnopqrstuvwxyz"
                                "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
                        const char *validSymbols = ".,-/:";
                        if (!validHelper(validChars, validSymbols, 2)) return false;
                        return true;
                    }

                    char intToChar(int num) const {
                        return (num + 48);
                    }

                    int charToInt(char ch) const {
                        return (ch - 48);
                    }

                    // extractor

                    friend std::istream & operator>>(std::istream & stream,
                            br::com::sbVB::VBLib::VBString & obj) {
                        using namespace std;
                        // string version begin
                        std::string str;
                        std::getline(stream, str, '\n');
                        obj = str.c_str();
                        // string version end

                        //                        // buffer version begin
                        //                        const int sizeMax = 1000*1000;
                        //                        char str[sizeMax];
                        //                        stream.getline(str,sizeMax,'\n');
                        //                        obj = str;
                        //                        // buffer version end

//                        cout << "DEBUG this:" << obj << endl;
//                        cout << "DEBUG str:" << str << endl;
                        return stream;
                    }

                    // insersor

                    friend std::ostream & operator<<(std::ostream & stream,
                            VBString & obj) {
                        if (obj.m_size > 0)
                            stream << obj.m_str;
                        return stream;
                    }
                    // for a given 9 digits, return the 2 digits to complete a CIC

                    VBString rightCIC() const {
                        br::com::sbVB::VBLib::VBString ret;
                        br::com::sbVB::VBLib::VBString CICleft = strInside(0, 8); // the left part of CIC of this
                        unsigned digit1 = findDigit(10, 9, CICleft);
                        CICleft += intToChar(digit1);
                        unsigned digit2 = findDigit(11, 10, CICleft);
                        ret = intToChar(digit1);
                        ret += intToChar(digit2);
                        return ret;
                    }

                    bool validCIC() const {
                        const char *validChars = "0123456789";
                        const char *validSymbols = "-.";
                        if (!validHelper(validChars, validSymbols, 11, 15)) return false;

                        // eliminate symbols
                        VBString ob;
                        for (unsigned i = 0; i < length(); i++) {
                            if (charIsValid((*this)[i], validChars))
                                ob += (*this)[i];
                        }
                        // now ob has the cic without the symbols. 
                        // ob has only validChars, and length must be 11
                        if (ob.length() != 11) return false;

                        VBString CICright = ob.rightCIC();

                        // if calculated CICright does not match with given CICright, that's false CIC
                        if (ob.strInside(9, 10) != CICright)
                            return false;

                        return true;
                    }

                    unsigned findDigit(int i, int lenght, const char *buffer) const {
                        unsigned sum = 0;
                        unsigned ret = 0;

                        for (unsigned k = 0; k < lenght; k++) {
                            sum += charToInt(buffer[k]) * i;
                            i--;
                        };

                        ret = 11 - (sum % 11);
                        if ((ret == 10) || (ret == 11))
                            ret = 0;

                        return ret;
                    }

                    bool validName() const {
                        const char *validChars = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
                        const char *validSymbols = "-_";
                        if (!validHelper(validChars, validSymbols, 2)) return false;
                        return true;
                    }

                    bool validPhone() const {
                        const char *validChars = "0123456789";
                        const char *validSymbols = "-.";
                        if (!validHelper(validChars, validSymbols, 5)) return false;
                        return true;
                    }

                    bool validZip() const {
                        const char *validChars = "0123456789";
                        const char *validSymbols = "-.";
                        if (!validHelper(validChars, validSymbols, 5, 10)) return false;
                        return true;
                    }

                    bool validCreditCardNumber() const {
                        const char *validChars = "0123456789";
                        const char *validSymbols = "-.";
                        if (!validHelper(validChars, validSymbols, 16, 19)) return false;

                        // eliminate symbols
                        unsigned i;
                        VBString ob;
                        for (i = 0; i < length(); i++) {
                            if (charIsValid((*this)[i], validChars))
                                ob += (*this)[i];
                        }
                        // now ob has the cic without the symbols. 
                        // ob has only validChars, and length must be 11
                        if (ob.length() != 16) return false;

                        int sum = 0;
                        int oddvalue = 0, evenvalue = 0;
                        int odd = 0, even = 0;

                        for (i = 0; i < ob.length(); i++) {
                            if (i % 2 == 0) {
                                oddvalue = charToInt(ob[i]);
                                if (2 * oddvalue > 9)
                                    oddvalue = 2 * oddvalue - 9;
                                else oddvalue = 2 * oddvalue;
                                odd += oddvalue;
                            } else {
                                evenvalue = charToInt(ob[i]);
                                even += evenvalue;
                            }
                        }
                        sum = even + odd;
                        if ((sum > 150) || (sum % 10 != 0))
                            return false;
                        return true;
                    }

                    bool validHelper(const char *validChars, const char* validSymbols,
                            unsigned minSize = 0, unsigned maxSize = 0) const {
                        // if user sets non-zero max or min, check size
                        unsigned length = getLength();
                        if (minSize > 0 && length < minSize) return false;
                        if (maxSize > 0 && length > maxSize) return false;
                        unsigned i;

                        // chars of *this must be validChars or validSymbols
                        for (i = 0; i < length; i++) {
                            if (!(charIsValid((*this)[i], validChars)
                                    || charIsValid((*this)[i], validSymbols))) return false;
                        }

                        // if a char is a symbol, the next char should not be a symbol
                        for (i = 0; i < length - 1; i++) {
                            if (charIsValid((*this)[i], validSymbols) &&
                                    !charIsValid((*this)[i + 1], validChars)) return false;
                        }

                        return true;
                    }

                    bool charIsValid(char ch, const char *validChars) const {
                        unsigned i;
                        for (i = 0; i < strlen(validChars); i++)
                            if (ch == validChars[i]) return true;
                        return false;
                    }


                    // true if zero length

                    bool IsEmpty() const {
                        return (getLength() == 0);
                    }

                    // clear contents to empty

                    void Empty() {
                        *this = "";
                    }

                    // convert this string to debug format

                    VBString debug(int format) const {
                        VBString ret = *this;
                        VBString aux, aux2;
                        unsigned i;
                        switch (format) {
                            case 1:
                                ret = "";
                                for (i = 0; i < getLength(); i++) {
                                    aux = m_str[i];
                                    aux.simpleEncrypt(0); // convert to hexa
                                    ret += aux;
                                    ret += ".";
                                }
                                break;
                            case 2:
                                ret = "";
                                for (i = 0; i < getLength(); i++) {
                                    char ch = m_str[i];
                                    bool charOK = ch >= ' ' && ch <= 'z' + 4;
                                    if (charOK)
                                        aux = ch;
                                    else
                                        aux = ".";
                                    ret += aux;
                                    ret += "  ";
                                }
                                break;
                            case 3:
                                aux = ret;
                                ret = aux.debug(1);
                                ret += '\n';
                                ret += aux.debug(2);
                                break;
                            default:
                            {
                            } // do nothing
                        }
                        return ret;
                    }

                    void wipeCtrmM() {
                        char lastChar = (*this)[getLength() - 1];
                        if (lastChar == 13) // 13 = ^M
                            * this = strInside(0, getLength() - 2);
                    }


                    // return true if left side of this is equal to subStr

                    bool leftSideIs(const char* subStr) const {
                        unsigned length = strlen(subStr);
                        bool ret = strInside(0, length - 1) == subStr;
                        return ret;
                    }

                    // return the string at right of this and leftString argument
                    // example: this=="abcdef", leftString="abc", return="def"

                    VBString separateLeftString
                    (const char* leftString) const {
                        unsigned length = strlen(leftString);
                        return strInside(length, getLength());
                    }


                    // Example: z_aux = 15, return 'f'
                    // Example: z_aux = 3, return = '3'

                    unsigned char p_ToAscii(unsigned char z_aux) const {
                        unsigned char z = tolower(z_aux);
                        if (z < 10) z += '0';
                        else z += 'a' - 10;
                        return z;
                    }

                    // Example: z_aux = 'F' or 'f',  return = 15
                    // Example: z_aux = '3', return = 3

                    unsigned char p_ToAsciiReverse(unsigned char z_aux) const {
                        unsigned char z = tolower(z_aux);
                        if (z < ('9' + 1)) z -= '0';
                        else z -= 'a' - 10;
                        return z;
                    }

                    // Example: ch = 'A' (input) ,  ch_hex = "41" (output)

                    void p_toHex(unsigned char ch, char *ch_hex) const {
                        unsigned char a;
                        a = (ch & 0x0f);
                        ch_hex[1] = p_ToAscii(a); // LSB
                        a = (ch & 0xf0) / 16;
                        ch_hex[0] = p_ToAscii(a);
                        ; // MSB
                    }

                    // Example: ch_hex = "41",  return = 'A'

                    unsigned char p_toHexReverse(char *ch_hex) const {
                        unsigned char ret;
                        int msb, lsb;
                        msb = p_ToAsciiReverse(ch_hex[0]);
                        lsb = p_ToAsciiReverse(ch_hex[1]);
                        ret = lsb + msb * 16;
                        return ret;
                    }


                    // encrypts object using code [0~255]

                    void simpleEncrypt(unsigned short code) {
                        // code is any number from 0 to 255
                        br::com::sbVB::VBLib::VBString ret;
                        unsigned len = strlen(m_str);
                        unsigned char ch;
                        char ch_hex[3];
                        ch_hex[2] = 0; // string terminator
                        for (unsigned i = 0; i < len; i++) {
                            ch = m_str[i] ^ code; // ^ is bitwise xor
                            p_toHex(ch, ch_hex);
                            ret += ch_hex; // adding string
                        }
                        *this = ret;
                    }

                    // de-encrypts object using code

                    void simpleEncryptReverse(unsigned short code) {
                        // code is any number from 0 to 255
                        VBString ret;
                        unsigned len = strlen(m_str);
                        char ch[2];
                        ch[1] = 0; // string terminator
                        char ch_hex[2];
                        for (unsigned i = 0; i < len / 2; i++) {
                            ch_hex[0] = m_str[2 * i];
                            ch_hex[1] = m_str[2 * i + 1];
                            ch[0] = p_toHexReverse(ch_hex);
                            ch[0] ^= code; // ^ is bitwise xor
                            ret += ch;
                        }
                        *this = ret;
                    }

                    // return the number of sub-strings
                    // new bug free code. Thanks to Leo Huf Campos Braga, November 21th, 2005

                    unsigned countSubString
                    (const char *subStr, bool caseSens = true) const {
                        unsigned ret = 0;
                        bool found;
                        VBString a = afterFind(subStr, found, caseSens);
                        while (found) {
                            // cout << "DEBUG: " << a << endl;
                            ret++;
                            // cout << "DEBUG: " << ret << endl;
                            VBString b = a.afterFind(subStr, found, caseSens);
                            a = b;
                        }
                        return ret;
                    }

                    // return the number of tokens

                    unsigned tokCount(char tok) const {
                        unsigned ret = 0;
                        unsigned len = getLength();
                        for (unsigned i = 0; i < len; i++) {
                            if (m_str[i] == tok)
                                ret++;
                        }
                        return ret;
                    }

                    void strtokchg(const char tok, const unsigned n, const char *newData) {
                        if (n > tokCount(tok)) {// if n too big
                            // cout << "n too big" << endl; // debug
                            return; // do nothing
                        }
                        unsigned tokPos_initial = strtokpos(tok, n) + 1;
                        unsigned tokPos_final = strtokpos(tok, n + 1) + 1;
                        if (n == tokCount(tok)) // the last string
                            tokPos_final++;
                        br::com::sbVB::VBLib::VBString before = strBefore(tokPos_initial);
                        br::com::sbVB::VBLib::VBString after = strAfter(tokPos_final - 1);
                        *this = before + newData + after;
                    }

                    void myDelete() {
                        if (m_str) {
                            delete [] m_str;
                            m_str = NULL;
                        }
                    }

                    char p_extendedToUpper(char in) {
                        in = toupper(in);
                        // change extended chars 
                        int lenChg = strlen(m_chgHiCaps);
                        for (int k = 0; k < lenChg; k++) {
                            if (in == m_chgLoCaps[k]) { // test for each char of chgLoCaps
                                return m_chgHiCaps[k]; // set correspondent HiCaps in its place
                            }
                        } // for k
                        return in;
                    }

                    char p_extendedToLower(char in) {
                        in = tolower(in);
                        // change extended chars 
                        int lenChg = strlen(m_chgHiCaps);
                        for (int k = 0; k < lenChg; k++) {
                            if (in == m_chgHiCaps[k]) { // test for each char of chgLoCaps
                                return m_chgLoCaps[k]; // set correspondent LoCaps in its place
                            }
                        } // for k
                        return in;
                    }

                    char p_safeToUpper(char in) {
                        in = p_toSafe(in);
                        in = toupper(in);
                        return in;
                    }

                    char p_safeToLower(char in) {
                        in = p_toSafe(in);
                        in = tolower(in);
                        return in;
                    }

                    // change extended chars to safe (non-extended) ones

                    char p_toSafe(char in) const {
                        int lenChg = strlen(m_chgHiCaps);
                        for (int k = 0; k < lenChg; k++) {
                            if (in == m_chgHiCaps[k]) { // test for each char of chgHiCaps
                                return m_chgHiCapsSafe[k]; // set correspondent safe
                            }
                            if (in == m_chgLoCaps[k]) { // test for each char of chgLoCaps
                                return m_chgLoCapsSafe[k]; // set correspondent safe
                            }
                        } // for k
                        return in;
                    }

                    // ignore extended char

                    void toLower() {
                        unsigned len = strlen(m_str);
                        for (unsigned i = 0; i < len; i++)
                            m_str[i] = tolower(m_str[i]);
                    }

                    // ignore extended char

                    void toUpper() {
                        unsigned len = strlen(m_str);
                        for (unsigned i = 0; i < len; i++)
                            m_str[i] = toupper(m_str[i]);
                    }

                    // convert to extended char lo caps

                    void extendedToLower() {
                        unsigned len = strlen(m_str);
                        for (unsigned i = 0; i < len; i++)
                            m_str[i] = p_extendedToLower(m_str[i]);
                    }

                    // convert to extended char hi caps

                    void extendedToUpper() {
                        unsigned len = strlen(m_str);
                        for (unsigned i = 0; i < len; i++)
                            m_str[i] = p_extendedToUpper(m_str[i]);
                    }

                    // convert to standard ascii char lo caps                 

                    void safeToLower() {
                        unsigned len = strlen(m_str);
                        for (unsigned i = 0; i < len; i++)
                            m_str[i] = p_safeToLower(m_str[i]);
                    }

                    // convert to standard ascii char hi caps

                    void safeToUpper() {
                        unsigned len = strlen(m_str);
                        for (unsigned i = 0; i < len; i++) {
                            // cout << "before=" << m_str[i] << endl;
                            m_str[i] = p_safeToUpper(m_str[i]);
                            // cout << "after="<< m_str[i] << endl;
                        }
                    }

                    // convert to standard ascii char hi or lo caps

                    void toSafe() {
                        unsigned len = strlen(m_str);
                        for (unsigned i = 0; i < len; i++) {
                            m_str[i] = p_toSafe(m_str[i]);
                        }
                    }

                    // global function

                    friend VBString operator+
                    (const char* str, const VBString & vbs) {
                        VBString r(str);
                        VBString ret = r + vbs;
                        return ret;
                    }

                    char getChar(unsigned pos) const {
                        if (pos < getLength())
                            return m_str[pos];
                        else
                            return 0; // null char
                    }

                    void putChar(unsigned pos, char ch) {
                        if (pos < getLength())
                            m_str[pos] = ch;
                    }


                    //////////////////////
                    // BSTR

#ifdef WIN32
                    // BSTR removed because some compilers won't compile it
#if 0

                    void VBString::getBSTR(const BSTR & pWord) {
                        unsigned i = 0;
                        while (pWord[i])
                            i++;
                        // after this loop, i has the length of the BSTR
                        unsigned length = i;
                        char *p = new char [length + 1];
                        if (!p) error("Could't alloc memory");
                        for (i = 0; i < length; i++)
                            p[i] = (char) pWord[i];
                        p[length] = 0; // terminate string
                        (*this) = p; // place the string to object
                        delete [] p; // delete p not to leak memory
                    }

                    BSTR VBString::exportBSTR() {
                        CComVariant VarStr(*this);
                        BSTR ret = VarStr.bstrVal;
                        return ret;
                    }
#endif
#endif



                    /////////////////////////////////////////////////////////////
                    // operator=

                    void operator=(const VBString & s) {
                        allocStr(s.m_size);
                        if (s.m_size) strcpy(m_str, s.m_str);
                    }

                    void operator=(const char *s) {
                        if (!s) s = "";
                        unsigned len = strlen(s);
                        allocStr(len);
                        if (len) strcpy(m_str, s);
                    }

                    void operator=(const char ch) {
                        VBString aux;
                        aux += ch;
                        *this = aux;
                    }

                    void operator=(const int i) {
                        VBString aux;
                        aux += i;
                        *this = aux;
                    }

                    void operator=(const unsigned i) {
                        VBString aux;
                        aux += i;
                        *this = aux;
                    }

                    void operator=(const float f) {
                        VBString aux;
                        // aux.setDecs(getDecs()); // use the number of decs of this
                        aux += f;
                        *this = aux;
                    }

                    void operator=(const double d) {
                        VBString aux;
                        // aux.setDecs(getDecs()); // use the number of decs of this
                        aux += d;
                        *this = aux;
                    }

                    void operator=(const long double d) {
                        VBString aux;
                        // aux.setDecs(getDecs()); // use the number of decs of this
                        aux += d;
                        *this = aux;
                    }


                    /////////////////////////////////////////////////////////////
                    // operator+=

                    void operator+=(const char ch) {
                        VBString ret = (*this) + ch;
                        operator=(ret);
                    }

                    void operator+=(const int i) {
                        VBString ret = (*this) + i;
                        operator=(ret);
                    }

                    //                    void operator+=(const long i) {
                    //                        VBString ret = (*this) + i;
                    //                        operator=(ret);
                    //                    }

                    void operator+=(const unsigned i) {
                        VBString ret = (*this) + i;
                        operator=(ret);
                    }

                    void operator+=(const double d) {
                        VBString ret = (*this) + d;
                        operator=(ret);
                    }

                    void operator+=(const long double d) {
                        VBString ret = (*this) + d;
                        operator=(ret);
                    }

                    void operator+=(const float f) {
                        VBString ret = (*this) + f;
                        operator=(ret);
                    }

                    void operator+=(const char* s) {
                        VBString ret = (*this) + s;
                        operator=(ret);
                    }

                    void operator+=(const VBString & s) {
                        VBString ret = (*this) + s;
                        operator=(ret);
                    }

                    /////////////////////////////////////////////////////////////
                    // operator+

                    VBString operator+(const char ch) const {
                        char buffer[2];
                        buffer[0] = ch;
                        buffer[1] = 0; // terminator string
                        VBString ret = (*this) + buffer; // buffer is char*
                        return ret;
                    }

                    VBString operator+(const int i) const {
                        std::ostringstream oss;
                        oss << i;
                        return (*this) +VBString(oss.str().c_str());
                    }

                    VBString operator+(const unsigned i) const {
                        std::ostringstream oss;
                        oss << i;
                        return (*this) +VBString(oss.str().c_str());
                    }

                    VBString operator+(const float f) const {
                        VBString ret = operator+((double) f);
                        return ret;
                    }

                    VBString operator+(const double d) const {
                        std::ostringstream oss;
                        oss << d;
                        return (*this) +VBString(oss.str().c_str());
                    }

                    VBString operator+(const long double d) const {
                        std::ostringstream oss;
                        oss << d;
                        return (*this) +VBString(oss.str().c_str());
                    }

                    VBString operator+(const char* s) const {
                        if (s) {
                            VBString aux(s);
                            return *this +aux;
                        } else
                            return (*this);
                    }

                    VBString operator+(const VBString & s) const {
                        //                        if (s.m_str)
                        //                            return operator+(s.m_str);
                        //                        else
                        //                            return operator+("");
                        //                        std::cout << m_size << std::endl;
                        //                        std::cout << s.m_size << std::endl;
                        char *buff = new char [m_size + s.m_size + 1]; // +1 for terminator char
                        ::strcpy(buff, m_str);
                        ::strcat(buff, s.m_str);
                        VBString ret(buff);
                        delete [] buff;
                        return ret;
                    }

                    VBString afterFind(const char findChar, bool & found,
                            bool caseSens = true) const {
                        char buffer[2];
                        buffer[0] = findChar;
                        buffer[1] = 0; // terminateString
                        return afterFind(buffer, found, caseSens);
                    }

                    VBString afterFind(const char *find, bool & found,
                            bool caseSens = true) const {
                        VBString thisTemp = *this;
                        VBString findTemp = find;
                        if (!caseSens) {
                            thisTemp.extendedToLower();
                            findTemp.extendedToLower();
                        }
                        found = true;
                        VBString b = thisTemp.beforeFind(findTemp);
                        if (b.getLength() == getLength()) {
                            found = false;
                            return (VBString(""));
                        }
                        char *inStr = m_str;
                        unsigned pos = b.getLength() + strlen(find);
                        VBString ret(inStr + pos);

                        /* OLD CODE. Before adding case sensitive option
                                found = true;
                                VBString b = beforeFind(find);
                                if (b.getLength() == getLength()) {
                                        found = false;
                                        return (VBString(""));
                                }
                                char *inStr = m_str;
                                unsigned pos = b.getLength() + strlen(find);
                                VBString ret(inStr+pos);
                         */
                        return ret;
                    }

                    // return the string before fing
                    // VBString r,a("123456789");
                    // r = a.afterFind("56"); // r = "789";
                    // r = a.afterFind("xx"); // r = ""; // string not found

                    VBString afterFind(const char *find) const {
                        bool found;
                        return (afterFind(find, found));
                    }

                    VBString beforeFind(const char findChar) const {
                        char buffer[2];
                        buffer[0] = findChar;
                        buffer[1] = 0; // terminateString
                        return beforeFind(buffer);
                    }

                    // return the string before fing
                    // VBString r,a("123456789");
                    // r = a.beforeFind("56"); // r = "1234";
                    // r = a.beforeFind("xx"); // r = "123456789"; // string not found

                    VBString beforeFind(const char *find) const {
                        char *inStr = new char [getLength() + 1];
                        ::strcpy(inStr, getStr());
                        char *r = strinc(find, inStr);
                        unsigned stopLen;
                        if (r)
                            stopLen = ::strlen(inStr) - ::strlen(r);
                        else
                            stopLen = ::strlen(inStr);
                        inStr[stopLen] = 0; // end string
                        VBString ret(inStr);
                        delete [] inStr;
                        return ret;
                    }

                    // Same as above, but will return in a bool reference if the
                    // subString was in fact found.                  

                    VBString beforeFind(const char *find,
                            bool &found,
                            bool caseSens = true) const {
                        VBString thisTemp = *this;
                        VBString findTemp = find;
                        if (!caseSens) {
                            thisTemp.extendedToLower();
                            findTemp.extendedToLower();
                        }
                        char *inStr = new char [getLength() + 1];
                        ::strcpy(inStr, getStr());
                        char *inStrTemp = new char [getLength() + 1];
                        ::strcpy(inStrTemp, thisTemp.getStr());
                        char *r = strinc(findTemp, inStrTemp);
                        unsigned stopLen;
                        if (r)
                            stopLen = ::strlen(inStr) - ::strlen(r);
                        else
                            stopLen = ::strlen(inStr);
                        inStr[stopLen] = 0; // end string
                        VBString ret(inStr);
                        delete [] inStr;
                        delete [] inStrTemp;

                        found = true;
                        if (ret.getLength() == getLength())
                            found = false;

                        /* OLD CODE

                                char *inStr = new char [getLength()+1];
                                if (!inStr)
                                        error("Alloc error !!!");
                                ::strcpy(inStr,getStr());
                                char *r = strinc(find,inStr);
                                unsigned stopLen;
                                if (r) 
                                        stopLen = ::strlen(inStr) - ::strlen(r);
                                else
                                        stopLen = ::strlen(inStr);
                                inStr[stopLen] = 0;  // end string
                                VBString ret(inStr);
                                delete [] inStr;
	
                                found = true;
                                if (ret.getLength() == getLength())
                                        found = false;
                         */
                        return ret;
                    }

                    VBString beforeFind(const char findChar,
                            bool &found,
                            bool caseSens = true) const {
                        char buffer[2];
                        buffer[0] = findChar;
                        buffer[1] = 0; // terminateString
                        return beforeFind(buffer, found, caseSens);
                    }


                    // find and replace 1 string 

                    void strchg(const char *find, const char *replace) {
                        VBString ret = beforeFind(find);
                        bool found;
                        br::com::sbVB::VBLib::VBString a = afterFind(find, found);
                        if (found)
                            ret += replace + a;
                        (*this) = ret; // place effect to the own object
                    }

                    // find and replace all instances of find string 

                    void strschg(const char *find, const char *replace) {
                        VBString ret, after, before;
                        before = beforeFind(find);
                        after = (*this);
                        ret = before;
                        bool stop = (after == before);
                        if (!stop) ret += replace;
                        while (!stop) {
                            after = after.afterFind(find);
                            before = after.beforeFind(find);
                            stop = (after == before);
                            if (!stop) {
                                ret += before;
                                ret += replace;
                            } else {
                                ret += before;
                            }
                        }
                        (*this) = ret; // place effect to the own object
                    }

                    VBString strtok(char tok, unsigned n) const {
                        bool found;
                        return (strtok(tok, n, found));
                    }

                    // VBString strtok2(const char tok, const unsigned n, bool & found) const;
                    // VBString VBString::strtok(char tok, unsigned long n, bool & found ) const

                    VBString strtok(const char tok, const unsigned n, bool & found) const {
                        unsigned tokPos;
                        return strtok_helper(tok, n, found, tokPos);
                    }

                    // VBString = "abc,def,ghi"
                    // tok =','
                    // n = 2
                    // return = "def"
                    // tokpos is the position of the token in the string

                    VBString strtok_helper(const char tok, const unsigned n, bool & found,
                            unsigned & tokPos) const {
                        found = false;
                        char *str = m_str;
                        if (!str) return br::com::sbVB::VBLib::VBString(""); // token not found 
                        unsigned len = getLength();
                        unsigned tokCount = 0;
                        unsigned i = 0, initial = 0, final = 0;
                        bool initOK = false, finalOK = false;

#if 0
                        // fix loop in case first letter is the tok
                        if ((str[0] == tok) && (n == 0)) {
                            initial = 0; // initial stores the position of nth token
                            initOK = true;
                            tokCount = 1;
                            i = 1;
                        }
#endif

                        // loop to identify the position of nth string
                        for (; (i < len) && !finalOK; i++) {
                            if (str[i] == tok)
                                tokCount++;
                            //		if ((str[0] == tok) || (!initOK && (tokCount == n))) {
                            if (!initOK && (tokCount == n)) {
                                initial = i; // initial stores the position of nth token
                                initOK = true;
                            }
                            if (tokCount == (n + 1)) {
                                final = i; // final stores the position of (n+1)th token
                                finalOK = true;
                            }
                        }

                        if (initOK && finalOK) {
                            found = true;
                            char *buffer = new char [final - initial + 1];
                            unsigned offset;
                            if (n == 0) offset = 0;
                            else offset = 1;
                            for (i = initial + offset; i < final; i++)
                                buffer[i - initial - offset] = str[i];
                            buffer[i - initial - offset] = 0; // end string
                            br::com::sbVB::VBLib::VBString ret(buffer);
                            delete [] buffer;
                            tokPos = initial + 1; // +1 to get on the token
                            if (n == 0) tokPos = 0;
                            return ret;
                        }
                        if (initOK && !finalOK) // n points to the last string
                        {
                            found = true;
                            VBString ret(str + initial + 1);
                            tokPos = initial + 1; // +1 to get on the token
                            if (n == 0) {
                                tokPos = 0;
                                ret = str;
                            }
                            return ret;
                        }

                        if ((str[0] == tok) && (n == 0)) {
                            found = true; // in this case, return is "", but str is found
                            tokPos = 0;
                        }

                        tokPos = getLength();
                        return VBString(""); // token not found or n too big
                    } // end of method strtok_helper


                    // *this "1234567890"
                    // pos = 3
                    // ret = "4567890"

                    VBString strAfter(unsigned pos) const {
                        if (pos > 0) {
                            VBString ret = m_str + pos;
                            if (pos >= getLength())
                                ret = "";
                            return ret;
                        } else
                            return *this;
                    }

                    // *this "1234567890"
                    // pos = 3
                    // ret = "123"

                    VBString strBefore(unsigned pos) const {
                        unsigned len = getLength();
                        char *p = new char [len + 1]; // +1 for the terminator char
                        ::strcpy(p, m_str); // copy string to other buffer
                        if (pos > len) pos = len;
                        p[pos] = 0; // terminate the string
                        br::com::sbVB::VBLib::VBString ret = p;
                        delete [] p;
                        return ret;
                    }

                    // return the position of the token
                    // VBString a = "abc,def,ghi,123,456,7890,yyy";
                    // int n=3;
                    // char tok = ',';
                    // int pos = a.strtokpos(tok,n); // pos=

                    unsigned strtokpos(char tok, unsigned n) const {
                        unsigned tokPos;
                        bool found;
                        strtok_helper(tok, n, found, tokPos);
                        return tokPos - 1;
                    }

                    bool operator<(const VBString & s) const {
                        return (::strcmp(m_str, s.m_str) < 0);
                    }

                    bool operator<=(const VBString & s) const {
                        return (::strcmp(m_str, s.m_str) <= 0);
                    }

                    bool operator>(const VBString & s) const {
                        return (::strcmp(m_str, s.m_str) > 0);
                    }

                    bool operator>=(const VBString & s) const {
                        return (::strcmp(m_str, s.m_str) >= 0);
                    }

                    bool operator==(const VBString & s) const {
                        return (::strcmp(m_str, s.m_str) == 0);
                    }

                    bool operator!=(const VBString & s) const {
                        return (!((*this) == s));
                    }

                    bool operator<(const char * s) const {
                        return operator<(VBString(s));
                    }

                    bool operator<=(const char * s) const {
                        return operator<=(VBString(s));
                    }

                    bool operator>(const char * s) const {
                        return operator>(VBString(s));
                    }

                    bool operator>=(const char * s) const {
                        return operator>=(VBString(s));
                    }

                    bool operator==(const char * s) const {
                        return operator==(VBString(s));
                    }

                    bool operator!=(const char * s) const {
                        return operator!=(VBString(s));
                    }

                    // convert object to web scape sequence

                    void escapeSequenceReverse() {
                        // Convert all + chars to space chars
                        replace("+", " ");

                        bool hasChange;
                        VBString ret, before, after = (*this);
                        do {
                            hasChange = false;
                            for (unsigned x = 0; x < after.getLength(); x++) {
                                if (after.m_str[x] == '%') {
                                    hasChange = true;
                                    before = after.strBefore(x);

                                    // convert the code after the '%' to ascii, and use it as replace string
                                    char strToReplace[2];
                                    strToReplace[0] = p_toHexReverse(after.m_str + x + 1);
                                    strToReplace[1] = 0; // terminate string

                                    ret += before + strToReplace;
                                    after = after.strAfter(x + 3);
                                    break;
                                }
                            }
                            if (!hasChange)
                                ret += after;
                        } while (hasChange);

                        // copy 
                        (*this) = ret;
                    }

                    // convert object to web unscape sequence

                    void escapeSequence() {

                        // Convert % separatelly not to give problem with the general % case
                        replace("%", "%25");

                        const char *charToConvert = "=.,?<>[]{};:'\"`~!@&#$^()+-*/_|\\����������������������������������������";

                        // Convert all %xy hex codes into ASCII chars 
                        bool hasChange;
                        do {
                            hasChange = false;
                            for (unsigned x = 0; x < m_size; x++) {
                                for (unsigned y = 0; y < strlen(charToConvert); y++) {
                                    if (m_str[x] == charToConvert[y]) {
                                        hasChange = true;
                                        char strToSearch[2];
                                        strToSearch[0] = charToConvert[y];
                                        strToSearch[1] = 0; // terminate string

                                        // replace string is %xx<zero>, where xx is charToConvert[y] converted to hex
                                        char strToReplace[4];
                                        strToReplace[0] = '%';
                                        p_toHex(charToConvert[y], strToReplace + 1);
                                        strToReplace[3] = 0; // terminate string
                                        strschg(strToSearch, strToReplace); // convert
                                        break;
                                    } // if
                                } // for y
                            } // for x
                        } while (hasChange);

                        replace(" ", "+"); // convert space char separatelly, since version 2.3 of VBMcgi
                    }

                    // this = str
                    // useful for expat XML processing

                    void setUnterminatedString(const char *str, unsigned length) {
                        myDelete();
                        m_str = new char [length + 1];
                        for (unsigned i = 0; i < length; i++)
                            m_str[i] = str[i];
                        m_str[length] = 0;
                        m_size = length;
                    }

                    void wipeLeadingSpace() {
                        unsigned i = 0;
                        while ((m_str[i] == '\n' || m_str[i] == '\t' || m_str[i] == ' ') && i < m_size)
                            i++;
                        if (i != 0) {
                            // *this = m_str+i; // can't do this
                            br::com::sbVB::VBLib::VBString s = m_str + i;
                            *this = s;
                        }
                    }

                    // get next word of a stream

                    void getNextWord(::std::istream & stream) {
                        std::string s;
                        stream >> s; // read using std string
                        (*this) = s.c_str(); // copy to this

                        // remove symbols if exist at right
                        int len = length(); // length of this
                        const char *symbols = ".,;";
                        int symbol_len = strlen(symbols);
                        if (len > 0) {
                            for (int i = 0; i < symbol_len; i++) {
                                if (m_str[len - 1] == symbols[i]) // if last char of this is one of the symbols
                                    (*this) = (*this).beforeFind(symbols[i]); // remove it
                            }
                        }
                    }

                    static void test() {
                        using namespace std;
                        std::cout << "== VBString::test()" << std::endl;

                        {
                            VBString s = "12345";
                            VBString s2 = s;
                            bool b;
                            b = s.existSubstring(s2);
                            VBAssert(b == true);

                            unsigned u = s.countSubString(s2);
                            VBAssert(u == 1, "u!=1");

                            VBString test = "teste, teste,<A href=\"url\">Link</A>, este, TesTe.";
                            VBString link, link_item;
                            bool found;
                            unsigned count;

                            link = test.afterFind("<a", found);
                            VBAssert(found == false); // como � atualmente

                            link = test.afterFind("<a", found, true);
                            VBAssert(found == false); // segue o default

                            link = test.afterFind("<a", found, false);
                            VBAssert(found == true);
                            VBAssert(link == " href=\"url\">Link</A>, este, TesTe.");

                            link_item = link.beforeFind("</a", found);
                            VBAssert(found == false);
                            VBAssert(link_item == link);

                            link_item = link.beforeFind("</a", found, false);
                            //cout << "DEBUG: Link_item: \"" << link_item << "\"" << endl;
                            VBAssert(found == true);
                            VBAssert(link_item == " href=\"url\">Link");

                            VBAssert(!test.existSubstring("link"));

                            // exist "link" testing in a non case sensitive way
                            VBAssert(test.existSubstring("link", false));

                            count = test.countSubString("teste");
                            VBAssert(count == 2);

                            count = test.countSubString("teste", false);
                            VBAssert(count == 3);

                            VBString t = "abcdef";
                            VBAssert(t.separateLeftString("abc") == "def");

                        }

                        {
                            std::ostringstream oss;
                            int i = 123;
                            oss << i;
                            VBString s(oss.str().c_str());
                            VBAssert(s == "123", "ostringstream");
                        }

                        // file system
                        {
                            const char *fileName = "VBString_test.txt";
                            ofstream outFile(fileName);
                            VBAssert(outFile);
                            if (!outFile)
                                return;

                            const char *lines[] = {
                                "line 1",
                                "line 2",
                                "line 3",
                                "line 4"
                            };

                            int nlines = sizeof (lines) / sizeof (const char *);

                            for (int i = 0; i < nlines; i++) {
                                outFile << lines[i] << endl;
                            }
                            outFile.close();
                            
                            ifstream inFile(fileName);
                            VBAssert(inFile);
                            if (!inFile)
                                return;
                            
                            int i=0;
                            VBString currLine;
                            while (true) {
                                ostringstream oss;
                                inFile >> currLine;
                                if (inFile.eof()) break;
                                oss << currLine;
                                VBString ossStr = oss.str().c_str();
                                VBAssert(ossStr==lines[i++]);
                            }


                        }



                        //                        VBAssert(false, "ttt");
                        //                        VBAssert(VBString("a") == VBString("ab"), "==");
                        //                        VBAssert(VBString("a") == "ab", "==");

                        {
                            VBString s = "hello";
                            VBAssert((s + "abc") == "helloabc", "VBString ==");

                            s = "";
                            VBAssert(s.getLength() == 0, "getLength");

                            VBString a;
                            a = "12345 ";
                            VBString b = a + "33";
                            VBString c = b;

                            VBAssert(c == b);
                            VBAssert(c >= b);
                            VBAssert(!(c < b));
                            VBAssert(c <= b);
                            VBAssert(a != b);
                            VBAssert(b == "12345 33");

                            // common error:
                            // a = "abc" + "def"; // can not add 2 pointers directly
                            // use instead
                            a = "abc";
                            a += "def";
                            // or a = "abc" + VBString("def"); 	
                            VBAssert(a == "abcdef");
                        }


                        {

                            VBString a;
                            a = "123";
                            VBAssert(a == "123", "123");
                            a = "456" + a;
                            VBAssert(a == "456123", "456123");
                            a = a + 78; // int
                            VBAssert(a == "45612378", "45612378");
                            //        a.setDecs(3);
                            //        a = a + 0.12345; // double
                            //        VBAssert(a == "456123780.123");
                            a = "abc";
                            a += 12; // int
                            VBAssert(a == "abc12", "abc12");
                            a = "abc";
                            a += 12.12345; // double
                            // cout << "a=" << a << endl;
                            VBAssert(a == "abc12.1235", "abc12.1235");
                            a = "abc";
                            a += "12"; // const char *
                            VBAssert(a == "abc12", "abc12");

                            // cout << "Enter anything:";
                            // cin >> a;
                            // cout << "a=" << a << endl;

                            std::istringstream iss;
                            iss.str("something");
                            iss >> a;
                            VBAssert(a == "something", "==");
                        }

                        {
                            VBString a, b;
                            a = "123456789";
                            b = a.beforeFind("56"); // b = "1234";
                            VBAssert(b == "1234", "beforeFind");
                            b = a.afterFind("xx"); // b = ""; if string not found
                            VBAssert(b == "", "afterFind");

                            a = "0123456789012345678901234567890123456789";
                            VBString find = "34";
                            VBString replace = "abc";
                            a.replace(find, replace); // (changes a)
                            VBAssert(a == "012abc56789012abc56789012abc56789012abc56789", "replace");

                            //   0   1   2   3   4   5    6   (tok)
                            a = "abc,def,ghi,123,456,7890,yyy";
                            char tok = ',';
                            VBAssert(a.strtok(tok, 0) == "abc", "strtok");
                            VBAssert(a.strtok(tok, 1) == "def", "strtok");
                            VBAssert(a.strtok(tok, 5) == "7890", "strtok");
                            bool found;
                            b = a.strtok(tok, 3, found); // found is a return value
                            VBAssert(found, "strtok found");
                            VBAssert(b == "123");
                        }


                        {
                            int k = 1234;
                            VBString s = "abc";
                            s += k;
                            VBAssert(s == "abc1234", "+= long");
                            // std::cout << s << std::endl;

                        }

                        {
                            std::deque<VBString> ds;
                            ds.push_back("path1");
                            ds.push_back("path2");

                            VBAssert(ds[0] == "path1");
                            VBAssert(ds[1] == "path2");
                        }

                    } // end of test()


                }; // end of VBString
            }
        }
    }
} // end of namespace


#ifndef _VBLIB_H_GLOBAL_NOT_AGAIN_
// static variable initialization
const char *br::com::sbVB::VBLib::VBString::m_chgHiCaps = "ÁÉÍÓÚÀÈÌÒÙÄËÏÖÜÂÊÎÔÛAOÑÇÃÕ";
const char *br::com::sbVB::VBLib::VBString::m_chgLoCaps = "áéíóúàèìòùäëïöüâêîôûaoñçãõ";
const char *br::com::sbVB::VBLib::VBString::m_chgHiCapsSafe = "AEIOUAEIOUAEIOUAEIOUAONCAO";
const char *br::com::sbVB::VBLib::VBString::m_chgLoCapsSafe = "aeiouaeiouaeiouaeiouaoncao";
#endif


