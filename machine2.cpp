#include <iostream>
#include <vector>
#include <string>

// если присутствуют символы не из алфавита
// возвращает номер в строке первого вхождения такого символа
// иначе ноль
int is_format_right(std::string str, int length) {
	for (int i = 0; i < length; ++i) {
		if (str[i] != '0' && str[i] != '1') return i + 1;
	}
	return 0;
}

// значение функции перехода - новое состояние
// и строка, которая записывается в стек на место последнего символа.
// используется при работе с "таблицей переходов" (см. далее)
struct item {
	int state;
	std::string data;
};

// своеобразная "таблица переходов":
// первая ячейка - текущее состояние, вторая - текущий символ на ленте,
// третья - последний символ в стеке. Результатом перехода является пара:
// новое состояние и строка, которая записывается в стек на место последнего символа.
std::vector <std::vector<std::vector<item>>> createTable() 
{
	std::vector <std::vector<std::vector<item>>> 
		Table(4, std::vector< std::vector<item>>(2, std::vector<item>(3)));
	Table[0][0][0].state = 3;  Table[0][0][1].state = 1;  Table[0][0][2].state = 3;
	Table[0][1][0].state = 0;  Table[0][1][1].state = 0;  Table[0][1][2].state = 3;
	Table[0][0][0].data = "";  Table[0][0][1].data = "";  Table[0][0][2].data = "";
	Table[0][1][0].data = "z00";  Table[0][1][1].data = "000";  Table[0][1][2].data = "";

	Table[1][0][0].state = 3;  Table[1][0][1].state = 1;  Table[1][0][2].state = 3;
	Table[1][1][0].state = 2;  Table[1][1][1].state = 3;  Table[1][1][2].state = 3;
	Table[1][0][0].data = "";  Table[1][0][1].data = "";  Table[1][0][2].data = "";
	Table[1][1][0].data = "z00";  Table[1][1][1].data = "";  Table[1][1][2].data = "";

	Table[2][0][0].state = 3;  Table[2][0][1].state = 2;  Table[2][0][2].state = 3;
	Table[2][1][0].state = 3;  Table[2][1][1].state = 2;  Table[2][1][2].state = 3;
	Table[2][0][0].data = "";  Table[2][0][1].data = "";  Table[2][0][2].data = "";
	Table[2][1][0].data = "";  Table[2][1][1].data = "000";  Table[2][1][2].data = "";

	Table[3][0][0].state = 3;  Table[3][0][1].state = 3;  Table[3][0][2].state = 3;
	Table[3][1][0].state = 3;  Table[3][1][1].state = 3;  Table[3][1][2].state = 3;
	Table[3][0][0].data = "";  Table[3][0][1].data = "";  Table[3][0][2].data = "";
	Table[3][1][0].data = "";  Table[3][1][1].data = "";  Table[3][1][2].data = "";

	return Table;
}

// автомат.
// в качестве возвращаемого значения используется ноль, 
// если цепочка принадлежит языку; в противном случае возвращается 
// номер первого "неподходящего" символа.
int machine(std::string str, int length) {

	int res = is_format_right(str, length);
	if (res != 0) return res;

	std::vector <std::vector<std::vector<item>>>
		Table(4, std::vector< std::vector<item>>(2, std::vector<item>(3)));
	Table = createTable();

	std::string stack = "z";  // маркер дна
	int state = 0; // начальное состояние
	std::string data; // то, что потом запишется в стек
	for (int i = 0; i < length; ++i) {

		int cur = stack.length() - 1;
		if (cur < 0) return i;
		if (state == 3) return i;
		// номера ячейки в "таблице переходов"
		int ind1 = state; // текущее состояние
		int ind2; // текущий символ на ленте,
		int ind3; // последний символ в стеке.
		switch (str[i]) {
			case '0':
				ind2 = 0;
				break;
			case '1':
				ind2 = 1;
				break;
		}
		switch (stack[cur]) {
		case 'z':
			ind3 = 0;
			break;
		case '0':
			ind3 = 1;
			break;
		case '1':
			ind3 = 2;
			break;
		}
		// переходим в новое состояние
		state = Table[ind1][ind2][ind3].state;
		std::string data = Table[ind1][ind2][ind3].data;
		// заменяем последний элемент в стеке
		stack.erase(cur, 1);
		stack = stack + data;
	}

	if (stack.length() != 1) return str.length();
	// цепочка не принадлежит языку,
	// так как язык допускается по пустому стеку.
	// длина пустого стека == 1 (только маркер дна)

	return 0; //цепочка принадлежит языку
}


int main() {

	setlocale(LC_ALL, "Russian");
	std::string str = "";
	while (str != "exit") {
		std::cout << "Введите строку. Если вы хотите выйти, введите 'exit'"
			<< std::endl;
		std::cin >> str;
		int res = machine(str, str.length()); //передаю цепочку автомату
		if (res==0) 
			std::cout << "Строка принадлежит языку." << std::endl;
		else 
			std::cout << "Ошибка. Первое несоответствие: " << res << " символ." 
				<< std::endl;
	}
	return 0;
}
