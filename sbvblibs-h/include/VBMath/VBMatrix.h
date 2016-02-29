// VBMatrix.h

// #include "VBMath/VBMathException.h"

namespace br {
    namespace com {
        namespace sbVB {
            namespace VBMath {

                template <typename T>
                class VBMatrix {
                    T *m_data;
                    unsigned m_rows; // number of m_rows.
                    unsigned m_cols; // number of columns.

                    void privateConstructor() {
                        m_data = NULL;
                        m_cols = m_rows = 0;
                    };

                public:

                    static void error(const char *msg) {
                        throw VBMathException(msg);
                    };

                    // constructor & destructor

                    VBMatrix() {
                        privateConstructor();
                    }; // default contructor
                    VBMatrix(unsigned rows, unsigned cols = 1);
                    VBMatrix(unsigned rows, unsigned cols, T initval);
                    VBMatrix(const VBMatrix<T> & x); // copy constructor
                    ~VBMatrix();

                    // it is better not to have return value for operator=(VBMatrix<T> & x)
                    // VBMatrix<T> operator=(VBMatrix<T> & x);
                    void operator=(const VBMatrix<T> & x);

                    // basic matrix functions

                    unsigned getRows() const {
                        return m_rows;
                    }; // m_rows of matrix

                    unsigned getCols() const {
                        return m_cols;
                    }; // columns of matrix

                    bool isempty() {
                        return !(m_rows * m_cols);
                    };

                    bool issquare() {
                        return (m_rows == m_cols);
                    };
                    void redim(unsigned m_rows, unsigned m_cols = 1);
                    void kill();
                    void deleteMatrix();

                    // functions that return lvalue
                    T & operator=(T & value_in);
                    T & val(unsigned row, unsigned col);
                    T & ValWithRangeCheck(unsigned row, unsigned col);

                    // the 2 methods below are overloaded for VBMatrixRC (range check)

                    T & operator()(unsigned r, unsigned c) {
                        return val(r, c);
                    };

                    T & operator[](unsigned e) {
                        return val(e, 0);
                    };

                    // functions that return const lvalue
                    const T & const_val(unsigned r, unsigned c) const;
                    // const T & const_val(unsigned r, unsigned c) const { static T ret; return ret;}; // dummy delete me


                    // friends for matrix operations
                    // friend VBMatrix<T> radd  (const VBMatrix<T> & mat, T reval);
                    // friend VBMatrix<T> rmult (const VBMatrix<T> & mat, T reval);
                    // friend VBMatrix<T> rmult (T reval, const VBMatrix<T> & mat);
                    // friend VBMatrix<T> madd  (const VBMatrix<T> & arg1, const VBMatrix<T>& arg2);
                    // friend VBMatrix<T> mmult (const VBMatrix<T> & arg1, const VBMatrix<T> & arg2);

                    // matrix unary operators begin
                    VBMatrix<T> operator+();
                    VBMatrix<T> operator-();
                    // matrix unary operators end

                    // basic matrix operations with matrices begin
                    VBMatrix<T> operator+(const VBMatrix<T> & arg) const;
                    VBMatrix<T> operator-(const VBMatrix<T> & arg) const;
                    VBMatrix<T> operator*(const VBMatrix<T> & arg) const;
                    VBMatrix<T> operator/(const VBMatrix<T> & arg) const;
                    VBMatrix<T> operator%(const VBMatrix<T> & arg) const;
                    void operator+=(const VBMatrix<T> &mat);
                    void operator-=(const VBMatrix<T> &mat);
                    void operator*=(const VBMatrix<T> &mat);
                    void operator/=(const VBMatrix<T> &mat);
                    void operator%=(const VBMatrix<T> &mat);

                    void operator+=(T re);
                    void operator-=(T re);
                    void operator*=(T re);
                    void operator/=(T re);
                    // basic matrix operations with matrices end

                    void switch_columns(int col1, int col2);
                    void switch_rows(int row1, int row2);
                    VBMatrix<T> copymat(VBMatrix<T> & x);

                    // matrix relational operators WRONG !
                    // friend VBMatrix<T> operator==(const VBMatrix<T> & ,const VBMatrix<T> & );
                    // friend VBMatrix<T> operator!=(const VBMatrix<T> & ,const VBMatrix<T> & );

                    // advanced matrix functions
                    VBMatrix<T> pinv(); // pseudo inverse of matrix (a'*a)^-1*a'
                    VBMatrix<T> transpose(); // transpose of matrix
                    VBMatrix<T> inv(); // inverse of matrix
                    void copy_column(VBMatrix<T> & mm, unsigned from_col, unsigned to_col);
                    VBMatrix<T> lu_decompose(VBMatrix<T> & indx, unsigned & d);
                    void lu_back_subst(VBMatrix<T> & indx, VBMatrix<T> & b);
                    VBMatrix<T> eye();
                    VBMatrix<T> scale();

                    static void test();
                };


                /////////////////////////////////////////////////////////////////////////////


                // --------------

