#ifndef CONTROL_H_INCLUDED
#define CONTROL_H_INCLUDED
#include "List_Actions.h"


bool only_letter(char *tab);
bool only_numbers(char *tab);
bool check_date(char *tab);
bool check_dates2(char *start, char *stop);
void save_changes(course* firstC, group* firstG, student* firstS);
bool check_birth_date(char *date1, char *date2);
bool check_alph(char *name1, char *name2);




#endif // CONTROL_H_INCLUDED
