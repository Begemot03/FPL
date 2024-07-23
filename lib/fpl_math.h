#pragma once

#include "fpl_extensions.h"
#include "fpl_utility.h"


/* 


	Математические методы


*/



//Abs - модуль числа
template<class T>
struct Abs;

template<class T, int n>
struct Abs<Integral<T, n>> {
	using result = Select<
							typename Less<Integral<T, n>, Int<0>>::result,
							Integral<T, -n>,
							Integral<T, n>
						>::result;
};

template<class T, int n, int m>
struct Abs<Rational<T, n, m>> {
	using result = Select<
							typename Less<Rational<T, n, m>, Int<0>>::result,
							Rational<T, -n, m>,
							Rational<T, n, m>
						>::result;
};

template<class T>
using Abs_R = Abs<T>::result;


//Min - минимальное число последовательности
template<class... lst>
struct Min;

template<class T>
struct Min<T> {
	using result = T;
};

template<class T, class... lst>
struct Min<T, lst...> {
	using result = Select<
							typename Less<T, typename Min<lst...>::result>::result,
							T,
							typename Min<lst...>::result
						>::result;
};

template<class... lst>
using Min_R = Min<lst...>::result;


//Max - максимальное число последовательности
template<class... lst>
struct Max;

template<class T>
struct Max<T> {
	using result = T;
};

template<class T, class... lst>
struct Max<T, lst...> {
	using result = Select<
							typename More<T, typename Max<lst...>::result>::result,
							T,
							typename Max<lst...>::result
						>::result;
};

template<class... lst>
using Max_R = Max<lst...>::result;


// ToOdd - приводит целое число к ближайшему нечетному числу
template<class T>
struct ToOdd;

template<class T, int n> 
struct ToOdd<Integral<T, n>> {
	using result = Integral<T, n % 2 ? n : n + 1>;
};

template<class T>
using ToOdd_R = ToOdd<T>::result;


// ToEven - приводит целое число к ближайшему нечетному числу
template<class T>
struct ToEven;

template<class T, int n> 
struct ToEven<Integral<T, n>> {
	using result = Integral<T, n % 2 ? n + 1 : n>;
};

template<class T>
using ToEven_R = ToEven<T>::result;


// Clamp - возвращает число между двумя границами
template<class T, class Min, class Max>
struct Clamp {
	using result = typename Select<
							typename Less<T, Min>::result,
							Min,
							typename Select<typename More<T, Max>::result, Max, T>::result
						>::result;
};

template<class T, class Min, class Max>
using Clamp_R = Clamp<T, Min, Max>::result;


// PI - result = pi
struct PI {
	using result = Double<314, 100>;
};

using PI_R = PI::result;


//E - result = e
struct E {
	using result = Double<2718, 1000>;
};

using E_R = E::result;


//Ceil - округление в большую сторону
template<class T>
struct Ceil;

template<class T, int n>
struct Ceil<Integral<T, n>> {
	using result = Integral<T, n>;
};

template<class T, int n, int m>
struct Ceil<Rational<T, n, m>> {
	using result = Rational<T, ((int)(n / m) + 1) * m, m>;
};

template<class T>
using Ceil_R = Ceil<T>::result;

//Floor - округление в большую сторону
template<class T>
struct Floor;

template<class T, int n>
struct Floor<Integral<T, n>> {
	using result = Integral<T, n>;
};

template<class T, int n, int m>
struct Floor<Rational<T, n, m>> {
	using result = Rational<T, (int)(n / m) * m, m>;
};

template<class T>
using Floor_R = Floor<T>::result;


//Factorial - факториал числа
template<class T>
struct Factorial;

template<class T>
struct Factorial<Integral<T, 0>> {
	using result = Integral<T, 1>;
};

template<class T, int n>
struct Factorial<Integral<T, n>> {
	using result = Integral<T, n * Factorial<Integral<T, n - 1>>::result::value>;
};

template<class T>
using Factorial_R = Factorial<T>::result;


//Pow - возведение в степень
template<class T, class U>
struct Pow;

template<class T, class U>
struct Pow<T, Integral<U, 1>> {
	using result = T;
};

template<class T, int n, class U, int m>
struct Pow<Integral<T, n>, Integral<U, m>> {
	using result = typename Mult<Integral<T, n>, typename Pow<Integral<T, n>, Integral<U, m - 1>>::result>::result;
};

template<class T, int n, int m, class U, int m1>
struct Pow<Rational<T, n, m>, Integral<U, m1>> {
	using result = typename Mult<Rational<T, n, m>, typename Pow<Rational<T, n, m>, Integral<U, m1 - 1>>::result>::result;
};

template<class T, class U>
using Pow_R = Pow<T, U>::result;