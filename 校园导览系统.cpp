#include <string>
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<conio.h>
#include<time.h>
#include<iostream>
using namespace std;

#define M 20
#define inf 10000
int dist[M][M]; //����
int path[M][M]; //·��

typedef struct LNode
{
    char name[10];
    char pass[10];
    struct LNode *next;
} LNode,*pNode;
//����ڵ�

struct vertex //������Ϣ�ṹ��
{
	int num;   //������
    char name[20];   //��������
	char info[80];   //�������
};


struct maps
{
	int n;   //����
	int m;   //����
	vertex v[M];
	int edgs[M][M];    //�ڽӾ���
}g;

pNode createList();     //��������û����������������
int login(pNode head);
void writeToFile(pNode head);
void registerUser(pNode head);
int menu1();       //�˵�1
void loginsystem();//��¼��ע��ϵͳ
int managesystem();
void create_vertex();
void create_maps();
void search_info();
void floyd();//��������
void floyd_print(int i,int j);
int locatevex(maps g,int v);
int exist(int v);
int delvex(maps &g);
void menu2();  //�˵�2
void guat_map();
time_t convertTimeStrTimeStamp(string str);
int countonlinepeople();

pNode createList()
{
	//�˺�����Ϊ�˹���һ�������洢�û���Ϣ�õġ�
	
	//����ͷ������������ͷ���Ҳ�����������ڣ������ͨ��ͷ��㣬�ҵ��������е�����
    pNode pHead = (pNode)malloc(sizeof(LNode));
    pHead->next=NULL;
    //ͷ��㲻�������
	
	//�Զ��ķ�ʽ��user.txt�ļ�
    FILE *fp = fopen("user.txt","r+");
    if(NULL == fp)
    {
	//���û�и��ļ������˳�����ʾδ�ҵ��ļ�
        printf("FILE NOT FOUND");
        exit(-1);
    }
	
	//��ȡ������ڣ�Ҳ����ͷ���
    pNode cur = pHead;
    while(1)
    {
	//��user.textѭ�������������ݲ����δ�������
	
	//������һ����ʱ�ڵ�
        pNode temp = (pNode)malloc(sizeof(LNode));
        if(!temp)
            exit(-1);
            
		//����fscanf�Ǵ��ļ���ȡ��Ϣ��������ڵ��name������pass����
        //���fscanf�ķ���ֵ����2����˵������û�������ˣ�Ҳ����¼�����
		//��⵽¼����Ϻ󽫷���Ŀռ������
        if(fscanf(fp,"%s%s",temp->name,temp->pass)!=2)
        {
            free(temp);
            break;
        }
		
		//�õ�ǰ�ڵ�(�����β��)�ĺ�����϶�ȡ�����ݵĽڵ�
        cur->next=temp;
		
		//�õ�ǰ�Ľڵ�Ϊ����β��
        cur = temp;

        //ʹ���һ���ڵ�ָ��գ������Ժ��ж�
        cur->next = NULL;
    }
    return pHead;
}


//��¼����
int login(pNode head)
{
	char buffer[80];
	time_t now;
	struct tm *lt;
    if(head->next==NULL)
    {
        printf("user list is empty\n");
        getch();
        return 0;
    }
    char name[10];
    char pass[10];
    printf("enter your name:");
    scanf("%s",name);
    printf("enter your password:");
    scanf("%s",pass);
    pNode temp = head->next;
    while(temp)
    {
        if(0==strcmp(temp->name,name) && 0==strcmp(temp->pass,pass))
        {
            printf("��¼�ɹ���");
			time(&now);
			lt=localtime(&now);
			strftime(buffer,80,"%Y-%m-%d %H:%M:%S",lt);
			FILE *w=fopen("user-login.txt","a");   //��user-login.txt
			fprintf(w,temp->name);
			fprintf(w,"\t");
			fprintf(w,buffer);
			fprintf(w,"\n");//�û����͵�¼ʱ��д��user-login.txt
            return 1;
        }
        temp = temp->next;
    }
    printf("user not found\n");
    return 0;
}


