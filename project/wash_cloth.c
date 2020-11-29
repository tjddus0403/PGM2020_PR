#include<stdio.h>
#include<string.h>
#define FULL 100
enum WHERE { BED, MYROOM, BROROOM, HALL ,DRY, WAHSING, BASKET };
enum WASH {DRY, HAND, MACHINE};

struct cloth{
	char who[30];
	char cloth_name[30];
	char method[10];
};
int select(int choice)
{
	switch(choice){
		case 1:
			//call add function
			break;
		case 2:
			//call delete function
			break;
		case 3:
			//call search function
			break;
		case 4:
			//call change function
			break;
		default:
			break;
	}	
}
int main()
{	
    struct cloth list[FULL];
	char *c=
	while(1){
		int choice;
		printf("Select the function\n1.Add cloth\n2.Delete cloth\n3.Search cloth\n4.Change cloth's option"};
		scanf("%d",&choice);
		switch(choice){
			case 1:
				//call add function
				break;
			case 2:
				//call delete fuction
				break;
			case 3:
				//call search fuction
				break;
			case 4:
				//call change fuction
				break;
			default:
				printf("Wrong choice! Select again!\n");
				break;
	}
}
