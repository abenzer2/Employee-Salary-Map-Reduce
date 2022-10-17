#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MINIMUM_SALARY 20000
#define MAXIMUM_SALARY 100000

char employee_names[100][7] = { "Adam", "Alex", "Aaron", "Ben", "Carl", "Dan", "David", "Edward", "Fred", "Frank", "George", "Hal", "Hank", "Ike", "John", "Jack", "Joe", "Larry", "Monte", "Matthew", "Mark", "Nathan", "Otto", "Paul", "Peter", "Roger", "Roger", "Steve", "Thomas", "Tim", "Ty", "Victor", "Walter"};   
char departments[4][20] ={"Finance", "Human Resource", "IT", "Manager"};
struct Employee
{
    char *name;
    int id;
    int salary;
    char *department;
};

int main()
{
    int i = 0;

    // Change number of employees here
    int n = 8;

    int lower_salary = 4;
    int higher_salary = 18;
    

    int lower_name_index = 0;
    int higher_name_index = 20;

    
    int lower_department_index = 0;
    int higher_department_index = 3;
    
    
    srand ( time(NULL) );

    struct Employee arr[n];

    for (int i = 0; i < n; i++)
    {

        arr[i].id = i;
        int name_index = rand() % (higher_name_index + 1 - lower_name_index) + lower_name_index;
        arr[i].name = employee_names[name_index];
        int department_index = rand() % (higher_department_index + 1 - lower_department_index) + lower_department_index;
        arr[i].department = departments[department_index];
        int salary_multiplier = rand() % (higher_salary + 1 - lower_salary) + lower_salary;
        arr[i].salary = salary_multiplier * 1000;
    }

    // Change Generated File name here
    char *filename = "employees3.csv";
    FILE *fpt = fopen(filename, "w+");
    fprintf(fpt, "id, Name, salary, department\n");
    for (i = 0; i < n; i++)
    {
        fprintf(fpt, "%d, %s, %d, %s\n", arr[i].id, arr[i].name, arr[i].salary, arr[i].department);
    }
    fclose(fpt);

    return 0;
}