#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#define LEN sizeof(LNode)
using namespace std;
int seat;     //通讯录成员的序号

typedef struct LNode
{
    int number;
    double telenum;
    char name[20];
    char street[20];
    char city[20];
    int eip;
    char country[20];
    struct LNode *next;
} LNode,*LinkList;
//用于通讯录结点

void printList(LinkList L)
{
    // 打印头结点地址为L的通讯录
    printf("\n          --------------------------------------------------------------------------------------------\n");
    printf("               学号       姓名     电话号码         国家          城市          街道             邮编\n");
    printf("          ----------------------------------------------------------------------------------------------\n");
    LinkList p=L;
    int n=1;
    if(L==NULL||L->next==NULL) printf("该通讯录中没有元素\n");
    else
        while(p->next !=NULL)
        {
            printf("          %2d   %-9d",n,p->next->number);
            printf("    %-5s  %.0f  %8s  %12s  %13s  %14d\n",p->next->name,p->next->telenum,p->next->country,p->next->city,p->next->street,p->next->eip);
            p=p->next;
            n++;
        }
    printf("          ---------------------------------------------------------------------------------------------\n");
    return ;
}

LinkList prior(LinkList L,LinkList p)  //获取当前元素的前一个元素的地址
{
    if(L->next==NULL) return(L);  //若第一个节点空,返回头结点
    LinkList p_prior=L;
    while(p_prior->next != p)  //第一个节点和p不等时
    {
        p_prior=p_prior->next;
    }
    return (p_prior);
}

void insertYouXu(LinkList L,LinkList Elem)
{
    //插入一个元素，使原有序表仍为有序
    LinkList p=L->next;    //p第一个节点
    while(p!=NULL && Elem->number>=p->number)
    {
        if(p->number==Elem->number)
        {
            printf("重复输入！！\n");
            return;
        }
        p=p->next;
    }         //确定Elem插入的位置
    if(p==NULL)
    {
        p=prior(L,p);
        Elem->next=NULL;
        p->next=Elem;
    }
    else       //若为空表，插到头结点之后
    {
        p=prior(L,p);
        Elem->next=p->next;
        p->next=Elem;
    }
}

LinkList creatIncreLink()
{
    LinkList L=(LinkList)malloc(LEN);  //头结点
    L->next=NULL;
    LinkList p;
    int num=1;

    int number;
    double telenum;
    char name[20];
    char country[20];
    char city[20];
    char street[20];
    int eip;
    printf("请输入学生学号、姓名和电话号码，建立通讯录，以'-1'为输入结束标志\n");
    printf("请输入学号 %d：",num);
    cin>>number;
    printf("请输入姓名 %d: ",num);
    cin>>name;
    printf("请输入电话号码 %d：",num);
    cin>>telenum;
    printf("请输入国家 %d：",num);
    cin>>country;
    printf("请输入城市 %d：",num);
    cin>>city;
    printf("请输入街道 %d：",num);
    cin>>street;
    printf("请输入邮编 %d：",num);
    cin>>eip;
    while (number>=0)  //以-1位结束标志
    {
        p=(LinkList)malloc(LEN); //新结点
        p->number=number;
        p->telenum=telenum;
        strcpy(p->name,name); //将name复制到p->name
        strcpy(p->country,country);
        strcpy(p->city,city);
        strcpy(p->street,street);
        p->eip=eip;
        insertYouXu(L,p);       //有序的插入新结点
        num++;                  //num++输入第二个学生的信息
        printf("请输入学号 %d：",num);
        scanf("%d",&number);
        printf("请输入姓名 %d: ",num);
        cin>>name;
        printf("请输入电话号码 %d：",num);
        cin>>telenum;
        printf("请输入国家 %d：",num);
        cin>>country;
        printf("请输入城市 %d：",num);
        cin>>city;
        printf("请输入街道 %d：",num);
        cin>>street;
        printf("请输入邮编 %d：",num);
        cin>>eip;
    }
    return(L);
}


