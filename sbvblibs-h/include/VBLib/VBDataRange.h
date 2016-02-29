//  VBDataRange.h

// #define _VBLIB_H_GLOBAL_NOT_AGAIN_
#include "VBLib/VBLib.h"

#pragma once

#include <set>
#include <deque>
#include <sstream>
#include <string>
//#define _VBLIB_H_GLOBAL_NOT_AGAIN_
#include "VBLib/VBLib.h"


namespace br {
    namespace com {
        namespace sbVB {
            namespace VBLib {
                
                template <typename T>
                struct VBSolution {
                    std::string parameters;
                    T value;
                    void setData(const char * par, T val) {
                        parameters = par;
                        value = val;
                    }
                    VBSolution<T>(const char * par="", T  val=0) {
                        setData(par,val);
                    }
                    bool operator<(const VBSolution<T> & ob) const {
                        return value < ob.value;
                    }
                    
                    friend std::ostream & operator << (std::ostream & out, const VBSolution<T> & ob) {
                        out << "VBSolution parameters=" << ob.parameters.c_str() << ", val=" << ob.value;
                        return out;
                    }

                };

                template <typename T>
                struct VBSolutionContainer {
                    std::set< VBSolution<T> > sc;
                    
                    void add(const VBSolution<T> & s) {
                        sc.insert(s);
                    }
                    
                    const VBSolution<T> & getBestSolution() const {
                        auto it = sc.begin(); // iterator to first element
                        return *it;
                    }
                    
                    static void testMe() {
                        using namespace std;
                        VBSolutionContainer<T> sc;
                        sc.add(VBSolution<T>("pameter list 1",1.4));
                        sc.add(VBSolution<T>("pameter list 2",1.2));
                        sc.add(VBSolution<T>("pameter list 3",1.3));
                        
                        cout << sc.getBestSolution() << endl;
                        
                    }                    
                };
                
                template <typename T>
                struct VBDataRange {
                    std::string dataName_;
                    std::deque<T> dataRange_;
                    int i_;

                    void setData(const char * dataName = "", const char * dataRange = "") {
                        using namespace std;
                        using namespace br::com::sbVB::VBLib;
                        dataName_ = dataName;
                        if (dataName_.empty())
                            return;
                        istringstream iss;
                        T val;
                        iss.str(dataRange);
                        while (!iss.eof()) {
                            iss >> val;
                            dataRange_.push_back(val);
                        }
                    }

                    VBDataRange(const char * dataName = "", const char * dataRange = "") : i_(0) {
                        setData(dataName, dataRange);
                    }

                    void dump() const {
                        using namespace std;
                        using namespace br::com::sbVB::VBLib;
                        VBLog::myout << "#### dataName = " << dataName_.c_str() << endl;

                        for (auto i = dataRange_.begin(); i != dataRange_.end(); ++i) {
                            VB_SHOWT(*i);
                        }
                    }

                    T getCurrentData() const {
                        using namespace std;
                        using namespace br::com::sbVB::VBLib;
                        if (i_ >= dataRange_.size() || dataRange_.empty()) {
                            VB_SHOWT(i_);
                            VBLog::myout << "#### getCurrentData range error" << endl;
                            return 0;
                        }
                        T ret = dataRange_[i_];
                        //                        VB_SHOWT(ret);
                        return ret;
                    }

                    void reset() {
                        i_ = 0;
                        //                        VB_SHOWT(getCurrentData());
                    }

                    int size() const {
                        return dataRange_.size();
                    }

                    int getIndex() const {
                        return i_;
                    }

                    void inc() {
                        i_++;
                    }

                    static void testMe() {
                        using namespace br::com::sbVB::VBLib;
                        VBDataRange<double> dr;
                        dr.setData("myvar", "1.1 2.2 3.3");

                        VBAssert(dr.size() == 3);

                        dr.dump();

                        dr.reset();
                        for (auto i = 0; i < dr.size(); ++i) {
                            double d = dr.getCurrentData();
                            VB_SHOWT(d);
                            dr.inc();
                        }

                    }

                }; // end of DataRange

                template <typename T>
                struct VBDataRangeContainer {
                    std::deque< VBDataRange<T> > drContainer;
                    std::deque<T> x;

                    void push(const VBDataRange<T> & dr) {
                        drContainer.push_back(dr);
                    }

                    virtual void myCallBack(void *object = 0) = 0;

                    int getNumberOfRangeVars() {
                        return drContainer.size();
                    }

