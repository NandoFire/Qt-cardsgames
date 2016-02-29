// VBMcgi.h
#ifndef __VBMCGI__
#define __VBMCGI__

#include <stdarg.h>
#include "VBLib/VBLib.h"


namespace br {
    namespace com {
        namespace sbVB {
            namespace VBMcgi {



                /////////////////////////////////////////////////////////////////////////////////////
                //
                // Defines for string mensages
                //
                /////////////////////////////////////////////////////////////////////////////////////

                // used when some file cannot be open or write
#define CANOTOPENFILE "Cannot process file "

                // used when memory alloc fail
#define INTERNAL_ERROR "Internal VBMcgi Error (failed to alloc memory)"  

                // used when no getenv(QUERY_STRING) return NULL
#define NO_QUERY_STRING	"someName=someValue"  

                // define string to find when search for function in html code, like SSI
                // signature of call
#define CALL_SIG "VBMCGI_CALL"

                // define maximal value for data upload (through POST) in one chunck
                // for now (2003-01-20) VBMcgi::formDecode only deals with one chunck
#define MAX_CONTENT_LENGTH 8*1024*1024 // 8MB

                //#define addFunction(fun,obj) addFunctionHelper(#fun,fun,(void*)& obj)
#define addFunction(fun) addFunctionHelper(#fun,fun)
#define addFunctionObj(fun,obj) addFunctionHelper(#fun,fun,(void*)& obj)


                class VBMcgi; // early class definition

                // function pointer type definition of functions that can 
                // be called by VBMCGI_CALL, and addFunction method
                typedef void (*fpType)(VBMcgi &obj, void *p);

                // prototype of custom callback
                void myCallBack(VBMcgi & cgi, void *p);


                // main VBMcgi class

                class VBMcgi {
                    ////////////////////////////////////////////////////////////////////////////////
                    // classes inside VBMcgi
                    ////////////////////////////////////////////////////////////////////////////////

                    class VBMcgi_FuncionNode {
                    public:
                        br::com::sbVB::VBLib::VBString m_funName;
                        fpType m_funPtr;
                        void *m_pToUserClass;

                        VBMcgi_FuncionNode(const char *funName = "",
                                fpType funPtr = 0,
                                void *pToUserClass = 0) {
                            m_funName = funName;
                            m_funPtr = funPtr;
                            m_pToUserClass = pToUserClass;
                        }
                    };

                    class VBMcgi_changeStringNode {
                    public:
                        br::com::sbVB::VBLib::VBString m_find, m_replace;

                        VBMcgi_changeStringNode(const char *find = "", const char *replace = "") {
                            m_find = find;
                            m_replace = replace;
                        }

                        bool operator==(const VBMcgi_changeStringNode &obj) { // ret = (this==a);
                            return m_find == obj.m_find;
                        }

                    };

                    enum HttpMethod {
                        GET,
                        POST,
                        UNDEFINED
                    };

                    char m_tok; // for getHtmlParameter
                    bool m_noHeader; // if true, cancel the http header

                    ////////////////////////////////////////////////////////////////////////////////
                    // attributes for cookie
                    ////////////////////////////////////////////////////////////////////////////////

                    br::com::sbVB::VBLib::VBString m_cexpires, m_current_time, m_cpath, m_cdomain, m_cnamevalue;
                    bool m_csecure;

                    // list of pairs of strings (search string and replace string)
                    br::com::sbVB::VBLib::VBList<VBMcgi_changeStringNode> m_xchgList;

                    // list form fields and contents in the form decode, for getVarContent (GVC)
                    // in version 1.x, it was done m_xchgList and m_xchgListGVC were the same variable
                    br::com::sbVB::VBLib::VBList<VBMcgi_changeStringNode> m_xchgListGVC;

                    // list of functions to be replaced in VBMCGI_CALL(userFunction)
                    br::com::sbVB::VBLib::VBList<VBMcgi_FuncionNode> m_funcList;

                    // defined inside the VBMcgi object, but used as a global variable due to the "static"
                    static bool m_static_haveHeader;
                    br::com::sbVB::VBLib::VBString m_callString;



                    // check if functionName exist in linked list of function
                    // if true, run relative function