void deleteElem(LinkList L,int i)       //从通讯录中删除第i个元素
{
    LinkList p=L;
    int j=0;
    while (p->next&&j<i-1)
    {
        p = p->next;
        j++;
    }
    if(!(p->next)) //如果第一个节点不存在,则
    {
        printf("第%d个元素删除失败\n",i);
        return ;
    }

    LinkList q = p->next;
    p->next = q->next;
    free(q);
}

int searchNum(LinkList L,int n)
{
    // 按学号查找通讯者
    int flag=0;
    LinkList p=L->next;
    seat=1;
    if(L->next==NULL) printf("该链表中没有元素,查找失败\n");
    else
    {
        while(p !=NULL)
        {
            if(p->number<=n)
                if(p->number==n)
                {
                    flag=1;
                    printf("要查找的是第%d位通讯者：\n",seat);
                    printf("                        学号: %d   姓名: %s   电话号码.:%.0f  国家:%s  城市:%s  街道:%s  邮编:%d\n",p->number,p->name,p->telenum,p->country,p->city,p->street,p->eip);
                }
            p=p->next;
            seat++;//!!!!
        }
    }
    return flag;
}

int searchName(LinkList L,char n[])
{
    int flag=0;     //设置一个标志,看是否匹配
    LinkList p=L->next;
    seat=1;
    if(L->next==NULL||L==NULL)   //第一个节点空或者链表空
        printf("该通讯录中没有元素,查找失败\n");
    else
    {
        while(p !=NULL)
        {
            if(!strcmp(p->name,n))  //比较p->name和输入的n,相同返回0,
            {
                flag=1;            //标志匹配成功
                printf("要查找的是第%d位通讯者：\n",seat);
                printf("                        Number: %d   Name: %s   TeleNo.:%.0f Country: %s  City: %s  Street: %s  eip: %d\n",p->number,p->name,p->telenum,p->country,p->city,p->street,p->eip);
            }
            p=p->next;
            seat++;
        }
    }
    return flag;
}

int delNum(LinkList L,int n)
{
    // 按学号删除通讯者
    int flag=0;
    LinkList p=L->next;
    seat=1;
    if(L->next==NULL)
        printf("该链表中没有元素,删除失败\n");
    else
    {
        while(p !=NULL)
        {
            if(p->number<=n)
            {
                if(p->number==n)
                {
                    flag=1;
                    printf("%d ",p->number);
                    p=p->next;
                    deleteElem(L,seat);

                }
            }
            else
            {
                p=p->next;
                seat++;
            }
        }
        printf("被删除\n");
    }
    return flag;
}


int delName(LinkList L,char n[])
{
    // 按姓名删除通讯者
    int flag=0;
    LinkList p=L->next;  //p为第一个节点
    seat=1;
    if(L->next==NULL)
        printf("该链表中没有元素,查找失败\n");
    else
    {
        while(p !=NULL)
        {
            if(!strcmp(p->name,n))
            {
                flag=1;
                printf("%s ",p->name); //如果匹配到了,则输出xxx被删除
                p=p->next;
                deleteElem(L,seat);
            }
            else
            {
                p=p->next;
                seat++;
            }
        }
        if(flag)printf("被删除\n");
    }
    return flag;
}

void write(LinkList L)
{
    ofstream output("test.txt"); //将数据流和文件进行关联
    LinkList p=L;
    while(p->next !=NULL)
    {
        output<<p->next->number<<setw(10)<<p->next->name<<setw(12)<<p->next->telenum<<setw(10)<<p->next->country<<setw(16)<<p->next->city<<setw(20)<<p->next->street<<setw(20)<<p->next->eip<<endl;
        p = p->next;
    }
}


