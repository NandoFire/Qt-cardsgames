// VBTableMonth.h
// www.vbmcgi.org

#ifndef __VBTABLEMONTH__
#define __VBTABLEMONTH__

#include "VBMcgi.h"

// all entities in namespace br::com::sbVB::VBMcgi
namespace br {
namespace com {
namespace sbVB {
namespace VBMcgi {

class VBLIB_DLL_API VBTableMonth 
{
	int m_month;
	int m_year;
	int m_border;
	br::com::sbVB::VBLib::VBString m_weekDay[7]; // 7 days in a week
	br::com::sbVB::VBLib::VBString m_color[7];   // 7 days in a week
	br::com::sbVB::VBLib::VBString m_noDayColor; // color for days that do not exist
	br::com::sbVB::VBLib::VBString m_dayContent[31]; // maximum of 31 days in a month
	br::com::sbVB::VBLib::VBString m_dayColor[31];   // maximum of 31 days in a month

	// attributes for html table
	br::com::sbVB::VBLib::VBString m_valign;
	int m_width, m_height; // size of html cell

	// return the weekday (0==Sunday, 6==Saturday) of a given day
	// for this month
	int getWeekday(int day) 
	{
		br::com::sbVB::VBLib::VBDate a;
		return a.getWeekDay(m_year,m_month,day);
	}

	// return the number of days of given month
	int getMonthDayMax() 
	{
		br::com::sbVB::VBLib::VBDate a;
		return a.daysInAMonth(m_year,m_month);
	}

public:

	// default constructor
	VBTableMonth();

	// get the number of weeks of a month,
	// for this function, a "week" is the number of lines beginning
	// with Sunday and ending in Saturday that are necessary
	// to completely show this month
	// some years where the return is 4
	// 1903, 1914, 1925, 1931, 1942, 1953, 1959, 1970, 1981, 1987, 1998, 
	// 2009, 2015, 2026, 2037, 2043, 2054, 2065, 2071, 2082, 2093, 2099
	// some pairs (year,month[jan==1]) where the return is 6
	// (1995,4), (1995,7), (1996,3), (1996,6), (1997,3), (1997,8), (1997,11), (1998,5),
	// (1998,8), (1999,1), (1999,5), (1999,10), (2000,1), (2000,4), (2000,7), (2001,9),
	// (2002,3), (2002,6), (2003,3), (2003,8), (2003,11)
	int getWeekMax();


	void setWeekDays(
		const char *Sunday,
		const char *Monday,
		const char *Tuesday,
		const char *Wednsday,
		const char *Thursday,
		const char *Friday,
		const char *Saturday);

	void setDate(int year, int month) 
	{
		m_month = month;
		m_year = year;
	}

	void setSundayColor(br::com::sbVB::VBLib::VBString color)		{ m_color[0] = color; }
	void setMondayColor(br::com::sbVB::VBLib::VBString color)		{ m_color[1] = color; }
	void setTuesdayColor(br::com::sbVB::VBLib::VBString color)	{ m_color[2] = color; }
	void setWednsdayColor(br::com::sbVB::VBLib::VBString color)	{ m_color[3] = color; }
	void setThursdayColor(br::com::sbVB::VBLib::VBString color)	{ m_color[4] = color; }
	void setFridayColor(br::com::sbVB::VBLib::VBString color)		{ m_color[5] = color; }
	void setSaturdayColor(br::com::sbVB::VBLib::VBString color)	{ m_color[6] = color; }
	void setNoDayColor(br::com::sbVB::VBLib::VBString color)		{ m_noDayColor = color; }

	void setBorder(int border)		{ m_border = border; }
	void setValign(br::com::sbVB::VBLib::VBString align)	{ m_valign = align; }
	void setWidth(int width)		{ m_width = width; }
	void setHeight(int height)		{ m_height = height; }
	void setDayContent(int day, br::com::sbVB::VBLib::VBString content);
	void setDayColor(int day, br::com::sbVB::VBLib::VBString color);
	void htmlOut(std::ostream & out = std::cout);
};

}}}} // close namespace ::br::com::sbVB::VBMcgi

#endif // __VBTABLEMONTH__
