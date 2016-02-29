// VBPageCount.h
// www.VBMcgi.org


#ifndef __VBPAGECOUNT__
#define __VBPAGECOUNT__

// all entities in namespace br::com::sbVB::VBMcgi
namespace br {
namespace com {
namespace sbVB {
namespace VBMcgi {

class VBLIB_DLL_API VBPageCount 
{
	char m_token;
	int m_count;
	void putData(std::ostream & out, const char *id, int data);
	void privateConstructor(const char *id, const char*fileName,bool increment);
public:
	VBPageCount(const char *id, const char*fileName="VBPageCount.txt");
	VBPageCount(const char *id, bool increment, const char*fileName="VBPageCount.txt");
	br::com::sbVB::VBLib::VBString getCount();
};

}}}} // close namespace ::br::com::sbVB::VBMcgi

#endif // __VBPAGECOUNT__
