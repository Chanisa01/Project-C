#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define BUFFER_SIZE 1000

char yn;

void replaceAll(char *str, const char *oldWord, const char *newWord);

struct Product {
        char name[20];
        int details[2];
	};

main(){

    system("cls");
    int choice;
    printf("----------------------------------------------Welcome to meow store----------------------------------------------\n");
    printf("\t\t\t\t\t\t(1) ADMIN\n\t\t\t\t\t\t(2) USER\n\t\t\t\t\t\t(3) Monthly report\n");
    printf("-----------------------------------------------------------------------------------------------------------------\n");
    printf("\nEnter a choice (Press 4 for Exit):");
    scanf("%d",&choice);
    switch (choice){
        case 1 :
            Admin();
            break;
        case 2 :
            User();
            break;
        case 3 :
            Report();
            break;
        default :
        printf("\n\nThank you, see you soon\n");
    }
}

void Admin() {
    system("cls");
    int ch,getCode;
    printf("-----------------------------------------------------------------------------------------------------------------\n");
    printf("\t\t\t\t\t\tADMIN\n");
    printf("-----------------------------------------------------------------------------------------------------------------\n");
    showproduct();
    printf("\nDo you want edit ? (Press Enter = Yes / Press N = No) : ");
    yn = getche();
    if(yn=='N'){
        main();
    }
    else{
        printf("\n\nDo you want to [add] product, Please enter 1\n");
        printf("Do you want to [delete] product, Please enter 2\n");
        printf("Do you want to [Edit] product, Please enter 3\n");
        printf("\nPlease input number 1 2 or 3 : ");
        scanf("%d",&ch);

        switch (ch){
            case 1:
                add();
                break;
            case 2:
                deleted();
                break;
            case 3:
                Edit();
                break;
            default :
                printf("Please input number 1 2 or 3 only !!\n");
                printf("Continue(Press Enter) or Exit(press E) : ");
                yn = getche();
                if (yn == 'E')
                    main();
                else
                    Admin();
        }
    }
}

void add(){
    system("cls");
    showproduct();
    printf("\t\t\t\t\t\tThis is the add page\n");
    printf("-----------------------------------------------------------------------------------------------------------------\n");
    struct Product pd;
    FILE *fp2;
    if((fp2=fopen("product.txt","a"))==NULL) {
		printf("Cannot open product.txt for write append\n");
		exit(1);
	}
    while(yn!='E') {
            printf("\n\nEnter code : ");
			scanf("%d",&pd.details[0]);
            getchar();
			printf("Enter product name : ");
			gets(pd.name);
			printf("Enter quantity : ");
			scanf("%d",&pd.details[1]);
			printf("Enter product price : ");
			scanf("%d",&pd.details[2]);
			fprintf(fp2,"%d %s %d %d\n",pd.details[0],pd.name,pd.details[1],pd.details[2]);
			printf("\nAdd product complete\n\n");
			printf("Continue(Press Enter) or Exit(press E) : ");
			yn = getche();
		}
    fclose(fp2);
    Admin();
}

void deleted(){
    int getCode;
    system("cls");
    showproduct();
    printf("\t\t\t\t\t\tThis is the delete page\n");
    printf("-----------------------------------------------------------------------------------------------------------------\n");
    printf("\nPlease Select Code Product : ");
    scanf("%d",&getCode);
    del(getCode);
    printf("\nDelete product complete\n\n");
    printf("Continue(Press Enter) or Exit(press E) : ");
    yn = getche();
    if (yn == 'E')
        Admin();
    else
        deleted();
}

void del(int getCode){
    char oldWord[100], newWord[100],test;
    struct Product pd;
    FILE * fPtr;
    FILE * fTemp;
    char buffer[BUFFER_SIZE];
    FILE *fpTemp;
	if((fpTemp=fopen("product.txt","r"))==NULL) {
		printf("Cannot open receipt.txt for read\n");
		exit(1);
		}
	while((fscanf(fpTemp,"%d %s %d %d",&pd.details[0],pd.name,&pd.details[1],&pd.details[2]))!=EOF)
        {
            if (getCode==pd.details[0])
            {
            snprintf(oldWord, 100,"%d %s %d %d",pd.details[0],pd.name,pd.details[1],pd.details[2]);
            }
        }
	fclose(fpTemp);
    snprintf(newWord, 100, "");

    fPtr  = fopen("product.txt", "r");
    fTemp = fopen("replace.tmp", "w");

    if (fPtr == NULL || fTemp == NULL)
    {
        printf("\nUnable to open file.\n");
        printf("Please check whether file exists and you have read/write privilege.\n");
        exit(EXIT_SUCCESS);
    }

    while ((fgets(buffer, BUFFER_SIZE, fPtr)) != NULL)
    {
        replaceAll(buffer, oldWord, newWord);
        fputs(buffer, fTemp);
    }

    fclose(fPtr);
    fclose(fTemp);
    remove("product.txt");
    rename("replace.tmp", "product.txt");
}

