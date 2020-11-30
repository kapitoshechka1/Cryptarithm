#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#pragma warning(disable:4996)

void print(int* values, int n)
{
	for (int i = 0; i < n; i++)
		printf("%d ", values[i]);
	printf("\n");
}

void begin_end(unsigned* begin, char* str, char* letters, int letter_len, int str_len)
{
	begin[0] = 1;
	for (int i = 1; i < str_len; i++)
	{
		begin[0] = 1;
		for (int i = 1; i < str_len; i++)
		{
			if ((str[i] == '+') || (str[i] == '='))
			{
				i++;
				for (int j = 0; j < letter_len; j++)
					if (letters[j] == str[i])
						begin[j] = 1;
				if (str[i - 1] == '=') return;
			}
		}
	}
}

void char_swap(char* a, int i, int j)
{
	char s = a[i];
	a[i] = a[j];
	a[j] = s;
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

void find_positions(unsigned* positions, char* str, char* letters, int letter_len, int str_len)
{
	for (int i = 0; i < str_len; i++)
		for (int j = 0; j < letter_len; j++)
			if (letters[j] == str[i])
				positions[i] = j;
}

int position(char* letters, char symbol, int letter_len)
{
	for (int i = 0; i < letter_len; i++)
	{
		if (letters[i] == symbol)
			return i;
	}
}

int equal_length(int* length, int count)
{
	for (int i = 1; i < count; i++)
		if (length[i] != length[i - 1]) return 0;
	if (length[count] != length[0] + 1) return 0;
	return 1;
}

int find_sum(char* str, int* values, int* positions, int* length, int str_len, int count)
{
	int sum[10] = { 0 };
	for (int i = count, pos = str_len - 1; i >= 0; i--)
	{
		sum[i] = 0;
		int k = 1;
		for (int j = length[i]; j > 0; j--)
		{
			sum[i] += (values[positions[pos]] * k);
			k *= 10;
			pos--;
		}
		if (sum[i] > sum[count]) return 0;
			pos--;
	}
	int summa = 0;
	for (int i = 0; i < count; i++)
		summa += sum[i];
	if (summa == sum[count])
	{
		for (int i = 0; i < str_len; i++)
		{
			if (str[i] == '+') printf("+");
			else if (str[i] == '=') printf("=");
			else printf("%d", values[positions[i]]);
		}
		return 1;
	}
	return 0;
}

void variations(char* str, int n)
{
	unsigned count_of_variants = 0;
	char letters[10] = { 0 };
	int sum_first = 0;
	int length[10] = { 0 }, values[11] = { 0 };
	int count = 0, success = 1;
	int str_len = strlen(str);
	for (int i = 0, j = 0; i < str_len; i++)
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
		if (str[i] == '=')
			sum_first = str[i + 1];
		success = 1;
	}
	int letter_len = strlen(letters);
	unsigned begin[10] = { 0 }, positions[100] = { 0 };
	for (int i = 0; i < n; i++)
		values[i] = i;
	if (equal_length(length, count))
		char_swap(letters, position(letters, sum_first, letter_len), 0);
	swap(values, 0, 1);
	find_positions(&positions,str, letters, letter_len, str_len);
	begin_end(&begin, str, letters, letter_len, str_len);
	if (find_sum(str, values, positions, length, str_len, count)) return;
	if (n >= letter_len)
	{
		while (next(values, n, letter_len))
		{
			int sum_last_digits = 0;
			for (int i = 0; i < letter_len; i++)
			{
				if ((values[i] == 0) && (begin[i]) && (i < letter_len - 1))
					swap(values, i, i + 1);
			}
			count_of_variants++;
			if (find_sum(str, values, positions, length, str_len, count)) return;
		}
	}
	printf("\n\nVariants: %d\n", count_of_variants);
	return;
}

int main()
{
	char str[100] = { 0 };
	fscanf(stdin, "%s", str);
	time_t start_time = clock();
	variations(str, 10);
	time_t end_time = clock();
	printf("\nTime: %.3f sec\n", ((float)end_time - (float)start_time) / 1000);
}