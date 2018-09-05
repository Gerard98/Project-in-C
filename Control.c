#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define false 0
#define true 1
#include "Control.h"
#include "List_Actions.h"

bool only_letter(char *tab){
bool b=false;
int a;
a=strlen(tab);
int i;
for(i=0;i<a;i++){
    if(isdigit(tab[i]) == 0)b=true;
    else b=false;
}

if(b == false)printf("Error! You can use only letters! Write again!\n");

return b;
}

bool only_numbers(char *tab){
bool b;
int a = strlen(tab) - 1;
for(int i=0;i<a;i++){
    if( isdigit(tab[i]) == 0){
        return false;
    }
    b=true;
}

return b;
}

bool check_date(char *tab){
bool stop=false;
int sum = strlen(tab);
if(sum > 8){
    printf("Error! Wrong date!\n");
    return stop;
}
int a = (tab[0]-48)*10 + tab[1]-48;
if( a < 0 || a > 31){
    printf("Error! Wrong date!\n");
    return stop;
}
if(tab[2] != '.' || tab[5] != '.'){
    printf("Error! Wrong date!\n");
    return stop;
}
int b = (tab[3]-48)*10 + tab[4]-48;
if( b < 0 || b > 12){
    printf("Error! Wrong date!\n");
    return stop;
}
int c = (tab[6]-48)*10 + tab[7]-48;
if( c <= 17 ){
    printf("Error! Wrong date!\n");
    return stop;
}
stop=true;
return stop;
}

bool check_dates2(char *start, char *stop){
bool b = false;
int yearStart = (start[6]-48)*10 + start[7]-48;
int yearStop = (stop[6]-48)*10 + stop[7]-48;
if( yearStart > yearStop ){
    printf("Error! Wrong dates!\n");
    return b;
}
int monthStart = (start[3]-48)*10 + start[4]-48;
int monthStop = (stop[3]-48)*10 + stop[4]-48;
if( yearStart == yearStop){
    if( monthStart > monthStop ){
        printf("Error! Wrong dates!\n");
        return b;
    }
}

int daysStart = (start[0]-48)*10 + start[1]-48;
int daysStop = (stop[0]-48)*10 + stop[1]-48;
if( yearStart == yearStop){
    if( monthStart == monthStop ){
        if( daysStart > daysStop){
            printf("Error! Wrong dates!\n");
            return b;
        }
    }
}
b = true;
return b;
}

bool check_dates3(char *date1, char *date2){
// dd.mm.yy
int y1 = date1[6]*10 + date1[7];
int y2 = date2[6]*10 + date2[7];
int m1 = date1[3]*10 + date1[4];
int m2 = date2[3]*10 + date2[4];
int d1 = date1[0]*10 + date1[1];
int d2 = date2[0]*10 + date2[1];
if(y1 < y2) return true;
if(y1 > y2) return false;
if(y1 == y2){
    if(m1 < m2) return true;
    if(m1 > m2) return false;
    if(m1 == m2){
        if(d1 < d2)return true;
        if(d1 > d2)return false;
        if(d1 == d2) return true;
    }
}
}

bool check_birth_date(char *date1, char *date2){
//yymmdd

int y1 = (date1[0]-48)*10 + date1[1]-48;
int y2 = (date2[0]-48)*10 + date2[1]-48;
int m1 = (date1[2]-48)*10 + date1[3]-48;
int m2 = (date2[2]-48)*10 + date2[3]-48;
int d1 = (date1[4]-48)*10 + date1[5]-48;
int d2 = (date2[4]-48)*10 + date2[5]-48;
if(y1 > y2) return true;
if(y1 < y2) return false;
if(y1 == y2){
    if(m1 > m2) return true;
    if(m1 < m2) return false;
    if(m1 == m2){
        if(d1 > d2)return true;
        if(d1 < d2)return false;
        if(d1 == d2) return true;
    }
}
}

void save_changes(course* firstC, group* firstG, student* firstS){

FILE * f1=fopen("Files/Courses.txt", "w");
if(f1 == NULL){
    printf("The file with the courses does not open!\n");
    return;
}
FILE * f2=fopen("Files/Groups.txt", "w");
if(f2 == NULL){
    fclose(f1);
    printf("The file with the groups does not open!\n");
    return;
}
FILE * f3=fopen("Files/Students.txt", "w");
if(f3 == NULL){
    fclose(f1);
    fclose(f2);
    printf("The file with the students does not open!\n");
    return;
}

clearerr(f1);
clearerr(f2);
clearerr(f3);

while(firstC){
    fprintf(f1,"%d ",firstC->id);
    fprintf(f1,"%d ",firstC->hours);
    fprintf(f1,"%d ",firstC->price);
    fprintf(f1,"%s",firstC->course_name);
    fprintf(f1,"%s\n",firstC->course_description);
    firstC = firstC->next;
}
while(firstG){
    fprintf(f2,"%d ",firstG->group_id);
    fprintf(f2,"%s ",firstG->start_date);
    fprintf(f2,"%s ",firstG->end_date);
    fprintf(f2,"%d\n",firstG->courseG);
    firstG = firstG->next;
}
while(firstS){
    fprintf(f3,"%s ",firstS->name);
    fprintf(f3,"%s ",firstS->surname);
    for(int i=0;i<firstS->amount;i++)
        fprintf(f3,"%d ",firstS->group_ID[i]);
    fprintf(f3,"%s ",firstS->email);
    fprintf(f3,"%s ",firstS->pesel);
    fprintf(f3,"%s ",firstS->phone_number);
    fprintf(f3,"%s\n",firstS->address);
    firstS = firstS->next;
}
fclose(f1);
fclose(f2);
fclose(f3);

return;
}

bool check_alph(char *name1, char *name2){
int i=0,max;
int the_same_name;
int max_n1 = strlen(name1);
int max_n2 = strlen(name2);
if(max_n1 > max_n2) max = max_n2;
if(max_n1 < max_n2) max = max_n1;
if(max_n1 == max_n2) {
        max = max_n1;
        the_same_name = 1;
}
while(i < max){
    int n1 = name1[i];
    int n2 = name2[i];

    if(n1 > n2) return false;
    if(n1 < n2) return true;
    if(n1 == n2)i++;
}
if(the_same_name == 1)return true;
return false;
}