                    void runFunction(const char *functionName) {
                        using namespace std;
                        using namespace br::com::sbVB::VBLib;

                        bool ret = false;
                        VBMcgi_FuncionNode *ptrTemp;

                        // p2 is to be used for function. This must exist even if not used.
                        // scan the list of funcData to search for function names that match
                        for (ptrTemp = m_funcList.GetFirst(); ptrTemp; ptrTemp = m_funcList.GetNext()) {
                            // cout << "DEBUG: functionName=" << functionName << endl;
                            if (ptrTemp->m_funName == VBString(functionName)) {
                                // run function
                                ptrTemp->m_funPtr(*this, ptrTemp->m_pToUserClass);
                                break; // break the search in the list
                            }
                        }
                    }


                    // path to the directory where to save uploaded files
                    br::com::sbVB::VBLib::VBString m_uploadDir;

                    // html parameners
                    // parameters that one pass from html directly to the user function with VBMCGI_CALL
                    // example: VBMCGI_CALL(userFun,1,2,3) => htmlParameters are 1,2,3
                    br::com::sbVB::VBLib::VBString m_htmlParameters;
                    unsigned m_numberOfParameters;
                    br::com::sbVB::VBLib::VBString m_tokStr;


                public:


                    // default constructor

                    VBMcgi()
                    : m_tok(',')
                    , m_csecure(false)
                    , m_callString("VBMCGI_CALL")
                    , m_noHeader(false)
                    // , m_out(out) 
                    {
                        //    addFunction(file);
                        //    addFunction(SSI);
                        char buff[2];
                        buff[0] = m_tok;
                        buff[1] = 0; // termination string
                        m_tokStr = buff;
                    };

                    // http headers

                    void httpHeader(const char *headerType = "text/html",
                            std::ostream & myCout = std::cout) {
                        using namespace std;
                        myCout << "Content-type:" << headerType << endl;
                    }

                    void httpCompleteHeader(const char *headerType = "text/html",
                            std::ostream & myCout = std::cout) {
                        using namespace std;
                        if (!m_static_haveHeader) {
                            httpHeader(headerType, myCout);
                            myCout << endl; // finalize header
                            m_static_haveHeader = true;
                        }

                    }
                    
                    // use this if you want to cancel http header in out method
                    void setNoHeader() {
                        m_noHeader = true;
                    }



                    // set name/value pairs in cookie, add separator betwen pairs 

                    void setCookieNameValue(const char *cookieName, const char *cookieValue) {
                        m_cnamevalue = cookieName;
                        // complete string with = and value 
                        m_cnamevalue += "=";
                        m_cnamevalue += cookieValue;
                    }

                    // set expires value to cookie, can be: now, end of session
                    // or in any future time, like: x minutes or y hours or z years

                    void setCookieExpires(const char *period, int value = 0) {
                        using namespace br::com::sbVB::VBLib;
                        using namespace std;
                        // get system time
                        time_t now, result;
                        time(&now);
                        tm when;
                        when = *localtime(&now);

                        // calculate date to expire cookie, adding value to current date
                        if (value) {
                            if (VBString(period) == "year") when.tm_year += value;
                            if (VBString(period) == "day") when.tm_mday += value;
                            if (VBString(period) == "hour") when.tm_hour += value;
                            if (VBString(period) == "minute") when.tm_min += value;

                            // adjust structure to real time/date format 
                            if ((result = mktime(&when)) != (time_t) - 1) {
                                when = *localtime(&result);
                                char cexpires[300];
                                strftime(cexpires, 30, "%a, %d-%b-%Y %H:%M:%S GMT", &when);
                                m_cexpires = cexpires;
                            }
                        } else {
                            m_cexpires = period;
                        }

                        if (VBString(period) == VBString("now")) m_cexpires = m_current_time;
                        if (VBString(period) == VBString("end-of-session")) m_cexpires = "";

                    }

                    // set all others (optional) field in cookie structure
                    // like: path, domain and secure

                    void setCookieField(const char *cookieField, const char *cookieValue) {

                        using namespace br::com::sbVB::VBLib;
                        // check what field is to set, and associated value to this

                        if (VBString(cookieField) == "domain")
                            m_cdomain = cookieValue;

                        if (VBString(cookieField) == "path")
                            m_cpath = cookieValue;

                        if (VBString(cookieField) == "secure")
                            m_csecure = true;

                    }