void Edit()
{
    system("cls");
    showproduct();
    printf("\t\t\t\t\t\tThis is the edit page\n");
    printf("-----------------------------------------------------------------------------------------------------------------\n");
    FILE * fPtr;
    FILE * fTemp;

    char buffer[BUFFER_SIZE];
    char oldWord[100], newWord[100];

    printf("\nEnter word to replace: ");
    scanf("%s", oldWord);

    printf("Replace with: ");
    scanf("%s", newWord);

    fPtr  = fopen("product.txt", "r");
    fTemp = fopen("replace.tmp", "w");

    if (fPtr == NULL || fTemp == NULL)
    {
        printf("\nUnable to open file.\n");
        printf("Please check whether file exists and you have read/write privilege.\n");
        exit(EXIT_SUCCESS);
    }

    while ((fgets(buffer, BUFFER_SIZE, fPtr)) != NULL)
    {
        replaceAll(buffer, oldWord, newWord);
        fputs(buffer, fTemp);
    }
    fclose(fPtr);
    fclose(fTemp);

    remove("product.txt");
    rename("replace.tmp", "product.txt");

    printf("\nSuccessfully replaced all occurrences of '%s' with '%s'\n", oldWord, newWord);
    printf("\nEdit product complete\n\n");
    printf("Continue(Press Enter) or Exit(press E) : ");
    yn = getche();
    if (yn == 'E')
        Admin();
    else
        Edit();
}

void addtempRecipt(int c,char *name,int q,int total){
    struct Product pd;
    FILE *fp2;
        if((fp2=fopen("tempRecipt.txt","a"))==NULL)
        {
		printf("Cannot open product.txt for write append\n");
		exit(1);
        }
        fprintf(fp2,"%d %s %d %d\n",c,name,q,total);
		fclose(fp2);
}

void User(){
    system("cls");
    char NameA[10];
    FILE *fp1,*fptemp;
    struct Product pd;
    struct Product pd2;
    time_t orig_format;
    time(&orig_format);
    char nameP[20];
    int code,quan,price;
    int total,stotal;
    printf("-----------------------------------------------------------------------------------------------------------------\n");
    printf("\t\t\t\t\t\tUSER\n");
    printf("-----------------------------------------------------------------------------------------------------------------\n");
    showproduct();
    while(yn!='E')
        {
        printf("\n\nPlease input code product : ");
        scanf("%d",&code);
        printf("Please quantity : ");
        scanf("%d",&quan);
            if((fp1=fopen("product.txt","r"))==NULL)
            {
            printf("Cannot open product.txt for read\n");
            exit(1);
            }
            while((fscanf(fp1,"%d %s %d %d",&pd.details[0],pd.name,&pd.details[1],&pd.details[2]))!=EOF){
                if (code == pd.details[0]){
                    price = pd.details[2];
                    break;
                }
            }
            fclose(fp1);
            total = pd.details[2] * quan;


            FILE *fp2;
            if((fp2=fopen("receipt.txt","a"))==NULL){
                printf("Cannot open receipt.txt for write append\n");
                exit(1);
            }
			fprintf(fp2,"%d %s %d %d %d %d %s\n",pd.details[0],pd.name,pd.details[1],pd.details[2],quan,total,asctime(gmtime(&orig_format)));
            fclose(fp2);

            userUpdateDatabase(pd.details[0],pd.name,pd.details[1],pd.details[2],quan);
            addtempRecipt(pd.details[0],pd.name,quan,total);
            printf("\nDo you want continue ? (Any Key = Yes / E = end and print receipt) : ");
            yn = getche();
    }

        printf("\n-----------------------------------------------------------------------------------------------------------------\n");
        printf("\t\t\t\t\t\tReceipt\n");
        printf("-----------------------------------------------------------------------------------------------------------------\n");
        printf("\t\t\tCode\t\tName\t\tQuantity\t\tPrice\n");
            if((fptemp=fopen("tempRecipt.txt","r"))==NULL){
                printf("Cannot open product.txt for read\n");
                exit(1);
            }
            while((fscanf(fptemp,"%d %s %d %d",&pd2.details[0],pd2.name,&pd2.details[1],&pd2.details[2]))!=EOF){
                printf("\t\t\t%d\t\t%s\t\t%d\t\t\t%d\n",pd2.details[0],pd2.name,pd2.details[1],pd2.details[2]);
                stotal= stotal+pd2.details[2];
            }
            fclose(fptemp);

    printf("\n-----------------------------------------------------------------------------------------------------------------\n");
    printf("\t\t\t\t\t\tTotal is %d Bath\n",stotal);
    printf("\t\t\t\t\tTHANK YOU FOR SHOPPING WITH US.\n");
    printf("-----------------------------------------------------------------------------------------------------------------\n");

    char *txtPtr = strstr("receipt.txt","\n");

      if((fp1=fopen("tempRecipt.txt","w"))==NULL)
            {
            printf("Cannot open tempRecipt for read\n");
            exit(1);
            }
            fp1=freopen(NULL,"w",fp1);
            fclose(fp1);

    printf("Continue(Press Enter) or Exit(press E) : ");
    yn = getche();
    if (yn == 'E')
        main();
    else
        User();
    }

