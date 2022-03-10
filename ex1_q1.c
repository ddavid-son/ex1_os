#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "stdbool.h"
#include <unistd.h>

typedef struct student
{
    char name[11];
    int grades[10];
    int numOfGrades;
} student;

student *students;
int numOfStudents = 0;
int arraySize = 16;

void sortGrades();
int compare(const void *a, const void *b);
void writeToFile();
void readAllDataFromFiles(int numOfFiles, char *argv[]);
void addLineToStudent(char *studentData);
void resize();
void createAndAddStudent(char *name);
bool findIfStudentExists(char* name);
void report_input_file(const char *file_name, int num_stud);
void report_data_summary(int num_stud, double avg);
void printAllStudents();
double getAvg();

int main(int argc, char *argv[])
{
    char* names[] = {"g","first.txt" , "second.txt" , "third.txt" , "forth.txt" };
    // init students array
    students = (student *)malloc(sizeof(student) * 16); // todo: add dynamic allocation

    // read and handle input
    readAllDataFromFiles(4/*argc*/, names/*argv*/);
    sortGrades();
    printAllStudents();
    
    report_data_summary(numOfStudents,getAvg());

    // write student array to file merged.txt
    writeToFile();

    return 0;
}

double getAvg(){
    int sum = 0;
    int numOfGrades = 0;
    for (int i = 0; i < numOfStudents; i++)
    {
        for (int j = 0; j < students[i].numOfGrades ; i++)
        {
            sum+= students[i].grades[j];
            numOfGrades++;
        }
    }
    return (double)sum / numOfGrades;    
}

void printAllStudents(){
    for (int i = 0 ; i < numOfStudents ; i++){
        printf("%s ", students[i].name);
        for (int j = 0; j < students[i].numOfGrades; j++)
        {
            printf("%d ", students[i].grades[j]);
        }
        printf("\n");
    }
}

void sortGrades()
{
    for (int i = 0; i < numOfStudents; i++)
    {
        qsort(students[i].grades, students[i].numOfGrades, sizeof(int), compare);
    }
}

int compare(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}

void writeToFile()
{
    FILE *fp;
    fp = fopen("merged.txt", "w");
    for (int i = 0; i < numOfStudents; i++)
    {
        fprintf(fp, "%s ", students[i].name);
        for (int j = 0; j < students[i].numOfGrades; j++)
        {
            fprintf(fp, "%d ", students[i].grades[j]);
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
}

void readAllDataFromFiles(int numOfFiles, char *argv[])
{
    int numOfStudnetInfile=0;
    for (int i = 1; i <= numOfFiles; i++)
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
                addLineToStudent(line);
            }
        }
        fclose(fp);
        report_input_file(argv[i], numOfStudnetInfile);
        numOfStudnetInfile = 0;
    }
}

void addLineToStudent(char *studentData)
{
    char *name = strtok(studentData, " ");
    int x;
    if (!findIfStudentExists(name))
    {
        //resize();
        createAndAddStudent(name);
    }

    for (int i = 0; i < numOfStudents; i++)
    {
        if (strcmp(students[i].name, name) == 0)
        {
            char *grades = strtok(NULL, " ");
            while (grades != NULL && (*grades) != '\n')
            {
                students[i].grades[students[i].numOfGrades] = atoi(grades);
                grades = strtok(NULL, " ");
                students[i].numOfGrades++;
            }

            return;
        }
    }
}

void resize(){
    if (numOfStudents == arraySize-1)
    {
        arraySize *= 2;
        students = (student *)realloc(students, sizeof(student) * arraySize);
    }
}

void createAndAddStudent(char *name)
{
    resize();
    student *student = malloc(sizeof(student));
    strcpy(student->name, name);
    student->numOfGrades = 0;
    students[numOfStudents] = *student;
    numOfStudents++;
}

bool findIfStudentExists(char* name)
{
    for (int i = 0; i < numOfStudents; i++)
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