                    // send cookie structure to browser.  name and value must be set
                    // after this, reset name and value variables, but leave anyone else

                    void sendCookie() {
                        using namespace std;
                        if (!m_cnamevalue.IsEmpty()) // if the cookie has a name
                        {
                            cout << "Set-Cookie: " << m_cnamevalue;
                            cout << ";expires=" << m_cexpires; // inconditionally set expires
                            if (!m_cpath.IsEmpty()) cout << ";path=" << m_cpath;
                            if (!m_cdomain.IsEmpty()) cout << ";domain=" << m_cdomain;
                            if (m_csecure) cout << ";secure";
                        }
                        cout << endl; // close this cookie.

                    }

                    // return cookie value from HTTP_COOKIE variable, if existe, else null

                    br::com::sbVB::VBLib::VBString getCookieValue(const char *cookieName) {
                        using namespace br::com::sbVB::VBLib;
                        using namespace std;

                        VBString ret;
                        char *cookie = getenv("HTTP_COOKIE");

                        // if getenv(HTTP_COOKIE) returns something valid
                        if (cookie) {
                            VBString completeCookieString, oneCookie;
                            VBString before;

                            // tmpString = "cookieName=cookieValue;cookieName2=cookieValue2;cookieName3=cookieValue3";
                            completeCookieString = cookie;

                            bool stop = false;
                            unsigned i = 0;
                            while (!stop) {
                                oneCookie = completeCookieString.strtok(';', i);
                                before = oneCookie.beforeFind("=");
                                if (before == cookieName) {
                                    ret = oneCookie.afterFind("=");
                                    return ret;
                                }
                                i++;
                                stop = oneCookie.IsEmpty();
                            }

                        }
                        // if there's no cookie with given name, or getenv(HTTP_COOKIE) returns nothing, return ""
                        return ret;

                    }

                    // return true if cookie named cookieName exists

                    bool existCookie(const char *cookieName) {
                        using namespace br::com::sbVB::VBLib;
                        VBString cookieVal = getCookieValue(cookieName);
                        return (cookieVal != VBString(""));
                    }

                    // add pair variable/content from source code 

                    void addBySource(const char* find, const char* replace) {
                        if (strlen(find)) // if find string exists
                        {
                            VBMcgi_changeStringNode xchgNodeLocal(find, replace);
                            m_xchgList.add(xchgNodeLocal);
                        }
                    };


                    // add pair variable/content from external file

                    void addByFile(const char* filein) {
                        using namespace br::com::sbVB::VBLib;
                        using namespace std;

                        VBString vn, vc, tmpString;
                        ifstream infile;

                        infile.open(filein);
                        if (!infile) {

                            VBString tmpString(CANOTOPENFILE);
                            tmpString += filein;

                            // send to sdtout a error msg 
                            htmlError(tmpString);
                        }

                        // master loop to read file
                        while (true) {
                            infile >> tmpString;

                            if (infile.eof()) break;

                            vn = tmpString.beforeFind(" ");
                            vc = tmpString.afterFind(" ");
                            addBySource(vn, vc);
                        };

                    }

                    // remove pair variable/content from source code 

                    void removeBySource(const char* find) {
                        VBMcgi_changeStringNode f(find, ""); // the second string is not used
                        m_xchgList.remove(f);

                    }

                    // return the data content variable partner with name passed

                    br::com::sbVB::VBLib::VBString getVarContent(const char* find) {
                        using namespace br::com::sbVB::VBLib;
                        // possible bug here, because use of replace in first argument of tempData
                        // xchgNode xchgNodeLocal(find,find);
                        VBMcgi_changeStringNode *ptrTemp; // =xchgList.get(xchgNodeLocal);

                        // exchange strings like done in changeAndStdOut
                        for (ptrTemp = m_xchgListGVC.GetFirst(); ptrTemp; ptrTemp = m_xchgListGVC.GetNext()) {
                            if (ptrTemp->m_find == VBString(find)) {
                                return (ptrTemp->m_replace); // return the char* inside VBString
                                // break; // break the search in the list
                            }
                        }
                        return (""); // no data to show
                    }

