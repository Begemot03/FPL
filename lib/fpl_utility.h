#pragma once

#include "fpl_extensions.h"

struct NullType {};

struct DeletedType {};

/* 


	Вспомогательные методы



*/


//TrueType - обертка над Bool type для result функций
struct TrueType {
	using result = Bool<1>;
};

using TrueType_R = TrueType::result;


//False - обертка над Bool type для result функций
struct FalseType {
	using result = Bool<0>;
};

using FalseType_R = FalseType::result;

// Select function value cond ? T : U
template<class cond, class T, class U>
struct Select {
	using result = T;
};

template<class T, class U>
struct Select<Bool<0>, T, U> {
	using result = U;
};

template<class cond, class T, class U>
using Select_R = Select<cond, T, U>::result;


// IsSame function T === U
template<class T, class U>
struct IsSame : public FalseType {};

template<class T>
struct IsSame<T, T> : public TrueType {};

template<class T, class U>
using IsSame_R = IsSame<T, U>::result;


//IsPtr - если текущее значение указатель то true иначе false
template<class T>
struct IsPrt : public FalseType {};
template<class T>
struct IsPrt<T *> : public TrueType {};

template<class T>
using IsPrt_R = IsPrt<T>::result;


//IsConst - если текущее значение const то true иначе false
template<class T>
struct IsConst : public FalseType {};

template<class T>
struct IsConst<const T> : public TrueType {};

template<class T>
using IsConst_R = IsConst<T>::result;


//IsRef - если текущее значение & то true иначе false
template<class T>
struct IsRef : public FalseType {};

template<class T>
struct IsRef<T&> : public TrueType {};

template<class T>
using IsRef_R = IsRef<T>::result;


//IsIntegral - если значение Integral то true иначе false
template<class T>
struct IsIntegral : public FalseType {};

template<class T, int n>
struct IsIntegral<Integral<T, n>> : public TrueType {};

template<class T>
using IsIntegral_R = IsIntegral<T>::result;


//IsRational - если значение Rational то true иначе false
template<class T>
struct IsRational : public FalseType {};

template<class T, int n, int m>
struct IsRational<Rational<T, n, m>> : public TrueType {};

template<class T>
using IsRational_R = IsRational<T>::result;


//RemoveCv - удаление квалификаторов const, volatile, const volatile
template<class T>
struct RemoveCv {
	using result = T;
};

template<class T>
struct RemoveCv<const T> {
	using result = T;
};

template<class T>
struct RemoveCv<volatile T> {
	using result = T;
};

template<class T>
struct RemoveCv<const volatile T> {
	using result = T;
};

template<class T>
using RemoveCv_R = RemoveCv<T>::result;