void read(string file) //逐行读入
{
    ifstream ifs;  //将数据流和文件进行关联
    ifs.open(file.data());   //将文件流对象与文件连接起来
    string s;
    while(getline(ifs,s))
    {
        cout<<s<<endl;
    }
    ifs.close();
}
int main(void)
{
//system("color 1f");
    LinkList L=NULL;
    printf("\n           ***************** ^@^欢迎使用通讯录系统***********\n");
    printf("           *               1 通讯录的建立                   *\n");
    printf("           *               2 插入通讯记录                   *\n");
    printf("           *               3 查询通讯记录                   *\n");
    printf("           *               4 删除通讯记录                   *\n");
    printf("           *               5 显示通讯录信息                 *\n");
    printf("           *               6 将信息写入文件                 *\n");
    printf("           *               7 读取文件内容                   *\n");
    printf("           *               0 退出管理系统                   *\n");
    printf("           **************** ^@^欢迎使用通讯录系统************\n");
    int flag=0;
    int menu;
    printf("请选择0-5：");
    scanf("%d",&menu);
    while(menu!=0)
    {
        switch(menu)
        {
        case 1:
        {
            L=creatIncreLink();
            printf("建立通讯录：");
            printList(L);
            flag=1;
            break;
        }
        case 2:
        {
            if(flag==1)
            {
                int number,telenum;
                char name[20];
                char country[20];
                char city[20];
                char street[20];
                int eip;
                printf("请输入通讯者的学号和姓名：\n");
                printf("请输入学号: ");
                cin>>number;
                printf("请输入姓名: ");
                cin>>name;
                printf("请输入电话号码: ");
                cin>>telenum;
                printf("请输入国家：");
                cin>>country;
                printf("请输入城市：");
                cin>>city;
                printf("请输入街道：");
                cin>>street;
                printf("请输入邮编：");
                cin>>eip;

                LinkList p=(LinkList)malloc(LEN); //新结点
                p->number=number;
                strcpy(p->name,name);
                strcpy(p->country,country);
                strcpy(p->city,city);
                strcpy(p->street,street);
                p->eip = eip;
                p->telenum=telenum;
                insertYouXu(L,p);       //有序的插入新结点
                printf("插入后：");
                printList(L);
            }
            else printf("\nERROR: 通讯录还没有建立，请先建立通讯录\n");
            break;
        }
        case 3:
        {
            int way,n;
            char na[20];
            int s;
            if(L!=NULL)
            {
                if(flag)
                {
                    printf("选择查找方式：\n");
                    printf("               1.按学号   2.按姓名");
                    scanf("%d",&way);
                    if(way==1)
                    {
                        printf("\n请输入学号:");
                        scanf("%d",&n);
                        s=searchNum(L,n);
                        if(s==0) printf("无此通讯者，查找失败！\n");
                    }
                    else if(way==2)
                    {
                        printf("\n请输入姓名:");
                        cin>>na;
                        s=searchName(L,na);
                        if(s==0) printf("无此通讯者，查找失败！\n");
                    }
                    else printf("通讯录中无记录！\n");
                }
                break;
            }
            else printf("通讯录中无记录！\n");
            break;
        }
        case 4:
        {
            int way;
            printf("选择删除方式：1.按序号  2. 按学号  3.按姓名 \n");
            scanf("%d",&way);
            if(way==1)
            {
                int n;
                printf("请输入通讯录序号: ");
                cin>>n;
                printf("删除后：\n");
                deleteElem(L,n);
                printList(L);
            }
            else if(way==2)
            {
                int n,f;
                printf("请输入学号: ");
                cin>>n;
                f=delNum(L,n);
                if(f!=0)
                {
                    printf("删除后：\n");
                    printList(L);
                }
                else printf("无该学号，删除失败!\n");
            }
            else if(way==3)
            {
                char na[20];
                int f;
                printf("\n请输入姓名:");
                cin>>na;
                f=delName(L,na);
                if(f!=0)
                {
                    printf("删除后：\n");
                    printList(L);
                }
                else printf("无该学号，删除失败!\n");
            }
            else printf("ERROR!!\n");
            break;
        }
        case 5:
        {
            printf("当前通讯录内容如下：\n");
            printList(L);
            break;
        }
        case 0:
            exit(0);
        default:
            printf("\n没有此功能，重新输入\n");
        case 6:
        {
            LinkList p=L;
            write(L);
            printf("写入文件成功\n");
            break;
        }
        case 7:
        {
            printf("文件通讯录信息:\n");
            read("test.txt");
            break;
        }
        }
        printf("选择功能：");
        scanf("%d",&menu);
    }
}
