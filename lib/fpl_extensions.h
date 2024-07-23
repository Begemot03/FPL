#pragma once

/* 


	Extension представляют собой обёртку над типами данных

	Имеют поля type и value

	Операторы для расширений

		Сравнение

			Equal<T, U>			- если T == U то true иначе false
			Less<T, U>			- если T < U то true иначе false
			More<T, U>			- если T > U то true иначе false

	

*/


#define _I(T) Int<T>
#define _B(T) Bool<T>
#define _C(T) Char<T>
#define _D(T, U) Double<T, U>
#define _F(T, U) Float<T, U>



// Integral обертка над значениями которые могут быть представлены одним целым числом
template<class T, int n>
struct Integral {
	using type = T;

	static constexpr type value = static_cast<T>(n);

	constexpr type operator()() const noexcept { return static_cast<type>(value); }
};


// Rational обертка над значениями которые могут быть представлены двумя целыми числами
template<class T, int n, int m>
struct Rational {
	using type = T;

	static constexpr type value = static_cast<T>(n) / m;

	constexpr type operator()() const noexcept { return static_cast<type>(value); }
};


// Int type wrapper
template<int n>
using Int = Integral<int, n>;


// Bool type wrapper
template<int n>
using Bool = Integral<bool, n>;


// Char type wrapper
template<int n>
using Char = Integral<char, n>;


// Double type wrapper
template<int n, int m>
using Double = Rational<double, n, m>;


// Double type wrapper
template<int n, int m>
using Float = Rational<float, n, m>;


/* 


	Операторы



*/



// Оператор == для расширений
template<class T, class U>
struct Equal {
	using result = Bool<(T::value == U::value)>;
};


// Оператор < для расширений
template<class T, class U>
struct Less {
	using result = Bool<(T::value < U::value)>;
};


// Оператор > для расширений
template<class T, class U>
struct More {
	using result = Bool<(T::value > U::value)>;
};


// Оператор + для расширений
// template<template<typename T1, int n> typename T, template<typename U1, int m> typename U>
// struct Add;

// template<typename X, typename Y, int n, int m>
// struct Add<typename Integral<typename X, n>, typename Integral<typename Y, m>> {
// 	using result = typename Integral<X, n + m>;
// };

// Оператор + для расширений
template<class T, class U>
struct Add;

template<class T, class U, int n, int m>
struct Add<Integral<T, n>, Integral<U, m>> {
	using result = Integral<T, n + m>;
};

template<class T, class U, int n, int n1, int m1>
struct Add<Integral<T, n>, Rational<U, n1, m1>> {
	using result = Rational<U, n * m1 + n1, m1>;
};

template<class T, class U, int n, int n1, int m1>
struct Add<Rational<U, n1, m1>, Integral<T, n>> {
	using result = Rational<U, n * m1 + n1, m1>;
};

template<class T, class U, int n1, int m1, int n2, int m2>
struct Add<Rational<T, n1, m1>, Rational<U, n2, m2>> {
	using result = Rational<T, n1 * m2 + n2 * m1, m1 * m2>;
};

// Результат оператора + для расширений
template<class T, class U>
using Add_R = Add<T, U>::result;


// Оператор - для расширений
template<class T, class U>
struct Minus;

template<class T, class U, int n, int m>
struct Minus<Integral<T, n>, Integral<U, m>> {
	using result = Integral<T, n - m>;
};

template<class T, class U, int n, int n1, int m1>
struct Minus<Integral<T, n>, Rational<U, n1, m1>> {
	using result = Rational<U, n * m1 - n1, m1>;
};

template<class T, class U, int n, int n1, int m1>
struct Minus<Rational<U, n1, m1>, Integral<T, n>> {
	using result = Rational<U, n1 - n * m1, m1>;
};

template<class T, class U, int n1, int m1, int n2, int m2>
struct Minus<Rational<T, n1, m1>, Rational<U, n2, m2>> {
	using result = Rational<T, n1 * m2 - n2 * m1, m1 * m2>;
};

// Результат оператора - для расширений
template<class T, class U>
using Minus_R = Minus<T, U>::result;


// Оператор * для расширений
template<class T, class U>
struct Mult;

template<class T, class U, int n, int m>
struct Mult<Integral<T, n>, Integral<U, m>> {
	using result = Integral<T, n * m>;
};

template<class T, class U, int n1, int m1, int n2, int m2>
struct Mult<Rational<T, n1, m1>, Rational<U, n2, m2>> {
	using result = Rational<T, n1 * n2, m1 * m2>;
};

template<class T, class U, int n, int n1, int m1>
struct Mult<Integral<T, n>, Rational<U, n1, m1>> {
	using result = Rational<U, n * n1, m1>;
};

template<class T, class U, int n, int n1, int m1>
struct Mult<Rational<U, n1, m1>, Integral<T, n>> {
	using result = Rational<U, n * n1, m1>;
};

// Результат оператора * для расширений
template<class T, class U>
using Mult_R = Mult<T, U>::result;


// Оператор / для расширений
template<class T, class U>
struct Div;

template<class T, class U, int n, int m>
struct Div<Integral<T, n>, Integral<U, m>> {
	using result = Integral<T, n / m>;
};

template<class T, class U, int n1, int m1, int n2, int m2>
struct Div<Rational<T, n1, m1>, Rational<U, n2, m2>> {
	using result = Rational<T, n1 * m2, m1 * n2>;
};

template<class T, class U, int n, int n1, int m1>
struct Div<Integral<T, n>, Rational<U, n1, m1>> {
	using result = Rational<U, n1, m1 * n>;
};

template<class T, class U, int n, int n1, int m1>
struct Div<Rational<U, n1, m1>, Integral<T, n>> {
	using result = Rational<U, n1, m1 * n>;
};

// Результат оператора / для расширений
template<class T, class U>
using Div_R = Div<T, U>::result;


// ToIntegral - Переводит из Integral / Rational в Integral (Int type в результате)
template<class T>
struct ToIntegral {
	using result = Int<static_cast<int>(T::value)>;
};

template<class T>
using ToIntegral_R = ToIntegral<T>::result;


// ToRational - Переводит из Integral / Rational в Rational (Double type в результате)
template<class T>
struct ToRational {
	using result = Double<static_cast<int>(T::value), 1>;
};

template<class T>
using ToRational_R = ToRational<T>::result;


// And - оператор &&
template<class T, class U>
struct And {
	using result = Bool<(T::value && U::value)>;
};

template<class T, class U>
using And_R = And<T, U>::result;


//Or - оператор ||
template<class T, class U>
struct Or {
	using result = Bool<(T::value || U::value)>;
};

template<class T, class U>
using Or_R = Or<T, U>::result;


//Not - оператор !
template<class T>
struct Not {
	using result = Bool<!(T::value)>;
};

template<class T>
using Not_R = Not<T>::result;