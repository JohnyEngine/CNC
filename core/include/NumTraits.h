#ifndef __NUMTRAITS_H_
#define __NUMTRAITS_H_

template< typename T1, typename T2 >
class BinaryNumericTraits
{
public:
    typedef T1 OpResult;
};

template<>
class BinaryNumericTraits<int, double>
{
public:
    typedef double OpResult;
};

template<>
class BinaryNumericTraits<double, int>
{
public:
    typedef double OpResult;
};

#endif // __NUMTRAITS_H_