                template <typename T>
                std::ostream & operator<<(std::ostream & stream, const VBMatrix<T> & obj) {
                    using namespace std;
                    unsigned i, j;
                    stream << "(" << obj.getRows() << "," << obj.getCols() << ")" << endl;
                    for (i = 0; i < obj.getRows(); i++) {
                        for (j = 0; j < obj.getCols(); j++) {
                            stream.precision(4); // 4 decimals
                            //			stream.width(5);
                            stream.setf(ios::showpos);
                            stream.setf(ios::internal);
                            stream.setf(ios::fixed);
                            //			stream.setf(ios::scientific);
                            //			stream.setf(ios::right);
                            //			stream.fill(' ');
                            //			stream.precision(4);
                            stream << obj.const_val(i, j) << " ";
                        }
                        if (i != obj.getRows() - 1) // do not place an endl in the last row
                            stream << endl;
                    }
                    stream.unsetf(ios::showpos);
                    stream.unsetf(ios::internal);
                    stream.unsetf(ios::fixed);
                    return stream;
                };

                // --------------

                template <typename T>
                std::istream & operator>>(std::istream & stream, VBMatrix<T> & obj) {
                    unsigned i, j;
                    for (i = 0; i < obj.m_rows; i++)
                        for (j = 0; j < obj.m_cols; j++)
                            stream >> obj(i, j);
                    return stream;
                };

                // --------------
                // copy from "from_col" of mm to "to_col" of this

                template <typename T>
                void VBMatrix<T>::copy_column(VBMatrix & mm, unsigned from_col, unsigned to_col) {
                    unsigned i;

                    if (m_rows != mm.m_rows)
                        error("copy_column can only be executed if number of m_rows are the same");
                    //  error (20);
                    for (i = 0; i < m_rows; i++)
                        (*this)(i, to_col) = mm(i, from_col);
                };


                // --------------
                // matrix inverse

                template <typename T>
                VBMatrix<T> VBMatrix<T>::inv() {
                    unsigned i, d;
                    if (m_rows != m_cols)
                        error("Inverse can only be calculated for square matrices");

                    VBMatrix<T> Y(m_rows, m_cols);
                    Y.eye(); // Y becomes identity matrix
                    VBMatrix<T> indx(m_cols); // index vector
                    VBMatrix<T> B(m_cols); // see page 38 of numerical recipes.

                    VBMatrix<T> decomp = lu_decompose(indx, d); // execute lu_decomposicao once

                    for (i = 0; i < m_cols; i++) {
                        B.copy_column(Y, i, 0);
                        decomp.lu_back_subst(indx, B);
                        Y.copy_column(B, 0, i);
                    }
                    return Y;
                };

                // --------------
                // matrix transpose

                template <typename T>
                VBMatrix<T> VBMatrix<T>::transpose() {
                    VBMatrix<T> ret(m_cols, m_rows); // return matrix

                    for (unsigned int i = 0; i < m_rows; i++)
                        for (unsigned int j = 0; j < m_cols; j++)
                            ret(j, i) = (*this)(i, j);

                    return ret;
                };

                // --------------
                // matrix pseudo inverse

                template <typename T>
                VBMatrix<T> VBMatrix<T>::pinv() {
                    VBMatrix<T> ret; // return matrix
                    VBMatrix<T> trans = (*this).transpose();

                    ret = ((trans * (*this)).inv()) * trans;

                    return ret;
                };

                // --------------
                //
                // Retorna a decomposicao L-U de uma matriz. indx e um vetor de saida
                // que grava a permutacao da linha afetada pela rotacao parcial, d e saida
                // como +-1 dependendo se o numero de intermudancas da linha era impar
                // ou par, respectivamente. Essa rotina e usada em combinacao com
                // lu_back_subst () para resolver equacoes lineares ou inverter a matriz.
                //

                template <typename T>
                VBMatrix<T> VBMatrix<T>::lu_decompose(VBMatrix<T> & indx, unsigned & d) {

                    if (m_rows != m_cols)
                        error("LU decompose can only be calculated for square matrices");

                    VBMatrix<T> AA = +(*this);
                    VBMatrix<T> vv(m_rows);

                    unsigned i, imax, j, k;
                    T big, dum, sum, temp;
                    d = 1;

                    for (i = 0; i < m_cols; i++) {
                        big = 0.0;
                        for (j = 0; j < m_rows; j++)
                            // if ((temp=fabs(AA(i,j))) > big)
                            // temp = genAbs(AA(i, j));
                            temp = VBNumTrait<T>::abs(AA(i, j));
                        
                        // if (genGT(temp, big)) // if (temp > big)
                        if (VBNumTrait<T>::gt(temp, big)) // if (temp > big)                            
                            big = temp;
                        if (big == T(0.0))
                            error("error while calculating LU decompose");
                        vv(i, 0) = T(1.0) / big;
                    }

                    for (j = 0; j < m_rows; j++) {
                        for (i = 0; i < j; i++) {
                            sum = AA(i, j);
                            for (k = 0; k < i; k++) ////?????
                                sum -= AA(i, k) * AA(k, j);
                            AA(i, j) = sum;
                        }
                        big = 0.0;
                        for (i = j; i < m_rows; i++) {
                            sum = AA(i, j);
                            for (k = 0; k < j; k++) ///////????????
                                sum -= AA(i, k) * AA(k, j);
                            AA(i, j) = sum;
                            // if ((dum=vv(i,0)*genAbs(sum)) >= big) {
                            if (genAsBool(dum = genGE(vv(i, 0) * genAbs(sum), big))) {
                                big = dum;
                                imax = i;
                            }
                        }
                        if (j != imax) {
                            for (k = 0; k < m_rows; k++) {
                                dum = AA(imax, k);
                                AA(imax, k) = AA(j, k);
                                AA(j, k) = dum;
                            }
                            d *= -1;
                            vv(imax, 0) = vv(j, 0);
                        }
                        indx(j, 0) = imax;
                        //           if (AA(j,j) == 0.0) AA(j,j)=TINY;
                        if (AA(j, j) == T(0.0))
                            error("error while calculating LU decompose");
                        //		   error (22);
                        if (j != m_cols) {
                            dum = T(1.0) / (AA(j, j));
                            for (i = j + 1; i < m_rows; i++) AA(i, j) *= dum;
                        }
                    }
                    return AA;
                }