                    // check if some var name and var content match
                    // this method is used in special situations
                    // the usage with variable number of parameters is rare

                    bool getVarContent(const char *find, const char *replace, ...) {
                        using namespace br::com::sbVB::VBLib;
                        // check if find have at least one pair
                        if (VBString(getVarContent(find)) == VBString("")) {
                            return (false);
                        }
                        bool foundNode = false;
                        char *varList = (char *) replace;
                        VBMcgi_changeStringNode *ptrTemp;

                        // Initialize variable arguments.
                        va_list marker;
                        va_start(marker, replace);

                        bool continueLoop = strlen(varList) > 0;
                        while (continueLoop) {
                            const char *szVarList = varList;

                            // for all variables registered 
                            for (ptrTemp = m_xchgListGVC.GetFirst(); (ptrTemp && !foundNode); ptrTemp = m_xchgListGVC.GetNext()) {
                                if (VBString(find) == ptrTemp->m_find &&
                                        VBString(szVarList) == ptrTemp->m_replace) {
                                    foundNode = true;
                                } else {
                                    foundNode = false;
                                }
                            }

                            // get the next argument
                            if (foundNode) {
                                varList = va_arg(marker, char*);
                                if (strlen(varList) > 0) {
                                    foundNode = false;
                                    continueLoop = true;
                                }
                            } else {
                                if (strlen(varList) == 0)
                                    continueLoop = false;
                            }


                        } // end while

                        // Reset variable arguments.
                        va_end(marker);

                        return (foundNode);


                    }
                    // easy-to-use method to get check-box

                    bool getCheckBox(const char *find, const char *replace) {
                        return getVarContent(find, replace, "");
                    }

                    // put pairs of function name and pointers to functions
                    // in a linked list to future use from runFunction
                    // add one pair for each call  return 0 means alloc o
                    // retunr 1 means could not alloc memory
                    // put pairs of function name and pointers to functions
                    // in a linked list to future use from runFunction
                    // pToUserClass is ...
                    // bool addFunctionHelper(const char *functionName, fpType ptr, void *p = 0);

                    void addFunctionHelper
                    (const char *functionName, fpType pointer, void *pToUserClass) {

                        VBMcgi_FuncionNode funcNodeLocal(functionName, pointer, pToUserClass);
                        m_funcList.add(funcNodeLocal);
                    }

                    void implementCallFunctionFeature(br::com::sbVB::VBLib::VBString & inputLine,
                            std::ostream & myCout = std::cout) {

                        using namespace std;
                        using namespace br::com::sbVB::VBLib;

                        VBString callArgument;
                        VBString functionToCall;
                        VBString stringAfterCall;

                        // implement the call function feature
                        // scan the current line to find callReservedWord
                        // callReservedWord is most likely to be "VBMcgi_CALL"
                        while (true) {
                            // send string before next call
                            myCout << inputLine.beforeFind(m_callString);

                            // store string after call and function name
                            inputLine = inputLine.afterFind(m_callString);

                            // if there was no more occurrences of callReservedWord, break loop
                            if (inputLine == "") break;

                            // get argument of CALL_SIG(argument); argument=name,parameters
                            callArgument = inputLine.beforeFind(")");

                            // call arguments begin
                            // get function name
                            functionToCall = callArgument.beforeFind(m_tokStr);

                            // get function parameters
                            m_htmlParameters = callArgument.afterFind(m_tokStr);

                            if (m_htmlParameters == "") {
                                m_numberOfParameters = 0;
                            } else {
                                m_numberOfParameters = m_htmlParameters.tokCount(m_tok) + 1;
                            }


                            if (functionToCall.getChar(0) == '(')
                                functionToCall = functionToCall.afterFind("(");

                            // run specified function, if exist
                            //if (functionToCall != VBString("")) // unnecessary
                            runFunction(functionToCall);

                            // store only string after call
                            stringAfterCall = stringAfterCall.afterFind(")");
                            // call arguments end

                        };

                    }


                    // the main method to output data implementing 
                    // string change feature and call function feature

