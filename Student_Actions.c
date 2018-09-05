#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define true 1
#define false 0
#include "Student_Actions.h"
#include "List_Actions.h"



void add_student_to_list(student **firstS, char *name, char *surname, int *group_ID, char *email, char *phone_number, char *pesel, char *address,int amount){

student *p = (student*)malloc(sizeof(student));

strcpy(p->pesel, pesel);
strcpy(p->address, address);
strcpy(p->phone_number, phone_number);
strcpy(p->name, name);
strcpy(p->surname, surname);
p->amount = amount;
int i=0;

while(i < amount){
    p->group_ID[i] = group_ID[i];
    i++;
}
strcpy(p->email, email);
p->next = *firstS;
*firstS = p;

}

student* load_students(student *firstS){

FILE * f3=fopen("Files/Students.txt","r");
if(f3 == NULL)return;
student *p = (student*)malloc(sizeof(student));
int a=1,i=0;
while(fscanf(f3, "%s", p->name) == 1){
    fscanf(f3,"%s", p->surname);
    while(a){
        if(fscanf(f3,"%d",&p->group_ID[i]) == 1)i++;
        else a=0;
    }
    fflush(stdin);
    p->amount = i;
    fscanf(f3,"%s", p->email);
    fscanf(f3,"%s", p->pesel);
    fscanf(f3,"%s", p->phone_number);
    fgets(p->address,50,f3);
    add_student_to_list(&firstS ,p->name,p->surname,p->group_ID,p->email,p->phone_number,p->pesel,p->address,p->amount);
    i=0;
    a=1;
}
fclose(f3);
return firstS;
}

void print_students(student *firstS){
int i=0;
if(firstS == NULL) printf("There are no students here!\n");

while(firstS){
    printf("%s %s\n",firstS->name,firstS->surname);
    printf("Groups: ");
    while(i < firstS->amount){
            printf("%d ",firstS->group_ID[i]);
            i++;
    }
    i=0;
    printf("\n");
    printf("Phone Number: %s\n",firstS->phone_number);
    printf("Email: %s\n",firstS->email);
    printf("Pesel: %s\n",firstS->pesel);
    printf("Address: %s\n",firstS->address);
    printf("\n");
    firstS = firstS->next;
}
}

