#pragma once



/* 



	Методы для упрощения работы с кастомными объектами-функциями



*/



/* 
	Вспомогательный объект-функция предоставляющая реализацию для замыкания другого объекта-функции с 2-мя параметрами 
	Сlose<Func, T>::lambda<U>::result <==> Func<T, U>::result  
*/
template<template<class, class> class Func, class T>
struct Сlose {
	template<class U>
	struct lambda {
		using result = Func<T, U>::result;
	};
};


/* 
	Вспомогательный объект-функция предоставляющая реализацию для замыкания другого объекта-функции с 2-мя параметрами 
	FlipСlose<Func, T>::lambda<U>::result <==> Func<U, T>::result  
*/
template<template<class, class> class Func, class T>
struct FlipСlosure {
	template<class U>
	struct lambda {
		using result = Func<U, T>::result;
	};
};


/* 
	Вспомогательный объект-функция предоставляющая реализацию для замыкания другого объекта-функции с A-мя параметрами 
	AClose<Func, lst1...>::lambda<lst2...>::result <==> Func<lst1..., lst2...>::result  
*/
template<template<class, class> class Func, class... lst1>
struct AClose {
	template<class... lst2>
	struct lambda {
		using result = Func<lst1..., lst2...>::result;
	};
};


/* 
	Вспомогательный объект-функция предоставляющая реализацию для замыкания другого объекта-функции с A-мя параметрами 
	FlipAClose<Func, lst1...>::lambda<lst2...>::result <==> Func<lst2..., lst1...>::result  
*/
template<template<class, class> class Func, class... lst1>
struct FlipAClose {
	template<class... lst2>
	struct lambda {
		using result = Func<lst2..., lst1...>::result;
	};
};