                    void out(const char* fileName, std::ostream & myCout = std::cout) {
                        using namespace std;
                        using namespace br::com::sbVB::VBLib;

                        if (!m_noHeader) {
                            // send html header *if* not sent yet
                            httpCompleteHeader("text/html", myCout);
                        }

                        VBMcgi_changeStringNode *ptrTemp = 0;
                        VBString inputLine;

                        ifstream outFile(fileName);
                        if (!outFile) {
                            VBString tmpString(CANOTOPENFILE);
                            tmpString += fileName;
                            // send to sdtout a error msg
                            htmlError(tmpString);
                        }


                        // read the entire changeFile and keep its contents as VBStrings
                        // in the linked list

                        VBString callReservedWord = CALL_SIG; // most likely "VBMCGI_CALL"
                        char tok[2]; // tok as string
                        tok[0] = m_tok;
                        tok[1] = 0; // terminate string
                        callReservedWord += "(";

                        while (true) // loop to scan the entire file
                        {
                            outFile >> inputLine;

                            if (outFile.eof() && inputLine.IsEmpty()) break;

                            // implementation of string change feature
                            for (ptrTemp = m_xchgList.GetFirst(); ptrTemp;
                                    ptrTemp = m_xchgList.GetNext())
                                inputLine.strschg(ptrTemp->m_find, ptrTemp->m_replace);

                            implementCallFunctionFeature(inputLine, myCout);

                            myCout << inputLine << endl;

                        } // end of loop to scan the entire file

                        outFile.close();

                    };


                    // get and set m_uploadDir

                    br::com::sbVB::VBLib::VBString getUploadDir() {
                        return m_uploadDir;
                    }

                    void setUploadDir(br::com::sbVB::VBLib::VBString dir) {
                        m_uploadDir = dir;
                    } // MUST have a trailing '/' (unix) or '\' (win)

                    // get html parameters

                    br::com::sbVB::VBLib::VBString getHtmlParameterString() {
                        return m_htmlParameters;
                    }
                    br::com::sbVB::VBLib::VBString getHtmlParameter(unsigned i);

                    unsigned getHtmlParameterNumber() {
                        return m_numberOfParameters;
                    }


                    // send to stdout error msg

                    void htmlError(const char* errorMsg) {
                        using namespace std;
                        httpHeader("text/html");
                        cout << "<title>VBMcgi Error</title>" << endl;
                        cout << "<html><body bgcolor=\"#FFFFFF\"><p align=\"center\">" << endl;
                        cout << "<a href=\"http://www.sbvb.com.br/vbmcgi\">VBMcgi</a> error: <br>" << errorMsg << "<br>" << endl;
                        cout << "</p></body></html>" << endl;
                        exit(0);
                    }

                    // decode variable from forms
                    // new name of urldecode

