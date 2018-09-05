#ifndef STUDENT_ACTIONS_H_INCLUDED
#define STUDENT_ACTIONS_H_INCLUDED
#include "List_Actions.h"


void add_student_to_list(student **firstS, char *name, char *surname, int *group_ID, char *email, char *phone_number, char *pesel, char *address, int amount);
student* load_students(student *firstS);
student* add_student(student *firstS, course *firstC, group *firstG);
void print_students(student *firstS);
student* delete_student(student *firstS, int *pesel);
void edit_student(student *firstS, group *firstG, char *pesel);
void print_one_student(student *firstS);
void sereach_student(student *firstS);
void sort_students_by_alph(student *firstS);
void sort_students_by_birth_day(student *firstS);
void sort_students(student *firstS);
#endif // STUDENT_ACTIONS_H_INCLUDED
