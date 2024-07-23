
/* 

	Обзор на библиотеку boost Phoenix ч.5

	Работа с объектами
	
	Вы можете использовать ленивые операторы
		
		if_(arg1 > 5) [
			std::cout << arg1
		]

*/

std::for_each(v.begin(), v.end(), 
	if_(arg1) [
		std::cout << arg1 << ", "
	]	
)
























