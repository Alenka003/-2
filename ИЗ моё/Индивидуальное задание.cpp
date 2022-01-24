#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
#include <Windows.h>

void Rez();

using namespace std;

const int a = 500;

struct People
{
	char people[a];//ФИО
	int64_t number;//номер телефона
	int64_t day;//день
	int64_t month;//месяц
	int64_t year;//год
	char disconn[a];//дата
	char percent[a];//задолжность
	char credite[a];//кредит
}People[10]{};

struct Services
{
	char service[a];//название
	long long code;//код
	int64_t cost;//тариф
	char data[a];//интервал
} Services[10]{};

struct PeopleService
{
	int64_t phone;//номер телефона
	int64_t Pcode;//код
	int64_t Pday;//день
	int64_t Pmonth;//месяц
	int64_t Pyear;//год
	char Ptime[a];//время
	int64_t Punit;//время использования
}PeopleServices[10]{};

struct Parametr
{
	char Ppeople[a];//ФИО
	int64_t number;
} Parametr[10]{};//10

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	FILE* file_1;
	errno_t Error1;
	Error1 = fopen_s(&file_1, "People.txt", "r+");
	if (Error1 == 0) {
		for (int i = 0; i < 10; i++) {
			fscanf_s(
				file_1,
				"%500[^,], %d, %d.%d.%d, %500[^,], %500[^,], %500[^\n] \n",
				People[i].people, a,
				&People[i].number,
				&People[i].day,
				&People[i].month,
				&People[i].year,
				People[i].disconn, a,
				People[i].percent, a,
				People[i].credite, a);
		}
		fclose(file_1);
	}
	else {
		cout << "Список клиентов пуст!" << endl;
	}
	FILE* file_2;
	errno_t Error2;
	Error2 = fopen_s(&file_2, "Param.txt", "r+");
	if (Error2 == 0) {
		for (int i = 0; i < 10; i++) {
			fscanf_s(
				file_2,
				"%500[^\n] \n",
				Parametr[i].Ppeople, a
			);
		}
		fclose(file_2);
	}
	else {
		cout << "Нет параметров!" << endl;
	}
	FILE* file_3;
	errno_t Error3;
	Error3 = fopen_s(&file_3, "PeopleServices.txt", "r+");
	if (Error3 == 0) {
		for (int i = 0; i < 10; i++) {
			int r = fscanf_s(
				file_3,
				"%d, %d, %d.%d.%d %500[^,], %d \n",
				&PeopleServices[i].phone,
				&PeopleServices[i].Pcode,
				&PeopleServices[i].Pday,
				&PeopleServices[i].Pmonth,
				&PeopleServices[i].Pyear,
				PeopleServices[i].Ptime, a,
				&PeopleServices[i].Punit
			);
			if (r == 0) {
				PeopleServices[i].Punit = 1;
				while (fgetc(file_3) != '\n');
			}
		}
		fclose(file_3);
	}
	else {
		cout << "Нет используемых услуг!" << endl;
		fclose(file_2);
	}
	FILE* file_4;
	errno_t Error4;
	Error4 = fopen_s(&file_4, "Services.txt", "r+");
	if (Error4 == 0) {
		for (int i = 0; i < 10; i++) {
			fscanf_s(file_4,
				"%500[^,], %d, %d, %500[^\n] \n",
				Services[i].service, a,
				&Services[i].code,
				&Services[i].cost,
				Services[i].data, a
			);
		}
		fclose(file_4);
	}
	else {
		cout << "Нет услуг!" << endl;
	}
	Rez();
	return 0;
}
/*
Получить перечень услуг и телефонных номеров
для заданных клиентов, с которыми заключён
договор во 2-м квартале нынешнего года
*/
void Rez()
{
	ofstream fout("Report.txt", ios::out);
	time_t seconds = time(0);
	tm timeinfo;//текущая дата и время
	localtime_s(&timeinfo, &seconds);//текущая дата в секундах

	// Поиск номеров каждого пользователя из списка параметров
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (strcmp(Parametr[i].Ppeople, People[j].people) == 0) {
				Parametr[i].number = People[j].number;
				break;
			}
		}
	}
	// Запись номеров всех услуг в массив
	int64_t serv[10][2];
	for (int i = 0; i < 10; i++) {
		serv[i][0] = Services[i].code;
		serv[i][1] = -1;
	}

	for (int i = 0; i < 10; i++) {
		bool t = false;
		for (int j = 0; j < 10; j++) {
			if (PeopleServices[i].phone == Parametr[j].number) {
				t = true;
				break;
			}
		}
		if (t) {
			if (
				People[i].year == timeinfo.tm_year + 1900 &&
				People[i].month >= 4 && People[i].month <= 6
				) {
				for (int k = 0; k < 10; k++) {
					if (serv[k][0] == PeopleServices[i].Pcode) {
						serv[k][1] = PeopleServices[i].phone;
						break;
					}
				}
			}
		}
	}
	for (int i = 0; i < 10; i++) {
		if (serv[i][1] != -1) {
			for (int j = 0; j < 10; j++) {
				if (Services[j].code == serv[i][0]) {
					fout << Services[j].service << ' ' << serv[i][1] << '\n';
					break;
				}
			}
		}
	}
	fout.close();
}