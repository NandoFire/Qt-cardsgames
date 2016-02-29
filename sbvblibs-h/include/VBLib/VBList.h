// VBList.h

// all entities in namespace br::com::sbVB::VBLib
namespace br {
    namespace com {
        namespace sbVB {
            namespace VBLib {


                /////////////////////////////////////////////////////////////////////
                //
                // VBList
                // a generic (using template) single linked list 
                //
                /////////////////////////////////////////////////////////////////////

                template <typename T>
                class VBList {

                    struct node {
                        T data;
                        node *p_next;
                    }; // end of class node

                    node *p_first, *p_last, *p_nextSave;
                    //  void (*error_function)();  // pointer to function

                    T *GetFirstConst(void* & externalPointer) const {
                        if (p_first) {
                            externalPointer = p_first->p_next;
                            return &p_first->data;
                        } else
                            return NULL;
                    };

                    T *GetNextConst(void* & externalPointer) const {
                        node *ret = (node*) externalPointer;
                        if (ret) {
                            externalPointer = (void*) ret->p_next;
                            return &ret->data;
                        } else
                            return NULL;
                    };

                public:
                    // default constructor

                    VBList() {
                        p_first = p_last = p_nextSave = NULL;
                        // error_function=error_fun;
                    }; // end of VBList();

                    T *GetFirst() {
                        if (p_first) {
                            p_nextSave = p_first->p_next;
                            return &p_first->data;
                        } else
                            return NULL;
                    };

                    T *GetNext() {
                        node *ret = p_nextSave;
                        if (p_nextSave) {
                            p_nextSave = (node*) p_nextSave->p_next;
                            return &ret->data;
                        } else
                            return NULL;
                    };

                    // add data to list (addTail)

                    bool add(const T & newData) {
                        node *p_new;
                        //	ASSERT(p_new=new node);
                        if ((p_new = new node) == NULL)
                            return (1);
                        // return true if allocation fails

                        p_new->data = newData; // copies data to list
                        // if new element is the first element of list
                        if (!p_first) {
                            p_first = p_last = p_new;
                            p_new->p_next = NULL;
                        }// if new element is NOT the first element of list
                        else {
                            p_last->p_next = p_new; // previous p_last points to new element
                            p_new->p_next = NULL; // finnish list
                            p_last = p_new; // now p_last points to new element
                        }
                        return (0);
                    }; // end of void add(T & newData)

                    // delete the whole list

                    void deleteAll() {
                        node *p_t1, *p_t2;
                        if (p_first) // if list exists
                        {
                            p_t1 = p_first;
                            p_t2 = p_first->p_next;
                            do { // since list exists, at least 1 delete

                                p_t1 = p_t2;
                                if (p_t2)
                                    p_t2 = p_t2->p_next;
                            } while (p_t1 != NULL);
                            p_last = p_first = NULL;
                        }
                    }; // end void deleteAll()

                    // delete one data from list

                    void remove(const T & dataToDelete) {
                        node *p_t1, *p_t2, *p_t3;
                        if (p_first) // if list exists
                        {
                            p_t1 = p_first;
                            p_t2 = p_first->p_next;

                            // if data to delete is the first one
                            // T must have operator== defined
                            if (p_first->data == dataToDelete) {
                                // for debug
                                // cout << "DEBUG Deleted:"<< p_first->data << endl;
                                delete p_first;
                                p_first = p_t2;
                                remove(dataToDelete); // recursivelly calls remove, to 
                                // be sure 
                            } else { // the data to delete is not the first one

                                // this loop will seek for data to delete and delete it
                                while (p_t1->p_next != NULL) { // since list exists, at least 1 delete

                                    if (p_t2->data == dataToDelete) {
                                        // for debug
                                        // cout << "DEBUG Deleted:"<< p_t2->data << endl;
                                        p_t3 = p_t2->p_next;
                                        delete p_t2;
                                        p_t1->p_next = p_t3; // re-links the list (bypass p_t2)
                                        // break; // if after deleting, stop the loop, uncomment this break
                                        // but it's better not to stop. Keep trying to delete until the end of list
                                        p_t2 = p_t3; // to keep going
                                    } else {
                                        // move pointers one step into the list
                                        // only if no remove was made.
                                        p_t1 = p_t2;
                                        p_t2 = p_t2->p_next;
                                    }

                                } // while
                            } // else
                        } // if p_first
                    } // remove

                    // default destructor

                    ~VBList() {
                        deleteAll();
                    }; // end of ~VBList();

                    // copy constructor

                    VBList(const VBList & obj) {
                        p_first = p_last = p_nextSave = NULL;
                        void *externalPointer;
                        T *p;
                        for (p = obj.GetFirstConst(externalPointer); p; p = obj.GetNextConst(externalPointer)) {
                            add(*p);
                        }
                    }

                    void operator=(const VBList & obj) {
                        void *externalPointer;
                        T *p;
                        for (p = obj.GetFirstConst(externalPointer); p; p = obj.GetNextConst(externalPointer)) {
                            add(*p);
                        }
                    }

                    static void test() {
                        std::cout << "== VBList<" << typeid (T).name()
                                << ">::test()" << std::endl;

                        T a[3];
                        a[0] = 1.1;
                        a[1] = 2.2;
                        a[2] = 3.3;

                        VBList<T> myList;
                        myList.add(a[0]);
                        myList.add(a[1]);
                        myList.add(a[2]);
                        int i = 0;
                        T* it;
                        for (it = myList.GetFirst();
                                it != 0;
                                it = myList.GetNext()) {

                            VBAssert(*it == a[i++]);

                        }

                        // copy constructor
                        VBList<T> myList2 = myList;
                        myList2.remove(a[1]);
                        it = myList2.GetFirst();
                        VBAssert(*it == a[0]);
                        it = myList2.GetNext();
                        VBAssert(*it == a[2]); // a[1] was removed

                        myList.deleteAll();
                        VBAssert(myList.GetFirst()==0);
                        

                    }


                }; // end of template <class T>

            }
        }
    }
} // close namespace ::br::com::sbVB::VBLib
