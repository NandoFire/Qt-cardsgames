// VBMenuHtml.h
// www.VBMcgi.org

#ifndef __VBMCGI_VBMenuHtml__
#define __VBMCGI_VBMenuHtml__

// all entities in namespace br::com::sbVB::VBMcgi
namespace br {
namespace com {
namespace sbVB {
namespace VBMcgi {

#define JSCRIPT_FILE = "rollover.js"

class VBLIB_DLL_API VBMenuHtml 
{
	br::com::sbVB::VBLib::VBString m_color;
	br::com::sbVB::VBLib::VBString m_size;
 	br::com::sbVB::VBLib::VBString m_javaScriptFileName;
	bool m_bold;
	bool m_braket;
	bool m_horizontal;
	bool m_italic; //***
	bool m_underline; //***
	int m_style; // menu style
public:
	VBMenuHtml();
	void setColor(br::com::sbVB::VBLib::VBString color) { m_color = color; }
	void setJavaScriptFileName(br::com::sbVB::VBLib::VBString fileName) { m_javaScriptFileName = fileName; }
	void setSize(br::com::sbVB::VBLib::VBString size) { m_size = size; }
	void setBold(bool bold=true) { m_bold = bold; }
	void setItalic(bool italic=false) { m_italic = italic; } //***
	void setUnderline(bool underline=false) { m_underline = underline; } //***
	void setHorizontal(bool horiz=false) { m_horizontal = horiz; }
	void setStyle(br::com::sbVB::VBLib::VBString style, char tok); // sets style and paramenters
	void item(br::com::sbVB::VBLib::VBString str, 
		br::com::sbVB::VBLib::VBString link, br::com::sbVB::VBLib::VBString imageName, 
		br::com::sbVB::VBLib::VBString imageOff, br::com::sbVB::VBLib::VBString imageOn);
	void menuFromFile(const char *fileName);
};

}}}} // close namespace ::br::com::sbVB::VBMcgi


#endif // __VBMCGI_VBMenuHtml__