                    int formDecode(bool copyToGetVarContents = false) {
                        using namespace br::com::sbVB::VBLib;

                        VBString queryStringStr;
                        const char *requestMethod, *queryString; // , *contentType;
                        VBString contentType;
                        unsigned contentLength = 0;
                        HttpMethod method;
                        bool error = false;

                        // define request method
                        // POST method has CONTENT_TYPE and CONTENT_LENGTH and not QUERY_STRING
                        // GET method has QUERY_STRING and not CONTENT_TYPE nor CONTENT_LENGTH
                        requestMethod = getenv("REQUEST_METHOD");
                        if (requestMethod == 0) {
                            // no REQUEST_METHOD specified, assume GET
                            method = GET;
                        } else {
                            VBString requestMethodStr = requestMethod;
                            requestMethodStr.toUpper();
                            // define INPUT method : accept POST or GET and reject any other
                            method = UNDEFINED;
                            if (requestMethodStr == "GET") method = GET;
                            if (requestMethodStr == "POST") method = POST;
                        }

                        // request method is defined. It should be either get or post
                        switch (method) {
                            case GET: // this method passes data through environment variable QUERY_STRING
                            {
                                queryString = getenv("QUERY_STRING");
                                if (queryString != 0)
                                    // if there's something in the variable queryString
                                    queryStringStr = queryString;
                                else
                                    // if there's nothing in the variable queryString
                                    queryStringStr = NO_QUERY_STRING;
                                break;
                            } // end of case GET


                            case POST: // this method passes data through stdin
                            {
                                // begin of POST code that does not support http upload
                                // first verify CONTENT_TYPE
                                // in future will call another function to operate with others data type
                                const char *contType = getenv("CONTENT_TYPE");
                                if (contType == 0 || VBString(contType) != "application/x-www-form-urlencoded") {
                                    htmlError("VBMcgi Error: Data type not supported, must be application/x-www-form-urlencoded");
                                }

                                // get size of data to read, put it in long variable
                                const char *contentLengthStr = getenv("CONTENT_TYPE");
                                contentLength = 0;
                                if (contentLengthStr)
                                    contentLength = atoi(contentLengthStr);

                                //                                // create buffer and bufferDataOut 
                                //                                char *buffer = new char[(contentLength + 1)]; // +1 for the termination char
                                //                                buffer[0] = 0; // terminate string
                                //
                                //                                // read data from SDTIN and put it in bufferDataIn
                                //                                cin.read(buffer, contentLength);
                                //                                buffer[contentLength] = '\0';

                                std::cin >> queryStringStr;

                                // output error if size of data if not equal to contenLength 
                                if (queryStringStr.length() != contentLength)
                                    htmlError("VBMcgi Error: I/O error reading query string");

                                // copy to a VBString
                                // queryStringStr = buffer;
                                // delete buffer
                                //                                if (buffer)
                                //                                    delete [] buffer;
                                //                                break;

                                // end of POST code that does not support http upload

                            } // case POST

                            default:
                            {
                                htmlError("VBMcgi Error: Method must be either post or get");
                                return (1); // return error and stop program 
                            };

                        } // end switch method

                        //////////////////////////////////////////////////////////////////
                        // at this point, either by post or get method, the queryStringStr 
                        // has the data from the html form
                        //////////////////////////////////////////////////////////////////

                        if (!queryStringStr.IsEmpty()) {
                            // decode query string and addByCode field_name paired with field_contents
                            int tokCount = 0;
                            VBString field;
                            do {
                                field = queryStringStr.strtok('&', tokCount);
                                bool hasEqualChar = false;
                                for (unsigned long i = 0; i < field.getLength(); i++) {
                                    if (field[i] == '=') {
                                        hasEqualChar = true;
                                        break;
                                    }
                                }
                                if (hasEqualChar) {
                                    // increment tok count, so that next time the field will
                                    // get the next pair of field_name and field_contents
                                    tokCount++;

                                    VBString field_name = field.strtok('=', 0);
                                    VBString field_contents = field.strtok('=', 1);

                                    field_name.escapeSequenceReverse();
                                    field_contents.escapeSequenceReverse();

                                    // add the pair field_name, field_contents to the variable that is used by getVarContent
                                    VBMcgi_changeStringNode xchgNodeLocal(field_name, field_contents);
                                    m_xchgListGVC.add(xchgNodeLocal);

                                    // if asked to, also gives "addBySource" to this, so the
                                    // "call function feature" will work on the same string pairs
                                    if (copyToGetVarContents) {
                                        addBySource(field_name, field_contents);
                                    }
                                }
                            } while (field.length() > 0);
                        }

                        return 0; // no error


                    }


                    // redirects browser to szUrl 

                    void redirect(const char *szUrl) {
                        using namespace std;
                        // status 301 is needed to make the client browser see correctly
                        // the address field
                        cout << "status: 301" << endl;

                        // 2 endl's are needed, otherwise it doesn't work !
                        cout << "location: " << szUrl << endl << endl;
                    }

                    // upload ONE file
                    // bool upload (const char *fileName);

                    br::com::sbVB::VBLib::VBString systemTime() {
                        using namespace br::com::sbVB::VBLib;
                        using namespace std;
                        VBString ret;

                        time_t ltime;
                        time(&ltime); // get time
                        struct tm *t = localtime(&ltime); // convert to tm struct

                        char buffer[10];
                        ret = "";
                        sprintf(buffer, "%02d", t->tm_hour);
                        ret += buffer;
                        ret += ":";
                        sprintf(buffer, "%02d", t->tm_min);
                        ret += buffer;
                        ret += ":";
                        sprintf(buffer, "%02d", t->tm_sec);
                        ret += buffer;

                        return ret;

                    }

