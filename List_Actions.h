#ifndef LIST_ACTIONS_H_INCLUDED
#define LIST_ACTIONS_H_INCLUDED
#define true 1
#define false 0

typedef int bool;

typedef struct student{
char name[15];
char surname[15];
char pesel[15];
char address[50];
char email[50];
char phone_number[15];
int group_ID[50];
int amount;
struct student *next;
}student;

typedef struct group{
int group_id;
char start_date[10];
char end_date[10];
int courseG;
struct group *next;
}group;

typedef struct course{
int id;
int hours;
int price;
char course_name[50];
char course_description[200];
struct course *next;
}course;

course* load_courses( course *firstC );
group* load_groups( group *firstC );
void add_course_to_list(course ** firstC, int id, int hours, int price, char course_name[50], char course_description[200]);
void print_courses(course *firstC);
void print_groups(group *firstG);
void print_taken_group(student *firstS, group *firstG);
void add_group_to_list(group **firstG, int id, char *start_date, char *end_date, int courseG);
group* add_group(group *firstG, course *firstC);
void sort_groups_by_start_date(group *firstG);
void sort_groups_by_id(group *firstG);
void sort_groups_by_end_date(group *firstG);
void sort_groups(group *firstG);

#endif // LIST_ACTIONS_H_INCLUDED