//д��txt�ļ���ÿһ�д���һ���û�
void writeToFile(pNode head)
{
    FILE *fw = fopen("user.txt","w");
    pNode temp=head->next;
    if(temp==NULL){
        return;
    }
    while(temp){
        fprintf(fw,temp->name);
        fprintf(fw,"\t");
        fprintf(fw,temp->pass);
        fprintf(fw,"\n");
        temp  = temp->next;
    }
}

//ע���û�
void registerUser(pNode head)
{
	pNode  L= createList();
	pNode p=L->next; 
    pNode temp = head->next;
    //���������û�ֱ����ͷ����ע��
    if(!temp)
    {
        temp = (pNode)malloc(sizeof(LNode));
        head->next = temp;
    }
    else
    {
        //�������û��������һ���ڵ�������½ڵ�
        while(temp->next)
        {
            temp = temp->next;
        }
        pNode last = (pNode)malloc(sizeof(LNode));
        temp->next = last;
        temp = last;
    }
    printf("enter your name:");
    scanf("%s",temp->name);
	while(p)
	{
		if(strcmp(p->name,temp->name)==0){
			printf("error\n");
			getch();
			exit(-1);
		}
		p=p->next;
	}
    printf("enter your password:");
    scanf("%s",temp->pass);
    temp->next=NULL;
	
}

int menu1()
{
    int choice;
	printf("\t******��ӭʹ�ù���У����ϵͳ******\n");
    printf("\t******        1.��¼          ******\n");
    printf("\t******        2.ע��          ******\n");
    printf("\t******        3.�˳�          ******\n");
    printf("enter your choice:");
    scanf("%d",&choice);
    return choice;
}


void loginsystem()
{
    int choice;
	int key=0;
    pNode head = createList();
	
    while(key==0)
    {
        choice = menu1();
        if(choice==1)
        {
            system("cls");
            if(login(head)==1)
            {
				key=1;
                printf("��������������˵���\n");
				getch();
            }
            system("cls");
        }
        else if(choice==2)
        {
            system("cls");
            registerUser(head);
			writeToFile(head);
            system("cls");
        }
        else if(choice==3)
        {
		    exit(-1);
        }
    }
}


int managesystem()
{
	char password[20]="iammanager";
	char pwd[20];
	char exit[10]="0";
input:printf("�������Ա����(��0�˳�):");
	scanf("%s",pwd);
	if(strcmp(password,pwd)!=0){
		if(strcmp(pwd,exit)==0)
			;
		else{
		printf("����������������룡");
		goto input;
		}
		return 0;
	}
	return 1;
}