                    br::com::sbVB::VBLib::VBString systemDatePortuguese() {
                        using namespace br::com::sbVB::VBLib;
                        using namespace std;
                        VBString ret;

                        time_t ltime;
                        time(&ltime); // get time
                        struct tm *t = localtime(&ltime); // convert to tm struct

                        const char *months[] = {
                            "Janeiro",
                            "Fevereiro",
                            "Marco",
                            "Abril",
                            "Maio",
                            "Junho",
                            "Julhy",
                            "Agosto",
                            "Setembro",
                            "Outubro",
                            "Novembro",
                            "Dezembro"
                        };

                        char buffer[10];
                        ret = "";
                        sprintf(buffer, "%02d", t->tm_mday);
                        ret += buffer;
                        ret += " de ";
                        ret += months[t->tm_mon];
                        ret += " de ";
                        ret += (1900 + t->tm_year);

                        return ret;

                    }


                    char getTok() const {
                       return m_tok;
                    }
                    
                    void setTok(char tok) {
                        m_tok = tok;
                    }


                    // the name was changed from test() to VBMcgi_test()
                    // not to confuse with VBMcgi::test()

                    static void VBMcgi_test() {
                        using namespace std;
                        using namespace br::com::sbVB::VBLib;
                        cout << "== VBMcgi_test()" << endl;

                        const char *fileName = "VBMcgi_out.html";
                        ofstream outFile(fileName);
                        if (!outFile) {
                            cout << "file not open (problems with permission ?)" << endl;
                            return;
                        }
                        VBAssert(outFile); // file is open

                        outFile << "text find_1_this text find_1_this text" << endl;
                        outFile << "text find_2_this text" << endl;
                        outFile << "text find_3_this text" << endl;

                        outFile.close();

                        VBMcgi cgi;
                        cgi.addBySource("find_1_this", "replace_for_this_1");
                        cgi.addBySource("find_2_this", "replace_for_this_2");
                        cgi.addBySource("find_3_this", "replace_for_this_3");

                        ostringstream oss;
                        cgi.out(fileName, oss);

                        VBString outStr = oss.str().c_str();

                        VBAssert(outStr ==
                                "Content-type:text/html\n\n"
                                "text replace_for_this_1 text replace_for_this_1 text\n"
                                "text replace_for_this_2 text\n"
                                "text replace_for_this_3 text\n");

                        // cout << outStr << endl;

                        ///////////////////////////////////////////////

                        oss.str(""); // clear the object

                        //                        cgi.addBySource("find_1_this", "replace_for_this_1");
                        //                        cgi.addBySource("find_2_this", "replace_for_this_2");
                        //                        cgi.addBySource("find_3_this", "replace_for_this_3");
                        cgi.addFunctionObj(myCallBack, oss);

                        outFile.open(fileName);
                        if (!outFile) {
                            cout << "file not open (problems with permission ?)" << endl;
                            return;
                        }
                        VBAssert(outFile); // file is open

                        outFile << "text find_1_this text" << endl;
                        outFile << "text find_2_this text" << endl;
                        outFile << "text VBMCGI_CALL(myCallBack) text" << endl;
                        outFile << "text find_3_this text" << endl;

                        outFile.close();

                        cgi.out(fileName, oss);

                        outStr = oss.str().c_str();

                        cout << "'" << outStr << "'" << endl;
                    }
                };



                ////////////////////////////////////////////////////////////////////
                // VBMath classes
                /////////////////////////////////////////////////////////////////////



                // test of the whole VBMcgi library

                void test() {
                    std::cout << "=== VBMcgi::test()" << std::endl;
                    VBMcgi::VBMcgi_test();

                }

                void myCallBack(VBMcgi & cgi, void *p) {
                    using namespace std;
                    using namespace br::com::sbVB::VBLib;

                    ostream * out = (ostream*) p;
                    *out << "********** inside myCallBack";
                }



            }
        }
    }
} // close namespace ::br::com::sbVB::VBMcgi

// defined inside the VBMcgi object, but used as a global variable due to the "static"
bool br::com::sbVB::VBMcgi::VBMcgi::m_static_haveHeader = false;


#endif



