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
void add(cloth_t** list_head,cloth_t*(*func)(cloth_t*,char*));
cloth_t* search(cloth_t* list_head,char* name);
void wash_date(cloth_t* tmp_node,int);
void show_info(cloth_t* list_head,cloth_t*(*func)(cloth_t*,char*),void(*func_)(cloth_t*,int));
void change_info(cloth_t* list_head,cloth_t*(*func)(cloth_t*,char*));
void delete(cloth_t* list_head,cloth_t*(*func)(cloth_t*,char*));
void open_closet(cloth_t* list_head);
void wash_method(cloth_t* list_head,cloth_t*(*func)(cloth_t*,char*));
void save(cloth_t* list_head);
void untracked(cloth_t* list_head);
void quit(cloth_t* list_head);
int choice();
void main()
{
	int num=0;
	int q=0;
	int quit_num=0;
	cloth_t* list_head=NULL;
	FILE* fp=NULL;

	while(1)
	{	int save_choice;
		q=choice();
		switch(q)
		{
			case 0:
				list_head=open(list_head);
				break;
			case 1:
				add(&list_head,search);
				break;
			case 2:
				show_info(list_head,search,wash_date);
				break;
			case 3:
				change_info(list_head,search);
				break;
			case 4:
				delete(list_head,search);
				break;
			case 5:
				open_closet(list_head);
				break;
			case 6:	
				wash_method(list_head,search);
				break;
			case 7:
				save(list_head);
				break;
			case 8:
				quit(list_head);
				quit_num=1;
				break;
			default:
				printf("잘못된 숫자 입력\n");
				break;
		}
		if(quit_num==1)
			break;
	}
}
int choice()
{
	int choice;
	printf("<Select the function>\n");
	printf("0. Load the file\n");
	printf("1. Add cloth\n");
	printf("2. Show cloth's information\n");
	printf("3. Change the cloth's information\n");
	printf("4. Delete the cloth\n");
	printf("5. Open the closet\n");
	printf("6. Washing method\n");
	printf("7. Save the file\n");
	printf("8. Quit\n");

	printf("Enter your choice number : ");
	scanf("%d",&choice);
	return choice;
}
void add(cloth_t** list_head,cloth_t*(*func)(cloth_t*,char*))
{	
	cloth_t* tmp_node;
	cloth_t* new_node;
	char name[30];
	new_node=(cloth_t*) malloc (sizeof(cloth_t));
	
	printf("옷 이름 : ");
	scanf("%s",name);
	
	tmp_node=func(*list_head,name);
	if(tmp_node)
	{
		printf("이미 존재하는 옷입니다.\n");
		return;
	}
	
	strcpy(new_node->name,name);
	printf("옷 주인 : ");	
	scanf("%s",new_node->owner);
	
	printf("1.Room1\n2.Room2\n3.Room3\n4.Dryer\n5.Washing Machine\n6.Laundry Basket\n7.Laundry Store\n");
	printf("옷 위치 : ");
	scanf("%d",&new_node->location);

	printf("1.Shirts\n2.Jumper\n3.Knit\n4.Cotton\n5.Jean\n");
	printf("옷 종류 : ");
	scanf("%d",&new_node->type);

	printf("최근 세탁 날짜 (ex)1102, 403..) : ");
	scanf("%d",&new_node->date);
	
	new_node->next=*list_head;
	*list_head=new_node;
	return;	
	
}
cloth_t* open(cloth_t* list_head)
{
	char file[30];
	printf("불러올 파일 이름 : ");	
	scanf("%s",file);
	cloth_t* new_node;
	FILE* fp=fopen(file,"r+");
	
	if(fp==NULL)
	{
		printf("Cannot open file\n");
		return NULL;
	}
	
	while(1)
	{
		new_node=(cloth_t*) malloc (sizeof(cloth_t));
		if(feof(fp)!=0)
			break;
		fscanf(fp,"%s %s %d %d %d\n", new_node->name,new_node->owner,&new_node->location,&new_node->type,&new_node->date);
		
		new_node->next=list_head;
		list_head=new_node;
	}
	fclose(fp);
	printf("Loaded the file\n");
	return list_head;
}

