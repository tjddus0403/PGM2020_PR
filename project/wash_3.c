#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define FULL 100

enum WHERE { ROOM1=1, ROOM2, ROOM3, DRYER, MACHINE, BASKET, STORE };
enum TYPE { SHIRTS=1, JUMPER, KNIT, COTTON, JEAN };
enum CHOICE { ADD=1, DELETE, SEARCH, CLOSET, DATE, QUIT };

typedef struct cloth{
	char name[30];
	char owner[30];
	int location;
	int type;
	int date;
	struct cloth* next;
}cloth_t;

cloth_t* fileopen(cloth_t *list)
{	
	cloth_t* new_cloth;
	FILE* fp=fopen("cloths.txt","r+");
	if(fp==NULL)
	{	printf("Failed to open file %s\n","cloths.txt");
		return NULL;}
	while(1)
	{
		new_cloth=(cloth_t*)malloc(sizeof(cloth_t));
		fscanf(fp,"%s %s %d %d %d",new_cloth->name,new_cloth->owner,&new_cloth->location,&new_cloth->type,&new_cloth->date);
		if (feof(fp)!=0)
			break;
		new_cloth->next=list;
		list=new_cloth;
	}
	fclose(fp);
	return list;
}

int filesave(cloth_t **list)
{	
	cloth_t* tmp_cloth;
	
	FILE* fp=fopen("cloths.txt","w+");
	if(fp==NULL)
	{	printf("Failed to open file %s\n","cloths.txt");
		return -1;}
	
	if (*list==NULL)
	{
		printf("동적메모리 할당 오류\n");
		return -1;
	}
	
	while(*list)
	{	
		tmp_cloth=*list;
		fprintf(fp,"%s %s %d %d %d\n",tmp_cloth->name,tmp_cloth->owner,tmp_cloth->location,tmp_cloth->type,tmp_cloth->date);
		*list=(*list)->next;
		free(tmp_cloth);
	}
	
	fclose(fp);

	printf("Saved\n");
	return 0;
}

cloth_t* check(cloth_t *list)
{
	cloth_t* tmp_cloth=list;
	char ch[30];
	printf("Enter the Name of cloth : ");
	scanf("%s",ch);
	int n=-1;
	while(tmp_cloth)
	{
		if(strcmp(tmp_cloth->name,ch)==0)
			return tmp_cloth;
		tmp_cloth=tmp_cloth->next;
	}
	return tmp_cloth;
}
//void delete(cloth_t *lp,int(*func)(cloth_t*))
//{
	
//}
void search(cloth_t *list,cloth_t* (*func)(cloth_t*))
{	
	cloth_t* tmp;
	tmp=func(list);
	char *where[]={"Room1","Room2","Room3","Dryer","Washing machine","Laundry basket","Laundry store"};
	char *type[]={"Shirts","Jumper","Knit","Cotton","Jean"};
	if(tmp==NULL)
		printf("This cloth is not your list\n");
	else
	{
		printf("\nName of cloth : %s\n",tmp->name);
		printf("Owner of cloth : %s\n",tmp->owner);
		printf("Location of cloth : %s\n",where[tmp->location-1]);
		printf("Type of cloth : %s\n",type[tmp->type-1]);
		printf("Date of last washing : %d\n",tmp->date);
	}
}

void add(cloth_t** list)
{	
	cloth_t* new_cloth;
	new_cloth=(cloth_t*)malloc(sizeof(cloth_t));
	
	printf("Name of cloth : ");
	scanf("%s",new_cloth->name);

	printf("Owner of cloth : ");	
	scanf("%s",new_cloth->owner);

	printf("1.Room1\n2.Room2\n3.Room3\n4.Dryer\n5.Washing Machine\n6.Laundry Basket\n7.Laundry Store\n");
	printf("Where is the cloth? : ");
	scanf("%d",&new_cloth->location);
		
	printf("1.Shirts\n2.Jumper\n3.Knit\n4.Cotton\n5.Jean\n");
	printf("What is the type of cloth? : ");
	scanf("%d",&new_cloth->type);

	printf("Enter the date of last washing cloth (ex)0403) : ");
	scanf("%d",&new_cloth->date);

	new_cloth->next=*list;
	*list=new_cloth;

}
void call(int choice,cloth_t *list)
{	
	list=fileopen(list);
	if(list==NULL)
	{
		printf("메모리 할당 오류\n");
		exit(1);
	}
	int c;
	switch(choice){
		case 1:
			add(&list);
			break;
		case 2:
			break;
		case 3:
			search(list,check);
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			break;
		case 7:
			printf("Save?\n1.Yes\n2.No\n");		
			scanf("%d",&c);
			if(c==1)
				filesave(&list);
			exit(1);
			
		default:
			break;
	}
}
void main()
{	
//	int num=0;
	cloth_t* list=NULL;

	while(1)
	{
		int choice;
		printf("\n<Select the function>\n1.Add cloth\n2.Delete cloth\n3.Search cloth\n4.Change option\n5.Open the closet\n6.Manage washing date\n7.Quit\n");
		scanf("%d",&choice);
		call(choice,list);
	
	}
}
