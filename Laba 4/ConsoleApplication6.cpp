#include <fstream>
#include <iostream>
#include <Windows.h>
int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	const int len = 200;
	char text[len];
	char c[] = "ЁёУуАаОоЭэЯяИиЮю";
	std::ifstream input;
	std::ofstream output;
	input.open("input.txt");
	output.open("output.txt");

	if (!(input.is_open() && output.is_open())) {
		std::cout << "Не удалось открыть файл.";
	}

	// Чтение из файла
	input.get(text, len, NULL);

	int s = 0;

	for (int i = 0; i < len; i++) {
		if (text[i] == '\n' || text[i] == ' ' || text[i] == '\0') {
			// Проверка на гласную букву
			for (int j = 0; j < sizeof(c); j++) {
				if (text[s] == c[j]) {
					// Вывод слова
					for (int k = s; k < i; k++) {
						output << text[k];
					}
					output << '\n';
					break; // Прервать проверку на гласную букву
				}
			}
			// Сдвиг начала слова
			s = ++i;
		}
		// Прервать глобальный цикл в конце строки
		if (text[i] == '\0') break;
	}
}