                // --------------
                //
                // Resolve o conjunto das equacoes lineares N A * X = B. Aqui "This" e
                // a decomposicao L-U da matriz A, determinada pela rotina lu_decompose().
                // indx e a saida como o vetor de permutacoes retornadop por lu_decompose().
                // b e saida como vetor do lado direito B e retorna como a solucao vetor X.
                // Essa rotina leva em conta a possibilidade de que B iniciar� com muitos
                // elementos zeros, assim, e eficiente para uso na inversao da matriz.
                // Veja Numerical Recipes pg 36-37.
                //

                template <typename T>
                void VBMatrix<T>::lu_back_subst(VBMatrix<T> & indx, VBMatrix<T> & b) {

                    //  if (!issquare())
                    //      error (19); 
                    //	error("Matrix must be square for lu_back_subst function");

                    //  if (m_rows != indx.m_rows)
                    //      error (23);
                    //  if (m_rows != b.m_rows)
                    //     error (24);

                    unsigned i, j, ip;
                    unsigned ii = 0;
                    T sum;

                    for (i = 0; i < m_rows; i++) {
                        ip = genConvToUnsigned(indx(i, 0));
                        sum = b(ip, 0);
                        b(ip, 0) = b(i, 0);
                        if (ii >= 0) {
                            for (j = ii; j < i; j++)
                                sum -= (*this)(i, j) * b(j, 0);
                        } else {
                            if (sum == T(0))
                                ii = i;
                        }
                        b(i, 0) = sum;
                    }
                    unsigned i2;
                    for (i2 = m_rows; i2 > 0; i2--) {
                        i = i2 - 1;
                        sum = b(i, 0);
                        for (j = i + 1; j < m_cols; j++)
                            sum -= (*this)(i, j) * b(j, 0);
                        b(i, 0) = sum / (*this)(i, i);
                    }
                };


                // --------------

                template <typename T>
                VBMatrix<T> VBMatrix<T>::eye() {
                    unsigned i, j;

                    if (m_rows != m_cols)
                        error("Identity matrix must be square");

                    for (i = 0; i < m_rows; i++)
                        for (j = 0; j < m_cols; j++) {
                            (*this) (i, j) = 0;
                            if (i == j)
                                (*this) (i, j) = 1;
                        }
                    return (*this);
                };


                // --------------
                // constructor

                template <typename T>
                VBMatrix<T>::VBMatrix(unsigned r, unsigned c) {
                    m_data = NULL;
                    redim(r, c); // alloc memory for matrix
                };

                // --------------
                // constructor

                template <typename T>
                VBMatrix<T>::VBMatrix(unsigned m_rows, unsigned m_cols, T initval) {
                    int i, j;
                    redim(m_rows, m_cols); // alloc memory for matrix
                    for (i = 0; i < m_rows; i++)
                        for (j = 0; j < m_cols; j++)
                            (*this) (i, j) = initval;
                };

                // --------------
                // copy constructor

                template <typename T>
                VBMatrix<T>::VBMatrix(const VBMatrix<T> & x) {
                    privateConstructor();
                    if (!m_data || m_rows != x.m_rows || m_cols != x.m_cols)
                        // if (*this) was never alloced or dinensions are different
                        this->redim(x.m_rows, x.m_cols); // alloc memory for copy
                    unsigned i, j;
                    for (i = 0; i < m_rows; i++)
                        for (j = 0; j < m_cols; j++)
                            (*this)(i, j) = x.const_val(i, j);
                };

                // --------------

                template <typename T>
                        void VBMatrix<T>::operator=(const VBMatrix<T> & x) {
                    if (!m_data || m_rows != x.m_rows || m_cols != x.m_cols)
                        // if (*this) was never alloced or dinensions are different
                        (*this).redim(x.m_rows, x.m_cols); // alloc memory for copy
                    unsigned i, j;
                    for (i = 0; i < m_rows; i++)
                        for (j = 0; j < m_cols; j++)
                            (*this)(i, j) = x.const_val(i, j);
                    //	return(*this); // no return
                };




                // --------------

