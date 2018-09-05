#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "List_Actions.h"


void add_course_to_list(course **firstC, int id, int hours, int price, char course_name[50], char course_description[200]){
course *p = (course*) malloc(sizeof(course));
p->id = id;
p->hours = hours;
p->price = price;
strcpy(p->course_name ,course_name);
strcpy(p->course_description ,course_description);
p->next = *firstC;
*firstC = p;
}

void add_group_to_list(group **firstG, int id, char *start_date, char *end_date, int courseG){
group *p = (group*)malloc(sizeof(group));
p->group_id = id;
strcpy(p->start_date, start_date);
strcpy(p->end_date, end_date);
p->courseG = courseG;
p->next = *firstG;
*firstG = p;
}

course* load_courses(course *firstC){

FILE * f1=fopen("Files/Courses.txt", "r");
if( f1 == NULL)return;
course *t = (course*)malloc(sizeof(course));
while( fscanf(f1, "%d", &t->id) == 1){
    fscanf(f1, "%d", &t->hours);
    fscanf(f1, "%d", &t->price);
    char trash;
    fscanf(f1, "%d", &trash);
    free(trash);
    fgets(t->course_name, 50, f1);
    fgets(t->course_description, 200, f1);
    add_course_to_list(&firstC, t->id, t->hours, t->price, t->course_name, t->course_description);
}

fclose(f1);
return firstC;
}

group* load_groups(group *firstG){
FILE * f2=fopen("Files/Groups.txt", "r");
if( f2 == NULL) return;
group *t = (group*)malloc(sizeof(group));

while( fscanf(f2, "%d" , &t->group_id ) == 1){
    fscanf(f2, "%s" , t->start_date);
    fscanf(f2, "%s" , t->end_date);
    fscanf(f2, "%d", &t->courseG);
    add_group_to_list(&firstG, t->group_id, t->start_date, t->end_date, t->courseG);
}

fclose(f2);
return firstG;
}

void print_courses(course *firstC){
if(!firstC)printf("There are no courses here!\n");
while(firstC){
    printf("Cours ID: %d\n",firstC->id);
    printf("%s",firstC->course_name);
    printf("Hours: %d\n",firstC->hours);
    printf("Price: %d\n",firstC->price);
    printf("%s\n\n",firstC->course_description);
    firstC = firstC->next;
}
}

void print_groups(group *firstG){
if(!firstG)printf("There are no groups here!\n");
while(firstG){
    printf("Group ID: %d\n",firstG->group_id);
    printf("Group take a part of this course: %d\n",firstG->courseG);
    printf("Group Start Date: %s\n",firstG->start_date);
    printf("Group End Date: %s\n\n",firstG->end_date);
    firstG = firstG->next;
}
}

group* add_group(group *firstG, course *firstC){
group *tmp = (group*)malloc(sizeof(group));
group *tmp2;
tmp2 = firstG;
int local_course;
int b;
bool stop=false;
bool stop2=false;
// START DATE
while(!stop2){
printf("Write start date:  (dd.mm.rr)\n");
stop = false;
while(!stop){
    fflush(stdin);
    fgets(tmp->start_date,9,stdin);
    stop = check_date(tmp->start_date);
}
// END DATE
printf("Write end date: (dd.mm.rr)\n");
stop = false;
while(!stop){
    fflush(stdin);
    fgets(tmp->end_date,9,stdin);
    stop = check_date(tmp->end_date);
}
stop2 = check_dates2(tmp->start_date, tmp->end_date);
}

// ID
printf("Write an ID of group: ");
printf("( ");
while(tmp2){
    printf("%d ",tmp2->group_id);
    tmp2 = tmp2->next;
}
printf(")\n");
do{
    stop = true;
    tmp2 = firstG;
    scanf("%d",&tmp->group_id);
    while(tmp2){
        if(tmp2->group_id == tmp->group_id){
            stop=false;
            printf("Error! The group with this ID already exist!\n");
            break;
        }
    tmp2 = tmp2->next;
}
}while(!stop);
printf("Take a course for this group!  ");
printf("(Write ID! If you need to check courses write '0')\n");
scanf("%d",&local_course);
if(local_course == 0){
    print_courses(firstC);
    scanf("%d",&local_course);
}


add_group_to_list(&firstG ,tmp->group_id ,tmp->start_date, tmp->end_date, local_course);
return firstG;
}

