#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#pragma warning(disable:4996)

unsigned count_of_variants = 0;
char str[100] = { 0 }, letters[10] = { 0 };

void print(int* values, int n)
{
	for (int i = 0; i < n; i++)
		printf("%d ", values[i]);
	printf("\n");
}

int beginning(char symbol)
{
	if (str[0] == symbol) return 1;
	for (int i = 1; i < strlen(str); i++)
	{
		if ((str[i] == '+') || (str[i] == '='))
		{
			i++;
			if (str[i] == symbol)
				return 1;
		}
	}
	return 0;
}

void swap(int* a, int i, int j)
{
	int s = a[i];
	a[i] = a[j];
	a[j] = s;
}

int next(int* values, int n, int m)
{
	int i;
	do
	{
		i = n - 1;
		while (i != -1 && values[i] >= values[i + 1]) i--;
		if (i == -1)
			return 0;
		int k = n - 1;
		while (values[i] >= values[k]) k--;
		swap(values, i, k);
		int l = i + 1, r = n - 1;
		while (l < r)
			swap(values, l++, r--);
	} while (i > m - 1);
	return 1;
}

int position(char symbol)
{
	for (int i = 0; i < strlen(letters); i++)
	{
		if (letters[i] == symbol)
			return i;
	}
}

int find_sum(int* sum, int* values, int* length, int count)
{
	for (int i = 0, pos = 0; length[i] != 0; i++)
	{
		sum[i] = 0;
		int k = pow(10, length[i]);
		for (int j = length[i]; j > 0; j--)
		{
			k /= 10;
			sum[i] += (values[position(str[pos])] * k);
			pos++;
		}
		if ((str[pos] == '+') || (str[pos] == '='))
			pos++;
	}
	int summa = 0;
	for (int i = 0; i < count; i++)
		summa += sum[i];
	if (summa == sum[count])
	{
		for (int i = 0; i < strlen(str); i++)
		{
			if (str[i] == '+') printf("+");
			else if (str[i] == '=') printf("=");
			else printf("%d", values[position(str[i])]);
		}
		printf("\n\nVariants: %d\n", count_of_variants);
		return 1;
	}
	return 0;
}

void variations(int* values, int n, int m, int* length, int count)
{
	int sum[10] = { 0 };
	for (int i = 0; i < n; i++)
		values[i] = i;
	if (m > 1) swap(values, 0, 1);
	if (find_sum(&sum, values, length, count)) return;
	if (n >= m)
	{
		while (next(values, n, m))
		{
			for (int i = 0; i < m; i++)
				if ((values[i] == 0) && (beginning(letters[i])) && (i < m - 1))
					swap(values, i, i + 1);
			if (find_sum(&sum, values, length, count)) return;
			count_of_variants++;
		}
	}
	return 0;
}


int main()
{
	int length[10] = { 0 }, values[10] = { 0 };;
	int count = 0, success = 1;
	fscanf(stdin, "%s", str);
	time_t start_time = clock();
	for (int i = 0, j = 0; i < strlen(str); i++)
	{
		if ((str[i] == '+') || (str[i] == '='))
			count++;
		else length[count]++;
		for (j = 0; j < strlen(letters); j++)
			if ((str[i] == letters[j]) || (str[i] == '+') || (str[i] == '='))
			{
				success = 0;
				break;
			}
		if (success == 1)
			letters[j] = str[i];
		success = 1;
	}
	variations(values, 10, strlen(letters), length, count);
	time_t end_time = clock();
	printf("\nTime: %.3f sec\n", ((float)end_time - (float)start_time) / 1000);
}