void show_info(cloth_t* list_head,cloth_t*(*func)(cloth_t*,char*),void(*func_)(cloth_t*,int))
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
		func_(tmp_node,tmp_node->location);
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
void wash_date(cloth_t* tmp_node,int location)
{
	int w_date;
	int w_day;
	int t_day;
	int w_month;
	int t_month;
	if ((location==5)||(location==6)||(location==7))
		return;
	printf("오늘 날짜를 입력하세요 : ");
	scanf("%d",&w_date);
	w_month=w_date/100;
	t_month=(tmp_node->date)/100;
	w_day=w_date%100;
	t_day=(tmp_node->date)%100;
	if( w_month==t_month)
	{
		if(w_day-t_day>=7)
			printf("세탁한지 일주일이 넘었습니다.\n 세탁하세요.\n");
		else
			printf("세탁한지 얼마 안되었군요.\n입어도 좋습니다.\n");
	}
	else
		printf("이번 달에 아직 세탁하지 않은 옷입니다.\n세탁하세요.\n");

}
void save(cloth_t* list_head)
{	
	char file[30];
	printf("내용을 저장할 파일 이름(파일의 원본 내용은 삭제되니 주의하세요): ");
	scanf("%s",file); 
	cloth_t* tmp_node;
	FILE* fp=fopen(file,"w+");
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

void change_info(cloth_t* list_head,cloth_t*(*func)(cloth_t*,char*))
{
	cloth_t* tmp_node;
	char name[30];
	char owner[30];
	int loc;
	int d;
	int change_choice;
	printf("수정하고 싶은 옷 이름 : ");
	scanf("%s",name);
	tmp_node=func(list_head,name);
	if(tmp_node==NULL)
	{
		printf("존재하지 않는 옷입니다.\n");
		return;
	}	
	printf("수정하고 싶은 항목을 선택해주세요.\n");
	printf("1. 옷 주인\n2. 옷 위치\n3.최근 세탁 날짜\n");
	scanf("%d",&change_choice);

	switch(change_choice)
	{
		case 1:
			printf("새로운 옷 주인 : ");
			scanf("%s",owner);
			strcpy(tmp_node->owner,owner);
			break;
		case 2:
			printf("1.Room1\n2.Room2\n3.Room3\n4.Dryer\n5.Washing Machine\n6.Laundry Basket\n7.Laundry Store\n");
			printf("새로운 옷 위치 : ");
			scanf("%d",&loc);
			tmp_node->location=loc;
			break;
		case 3:
			printf("최근 세탁 날짜 (ex)1102, 403..) : ");
			scanf("%d",&d);
			tmp_node->date=d;
			break;
		default:
			printf("옳지 못한 번호입니다.\n");
			break;
	}
}

void delete(cloth_t* list_head,cloth_t*(*func)(cloth_t*,char*))
{
	cloth_t* tmp_node;
	cloth_t* pre;
	cloth_t* buffer;
	char name[30];
	int del_choice;
	int num=0;
	printf("삭제하고 싶은 옷 이름 : ");
	scanf("%s",name);
	tmp_node=func(list_head,name);
	if(tmp_node==NULL)
	{
		printf("존재하지 않는 옷입니다.\n");
		return;
	}
	printf("정말 삭제하시겠습니까?\n1.Yes\n2.No\n");
	scanf("%d",&del_choice);
	if (del_choice==1)		
	{	
		if(strcmp(list_head->name,name)==0)
		{
			buffer=list_head;
			list_head=list_head->next;
			free(buffer);
			printf("삭제되었습니다.\n");
			return;
		}
		buffer=list_head;
		while(buffer!=NULL)
		{	
			pre=buffer;
			buffer=buffer->next;
			if(strcmp(buffer->name,name)==0)
			{	
				pre->next=buffer->next;
				free(buffer);
				return;
			}
		}	
	}
}
void open_closet(cloth_t* list_head)
{	
	cloth_t* tmp_node;
	int closet_choice;
	int count=0;
	printf("확인할 옷장을 선택하세요.\n");
	printf("1.Room1\n2.Room2\n3.Room3\n4.Dryer\n5.Washing Machine\n6.Laundry Basket\n7.Laundry Store\n");	
	scanf("%d",&closet_choice);

	while(list_head)
    {
        tmp_node=list_head;
        if(tmp_node->location==closet_choice)
		{	printf("%s\n",tmp_node->name);
			if(closet_choice==6)
				count++;}
        list_head=list_head->next;
 	}
	if(closet_choice==6)
	{	printf("현재 빨래통에 %d개의 빨래감이 있습니다.\n",count);
		if(count>=10)
			printf("빨래하시길 권합니다.\n");
	}
}
void wash_method(cloth_t* list_head,cloth_t*(*func)(cloth_t*,char*))
{	
	cloth_t* tmp_node;
	char name[30];
	printf("세탁방법을 알고 싶은 옷 이름 : ");
	scanf("%s",name);
	tmp_node=func(list_head,name);
	if(tmp_node==NULL)
	{	printf("존재하지 않는 옷입니다.\n");
		return;}
	switch(tmp_node->type)
	{
		case 1:
			printf("셔츠 종류의 옷이군요.\n집에서 세탁 후 다리미질을 하시거나 세탁소에 맡기는 것을 추천해요.\n");
			break;
		case 2:
			printf("점퍼 종류의 옷이군요.\n집에서 세탁해도 문제는 없지만 될 수 있으면 세탁소에 맡기세요.\n");
			break;
		case 3:
			printf("니트 종류의 옷이군요.\n처음 세탁 시 세탁소에 맡기고 그 이후부터는 손세탁하는 것을 추천해요.\n");
			break;
		case 4:
			printf("면 종류의 옷이군요.\n집에서 세탁기를 이용하시면 됩니다.\n");
			break;
		case 5:
			printf("청바지 종류의 옷이군요.\n청색 물이 빠질 수 있으니 흰 옷과는 절대 세탁하지 말아주세요.\n집에서 세탁기를 이용하시면 됩니다.\n");
			break;
		default:
			break;
	}		
}

void quit(cloth_t* list_head)
{
	int quit_choice;
	printf("변경사항을 저장하시겠습니까?\n");
	printf("1.Yes\n2.No\n");
	scanf("%d",&quit_choice);
	if(quit_choice==1)
		save(list_head);
	untracked(list_head);
	return;
}