                template <typename T>
                void VBMatrix<T>::redim(unsigned r, unsigned c) {
                    m_rows = r;
                    m_cols = c;
                    unsigned els = m_rows*m_cols;
                    if (els > 0) {

                        if (m_data)
                            delete [] m_data;

                        if ((m_data = new T [els]) == NULL) {
                            throw VBMathException("couldn't alloc memory");
                        }

                        // fill with zeros
                        for (unsigned i = 0; i < els; i++)
                            m_data[i] = 0;

                    } else {
                        m_rows = m_cols = 0; // empty matrix
                        if (m_data) {
                            deleteMatrix();
                        }
                    }
                };

                // --------------

                template <typename T>
                VBMatrix<T>::~VBMatrix() {
                    deleteMatrix();
                };

                // --------------

                template <typename T>
                void VBMatrix<T>::deleteMatrix() {
                    if (m_data) {
                        delete [] m_data;
                        m_data = 0;
                    }
                };



                // --------------

                template <typename T>
                T & VBMatrix<T>::ValWithRangeCheck(unsigned row, unsigned col) {
                    // if (row < 0 || row >= getRows() || col < 0 || col >= getCols())
                    // now, with the type as unsigned, to test row < 0 and col < 0 is not necessary

                    // generic error handler
                    //if (row >= getRows() || col >= getCols())
                    //	error("Range check error");

                    // more specific error handler
                    br::com::sbVB::VBLib::VBString err = "Range check error";
                    if (row >= getRows()) {
                        err += ", row = ";
                        err += (int) row;
                        err += ", should be less than ";
                        err += (int) getRows();
                        error(err);
                    }

                    if (col >= getCols()) {
                        err += ", col = ";
                        err += (int) col;
                        err += ", should be less than ";
                        err += (int) getCols();
                        error(err);
                    }

                    // all ok, just return the value
                    return (val(row, col));
                };

                // --------------

                template <typename T>
                        T & VBMatrix<T>::operator=(T & value_in) {
                    unsigned i, j;
                    for (i = 0; i < m_rows; i++)
                        for (j = 0; j < m_cols; j++)
                            (*this)(i, j) = value_in;
                    return value_in;
                };

                // --------------
                // Matrix in FORTRAN style. Store by columns.

                template <typename T>
                T & VBMatrix<T>::val(unsigned r, unsigned c) {
                    return (m_data[r + m_rows * c]);
                };

                // --------------
                // Matrix in FORTRAN style. Store by columns.

                template <typename T>
                const T & VBMatrix<T>::const_val(unsigned r, unsigned c) const {
                    return (m_data[r + m_rows * c]);
                };

                // --------------
                // switch (*this).col1 to (*this).col2

                template <typename T>
                void VBMatrix<T>::switch_columns(int col1, int col2) {
                    unsigned i;
                    VBMatrix<T> temp(1, m_rows);
                    for (i = 0; i < m_rows; i++)
                        temp(0, i) = (*this)(i, col1);
                    for (i = 0; i < m_rows; i++)
                        (*this)(i, col1) = (*this)(i, col2);
                    for (i = 0; i < m_rows; i++)
                        (*this)(i, col2) = temp(0, i);
                };

                // --------------
                // switch (*this).row1 to (*this).row2

                template <typename T>
                void VBMatrix<T>::switch_rows(int row1, int row2) {
                    unsigned i;
                    VBMatrix<T> temp(1, m_cols);
                    for (i = 0; i < m_cols; i++)
                        temp(0, i) = (*this)(i, row1);
                    for (i = 0; i < m_cols; i++)
                        (*this)(i, row1) = (*this)(i, row2);
                    for (i = 0; i < m_cols; i++)
                        (*this)(i, row2) = temp(0, i);
                };


                // --------------

                template <typename T>
                VBMatrix<T> VBMatrix<T>::scale() {
                    T temp, maximum;
                    unsigned i, j;
                    if (!issquare())
                        error("Matrix must be square");

                    VBMatrix<T> scale_vector(m_rows);

                    for (i = 0; i < m_rows; i++) {
                        maximum = 0.0;
                        for (j = 0; j < m_cols; j++) {
                            if ((temp = (T) fabs((*this)(i, j))) > maximum)
                                maximum = temp;
                        }
                        if (maximum == 0.0)
                            error("singular matrix");
                        scale_vector(i, 0) = 1. / maximum; // save scaling
                    }
                    return scale_vector;
                };

                // global functions auxiliary to VBMatrix begin

                // --------------

                template <typename T>
                VBMatrix<T> madd(const VBMatrix<T> & arg1, const VBMatrix<T>& arg2) {
                    unsigned i, j, nc, nr;
                    nc = arg2.m_cols;
                    nr = arg2.m_rows;

                    if ((arg1.m_rows != nr) || (arg1.m_cols != nc))
                        VBMatrix<T>::error("Dimensions must be the same to perform matrix add");

                    VBMatrix<T> sum(nr, nc);
                    for (i = 0; i < nr; i++)
                        for (j = 0; j < nc; j++)
                            sum(i, j) = arg1(i, j) + arg2(i, j);
                    return sum;
                }


                // --------------

