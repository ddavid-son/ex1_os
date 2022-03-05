#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "stdbool.h"

typedef struct student
{
    char name[11];
    int grades[10];
    int numOfGrades;
} student;

student *students;
int numOfStudents = 0;

int main(int argc, char *argv[])
{

    // init students array
    students = (student *)malloc(sizeof(student) * 16); // todo: add dynamic allocation

    // read and handle input
    readAllDataFromFiles(argc, argv);
    sortGrades();

    // write student array to file merged.txt
    writeToFile();

    return 0;
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
    // read all file names form argv
    char *fileName = malloc(sizeof(char) * numOfFiles);
    for (int i = 1; i < numOfFiles; i++)
    {
        strcpy(fileName[i - 1], argv[i]);
        printf("%s\n", fileName); // for denugging
    }

    // read all lines form files
    for (int i = 0; i < numOfFiles; i++)
    {
        FILE *fp = fopen(fileName[i], "r");
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
                addLineToStudent(line);
            }
        }
        fclose(fp);
    }
}

void addLineToStudent(char *studentData)
{
    char *name = strtok(studentData, " ");

    if (!findIfStudentExists(name))
    {
        createAndAddStudent(name);
    }

    for (int i = 0; i < numOfStudents; i++)
    {
        if (strcmp(students[i].name, name) == 0)
        {
            char *grades = strtok(NULL, " ");
            while (grades != NULL)
            {
                students[i].grades[students[i].numOfGrades] = atoi(grades);
                grades = strtok(NULL, " ");
                students[i].numOfGrades++;
            }

            return;
        }
    }
}

void createAndAddStudent(char *name)
{
    student *student = malloc(sizeof(student));
    strcpy(student->name, name);
    student->numOfGrades = 0;
    numOfStudents++;
}

bool findIfStudentExists(name)
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

// ---------------------------------------------- tzvi report format ----------------------------------------------------- //
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
// ---------------------------------------------- tzvi report format ----------------------------------------------------- //
