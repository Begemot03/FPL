#pragma once

#include "fpl_extensions.h"
#include "fpl_math.h"


/* 


	Методы для получения случайных последовательностей

	Формула, которая используется 
		Xn+1 = (A * Xn + B) mod M

	У каждого метода есть доп поле next - следующий элемент последовательсти



*/



/* 
	RandomSequences создает поле псевдослучайных чисел с помощью 4-х параметров
		T - начальное значение
		A - коэф 1
		B - коэф 2
		M - ограничитель (т.е. последовательность от 0 то M)
*/
template<class T, class A, class B, class M>
struct RandomSequence;

template<int n, int a, int b, int m>
struct RandomSequence<Int<n>, Int<a>, Int<b>, Int<m>> {
	using result = Int<(n * a + b) % m>;

	using next = RandomSequence<result, Int<a>, Int<b>, Int<m>>;
};

template<class T, class A, class B, class M>
using RandomSequence_R = RandomSequence<T, A, B, M>::result;


// Random - метод принимает начальное значние и генерирует последовательность псевдослучайных чисел
template<class T>
struct Random;

template<int n>
struct Random<Int<n>> {
	using result = RandomSequence<Int<n>, Int<n % 2 + 1>, Int<n % 23>, Int<577>>::result;

	using next = Random<Int<n + 1>>;
};

template<class T>
using Random_R = Random<T>::result;


// RandomBetween - метод принимает начальное значние и min max значния в последовательности и генерирует последовательность псевдослучайных чисел
template<class T, class Min, class Max>
struct RandomBetween;

template<int n, int min, int max>
struct RandomBetween<Int<n>, Int<min>, Int<max>> {
	using result = Int<
						Random<Int<n>>::result::value % (max - min + 1) + min
						>;

	using val = Random<Int<n>>::result;

	using next = RandomBetween<Int<n + 1>, Int<min>, Int<max>>;
};

template<class T, class Min, class Max>
using RandomBetween_R = RandomBetween<T, Min, Max>::result;