student* add_student(student *firstS, course *firstC, group *firstG){
bool b,c;
student *t = (student*)malloc(sizeof(student));
// NAME
printf("Write name:\n");
do{
    fflush(stdin);
    scanf("%s",t->name);
    if( strlen(t->name) > 15){
        b=false;
        printf("Error! You can use only 15 letters!\n");
    }
    else b = only_letter(t->name);
    }while(b == false);
// SURNAME
printf("Write surname:\n");
do{
    fflush(stdin);
    scanf("%s",t->surname);
    if( strlen(t->surname) > 15){
        b=false;
        printf("Error! You can use only 15 letters!\n");
    }
    else b = only_letter(t->surname);
    }while(b == false);
// PHONE NUMBER
printf("Write a phone number:\n");
do{
    scanf("%s",t->phone_number);
    if(strlen(t->phone_number) == 9){
        b = only_numbers(t->phone_number);
        if( b == false ) printf("Error! You can use only numbers!\n");
    }
    else{
        printf("Error! Phone number have 9 numbers!\n");
        b = false;
    }
}while(b == false);
// PESEL
printf("Write a pesel\n");
do{
    c = true;
    fflush(stdin);
    scanf("%s",t->pesel);
    if(strlen(t->pesel) == 11) b = only_numbers(t->pesel);
    else{
        printf("Error! Pesel have 11 numbers!\n");
        c = false;
    }
    if( b == false ) {
        printf("Error! You can use only numbers!\n");
        c = false;
    }
}while (c == false);
// ADDRESS
printf("Write a Address\n");
fflush(stdin);
fgets(t->address, 50, stdin);
int i=0;
// EMAIL
printf("Write a Email\n");
do{
b = false;
scanf("%s",t->email);
int spr;
spr = strlen(t->email);
for(i=0;i<spr;i++){
    if(t->email[i] == '@') b = true;
}
if( b == false)printf("Error! Email must have a '@' inside\n");
}while( b == false);
i=0;
// COURSES
printf("Take a Course\n");
int n=1,a,spr=0;

int odp1;
char odp2;
int *local = (int*)malloc(n * sizeof(int));
bool stop=true,stop2=false;
if(firstC == NULL){
    printf("Error! You need to create course first!\n");
    return;
}
while(firstC){
    printf("%s ",firstC->course_name);
    printf("%d\n",firstC->id);
    local[i] = firstC->id;
    i++;
    n++;
    firstC = firstC->next;
}

while(spr != 1){
    scanf("%d",&a);
    for(int j=0;j<i;j++){
        if(a == local[j]) spr=1;
    }
    if(spr != 1)printf("Error! Course does not exist\n");
}
// GROUPS
group *tmp2;
tmp2 = firstG;
while(tmp2){
    if(tmp2->courseG == a) stop2 = true;
    tmp2 = tmp2->next;
}

t->amount = 0;
group *tmp;
if(stop2 == true){
printf("Take a Group: ");
printf("(If you need to check groups write '0')\n");
i=0;
int sum=0;
tmp = firstG;
scanf("%d",&odp1);
if(odp1 == 0){
    while(tmp){
        if(tmp->courseG == a){
            printf("Group ID: %d\n",tmp->group_id);
            printf("Start Date: %s\n",tmp->start_date);
            printf("End Date: %s\n",tmp->end_date);
            printf("\n");
            local[i] = tmp->group_id;
            i++;
        }
    tmp = tmp->next;
    }
}

while(stop == true){
do{
spr = 0;
scanf("%d",&odp1);
for(int j=0;j<i;j++){
    if(odp1 == local[j]){
        spr = 1;
        break;
    }

}
if(spr != 1)printf("Error! The group does not exist\n");
}while(spr != 1);

t->group_ID[sum] = odp1;
t->amount++;

if(t->amount < i){
printf("Do you want to add student to other group? (Y/N) \n");
fflush(stdin);
scanf("%c",&odp2);
while(odp2 != 'Y' && odp2 != 'N'){
    printf("Error! You should write Y or N!\n");
    fflush(stdin);
    scanf("%c",&odp2);
}
if(odp2 == 'Y') {
        stop = true;
        sum++;
        }
if(odp2 == 'N') stop = false;
}
else stop = false;
}

add_student_to_list(&firstS, t->name, t->surname, t->group_ID, t->email, t->phone_number, t->pesel, t->address, t->amount);
return firstS;
}
if(stop2 == false){
    printf("This course has no group!\n");
    printf("You need to create group first!\n");
return firstS;
}

}

student* delete_student(student *firstS, int *pesel){
int a=0;
if(firstS == NULL)return;
student *tmp;
if(strcmp(firstS->pesel,pesel) == 0){
    if(firstS->next){
        tmp = firstS;
        firstS = firstS->next;
        free(tmp);
    }
    else{
        tmp = firstS;
        firstS = NULL;
        free(tmp);
    }
    return firstS;
}
while(firstS->next){
    if(strcmp(firstS->next->pesel,pesel) == 0){
        tmp = firstS->next;
        firstS->next = tmp->next;
        free(tmp);
        a=1;
        break;
    }
    firstS = firstS->next;
}
if(a == 0)printf("There is no student with this pesel\n");
return firstS;
}

