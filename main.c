#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define true 1
#define false 0
#include "List_Actions.h"
#include "Student_Actions.h"

void printf_main_page(){
    printf("*****MAIN PAGE*****\n");
    printf("1) Add Course\n");
    printf("2) Delete Course\n");
    printf("3) Edit Course\n");
    printf("4) Sereach Course\n");
    printf("5) Write Courses\n");
    printf("6) Write Groups\n");
    printf("7) Add Student\n");
    printf("8) Delete Student\n");
    printf("9) Edit Student\n");
    printf("10) Sereach Students \n");
    printf("11) Write Students\n");
    printf("12) Build New Group\n");
    printf("13) Write the Students of the group\n");
    printf("14) End of Program\n");


}

int main()
{
printf("********** Course management program **********\n");
printf("**********  Created by Gerard Gosk   **********\n\n\n");
student *firstS = NULL;
course *firstC = NULL;
group *firstG = NULL;
firstS = load_students(firstS);
firstC = load_courses(firstC);
firstG = load_groups(firstG);
int back = 1,local_idC,sum;
int tmp_id;
bool stop = false;
char local_idG[15];
char answer;
while(back){
printf_main_page();
int main_number;
fflush(stdin);
scanf("%d",&main_number);
if(main_number < 0 || main_number >14)
        printf("Error! Select a number from 1 to 14\n");

switch(main_number){
    case 1:
        firstC = add_course(firstC);
        break;
    case 2:
        if(firstC == NULL){
            printf("There are no courses at the moment\n");
            break;
        }
        printf("Write a ID of Course: \n");
        scanf("%d",&local_idC);
        firstC = delete_course(firstC, local_idC);
        break;
    case 3:
        if(firstC == NULL){
            printf("There are no courses at the moment\n");
            break;
        }
        do{
        stop = true;
        printf("Write a ID of Course: (if you need to check courses, write '0')\n");
        char tmp_check[10];
        fflush(stdin);
        fgets(tmp_check,10,stdin);
        while(only_numbers(tmp_check) == false){
            printf("Error! You need to use only digits\n");
            fflush(stdin);
            fgets(tmp_check,10,stdin);
        }
        int sum = strlen(tmp_check) - 2;
        tmp_id = 0;
        for(int i=0; i <= sum; i++){
        tmp_id += ((tmp_check[i]-48)*pow(10, sum-i));
        }
        if(tmp_id == 0){
            print_courses(firstC);
            stop=false;
        }
        else stop = true;
        }while(!stop);
        edit_course(firstC,tmp_id);
        break;
    case 4:
        if(firstC == NULL){
            printf("There are no courses at the moment\n");
            break;
        }
        sereach_course(firstC);
        break;
    case 5:
        printf("Do you want to sort courses? (Y/N) \n");
        fflush(stdin);
        scanf("%c",&answer);
        while(answer != 'Y' && answer != 'N'){
            printf("Error! You must use Y or N!\n");
            fflush(stdin);
            scanf("%c",&answer);
        }
        if(answer == 'Y')sort_courses(firstC);
        print_courses(firstC);
        break;
    case 6:
        printf("Do you want to sort groups? (Y/N) \n");
        fflush(stdin);
        scanf("%c",&answer);
        while(answer != 'Y' && answer != 'N'){
            printf("Error! You must use Y or N!\n");
            fflush(stdin);
            scanf("%c",&answer);
        }
        if(answer == 'Y') sort_groups(firstG);
        print_groups(firstG);
        break;
    case 7:
        firstS = add_student(firstS,firstC,firstG);
        break;
    case 8:
        if(firstS == NULL){
            printf("There are no students at the moment\n");
            break;
        }
        printf("Write a pesel of student:  ");
        printf("(If you need to check students, write '0')\n");
        stop = false;
        while(!stop){
            scanf("%s", &local_idG);
            if( strlen(local_idG) == 11){
                stop = only_numbers(local_idG);
                if(stop == false) printf("Error! Pesel have only digits!\n");
            }
            if( strlen(local_idG) == 1){
                if(local_idG[0] == '0'){
                    print_students(firstS);
                    printf("Write a pesel now: \n");
                    scanf("%s", &local_idG);
                    stop = only_numbers(local_idG);
                    if(stop == false) printf("Error! Pesel have only digits!\n");
                }
            }
            if(strlen(local_idG) != 11 && strlen(local_idG) != 1)printf("Error! You should use 11 digits\n");
        }
        firstS = delete_student(firstS, local_idG);
        break;
    case 9:
        if(firstS == NULL){
            printf("There are no students at the moment\n");
            break;
        }
        printf("Write a pesel of student:  ");
        printf("(If you need to check students, write '0')\n");
        stop = false;
        while(!stop){
            scanf("%s", &local_idG);
            if( strlen(local_idG) == 11){
                stop = only_numbers(local_idG);
                if(stop == false) printf("Error! Pesel have only digits!\n");
            }
            if( strlen(local_idG) == 1){
                if(local_idG[0] == '0'){
                    print_students(firstS);
                    printf("Write a pesel now: \n");
                    scanf("%s", &local_idG);
                    stop = only_numbers(local_idG);
                    if(stop == false) printf("Error! Pesel have only digits!\n");
                }
            }
            if(strlen(local_idG) != 11 && strlen(local_idG) != 1)printf("Error! You should use 11 digits\n");
        }
        edit_student(firstS, firstG, local_idG);
        break;
    case 10:
        if(firstS == NULL){
            printf("There are no students at the moment\n");
            break;
        }
        sereach_student(firstS);
        break;
    case 11:
        printf("Do you want to sort students? (Y/N) \n");
        fflush(stdin);
        scanf("%c",&answer);
        while(answer != 'Y' && answer != 'N'){
            printf("Error! You must use Y or N!\n");
            fflush(stdin);
            scanf("%c",&answer);
        }
        if(answer == 'Y')sort_students(firstS);
        print_students(firstS);
        break;
    case 12:
        firstG = add_group(firstG, firstC);
        break;
    case 13:
        print_taken_group(firstS, firstG);
        break;
    case 14:
        printf("Do you want to save changes? (Y/N)\n");
        fflush(stdin);
        scanf("%c",&answer);
        while(answer != 'Y' && answer != 'N'){
            printf("Error! You must use Y or N!\n");
            scanf("%c",&answer);
        }
        if(answer == 'Y'){
            save_changes(firstC, firstG, firstS);
            return;
        }
        else return;
}
}

return 0;
}

