#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define size 1111

struct student_data getLine(char *line);
void displayData(struct student_data data);
void displayOutput(int counter, struct student_data *details);
struct student_data
{

    float cgpa, credit_hours;
    char *first_name, *last_name, *major, *degree, *ta, *advisor;
};

int main()
{
    struct student_data student_details[55];
    char line[size];
    int itr, counter = 0;

    FILE *file_ptr = fopen("students_dataset.csv", "r");
    if (file_ptr == NULL)
    {
        printf("Error reading file students_dataset ");
        exit(-1);
    }
    while (fgets(line, size, file_ptr) != NULL)
    {
        student_details[counter++] = getLine(line);
    }
    fclose(file_ptr);
    displayOutput(counter, student_details);
    return 0;
}

void displayOutput(int counter, struct student_data *data)
{
    char *dataCheck = malloc(1000 * sizeof(char));
    char *advisor_check = malloc(1000 * sizeof(char));
    *dataCheck = *advisor_check = '\0';
    int degreeCount = 0, loc, credit_hours = 0, counter_cse = 0;
    float avg_cgpa_cse = 0.0;
    printf("--------------------------------------------\n");
    printf("Number of Degrees present in students_dataset.csv:\n");
    for (int itr = 0; itr < counter; itr++)
    {
        if (!strstr(dataCheck, data[itr].degree))
        {
            // if(!strstr("Undeclared",data[itr].degree))
            degreeCount++;
            strcat(dataCheck, data[itr].degree);
            strcat(dataCheck, ",");
            // if(!strstr("Undeclared",data[itr].degree))
            printf("%d. %s\n", degreeCount, data[itr].degree);
        }
        // "undeclared" in Degree field  is also counted as one of degree
        // to uncount "Undeclared", uncomment 57 and 61 line
    }

    printf("Total Degree Count : %d\n", degreeCount);
    printf("--------------------------------------------\n");
    printf("      \n");
    struct student_data student_details;

    for (int i = 1; i < counter; i++)
    {
        if (strstr("Computer Science", data[i].major))
        {
            counter_cse++;
            avg_cgpa_cse += data[i].cgpa;
        }
        credit_hours += data[i].credit_hours;
        loc = i;
        while (loc > 0 && (data[loc - 1].cgpa < data[loc].cgpa))
        {
            student_details = data[loc];
            data[loc] = data[loc - 1];
            data[loc - 1] = student_details;
            loc--;
        }
    }
    printf("--------------------------------------------\n");
    printf("Students with top 3 CGPA\n");

    for (int itr = 0; itr < counter; itr++)
    {

        if (itr <= 2)
            printf("%d. %s %s: %.2f\n", itr + 1, data[itr].first_name, data[itr].last_name, data[itr].cgpa);

        else if (data[itr].cgpa == data[itr - 1].cgpa)
            printf("%d. %s %s: %.2f\n", itr + 1, data[itr].first_name, data[itr].last_name, data[itr].cgpa);

        else
            break;
    }
    printf("--------------------------------------------\n");
    printf("      \n");
    printf("--------------------------------------------\n");
    printf("Average Credit Hours:\n");
    printf(" %.2f\n", (credit_hours / (float)counter));
    printf("--------------------------------------------\n");
    printf("      \n");
    printf("--------------------------------------------\n");
    printf("Average CGPA of Computer Science Students:\n");
    printf("%.2f", avg_cgpa_cse / counter_cse);
    printf("      \n");
    printf("--------------------------------------------\n");
    printf("      \n");
    printf("--------------------------------------------\n");
    char *biology = malloc(1000 * sizeof(char)), *math = malloc(1000 * sizeof(char)), *history = malloc(1000 * sizeof(char)),
         *cse = malloc(1000 * sizeof(char)), *ece = malloc(1000 * sizeof(char));
    *biology = *math = *history = *cse = *ece = '\0';
    int biology_adv = 0, math_adv = 0, history_adv = 0, cse_adv = 0, ece_adv = 0;
    for (int itr = 0; itr < counter; itr++)
    {
        if (strstr("ECE", data[itr].major))
        {

            if (!strstr(ece, data[itr].advisor))
            {
                ece_adv++;
                strcat(ece, data[itr].advisor);
            }
        }
        else if (strstr("Computer Science", data[itr].major))
        {
            if (!strstr(cse, data[itr].advisor))
            {
                cse_adv++;
                strcat(cse, data[itr].advisor);
            }
        }
        else if (strstr("Biology", data[itr].major))
        {
            if (!strstr(biology, data[itr].advisor))
            {
                biology_adv++;
                strcat(biology, data[itr].advisor);
            }
        }
        else if (strstr("Math", data[itr].major))
        {
            if (!strstr(math, data[itr].advisor))
            {
                math_adv++;
                strcat(math, data[itr].advisor);
            }
        }
        else if (strstr("History", data[itr].major))
        {
            if (!strstr(history, data[itr].advisor))
            {
                history_adv++;
                strcat(history, data[itr].advisor);
            }
        }
        else
            continue;
    }

    printf("Number of advisory per major: \n");
    printf("Computer Science: %d\n", cse_adv);
    printf("Math: %d\n", math_adv);
    printf("Biology: %d\n", biology_adv);
    printf("ECE: %d\n", ece_adv);
    printf("History: %d\n", history_adv);
    printf("--------------------------------------------\n");
    free(dataCheck);
    free(advisor_check);
    free(biology);
    free(math);
    free(cse);
    free(ece);
    free(history);
}

struct student_data getLine(char *line)
{
    struct student_data data;
    data.first_name = strdup(strtok(line, ","));
    data.last_name = strdup(strtok(NULL, ","));
    data.major = strdup(strtok(NULL, ","));
    data.degree = strdup(strtok(NULL, ","));
    data.cgpa = atof(strtok(NULL, ","));
    data.credit_hours = atof(strtok(NULL, ","));
    data.ta = strdup(strtok(NULL, ","));
    data.advisor = strdup(strtok(NULL, ","));

    return data;
}