void edit_student(student *firstS, group *firstG, char *pesel){
int local,courseID,i=1,j=0,groupID,amount=1;
bool stop2 = true, stop ,main_stop = false;
bool c,b;
char tmp;
student* t = (student*)malloc(sizeof(student));
if( firstS == NULL ) printf("There are no students here!\n");
while(firstS){
    if( strcmp(firstS->pesel,pesel) == 0){
    printf("What did you want to change?\n");
    printf("1) Name\n");
    printf("2) Surname\n");
    printf("3) Phone Number\n");
    printf("4) Email\n");
    printf("5) Address\n");
    printf("6) Groups\n");
    printf("7) Pesel\n");
    printf("8) Back\n");
    do{
    scanf("%d",&local);
    switch(local){
        case 1:
            printf("Write name:\n");
do{
    scanf("%s",firstS->name);
    if( strlen(firstS->name) > 15){
        b=false;
        printf("Error! You can use only 15 letters!\n");
    }
    else b = only_letter(firstS->name);
    }while(b == false);
        break;

        case 2:
            printf("Write surname:\n");
do{
    scanf("%s",firstS->surname);
    if( strlen(firstS->surname) > 15){
        b=false;
        printf("Error! You can use only 15 letters!\n");
    }
    else b = only_letter(firstS->surname);
    }while(b == false);
        break;
        case 3:
            printf("Write a phone number:\n");
do{
    scanf("%s",firstS->phone_number);
    if(strlen(firstS->phone_number) == 9){
        b = only_numbers(firstS->phone_number);
        if( b == false ) printf("Error! You can use only numbers!\n");
    }
    else{
        printf("Error! Phone number have 9 numbers!\n");
        b = false;
    }
}while(b == false);
        break;
        case 4:
            printf("Write a Email\n");

do{
b = false;
scanf("%s",firstS->email);
int spr;
spr = strlen(firstS->email);
for(i=0;i<spr;i++){
    if(firstS->email[i] == '@') b = true;
}
if( b == false)printf("Error! Email must have a '@' inside\n");
}while( b == false);
        break;
        case 5:
            printf("Write a Address\n");
            fflush(stdin);
            fgets(firstS->address, 50, stdin);
        break;
        case 6:
            printf("Write an ID of student group:  \n");
            printf("(If you need to check groups write '0')\n");
            do{
                scanf("%d",&groupID);
                if( groupID == 0){
                    print_groups(firstG);
                    stop = false;
                }
                else stop = true;
            }while(!stop);
            student *schowek = firstS;
            stop = false;
            firstS->group_ID[0] = groupID;
            do{
                printf("Do you want to add student to other group? (Y/N)\n");
                j=0;
                fflush(stdin);
                scanf("%c",&tmp);
                if( tmp != 'Y' && tmp != 'N'){
                    printf("Error! You should write Y or N!\n");
                    stop = false;
                }
                else{
                    if(tmp == 'Y'){
                        amount++;
                        scanf("%d",&groupID);
                        while(j < i){
                            if(schowek->group_ID[j] == groupID){
                                printf("Error! This student belongs to this group!\n");
                                stop2 = false;
                                break;
                            }
                        stop2 = true;
                        j++;
                        }
                        if(stop2 != false) {
                            firstS->group_ID[i] = groupID;
                            i++;
                        }
                        stop = false;
                    }
                    if(tmp == 'N'){
                        stop = true;
                    }
                }
            }while(!stop);
            firstS->amount = amount;
        break;
        case 7:
            printf("Write a pesel\n");
do{
    scanf("%s",firstS->pesel);
    if(strlen(firstS->pesel) == 11) b = only_numbers(t->pesel);
    else{
        printf("Error! Pesel have 11 numbers!\n");
        c = false;
    }
    if( b == false ) {
        printf("Error! You can use only numbers!\n");
        c = false;
    }
}while (c == false);
        break;
        case 8:
            return;
    }
    printf("what would you edit more?\n");
    }while(!main_stop);
    }
    else{
        firstS = firstS->next;
    }
}
}

void print_one_student(student *firstS){
int i=0;
printf("%s %s\n",firstS->name,firstS->surname);
printf("Groups: ");
while(i < firstS->amount){
    printf("%d ",firstS->group_ID[i]);
    i++;
}

printf("\n");
printf("Phone Number: %s\n",firstS->phone_number);
printf("Email: %s\n",firstS->email);
printf("Pesel: %s\n",firstS->pesel);
printf("Address: %s\n",firstS->address);
}