                template <typename T>
                VBMatrix<T> mmult(const VBMatrix<T> & arg1, const VBMatrix<T> & arg2) {
                    unsigned k, j, i;
                    unsigned a1c = arg1.getCols();
                    unsigned a1r = arg1.getRows();
                    unsigned a2c = arg2.getCols();

                    T sum;

                    if (a1c != arg2.getRows())
                        VBMatrix<T>::error("arg1.m_cols must be equal to arg2.m_rows to perform matrix multiplication");

                    VBMatrix<T> result(a1r, a2c);

                    for (i = 0; i < a1r; ++i) {
                        for (j = 0; j < a2c; ++j) {
                            sum = 0;
                            for (k = 0; k < a1c; k++) {
                                sum += arg1.const_val(i, k) * arg2.const_val(k, j);
                            } // for k
                            result(i, j) = sum;
                        } // for j
                    } // for i
                    return result;
                };


                // --------------

                template <typename T>
                VBMatrix<T> rmult(const VBMatrix<T> & mat, T reval) {
                    unsigned i, j, nc, nr;
                    nr = mat.getRows();
                    nc = mat.getCols();
                    VBMatrix<T> multi(nr, nc);
                    for (i = 0; i < nr; i++)
                        for (j = 0; j < nc; j++)
                            multi(i, j) = mat.const_val(i, j) * reval;
                    return multi;
                };


                // --------------

                template <typename T>
                VBMatrix<T> rmult(T reval, const VBMatrix<T> & mat) {
                    return rmult(mat, reval);
                };

                // --------------

                template <typename T>
                VBMatrix<T> radd(const VBMatrix<T> & mat, T reval) {
                    unsigned i, j, nc, nr;
                    nr = mat.m_rows;
                    nc = mat.m_cols;
                    VBMatrix<T> multi(nr, nc);
                    for (i = 0; i < nr; i++)
                        for (j = 0; j < nc; j++)
                            multi(i, j) = mat.const_val(i, j) + reval;
                    return multi;
                };

                // global functions auxiliary to VBMatrix end


                // --------------

                template <typename T>
                VBMatrix<T> VBMatrix<T>::copymat(VBMatrix<T> & x) {
                    unsigned i, j;
                    for (i = 0; i < m_rows; i++)
                        for (j = 0; j < m_cols; j++)
                            (*this)(i, j) = x(i, j);
                    return (*this);
                };





                // after madd, mmult, etc
                // basic matrix operations with matrices begin

                template <typename T>
                VBMatrix<T> VBMatrix<T>::operator+(const VBMatrix<T> & arg) const {
                    return madd<T > ((*this), arg);
                };

                template <typename T>
                VBMatrix<T> VBMatrix<T>::operator-(const VBMatrix<T> & arg) const {
                    return madd<T > ((*this), -arg);
                };

                template <typename T>
                VBMatrix<T> VBMatrix<T>::operator*(const VBMatrix<T> & arg) const {
                    return mmult<T > ((*this), arg);
                };

                template <typename T>
                VBMatrix<T> VBMatrix<T>::operator/(const VBMatrix<T> & arg) const {
                    return mmult<T > ((*this), arg.inv());
                };

                template <typename T>
                VBMatrix<T> VBMatrix<T>::operator%(const VBMatrix<T> & arg) const {
                    return mmult<T > ((*this).inv(), arg);
                };

                template <typename T>
                        void VBMatrix<T>::operator+=(const VBMatrix<T> &mat) {
                    mincr(mat);
                };

                template <typename T>
                        void VBMatrix<T>::operator-=(const VBMatrix<T> &mat) {
                    mdecr(mat);
                };

                template <typename T>
                        void VBMatrix<T>::operator*=(const VBMatrix<T> &mat) {
                    (*this) = mmult<T > ((*this), mat);
                };

                template <typename T>
                        void VBMatrix<T>::operator/=(const VBMatrix<T> &mat) {
                    (*this) = mmult<T > ((*this), mat.inv());
                };

                template <typename T>
                        void VBMatrix<T>::operator%=(const VBMatrix<T> &mat) {
                    (*this) = mmult<T > ((*this).inv(), mat);
                };

                template <typename T>
                        void VBMatrix<T>::operator+=(T re) {
                    ((*this) = radd<T > (*this, re));
                };

                template <typename T>
                        void VBMatrix<T>::operator-=(T re) {
                    ((*this) = radd<T > (*this, -re));
                };

                template <typename T>
                        void VBMatrix<T>::operator*=(T re) {
                    ((*this) = rmult<T > (*this, re));
                };

                template <typename T>
                        void VBMatrix<T>::operator/=(T re) {
                    ((*this) = rmult<T > (*this, 1. / re));
                };
                // basic matrix operations with matrices end

                // matrix unary operators begin

                template <typename T>
                VBMatrix<T> VBMatrix<T>::operator+() {
                    return rmult<T > (*this, (T) 1.0);
                };

                template <typename T>
                VBMatrix<T> VBMatrix<T>::operator-() {
                    return rmult<T > (*this, (T) - 1.0);
                };
                // matrix unary operators end


                // global functions basic matrix operations begin
                // operation M + r = M + r * ones(M)

                template <typename T>
                VBMatrix<T> operator+(const VBMatrix<T> & mat, T re) {
                    return radd<T > (mat, re);
                };

