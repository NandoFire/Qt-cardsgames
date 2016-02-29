// VBCrossDLL.h

#include <deque>
#include <list>

// additional includes for dll and so
#ifdef WIN32
	// code for Windows
	#include <windows.h>
#else
	// code for Unix
	#include <dlfcn.h>
//	#define GetFunctionFromModule dlsym
//	#define CloseModule dlclose
//	typedef (void*) LpHandleType;
#endif


// all entities in namespace br::com::sbVB::VBLib
namespace br {
namespace com {
namespace sbVB {
namespace VBLib {

class VBException_crossDLL : public ::br::com::sbVB::VBLib::VBException
{
public:
	VBException_crossDLL (const char *m) : VBException(m) {};
};

// cross platform DLL loader (DLL in Windows and so in unix)
class VBCrossDLL
{
	bool m_isLoaded;
	bool m_throwExceptionIfNotFound;
	::br::com::sbVB::VBLib::VBString m_dllName;
#ifdef WIN32
	// code for Windows
	HINSTANCE m_dllHandle;
#else
	// code for Unix
	void *m_soHandle;
#endif

public:

// constructor
VBCrossDLL() : m_throwExceptionIfNotFound(true), m_isLoaded(false)
{
}

// destructor
~VBCrossDLL()
{
	// ::std::cout << "DEBUG VBCrossDLL destructor" << ::std::endl;
	if (m_isLoaded)
		unLoad();
}

	// copy constructor 
VBCrossDLL(const VBCrossDLL & obj) 
{
	m_throwExceptionIfNotFound = obj.m_throwExceptionIfNotFound;
	m_isLoaded = obj.m_isLoaded;
	m_dllName = obj.m_dllName;
	if (obj.m_isLoaded)
	{	
		VBCrossDLL & obj_nonConst = const_cast<VBCrossDLL &>(obj); // remove constness
		obj_nonConst.m_isLoaded = false; // "obj" is not loaded any more, so no unload at destructor

#ifdef WIN32
		// code for Windows
		m_dllHandle = obj_nonConst.m_dllHandle; // "this" now points to "obj"
#else
		// code for Unix
		m_soHandle = obj_nonConst.m_soHandle; // "this" now points to "obj"
#endif

	}

/* // this version works, but requires unload and load of dll ############
obj_nonConst.unLoad();
// load(m_dllName); // one shouldn't call that method from a constructor
m_dllHandle = LoadLibrary(m_dllName);
if (!m_dllHandle) 
	throw VBException_crossDLL(VBString("Could not Load DLL ") + m_dllName);
// this version works, but requires unload and load of dll ############ */

/* // this version does not work!!! #####################
// unsigned size = sizeof(HINSTANCE);
// m_dllHandle = new HINSTANCE;
// memcpy(m_dllHandle, obj.m_dllHandle, size);
// this version does not work!!! ##################### */
}

// operator=
void operator=(const VBCrossDLL & obj) 
{
	m_throwExceptionIfNotFound = obj.m_throwExceptionIfNotFound;
	m_isLoaded = obj.m_isLoaded;
	m_dllName = obj.m_dllName;

	if (obj.m_isLoaded)
	{	
		VBCrossDLL & obj_nonConst = const_cast<VBCrossDLL &>(obj); // remove constness
		obj_nonConst.m_isLoaded = false; // "obj" is not loaded any more, so no unload at destructor
#ifdef WIN32
		// code for Windows
		m_dllHandle = obj_nonConst.m_dllHandle; // "this" now points to "obj"
#else
		// code for Unix
		m_soHandle = obj_nonConst.m_soHandle; // "this" now points to "obj"
#endif

	}
	
}


void setThrowExceptionIfNotFound(bool b)
{
	m_throwExceptionIfNotFound = b;
}

bool getThrowExceptionIfNotFound()
{
	return m_throwExceptionIfNotFound;
}



// get dll name
::br::com::sbVB::VBLib::VBString getName() const
{
	return m_dllName;
}


	// load dll, throw exception if can not load
	void load(const char *dllName) throw (VBException_crossDLL)
{
	m_dllName = dllName;
#ifdef WIN32
	// code for Windows
	#if _MSC_VER == 1200 // VC6
		m_dllHandle = LoadLibrary(dllName);
	#endif

	#if _MSC_VER > 1200 // VC2003, vc2005 or earlier
		/*m_dllHandle = LoadLibrary((LPCWSTR)dllName);*/
		m_dllHandle = LoadLibraryA((LPCSTR)dllName);
	#endif

	if (!m_dllHandle) 
		throw VBException_crossDLL(VBString("Could not Load DLL ") + m_dllName);
#else
	// code for Unix
	m_soHandle = dlopen(dllName,RTLD_NOW);	
	if (!m_soHandle) 
	{
		VBString explanation = "Could not Load so " + m_dllName;
		// cout << "DEBUG" << explanation << endl;
		// cout << "DEBUG" << dlerror() << endl;
		if (dlerror())
		{
			explanation += ". Explanation";
			explanation += dlerror();
		}
		// cout << "DEBUG" << explanation << endl;
		throw VBException_crossDLL(explanation);
	}
#endif
	m_isLoaded = true;
}


