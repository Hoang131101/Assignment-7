#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct
{
    char name[50];
    int phonenumber;
    char address[50];
}info;

void addperson(info info1[], int* count){
    static int t = 1;
    FILE *peoplefile = fopen("personal.txt","a");
    if(peoplefile == NULL){
        printf("cannot open file");
        return;
    }
    if(*count >= 100){
        printf("The list is full!\n");
        return;
    }

    info newguest;
    printf("Enter name: ");
    getchar();
    fgets(newguest.name, sizeof(newguest.name),stdin);
    newguest.name[strlen(newguest.name) - 1] = '\0';//loai bo ky tu \n
    printf("Enter phone number: ");
    scanf("%d", &newguest.phonenumber);
    printf("Enter address: ");
    getchar();
    fgets(newguest.address, sizeof(newguest.address),stdin);
    newguest.address[strlen(newguest.address) - 1] = '\0';//loai bo ky tu \n

    fprintf(peoplefile,"Name: %s\n", newguest.name);
    fprintf(peoplefile,"phone number: %d\n",newguest.phonenumber);
    fprintf(peoplefile,"address: %s\n",newguest.address);

    info1[*count] = newguest;
    (*count)++;
    fclose(peoplefile);
}


void display(info info1[], int count){
    for(int i = 0;i < count;i++){
        printf("%d  Name: %s\n",i+1,info1[i].name);
        printf("    Phone number: %d\n",info1[i].phonenumber);
        printf("    Address: %s\n",info1[i].address);
    }
}

void search(info info1[], int count){
    int i,s;
    char namesearch[50];
    printf("Enter name to search: ");
    getchar();
    fgets(namesearch, sizeof(namesearch),stdin);
    namesearch[strcspn(namesearch, "\n")] = '\0'; // Loại bỏ ký tự '\n

    FILE *peoplefile = fopen("personal.txt", "r");
    if (peoplefile == NULL) {
        printf("cannot open file!");
        return;
    }
    
    for(int i = 0;i < count;i++){
        if(strcmp(namesearch,info1[i].name)==0){
            printf("Contract found: \n");
            printf("Name: %s\n",info1[i].name);
            printf("Phone: %d\n",info1[i].phonenumber);
            printf("Address: %s\n",info1[i].address);
            s = 1;
            break;
        }
    }
    if(!s){
        printf("Cannot find the name you entered!\n");
    }
}

int main()
{
    int count,n;
    int check;
    info info1[100];
    FILE *peoplefile = fopen("personal.txt","w");
    if(peoplefile == NULL){
        printf("cannot open file");
        return 1;
    }
    printf("Welcome to the contract manager!\n");
    printf("1. Add new contract\n");
    printf("2. Display all contracts\n");
    printf("3. Search for a contract\n");
    printf("4. Exit\n");
    fclose(peoplefile);
    while (1)
    {
        do{
            printf("Enter your choice: ");
            scanf("%d",&n);

            if(n < 1 || n>4){
                printf("Error your choice must be between 1-4\n");
            }
        } while(n<1 || n>4);
        
        switch (n)
        {
        case 1:
            addperson(info1, &count);
            break;
        case 2:
            display(info1, count);
            break;
        case 3:
            search(info1, count);
            break;
        case 4:
            printf("Goodbye!");
            exit(0);
            break;
        default:
            printf("Invalid choice!\n");
        }

    }
    return 0;

}