                template <typename T>
                VBMatrix<T> operator+(T re, const VBMatrix<T> & mat) {
                    return radd<T > (mat, re);
                };

                template <typename T>
                VBMatrix<T> operator-(const VBMatrix<T> & mat, T re) {
                    return radd<T > (mat, -re);
                };

                template <typename T>
                VBMatrix<T> operator-(T re, const VBMatrix<T> & mat) {
                    return radd<T > (-mat, re);
                };

                template <typename T>
                VBMatrix<T> operator*(const VBMatrix<T> & mat, T re) {
                    return rmult<T > (mat, re);
                };

                template <typename T>
                VBMatrix<T> operator*(T re, const VBMatrix<T> & mat) {
                    return rmult<T > (mat, re);
                };

                template <typename T>
                VBMatrix<T> operator/(const VBMatrix<T> & mat, T re) {
                    return rmult<T > (mat, 1. / re);
                };

                template <typename T>
                VBMatrix<T> operator/(T re, const VBMatrix<T> & mat) {
                    return rmult<T > (mat.inv(), re);
                };
                // global functions basic matrix operations end



                ////////////////////////////////////////////////////////////////////
                // Definition of types based on generic class VBMatrix
                /////////////////////////////////////////////////////////////////////

                typedef VBMatrix<float> VBMatrix_F;
                typedef VBMatrix<double> VBMatrix_D;
                typedef VBMatrix<long double> VBMatrix_LD;

                typedef VBMatrix< std::complex<float> > VBMatrix_CF;
                typedef VBMatrix< std::complex<double> > VBMatrix_CD;
                typedef VBMatrix< std::complex<long double> > VBMatrix_CLD;


                ////////////////////////////////////////////////////////////////////
                //
                // VBMatrixRC - With Range Check
                //
                /////////////////////////////////////////////////////////////////////

                template <typename T>
                class VBMatrixRC : public VBMatrix<T> {
                public:

                    T & operator()(unsigned r, unsigned c) {
                        return VBMatrix<T>::ValWithRangeCheck(r, c);
                    };

                    T & operator[](unsigned e) {
                        return VBMatrix<T>::ValWithRangeCheck(e, 0);
                    };
                };


                ////////////////////////////////////////////////////////////////////
                // Definition of types based on generic class VBMatrixRC
                /////////////////////////////////////////////////////////////////////

                typedef VBMatrixRC<float> VBMatrixRC_F;
                typedef VBMatrixRC<double> VBMatrixRC_D;
                typedef VBMatrixRC<long double> VBMatrixRC_LD;

                typedef VBMatrixRC< std::complex<float> > VBMatrixRC_CF;
                typedef VBMatrixRC< std::complex<double> > VBMatrixRC_CD;
                typedef VBMatrixRC< std::complex<long double> > VBMatrixRC_CLD;



                // return true if every element of myMatrix is near to answer

                template <typename T>
                bool nearEqualMatrix(VBMatrix<T> & myMatrix, VBMatrix<T> & answer, double eps) {
                    if ((myMatrix.getRows() != answer.getRows()) || (myMatrix.getCols() != answer.getCols()))
                        throw VBMathException("incompatible dimensions in nearEqualMatrix");
                    unsigned i, j;
                    for (i = 0; i < myMatrix.getRows(); i++) {
                        for (j = 0; j < myMatrix.getCols(); j++) {
                            if (!genNearEqual(myMatrix(i, j), answer(i, j), eps))
                                return false;
                        }
                    }
                    return true;
                };


                ////////////////////////////////////////////////////////////////////
                // VBMatrix related global functions
                /////////////////////////////////////////////////////////////////////

                /*
                % [A]=vb_lsmat(t,g)
                %
                % Polinomial Regression Matrix.
                %
                % for a pair of vectors y and t,
                % creates matrix A to compute coeficients k of polinomial of g order
                % y= xg*t^g + ... + x2*t^2 + x1*t + x0
                % where k=pinv(A)*y
                %
                % A = [t1^g ... t1^2 t1 1 
                %         ...
                %      tn^g ... tn^2 t1 1]
                %
                % n = length(t);
                % x = [xg; ... ; x1; x0]

                 */


                template <typename T>
                VBMatrix<T> polinomialRegressionMatrix(VBMatrix<T> & t, unsigned g) {
                    VBMatrix<T> ret(t.getRows(), g);
                    unsigned i, j;
                    for (i = 0; i < ret.getRows(); i++)
                        for (j = 0; j < ret.getCols(); j++) {
                            T element = t(i, 0);
                            ret(i, ret.getCols() - j - 1) = pow((double) element, (double) (g - j - 1));
                        }
                    return ret;
                };

                /////////////////// tests

