// VBBinaryData.h

// all entities in namespace br::com::sbVB::VBLib
namespace br {
    namespace com {
        namespace sbVB {
            namespace VBLib {

                class VBException_binaryData : public ::br::com::sbVB::VBLib::VBException {
                public:

                    VBException_binaryData(const char *m) : VBException(m) {
                    };
                };

                class VBBinaryData {
                    unsigned char *m_data;
                    unsigned m_size;
                    bool m_loadedOK;

                public:
                    // default constructor
                    VBBinaryData() : m_data(0), m_size(0) {
                    };

                    // copy constructor
                    VBBinaryData(const VBBinaryData & obj) {
                        m_size = obj.m_size;
                        if (m_size > 0) {
                            m_data = new unsigned char [obj.m_size];
                            memcpy(m_data, obj.m_data, m_size);
                        } else
                            m_data = 0;
                    }

                    VBString getStringInHex() const {
                        VBString ret;
                        for (unsigned i = 0; i < getSize(); i++) {
                            ret += ::br::com::sbVB::VBLib::charInt2asciiString(m_data[i]);
                        }
                        return ret;
                    }

                    void setFromStringInHex(VBString in) {
                        unsigned size = in.getLength();
                        if ((size % 2) != 0)
                            throw VBException_binaryData("size not even in VBBinaryData::setFromStringInHex");
                        create(size / 2);
                        VBString byteStr;

                        for (unsigned i = 0; i < size; i++) {
                            if ((i % 2) == 0) { // i is even (0, 2, 4, .... 
                                byteStr = in.strInside(i, i + 1);
                                (*this)(i / 2) = ::br::com::sbVB::VBLib::asciiString2charInt(byteStr);
                            }
                        }
                    }

                    void loadFromFileAsBin(const char *fileName) {
                        ::std::ifstream fileRead(fileName, ::std::ios::binary);
                        if (!fileRead)
                            throw VBException_binaryData("file not open in VBBinaryData::loadFromFile");

                        // get number of bytes of file
                        fileRead.seekg(0, ::std::ios::end);
                        unsigned byteCount = (unsigned) fileRead.tellg();

                        // close and reopen to place the file pointer to the beginning
                        fileRead.close();
                        fileRead.open(fileName, ::std::ios::binary);
                        if (!fileRead)
                            throw VBException_binaryData("file not open in VBBinaryData::loadFromFile");

                        create(byteCount); // alloc data for the VBBinaryData
                        fileRead.read((char*) m_data, byteCount); // read all bytes of file to buffer
                        fileRead.close();
                    }

                    void loadFromFileAsText(const char *fileName) {
                        // this version uses only 1 copy of data in memory

                        ::std::ifstream file(fileName);
                        if (!file)
                            throw VBException_binaryData("could not open file in VBBinaryData::loadFromFileAsText");

                        VBString str;
                        unsigned size = 0;
                        // loop to read entire file 
                        while (true) {
                            file >> str; // read the line
                            if (file.eof()) break;
                            size += str.getLength() / 2; // / 2 because there are 2 chars for each byte
                        }

                        // alloc space in this VBBinaryData
                        create(size);

                        // put file pointer to the beginning again
                        // file.seekg(0, ::std::ios::beg); // that does not work, so I'm using some other way below
                        file.close();
                        ::std::ifstream file2(fileName);
                        if (!file2)
                            throw VBException_binaryData("could not open file2 in VBBinaryData::loadFromFileAsText");

                        unsigned i = 0; // points to the position of byte to be inserted to this VBBinaryData
                        // loop to read entire file again. This time copying data to this VBBinaryData
                        while (true) {
                            file2 >> str; // read the line
                            // ::std::cout << "DEBUG:" << str << ::std::endl;
                            if (file2.eof()) break;
                            for (unsigned k = 0; k < str.getLength() / 2; k++) // / 2 because each byte has 2 lettes
                            {
                                // for all bytes of current line, copy to this VBBinaryData
                                unsigned char currByte;
                                VBString currByteStr = str.strInside(2 * k, 2 * k + 1);
                                currByte = charInt2asciiReverse(currByteStr[0]) * 16; // MSB
                                currByte += charInt2asciiReverse(currByteStr[1]); // LSB
                                (*this)(i) = currByte; // place data to this
                                // ::std::cout << "DEBUG:" << ::std::hex << 
                                //	::br::com::sbVB::VBLib::charInt2asciiString(currByte) << ::std::endl;
                                i++;
                            }
                        }
                    }

                    void saveToFileAsBin(const char *fileName) const {
                        ::std::ofstream fileWrite(fileName, ::std::ios::binary);
                        if (!fileWrite)
                            throw VBException_binaryData("file not open in VBBinaryData::saveToFile");

                        fileWrite.write((char*) m_data, m_size); // write entire file 
                        fileWrite.close();
                    }

                    void saveToFileAsText(const char *fileName, unsigned bytesPerLine=20) const {
                        ::std::ofstream fileWrite(fileName);
                        if (!fileWrite)
                            throw VBException_binaryData("file not open in VBBinaryData::saveToFile");

                        for (unsigned i = 0; i < m_size; i++) {
                            if (i % bytesPerLine == 0 && i != 0)
                                fileWrite << ::std::endl;
                            fileWrite << ::br::com::sbVB::VBLib::charInt2asciiString(m_data[i]);
                        }
                        fileWrite << ::std::endl;
                    }

                    void create(unsigned size) {
                        if (size != m_size) {
                            myDelete();
                            if (size > 0) {
                                m_data = new unsigned char [size];
                                m_size = size;
                            }
                        }
                    }

