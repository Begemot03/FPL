#include <iostream>

#include "lib/fpl_extensions.h"
#include "lib/fpl_typelist.h"
#include "lib/fpl_utility.h"
#include "lib/fpl_functions.h"
#include "lib/fpl_random.h"
#include "lib/fpl_math.h"



/* 

	Про FPL - С++ библиотека времени-компиляции позволяет обрабатывать данные на этапе компиляции и придерживается функционального стиля

*/



int main() {
	using testlist = CreateIntList_R<1, 2, 3, 4, 5>;

	using i = AClose<And, _I(1), _I(0)>::lambda<>::result;

	return 0;
}



/* 



	Список всех типов

		NullType							- утилитарный тип (пустой тип)
		DeletedType							- утилитарный тип (тип удаленного элемента, использоуется в методах списков)
		Integral<T, T n>					- обертка над всеми типами, которые могут быть представлены c помощью одного числа
		Rational<T, T n, T m>				- обертка над всеми типами, которые могут быть представлены c помощью двух чисел
		Int<n>								- обертка над int (Integral<int, n>)
		Double<n, m>						- обертка над double (Rational<double, n, m>)
		Float<n, m>							- обертка над float (Rational<float, n, m>)
		Bool<n>								- обертка над bool всё что не 0 это true(1) иначе false(0) (Integral<bool, n>)
		Char<n>								- обертка над char (Integral<char, n>)
		TypeList<lst...>					- список типов
		String<lst...>						- список Char<T>

	

	Про выбор типа при операциях между расширениями, тип итогового расширения будет равен

		1) Если два члена только Integral или Rational то будет тип первого члена (пример Add<Int<5>, Char<34>>::result у result = Integral<int, 39>, если же Add<Char<5>, Int<34>>::result у result = Integral<char, 39>)
		2) Если члены имеют смешнаную основу, то есть Integral + Rational или Rational + Integral, то тип будет такой же как и у Rational



	Список методов

		Для TypeList (15)

			At<index, TypeList<...>>		- получение элемента по индексу
			Prepend<T, TypeList<...>>		- добавляет в начало TypeList элемент T
			PrependEnd<T, TypeList<...>>	- добавляет в конец TypeList элемент T
			RemoveTypes<T, TypeList<...>>	- удаляет из списка элементы равные T (осторожно! DeletedType удалиться из списка)
			Remove<T, TypeList<...>>		- удаляет первое вхождение элемента
			Reverse<TypList<...>>			- переворачивает список
			Has<T, TypeList<...>>			- проверяет наличие элемента в списке
			Insert<N, T, TypeList<...>>		- вставка элемента T по позиции N
			FindOn<N, T, TypeList<...>>		- поиск элемента T с позиции N, возвращает индекс элемента если он есть в списке, иначе Int<-1>
			Find<T, TypeList<...>>			- поиск элемента T с начала списка, возвращает индекс элемента если он есть в списке, иначе Int<-1>
			Len<TypeList<...>>				- длина списка
			Map<Func, TypeList<...>>		- Func ко всем x : TypeList<...>
			Filter<Cond, TypeList<...>>		- Возвращает новый список, элементы которого удовлетворяют Cond
			Sort<TypeList<...>>				- Сортирует элемент в возврастающем порядке
			CreateTypeList<Wrapper, lst...>	- Создает typelist, элементы которого будут типа Wrapper (CreateTypeList<Int<1>, 1, 2, 3, 4> => TypeList<Int<1>, Int<2>, Int<3>, Int<4>>), но с типами, которые принимают 2 числа, второе число берется из Wrapper (createTypeList<Double<1, 10>, 1, 2, 3> => TypeList<Double<1, 10>, Double<2, 10>, Double<3, 10>>)



		Для Extensions (12)
			
			Макросы быстрого создания: 
				_I(T)						- Int<T>
				_B(T)						- Bool<T>
				_C(T)						- Char<T>
				_D(T, U)					- Double<T, U>
				_F(T, U)					- Float<T, U>


			ToIntegral<T>					- приводит T к Integral<int, ...>
			ToRational<T>					- приводит T к Rational<double, ...>
			Equal<T, U>						- если T::value == U::value то true иначе false
			Less<T, U>						- если T::value < U::value то true иначе false
			More<T, U>						- если T::value > U::value то true иначе false
			Add<T, U>						- T + U
			Minus<T, U>						- T - U
			Mult<T, U>						- T * U
			Div<T, U>						- T / U
			And<T, U>						- T && U
			Or<T, U>						- T || U
			Not<T>							- !T
		


		Утилитарные (10)
		
			Select<cond, T, U>				- если cond == Bool<1> то T иначе Bool<0>
			IsSame<T, U>					- если T == U то Bool<1> иначе Bool<0>
			IsPrt<T>						- если T == * то Bool<1> иначе Bool<0>
			IsConst<T>						- если T == const то Bool<1> иначе Bool<0>
			IsRef<T>						- если T == ref то Bool<1> иначе Bool<0>
			RemoveCv<T>						- удаляет все квалификаторы перед типом
			IsIntegral						- если T == Integral то Bool<1> иначе Bool<0>
			IsRational						- если T == Rational то Bool<1> иначе Bool<0>
			TrueType						- нужен для наследования в других структурах того чтобы result = Bool<1>
			FalseType						- нужен для наследования в других структурах того чтобы result = Bool<0>



		Для улучшения работы с кастомными и прочими методами (4)

			Close<Func, T>::lambda<U>		- преобразует функцию с двумя аргументами в функцию с одним аргументом Func<T, U> => Close<Func, T>::lambda<U>
			FlipСlose<Func, T>::lambda<U>	- преобразует функцию с двумя аргументами в функцию с одним аргументом Func<U, T> => FlipClose<Func, T>::lambda<U>
			AClose<Func, T>::lambda<U>		- преобразует функцию Func<lst1..., lst2...> => AClose<Func, lst1...>::lambda<lst2...>
			FlipAClose<Func, T>::lambda<U>	- преобразует функцию Func<lst2..., lst1...> => AClose<Func, lst1...>::lambda<lst2...>

		Математические (12)

			Abs<T>							- метод модуля числа ( T < 0 ? -T : T)
			Min<lst...>						- метод для поиска минимального числа в последовательности
			Max<lst...>						- метод для поиска максимального числа в последовательности
			ToOdd<T>						- метод приводит T к ближайшему нечетному числу (только Integral)
			ToEven<T>						- метод приводит T к ближайшему четному числу (только Integral)
			Clamp<T, Min, Max>				- метод result = min <= T <= max
			PI								- метод result = 3,14 (Rational)
			E								- метод result = 2,718 (Rational)
			Ceil<T>							- метод округляет T к большему числу
			Floor<T>						- метод округляет T к меньшему числу
			Factorial<T>					- метод T!
			Pow<T, U>						- метод возводит T в степень U


		
		Рандом (3)

			RandomSequence<T, A, B, M>		- генерирует последовательность псевдослучайных чисел (T - начальное значение, A, B - свободные коэфициенты, M - ограничитель последовательности)
			Random<T>						- генерирует последовательность псевдослучайных чисел, используя только начальное значение
			RandomBetween<T, Min, Max>		- генерирует последовательность псевдослучайных чисел в интервале [Min, Max]



*/



