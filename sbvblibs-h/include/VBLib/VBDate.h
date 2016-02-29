// VBDate.h
// all entities in namespace br::com::sbVB::VBLib
namespace br {
    namespace com {
        namespace sbVB {
            namespace VBLib {

                /////////////////////////////////////////////////////////////////////
                //
                // class VBDate
                //
                /////////////////////////////////////////////////////////////////////

                // _VBWeekdays and _VBMonths are not used. They are declared not to have
                // compiler error in some compilers

                typedef enum VBWeekdays {
                    VBsun, VBmon, VBtue, VBwed, VBthu, VBfri, VBsat, VBinvalid
                } _VBWeekdays;


                // one should not use "oct" as short for october, and
                // "dec" as short for december, because "oct" and "dec" identifiers
                // are already used by the standard library

                typedef enum VBMonths {
                    VBjan, VBfeb, VBmar, VBapr, VBmay, VBjun,
                    VBjul, VBaug, VBsep, VBoct, VBnov, VBdec
                } _VBMonths;


                //                                      jan fev mar apr may jun jul ago sep oct nov dec   
                static const int VBDaysInMonths[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

                static const char *VBMonthNames[] = {
                    "Jan", "Feb", "Mar", "Apr", "May", "Jun",
                    "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
                };

                class VBDate {
                    int m_baseYear;
                    VBMonths m_baseMonth;
                    int m_baseDay;
                    VBWeekdays m_baseWeekDay;
                public:

                    //	// set base date if given date is valid. Do nothing otherwise
                    //	// ATTENTION: does not change m_baseWeekDay !
                    //	bool p_setDate(int year, int month, int day);
                    //
                    //	// return input with 2 digits
                    //	::VBString twoDigits(int i) const;
                    //
                    //	// place in delta the number of days that separates the given day
                    //	// from base day.
                    //	// if date is not valid, do nothing and return false
                    //	bool deltaDays(int year, int month, int day, long & deltaDays) const;
                    //
                    //	// return true given date is valid
                    //	// return false otherwise
                    //	// does not depend on base date
                    //	bool validDate(int year, int month, int day) const;
                    //
                    //	// return true if the given day is future compared with base day
                    //	// return false otherwise
                    //	// if given day and base day are the same, return false
                    //	// does not depend on base date
                    //	bool isFuture(int year, int month, int day) const;
                    //
                    //	// return the number of days from a given date to end of month
                    //	// does not depend on base date
                    //	// example: given date: November 10, 2001; return value will be 20
                    //	int remainingDaysOfGivenMonth(int year, int month, int day) const;
                    //
                    //	// return the number of days from a given date to given date's current year,
                    //	// not counting the current month, that is, from the next month on
                    //	// does not depend on base date
                    //	// Examples: year 2001, month 12, return 0;
                    //	// year 2001, month 11, return 31;
                    //	int remainingDaysOfGivenYearFromNextMonthOn(int year, int month) const;
                    //
                    //	// return the number of days from a given date to this date's current year's final day
                    //	// example: given date: November 15, 2001; return value will be 15+31 = 46
                    //	int remainingDaysofGivenYear(int year, int month, int day) const;
                    //
                    //	// return the number of days 
                    //	// example: base date: April 15, 2001; given year 2005.
                    //	// this function will return the sum of number of days of year 2002, 2003, 2004,
                    //	// that is, 365+365+366, that is, 1096
                    //	long numberOfDaysOfFullYearsFromNextYearToYearBeforeGivenYear(int year) const;
                    //
                    //	// example: base date: April 21, 2001; given date is December 27, 2001
                    //	// return is 361
                    //	int numberOfDaysOfGivenYearUntilGivenDate(int year, int month, int day) const;
                    //
                    //public:
                    //
                    //	VBDate(); // default constructor
                    //
                    //	// get system date and set it to this
                    //	void setSystemDate();
                    //
                    //	// return the weekday of a given date. sun=0, .. sat = 6
                    //	// if date is invalid, the return value is -1
                    //	int getWeekDay(const int year,const int month,const int day) const;
                    //
                    //	//                                         jan fev mar apr may jun jul aug sep oct nov dec   
                    //	static const int VBDaysInMonths[12]; // = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
                    //
                    //	// return true if hear is leap 
                    //	// does not depend on base date
                    //	bool leapYear (int year) const;
                    //
                    //	// return the number of days of a given year, with attention to 
                    //	// leap year. The return value is 365 or 366.
                    //	// does not depend on base date
                    //	int daysInAYear(int year) const;
                    //
                    //	// return the number of days of a given month, 
                    //	// with attention to leap year. 
                    //	// if date is invalid return -1
                    //	// does not depend on base date
                    //	int daysInAMonth(int year, int month) const;
                    //
                    //	// set date if given date is valid do nothing otherwise
                    //	bool setDate(int year, int month, int day);
                    //	bool setDate(VBDateTime dateTime);
                    //	bool setDateYYYYMMDD(::VBString date);
                    //
                    //	// return the delta days between this and cal
                    //	long deltaDays(const VBDate & cal) const;
                    //
                    //	// Return a VBDate whose date is this VBDate added (or subtracted) by delta days.
                    //	VBDate dateAfterDeltaDays(const long deltaDays) const;
                    //
                    //	// get weekDay of this
                    //	int getWeekDay() const;
                    //
                    //	// return a string with base date in given format
                    //	::VBString getDate(int format=1) const;
                    //
                    //	// Set this date to the day after.
                    //	void tomorrow();
                    //
                    //	// Set this date to the day before.
                    //	void yesterday();


                    // set base date if given date is valid. Do nothing otherwise
                    // ATTENTION: does not change m_baseWeekDay !

                    bool p_setDate(int year, int month, int day) {
                        bool OK = validDate(year, month, day);
                        if (!OK) return false;
                        m_baseYear = year;
                        m_baseMonth = (VBMonths) month;
                        m_baseDay = day;
                        return true;
                    }

                    // default constructor

                    VBDate() {
                        m_baseYear = 2001;
                        m_baseMonth = VBapr;
                        m_baseDay = 21;
                        m_baseWeekDay = VBsat;
                    }


#if 0 // commented out begin

                    struct tm {
                        int tm_sec; // seconds after the minute - [0,59] 
                        int tm_min; // minutes after the hour - [0,59] 
                        int tm_hour; // hours since midnight - [0,23] 
                        int tm_mday; // day of the month - [1,31] 
                        int tm_mon; // months since January - [0,11] 
                        int tm_year; // years since 1900 
                        int tm_wday; // days since Sunday - [0,6] 
                        int tm_yday; // days since January 1 - [0,365] 
                        int tm_isdst; // daylight savings time flag 
                    };
                    time_t ltime;
                    tm *t;

                    time(&ltime); // get time and date
                    t = localtime(&ltime); // convert to struct tm

                    // display
                    cout << "Now is:" << endl;
                    cout << "Time: " << t->tm_hour << ":" << t->tm_min
                    << ":" << t->tm_sec << endl;
                    cout << "Year: " << t->tm_year + 1900 << endl;
                    cout << "Month: " << months[t->tm_mon] << endl;
                    cout << "Day: " << t->tm_mday << endl;
                    cout << "Week day: " << weekDay[t->tm_wday] << endl;

#endif // commented out end

                    void setSystemDate() {

                        time_t ltime;
                        tm *t;
                        time(&ltime); // get time and date
                        t = localtime(&ltime); // convert to struct tm

                        setDate(t->tm_year + 1900, t->tm_mon, t->tm_mday);
                    }

                    bool leapYear(int year) const {
                        int k = year % 4; // every 4 years, force leap year true
                        bool ret = (k == 0);
                        k = year % 100; // over previous, every 100 years, force leap year false
                        ret = ret && !(k == 0);
                        k = year % 400; // over previous, every 400 years, force leap year true
                        ret = ret || (k == 0);
                        return ret;
                    }

                    int daysInAYear(int year) const {
                        int ret = 365;
                        if (leapYear(year))
                            ret++;
                        return ret;
                    }

                    int daysInAMonth(int year, int month) const {
                        // if (!validDate(year,month,1)) return -1;
                        // can't test valid date, because validDate calls daysInAMonth
                        int ret;
                        ret = VBDaysInMonths[month];
                        if (leapYear(year) && (month == VBfeb))
                            ret++;
                        return ret;
                    }

                    bool validDate(int year, int month, int day) const {
                        if (month < VBjan || month > VBdec) return false;
                        if (day <= 0 || day > daysInAMonth(year, month)) return false;
                        return true;
                    }

                    bool isFuture(int year, int month, int day) const {
                        if (year > m_baseYear) return true;
                        if (year < m_baseYear) return false;
                        if (month > m_baseMonth) return true;
                        if (month < m_baseMonth) return false;
                        if (day > m_baseDay) return true;
                        return false;
                    }

                    int remainingDaysOfGivenMonth(int year, int month, int day) const {
                        if (!validDate(year, month, day)) return -1;
                        return daysInAMonth(year, month) - day;
                    }

                    int remainingDaysOfGivenYearFromNextMonthOn(int year, int month) const {
                        if (!validDate(year, month, 1)) return -1;
                        int ret = 0;
                        for (int m = month + 1; m < 12; m++)
                            ret += daysInAMonth(year, m);
                        return ret;
                    }

                    int remainingDaysofGivenYear(int year, int month, int day) const {
                        int ret;
                        ret = remainingDaysOfGivenMonth(year, month, day);
                        ret += remainingDaysOfGivenYearFromNextMonthOn(year, month);
                        return ret;
                    }

                    long numberOfDaysOfFullYearsFromNextYearToYearBeforeGivenYear(int year) const {
                        long ret = 0;
                        for (int y = m_baseYear + 1; y < year; y++)
                            ret += daysInAYear(y);
                        return ret;
                    }

                    int numberOfDaysOfGivenYearUntilGivenDate(int year, int month, int day) const {
                        if (!validDate(year, month, day)) return -1;
                        int ret = 0;
                        for (int m = 0; m < month; m++)
                            ret += daysInAMonth(year, m);
                        // after this loop, all days until previous month are already added
                        ret += day;
                        return ret;
                    }

                    bool setDate(int year, int month, int day) {
                        bool OK = validDate(year, month, day);
                        if (!OK) return false;
                        m_baseWeekDay = (VBWeekdays) getWeekDay(year, month, day);
                        p_setDate(year, month, day);
                        return true;
                    }

                    //                    bool setDate(VBDateTime dateTime) {
                    //                        return setDate(dateTime.m_tm.tm_year + 1900, dateTime.m_tm.tm_mon, dateTime.m_tm.tm_mday);
                    //                    }

                    bool setDateYYYYMMDD(VBString date) {
                        int year, month, day;
                        year = atoi(date.strInside(0, 3));
                        month = atoi(date.strInside(4, 5));
                        day = atoi(date.strInside(6, 7));
                        return setDate(year, month - 1, day);
                    }

                    bool deltaDays(int year, int month, int day, long & delta) const {
                        bool OK = validDate(year, month, day);
                        if (!OK) return false;

                        delta = 0;
                        if (year == m_baseYear && month == m_baseMonth && day == m_baseDay) {
                            // given day is the same as base day
                            return true;
                        }

                        if (isFuture(year, month, day)) {
                            // cout << "DEBUG given date is future compared to base date" << endl;
                            if (year > m_baseYear) {
                                // cout << "DEBUG given year is not the same as base year" << endl;
                                delta += remainingDaysofGivenYear(m_baseYear, m_baseMonth, m_baseDay);
                                delta += numberOfDaysOfFullYearsFromNextYearToYearBeforeGivenYear(year);
                                delta += numberOfDaysOfGivenYearUntilGivenDate(year, month, day);
                            } else {
                                // cout << "DEBUG given year is the same as base year << endl;
                                if (month > m_baseMonth) {
                                    // cout << "DEBUG given month is not the same as base month" << endl;
                                    delta += remainingDaysOfGivenMonth(m_baseYear, m_baseMonth, m_baseDay);
                                    // full months from next month, before given month
                                    for (int m = m_baseMonth + 1; m < month; m++)
                                        delta += daysInAMonth(year, m);
                                    delta += day; // days in the given month

                                } else {
                                    // cout << "DEBUG given month is the same as base month" << endl;
                                    delta += day - m_baseDay;
                                }
                            }
                        } else {
                            // to solve the problem for the past, one can only invert the problem
                            // so that the problem becomes future (already solved)
                            VBDate aux;
                            aux.p_setDate(year, month, day); // here, setDate can not be used.
                            // if used, an infinite re-enntry loop is generated.
                            bool ret = aux.deltaDays(m_baseYear, m_baseMonth, m_baseDay, delta);
                            delta *= -1; // invert the delta to fix the inverted problem
                            return ret;
                        }
                        return true;
                    }

                    long deltaDays(const VBDate & cal) const {
                        long ret;
                        deltaDays(cal.m_baseYear, cal.m_baseMonth, cal.m_baseDay, ret);
                        return ret;
                    }

                    int getWeekDay(const int year, const int month, const int day) const {
                        bool OK = validDate(year, month, day);
                        if (!OK) return VBinvalid;

                        long delta;
                        deltaDays(year, month, day, delta);
                        // cout << "DEBUG delta=" << delta << endl;

                        // the code below is valid for both positive and negative delta
                        int k = delta % 7; // k is positive or negative
                        k += m_baseWeekDay + 7; // plus 7 to guarantee k > 0
                        return (k % 7); // return 0 ~ 6
                    }

                    int getWeekDay() const {
                        return getWeekDay(m_baseYear, m_baseMonth, m_baseDay);
                    }

                    VBDate dateAfterDeltaDays(const long d) const {
                        long deltaDays = d;
                        VBDate ret;
                        ret.setDate(m_baseYear, m_baseMonth, m_baseDay);
                        if (deltaDays > 0) {
                            // go to future
                            while (deltaDays != 0) {
                                ret.tomorrow();
                                deltaDays--;
                            }
                        } else {
                            // go to past
                            while (deltaDays != 0) {
                                ret.yesterday();
                                deltaDays++;
                            }
                        }
                        return ret;
                    }

                    void tomorrow() {
                        int daysThisMonth = daysInAMonth(m_baseYear, m_baseMonth);
                        if (m_baseDay < daysThisMonth) {
                            setDate(m_baseYear, m_baseMonth, m_baseDay + 1);
                            return;
                        }
                        if (m_baseMonth < VBdec) {
                            // it it the last day of month, so tomorrow is the first day of next month
                            setDate(m_baseYear, m_baseMonth + 1, 1);
                            return;
                        }
                        // it is the last day of year, so tomorrow is the first day of next year
                        setDate(m_baseYear + 1, VBjan, 1);
                    }

                    void yesterday() {
                        if (m_baseDay > 1) {
                            setDate(m_baseYear, m_baseMonth, m_baseDay - 1);
                            return;
                        }

                        if (m_baseMonth != VBjan) {
                            // it is the first day of a month not January, so yesterday is the last day of previous month
                            int daysLastMonth = daysInAMonth(m_baseYear, m_baseMonth - 1);
                            setDate(m_baseYear, m_baseMonth - 1, daysLastMonth);
                            return;
                        }

                        // it is the first day of year, so yesterday is the last day of previous year
                        setDate(m_baseYear - 1, VBdec, 31);
                    }

                    VBString getDate(int format = 1, int language = 0) const {
                        const char *monthName[][12] = {
                            { // 0 - english	
                                "January", "February", "March", "April", "May", "June",
                                "July", "August", "September", "October", "November", "December"
                            },
                            { // 1 - portuguese
                                "Janeiro", "Fevereiro", "Março", "Abril", "Maio", "Junho",
                                "Julho", "Agosto", "Setembro", "Outubro", "Novembro", "Dezembro"
                            }
                        };

                        VBString ret;
                        switch (format) {
                            case 1: // Example: "November 24th, 2001"
                                ret = monthName[language][this->m_baseMonth];
                                ret += " ";
                                ret += this->m_baseDay;
                                switch (this->m_baseDay) {
                                    case 1:
                                    case 21:
                                    case 31:
                                        ret += "st";
                                        break;
                                    case 2:
                                    case 22:
                                        ret += "nd";
                                        break;
                                    case 3:
                                    case 23:
                                        ret += "rd";
                                        break;
                                    default:
                                        ret += "th";
                                }
                                ret += ", ";
                                ret += this->m_baseYear;
                                break;
                            case 2: // Example: yyyy-mm-dd, that is, "2001-11-24"
                                ret = this->m_baseYear;
                                ret += "-";
                                ret += twoDigits(this->m_baseMonth + 1);
                                ret += "-";
                                ret += twoDigits(this->m_baseDay);
                                break;
                            case 3: // Example: "24 de Novembro de 2001"
                                ret = this->m_baseDay;
                                ret += " de ";
                                ret += monthName[1][this->m_baseMonth];
                                ret += " de ";
                                ret += this->m_baseYear;
                                break;
                            case 4: // Example: yyyy-mm-dd, that is, "20011124"
                                ret = this->m_baseYear;
                                ret += twoDigits(this->m_baseMonth + 1);
                                ret += twoDigits(this->m_baseDay);
                                break;
                            default:
                                ret = "";
                        }

                        return ret;

                    }

                    VBString twoDigits(int i) const {
                        VBString ret;
                        if (i < 10)
                            ret = "0";
                        ret += i;
                        return ret;
                    }

                public:

                    static void test() {
                        using namespace br::com::sbVB::VBLib;

                        std::cout << "== VBDate::test()" << std::endl;

                        VBDate myDate;
                        // cout << "days on feb 2006=" << myDate.daysInAMonth(2006, 1) << endl;
                        VBAssert(myDate.daysInAMonth(2006, 1) == 28);

                        myDate.setDateYYYYMMDD("20120610");
                        // cout << "myDate=" << myDate.getDate() << endl;
                        // cout << "myDate wd=" << myDate.getWeekDay() << endl;
                        VBAssert(myDate.getDate() == "June 10th, 2012");
                        VBAssert(myDate.getWeekDay() == VBsun);
                        VBDate newDate = myDate.dateAfterDeltaDays(100);
                        VBAssert(newDate.getDate() == "September 18th, 2012");
                        VBAssert(newDate.getWeekDay() == VBtue);
                        VBAssert(myDate.deltaDays(newDate) == 100);
                        newDate = newDate.dateAfterDeltaDays(100);
                        VBAssert(newDate.getDate() == "December 27th, 2012");
                        VBAssert(newDate.getWeekDay() == VBthu);

                        // VBsun, VBmon, VBtue, VBwed, VBthu, VBfri, VBsat, VBinvalid

                    }



                }; // end of VBDate




                ///////////////////////////////////////////////////////////////////////
                ////
                //// class VBDateTime
                ////
                ///////////////////////////////////////////////////////////////////////
                //
                ///**********************************************************
                //struct tm 
                //{
                //	int tm_sec;     // seconds after the minute - [0,59] 
                //	int tm_min;     // minutes after the hour - [0,59] 
                //	int tm_hour;    // hours since midnight - [0,23] 
                //	int tm_mday;    // day of the month - [1,31] 
                //	int tm_mon;     // months since January - [0,11] 
                //	int tm_year;    // years since 1900 
                //	int tm_wday;    // days since Sunday - [0,6] 
                //	int tm_yday;    // days since January 1 - [0,365] 
                //	int tm_isdst;   // daylight savings time flag 
                //};
                //**********************************************************/
                //

                class VBDateTime {
                    tm m_tm; // standard lib's struct tm to store date and time
                    unsigned m_miliseconds;

                public:

                    operator struct tm() const {
                        return m_tm;
                    };

                    // default constructor

                    VBDateTime() {
                    }

                    VBString getTimeStr(unsigned format = 0) const {
                        VBString ret;
                        ret += " ";
                        ret += twoDigits(m_tm.tm_hour);
                        ret += ":";
                        ret += twoDigits(m_tm.tm_min);
                        if (format > 1) {
                            ret += ":";
                            ret += twoDigits(m_tm.tm_sec);
                            if (format > 2) {
                                ret += ",";
                                ret += m_miliseconds;
                            }
                        }
                        return ret;
                    }

                    // Example: 31-Mar-2002 23:59:59 GMT

                    VBString getDateStr(int dateFormat = 0) const {
                        VBString ret;
                        VBDate date = *this; // get VBDate object from this
                        ret = date.getDate(dateFormat);
                        ret += VBString(" ") + getTimeStr();
                        //	ret += " GMT";
                        return ret;
                    }

                    VBString twoDigits(int i) const {
                        VBString ret;
                        if (i < 10)
                            ret = "0";
                        ret += i;
                        return ret;
                    }

                    // add or subtract time to this VBDate

                    void addYear(int year) {
                        m_tm.tm_year += year;

                        VBDate cal_from;
                        if (!cal_from.setDate(m_tm.tm_year + 1900 + year, m_tm.tm_mon, m_tm.tm_mday)) {
                            // invalid date. This can only be caused by leap year
                            m_tm.tm_mon = 3; // march
                            m_tm.tm_mday = 1;
                        }
                    }

                    void setDate(int year, unsigned month, unsigned day) {
                        m_tm.tm_year = year - 1900; // input year is normal year. Stored year is tm style (-1900)
                        m_tm.tm_mon = month; // months since January - [0,11] 
                        m_tm.tm_mday = day; // day of the month - [1,31] 



                        // 	getWeekDay
                        //	int tm_wday;    // days since Sunday - [0,6] 
                        //	int tm_yday;    // days since January 1 - [0,365] 

                    }

                    void setTime(unsigned hour,
                            unsigned minute, unsigned second, unsigned miliseconds) {
                        m_tm.tm_hour = hour; // hours since midnight - [0,23] 
                        m_tm.tm_min = minute; // minutes after the hour - [0,59] 
                        m_tm.tm_sec = second; // seconds after the minute - [0,59] 
                        m_miliseconds = miliseconds;
                    }

                    double getDifSeconds(const VBDateTime & dt) const {
                        double ret = 0;
                        double aux = (double) (m_miliseconds) / 1000.0;
                        ret += aux;
                        aux = (double) (dt.m_miliseconds) / 1000.0;
                        ret -= aux;
                        ret += m_tm.tm_sec - dt.m_tm.tm_sec;
                        ret += m_tm.tm_min * 60 - dt.m_tm.tm_min * 60;
                        ret += m_tm.tm_hour * 60 * 60 - dt.m_tm.tm_hour * 60 * 60;

                        // year, month, day not considered yet

                        return ret;
                    }

                    void addMonth(int month) {
#if 0
                        time_t secondsToAdd = 30 * 24 * 60 * 60; // seconds of 1 month
                        secondsToAdd *= month;
                        time_t now = mktime(&m_tm);
                        time_t newDateTime = now + secondsToAdd;
                        setThisTM(newDateTime);
#endif

                        m_tm.tm_mon += month;

                        VBDate cal_from;
                        if (!cal_from.setDate(m_tm.tm_year + 1900, m_tm.tm_mon + month, m_tm.tm_mday)) {
                            // invalid date. This can only be caused by leap year
                            m_tm.tm_mon = 3; // march
                            m_tm.tm_mday = 1;
                        }
                    }

                    void addDay(int day) {
                        addHour(24*day);
//                        time_t secondsToAdd = 24 * 60 * 60; // seconds of 1 day
//                        secondsToAdd *= day;
//                        time_t now = mktime(&m_tm);
//                        time_t newDateTime = now + secondsToAdd;
//                        setThisTM(newDateTime);
                    }

                    void addHour(int hour) {
                        addMinute(60*hour);
//                        time_t secondsToAdd = 60 * 60; // seconds of 1 hour
//                        secondsToAdd *= hour;
//                        time_t now = mktime(&m_tm);
//                        time_t newDateTime = now + secondsToAdd;
//                        setThisTM(newDateTime);
                    }

                    void addMinute(int minute) {
                        addSecond(60*minute);
//                        time_t secondsToAdd = 60; // seconds of 1 minute
//                        secondsToAdd *= minute;
//                        time_t now = mktime(&m_tm);
//                        time_t newDateTime = now + secondsToAdd;
//                        setThisTM(newDateTime);
                    }

                    void addSecond(int second) {
                        time_t secondsToAdd = second;
                        time_t now = mktime(&m_tm);
                        time_t newDateTime = now + secondsToAdd;
                        setThisTM(newDateTime);
                    }

                    void setThisTM(time_t ltime) {
                        tm *p_tm = localtime(&ltime); // convert to struct tm
                        // copy each attribute
                        m_tm.tm_sec = p_tm->tm_sec; // seconds after the minute - [0,59] 
                        m_tm.tm_min = p_tm->tm_min; // minutes after the hour - [0,59] 
                        m_tm.tm_hour = p_tm->tm_hour; // hours since midnight - [0,23] 
                        m_tm.tm_mday = p_tm->tm_mday; // day of the month - [1,31] 
                        m_tm.tm_mon = p_tm->tm_mon; // months since January - [0,11] 
                        m_tm.tm_year = p_tm->tm_year; // years since 1900 
                        m_tm.tm_wday = p_tm->tm_wday; // days since Sunday - [0,6] 
                        m_tm.tm_yday = p_tm->tm_yday; // days since January 1 - [0,365] 
                        m_tm.tm_isdst = p_tm->tm_isdst; // daylight savings time flag 
                    }

                    void setNow() {
                        time_t ltime;
                        time(&ltime); // get number of seconds elapsed since 00:00:00 on January 1, 1970, 
                        setThisTM(ltime);

#ifdef WIN32	
                        // Windows code
                        //	time_t tz_sec; // Difference in seconds between Greenwitch time and local time
                        //	tz_sec = timezone; 

                        m_miliseconds = 0;
#else
                        // Unix code
                        struct timeval tv;
                        struct timezone tz;
                        gettimeofday(&tv, &tz);
                        m_miliseconds = tv.tv_usec / 1000;

#endif

                        //	m_timeRelativeToGreenwitch = tz_sec / 60 / 60; // Difference in hours
                        // cout << "DEBUG: " << m_timeRelativeToGreenwitch  << endl; // Brazil is -3
                    }

                    operator VBDate() const {
                        VBDate ret;
                        ret.setDate(m_tm.tm_year + 1900, m_tm.tm_mon, m_tm.tm_mday);
                        return ret;
                    }

                    // return date-time as string

                    VBString getDateTimeStr() const {
                        VBString tok = "|";
                        VBString ret;
                        ret += getYear();
                        ret += tok;
                        ret += getMonth();
                        ret += tok;
                        ret += getDay();
                        ret += tok;
                        ret += getHour();
                        ret += tok;
                        ret += getMinute();
                        ret += tok;
                        ret += getSecond();
                        ret += tok;
                        ret += getMiliSecond();

                        return ret;
                    }

                    // set this based in argument, compatible with getDateTimeStr

                    void setDateTimeStr(const char *setTimeStr) {
                        char tok = '|';
                        VBString st = setTimeStr;
                        int year = atoi(st.strtok(tok, 0));
                        unsigned month = atoi(st.strtok(tok, 1));
                        unsigned day = atoi(st.strtok(tok, 2));
                        unsigned hour = atoi(st.strtok(tok, 3));
                        unsigned minute = atoi(st.strtok(tok, 4));
                        unsigned second = atoi(st.strtok(tok, 5));
                        unsigned miliseconds = atoi(st.strtok(tok, 6));

                        setDate(year, month, day);
                        setTime(hour, minute, second, miliseconds);
                    }

                    // return true if this is less than argument

                    bool operator<(const VBDateTime & dt) const {
                        if (getYear() > dt.getYear())
                            return false;
                        if (getYear() < dt.getYear())
                            return true;
                        if (getMonth() > dt.getMonth())
                            return false;
                        if (getMonth() < dt.getMonth())
                            return true;
                        if (getDay() > dt.getDay())
                            return false;
                        if (getDay() < dt.getDay())
                            return true;
                        if (getHour() > dt.getHour())
                            return false;
                        if (getHour() < dt.getHour())
                            return true;
                        if (getMinute() > dt.getMinute())
                            return false;
                        if (getMinute() < dt.getMinute())
                            return true;
                        if (getSecond() > dt.getSecond())
                            return false;
                        if (getSecond() < dt.getSecond())
                            return true;
                        if (getMiliSecond() > dt.getMiliSecond())
                            return false;
                        if (getMiliSecond() < dt.getMiliSecond())
                            return true;

                        return false;
                    }

                    // return true if this is greater than argument

                    bool operator>(const VBDateTime & dt) const {
                        return dt < *this;
                    }

                    bool operator==(const VBDateTime & dt) const {
                        using namespace std;
                        if (getYear() != dt.getYear()) {
                            cout << "DEBUG operator==, year" << endl;
                            return false;
                        }
                        if (getMonth() != dt.getMonth()) {
                            cout << "DEBUG operator==, month" << endl;
                            return false;
                        }
                        if (getDay() != dt.getDay()) {
                            cout << "DEBUG operator==, day" << endl;
                            return false;
                        }
                        if (getHour() != dt.getHour()) {
                            cout << "DEBUG operator==, hour" << endl;
                            cout << "DEBUG getHour()=" << getHour() << endl;
                            cout << "DEBUG dt.getHour()=" << dt.getHour() << endl;
                            return false;
                        }
                        if (getMinute() != dt.getMinute()) {
                            cout << "DEBUG operator==, minute" << endl;
                            return false;
                        }
                        if (getSecond() != dt.getSecond()) {
                            cout << "DEBUG operator==, second" << endl;
                            return false;
                        }
                        if (getMiliSecond() != dt.getMiliSecond()) {
                            cout << "DEBUG operator==, milisecond" << endl;
                            return false;
                        }

                        return true;
                    }

                    int getYear() const {
                        return m_tm.tm_year + 1900;
                    }

                    unsigned getMonth() const {
                        return m_tm.tm_mon;
                    }

                    unsigned getDay() const {
                        return m_tm.tm_mday;
                    }

                    unsigned getHour() const {
                        return m_tm.tm_hour;
                    }

                    unsigned getMinute() const {
                        return m_tm.tm_min;
                    }

                    unsigned getSecond() const {
                        return m_tm.tm_sec;
                    }

                    unsigned getMiliSecond() const {
                        return m_miliseconds;
                    }

                    unsigned long getSecondsToJulianDate() const {
                        unsigned long ret = 0;
                        VBDate julianDate, thisDate;
                        julianDate.setDate(1970, 1, 1);
                        thisDate.setDate(getYear(), getMonth(), getDay());
                        unsigned deltaDays = thisDate.deltaDays(julianDate);

                        // add years
                        ret += deltaDays * 24 * 60 * 60;
                        ret += (getHour()) * 60 * 60;
                        ret += (getMinute()) * 60;
                        ret += (getSecond());

                        return ret;
                    }

                    static void test() {
                        using namespace std;
                        cout << "== VBDateTime::test()" << endl;
                        VBDateTime dt;
                        dt.setNow();

                        VBString time = dt.getDateStr();
                        // cout << time << endl;

                        VBString dtStr = dt.getDateTimeStr();
                        // cout << dtStr << endl;                        
                        VBDateTime dt2;
                        dt2.setDateTimeStr(dtStr);
                        VBDateTime dt3;
                        dt3 = dt2;

                        dt.addMinute(1);
                        dt3.addMinute(1);

                        cout << "before add" << endl;
                        cout << "dt=" << dt.getDateTimeStr() << endl;
                        cout << "dt2=" <<dt2.getDateTimeStr() << endl;
                        cout << "dt3=" <<dt3.getDateTimeStr() << endl;

//                        VBAssert(dt == dt2, "dt == dt2 1");
//                        VBAssert(dt3 == dt2,"dt3 == dt2 1");

                        dt.addSecond(60);
//                        dt2.addMinute(1);
                        dt3.addSecond(60);

                        
                        cout << "after add" << endl;
                        cout << "dt=" << dt.getDateTimeStr() << endl;
                        cout << "dt2=" <<dt2.getDateTimeStr() << endl;
                        cout << "dt3=" <<dt3.getDateTimeStr() << endl;

                        VBAssert(dt == dt2, "dt == dt2 2");
                        VBAssert(dt3 == dt2,"dt3 == dt2 2");
                        
                        return;


                        cout << dt.getDateTimeStr() << endl;
                        cout << dt2.getDateTimeStr() << endl;
                        cout << dt3.getDateTimeStr() << endl;
                        
                        VBAssert(dt == dt2, "dt == dt2 3");
                        VBAssert(dt3 == dt2,"dt3 == dt2 3");

                        return;
                        cout << dt.getDateTimeStr() << endl;
                        cout << dt2.getDateTimeStr() << endl;


                        VBAssert(dt == dt2, "addHour");

                        cout << dt.getDateTimeStr() << endl;
                        cout << dt2.getDateTimeStr() << endl;

                        dt.addSecond(60);
                        dt2.addMinute(1);
                        VBAssert(dt == dt2, "addMinute");

                        cout << dt.getDateTimeStr() << endl;
                        cout << dt2.getDateTimeStr() << endl;

                        //                        VBAssert(now.getSecondsToJulianDate() == 
                        //                                otherTime.getSecondsToJulianDate(),
                        //                                "julian date equal");
                        //
                        //                        int deltaSeconds = 3; // anything
                        //                        otherTime.addSecond(deltaSeconds);
                        //                        VBAssert(now.getSecondsToJulianDate() + deltaSeconds == 
                        //                                otherTime.getSecondsToJulianDate() ,
                        //                                "julian date +");
                        //
                        //                        cout << "now.getSecondsToJulianDate()=" << now.getSecondsToJulianDate() << endl;
                        //                        cout << "otherTime.getSecondsToJulianDate()=" << otherTime.getSecondsToJulianDate() << endl;

                    }


                }; // end of VBDateTime

                //
                ///////////////////////////////////////////////////////////////////////
                ////
                //// class VBDateTimeTimezone
                ////
                ///////////////////////////////////////////////////////////////////////
                //
                //class VBDateTimeTimezone : public VBDateTime
                //{
                //	int m_timeRelativeToGreenwitch;
                //public:
                //	VBDateTimeTimezone() {};
                //
                //}; // end of VBDateTimeTimezone

            }
        }
    }
} // close namespace ::br::com::sbVB::VBLib
