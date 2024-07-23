#pragma once

#include "fpl_utility.h"
#include "fpl_extensions.h"


/* 



	Реализация списка типов

		Список имеет поля
		
			tail - хвост списка
			value - текущее значение

		Про tail

			берем список typedef TypeList<char, int, double> a;

			a::tail <===> TypeList<int, double>
			a::tail::tail <===> TypeList<double>
			a::tail::tail::tail <===> TypeList<>
			a::tail::tail::tail::tail <===> NullType

			Тут видно что у списка есть ограничитель NullType

		Пустой список

			TypeList<>

			value = NullType
			tail = NullType



*/
template<class... lst>
struct TypeList;

template<class H, class... lst>
struct TypeList<H, lst...>
{
	using tail = TypeList<lst...>;
	using value = H;
};

template<>
struct TypeList<>
{
	using tail = NullType;
	using value = NullType;
};


// String - список символов
template<int... lst>
using String = TypeList<Char<lst>...>;



/* 

	Методы для работы с TypeList

*/



// Prepend - добавление элемента в начало списка
template<class T, class List>
struct Prepend;

template<class T>
struct Prepend<T, TypeList<>>
{
    using result = TypeList<T>;
};

template<class T, class H, class... lst>
struct Prepend<T, TypeList<H, lst...>>
{
    using result = TypeList<T, H, lst...>;
};

// result для Prepend
template<class T, class List>
using Prepend_R = Prepend<T, List>::result;


// PrependEnd - добавление элемента в конец списка
template<class T, class List>
struct PrependEnd;

template<class T>
struct PrependEnd<T, TypeList<>>
{
    using result = TypeList<T>;
};

template<class T, class H, class... lst>
struct PrependEnd<T, TypeList<H, lst...>>
{
    using result = TypeList<H, lst..., T>;
};

// result для PrependEnd
template<class T, class List>
using PrependEnd_R = PrependEnd<T, List>::result;


//RemoveTypes - удалять элементы определенного типа из списка
template<class T, class List>
struct RemoveTypes;

template<class T, class H, class... lst>
struct RemoveTypes<T, TypeList<H, lst...>> {
	using result = 	Select<
						typename IsSame<H, T>::result,
						typename RemoveTypes<T, TypeList<lst...>>::result,
						typename Prepend<H, typename RemoveTypes<T, TypeList<lst...>>::result>::result
				>::result;
};

template<class T>
struct RemoveTypes<T, TypeList<>> {
	using result = TypeList<>;
};

// result для RemoveTypes
template<class T, class List>
using RemoveTypes_R = RemoveTypes<T, List>::result;


//Remove - удалить первый T элемент
template<class T, class List>
struct Remove;

template<class T, class H, class... lst>
struct Remove<T, TypeList<H, lst...>> {
	using result = Select<
							typename IsSame<T, H>::result,
							TypeList<lst...>,
							typename Prepend<H, typename Remove<T, TypeList<lst...>>::result>::result
						>::result;
};

template<class T>
struct Remove<T, TypeList<>> {
	using result = TypeList<>;
};


// Len - длина списка
template<class List>
struct Len;

template<class H, class... lst>
struct Len<TypeList<H, lst...>> {
	using result = Int<1 + Len<TypeList<lst...>>::result::value>;
};

template<>
struct Len<TypeList<>> {
	using result = Int<0>;
};

// result для Len
template<class List>
using Len_R = Len<List>::result;


//At - получение элемента по индексу
template<class N, class List>
struct At;

template<class N>
struct At <N, TypeList<>> {
	using result = NullType;
};

template<class T, int n, class H, class... lst>
struct At<Integral<T, n>, TypeList<H, lst...> > {
	static_assert(n < Len<TypeList<H, lst...>>::result::value, "index > list size");

	using result = Select<
							typename Equal<Integral<T, n>, Int<0>>::result,
							H,
							typename At<Integral<T, n - 1>, TypeList<lst...>>::result
						>::result;
};

// result для At
template<class N, class List>
using At_R = At<N, List>::result;


// Map - применить функцию ко всем элементам списка и вернуть новый список
template <template <class> class Func, class List>
struct Map;

template <template <class> class Func, class... lst>
struct Map<Func, TypeList<lst...>> {
    using result = TypeList<typename Func<lst>::result...>;
};

// result для Map
template<template <class> class Func, class List>
using Map_R = Map<Func, List>::result;


// Filter - возвращает новый список, элементы которого удовлетворяют условию
template<template<class> class Cond, class List>
struct Filter;

template<template<class> class Cond, class... lst>
struct Filter<Cond, TypeList<lst...>> {
	using result = RemoveTypes<
								DeletedType, 
								TypeList<typename Select<typename Cond<lst>::result, lst, DeletedType>::result...>
							>::result;
};

// result для Filter
template<template <class> class Cond, class List>
using Filter_R = Filter<Cond, List>::result;


