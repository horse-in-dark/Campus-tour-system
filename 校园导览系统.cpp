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
int dist[M][M]; //距离
int path[M][M]; //路径

typedef struct LNode
{
    char name[10];
    char pass[10];
    struct LNode *next;
} LNode,*pNode;
//定义节点

struct vertex //景点信息结构体
{
	int num;   //景点编号
    char name[20];   //景点名称
	char info[80];   //景点介绍
};


struct maps
{
	int n;   //点数
	int m;   //边数
	vertex v[M];
	int edgs[M][M];    //邻接矩阵
}g;

pNode createList();     //创建存放用户姓名和密码的链表
int login(pNode head);
void writeToFile(pNode head);
void registerUser(pNode head);
int menu1();       //菜单1
void loginsystem();//登录与注册系统
int managesystem();
void create_vertex();
void create_maps();
void search_info();
void floyd();//弗洛伊德
void floyd_print(int i,int j);
int locatevex(maps g,int v);
int exist(int v);
int delvex(maps &g);
void menu2();  //菜单2
void guat_map();
time_t convertTimeStrTimeStamp(string str);
int countonlinepeople();

pNode createList()
{
	//此函数是为了构造一个链表，存储用户信息用的。
	
	//链表头结点声明，这个头结点也就是链表的入口，你可以通过头结点，找到链表所有的数据
    pNode pHead = (pNode)malloc(sizeof(LNode));
    pHead->next=NULL;
    //头结点不存放数据
	
	//以读的方式打开user.txt文件
    FILE *fp = fopen("user.txt","r+");
    if(NULL == fp)
    {
	//如果没有该文件，则退出并显示未找到文件
        printf("FILE NOT FOUND");
        exit(-1);
    }
	
	//获取链表入口，也就是头结点
    pNode cur = pHead;
    while(1)
    {
	//从user.text循环读入所有数据并依次存于链表
	
	//先制造一个临时节点
        pNode temp = (pNode)malloc(sizeof(LNode));
        if(!temp)
            exit(-1);
            
		//下面fscanf是从文件读取信息，并存入节点的name变量和pass变量
        //如果fscanf的返回值不是2，则说明后面没有数据了，也即是录入完毕
		//检测到录入完毕后将分配的空间清除掉
        if(fscanf(fp,"%s%s",temp->name,temp->pass)!=2)
        {
            free(temp);
            break;
        }
		
		//让当前节点(链表的尾部)的后面加上读取到数据的节点
        cur->next=temp;
		
		//让当前的节点为链表尾部
        cur = temp;

        //使最后一个节点指向空，方便以后判断
        cur->next = NULL;
    }
    return pHead;
}


//登录函数
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
            printf("登录成功！");
			time(&now);
			lt=localtime(&now);
			strftime(buffer,80,"%Y-%m-%d %H:%M:%S",lt);
			FILE *w=fopen("user-login.txt","a");   //打开user-login.txt
			fprintf(w,temp->name);
			fprintf(w,"\t");
			fprintf(w,buffer);
			fprintf(w,"\n");//用户名和登录时间写入user-login.txt
            return 1;
        }
        temp = temp->next;
    }
    printf("user not found\n");
    return 0;
}


//写入txt文件，每一行存在一个用户
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