	// check if dll or so load is ok, but does not load
	bool loadOK(const char *dllName)
{
	m_dllName = dllName;
	bool loaded;
#ifdef WIN32
	// code for Windows
	#if _MSC_VER == 1200 // VC6
		m_dllHandle = LoadLibrary(dllName);
	#endif

	#if _MSC_VER > 1200 // VC2003, vc2005 or earlier
		/*m_dllHandle = LoadLibrary((LPCWSTR)dllName);*/
		m_dllHandle = LoadLibraryA((LPCSTR)dllName);
	#endif

	loaded = m_dllHandle != 0;
	if (loaded)
		unLoad();
	return (loaded);
#else
	// code for Unix
	// m_soHandle = dlopen(dllName,RTLD_LAZY | RTLD_LOCAL);	
	m_soHandle = dlopen(dllName,RTLD_NOW);	
	loaded = m_soHandle != 0;
	if (loaded)
		unLoad();
	return (loaded);
#endif
}


// unload
void unLoad()
throw (VBException_crossDLL)
{
	if (m_isLoaded)
	{
		bool dllUnloadSuccess;
	#ifdef WIN32
		// code for Windows
		dllUnloadSuccess = (FreeLibrary(m_dllHandle) != 0);
		if (!dllUnloadSuccess) 
			throw VBException_crossDLL(VBString("Could not unload DLL ") + m_dllName);
	#else
		// code for Unix
		dllUnloadSuccess = (dlclose(m_soHandle) == 0);
		if (!dllUnloadSuccess) 
			throw VBException_crossDLL(VBString("Could not unload so ") + m_dllName);
	#endif
		m_isLoaded = false;
	}
}

	// get address of function or object from dll or so
	void *getAddress(const char *exportedName) throw (VBException_crossDLL)
{
	if (!m_isLoaded)
		throw VBException_crossDLL("DLL or so not loaded.");
	void *ret;
#ifdef WIN32
	// code for Windows
	ret = GetProcAddress(m_dllHandle,exportedName);
#else
	// code for Unix
	ret = dlsym(m_soHandle, exportedName);
#endif
	if (m_throwExceptionIfNotFound && ret == 0)
		throw VBException_crossDLL("Could not get address from dynamic library");
	return ret;
	
}


// return true if dll or so has exportedName
bool hasExportedName(const char *exportedName)
throw (VBException_crossDLL)
{
	if (!m_isLoaded)
		throw VBException_crossDLL("DLL or so not loaded.");
#ifdef WIN32
	// code for Windows
	return (GetProcAddress(m_dllHandle,exportedName) != 0);
#else
	// code for Unix
	return (dlsym(m_soHandle, exportedName) != 0);
#endif
}

// return true if dll or so has all names in strArray as exported
bool hasAllNeededExportedNames(const char **strArray, unsigned size)
{
	for (unsigned i = 0 ; i < size ; i++)
	{
		if (!hasExportedName(strArray[i]))
			return false;
	}
	return true;

}

#if 0
static void getDllsWithAllExportedNames(const char **exportedNamesDllMustHave,unsigned size,
	::std::list<VBString> & dllNames, const char *directory, const char *extension)
throw (VBException_crossDLL)
{
	VBCrossDLL currentDll;
	br::com::sbVB::VBLib::VBFileDirectory fileDir;
	VBString currElement;
	for (currElement = fileDir.getFirst(directory) ; 
		!fileDir.eolist() ; currElement = fileDir.getNext()) 
	{
		if (VBString(extension)==currElement.getFileExtension())
		{
			::std::cout << "DEBUG: " << currElement << ::std::endl;

			if (currentDll.loadOK(currElement))
			{
				currentDll.load(currElement);
				if (currentDll.hasAllNeededExportedNames(exportedNamesDllMustHave,size))
				{
					::std::cout << "DEBUG added: " << currElement << ::std::endl;
					dllNames.push_back(currElement);
				}
				currentDll.unLoad();
			}
		}
	}
}
#endif

};


////////////////////////////////////////////////////////////////////////

class VBCrossDLLContainer
{
	::std::deque<br::com::sbVB::VBLib::VBCrossDLL> m_dllContainer;
public:

void loadDllsWithAllExportedNames
(const char **exportedNamesDllMustHave,unsigned size,
	const char *directory, const char *extension)
throw (VBException_crossDLL)
{
	// before loading more dll's, unload all of them
	unLoad();

	VBCrossDLL currentDll;
	br::com::sbVB::VBLib::VBFileDirectory fileDir;
	VBString currElement;
	for (currElement = fileDir.getFirst(directory) ; 
		!fileDir.eolist() ; currElement = fileDir.getNext()) 
	{
		if (VBString(extension)==currElement.getFileExtension())
		{
//			::std::cout << "DEBUG: " << currElement << ::std::endl;

			if (currentDll.loadOK(currElement))
			{
				currentDll.load(currElement);
				if (currentDll.hasAllNeededExportedNames(exportedNamesDllMustHave,size))
				{
//					::std::cout << "DEBUG added: " << currElement << ::std::endl;
					m_dllContainer.push_back(currentDll);
				}
			}
		}
	}
}

unsigned getNumberOfDlls()
{
	return m_dllContainer.size();
}

VBCrossDLL & operator[](unsigned i)
throw (VBException_crossDLL)
{
	return m_dllContainer[i];
}


void unLoad() throw (VBException_crossDLL)
{
	std::deque<VBCrossDLL>::iterator it;
	for (it = m_dllContainer.begin() ; it != m_dllContainer.end() ; it++)
	{
		it->unLoad();
	}

	// make the container empty
	m_dllContainer.clear();
}

~VBCrossDLLContainer()
{
	unLoad();
}

};


}}}} // close namespace ::br::com::sbVB::VBLib