void print_taken_group(student *firstS, group *firstG){
int local_menu,i=1;
int local_groups[50];
bool check;
group *tmpG = firstG;
student *tmpS = firstS;
while(tmpG){
    printf("%d)Group with ID: %d\n",i,tmpG->group_id);
    local_groups[i] = tmpG->group_id;
    i++;
    tmpG = tmpG->next;
}
scanf("%d",&local_menu);
while(local_menu > i || local_menu < 1){
    printf("Error! You must take number between 1-%d\n",i);
    scanf("%d",&local_menu);
}
while(tmpS){
    for(int j=0 ; j < tmpS->amount ; j++){
        if(tmpS->group_ID[j] == local_groups[local_menu]){
            print_one_student(tmpS);
            check = true;
            break;
        }
    }
tmpS = tmpS->next;
}
if( check != true){
    printf("Group does not have any students yet\n");
}
}

void sort_groups_by_id(group *firstG){
group *tmp = NULL;
group *tmp2 = NULL;
group *tmp3 = (group*)malloc(sizeof(group));

for(tmp = firstG; tmp != NULL; tmp = tmp->next)
    for(tmp2 = tmp; tmp2 != NULL; tmp2 = tmp2->next){
        if(tmp->group_id > tmp2->group_id){
            tmp3->group_id = tmp->group_id;
            tmp->group_id = tmp2->group_id;
            tmp2->group_id = tmp3->group_id;

            strcpy(tmp3->start_date, tmp->start_date);
            strcpy(tmp->start_date, tmp2->start_date);
            strcpy(tmp2->start_date, tmp3->start_date);

            strcpy(tmp3->end_date, tmp->end_date);
            strcpy(tmp->end_date, tmp2->end_date);
            strcpy(tmp2->end_date, tmp3->end_date);

            tmp3->courseG = tmp->courseG;
            tmp->courseG = tmp2->courseG;
            tmp2->courseG = tmp3->courseG;
        }
    }
}

void sort_groups_by_end_date(group *firstG){
group *tmp = NULL;
group *tmp2 = NULL;
group *tmp3 = (group*)malloc(sizeof(group));

for(tmp = firstG; tmp != NULL; tmp = tmp->next)
    for(tmp2 = tmp; tmp2 != NULL; tmp2 = tmp2->next){
        if(check_dates3(tmp->end_date, tmp2->end_date) == false){
            tmp3->group_id = tmp->group_id;
            tmp->group_id = tmp2->group_id;
            tmp2->group_id = tmp3->group_id;

            strcpy(tmp3->start_date, tmp->start_date);
            strcpy(tmp->start_date, tmp2->start_date);
            strcpy(tmp2->start_date, tmp3->start_date);

            strcpy(tmp3->end_date, tmp->end_date);
            strcpy(tmp->end_date, tmp2->end_date);
            strcpy(tmp2->end_date, tmp3->end_date);

            tmp3->courseG = tmp->courseG;
            tmp->courseG = tmp2->courseG;
            tmp2->courseG = tmp3->courseG;
        }
    }

}

void sort_groups_by_start_date(group *firstG){
group *tmp = NULL;
group *tmp2 = NULL;
group *tmp3 = (group*)malloc(sizeof(group));

for(tmp = firstG; tmp != NULL; tmp = tmp->next)
    for(tmp2 = tmp; tmp2 != NULL; tmp2 = tmp2->next){
        if(check_dates3(tmp->start_date, tmp2->start_date) == false){
            tmp3->group_id = tmp->group_id;
            tmp->group_id = tmp2->group_id;
            tmp2->group_id = tmp3->group_id;

            strcpy(tmp3->start_date, tmp->start_date);
            strcpy(tmp->start_date, tmp2->start_date);
            strcpy(tmp2->start_date, tmp3->start_date);

            strcpy(tmp3->end_date, tmp->end_date);
            strcpy(tmp->end_date, tmp2->end_date);
            strcpy(tmp2->end_date, tmp3->end_date);

            tmp3->courseG = tmp->courseG;
            tmp->courseG = tmp2->courseG;
            tmp2->courseG = tmp3->courseG;
        }
    }
}

void sort_groups(group *firstG){
bool stop = true;
while(stop){
printf("By what you want to sort groups\n");
printf("1) ID\n");
printf("2) Start date\n");
printf("3) End date\n");
printf("4) If you dont wanna sort groups\n");
int local_menu;
scanf("%d",&local_menu);
while(local_menu < 1 || local_menu > 3){
    printf("Error! You need to write a digit between 1-3\n");
    scanf("%d",&local_menu);
}
stop = false;
switch(local_menu){
case 1:
    sort_groups_by_id(firstG);
    break;
case 2:
    sort_groups_by_start_date(firstG);
    break;
case 3:
    sort_groups_by_end_date(firstG);
    break;
case 4:
    return;
}
}
}