//注册用户
void registerUser(pNode head)
{
	pNode  L= createList();
	pNode p=L->next; 
    pNode temp = head->next;
    //当表中无用户直接在头结点后注册
    if(!temp)
    {
        temp = (pNode)malloc(sizeof(LNode));
        head->next = temp;
    }
    else
    {
        //表中有用户则在最后一个节点后生成新节点
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
	printf("\t******欢迎使用桂航南校导览系统******\n");
    printf("\t******        1.登录          ******\n");
    printf("\t******        2.注册          ******\n");
    printf("\t******        3.退出          ******\n");
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
                printf("按任意键进入主菜单：\n");
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
input:printf("输入管理员密码(按0退出):");
	scanf("%s",pwd);
	if(strcmp(password,pwd)!=0){
		if(strcmp(pwd,exit)==0)
			;
		else{
		printf("输入错误，请重新输入！");
		goto input;
		}
		return 0;
	}
	return 1;
}



void create_vertex()
{
	g.v[0].num=1;
	strcpy(g.v[0].name,"北门");
	strcpy(g.v[0].info,"桂林航天工业学院南校区大门，因面朝北面被称为北门");
     
	g.v[1].num=2;
	strcpy(g.v[1].name,"飞天楼");
	strcpy(g.v[1].info,"教学楼（含图书馆）");

	g.v[2].num=3;
	strcpy(g.v[2].name,"火车车吧");
	strcpy(g.v[2].info,"由火车车厢构成，可以买书，看书");

	g.v[3].num=4;
	strcpy(g.v[3].name,"体育活动中心");
	strcpy(g.v[3].info,"可以进行体育活动，如排球、羽毛球");

	g.v[4].num=5;
	strcpy(g.v[4].name,"航空文化广场");
	strcpy(g.v[4].info,"露天展示着两架战斗机");

	g.v[5].num=6;
	strcpy(g.v[5].name,"田径场");
	strcpy(g.v[5].info,"运动场所");

	g.v[6].num=7;
	strcpy(g.v[6].name,"巡天楼");
	strcpy(g.v[6].info,"教学楼");

	g.v[7].num=8;
	strcpy(g.v[7].name,"停车场");
	strcpy(g.v[7].info,"停车场所");

	g.v[8].num=9;
	strcpy(g.v[8].name,"天7");
	strcpy(g.v[8].info,"天和苑7号公寓楼");

	g.v[9].num=10;
	strcpy(g.v[9].name,"食堂");
	strcpy(g.v[9].info,"天宫楼（食堂）");

	g.v[10].num=11;
	strcpy(g.v[10].name,"天1");
	strcpy(g.v[10].info,"天和苑1号公寓楼");

	g.v[11].num=12;
	strcpy(g.v[11].name,"天和广场");
	strcpy(g.v[11].info,"天和广场（含小鱼塘）");

	g.v[12].num=13;
	strcpy(g.v[12].name,"天3");
	strcpy(g.v[12].info,"天和苑3号公寓楼");

	g.v[13].num=14;
	strcpy(g.v[13].name,"天2");
	strcpy(g.v[13].info,"天和苑2号公寓楼");

	g.v[14].num=15;
	strcpy(g.v[14].name,"天5");
	strcpy(g.v[14].info,"天和苑5号公寓楼（教职工宿舍）");

	g.v[15].num=16;
	strcpy(g.v[15].name,"天4");
	strcpy(g.v[15].info,"天和苑4号公寓楼（教职工宿舍）");

	g.v[16].num=17;
	strcpy(g.v[16].name,"天6");
	strcpy(g.v[16].info,"天和苑6号公寓楼（教职工宿舍）");
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
			g.edgs[i][j]=inf;//初始化邻接矩阵
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
	printf("桂航南校区的景点有：\n");
		for(i=0;i<17;i++)
		{
			printf("%d:%s\n",g.v[i].num,g.v[i].name);
		}
		while(1)
		{
			printf("请输入你想要查询的景点编号(按0退出）：\n");
			scanf("%d",&n);
			getchar();
			if(n<0||n>17)
			{
				printf("输入错误，请重新输入！\n");
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



void floyd()//弗洛伊德
{
	int i,j,k;
	for(i=0;i<g.n;i++)
	{
		for(j=0;j<g.n;j++)
		{
			dist[i][j]=g.edgs[i][j];     //初始化距离与路径矩阵 dist[]距离矩阵 path[]路径矩阵
			if(i!=j&&dist[i][j]<inf)
			{
				path[i][j]=i;
			}
			else
			{
				path[i][j]=-1;//-1代表不可达
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
					dist[i][j]=dist[i][k]+dist[k][j];  //更新距离矩阵
					path[i][j]=k;     //path用于记录最短路径上的结点
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
		floyd_print(i,path[i][j]);           //将中间点作为终点继续打印路径
		printf("%s->",g.v[path[i][j]].name); //打印中间景点名字
		floyd_print(path[i][j],j);           //将中间点作为起点继续打印路径
	}
}


int locatevex(maps g,int v)//locatevex
{	int i;
	for(i=0;i<g.n;i++)
	  if(v==g.v[i].num)  return i;//找到，返回顶点序号i 
 	return -1;//没有找到这个顶点 
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
		printf("%s不能访问!",g.v[m].name);
		return -1;}
	else
		return 1;
}


int delvex(maps &g)
{	int i,j,v; 
	printf("\n请输入不能访问的景点编号：");
	scanf("%d",&v);
	while(v<1||v>17)
	{	printf("\n输入错误！请重新输入:");
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
	printf("**********欢迎使用桂航南校区导览系统**********\n\n");
	printf("     *****1.桂航南校区景点信息查询*****       \n");
	printf("     *****2.两景点之间最短路径查询*****       \n");
	printf("     *****3.动态更新路线          *****       \n");
	printf("     *****4.查看使用系统人数      *****       \n");
	printf("     *****5.退出系统              *****       \n");
}


void guat_map()
{
	printf("                              *****桂航南校区平面图*****                              \n\n");
	printf("                                       1.北门                                           \n");
	printf("                                          |                                             \n");
	printf("                                          |                                             \n");
	printf("                                       2.飞天楼                                         \n");
	printf("                                          / \\                                           \n");
	printf("                                         /   \\                 6.                       \n");
	printf("                3.火车书吧---4.体育活动中心---5.航空文化广场--- 田                      \n");
	printf("                      |           |               |             径                      \n");
	printf("                7.巡天楼---- 8.停车场      --- 9.天7        --- 场                      \n");
	printf("                    |             |               |                                     \n");
	printf("  10.天宫(食堂) --11.天1  ---- 12.天和广场   ---13.天3                                  \n");
	printf("                \\   |             |               |                                     \n");
	printf("                 14.天2   ----15.天5        ---16.天4                                   \n");
	printf("                                 \\               /                                      \n");
    printf("                                  \\             /                                       \n");
	printf("                                      17.天 6                                           \n");
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
  
    time_t timeStamp = mktime(&tm_); //已经减了8个时区  
    return timeStamp; //秒时间  

}


  int countonlinepeople()
  {
	char begin[40],end[40];
    printf("请输入起始时间(格式如2022-01-01 00:00:00):\n");
	cin.ignore();
	cin.getline(begin,40);
	printf("请输入终止时间(格式如2022-01-01 00:00:00):\n");
	cin.getline(end,40);

	long beginstamp=convertTimeStrTimeStamp(begin);
	long endstamp=convertTimeStrTimeStamp(end);
    //1:创建文件流，文件指针名=fopen（文件名,使用文件方式）打开失败则返回NULL;
    FILE *fp=fopen("user-login.txt","r"); //以data.txt文件为例
	
    //2:检测文件是否打开成功；
    if(!fp){
       printf("打开失败！\n");
       return -1; //返回异常
    }
    //3:
    //用来储存一个整型数据
    char  name[20], date[40],time[40];//用来储存两个字符串数据
	long datestamp;
	int count=0;
    while(!feof(fp)) //feof（）检测一个文件是否结束，即到达文件尾，若结束，则返回非0值，否则返回0
    { 
           fscanf(fp,"%s%s%s\n",name,date,time); 
		   strcat(date," ");
		   strcat(date,time);
		   datestamp=convertTimeStrTimeStamp(date);
		   if(datestamp>=beginstamp&&datestamp<=endstamp)
			   count=count+1;
    }
    
 
    //检测读取结果
	//printf("%s %s %s\n",name,date,time);
    //关闭流
    fclose(fp);
	printf("在%s到%s的一段时间里，有%d人使用过该系统!\n",begin,end,count);
 }


int main()
{
	int i,n;
	int begin,end;
	loginsystem();
	create_vertex();
	create_maps();
	guat_map();
	/*for(int m=0;m<g.n;m++){            //输出egds矩阵
		for(int n=0;n<g.n;n++){
			printf("%d\t",g.edgs[m][n]);
		}
		printf("\n");
	}*/

	while(1)
	{
		menu2();
		printf("输入操作指令：\n");
		scanf("%d",&n);
		if(n<1||n>5)
		{
			printf("输入错误，请重新输入！！！\n");
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
				printf("请输入起点景点的编号：\n");
				scanf("%d",&begin);
				printf("请输入终点景点的编号：\n");
				scanf("%d",&end);
				if(begin==end){
					printf("已在目的地！请重请输入 \n");
				}
				else
				{
				if(exist(end)==-1||exist(begin)==-1)
					continue;
				floyd();
				printf("从%s到%s的最短距离是：%d\n",g.v[begin-1].name,g.v[end-1].name,dist[begin-1][end-1]);
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