void sereach_student(student *firstS){
printf("By what you want to sereach student?\n");
int local_number,local_groupID,schowek[50];
char local_name[15],local_surname[15],local_pesel[15], local_phone_number[15], local_address[50];
student *tmp;
bool b,c,stop;
printf("1) Name\n");
printf("2) Email\n");
printf("3) Pesel\n");
printf("4) Phone Number\n");
printf("5) Group\n");
printf("6) Address\n");
scanf("%d",&local_number);
switch(local_number){
case 1:
    tmp = firstS;
    printf("Write the name of the student you are looking for\n");
    do{
    scanf("%s",local_name);
    if( strlen(local_name) > 15){
        b=false;
        printf("Error! You can use only 15 letters!\n");
    }
    else b = only_letter(local_name);
    }while(b == false);
    stop = false;
    while(tmp){
        if(strcmp(local_name, tmp->name) == 0){
            print_one_student(tmp);
            stop = true;
            break;
        }
    tmp = tmp->next;
    }
    if(stop == false){
        printf("Student with this name does not exist\n");
    }
    break;
case 2:
    tmp = firstS;
    printf("Write the surname of the student you are looking for\n");
    do{
    scanf("%s",local_surname);
    if( strlen(local_surname) > 15){
        b=false;
        printf("Error! You can use only 15 letters!\n");
    }
    else b = only_letter(local_surname);
    }while(b == false);
    stop = false;
    while(tmp){
        if(strcmp(local_surname, tmp->surname) == 0){
            print_one_student(tmp);
            stop = true;
            break;
        }
    tmp = tmp->next;
    }
    if(stop == false){
        printf("Student with this surname does not exist\n");
    }
    break;
case 3:
    tmp = firstS;
    printf("Write the pesel of the student you are looking for\n");
    do{
    scanf("%s",local_pesel);
    if(strlen(local_pesel) == 11) b = only_numbers(local_pesel);
    else{
        printf("Error! Pesel have 11 numbers!\n");
        c = false;
    }
    if( b == false ) {
        printf("Error! You can use only numbers!\n");
        c = false;
    }
}while (c == false);
stop = false;
while(tmp){
    if(strcmp(local_pesel, tmp->pesel) == 0){
        print_one_student(tmp);
        stop = true;
        break;
    }
tmp = tmp->next;
}
if(stop == false){
    printf("Student with this pesel does not exist\n");
}
break;
case 4:
tmp = firstS;
printf("Write the phone number of the student you are looking for\n");
do{
    scanf("%s",local_phone_number);
    if(strlen(local_phone_number) == 9){
        b = only_numbers(local_phone_number);
        if( b == false ) printf("Error! You can use only numbers!\n");
    }
    else{
        printf("Error! Phone number have 9 numbers!\n");
        b = false;
    }
}while(b == false);
stop = false;
while(tmp){
    if(strcmp(local_phone_number, tmp->phone_number) == 0){
        print_one_student(tmp);
        stop = true;
        break;
    }
tmp = tmp->next;
}
if(stop == false){
    printf("Student with this phone number does not exist\n");
}
break;
case 5:
    tmp = firstS;
    printf("Write the group ID of the student you are looking for\n");
    scanf("%d",&local_groupID);
    stop = false;
    while(tmp){
        for(int i=0;i < tmp->amount;i++){
            if(tmp->group_ID[i] == local_groupID){
                print_one_student(tmp);
                break;
                stop = true;
            }
        }
    tmp = tmp->next;
}
if(stop == false){
    printf("Student with this group ID does not exits\n");
}
break;
case 6:
    tmp = firstS;
    printf("Write the address of the student you are looking for\n");
    fflush(stdin);
    fgets(local_address,50,stdin);
    stop = false;
    while(tmp){
        if(strcmp(tmp->address, local_address) == 0){
            print_one_student(tmp);
            stop = true;
            break;
        }
    }
    if(stop == false){
           printf("Student with this address does not exits\n");
    }
break;
}
}