void create_vertex()
{
	g.v[0].num=1;
	strcpy(g.v[0].name,"����");
	strcpy(g.v[0].info,"���ֺ��칤ҵѧԺ��У�����ţ����泯���汻��Ϊ����");
     
	g.v[1].num=2;
	strcpy(g.v[1].name,"����¥");
	strcpy(g.v[1].info,"��ѧ¥����ͼ��ݣ�");

	g.v[2].num=3;
	strcpy(g.v[2].name,"�𳵳���");
	strcpy(g.v[2].info,"�ɻ𳵳��ṹ�ɣ��������飬����");

	g.v[3].num=4;
	strcpy(g.v[3].name,"���������");
	strcpy(g.v[3].info,"���Խ������������������ë��");

	g.v[4].num=5;
	strcpy(g.v[4].name,"�����Ļ��㳡");
	strcpy(g.v[4].info,"¶��չʾ������ս����");

	g.v[5].num=6;
	strcpy(g.v[5].name,"�ﾶ��");
	strcpy(g.v[5].info,"�˶�����");

	g.v[6].num=7;
	strcpy(g.v[6].name,"Ѳ��¥");
	strcpy(g.v[6].info,"��ѧ¥");

	g.v[7].num=8;
	strcpy(g.v[7].name,"ͣ����");
	strcpy(g.v[7].info,"ͣ������");

	g.v[8].num=9;
	strcpy(g.v[8].name,"��7");
	strcpy(g.v[8].info,"���Է7�Ź�Ԣ¥");

	g.v[9].num=10;
	strcpy(g.v[9].name,"ʳ��");
	strcpy(g.v[9].info,"�칬¥��ʳ�ã�");

	g.v[10].num=11;
	strcpy(g.v[10].name,"��1");
	strcpy(g.v[10].info,"���Է1�Ź�Ԣ¥");

	g.v[11].num=12;
	strcpy(g.v[11].name,"��͹㳡");
	strcpy(g.v[11].info,"��͹㳡����С������");

	g.v[12].num=13;
	strcpy(g.v[12].name,"��3");
	strcpy(g.v[12].info,"���Է3�Ź�Ԣ¥");

	g.v[13].num=14;
	strcpy(g.v[13].name,"��2");
	strcpy(g.v[13].info,"���Է2�Ź�Ԣ¥");

	g.v[14].num=15;
	strcpy(g.v[14].name,"��5");
	strcpy(g.v[14].info,"���Է5�Ź�Ԣ¥����ְ�����ᣩ");

	g.v[15].num=16;
	strcpy(g.v[15].name,"��4");
	strcpy(g.v[15].info,"���Է4�Ź�Ԣ¥����ְ�����ᣩ");

	g.v[16].num=17;
	strcpy(g.v[16].name,"��6");
	strcpy(g.v[16].info,"���Է6�Ź�Ԣ¥����ְ�����ᣩ");
}



void create_maps()
{
	int i,j;
	g.n=17;
	g.m=25;
	for(i=0;i<g.n;i++)
	{
		for(j=0;j<g.n;j++)
		{
			g.edgs[i][j]=inf;//��ʼ���ڽӾ���
		}
	}
	for(i=0;i<g.n;i++)
	{
		g.edgs[i][i]=0;
		}
	g.edgs[0][1]=g.edgs[1][0]=70;
	g.edgs[1][3]=g.edgs[3][1]=60;
	g.edgs[1][4]=g.edgs[4][1]=60;
	g.edgs[2][3]=g.edgs[3][2]=90;
	g.edgs[3][4]=g.edgs[4][3]=90;
	g.edgs[4][5]=g.edgs[5][4]=30;
	g.edgs[2][6]=g.edgs[6][2]=70;
	g.edgs[3][7]=g.edgs[7][3]=60;
	g.edgs[4][8]=g.edgs[8][4]=60;
	g.edgs[6][7]=g.edgs[7][6]=90;
	g.edgs[7][8]=g.edgs[8][7]=90;
	g.edgs[6][10]=g.edgs[10][6]=60;
	g.edgs[7][11]=g.edgs[11][7]=60;
	g.edgs[8][12]=g.edgs[12][8]=60;
	g.edgs[9][10]=g.edgs[10][9]=90;
	g.edgs[9][13]=g.edgs[13][9]=90;
	g.edgs[10][13]=g.edgs[13][10]=60;
	g.edgs[10][11]=g.edgs[11][10]=90;
	g.edgs[11][12]=g.edgs[12][11]=90;
	g.edgs[11][14]=g.edgs[14][11]=60;
	g.edgs[12][15]=g.edgs[15][12]=60;
	g.edgs[13][14]=g.edgs[14][13]=90;
	g.edgs[14][15]=g.edgs[15][14]=90;
	g.edgs[14][16]=g.edgs[16][14]=75;
	g.edgs[15][16]=g.edgs[16][15]=75;
}



	 
void search_info()
{
	int i,n;
	printf("����У���ľ����У�\n");
		for(i=0;i<17;i++)
		{
			printf("%d:%s\n",g.v[i].num,g.v[i].name);
		}
		while(1)
		{
			printf("����������Ҫ��ѯ�ľ�����(��0�˳�����\n");
			scanf("%d",&n);
			getchar();
			if(n<0||n>17)
			{
				printf("����������������룡\n");
				continue;
			}
			else if(n==0)
			{
				break;
			}
			else
			{
				printf("%d:%s\n",g.v[n-1].num,g.v[n-1].name);
				printf("%s\n",g.v[n-1].info);
			}
		}
}