/* 
	Методичка для понимания как всё устроенно

	У всех методов что есть поле result есть укороченная версия, которая сразу возвращает результат, но в самой реализации требуется оригинальная версия метода, т.е.
	Вы можете написать что-то такое:

		using adding = Add_R<int, Int<5>, Int<2>>; тут addding это результат сложения, но если
		using adding = Add<int, Int<5>, Int<2>>; тут adding это сам метод Add<T, U>, чтобы получить result нужно
		using addingResult = adding::result;
		если коротко, то Add_R<...> === Add<...>::result
		в ядре самой библиотеки требуется чтобы в методы передавались методы, а не результат, то есть
		Filter_R<IsConst, TypeList<...>> или Filter<IsConst, TypeList<...>>::result, но не
		Filter_R<IsConst_R, TypeList<...>> или Filter<IsConst_R, TypeList<...>>::result, так как это уже результат, а не метод


	Все объекты в данной библиотеке могут иметь такие поля как:

		value		- значение, записанное объект (значение)
		type		- тип данных (тип)
		result		- результат выполнения функции (тип)
		lambda		- объект-функция в объекте-функция (тип)
		next		- следующий элемент в объекте (тип) (пока только в рандоме)



	Cпециально для TypeList (лист типов, так же может хранить значения с помощью extensions)

		tail - следующий элемент списка
		последний элемент имеет тип NullType


	Имена аргументов и их значение

		lst			- список типов (например <int, char, double...>)
		Cond		- объект, результат которого bool (decltype(result) == bool)
		Func		- объект, который примимает n-ое число параметров и применяет к ним функцию и результат которого это результат функции (пример Func = Add<Int<2>, Int<3>>::result == Int(5)
		List		- объект-список (TypeList)
		T, U...		- какой-то свободный тип (любая большая буква это тип)
		H			- голова списка (TypeList header)
		Min, Max...	- аргумент-тип для понятного назначения
		cond		- либо false либо true
		n, m...		- какое-то численное значение (любая маленькая буква это значение)
		min, max...	- аргумент-значение для понятного назначения
		


*/