                    void createAndFill(unsigned size, unsigned char ch) {
                        create(size);
                        for (unsigned i = 0; i < size; i++)
                            m_data[i] = ch;
                    }

                    unsigned char operator[](unsigned i) const {
                        if (i < m_size)
                            return m_data[i];
                        else
                            throw VBException_binaryData("range check error in VBBinaryData::operator[]");

                        // some useless return
                        return 0;
                    }

                    unsigned char & operator()(unsigned i) {
                        if (i >= m_size)
                            throw VBException_binaryData("range check error in VBBinaryData::operator()");

                        return m_data[i];
                    }

                    const unsigned char* getDataPointer() const {
                        return m_data;
                    }

                    void operator=(const VBBinaryData & obj) {
                        myDelete();
                        m_size = obj.m_size;
                        if (m_size > 0) {
                            m_data = new unsigned char [obj.m_size];
                            memcpy(m_data, obj.m_data, m_size);
                        }
                    }

                    // copy string to this VBBinaryData

                    void operator=(const char * str) {
                        this->setData(str, strlen(str));
                    }

                    void setData(const char *data, unsigned size) {
                        setData((const unsigned char *) data, size);
                    }

                    void dump(::std::ostream & out = ::std::cout) const {
                        out << "VBBinaryData dump. Size = " << m_size << ::std::endl;

                        VBString s;
                        for (unsigned i = 0; i < m_size; i++) {
                            int k = (int) m_data[i];
                            // every byte should be displayed with 3 digits
                            if (k < 100)
                                s += "0";
                            if (k < 10)
                                s += "0";

                            s += k; // int converted to string
                            s += ","; // separator of byte to the next
                            if ((i + 1) % 10 == 0) {
                                // print the intermediate lines
                                out << s << ::std::endl;
                                s = "";
                            }
                        }
                        // print the last line
                        // out << s << ::std::endl;
                    }

                    void setDataInHex(const char *data) {
                        unsigned size = strlen(data);
                        if (size % 2)
                            throw VBException_binaryData("data length must be even in VBBinaryData::setDataInHex");

                        unsigned char byte;
                        this->create(size / 2);
                        for (unsigned i = 0; i < size; i++) {
                            if (!(i % 2))
                                byte = charInt2asciiReverse(data[i]) * 16;
                            else {
                                byte += charInt2asciiReverse(data[i]);
                                (*this)(i / 2) = byte;
                            }
                        }
                    }

                    void setData(const void *data, unsigned size) {
                        // VB_SHOW(size);
                        if (m_size != size) {
                            // cout << "DEBUG mydelete" << endl;
                            myDelete();
                            m_size = size;
                        }
                        if (size > 0) {
                            m_data = new unsigned char [size];
                            memcpy(m_data, data, size);
                        }
                    }

                    void myDelete() {
                        if (m_data) {
                            delete [] m_data;
                            m_data = 0;
                            m_size = 0;
                        }
                    }

                    virtual ~VBBinaryData() {
                        myDelete();
                    }

                    unsigned getSize() const {
                        return m_size;
                    }

                    bool operator==(const VBBinaryData & obj) const {
                        if (getSize() != obj.getSize())
                            return false;

                        for (unsigned i = 0; i < m_size; i++) {
                            if (m_data[i] != obj.m_data[i])
                                return false;
                        }
                        return true;
                    }

                    bool operator!=(const VBBinaryData & obj) const {
                        return !operator==(obj);
                    }

                    void subObjectCopyTo(unsigned from, unsigned to,
                            VBBinaryData & subObject) const {
                        if (to < from)
                            throw VBException_binaryData("to < from in VBBinaryData::subObject");

                        unsigned size = to - from;
                        subObject.create(size);
                        for (unsigned i = 0; i < size; i++)
                            subObject(i) = (*this)[i + from];
                    }

                    void subObjectCopyFrom(unsigned fromThis, unsigned fromSource,
                            unsigned nBytes, const br::com::sbVB::VBLib::VBBinaryData & copyFromObject) {
                        for (unsigned i = 0; i < nBytes; i++)
                            (*this)(i + fromThis) = copyFromObject[i + fromSource];
                    }

                    VBBinaryData operator+(const VBBinaryData & obj) const {
                        VBBinaryData ret;
                        ret.create(getSize() + obj.getSize());
                        ret.subObjectCopyFrom(0, 0, getSize(), *this);
                        ret.subObjectCopyFrom(getSize(), 0, obj.getSize(), obj);
                        return ret;
                    }

                    static void test() {
                        using namespace std;
                        cout << "== VBBinaryData::test()" << endl;
                        try {
                            VBBinaryData a;
                            double d[] = {1.1, 2.2, 3.3, 4.4};
                            a.setData((void*) d, sizeof (d));
                            ostringstream oss;
                            a.dump(oss);
                            VBString ossStr = oss.str().c_str();
                            // cout << ossStr << endl;
                            VBAssert(ossStr ==
                                    "VBBinaryData dump. Size = 32\n"
                                    "154,153,153,153,153,153,241,063,154,153,\n"
                                    "153,153,153,153,001,064,102,102,102,102,\n"
                                    "102,102,010,064,154,153,153,153,153,153,\n");
                            
                            

                        } catch (const VBException_binaryData & e) {
                            cout << "VBException_binaryData" << endl;
                        }


                    }


                }; // end of class VBBinaryData

            }
        }
    }
} // close namespace ::br::com::sbVB::VBLib

