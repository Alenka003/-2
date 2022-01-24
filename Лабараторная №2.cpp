#include<iostream>;
using namespace std;

int main ()
{
	setlocale(LC_ALL, "ru");
	int x[10];
	for (int i = 0; i < 10; i++) {
		int q;
		cout << "Введите "<< i <<" элемент: \n";
		cin >> q;
		x[i] = q;
	}
	int y = x[0];
	int min = x[0];
	int max = x[0];
	int k = -1;
	for (int i = 1; i < 10; i++) {
		y += x[i];
		k += 1;
		if (min > x[i]) { min = x[i]; }
		else if (max < x[i]) { max = x[i]; }
	}
	float s = (float)(y-min-max) / k;
	cout << s << endl;

	return 0;
}