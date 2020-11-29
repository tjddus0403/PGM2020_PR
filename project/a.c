#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct cloth{
	char name[30];
	char owner[30];
	int location;
	int type;
	int date;
	struct cloth* next;
}cloth_t;
cloth_t* open(cloth_t* list_head);
void add(cloth_t* list_head);
cloth_t* search(cloth_t* list_head,char* name);
void show_info(cloth_t* list_head,cloth_t*(*func)(cloth_t*,char* name));
void save(cloth_t* list_head);
void untracked(cloth_t* list_head);
void call(cloth_t* list_head,int* q);
void main()
{
	int num=0;
	int q=0;
	cloth_t* list_head=NULL;
	list_head=open(list_head);
	while(1)
	{
		call(list_head,&q);
		if (q==1)
			break;
	}
}
void call(cloth_t* list_head,int* q)
{
	int choice;
	int quit_choice;
	printf("<Select the function>\n");
	printf("1. Add cloth\n");
	printf("2. Show cloth's information\n");
	printf("3. Change the cloth's information\n");
	printf("4. Delete the cloth\n");
	printf("5. Open the closet\n");
	printf("6. Washing method\n");
	printf("7. Quit\n");
	printf("Enter your choice number : ");
	scanf("%d",&choice);
	
	switch(choice)
	{
		case 1:
			add(list_head);
			break;
		case 2:
			show_info(list_head,search);
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			break;
		case 7:
			printf("Save?\n1. Yes\n2. No\n");
			scanf("%d",&quit_choice);
			if(quit_choice==1)
				save(list_head);
			else
				untracked(list_head);
			*q=1;
			break;
		default:
			break;
	}
}
void add(cloth_t* list_head)
{
	cloth_t* new_node;
	cloth_t* next_p;
	cloth_t* prev_p;
	
	char name[30];
	char owner[30];
	int loc;
	int t;
	int d;
//사용자로부터 입력
	printf("옷 이름 : ");
	scanf("%s",name);

	printf("옷 주인 : ");	
	scanf("%s",owner);
	
	printf("1.Room1\n2.Room2\n3.Room3\n4.Dryer\n5.Washing Machine\n6.Laundry Basket\n7.Laundry Store\n");
	printf("옷 위치 : ");
	scanf("%d",&loc);

	printf("1.Shirts\n2.Jumper\n3.Knit\n4.Cotton\n5.Jean\n");
	printf("옷 종류 : ");
	scanf("%d",&t);

	printf("최근 세탁 날짜 (ex)1102, 403..) : ");
	scanf("%d",&d);
//노드생성
	new_node=(cloth_t*)malloc(sizeof(cloth_t));
	strcpy(new_node->name,name);
	strcpy(new_node->owner,owner);
	new_node->location=loc;
	new_node->type=t;
	new_node->date=d;
//노드삽입 위치 검색
	next_p=list_head;
	prev_p=NULL;
	
	while(next_p)
	{
		if(next_p->location > new_node->location)
			break;
		prev_p=next_p;
		next_p=next_p->next;
	}
//노드삽입
	new_node->next=next_p;
	if(prev_p)
		prev_p->next=new_node;
	else
		list_head=new_node;
	return;
}
cloth_t* open(cloth_t* list_head)
{
	FILE* fp=NULL;
	cloth_t* new_node;
	
	fp=fopen("wash.txt","r+");
	if(fp==NULL)
	{
		printf("Cannot open file\n");
		return list_head;
	}
	
	while(1)
	{
		new_node=(cloth_t*)malloc(sizeof(cloth_t));
		if(feof(fp)!=0)
			break;
		fscanf(fp,"%s %s %d %d %d\n", new_node->name,new_node->owner,&new_node->location,&new_node->type,&new_node->date);
		
		new_node->next=list_head;
		list_head=new_node;
	}
	fclose(fp);
	return list_head;
}

void show_info(cloth_t* list_head,cloth_t*(*func)(cloth_t*,char* name))
{	
	cloth_t* tmp_node;
	char *where[]={"Room1","Room2","Room3","Dryer","Washing machine","Laundry basket","Laundry store"};
	char *type[]={"Shirts","Jumper","Knit","Cotton","Jean"};
	char name[30];
	printf("찾고 싶은 옷 이름 : ");
	scanf("%s",name);
	tmp_node=func(list_head,name);
	if(tmp_node)
	{
		printf("옷 이름 : %s\n", tmp_node->name);
		printf("옷 주인 : %s\n", tmp_node->owner);
		printf("옷 위치 : %s\n",where[(tmp_node->location)-1]);
		printf("옷 종류 : %s\n",type[(tmp_node->type)-1]);
		printf("최근 세탁 날짜 : %d\n",tmp_node->date);
	}
	else
		printf("존재하지 않는 옷입니다.\n");
}
cloth_t* search(cloth_t* list_head,char* name)
{
	cloth_t* tmp=list_head;
	while(tmp)
	{
		if(!strcmp(tmp->name, name))
			return tmp;
		tmp=tmp->next;
	}
	return tmp;
}

void save(cloth_t* list_head)
{
	cloth_t* tmp_node;
	FILE* fp=fopen("wash.txt","w+");
	if(fp==NULL)
	{
		printf("Cannot open file\n");
		return;
	}
	while(list_head)
	{
		tmp_node=list_head;
		fprintf(fp,"%s %s %d %d %d\n",tmp_node->name,tmp_node->owner,tmp_node->location,tmp_node->type,tmp_node->date);
		list_head=list_head->next;
		free(tmp_node);
	}
	fclose(fp);
	printf("Saved the file\n");
}

void untracked(cloth_t* list_head)
{
	cloth_t* tmp_node;
	while(list_head)
	{
		tmp_node=list_head;
		list_head=list_head->next;
		free(tmp_node);
	}
	return;
}
