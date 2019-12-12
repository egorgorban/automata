#include <iostream>
#include <vector>
#include <string>

// ���� ������������ ������� �� �� ��������
// ���������� ����� � ������ ������� ��������� ������ �������
// ����� ����
int is_format_right(std::string str, int length) {
	for (int i = 0; i < length; ++i) {
		if (str[i] != '0' && str[i] != '1') return i + 1;
	}
	return 0;
}

// �������� ������� �������� - ����� ���������
// � ������, ������� ������������ � ���� �� ����� ���������� �������.
// ������������ ��� ������ � "�������� ���������" (��. �����)
struct item {
	int state;
	std::string data;
};

// ������������ "������� ���������":
// ������ ������ - ������� ���������, ������ - ������� ������ �� �����,
// ������ - ��������� ������ � �����. ����������� �������� �������� ����:
// ����� ��������� � ������, ������� ������������ � ���� �� ����� ���������� �������.
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

// �������.
// � �������� ������������� �������� ������������ ����, 
// ���� ������� ����������� �����; � ��������� ������ ������������ 
// ����� ������� "�������������" �������.
int machine(std::string str, int length) {

	int res = is_format_right(str, length);
	if (res != 0) return res;

	std::vector <std::vector<std::vector<item>>>
		Table(4, std::vector< std::vector<item>>(2, std::vector<item>(3)));
	Table = createTable();

	std::string stack = "z";  // ������ ���
	int state = 0; // ��������� ���������
	std::string data; // ��, ��� ����� ��������� � ����
	for (int i = 0; i < length; ++i) {

		int cur = stack.length() - 1;
		if (cur < 0) return i; // if (cur == -1) return i //i+1??
		if (state == 3) return i;
		// ������ ������ � "������� ���������"
		int ind1 = state; // ������� ���������
		int ind2; // ������� ������ �� �����,
		int ind3; // ��������� ������ � �����.
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
		// ��������� � ����� ���������
		state = Table[ind1][ind2][ind3].state;
		std::string data = Table[ind1][ind2][ind3].data;
		// �������� ��������� ������� � �����
		stack.erase(cur, 1);
		stack = stack + data;
	}

	if (stack.length() != 1) return str.length();
	// ������� �� ����������� �����,
	// ��� ��� ���� ����������� �� ������� �����.
	// ����� ������� ����� == 1 (������ ������ ���)

	return 0; //������� ����������� �����
}


int main() {

	setlocale(LC_ALL, "Russian");
	std::string str = "";
	while (str != "exit") {
		std::cout << "������� ������. ���� �� ������ �����, ������� 'exit'"
			<< std::endl;
		std::cin >> str;
		int res = machine(str, str.length()); //������� ������� ��������
		if (res==0) 
			std::cout << "������ ����������� �����." << std::endl;
		else 
			std::cout << "������. ������ ��������������: " << res << " ������." 
				<< std::endl;
	}
	return 0;
}