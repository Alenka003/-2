#include <iostream>
#include <fstream>
#include <Windows.h>

using namespace std;


struct dop
{
	int age;
	char time[10];
};

struct MyStruct
{
	char surname[30];
	char name[30];
	char patronymic[30];
	char city[20];
	char street[20];
	int NumberHouse;
	int NumberFlat;
	int NumberCart;
	int Code;
	dop buyer; //дополнение массива структур новыми структурами
};

// Общие константы
const int buyerAmount = 4;
int length = 0;
MyStruct Buyers[buyerAmount];

// Функция для сортировки
void Sort()
{
	for (int i = 0; i < length; i++) {
		for (int j = 0; j < length - i - 1; j++) {
			if (Buyers[j].buyer.age > Buyers[j + 1].buyer.age) {
				swap(Buyers[j], Buyers[j + 1]);
			}
		}
	}
	for (int i = 0; i < length; i++) {
		cout << Buyers[i].surname << " " << Buyers[i].buyer.age << "\n";
	}
}

// Функция для вывода всех структур в консоль
void print() {
	for (int k = 0; k < length; k++)
	{
		cout << Buyers[k].surname << " " << Buyers[k].name << " " << Buyers[k].patronymic << "\n" << Buyers[k].city << " "
			<< Buyers[k].street << " " << Buyers[k].NumberHouse << " " << Buyers[k].NumberFlat << "\n" << Buyers[k].NumberCart << " "
			<< Buyers[k].Code << " " << Buyers[k].buyer.age << " " << Buyers[k].buyer.time << "\n\n";
	}
}

// Функция для добавления структуры
void add() {
	fstream output;
	output.open("output.txt", ios::app);

	if (!output.is_open()) {
		cout << "Не удалось открыть файл." << endl;
		return;
	}

	MyStruct Buyer = {};

	// Чтение данных из консоли
	cout << "Данные покупателя\n";
	cout << "Фамилия: ";
	cin.getline(Buyer.surname, 30);
	cout << "Имя: ";
	cin.getline(Buyer.name, 30);
	cout << "Отчество: ";
	cin.getline(Buyer.patronymic, 30);
	cout << "Город: ";
	cin.getline(Buyer.city, 30);
	cout << "Улица: ";
	cin.getline(Buyer.street, 30);
	cout << "Номер дома: ";
	cin >> Buyer.NumberHouse;
	cout << "Номер квартиры: ";
	cin >> Buyer.NumberFlat;
	cout << "Номер кредитной карты: ";
	cin >> Buyer.NumberCart;
	cout << "Код покупки: ";
	cin >> Buyer.Code;
	cout << "Возраст: ";
	cin >> Buyer.buyer.age;
	cin.ignore();
	cout << "Время покупки: ";
	cin.getline(Buyer.buyer.time, 10);

	// Запись в файл
	output << Buyer.surname << "\t";
	output << Buyer.name << "\t";
	output << Buyer.patronymic << "\t";
	output << Buyer.city << "\t";
	output << Buyer.street << "\t";
	output << Buyer.NumberHouse << "\t";
	output << Buyer.NumberFlat << "\t";
	output << Buyer.NumberCart << "\t";
	output << Buyer.Code << "\t";
	output << Buyer.buyer.age << "\t";
	output << Buyer.buyer.time << "\n";

	Buyers[length++] = Buyer;
	cout << endl;
	output.close();
}

void printMoreThan() {
	for (int k = 0; k < length; k++) {
		if (Buyers[k].buyer.age >= 20) {
			cout << "Возраст больше 19: " << Buyers[k].name << " " << Buyers[k].buyer.age << "\n";
		}
	}
}

// Функция загрузки структур из файла
void load() {
	fstream input;
	input.open("output.txt", ios::in);

	while (true) {
		MyStruct Buyer = {};
		input.getline(Buyer.surname, 30, '\t');
		input.getline(Buyer.name, 30, '\t');
		input.getline(Buyer.patronymic, 30, '\t');
		input.getline(Buyer.city, 30, '\t');
		input.getline(Buyer.street, 30, '\t');
		input >> Buyer.NumberHouse;
		input >> Buyer.NumberFlat;
		input >> Buyer.NumberCart;
		input >> Buyer.Code;
		input >> Buyer.buyer.age;
		input.ignore();
		input.getline(Buyer.buyer.time, 10, '\n');
		if (input.good()) {
			Buyers[length++] = Buyer;
		}
		else break;
		input.close();
	}
}
int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	load();
	int choice;
	while (true) {
		cout << "\n\n"
			<< "Выберите действие:\n"
			<< "1. Добавить структуру\n"
			<< "2. Вывести список структур\n"
			<< "3. Сортировка структур по возрасту\n"
			<< "4. Вывести структуры с возрастом больше 19\n";
		cin >> choice;
		cin.ignore();
		if (choice == 1) {
			add();
		}
		else if (choice == 2) {
			print();
		}
		else if (choice == 3) {
			Sort();
		}
		else if (choice == 4) {
			printMoreThan();
		}
	}
	return 0;
}