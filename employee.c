#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MINIMUM_SALARY 20000
#define MAXIMUM_SALARY 100000

char employee_names[100][7] = { "Adam", "Alex", "Aaron", "Ben", "Carl", "Dan", "David", "Edward", "Fred", "Frank", "George", "Hal", "Hank", "Ike", "John", "Jack", "Joe", "Larry", "Monte", "Matthew", "Mark", "Nathan", "Otto", "Paul", "Peter", "Roger", "Roger", "Steve", "Thomas", "Tim", "Ty", "Victor", "Walter"};   

struct Employee
{
    char *name;
    int id;
    int salary;
};

int main()
{
    int i = 0, n = 8;

    int lower_salary = 4;
    int higher_salary = 9;

    int lower_name_index = 0;
    int higher_name_index = 40;
    
    // srand(getpid());
    
        srand ( time(NULL) );

    struct Employee arr[n];

    for (int i = 0; i < n; i++)
    {

        arr[i].id = i;
        int name_index = rand() % (higher_name_index + 1 - lower_name_index) + lower_name_index;
        arr[i].name = employee_names[name_index];
        int salary_multiplier = rand() % (higher_salary + 1 - lower_salary) + lower_salary;
        arr[i].salary = salary_multiplier * 1000;
    }

    FILE *fpt = fopen("employees2.csv", "w+");
    fprintf(fpt, "id, Name, salary\n");
    for (i = 0; i < n; i++)
    {
        fprintf(fpt, "%d, %s, %d\n", arr[i].id, arr[i].name, arr[i].salary);
    }
    fclose(fpt);

    return 0;
}