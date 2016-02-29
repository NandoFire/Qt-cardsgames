// VBNumTrait.h

namespace br {
    namespace com {
        namespace sbVB {
            namespace VBMath {

                typedef unsigned char byte;


                ////////////////////////////////////////////////////////////////////
                // generic absolute
                /////////////////////////////////////////////////////////////////////

                template <typename T>
                T complexAbs(const std::complex<T> & x) {
                    return sqrt(x.real() * x.real() + x.imag() * x.imag());
                };

                //double complexAbs(const std::complex<double> & x) {
                //	return sqrt(x.real()*x.real() + x.imag()*x.imag());
                //};

                ////////////////////////////////////////////////////////////////////
                // Num Trait interface
                /////////////////////////////////////////////////////////////////////

                template <typename T>
                struct VBNumTrait {

                    static bool asBool(const T & x) {
                        return (x != 0);
                    }

                    static T abs(const T & x) {
                        // default implementation (for float, double and long double)
                        return ::fabs(x);
                    }

                    static bool gt(const T & x, const T & y) {
                        return x > y;
                    }

                    static bool ge(const T & x, const T & y) {
                        return x >= y;
                    }

                    static unsigned convToUnsigned(const T & x) {
                        // default implementation (for float, double and long double)
                        return (unsigned) x;
                    }

                    static bool nearEqual(const T & x, const T & y, double eps) {
                        T absDiff = ::fabs(x - y);
                        return absDiff < eps;
                    }

                }; // end of VBNumTrait


                ////////////////////////////////////////////////////////////////////
                // Num Trait for complex<float>
                /////////////////////////////////////////////////////////////////////

                template <>
                struct VBNumTrait< std::complex<float> > {

                    static bool asBool(const std::complex<float> & x) {
                        return (x.real() != 0 || x.imag() != 0);
                    }

                    static std::complex<float> abs(const std::complex<float> & x) {
                        // implementation for fcomplex
                        float absolute = (float) complexAbs(x);
                        return std::complex<float>(absolute, 0);
                    }

                    static bool gt(const std::complex<float> & x,
                            const std::complex<float> & y) {
                        // implementation for fcomplex
                        return complexAbs(x) > complexAbs(y);
                    }

                    static bool ge(const std::complex<float> & x,
                            const std::complex<float> & y) {
                        // implementation for fcomplex
                        return complexAbs(x) >= complexAbs(y);
                    }

                    static unsigned convToUnsigned(const std::complex<float> & x) {
                        // implementation for dcomplex
                        return (unsigned) complexAbs(x);
                    }

                    static bool nearEqual(const std::complex<float> & x, const std::complex<float> & y,
                            float eps) {
                        float absDiff = fabs((float) complexAbs(x - y));
                        return absDiff < eps;
                    }

                };



                ////////////////////////////////////////////////////////////////////
                // Num Trait for complex<double>
                /////////////////////////////////////////////////////////////////////

                template <>
                struct VBNumTrait< std::complex<double> > {

                    static bool asBool(const std::complex<double> & x) {
                        return (x.real() != 0 || x.imag() != 0);
                    }

                    static std::complex<double> abs(const std::complex<double> & x) {
                        // implementation for dcomplex
                        double absolute = complexAbs(x);
                        return std::complex<double>(absolute, 0);
                    }

                    static bool gt(const std::complex<double> & x,
                            const std::complex<double> & y) {
                        // implementation for dcomplex
                        return complexAbs(x) > complexAbs(y);
                    }

                    static bool ge(const std::complex<double> & x,
                            const std::complex<double> & y) {
                        // implementation for dcomplex
                        return complexAbs(x) >= complexAbs(y);
                    }

                    static unsigned convToUnsigned(const std::complex<double> & x) {
                        // implementation for dcomplex
                        return (unsigned) complexAbs(x);
                    }

                    static bool nearEqual(const std::complex<double> & x, const std::complex<double> & y,
                            double eps = 1e-8) {
                        double absDiff = fabs(complexAbs(x - y));
                        return absDiff < eps;
                    }
                };



                ////////////////////////////////////////////////////////////////////
                // Num Trait for complex<long double>
                /////////////////////////////////////////////////////////////////////

                template <>
                struct VBNumTrait< std::complex<long double> > {

                    static bool asBool(const std::complex<long double> & x) {
                        return (x.real() != 0 || x.imag() != 0);
                    }

                    static std::complex<long double> abs(const std::complex<long double> & x) {
                        // implementation for dcomplex
                        long double absolute = complexAbs(x);
                        return std::complex<long double>(absolute, 0);
                    }

                    static bool gt(const std::complex<long double> & x,
                            const std::complex<long double> & y) {
                        // implementation for dcomplex
                        return complexAbs(x) > complexAbs(y);
                    }

                    static bool ge(const std::complex<long double> & x,
                            const std::complex<long double> & y) {
                        // implementation for dcomplex
                        return complexAbs(x) >= complexAbs(y);
                    }

                    static unsigned convToUnsigned(const std::complex<long double> & x) {
                        // implementation for dcomplex
                        return (unsigned) complexAbs(x);
                    }

                    static bool nearEqual(const std::complex<long double> & x,
                            const std::complex<long double> & y,
                            double eps = 1e-8) {
                        double absDiff = fabs(complexAbs(x - y));
                        return absDiff < eps;
                    }
                };



                // global functions for VBNumTrait

                template <typename T>
                bool operator>(std::complex<T> x, std::complex<T> y) {
                    return complexAbs(x) > complexAbs(y);
                }

                template <typename T>
                bool operator>=(std::complex<T> x, std::complex<T> y) {
                    return complexAbs(x) >= complexAbs(y);
                }

                template<typename T>
                T genAbs(const T & x) {
                    return VBNumTrait<T>::abs(x);
                };

                // GT = Greater than (>)

                template<typename T>
                bool genGT(const T & x, const T & y) {
                    return VBNumTrait<T>::gt(x, y);
                };

                // GE = Greater or Equal than (>=)

                template<typename T>
                bool genGE(const T & x, const T & y) {
                    return VBNumTrait<T>::ge(x, y);
                };

                // return true if not zero

                template<typename T>
                bool genAsBool(const T & x) {
                    return VBNumTrait<T>::asBool(x);
                };

                template<typename T>
                unsigned genConvToUnsigned(const T & x) {
                    return VBNumTrait<T>::convToUnsigned(x);
                };

                template<typename T>
                bool genNearEqual(const T & x, const T & y, double eps = 1e08) {
                    return VBNumTrait<T>::nearEqual(x, y, eps);
                };

            }
        }
    }
} // close namespace ::br::com::sbVB::VBMath