                template <typename T>
                void testCheckAMatrix() {
                    using namespace std;
                    using namespace br::com::sbVB::VBLib;
                    cout << "= testCheckAMatrix" << endl;
                    /*=============================================
                    a =
                    1	2
                    3	4
                            =============================================*/
                    VBMatrix<T> myMatrix(2, 2);
                    myMatrix(0, 0) = 1;
                    myMatrix(0, 1) = 2;
                    myMatrix(1, 0) = 3;
                    myMatrix(1, 1) = 4;
                    // cout << "DEBUG:" << endl << myMatrix << endl;

                    VBMatrix<T> expectedAnswer(2, 2);
                    expectedAnswer(0, 0) = 1;
                    expectedAnswer(0, 1) = 2;
                    expectedAnswer(1, 0) = 3;
                    expectedAnswer(1, 1) = 4;

                    double eps = 1e-8;
                    VBAssert(nearEqualMatrix(myMatrix, expectedAnswer, eps), "matrices are different");
                };

                template <typename T>
                void test_rmult() {
                    using namespace std;
                    using namespace br::com::sbVB::VBLib;
                    cout << "= test_rmult" << endl;
                    VBMatrix<T> oneMatrix(2, 2);
                    oneMatrix(0, 0) = 1;
                    oneMatrix(0, 1) = 2;
                    oneMatrix(1, 0) = -1;
                    oneMatrix(1, 1) = 2;

                    // each element is muitiplied by 1.1;
                    VBMatrix<T> myAnswer = rmult<T > (oneMatrix, 1.1);

                    VBMatrix<T> expectedAnswer(2, 2);
                    expectedAnswer(0, 0) = 1.1;
                    expectedAnswer(0, 1) = 2.2;
                    expectedAnswer(1, 0) = -1.1;
                    expectedAnswer(1, 1) = 2.2;

                    double eps = 1e-8;
                    VBAssert(nearEqualMatrix(myAnswer, expectedAnswer, eps), "matrices are different");
                };

                template <typename T>
                void testInvertMatrix() {
                    using namespace std;
                    using namespace br::com::sbVB::VBLib;
                    cout << "= testInvertMatrix" << endl;
                    /*=============================================
                    a = [
                    1	2
                    -1	2
                    ]
                    inv(a)
                    ans =
                    0.5		-0.5
                    0.25	0.25
                            =============================================*/
                    VBMatrix<T> myMatrix(2, 2);
                    myMatrix(0, 0) = 1;
                    myMatrix(0, 1) = 2;
                    myMatrix(1, 0) = -1;
                    myMatrix(1, 1) = 2;
                    // cout << "DEBUG: myMatrix=" << myMatrix << endl;

                    VBMatrix<T> myAnswer = myMatrix.inv();
                    // cout << "DEBUG:" << endl << invMat << endl;
                    // a = b*c+d*e;

                    VBMatrix<T> expectedAnswer(2, 2);
                    expectedAnswer(0, 0) = 0.5;
                    expectedAnswer(0, 1) = -0.5;
                    expectedAnswer(1, 0) = 0.25;
                    expectedAnswer(1, 1) = 0.25;

                    double eps = 1e-8;
                    VBAssert(nearEqualMatrix(myAnswer, expectedAnswer, eps), "matrice inverse error");
                };

                template <typename T>
                void testRegression() {
                    using namespace std;
                    using namespace br::com::sbVB::VBLib;
                    cout << "= testRegression" << endl;
                    // y=[1 3 4 7 9 0.1];
                    VBMatrix<T> y(6, 1);
                    y(0, 0) = 1;
                    y(1, 0) = 3;
                    y(2, 0) = 4;
                    y(3, 0) = 7;
                    y(4, 0) = 9;
                    y(5, 0) = 0.1;
                    // cout << "DEBUG y=" << y << endl;

                    // x=[2 3 5 9 10 0.3];
                    VBMatrix<T> x(6, 1);
                    x(0, 0) = 2;
                    x(1, 0) = 3;
                    x(2, 0) = 5;
                    x(3, 0) = 9;
                    x(4, 0) = 10;
                    x(5, 0) = 0.3;
                    // cout << "DEBUG x=" << x << endl;

                    unsigned g = 2;
                    VBMatrix<T> A = polinomialRegressionMatrix(x, 2);
                    // cout << "DEBUG A=" << A << endl;
                    // cout << "pinv A=" << A.pinv() << endl;
                    // cout << "y=" << y << endl;

                    VBMatrix<T> myAnswer = A.pinv() * y;
                    // cout << "DEBUG a=" << a << endl;

                    VBMatrix<T> expectedAnswer(g, 1);
                    expectedAnswer(0, 0) = -0.24560903409714;
                    expectedAnswer(1, 0) = 0.87282096261375;
                    // cout << "DEBUG expectedAnswer=" << expectedAnswer << endl;

                    double eps = 1e-8;
                    if (typeid (T) == typeid (float))
                        eps = 1e-5;
                    VBAssert(nearEqualMatrix(myAnswer, expectedAnswer, eps), "matrices are different");
                };

                template <typename T>
                void testGenericComplex() {
                    using namespace std;
                    using namespace br::com::sbVB::VBLib;
                    cout << "= testGenericComplex" << endl;
                    std::complex<T> a(1.0, 1.0), b(2.0, -2.0);
                    // b > a => gt(b,a)
                    
                    
                    VBAssert(VBNumTrait<std::complex<T> >::gt(b, a));
                    VBAssert(VBNumTrait<std::complex<T> >::ge(b, a));
                    VBAssert(VBNumTrait<std::complex<T> >::ge(a, a));
                    VBAssert(VBNumTrait<std::complex<T> >::ge(b, b));

//                    VBAssert(genGT(b, a));
//                    VBAssert(genGE(b, a));
//                    VBAssert(genGE(a, a));
//                    VBAssert(genGE(b, b));
                };