// Reverse - переворачивает список
template<class List>
struct Reverse;

template<class H, class... lst>
struct Reverse<TypeList<H, lst...>> {
	using result = typename PrependEnd<
										H, 
										typename Reverse<TypeList<lst...>>::result
									>::result;
};

template<>
struct Reverse<TypeList<>> {
	using result = TypeList<>;
};

// result для Reverse
template<class List>
using Reverse_R = Reverse<List>::result;


// CreateIntList - создает typelist заполненый Int<...>
template<int... lst>
struct CreateIntList {
	using result = TypeList<Int<lst>...>;
};

template<int... lst>
using CreateIntList_R = CreateIntList<lst...>::result;

//MinElement - минимальный элемент в списке
template<class List>
struct MinElement;

template<class T, class... lst>
struct MinElement<TypeList<T, lst...>> {
	using result = Select<
							typename Less<T, typename MinElement<TypeList<lst...>>::result>::result,
							T,
							typename MinElement<TypeList<lst...>>::result
							>::result;
};

template<class T>
struct MinElement<TypeList<T>> {
	using result = T;
};

template<class List>
using MinElement_R = MinElement<List>::result;


//MaxElement - максимальный элемент в списке
template<class List>
struct MaxElement;

template<class T, class... lst>
struct MaxElement<TypeList<T, lst...>> {
	using result = Select<
							typename More<T, typename MaxElement<TypeList<lst...>>::result>::result,
							T,
							typename MaxElement<TypeList<lst...>>::result
							>::result;
};

template<class T>
struct MaxElement<TypeList<T>> {
	using result = T;
};

template<class List>
using MaxElement_R = MaxElement<List>::result;


// Sort - сортировка массива
template<class List>
struct Sort {
	using result = 	Prepend<
								typename MinElement<List>::result,
								typename Sort<typename Remove<typename MinElement<List>::result, List>::result>::result
							>::result;
};

template<class T>
struct Sort<TypeList<T>> {
	using result = TypeList<T>;
};

template<class List>
using Sort_R = Sort<List>::result;


//Has - проверяет есть ли элемент в списке
template<class T, class List>
struct Has;

template<class T, class H, class... lst>
struct Has<T, TypeList<H, lst...>> {
	using result = Select<
							typename IsSame<T, H>::result,
							Bool<1>,
							typename Has<T, TypeList<lst...>>::result
						>::result;
};

template<class T>
struct Has<T, TypeList<>> {
	using result = Bool<0>;
};


//Insert - добавляет элемент в указанную позицию
template<class N, class T, class List>
struct Insert;

template<class U, int n, class T, class H, class... lst>
struct Insert<Integral<U, n>, T, TypeList<H, lst...>> {
	static_assert(n - 1 < Len<TypeList<H, lst...>>::result::value, "index > list size");

	using result = Select<
							typename Equal<Integral<U, n>, Integral<U, 0>>::result,
							TypeList<T, H, lst...>,
							typename Prepend<H, typename Insert<Integral<U, n - 1>, T, TypeList<lst...>>::result>::result
						>::result;
};

template<class U, int n, class T>
struct Insert<Integral<U, n>, T, TypeList<>> {
	using result = TypeList<T>;
};

template<class N, class T, class List>
using Insert_R = Insert<N, T, List>::result;


//FindOn - возвращает индекс элемента начиная с N-го элемента, если элемента нет то Int<-1>
template<class N, class T, class List>
struct FindOn;

template<class U, int n, class T, class H, class... lst>
struct FindOn<Integral<U, n>, T, TypeList<H, lst...>> {
	using result = Select<
							typename IsSame<T, H>::result,
							Integral<U, n>,
							typename FindOn<Integral<U, n + 1>, T, TypeList<lst...>>::result
						>::result;
};

template<class U, int n, class T> 
struct FindOn<Integral<U, n>, T, TypeList<>>{
	using result = Int<-1>;
};

template<class N, class T, class List>
using FindOn_R = FindOn<N, T, List>::result;


//Find -  возвращает индекс элемента начиная сначала списка, если элемента нет то Int<-1>
template<class T, class List>
using Find = FindOn<Int<0>, T, List>;

template<class T, class List>
using Find_R = Find<T, List>::result;


//CreateTypeList - создает TypeList получая тип
template<class T, int... lst>
struct CreateTypeList;

template<class T, int n, template<class, int> class Type, int... lst>
struct CreateTypeList<Type<T, n>, lst...> {
	using result = TypeList<Type<T, lst>...>;
};

template<class T, int n, int m, template<class, int, int> class Type, int... lst>
struct CreateTypeList<Type<T, n, m>, lst...> {
	using result = TypeList<Type<T, lst, m>...>;
};

template<class T, int... lst>
using CreateTypeList_R = CreateTypeList<T, lst...>::result;