#include <iostream>
#include <string>
#include <vector>
#define EMPTY_STRING_IS_APPROPRIABLE
// определить - если строка '++' является подходящей
std::vector<std::vector<int>> createTable() //таблица перехода состояний
/*
* нулевой столбец - номера состояний (q_0, ... ,q_6)
* q_0- начальное, q_0, q_1, q_2 - финальные; q_6 - "дьявольское состояние"
* далее - таблица переходов
* (первый столбец - переход по "a", второй - по "b", третий - по "-")
*
*/
{
  std::vector<std::vector<int>> table(7, std::vector<int>(4));
  for (int i = 0; i < 7; ++i)
    table[i][0] = i;
  table[0][1] = 1; table[1][1] = 6; table[2][1] = 1;
  table[3][1] = 1; table[4][1] = 6; table[5][1] = 6;
  table[6][1] = 6; table[0][2] = 2; table[1][2] = 2;
  table[2][2] = 6; table[3][2] = 6; table[4][2] = 2;
  table[5][2] = 6; table[6][2] = 6; table[0][3] = 6;
  table[1][3] = 3; table[2][3] = 4; table[3][3] = 6;
  table[4][3] = 6; table[5][3] = 6; table[6][3] = 6;
  return table;
}
bool is_format_right(std::string str, int len)
{
  #ifndef EMPTY_STRING_IS_APPROPRIABLE
    if (len == 2)
      return false;
  #endif
  for (int i = 1; i < len-1; ++i)
  {
    char symbol = str[i];
    if (symbol != 'a' && symbol != 'b' && symbol != '-')
      return false;
  }
  return true;
}
bool machine(std::string str)
{
  int len = str.length();
  if (!is_format_right(str, len))
    return false;
  std::vector<std::vector<int>> table(7, std::vector<int>(4));
  table = createTable();
  int state = 0; // текущее состояние автомата
  for (int cur = 1; cur < len - 1; ++cur)
  {
    int col; /* столбец в таблице, где находится
    символ, по которому мы переходим */
    switch (str[cur])
    {
      case 'a':
        col = 1;
        break;
      case 'b':
        col = 2;
        break;
      case '-':
        col = 3;
        break;
    }
    // переход из состояния q_i по символу, находящемуся в j-том столбце,
    // осуществляется в состояние с номером table[i][j]
    state = table[state][col];
  }
  if (state == 0 || state == 1 || state == 2)
    return true;
  return false;
}

int main()
{
  setlocale(LC_ALL, "Russian");
  std::string basic_str ="";
  while (basic_str != "exit")
  {
    std::cout << "Введите строку. Если вы хотите выйти, введите 'exit'"
      << std::endl;
    std::cin >> basic_str;
    // ищем '+' в последовательности символов
    // начиная со второго '+' рассматриваем
    // подцепочки от предыдущего плюса до текущего
    // если находим цепочки языка, выводим на экран
    // если нет, то переменная is_there_anything равна false
    // тогда мы выведем сообщение о том, что подцепочек
    // данного языка во входной последовательности нет
    int ind = -1; // номер предыдущего '+'
    bool is_there_anything = false;
    for (int i = 0; i < basic_str.length(); ++i)
    {
      if (basic_str[i] != '+')
        continue;
      if (ind == -1)
      {
        ind = i;
        continue;
      }
      std::string str = basic_str.substr(ind, i + 1 - ind);
      if (machine(str))
      {
        is_there_anything = true;
        std::cout << str << std::endl;
      }
      ind = i;
    }
    if (!is_there_anything && basic_str!="exit")
    std::cout << "В вашей строке нет цепочек языка" << std::endl;
  }
  return 0;
}