void sort_students_by_birth_day(student *firstS){
student *tmp = NULL;
student *tmp2 = NULL;
student *tmp3 = (student*)malloc(sizeof(student));

for(tmp = firstS; tmp != NULL; tmp = tmp->next)
    for(tmp2 = tmp; tmp2 != NULL; tmp2 = tmp2->next){
        if(check_birth_date(tmp->pesel, tmp2->pesel) == false){

            strcpy(tmp3->address, tmp->address);
            strcpy(tmp->address, tmp2->address);
            strcpy(tmp2->address, tmp3->address);

            strcpy(tmp3->email, tmp->email);
            strcpy(tmp->email, tmp2->email);
            strcpy(tmp2->email, tmp3->email);

            strcpy(tmp3->name, tmp->name);
            strcpy(tmp->name, tmp2->name);
            strcpy(tmp2->name, tmp3->name);

            strcpy(tmp3->pesel, tmp->pesel);
            strcpy(tmp->pesel, tmp2->pesel);
            strcpy(tmp2->pesel, tmp3->pesel);

            strcpy(tmp3->phone_number, tmp->phone_number);
            strcpy(tmp->phone_number, tmp2->phone_number);
            strcpy(tmp2->phone_number, tmp3->phone_number);

            strcpy(tmp3->surname, tmp->surname);
            strcpy(tmp->surname, tmp2->surname);
            strcpy(tmp2->surname, tmp3->surname);

            for(int i=0; i < tmp->amount; i++){
                tmp3->group_ID[i] = tmp->group_ID[i];

            }

            for(int i=0; i < tmp2->amount; i++){
                tmp->group_ID[i] = tmp2->group_ID[i];
            }

            for(int i=0; i < tmp->amount; i++){
                tmp2->group_ID[i] = tmp3->group_ID[i];
            }

            tmp3->amount = tmp->amount;
            tmp->amount = tmp2->amount;
            tmp2->amount = tmp3->amount;
        }
    }

}

void sort_students_by_alph(student *firstS){
student *tmp = NULL;
student *tmp2 = NULL;
student *tmp3 = (student*)malloc(sizeof(student));

for(tmp = firstS; tmp != NULL; tmp = tmp->next)
    for(tmp2 = tmp; tmp2 != NULL; tmp2 = tmp2->next){
        if(check_alph(tmp->name, tmp2->name) == false){
            strcpy(tmp3->address, tmp->address);
            strcpy(tmp->address, tmp2->address);
            strcpy(tmp2->address, tmp3->address);

            strcpy(tmp3->email, tmp->email);
            strcpy(tmp->email, tmp2->email);
            strcpy(tmp2->email, tmp3->email);

            strcpy(tmp3->name, tmp->name);
            strcpy(tmp->name, tmp2->name);
            strcpy(tmp2->name, tmp3->name);

            strcpy(tmp3->pesel, tmp->pesel);
            strcpy(tmp->pesel, tmp2->pesel);
            strcpy(tmp2->pesel, tmp3->pesel);

            strcpy(tmp3->phone_number, tmp->phone_number);
            strcpy(tmp->phone_number, tmp2->phone_number);
            strcpy(tmp2->phone_number, tmp3->phone_number);

            strcpy(tmp3->surname, tmp->surname);
            strcpy(tmp->surname, tmp2->surname);
            strcpy(tmp2->surname, tmp3->surname);

            for(int i=0; i < tmp->amount; i++){
                tmp3->group_ID[i] = tmp->group_ID[i];

            }

            for(int i=0; i < tmp2->amount; i++){
                tmp->group_ID[i] = tmp2->group_ID[i];
            }

            for(int i=0; i < tmp->amount; i++){
                tmp2->group_ID[i] = tmp3->group_ID[i];
            }

            tmp3->amount = tmp->amount;
            tmp->amount = tmp2->amount;
            tmp2->amount = tmp3->amount;
        }
    }


}

void sort_students(student *firstS){
bool stop = true;

printf("By what you want to sort students\n");
printf("1) Alphabetically\n");
printf("2) Date of birth\n");
printf("3) If you dont wanna sort students\n");
int local_menu;
scanf("%d",&local_menu);
while(local_menu > 3 || local_menu < 1){
    printf("Error! You need to write a digital between 1-3\n");
    scanf("%d",&local_menu);
}
switch(local_menu){
case 1:
    sort_students_by_alph(firstS);
    break;
case 2:
    sort_students_by_birth_day(firstS);
    break;
case 3:
    return;
}

}



