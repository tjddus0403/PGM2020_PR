#include<stdio.h>
#include<string.h>
#define FULL 100
enum WHERE { MYROOM=1, BROROOM, HALL ,DRY, WAHSING, BASKET, STORE };

typedef struct cloth{
	char who[30];
	char name[100];
//	char location[30];
	int location;
	char method[100];
}cloth_c;

int num=0;

void delete(cloth_c *lp, int (*func)(cloth_C*))
{
	int n;
	n=func(lp);
	if(n==-1)
		printf("존재하지 않는 옷입니다.\n");
	else if(n>-1)
	{
		
	}
}
void search_print( cloth_c *lp, int (*func)(cloth_c*))
{	
	int n;
	n=func(lp);
	char *where[]={"My room closet","Brother's room closet","Hall closet","Dryer","Washing machine","Laundry basket","Laundry store"};
	if(n==-1)
		printf("존재하지 않는 옷입니다.\n");
	else if (n>-1)
	{	
		printf("\n옷 이름: %s\n",lp[n].name);
		printf("\n옷 주인: %s\n",lp[n].who);
		printf("\n옷 위치: %s\n",where[lp[n].location-1]);
		printf("\n세탁 방법: %s\n",lp[n].method);
	}
}
int search_check( cloth_c *lp)
{	
	char a[100];
	printf("\n옷의 이름:");
	scanf("%s",a);
	int n=-1;
	for(int i=0;i<num;i++)
	{	
		if (strcmp(lp[i].name, a)==0)
			n=i;
	}
	return n;
}
int add(cloth_c *lp)
{
	if(num>FULL)
	{	printf("\n옷이 가득 찼습니다.\n");
		return 0;}
	char owner[30];
	char name[100];
	int loc;
	char m[100];
	printf("\n옷의 주인:");
	scanf("%s",owner);
	
	printf("\n옷의 이름:");
	scanf("%s",name);

	printf("\n1. Myroom closet\n2. Brother's room closet\n3. Hall closet\n4. Dryer\n5. Washing machine\n6. Laundry basket\n7. Laundry store\n");
	
	printf("\n옷의 위치:");
	scanf("%d",&loc);
	
	printf("\n세탁 방법:");
	scanf("%s",m);
	
	
	strcpy(lp[num].who, owner);
	strcpy(lp[num].name, name);
	lp[num].location=loc;
	strcpy(lp[num].method, m);
	num++;
	return 0;
	//printf("%s\n",lp[num].who);
}
void call(int choice,cloth_c *lp)
{
	switch(choice){
		case 1:
			//call add function
			add(lp);
			break;
		case 2:
			//call delete function
			break;
		case 3:
			search_print(lp,search_check);
			break;
		case 4:
			//call change function
			break;
		default:
			break;
	}	
}

void main()
{	
	cloth_c list[FULL];
	cloth_c *lp=list;
	while(1){
		int choice;
		printf("\n<Select the function>\n1.Add cloth\n2.Delete cloth\n3.Search cloth\n4.Change cloth's option\n");
		scanf("%d",&choice);
		call(choice, lp);
	}
}