void floyd()//��������
{
	int i,j,k;
	for(i=0;i<g.n;i++)
	{
		for(j=0;j<g.n;j++)
		{
			dist[i][j]=g.edgs[i][j];     //��ʼ��������·������ dist[]������� path[]·������
			if(i!=j&&dist[i][j]<inf)
			{
				path[i][j]=i;
			}
			else
			{
				path[i][j]=-1;//-1�����ɴ�
			}
		}
	}
	for(k=0;k<g.n;k++)
	{
		for(i=0;i<g.n;i++)
		{
			for(j=0;j<g.n;j++)
			{
				if(dist[i][j]>(dist[i][k]+dist[k][j]))
				{
					dist[i][j]=dist[i][k]+dist[k][j];  //���¾������
					path[i][j]=k;     //path���ڼ�¼���·���ϵĽ��
				}
			}
		}
	}
}


void floyd_print(int i,int j)
{
	if(path[i][j]==i||path[i][j]==j)
	{
		return ;
	}
	else{
		floyd_print(i,path[i][j]);           //���м����Ϊ�յ������ӡ·��
		printf("%s->",g.v[path[i][j]].name); //��ӡ�м侰������
		floyd_print(path[i][j],j);           //���м����Ϊ��������ӡ·��
	}
}


int locatevex(maps g,int v)//locatevex
{	int i;
	for(i=0;i<g.n;i++)
	  if(v==g.v[i].num)  return i;//�ҵ������ض������i 
 	return -1;//û���ҵ�������� 
} 


int exist(int v)
{
	int i;
	int count=0;
	int m=locatevex(g,v);

	for(i=0;i<g.n;i++){
		if(g.edgs[i][m]==inf&&g.edgs[m][i]==inf)
			count++;
	}
	if(count==g.n-1){
		printf("%s���ܷ���!",g.v[m].name);
		return -1;}
	else
		return 1;
}


int delvex(maps &g)
{	int i,j,v; 
	printf("\n�����벻�ܷ��ʵľ����ţ�");
	scanf("%d",&v);
	while(v<1||v>17)
	{	printf("\n�����������������:");
		scanf("%d",&v);
	}
	int m=locatevex(g,v);
	if(m==-1)
	{
		return 0;
	}

	for(i=0;i<g.n;i++)
	{
		if(g.edgs[i][m]>0&&g.edgs[i][m]!=inf){
		g.edgs[i][m]=g.edgs[m][i]=inf;
		g.m=g.m-1;}
	}

}


void menu2()
{
	printf("\n");
	printf("**********��ӭʹ�ù���У������ϵͳ**********\n\n");
	printf("     *****1.����У��������Ϣ��ѯ*****       \n");
	printf("     *****2.������֮�����·����ѯ*****       \n");
	printf("     *****3.��̬����·��          *****       \n");
	printf("     *****4.�鿴ʹ��ϵͳ����      *****       \n");
	printf("     *****5.�˳�ϵͳ              *****       \n");
}


void guat_map()
{
	printf("                              *****����У��ƽ��ͼ*****                              \n\n");
	printf("                                       1.����                                           \n");
	printf("                                          |                                             \n");
	printf("                                          |                                             \n");
	printf("                                       2.����¥                                         \n");
	printf("                                          / \\                                           \n");
	printf("                                         /   \\                 6.                       \n");
	printf("                3.�����---4.���������---5.�����Ļ��㳡--- ��                      \n");
	printf("                      |           |               |             ��                      \n");
	printf("                7.Ѳ��¥---- 8.ͣ����      --- 9.��7        --- ��                      \n");
	printf("                    |             |               |                                     \n");
	printf("  10.�칬(ʳ��) --11.��1  ---- 12.��͹㳡   ---13.��3                                  \n");
	printf("                \\   |             |               |                                     \n");
	printf("                 14.��2   ----15.��5        ---16.��4                                   \n");
	printf("                                 \\               /                                      \n");
    printf("                                  \\             /                                       \n");
	printf("                                      17.�� 6                                           \n");
}


