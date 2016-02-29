// VBTableMonth.h
// www.vbmcgi.org


// experimental, not to be used begin
#if 0

#ifndef __VBSessionServer__
#define __VBSessionServer__


#include "VBMcgi/VBMcgi.h"

// all entities in namespace br::com::sbVB::VBMcgi
namespace br {
namespace com {
namespace sbVB {
namespace VBMcgi {


#pragma warning(disable:4786)
#pragma warning(disable:4503)

struct VBLIB_DLL_API VBSessionServerException : public ::br::com::sbVB::VBLib::VBException
{
	VBSessionServerException(const char *m) : VBException(m) {};
};

class VBLIB_DLL_API VBSessionServer
{
	typedef std::pair<br::com::sbVB::VBLib::VBString, br::com::sbVB::VBLib::VBString> SessionDataTypePair;
	typedef std::map<br::com::sbVB::VBLib::VBString, br::com::sbVB::VBLib::VBString> SessionDataType;
	typedef SessionDataType::iterator SessionDataTypeIterator;
	typedef std::map<br::com::sbVB::VBLib::VBString,SessionDataType> AllDataType;
	typedef AllDataType::iterator AllDataTypeIterator;
	typedef std::pair<br::com::sbVB::VBLib::VBString,SessionDataType> AllDataTypePair; 

	AllDataType m_data;
	br::com::sbVB::VBLib::VBString m_sessionID;
	unsigned m_time; 
		
public:

	VBSessionServer(); // default constructor
	~VBSessionServer(); // destructor
	bool existSession(const char * sessionID); // return true if session exists
	bool deleteSesssion(const char * sessionID); // deletes an existing session and all its variables
	// return true if session existed and was deleted, return false if session did not exist
	void addVariable(const char * sessionID, const char * varName, const char * value); 
	br::com::sbVB::VBLib::VBString getVarValue(const char * sessionID, const char * varName);

	// debug methods
	br::com::sbVB::VBLib::VBString listSession(AllDataTypeIterator it);
	br::com::sbVB::VBLib::VBString listSessionContainers(bool hideVar, const char *sID="");
	br::com::sbVB::VBLib::VBString createSession();

};

struct VBLIB_DLL_API VBSessionClientException : public ::br::com::sbVB::VBLib::VBException
{
	VBSessionClientException(const char *m) : VBException(m) {};
};

class VBLIB_DLL_API VBSessionClient
{
public:
	void connect();
};

}}}} // close namespace ::br::com::sbVB::VBMcgi

#endif // #ifndef

///////////////////////////////////////////////////////////
#endif 
// experimental, not to be used end