                template <typename T>
                void testInvertComplexMatrix() {
                    using namespace std;
                    using namespace br::com::sbVB::VBLib;
                    cout << "= testInvertComplexMatrix" << endl;
                    /*=============================================
                    format long
                    a = [ (1+3j) (2+5j) ;
                    (5-2j)  (-1+4j)]
                    inv(a)
                    ans =
                    -0.03156480859637 - 0.10208193418402i  0.11148421759570 + 0.08394895903291i
                    0.08394895903291 - 0.11148421759570i -0.06245802552048 - 0.05305574210880i
                            =============================================*/

                    VBMatrix< complex<T> > myMatrix(2, 2);
                    myMatrix(0, 0) = complex<T>(1, 3);
                    myMatrix(0, 1) = complex<T>(2, 5);
                    myMatrix(1, 0) = complex<T>(5, -2);
                    myMatrix(1, 1) = complex<T>(-1, 4);

                    VBMatrix< complex<T> > myAnswer = myMatrix.inv();
                    // cout << "DEBUG:" << endl << myAnswer << endl;

                    VBMatrix< complex<T> > expectedAnswer(2, 2);
                    expectedAnswer(0, 0) = complex<T>(-0.03156480859637, -0.10208193418402);
                    expectedAnswer(0, 1) = complex<T>(0.11148421759570, 0.08394895903291);
                    expectedAnswer(1, 0) = complex<T>(0.08394895903291, -0.11148421759570);
                    expectedAnswer(1, 1) = complex<T>(-0.06245802552048, -0.05305574210880);

                    double eps = 1e-8;
                    if (typeid (T) == typeid (float))
                        eps = 1e-5;
                    VBAssert(nearEqualMatrix(myAnswer, expectedAnswer, eps), "matrices are different 2x2");

                    /*=============================================
                    format long
                    a = [ (1+j) (-2+3j) (1-j);
                    (2-4j) (2-j) (-1+4j)
                    (3-3j) (-1-j) (2+j)];
                    inv(a)
                    ans =
	
                      Columns 1 through 2 
	  
                            -0.01040763226366 - 0.04293148308760i -0.05767562879445 + 0.07458803122290i
                            -0.08716392020815 - 0.29705117085863i -0.04553339115351 - 0.12532523850824i
                            0.09063313096271 - 0.18863833477884i -0.10190806591500 - 0.23287077189939i
		
                              Column 3 
		  
                                    0.18516912402428 + 0.07632263660017i
                                    -0.01170858629662 + 0.13920208152645i
                                    0.11665221162186 + 0.16869037294016i
                    =============================================*/
                    myMatrix.redim(3, 3);
                    myMatrix(0, 0) = complex<T>(1, 1);
                    myMatrix(0, 1) = complex<T>(-2, 3);
                    myMatrix(0, 2) = complex<T>(1, -1);

                    myMatrix(1, 0) = complex<T>(2, -4);
                    myMatrix(1, 1) = complex<T>(2, -1);
                    myMatrix(1, 2) = complex<T>(-1, 4);

                    myMatrix(2, 0) = complex<T>(3, -3);
                    myMatrix(2, 1) = complex<T>(-1, -1);
                    myMatrix(2, 2) = complex<T>(2, 1);

                    myAnswer = myMatrix.inv();
                    // cout << "DEBUG:" << endl << myAnswer << endl;

                    expectedAnswer.redim(3, 3);
                    expectedAnswer(0, 0) = complex<T>(-0.01040763226366, -0.04293148308760);
                    expectedAnswer(0, 1) = complex<T>(-0.05767562879445, 0.07458803122290);
                    expectedAnswer(0, 2) = complex<T>(0.18516912402428, 0.07632263660017);

                    expectedAnswer(1, 0) = complex<T>(-0.08716392020815, -0.29705117085863);
                    expectedAnswer(1, 1) = complex<T>(-0.04553339115351, -0.12532523850824);
                    expectedAnswer(1, 2) = complex<T>(-0.01170858629662, 0.13920208152645);

                    expectedAnswer(2, 0) = complex<T>(0.09063313096271, -0.18863833477884);
                    expectedAnswer(2, 1) = complex<T>(-0.10190806591500, -0.23287077189939);
                    expectedAnswer(2, 2) = complex<T>(0.11665221162186, 0.16869037294016);

                    VBAssert(nearEqualMatrix(myAnswer, expectedAnswer, eps), 
                            "matrices are different 3x3");
                };

                template <typename T>
                void VBMatrix<T>::test() {
                    T aux;
                    std::cout << "== VBMatrix<" << typeid (aux).name()
                            << ">::test()" << std::endl;

                    test_rmult<T > ();
                    testCheckAMatrix<T > ();
                    testInvertMatrix<T > ();
                    testRegression<T > ();
                    testGenericComplex<T > ();
                    testInvertComplexMatrix<T >();

                };

            }
        }
    }
} // close namespace ::br::com::sbVB::VBMath
