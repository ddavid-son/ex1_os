#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "stdbool.h"
#include <unistd.h>

typedef struct student
{
    char name[11];
    int grades[10];
    int grades_num;
} student;

student *students;
int studs_num = 0;
int arr_size = 16;

void sort_grades();
int compare(const void *a, const void *b);
void write_to_file();
void get_stud_data(int numOfFiles, char *argv[]);
void add_grades(char *studentData);
void resize();
void create_new_stud(char *name);
bool stud_exists(char* name);
void report_input_file(const char *file_name, int num_stud);
void report_data_summary(int num_stud, double avg);
void printAllStudents();
double calc_avg();

int main(int argc, char *argv[])
{
    // init students array
    students = (student *)malloc(sizeof(student) * 100);

    // read and handle input
    get_stud_data(argc, argv);

    sort_grades();
    report_data_summary(studs_num,calc_avg());

    // write student array to file merged.txt
    write_to_file();

    return 0;
}

double calc_avg(){
    int sum = 0;
    int numOfGrades = 0;
    for (int i = 0; i < studs_num; i++)
    {
        for (int j = 0; j < students[i].grades_num ; j++)
        {
            sum+= students[i].grades[j];
            numOfGrades++;
        }
    }
    return (double)sum / numOfGrades;    
}

void sort_grades()
{
    for (int i = 0; i < studs_num; i++)
    {
        qsort(students[i].grades, students[i].grades_num, sizeof(int), compare);
    }
}

int compare(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}

void write_to_file()
{
    FILE *fp;
    fp = fopen("merged.txt", "w");
    for (int i = 0; i < studs_num; i++)
    {
        fprintf(fp, "%s ", students[i].name);
        for (int j = 0; j < students[i].grades_num; j++)
        {
            fprintf(fp, "%d ", students[i].grades[j]);
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
}

void get_stud_data(int numOfFiles, char *argv[])
{
    int numOfStudnetInfile=0;
    for (int i = 1; i < numOfFiles; i++)
    {
        FILE *fp = fopen(argv[i], "r");
        if (fp == NULL) 
        {
            printf("Error Reading File\n");
            exit(1);
        }
        char *line = malloc(sizeof(char) * 81);
        while (fgets(line, 81, fp) != NULL)
        {
            if (line[0] == '\n')
            {
                continue;
            }
            else
            {
                numOfStudnetInfile++;
                add_grades(line);
            }
        }
        fclose(fp);
        report_input_file(argv[i], numOfStudnetInfile);
        numOfStudnetInfile = 0;
    }
}

void add_grades(char *studentData)
{
    char *name = strtok(studentData, " ");
    if (!stud_exists(name))
    {
        create_new_stud(name);
    }

    for (int i = 0; i < studs_num; i++)
    {
        if (strcmp(students[i].name, name) == 0)
        {
            char *grades = strtok(NULL, " ");
            while (grades != NULL && (*grades) != '\n' && (*grades) != '\r')
            {
                students[i].grades[students[i].grades_num] = atoi(grades);
                grades = strtok(NULL, " ");
                students[i].grades_num++;
            }

            return;
        }
    }
}

void resize(){
    if (studs_num == arr_size-1)
    {
        arr_size *= 2;
        students = (student *)realloc(students, sizeof(student) * arr_size);
    }
}

void create_new_stud(char *name)
{
    student stud;
    strcpy(stud.name, name);
    stud.grades_num = 0;
    students[studs_num++] = stud;
}

bool stud_exists(char* name)
{
    for (int i = 0; i < studs_num; i++)
    {
        if (strcmp(students[i].name, name) == 0)
        {
            return true;
        }
    }
    return false;
}

// ---------------------------------------------- Tzvi report format ----------------------------------------------------- //
void report_input_file(const char *file_name, int num_stud)
{
    fprintf(stderr, "process: %d file: %s number of students: %d\n",
            getpid(), file_name, num_stud);
}
void report_data_summary(int num_stud, double avg)
{
    fprintf(stderr, "process: %d data summary - number of students:"
                    " %d grade average: %.2f\n",
            getpid(), num_stud, avg);
}
// ---------------------------------------------- Tzvi report format ----------------------------------------------------- //
