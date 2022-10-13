#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <omp.h>

#define FILENAME_LEN 50
#define FILENAME_NUM 100
#define HASH_TABLE_MAX_SIZE 100000
#define MAX_LINE_SIZE 100000

int hash_size[FILENAME_NUM];

typedef struct employees
{
	char id[50];
	char name[50];
	int salary;
} dict;

dict employees[FILENAME_NUM][MAX_LINE_SIZE];

// int hash_size[FILENAME_NUM];
typedef struct HashTable Node;
struct HashTable
{
	char *name;
	int salary;
	Node *pNext;
};

Node *hashTable[FILENAME_NUM + 1][HASH_TABLE_MAX_SIZE];

void readFunc(const char *filename, int index)
{
	FILE *fp = fopen(filename, "r");
	if (fp == NULL)
	{
		printf("input file is invalid !");
		return;
	}
	char buff[1024];
	int row_count = 0;
	int field_count = 0;

	int i = 0;
	while (fgets(buff, 1024, fp))
	{
		field_count = 0;
		row_count++;
		if (row_count == 1)
			continue;
		char *field = strtok(buff, ",");
		while (field)
		{
			if (field_count == 0)
				strcpy(employees[index][i].id, field);
			if (field_count == 1)
				strcpy(employees[index][i].name, field);
			if (field_count == 2)
				employees[index][i].salary = strtol(field, &field, 10);
			field = strtok(NULL, ",");
			field_count++;
		}
		i++;
	}
	fclose(fp);
}

void printValues(int file_num)
{
	for (int index = 0; index < file_num; index++)
	{
	printf("For File  %d\n", index + 1);
	for (int i = 0; i < 10; i++)
	{
		printf("id->%s, name->%s, salary->%d\n", employees[index][i].id, employees[index][i].name, employees[index][i].salary);
	}
	}
}

void initializeHashTablesFunc(int index)
{
	char *name = "";
	int salary = 0;
	unsigned int pos = 0;

	Node *NewNode = (Node *)malloc(sizeof(Node));
	memset(NewNode, 0, sizeof(Node));
	NewNode->name = (char *)malloc(sizeof(char) * (strlen(name) + 1));

	strcpy(NewNode->name, name);
	NewNode->salary = salary;

	hashTable[index][pos] = NewNode;
}

void hashTablePrintFunc(int fileNumbers)
{
	int i = 0;
	Node *p;
	printf("=========== content of hash table ===========\n");
	for (int i = 0; i < fileNumbers; i++)
	{
		printf("File Number:%d\n",i+1);
		for (int j = 0; j < 100; j++)
		{
			p = hashTable[i][j];
			if (p)
				printf("Name->%s Salary->%d\n", p->name, p->salary);
		}
	}
}

void replaceHashAt(dict employee, int index)
{
	char *name = employee.name;
	int salary = employee.salary;

	Node *NewNode = (Node *)malloc(sizeof(Node));
	memset(NewNode, 0, sizeof(Node));
	NewNode->name = (char *)malloc(sizeof(char) * (strlen(name) + 1));

	strcpy(NewNode->name, name);
	NewNode->salary = salary;

	hashTable[index][0] = NewNode;
}
void concatHashAt(dict employee, int index)
{
	char *name = employee.name;
	int salary = employee.salary;


	Node *NewNode = (Node *)malloc(sizeof(Node));
	memset(NewNode, 0, sizeof(Node));
	NewNode->name = (char *)malloc(sizeof(char) * (strlen(name) + 1));

	strcpy(NewNode->name, name);
	NewNode->salary = salary;

	int lastPos = 0;

	for (int i = 0; i < MAX_LINE_SIZE; i++)
	{
		if (hashTable[index][i] != NULL)
		{
			lastPos++;
		}
	}

	hashTable[index][lastPos] = NewNode;

	hash_size[index]++;
}
void mapperFunc(int file_num)
{
	for (int index = 0; index < file_num; index++)
	{
		int max_salary = 0;
		for (int i = 0; i < 100; i++)
		{
			dict employee = employees[index][i];
			if (employee.salary > max_salary)
			{
				max_salary = employee.salary;
				replaceHashAt(employee, index);
			}
			else if (employee.salary == max_salary)
			{
				concatHashAt(employee, index);
			}
		}
	}
}

int main()
{
	int file_num = 0;
	FILE *read_filename = fopen("filename_list.txt", "r");
	char **filename_list_array = (char **)malloc(sizeof(char *) * 100);
	int i, j;

	for (i = 0; i < FILENAME_NUM; i++)
	{
		filename_list_array[i] = (char *)malloc(sizeof(char) * 50);
	}

	if (read_filename == NULL)
	{
		printf("open the file incorrectly !");
		return 0;
	}
	while (!feof(read_filename))
	{
		fscanf(read_filename, "%s\n", filename_list_array[file_num]);
		file_num++;
	}

	for (i = 0; i < file_num; i++) readFunc(filename_list_array[i], i);

	// printValues(file_num);
	mapperFunc(file_num);

	hashTablePrintFunc(file_num);

	// Clearing
	for (i = 0; i < FILENAME_NUM; i++)
	{
		free(filename_list_array[i]);
	}
	free(filename_list_array);

	return 0;
}