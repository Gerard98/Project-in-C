#ifndef COURSE_ACTIONS_H_INCLUDED
#define COURSE_ACTIONS_H_INCLUDED
#include "List_Actions.h"


course* delete_course(course* firstC, int ID);
course* add_course(course *firstC);
void edit_course(course* firstC, int ID);
void print_one_course(course *firstC);
void sereach_course(course* firstC);
void sort_course_by_id(course* firstC);
void sort_courses(course* firstC);
void sort_course_by_hours(course *firstC);
void sort_course_by_price(course *firstC);
#endif // COURSE_ACTIONS_H_INCLUDED