void Report(){
    system("cls");
    struct Product pd;
    int numb,q,q2,p,day,y;
    int total,stotal=0;
    char name[20],time[20],m[10],getM[10],date[2];

	FILE *fp1;
	printf("Please input month (Such as : May) : ");
    scanf("%s",getM);
    printf("-----------------------------------------------------------------------------------------------------------------\n");
    printf("\t\t\t\t\tMonthly report %s\n",getM);
    printf("-----------------------------------------------------------------------------------------------------------------\n");
    printf("Code\t|NameProduct\t|Price of product\t|quantity\t|Total\t|Month\t|Date\t|Time\t\t|Year\n");
    printf("-----------------------------------------------------------------------------------------------------------------\n");
	if((fp1=fopen("receipt.txt","r"))==NULL) {
		printf("Cannot open receipt.txt for read\n");
		exit(1);
		}
	while((fscanf(fp1,"%d %s %d %d %d %d %s %s %d %s %d",&numb,name,&q,&p,&q2,&total,date,m,&day,time,&y))!=EOF)
        {
            if (m[3]==getM[3])
            {
            printf("%d\t%s\t\t\t%d\t\t\t%d\t%d\t%s\t%d\t%s\t%d\n",numb,name,p,q2,total,m,day,time,y);
            stotal= stotal+total;
            }
        }
    printf("-----------------------------------------------------------------------------------------------------------------\n");
    printf("\t\t\t\t\t\tTotal is %d Bath\n",stotal);
    printf("-----------------------------------------------------------------------------------------------------------------\n");
    fclose(fp1);
    printf("Continue(Press Enter) or Exit(press E) : ");
    yn = getche();
    if (yn == 'E')
        main();
    else
        Report();
   }

void replaceAll(char *str, const char *oldWord, const char *newWord)
{
    char *pos, temp[BUFFER_SIZE];
    int index = 0;
    int owlen;

    owlen = strlen(oldWord);

    if (!strcmp(oldWord, newWord)) {
        return;
    }

    while ((pos = strstr(str, oldWord)) != NULL)
    {
        strcpy(temp, str);
        index = pos - str;
        str[index] = '\0';
        strcat(str, newWord);
        strcat(str, temp + index + owlen);
    }
}

void userUpdateDatabase(int no,char *name,int q,int p,int qUse)
{
    char oldWord[100], newWord[100];
    char buffer[BUFFER_SIZE];

    FILE * fPtr;
    FILE * fTemp;

    snprintf(oldWord, 100, "%d %s %d %d",no,name,q,p);
    q=q-qUse;
    snprintf(newWord, 100, "%d %s %d %d",no,name,q,p);

    fPtr  = fopen("product.txt", "r");
    fTemp = fopen("replace.tmp", "w");

    if (fPtr == NULL || fTemp == NULL)
    {
        printf("\nUnable to open file.\n");
        printf("Please check whether file exists and you have read/write privilege.\n");
        exit(EXIT_SUCCESS);
    }

    while ((fgets(buffer, BUFFER_SIZE, fPtr)) != NULL)
    {
        replaceAll(buffer, oldWord, newWord);
        fputs(buffer, fTemp);
    }
    fclose(fPtr);
    fclose(fTemp);

    remove("product.txt");
    rename("replace.tmp", "product.txt");

    return 0;
}

void showproduct(){
    struct Product pd;
	FILE *fp1;
	if((fp1=fopen("product.txt","r"))==NULL) {
		printf("Cannot open product.txt for read\n");
		exit(1);
	}
	printf("\t\t\t\t\t\tMeow Store\n");
	printf("-----------------------------------------------------------------------------------------------------------------\n");
	while((fscanf(fp1,"%d %s %d %d",&pd.details[0],pd.name,&pd.details[1],&pd.details[2]))!=EOF) {
		printf("\t\t\t\t\t%d\t%s\t%d\t%d\n",pd.details[0],pd.name,pd.details[1],pd.details[2]);
	}
    fclose(fp1);
    printf("-----------------------------------------------------------------------------------------------------------------\n");
}