time_t convertTimeStrTimeStamp(string str){
	struct tm tm_;  
    int year, month, day, hour, minute,second;  
    sscanf(str.c_str(),"%d-%d-%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second);  
    tm_.tm_year  = year-1900;  
    tm_.tm_mon   = month-1;  
    tm_.tm_mday  = day;  
    tm_.tm_hour  = hour;  
    tm_.tm_min   = minute;  
    tm_.tm_sec   = second;  
    tm_.tm_isdst = 0;  
  
    time_t timeStamp = mktime(&tm_); //�Ѿ�����8��ʱ��  
    return timeStamp; //��ʱ��  

}


  int countonlinepeople()
  {
	char begin[40],end[40];
    printf("��������ʼʱ��(��ʽ��2022-01-01 00:00:00):\n");
	cin.ignore();
	cin.getline(begin,40);
	printf("��������ֹʱ��(��ʽ��2022-01-01 00:00:00):\n");
	cin.getline(end,40);

	long beginstamp=convertTimeStrTimeStamp(begin);
	long endstamp=convertTimeStrTimeStamp(end);
    //1:�����ļ������ļ�ָ����=fopen���ļ���,ʹ���ļ���ʽ����ʧ���򷵻�NULL;
    FILE *fp=fopen("user-login.txt","r"); //��data.txt�ļ�Ϊ��
	
    //2:����ļ��Ƿ�򿪳ɹ���
    if(!fp){
       printf("��ʧ�ܣ�\n");
       return -1; //�����쳣
    }
    //3:
    //��������һ����������
    char  name[20], date[40],time[40];//�������������ַ�������
	long datestamp;
	int count=0;
    while(!feof(fp)) //feof�������һ���ļ��Ƿ�������������ļ�β�����������򷵻ط�0ֵ�����򷵻�0
    { 
           fscanf(fp,"%s%s%s\n",name,date,time); 
		   strcat(date," ");
		   strcat(date,time);
		   datestamp=convertTimeStrTimeStamp(date);
		   if(datestamp>=beginstamp&&datestamp<=endstamp)
			   count=count+1;
    }
    
 
    //����ȡ���
	//printf("%s %s %s\n",name,date,time);
    //�ر���
    fclose(fp);
	printf("��%s��%s��һ��ʱ�����%d��ʹ�ù���ϵͳ!\n",begin,end,count);
 }


int main()
{
	int i,n;
	int begin,end;
	loginsystem();
	create_vertex();
	create_maps();
	guat_map();
	/*for(int m=0;m<g.n;m++){            //���egds����
		for(int n=0;n<g.n;n++){
			printf("%d\t",g.edgs[m][n]);
		}
		printf("\n");
	}*/

	while(1)
	{
		menu2();
		printf("�������ָ�\n");
		scanf("%d",&n);
		if(n<1||n>5)
		{
			printf("����������������룡����\n");
			continue;
		}
		else
		{
			if(n==1)
			{
				search_info();
			}
			else if(n==2)
			{
				guat_map();
				printf("��������㾰��ı�ţ�\n");
				scanf("%d",&begin);
				printf("�������յ㾰��ı�ţ�\n");
				scanf("%d",&end);
				if(begin==end){
					printf("����Ŀ�ĵأ����������� \n");
				}
				else
				{
				if(exist(end)==-1||exist(begin)==-1)
					continue;
				floyd();
				printf("��%s��%s����̾����ǣ�%d\n",g.v[begin-1].name,g.v[end-1].name,dist[begin-1][end-1]);
				printf("%s->",g.v[begin-1].name);
				floyd_print(begin-1,end-1);
				printf("%s\n",g.v[end-1].name);
				}
			}
			else if(n==3)
			{
				if(managesystem()==1)
				         delvex(g);

			}
			else if(n==4)
			{
				countonlinepeople();
			}
			else if(n==5)
			{
				return 0;
			}
		}
	}
	return 0;
}