                    void recursiveCall(int level, void *object = 0) {
                        using namespace std;
                        using namespace br::com::sbVB::VBLib;
                        int numberOfRangeVars = getNumberOfRangeVars();
                        //                        VBLog::myout << "recursiveCall begin" << endl;
                        //                        VB_SHOWT(numberOfRangeVars - level);
                        //                        VB_SHOWT(level);
                        bool execute = true;

                        //                        VB_SHOWT(level);
                        //                        VB_SHOWT(size - level);

                        // if this is the last level, that is, no more recursiveCall
                        if (level <= 1) {
                            // for all variables in the last rangeVar
                            drContainer[numberOfRangeVars - level].reset(); // reset container of current level
                            for (auto i = 0; i < drContainer[numberOfRangeVars - level].size(); ++i) {
                                double d = drContainer[numberOfRangeVars - level].getCurrentData();
                                x[numberOfRangeVars - level] = d;
                                myCallBack(object);
                                //                            VB_SHOWT(i);
                                //                                VB_SHOWT(d);
                                //                                VB_SHOWT(drContainer[numberOfRangeVars - level].getIndex());
                                drContainer[numberOfRangeVars - level].inc();
                            }
                        } else { // it is not the last level, so there is need to call recursive call for level-1    
                            // for all variables in current rangeVar
                            drContainer[numberOfRangeVars - level].reset(); // reset container of current level
                            int nVarsCurrRangeVar = drContainer[numberOfRangeVars - level].size();
                            //                            VB_SHOWT(nVarsCurrRangeVar);
                            for (auto i = 0; i < nVarsCurrRangeVar; ++i) {
                                double d = drContainer[numberOfRangeVars - level].getCurrentData();
                                x[numberOfRangeVars - level] = d;
                                recursiveCall(level - 1, object);
                                drContainer[numberOfRangeVars - level].inc();
                            }
                        }

                        //                        VBLog::myout << "recursiveCall end" << endl;
                    }

                    void resetAllContainers() {
                        for (auto i = drContainer.begin(); i != drContainer.end(); ++i) {
                            i->reset();
                        }
                    }

                    void prepareRecursiveCall() {

                        // all range variables with inner pointer to first variable
                        resetAllContainers();

                        x.resize(getNumberOfRangeVars()); // the x vector has the dimension of the number of range variables added
                        //                        VB_SHOWT(drContainer.size());

                        int k = 0;
                        // x vector with initial value of each range variable
                        for (auto i = drContainer.begin(); i != drContainer.end(); ++i) {
                            x[k] = i->getCurrentData();
                            //                            VB_SHOWT2(k,x[k]);
                            k++;
                        }
                    }

                    void calculateAllSolutions(void *object = 0) {
                        using namespace std;
                        prepareRecursiveCall();
                        recursiveCall(getNumberOfRangeVars(), object);
                    }

                    T getData(const char *dataName) const {
                        using namespace std;
                        using namespace br::com::sbVB::VBLib;
                        //                        VBLog::myout << "@@@@@@@@@@@ dataName=" << dataName << endl;
                        T ret = 0;
                        for (auto i = drContainer.begin(); i != drContainer.end(); ++i) {
                            //                            VBLog::myout << "loop dataName=" << i->dataName_ << endl;
                            if (i->dataName_ == dataName) {
                                ret = i->getCurrentData();
                                break;
                            }
                        }
                        return ret;
                    }

                    void incData(const char *dataName) {
                        for (auto i = drContainer.begin(); i != drContainer.end(); ++i) {
                            if (i->dataName_ == dataName)
                                i->inc();
                        }
                    }

                    template <typename TT>
                    struct VBDataRangeContainerTest : public VBDataRangeContainer<TT> {

                        void myCallBack(void *object = 0) {
                            using namespace std;
                            using namespace br::com::sbVB::VBLib;
                            //                            VBLog::myout << "@@@@@@@@@@@ myCallBack begin" << endl;
                            static int count = 0;
                            count++;
//                            VB_SHOWT(count);

                            //                            int numberOfRangeVars = getNumberOfRangeVars();
                            //                            VB_SHOWT(numberOfRangeVars);
                            //                            VBAssert(getNumberOfRangeVars() == 3);

                            // it is necessary to use this-> before the member variables
                            // because this is a virtual method
                            ostringstream oss;
                            oss << count << ": (";
                            for (auto i = this->x.begin(); i != this->x.end(); ++i) {
                                //                                VB_SHOWT(*i);
                                oss << *i;
                                if ((i + 1) != this->x.end())
                                    oss << ","; // add "," to after all variables but the last one
                            }
                            oss << ")" << endl;
                            
                            string ossStr = oss.str();

//                            double x1 = this->getData("x1");
//                            double x2 = this->getData("x2");
//                            double x3 = this->getData("x3");
//                            double x4 = this->getData("x4");
//                            VB_SHOWT(x1);
//                            VB_SHOWT(x2);
//                            VB_SHOWT(x3);
//                            VB_SHOWT(x4);

                            //                            VBLog::myout << "@@@@@@@@@@@ myCallBack end" << endl;
                        }
                    };

                    static void testMe() {
                        VBDataRangeContainer<T> *drc = new VBDataRangeContainerTest<T>();
                        drc->push(VBDataRange<T>("x1", "11 12 13"));
                        drc->push(VBDataRange<T>("x2", "21 22 23"));
                        drc->push(VBDataRange<T>("x3", "31 32"));
                        drc->push(VBDataRange<T>("x4", "41 42 43"));
                        //                        drc->push(DataRange<T>("x5", "51 52"));

                        //                        VB_SHOWT(drc.getData("x1"));
                        //                        VB_SHOWT(drc.getData("x2"));
                        //                        drc.incData("x2");
                        //                        VB_SHOWT(drc.getData("x2"));


                        drc->calculateAllSolutions();

                        //                        drc.dump();

                        delete drc;

                    }

                    void dump() const {
                        using namespace std;
                        using namespace br::com::sbVB::VBLib;
                        VBLog::myout << "DataRangeContainer dump" << endl;
                        for (auto i = drContainer.begin(); i != drContainer.end(); ++i) {
                            i->dump();
                        }
                    }
                };





            }
        }
    }
} // close namespace br::com::sbVB::nlp



