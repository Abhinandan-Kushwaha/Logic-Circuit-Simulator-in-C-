#include<graphics.h>
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<iostream.h>
#include<dos.h>
int szz=0,set=0,t=0,music=1,mx,my,midx,midy,cur=0,lx,ly,lin,nog=0,select_mode=0;
char exp[50];
void pointer(int);
void proximity();
void redraw();
void act();
void border();
void toolbar();
char va[90][15];
int bva[90];

typedef struct stack{
int x,y,dir,col;
struct stack*link;
}stack;

stack*strt,*tp;

void push(int x,int y,int dir,int col)
{
 stack* n=(stack*)malloc(sizeof(stack));
 n->x=x;
 n->y=y;
 n->dir=dir;
 n->col=col;
 if(szz==0)
 {
  strt=n;
  tp=n;
 }
 else
 {
   tp->link=n;
   tp=tp->link;
  }
szz=1;
}

typedef struct mylist{
int gate;
int sno;
int x;
int y;
char in1[15];
char in2[15];
char o[15];
char vin1[15];
char vin2[15];
char vo[15];
int cin1;
int cin2;
int co;
struct mylist *inl1;
struct mylist *inl2;
struct mylist *ol;
struct mylist *goinl1;
struct mylist *goinl2;
struct mylist *gool;

struct mylist *link;
struct mylist *prev_link;
}node;

node *start;
node *current;
node*last;
void disp();
void calco(node*n);
char pop();
int precedence(char c);
int evaluate3(int ,int,int);
int evaluate4(int ,int,int,int);
int var1,var2,var3,var4;

int evaluate(int ,int);
char st[50];
int top=-1;
char P[50];
char PP[50];
int nv=2;
int isAlpha(char c)
{
int r=0;
if((c>='A'&&c<='Z')||(c>='a'&&c<='z'))
r=1;
return r;
}
int nov(char s[])
{
int anv=0,i;
char c;
for(i=0;i<strlen(s);i++)
{
c=s[i];
if((c>='a'&&c<='z')||(c>='A'&&c<='Z')||c==1||c==0)
anv++;
}
return anv;
}
int found(char s[],char v)
{
int f=0,i;
char c;
for(i=0;i<strlen(s);i++)
{
c=s[i];
if(c==v)
{
f=1;
break;
}
}
return f;
}

void boolean(int cmd)
{
start:
clrscr();
cleardevice();

int pr,l,i,j,k,m,fxn=0,anv=0,nfvar1=0,nfvar2=0,nfvar3=0,nfvar4=0;
char op,c;
char ss2[50];
char ss[50];
char sss[50];
char ssh[50];
char shh[50];
char s[50];
int p=0;

//			Initialising the arrays:
for(i=0;i<50;i++)
{
P[i]='\0';
PP[i]='\0';
st[i]='\0';
ss[i]='\0';
ss2[i]='\0';
sss[i]='\0';
ssh[i]='\0';
shh[i]='\0';
s[i]='\0';
}
top=-1;


if(cmd!=2)
{
setcolor(14);
rectangle(mx-160,10,mx,220);
gotoxy(63,2);
cout<<"General\tComputer";
gotoxy(63,3);
cout<<"Symbol\tSymbol";
gotoxy(63,5);
cout<<"=>\t>";
gotoxy(63,6);
cout<<"<=>\t=";
gotoxy(63,7);
cout<<"Complem\t~";
gotoxy(63,8);
cout<<"OR\t+";
gotoxy(63,9);
cout<<"AND\t.";
gotoxy(62,11);
cout<<"Complement symbol";
gotoxy(62,12);
cout<<"  allowed only";
gotoxy(63,13);
cout<<"BEFORE a variable";


setcolor(4);

line(mx-160,55,mx,55);
line(mx-80,10,mx-80,160);
}//end of if (cmd!=2)
gotoxy(1,1);
puts("Enter number of variables in the table");
scanf("%d",&nv);
if(cmd==0)
{
puts("Enter the expression");
scanf("%s",&ss);
anv=nov(ss);
}
else if(cmd==2)
{
strcpy(ss,exp);
}
else
{
 cout<<"1. Check Validity of an Implication\n2. Compare 2 boolean Expressions\n";
 cout<<"\n\tPress 1 or 2\n";
 op=getch();
 if(op==1)
 {
 puts("Enter the expression");
gets(ss);
 }
 else
 {
 puts("Enter 1st expression");
gets(ss);
 puts("Enter 2nd expression");
gets(ss2);
  }
}
if(cmd!=2)
{
puts("Do you want to Set the ORDER of variables?   Y / N");
c=getch();
fflush(stdin);
}
else
c='y';
if(c=='y'||c=='Y'||c=='1')
{
puts("Enter the variable names in order");
if(nv>=1)
var1=getche();
if(nv>=2)
var2=getche();
if(nv>=3)
var3=getche();
if(nv>=4)
var4=getche();
set=1;
}
else
{
if(anv<nv)
{
puts("\n\nIf no of variables in Expression is less than that in Truth Table\nThen You must enter the order of variables!!");
getch();
goto start;
}
}
if(anv<nv)
{
if(!found(ss,var1))
nfvar1=1;
if(nv>=2&&!found(ss,var2))
nfvar2=1;
if(nv>=3&&!found(ss,var3))
nfvar3=1;
if(nv>=4&&!found(ss,var4))
nfvar4=1;
}

sss[0]=ss[0];
int co=1,cou=1,coun=1;
for(i=1;i<strlen(ss);i++)
{
if(ss[i-1]=='~')
{
sss[co++]=ss[i];
continue;
}
if(isAlpha(ss[i-1])&&isAlpha(ss[i]))
sss[co++]='.';
sss[co++]=ss[i];
}
ssh[0]=sss[0];
for(i=1;i<co;i++)
{
if(sss[i]=='('&&isAlpha(sss[i-1]))
ssh[cou++]='.';
ssh[cou++]=sss[i];
}
shh[0]=ssh[0];
for(i=1;i<cou-1;i++)
{
if(ssh[i]==')'&&isAlpha(ssh[i-1])&&isAlpha(ssh[i+1]))
{
shh[coun++]=ssh[i];
shh[coun++]='.';
continue;
}
shh[coun++]=ssh[i];
}
shh[coun++]=ssh[cou-1];
shh[coun++]='\0';
l=strlen(shh);
s[0]='(';
for(i=1;i<=l;i++)
s[i]=shh[i-1];
s[l+1]=')';
s[l+2]='\0';
printf("Rectified Expression : %s\n",s);
char x;

for(i=0;i<=l+1;i++)
{
c=s[i];

if(c=='(')
st[++top]=c;

else if((c>='A'&&c<='Z')||(c>='a'&&c<='z'))
P[p++]=c;

else if(c==')')
{
x=pop();
while(x!='(')
{
P[p++]=x;
x=pop();
}
}

else
{
pr=precedence(c);

if(pr>precedence(st[top]))
st[++top]=c;

else
{
while(pr<=precedence(st[top]))
{
x=pop();
P[p++]=x;
}
st[++top]=c;
}

}//end of else
}//end of for

printf("Postfix form : %s\n",P);
for(i=0;i<l;i++)
PP[i]=P[i];
printf("\n");

if(nv==2)
{
for(i=0;i<2;i++)
for(j=0;j<2;j++)
{
fxn=evaluate(i,j);
if(fxn==-1)
goto start;
else
printf("\t%d %d\t%d\n",i,j,fxn);
}
printf("\t______________\n");
printf("\t%c %c\t%s",var1,var2,ss);
}

else if(nv==3)
{
for(i=0;i<2;i++)
for(j=0;j<2;j++)
for(k=0;k<2;k++)
{
if(nfvar1==1)
fxn=evaluate3(2,j,k);
else if(nfvar2==1)
fxn=evaluate3(i,2,k);
else if(nfvar3==1)
fxn=evaluate3(i,j,2);
else
fxn=evaluate3(i,j,k);

if(fxn==-1)
goto start;
else
printf("\t%d %d %d\t%d\n",i,j,k,fxn);
}
printf("\t________________\n");
printf("\t%c %c %c\t%s",var1,var2,var3,ss);

}

else if(nv==4)
{
for(i=0;i<2;i++)
for(j=0;j<2;j++)
for(k=0;k<2;k++)
for(m=0;m<2;m++)
{
if(nfvar1==1&&nfvar2==1)
fxn=evaluate4(2,2,k,m);
else if(nfvar1==1&&nfvar3==1)
fxn=evaluate4(2,j,2,m);
else if(nfvar1==1&&nfvar4==1)
fxn=evaluate4(2,j,k,2);
if(nfvar2==1&&nfvar3==1)
fxn=evaluate4(i,2,2,m);
else if(nfvar2==1&&nfvar4==1)
fxn=evaluate4(i,2,k,2);
else if(nfvar3==1&&nfvar4==1)
fxn=evaluate4(i,j,2,2);
else if(nfvar1==1)
fxn=evaluate4(2,j,k,m);
else if(nfvar2==1)
fxn=evaluate4(i,2,k,m);
else if(nfvar3==1)
fxn=evaluate4(i,j,2,m);
else if(nfvar4==1)
fxn=evaluate4(i,j,k,2);
else
fxn=evaluate4(i,j,k,m);
if(fxn==-1)
goto start;
else
printf("\t%d %d %d %d\t\t%d\n",i,j,k,m,fxn);
}
printf("\t________________________\n");
printf("\t%c %c %c %c\t\t%s",var1,var2,var3,var4,ss);
}

printf("\n\t\tHit  Esc  to Exit");
for(i=0;;)
{
i++;
c=getch();
if(c==27||i==3)
break;
}
clrscr();
cleardevice();
redraw();
}

char pop()
{
return st[top--];
}

int precedence(char c)
{
int pr=0;
switch(c)
{
case '(':
pr=0;
break;
case '>':
case '=':
pr=1;
break;
case '+':
pr=2;
break;
case '.':
pr=3;
break;
case '~':
pr=4;
break;
}
return pr;
}

int value(int a,int b,char c)
{
int v=0;
switch(c)
{
case '.':
if(a!=0&&b!=0)
v=1;
break;
case '+':
if(a==1||b==1)
v=1;
break;
case '>':
if(a==2)
v=b;
else if(b==2)
v=a;
else if(a==0||b==1)
v=1;
break;
case '=':
if(a==2)
v=b;
else if(b==2)
v=a;
else if(a==b)
v=1;
break;

}
return v;
}

int evaluate(int a,int b)
{
int v=0;
int t=-1,tp=-1,i,j;
int l=strlen(P);
char c;

for(i=0;i<l;i++)
{
c=P[i];
if((c>='A'&&c<='Z')||(c>='a'&&c<='z')||c==1||c==0)
{
if(set==0)
{
if(tp>=0)
{
if(c==var1)
PP[i]=a;
else
{
PP[i]=b;
var2=c;
}
}

else
{
var1=c;
PP[i]=a;
++tp;
}
}
else
{
if(c==var1)
PP[i]=a;
else if(c==var2)
PP[i]=b;
else
{
puts("Variables unmatched!! Retry!!");
getch();
return-1;
}
}
}

else
{
PP[i]=c;
}
}
for(i=0;i<l;i++)
{
c=P[i];
if((c>='A'&&c<='Z')||(c>='a'&&c<='z')||c==1||c==0)
st[++t]=PP[i];
else if(c=='~')
{
if(st[t]==1)
st[t]=0;
else
st[t]=1;
}
else
{
v=value(st[t-1],st[t],c);
t=t-2;
st[++t]=v;
}
}
return st[t];
}


int evaluate3(int a,int b,int k)
{
int v=0;
int t=-1,tp=-1,i,j;
int l=strlen(P);
char c;

for(i=0;i<l;i++)
{
c=P[i];
if((c>='A'&&c<='Z')||(c>='a'&&c<='z')||c==1||c==0)
{
if(set==0)
{
if(tp==-1)
{
var1=c;
PP[i]=a;
tp=0;
}

else if(tp==0)
{
if(c==var1)
PP[i]=a;
else
{
var2=c;
PP[i]=b;
tp=1;
}
}

else
{
if(c==var1)
PP[i]=a;
else if(c==var2)
PP[i]=b;
else
{
PP[i]=k;
var3=c;
}
}
}

else
{
if(c==var1)
PP[i]=a;
else if(c==var2)
PP[i]=b;
else if(c==var3)
PP[i]=k;
else
{
puts("Variables unmatched!! Retry!!");
return-1;
}
}
}
else
{
PP[i]=c;
}
}
for(i=0;i<l;i++)
{
c=P[i];
if((c>='A'&&c<='Z')||(c>='a'&&c<='z')||c==1||c==0)
st[++t]=PP[i];
else if(c=='~')
{
if(st[t]==1)
st[t]=0;
else
st[t]=1;
}
else
{
v=value(st[t-1],st[t],c);
t=t-2;
st[++t]=v;
}
}
return st[t];
}

int evaluate4(int a,int b,int k,int m)
{
int v=0;
int t=-1,tp=-1,i,j;
int l=strlen(P);
char c;

for(i=0;i<l;i++)
{
c=P[i];
if((c>='A'&&c<='Z')||(c>='a'&&c<='z'))
{
if(set==0)
{
if(tp==-1)
{
var1=c;
PP[i]=a;
tp=0;
}

else if(tp==0)
{
if(c==var1)
PP[i]=a;
else
{
var2=c;
PP[i]=b;
tp=1;
}
}

else if(tp==1)
{
if(c==var1)
PP[i]=a;
else if(c==var2)
PP[i]=b;
else
{
PP[i]=k;
var3=c;
tp=2;
}
}
else
{
if(c==var1)
PP[i]=a;
else if(c==var2)
PP[i]=b;
else if(c==var3)
PP[i]=k;
else
{
PP[i]=m;
var4=c;
}
}
}
else
{
if(c==var1)
PP[i]=a;
else if(c==var2)
PP[i]=b;
else if(c==var3)
PP[i]=k;
else if(c==var4)
PP[i]=m;
else
{
puts("Variables unmatched!! Retry!!");
return-1;
}
}
}

else
{
PP[i]=c;
}
}
for(i=0;i<l;i++)
{
c=P[i];
if((c>='A'&&c<='Z')||(c>='a'&&c<='z'))
st[++t]=PP[i];
else if(c=='~')
{
if(st[t]==1)
st[t]=0;
else
st[t]=1;
}
else
{
v=value(st[t-1],st[t],c);
t=t-2;
st[++t]=v;
}
}
return st[t];
}

node* getn()
{
node*n=(node*)malloc(sizeof(node));
n->inl1=NULL;
n->inl2=NULL;
n->ol=NULL;
n->goinl1=NULL;
n->goinl2=NULL;
n->gool=NULL;
n->cin1=0;
n->cin2=0;
n->co=0;
strcpy(n->in1,"?");
strcpy(n->in2,"?");
strcpy(n->o,"?");
return n;
}

void keysound()
{
if(music==0)
return;
int i;
for(i=0;i<10;i++)
{
sound(800+20*i);
delay(5);
nosound();
}
}
void msgsound()
{
if(music==0)
return;
sound(500);
delay(100);
nosound();
sound(500);
delay(100);
nosound();
}

void exitmsg()
{
msgsound();
setcolor(1);
rectangle(midx-140,midy-60,midx+140,midy+60);
rectangle(midx-145,midy-65,midx+145,midy+65);
setfillstyle(1,6);
floodfill(midx-142,midy-62,1);


setfillstyle(1,7);
floodfill(midx,midy,1);
settextstyle(1,0,1);
setcolor(1);
outtextxy(midx-130,midy-50,"Do you Really want to EXIT");
while(!kbhit())
{
setcolor(4);
outtextxy(midx-40,midy,"Y  /  N");
delay(500);
setcolor(7);
outtextxy(midx-40,midy,"Y  /  N");
delay(400);
}
char c=getch();
if(c=='y'||c=='Y')
exit(0);
if(c=='n'||c=='N')
{
clrscr();
cleardevice();
border();
toolbar();
redraw();
}
else
exitmsg();
}

/***************************	AND	********************************/
void draw_and(int x,int y)
{
line(x-10,y-8,x+10,y-8);
line(x-10,y+8,x+10,y+8);
line(x+10,y-15,x+10,y+15);
line(x+10,y-15,x+20,y-15);
line(x+10,y+15,x+20,y+15);
arc(x+20,y,270,90,15);
}


/***************************   OR	********************************/
void draw_or(int x,int y)
{
line(x-10,y-8,x+10,y-8);
line(x-10,y+8,x+10,y+8);
arc(x,y,290,70,15);
line(x+4,y-15,x+35,y);
line(x+4,y+15,x+35,y);
}

/***************************   XOR	********************************/
void draw_xor(int x,int y)
{
line(x-15,y-8,x+5,y-8);
line(x-15,y+8,x+5,y+8);
arc(x-5,y,290,70,15);
arc(x,y,290,70,15);
line(x+4,y-15,x+35,y);
line(x+4,y+15,x+35,y);
}


/***************************	NOT	********************************/
void draw_not(int x,int y)
{
line(x-10,y-5,x+10,y-5);
line(x+10,y-15,x+10,y+15);
line(x+10,y-15,x+35,y);
line(x+10,y+15,x+35,y);
circle(x+38,y,3);
}



/***************************	NAND	********************************/
void draw_nand(int x,int y)
{
line(x-10,y-8,x+10,y-8);
line(x-10,y+8,x+10,y+8);
line(x+10,y-15,x+10,y+15);
line(x+10,y-15,x+20,y-15);
line(x+10,y+15,x+20,y+15);
arc(x+20,y,270,90,15);
circle(x+38,y,3);
}



/***************************    NOR	********************************/
void draw_nor(int x,int y)
{
line(x-10,y-8,x+10,y-8);
line(x-10,y+8,x+10,y+8);
arc(x,y,290,70,15);
line(x+4,y-15,x+35,y);
line(x+4,y+15,x+35,y);
circle(x+38,y,3);
}

/***************************    XNOR	********************************/
void draw_xnor(int x,int y)
{
line(x-15,y-8,x+5,y-8);
line(x-15,y+8,x+5,y+8);
arc(x-5,y,290,70,15);
arc(x,y,290,70,15);
line(x+4,y-15,x+35,y);
line(x+4,y+15,x+35,y);
circle(x+38,y,3);
}


/***************************	BORDER ********************************/
void border()
{
setcolor(3);
rectangle(0,0,mx,my);
rectangle(5,30,mx-10,my-5);
setfillstyle(1,3);
floodfill(5,20,getcolor());
setcolor(14);
settextstyle(1,0,4);
outtextxy(midx-180,-8,"Logic Circuit Simulator");
settextstyle(11,0,4);

setcolor(4);
outtextxy(mx-125,2,"K Creative Labs");
settextstyle(11,1,4);
outtextxy(mx,midy-195,"By - Abhinandan Kushwaha");

}


void draw_gate(node* n,int cursor,int del)
{
int x=n->x;
int y=n->y;

if(del==0)
setcolor(15);
else
{
setcolor(getbkcolor());
}
switch(cursor)
{
case 0:
draw_and(x,y);
break;
case 1:
draw_or(x,y);
break;
case 2:
draw_not(x,y);
break;
case 3:
draw_nand(x,y);
break;
case 4:
draw_nor(x,y);
break;
case 5:
draw_xor(x,y);
break;
case 6:
draw_xnor(x,y);
break;
}
}

void tooltext()
{
int i;
char gates[7][5]={"AND","OR","NOT","NAND","NOR","XOR","XNOR"};

for(i=0;i<420;i+=60)
{
gotoxy(i/10+6,25);
cout<<gates[i/60];
}
gotoxy(49,25);
cout<<"Connect";
gotoxy(60,25);
cout<<"Select";
gotoxy(72,25);
cout<<"Move";

}

/***************************	TOOL BAR	********************/

void toolbar()
{
int i;
settextstyle(11,0,4);
if(music==0)
setcolor(getbkcolor());
else
setcolor(4);
outtextxy(10,my-72,"Hit 'n' to deactivate sound");

setcolor(4);
rectangle(10,my-60,mx-10,my-10);
rectangle(15,my-55,mx-15,my-15);
setfillstyle(1,4);
floodfill(12,my-58,getcolor());
if(t==0)
{
/****************	deleting the box	*****************/
setcolor(getbkcolor());
rectangle(10,30,mx-10,70);
setfillstyle(1,getbkcolor());
floodfill(midx,32,getbkcolor());
/****************				*****************/

setcolor(15);
rectangle(15,32,40,52);
setcolor(12);
rectangle(20,37,35,47);
rectangle(19,36,36,48);
setfillstyle(1,14);
floodfill(21,45,getcolor());
setcolor(15);
settextstyle(11,0,4);
outtextxy(45,35,"Hit T to get extra tools");
setcolor(0);
outtextxy(25,39,"T");
}
else
{
/****************	deleting the text	*****************/
setcolor(getbkcolor());
settextstyle(11,0,4);
outtextxy(45,35,"Hit T to get extra tools");
/****************				*****************/

setcolor(15);
settextstyle(11,0,4);
outtextxy(mx-110,35," Hit T to");
outtextxy(mx-110,45,"minimise the");
outtextxy(mx-110,55," tool box");

rectangle(10,30,mx-10,70);
rectangle(15,32,mx-15,68);
setfillstyle(1,15);
floodfill(12,31,getcolor());
setfillstyle(1,8);
floodfill(155,50,getcolor());
setfillstyle(1,7);
ellipse(120,50,0,360,55,15);
floodfill(120,49,getcolor());
ellipse(120,50,0,360,40,13);
setcolor(BLUE);
settextstyle(11,0,4);
outtextxy(100,42,"TRUTH");
outtextxy(100,51,"TABLE");

setcolor(15);
setfillstyle(1,7);
ellipse(240,50,0,360,55,15);
floodfill(240,49,getcolor());
ellipse(240,50,0,360,40,13);
setcolor(BLUE);
settextstyle(11,0,4);
outtextxy(210,46,"SIMULATE");

setcolor(15);
setfillstyle(1,7);
ellipse(360,50,0,360,55,15);
floodfill(360,49,getcolor());
ellipse(360,50,0,360,40,13);
floodfill(410,49,getcolor());

setcolor(BLUE);
settextstyle(11,0,4);
outtextxy(335,42,"BOOLEAN");
outtextxy(340,51,"WORLD");

}
setcolor(4);

for(i=0;i<7;i++)
{
rectangle(20+i*50,my-50,70+i*50,my-20);
setfillstyle(1,6);
if(i!=cur);
floodfill(25+i*50,my-30,getcolor());
}

if(select_mode==1)
{
setfillstyle(7,2);
floodfill(68+(cur+1)*50,my-35,getcolor());
}

setfillstyle(1,1);
if(cur<9)
floodfill(68+cur*50,my-35,getcolor());
else
floodfill(120+cur*50,my-35,getcolor());

for(i=0;i<420;i+=60)
gotoxy(i/10+6,25);

ellipse(415,my-34,0,360,40,16);
setfillstyle(1,6);
if(cur!=7)
floodfill(415,my-32,getcolor());
ellipse(495,my-35,0,360,35,16);
setfillstyle(1,6);
if(cur!=8&&select_mode==0)
floodfill(495,my-35,getcolor());

ellipse(580,my-35,0,360,33,16);
setfillstyle(1,6);
if(cur!=9)
floodfill(580,my-35,getcolor());


setfillstyle(1,14);
floodfill(480,my-18,4);

setfillstyle(1,1);
if(cur==10)
floodfill(170,50,15);
else if(cur==11)
floodfill(290,50,15);
else if(cur==12)
floodfill(410,50,15);

tooltext();
}

/***********************************************************************/

void move()
{
char c;
c=getch();

if(c=='\r')
{
pointer(1);
return;
}

draw_gate(current,current->gate,1);  //deleting the gate

switch(c)
{
case 27:
exitmsg();
break;

case 115:
if(current->x>45)
{
pointer(1);
(current->x)-=15;
pointer(0);
}
break;


case 75:
if(current->x>45)
{
pointer(1);
(current->x)--;
pointer(0);
}
break;

case 116:
if(current->x<mx-80)
{
pointer(1);
(current->x)+=15;
pointer(0);
}
break;


case 77:
if(current->x<mx-80)
{
pointer(1);
(current->x)++;
pointer(0);
}
break;

case -115:
if(current->y>60)
{
pointer(1);
(current->y)-=10;
pointer(0);
}
break;

case 72:
if(current->y>60)
{
pointer(1);
(current->y)--;
pointer(0);
}
break;

case -111:
if(current->y<my-100)
{
pointer(1);
(current->y)+=10;
pointer(0);
}
break;


case 80:
if(current->y<my-100)
{
pointer(1);
(current->y)++;
pointer(0);
}
break;

}

draw_gate(current,current->gate,0);  //redrawing the gate
move();
}

void pointer(int del)
{
int x=current->x+20;
int y=current->y;
int col;

if(del==1)//deleting the pointer
col=getbkcolor();
else
col=5;

setcolor(col);

circle(x,y,3);
setfillstyle(1,col);
floodfill(x,y,getcolor());
}

void draw()
{
int clr=15;
for(;;)
{
setcolor(clr);

char c=getch();
if(c=='\r')
{
proximity();
redraw();
break;
}
switch(c)
{

case 'x':
clr=getbkcolor();
break;

case 'c':
clr=15;
break;

case 27:
return;

case 75:
push(lx,ly,75,getcolor());
line(lx,ly,lx-2,ly);
lx-=2;
break;
case 115:
push(lx,ly,75,getcolor());
line(lx,ly,lx-6,ly);
lx-=6;
break;

case 77:
push(lx,ly,77,getcolor());
line(lx,ly,lx+2,ly);
lx+=2;
break;
case 116:
push(lx,ly,77,getcolor());
line(lx,ly,lx+6,ly);
lx+=6;
break;

case 72:
push(lx,ly,72,getcolor());
line(lx,ly,lx,ly-2);
ly-=2;
break;
case -115:
push(lx,ly,72,getcolor());
line(lx,ly,lx,ly-6);
ly-=6;
break;

case 80:
push(lx,ly,80,getcolor());
line(lx,ly,lx,ly+2);
ly+=2;
break;
case -111:
push(lx,ly,80,getcolor());
line(lx,ly,lx,ly+6);
ly+=6;
break;

}
}
}

void update(node*n)
{
node*tmp;
 calco(n);
 if(n->goinl1!=NULL)
 {
  tmp=n->goinl1;
  if(tmp->cin1==1&&tmp->inl1==current)
  {
   strcpy(tmp->in1,n->in1);
   strcpy(va[3*tmp->sno],n->in1);
   }
  if(tmp->cin2==1&&tmp->inl2==current)
  {
   strcpy(tmp->in2,n->in1);
   strcpy(va[3*tmp->sno+1],n->in1);
  }
  if(tmp->co==1&&tmp->ol==current)
  {
   strcpy(tmp->o,n->in1);
   strcpy(va[3*tmp->sno+2],n->in1);
  }
  if(tmp==n)
  calco(n);
  else
   update(tmp);
  }
  if(n->goinl2!=NULL)
 {
  tmp=n->goinl2;

  if(tmp->cin1==2&&tmp->inl1==current)
  {
   strcpy(tmp->in1,n->in2);
   strcpy(va[3*tmp->sno],n->in2);
  }
  if(tmp->cin2==2&&tmp->inl2==current)
  {
   strcpy(tmp->in2,n->in2);
   strcpy(va[3*tmp->sno+1],n->in2);
  }
  if(tmp->co==2&&tmp->ol==current)
  {
   strcpy(tmp->o,n->in2);
   strcpy(va[3*tmp->sno+2],n->in2);
  }
  if(tmp==n)
  calco(n);
  else
   update(tmp);
  }
  if(n->gool!=NULL)
 {
  tmp=n->gool;

  if(tmp->cin1==3&&tmp->inl1==current)
  {
   strcpy(tmp->in1,n->o);
   strcpy(va[3*tmp->sno],n->o);
  }
  if(tmp->cin2==3&&tmp->inl2==current)
  {
   strcpy(tmp->in2,n->o);
   strcpy(va[3*tmp->sno+1],n->o);
  }
  if(tmp->co==3&&tmp->ol==current)
  {
   strcpy(tmp->o,n->o);
   strcpy(va[3*tmp->sno+2],n->o);
  }
   if(tmp==n)
   calco(n);
  else
  update(tmp);
  }

disp();
}
void dec_sno(node*n)
{
while(n!=NULL)
{
n->sno=n->sno-1;
n=n->link;
}
}
void select(int op)
{
node* n=getn();
n=current;

pointer(0);

char c,cc,ccc;

if(op==1)
{
select_mode=1;
toolbar();
}

cc=getch();

if(cc=='\r')
{

 if(op==1)//op=1 indicates connection mode
 {
 select_mode=0;
 toolbar();
  settextstyle(11,0,4);
  get:
  setcolor(12);
  if(current->gate==2)
  outtextxy(midx-25,my-70,"1. 1st Input                3. Output line");
  else
  outtextxy(midx-25,my-70,"1. 1st Input  2. 2nd Input  3. Output line");

  c=getch();

  //Deleting the message
  setcolor(getbkcolor());
  outtextxy(midx-25,my-70,"1. 1st Input  2. 2nd Input  3. Output line");

  switch(c)
  {

   case '1':
   lin=1;
   lx=current->x-10;
   if(current->gate==2)
   ly=current->y;
   else
   ly=current->y-8;
   break;
   case '2':
   if(current->gate!=2)
   {
   lin=2;
   lx=current->x-10;
   ly=current->y+8;
   }
   break;
   case '3':
   lin=3;
   lx=current->x+35;
   ly=current->y;
   break;
   case 27:
   return;
   default:
   goto  get;
  }//end of switch block

  setcolor(12);
  outtextxy(midx-25,my-70,"Hit S to set value at selected line");
  ccc=getch();

  //Deleting the message:
  setcolor(getbkcolor());
  outtextxy(midx-25,my-70,"Hit S to set value at selected line");
  setcolor(12);

  if(ccc=='s'||ccc=='S')
  {
   char ss[1];
   gotoxy(2,22);
   gets(ss);
   //c=ss[0];

   if(lin==1)
   {
    strcpy(current->in1,ss);
    outtextxy(current->x-18,current->y-10,ss);
    strcpy(va[current->sno*3],ss);

     }
   else if(lin==2)
   {
    strcpy(current->in2,ss);
    outtextxy(current->x-18,current->y+6,ss);
    strcpy(va[current->sno*3+1],ss);
}
   else if(lin==3)
   {
    strcpy(current->o,ss);
    outtextxy(current->x+37,current->y-2,ss);
   strcpy(va[current->sno*3+2],ss);
}
   //calco(current);
   update(current);
   redraw();
  }//end of if ccc=='s'

  else
  draw();

 }//end of op=1 (connection mode)

 if(op==2)
 {
  strcpy(exp,current->o);
  boolean(2);
  return;
 }
 if(op==0)
  {
   outtextxy(midx-25,my-70,"Hit D to destroy this gate");
   char cd=getch();
   if(cd=='d'||cd=='D')
   {
   setcolor(getbkcolor());
   outtextxy(midx-25,my-70,"Hit D to destroy this gate");
   setcolor(15);
   pointer(1);
   draw_gate(current,current->gate,1);
   node*tpr=current->link;
   dec_sno(tpr);
   tpr->prev_link=current->prev_link;
   current=current->prev_link;
   current->link=tpr;
   last=current;
   nog--;
   pointer(0);
   }

 return;
 }
}//end of cc='\r'

switch(cc)
{
case 27:
if(op==1)
{
pointer(1);
cur--;
select_mode=0;
return;
}
else
exitmsg();

case 75:
if(n->prev_link!=NULL)
{
pointer(1);
n=n->prev_link;
}
break;

case 77:
if(n->link!=NULL)
{
pointer(1);
n=n->link;
}
break;
}
current=n;
pointer(0);
select(op);
select_mode=0;
toolbar();
}

void proximity()
{
setcolor(getbkcolor());
outtextxy(midx+60,my-80,"proxy o");
outtextxy(midx-70,my-80,"proxy in1");
outtextxy(midx,my-80,"proxy in2");
setcolor(15);
int i;
//char op[7][2]={".","+","~","/\\","\\/","@","$"};
node *n=getn();
n=start;
for(i=0;i<nog;i++)
{
//checking proximity with 1st input line
if(lx<(n->x)&&lx>(n->x)-15&&ly<(n->y)&&ly>(n->y)-13)
{
outtextxy(midx-70,my-80,"proxy in1");

if(lin==1)
{
n->inl1=current;
current->goinl1=n;
n->cin1=1;

//strcpy(n->in1,current->in1);
}
else if(lin==2)
{
n->inl1=current;
current->goinl2=n;
n->cin1=2;
//strcpy(n->in1,current->in2);
}
else if(lin==3)
{
n->inl1=current;
current->gool=n;
n->cin1=3;
}
update(current);
break;
}
//checking proximity with 2nd input line
else if(lx<(n->x)&&lx>(n->x)-15&&ly>(n->y)&&ly<(n->y)+13)
{
outtextxy(midx,my-80,"proxy in2");
if(lin==1)
{
n->inl2=current;
current->goinl1=n;
n->cin2=1;
//strcpy(n->in2,current->in1);
}
else if(lin==2)
{
n->inl2=current;
current->goinl2=n;
n->cin2=2;
//strcpy(n->in2,current->in2);
}
else if(lin==3)
{
n->inl2=current;
current->gool=n;
n->cin2=3;
}
update(current);
break;
}
//checking proximity with output line
else if(lx<(n->x)&&lx>(n->x)-15&&ly>(n->y)&&ly<(n->y)+10)
{
outtextxy(midx+60,my-80,"proxy o");
if(lin==1)
{
n->ol=current;
current->goinl1=n;
n->co=1;
//strcpy(n->o,current->in1);
}
else if(lin==2)
{
n->ol=current;
current->goinl2=n;
n->co=2;
//strcpy(n->o,current->in2);
}
else if(lin==3)
{
n->ol=current;
current->gool=n;
n->co=3;
//strcpy(n->o,current->o);
}
update(current);
break;
}
n=n->link;
}
}

void connect()
{
pointer(0);
select(1);
}
void calco(node*n)
{
   char op[7][7]={".","+","~",".","+"," xor "," xnor "};
   char s[15];
   strcpy(s,"");
   strcat(s,"(");

   if(n->gate==5)
   {
   strcat(s,"(");
   strcat(s,"~");
   strcat(s,n->in1);
   strcat(s,".");
   strcat(s,n->in2);
   strcat(s,")");

   strcat(s,"+");
   strcat(s,"(");
   strcat(s,n->in1);
   strcat(s,".");
   strcat(s,"~");
   strcat(s,n->in2);
   strcat(s,")");

   }
   else if(n->gate==6)
   {
   strcat(s,"(");
   strcat(s,"~");
   strcat(s,n->in1);
   strcat(s,"+");
   strcat(s,n->in2);
   strcat(s,")");

   strcat(s,".");
   strcat(s,"(");
   strcat(s,n->in1);
   strcat(s,"+");
   strcat(s,"~");
   strcat(s,n->in2);
   strcat(s,")");
   }
   else
   {
   if(!strcmp(n->in1,n->in2))
   {
    if(n->gate==0||n->gate==1)
    strcat(s,n->in1);
    else if(n->gate==3||n->gate==4)
    {
    strcat(s,"~(");
    strcat(s,n->in1);
    }
   }
  else
  {
  if(n->gate>1&&n->gate<5)
  strcat(s,"~");
  if(n->gate>2&&n->gate<5)
  strcat(s,"(");

  strcat(s,n->in1);
  if(n->gate!=2)
  {
  strcat(s,op[n->gate]);
  strcat(s,n->in2);
  }
  if(n->gate>2&&n->gate<5)
  strcat(s,")");
  }
  }
  strcat(s,")");

  strcpy(n->o,s);
  strcpy(va[3*n->sno+2],s);
  //update(n,n->gool);

}

void calculate()
{
int i,j;
char s[15];
node*n=getn();
//node*min=getn();
node*tmp=getn();
n=start;
char op[7][2]={".","+","~","/\\","\\/","@","$"};
for(i=0;i<nog;i++)
{
//n->traversed=0;
   char s[15];
  strcpy(s,n->in1);
  strcat(s,op[n->gate]);
  strcat(s,n->in2);
  strcpy(n->o,s);


 if(n->inl1!=NULL)
 {
 gotoxy(10,10);
 cout<<"1 not null";
  tmp=n->inl1;

  if(tmp->goinl1==n)
  strcpy(n->in1,tmp->in1);
  else if(tmp->goinl2==n)
  strcpy(n->in1,tmp->in2);
  else if(tmp->gool==n)
  strcpy(n->in1,tmp->o);
 }
 if(n->inl2!=NULL)
 {
 gotoxy(10,11);
 cout<<"2 not null";
  tmp=n->inl2;

  if(tmp->goinl1==n)
  strcpy(n->in2,tmp->in1);
  else if(tmp->goinl2==n)
  strcpy(n->in2,tmp->in2);
  else if(tmp->gool==n)
  strcpy(n->in2,tmp->o);
 }
 if(n->ol==NULL)
 {gotoxy(10,12);
 cout<<"3 null";
 }
 if(n->ol!=NULL)
 {
 gotoxy(10,12);
 cout<<"3 not null";
  tmp=n->ol;

  if(tmp->goinl1==n)
  strcpy(n->o,tmp->in1);
  else if(tmp->goinl2==n)
  strcpy(n->o,tmp->in2);
  else if(tmp->gool==n)
  strcpy(n->o,tmp->o);
 }

n=n->link;
}
}

void disp()
{
gotoxy(2,22);
int i,col;
node*n=getn();
n=start;
col=getbkcolor();
setcolor(col);
setfillstyle(1,col);
for(i=0;i<nog;i++)
{
 rectangle(n->x-18,n->y-10,n->x-18+10,n->y-10+10);
 rectangle(n->x-18,n->y+6,n->x-18+10,n->y+6+10);
 rectangle(n->x+37,n->y-2,n->x+37+30,n->y-2+10);
 floodfill(n->x-15,n->y-5,col);
 floodfill(n->x-15,n->y+10,col);
 floodfill(n->x+40,n->y,col);

 n=n->link;
}

setcolor(14);
n=start;
for(i=0;i<nog;i++)
{
 if(n->gate>1&&n->gate<5)
 {
 if(strlen(n->in1)==1)
 outtextxy(n->x-18,n->y-10,n->in1);
 else
 outtextxy(n->x-18,n->y-10,"*");

 outtextxy(n->x+44,n->y-2,n->o);
 if(n->gate!=2)
 {
  if(strlen(n->in2)==1)
   outtextxy(n->x-18,n->y+6,n->in2);
  else
   outtextxy(n->x-18,n->y-10,"*");
  }
 }
 else
 {
  if(strlen(n->in1)==1)
 outtextxy(n->x-18,n->y-10,n->in1);
 else
 outtextxy(n->x-18,n->y-10,"*");
 if(strlen(n->in2)==1)
 outtextxy(n->x-18,n->y+6,n->in2);
 else
 outtextxy(n->x-18,n->y+6,"*");

  if(n->gate==5)
  {
   outtextxy(n->x+40,n->y-2,n->in1);
   outtextxy(n->x+40+strlen(n->in1)*7,n->y-2," xor ");
   outtextxy(n->x+40+strlen(n->in1)*7+35,n->y-2,n->in2);
   }
  else if(n->gate==6)
  {
   outtextxy(n->x+40,n->y-2,n->in1);
   outtextxy(n->x+40+strlen(n->in1)*7,n->y-2," xnor ");
   outtextxy(n->x+40+strlen(n->in1)*7+42,n->y-2,n->in2);
   }
  else
  {
 outtextxy(n->x+37,n->y-2,n->o);
 }
}
 n=n->link;
}
}
void vdisp()
{
gotoxy(2,22);
int i;
node*n=getn();
n=start;
n=start;
setcolor(12);
for(i=0;i<nog;i++)
{
 if(strlen(n->in1)==1&&strcmp(n->in1,"?")!=0)
 {
  n->vin1[0]=n->vin1[0]+47;
  outtextxy(n->x-18-10,n->y-10,n->vin1);
 }
 if(strlen(n->in2)==1&&strcmp(n->in2,"?")!=0)
 {
  n->vin2[0]=n->vin2[0]+47;
  outtextxy(n->x-18-10,n->y+6,n->vin2);
 }
 n=n->link;
}
}
void blink(int x,int y,char s[])
{
int i,l=strlen(s);
 while(!kbhit())
 {
  gotoxy(x,y);
  cout<<s;
  delay(700);
  gotoxy(x,y);
  for(i=0;i<l;i++)
  cout<<" ";
  delay(500);
 }
}

void overflow()
{
clrscr();
cleardevice();
settextstyle(1,0,2);
outtextxy(midx-150,midy,"OVERFLOW !!!");
gotoxy(10,10);
cout<<"Press any key to Continue";
msgsound();
getch();
redraw();
act();
}

void rep(char ch,int v)
{
node*n=start;
int i,k;
for(k=0;k<nog;k++)
{
 for(i=0;i<strlen(n->in1);i++)
  if(n->in1[i]==ch)
   n->vin1[i]=v;
 for(i=0;i<strlen(n->in2);i++)
  if(n->in2[i]==ch)
   n->vin2[i]=v;
 for(i=0;i<strlen(n->o);i++)
  if(n->o[i]==ch)
   n->vo[i]=v;
  n=n->link;
 }
}
int tvalue(int a,int b,char c)
{
int vl=1;
switch(c)
{
case '.':
if(a==2&&b==2)
vl=2;
break;
case '+':
if(a==2||b==2)
vl=2;
break;
}
return vl;
}

int position(char collect[],char c,int clt)
{
 int i,psn=-1;
 for(i=0;i<clt;i++)
 {
  if(collect[i]==c)
  {
   psn=i;
   break;
  }
 }
 return psn;
}

void simulate()
{
node*n=start;
int j;
char c,num;

for(j=0;j<nog;j++)
{
 if(n->gate>4)
 {
  gotoxy(2,22);
  cout<<"Unable to simulate due to presence of XOR or XNOR gates in the circuit";
  return;
 }
 n=n->link;
}
clrscr();
cleardevice();
border();
toolbar();
redraw();
n=start;
for(j=0;j<nog;j++)
{
 strcpy(n->vin1,n->in1);
 strcpy(n->vin2,n->in2);
 strcpy(n->vo,n->o);
 n=n->link;
}
char collect[50];
int clt=0,psn;
for(j=0;j<90;j++)
{
 c=va[j][0];
 if(c!='?'&&strlen(va[j])==1)
 {
  her:
  psn=position(collect,va[j][0],clt);
  if(psn>=0)
   num=bva[psn];
  else if((va[j][0]>='A'&&va[j][0]<='Z')||(va[j][0]>='a'&&va[j][0]<='z'))
  {
   msgsound();
   gotoxy(2,22);
   cout<<"Enter value of"<<va[j];
   num=getche()-47;
   char nuum=num+47;
   cout<<nuum;
  }
  if(num==1||num==2)
  {
  collect[clt]=va[j][0];
  bva[clt++]=num;
  rep(va[j][0],num);
  }
  else if(num==-20)//If user hits Esc key(27-47=-20)
  exitmsg();
  else
  {
  gotoxy(15,22);
  cout<<"    ";
  simulate();
  }
 }
}

for(j=0;j<50;j++)
{
P[j]='\0';
PP[j]='\0';
st[j]='\0';
}
top=-1;

n=start;
top=-1;
for(j=0;j<nog;j++)
{
 char s[50],c,x;
 strcpy(s,n->vo);
 int pr,p=0,i,l=strlen(s);

 for(i=0;i<l;i++)
 {
  c=s[i];

  if(c=='(')
   st[++top]=c;

  else if(c==1||c==2)
   P[p++]=c;

  else if(c==')')
  {
   x=pop();
   while(x!='(')
   {
    P[p++]=x;
    x=pop();
   }
  }

  else
  {
   pr=precedence(c);

   if(pr>precedence(st[top]))
    st[++top]=c;

   else
   {
    while(pr<=precedence(st[top]))
    {
     x=pop();
     P[p++]=x;
    }
    st[++top]=c;
   }

  }//end of else
 }//end of for
//cout<<"Postfix"<<P;

int v,result,toop=-1;
for(i=0;i<50;i++)
st[i]='\0';

l=strlen(P);
for(i=0;i<l;i++)
{
 c=P[i];
 if(c==1||c==2)
  st[++toop]=c;
 else if(c=='~')
 {
  if(st[toop]==1)
   st[toop]=2;
  else
   st[toop]=1;
  }
 else
 {
  v=tvalue(st[toop-1],st[toop],c);
  //cout<<"Eval"<<st[toop-1]<<"&"<<st[toop]<<"got"<<v;
  toop-=2;
  st[++toop]=v;
 }
}
result= st[toop];
//cout<<"res"<<result;
if(result==2)
{
 //cout<<"coloured";
 setfillstyle(1,2);
 floodfill(n->x+20,n->y,15);
}
n=n->link;
}
vdisp();
}


void tt()
{
 msgsound();
 blink(5,6,"Select Gate whose output's Truth Table U want");
 select(2);
}

void act()
{
char c=getch();
switch(c)
{
case 27:
exitmsg();
break;

case 'd':
//calculate();
disp();
break;

case 'n':
case 'N':
if(music==1)
music=0;
else
music=1;
toolbar();
break;

case 't':
case 'T':
if(t==0)
{
t=1;
cur=10;
toolbar();
}
else
{
t=0;
cur=0;
toolbar();
}
break;

case 'm':
//case 'M':
keysound();
cur=9;
toolbar();
break;

case 's':
case 'S':
keysound();
cur=8;
toolbar();
break;

case 'c':
case 'C':
keysound();
cur=7;
toolbar();
break;

case 75:
keysound();
if(t==1&&cur>9)
{
 if(cur==10)
 {
 setfillstyle(1,7);
 floodfill(170,50,15);

  cur=12;
 setfillstyle(1,1);
 floodfill(410,50,15);
 }
 else
 {
 setfillstyle(1,7);
 if(cur==11)
 floodfill(290,50,15);
 else if(cur==12)
 floodfill(410,50,15);

  cur--;
  setfillstyle(1,1);
  if(cur==10)
  floodfill(170,50,15);
  else if(cur==11)
  floodfill(290,50,15);

 }
}
else
{
 if(cur!=0)
 {
  setfillstyle(1,6);
 if(cur==9)
 floodfill(580,my-35,4);
 else if(cur==8&&select_mode==0)
 floodfill(495,my-35,4);
 else if(cur==7)
 floodfill(415,my-32,4);
 else
 floodfill(25+cur*50,my-30,4);

 cur--;
 setfillstyle(1,1);
 if(cur==9)
 floodfill(580,my-35,4);
 else if(cur==8&&select_mode==0)
 floodfill(495,my-35,4);
 else if(cur==7)
 floodfill(415,my-32,4);
 else
 floodfill(25+cur*50,my-30,4);
 }
 else
 {
  setfillstyle(1,6);
  floodfill(25,my-30,4);
  cur=9;
  setfillstyle(1,1);
  floodfill(580,my-35,4);

 }
}
tooltext();
break;

case 77:
keysound();

if(t==1&&cur>9)
{
 if(cur==12)
 {
  setfillstyle(1,7);
  floodfill(410,50,15);

  cur=10;
  setfillstyle(1,1);
  floodfill(170,50,15);
 }
 else
 {
  setfillstyle(1,7);
  if(cur==10)
  floodfill(170,50,15);
  else if(cur==11)
  floodfill(290,50,15);

  cur++;
  setfillstyle(1,1);
  if(cur==11)
  floodfill(290,50,15);
  else if(cur==12)
  floodfill(410,50,15);
 }
}
else
{
 if(cur!=9)
 {
  setfillstyle(1,6);
  if(cur==8&&select_mode==0)
  floodfill(495,my-35,4);
  else if(cur==7)
  floodfill(415,my-32,4);
  else
  floodfill(25+cur*50,my-30,4);

  cur++;
  setfillstyle(1,1);
  if(cur==9)
  floodfill(580,my-35,4);
  else if(cur==8&&select_mode==0)
  floodfill(495,my-35,4);
  else if(cur==7)
  floodfill(415,my-32,4);
  else
  floodfill(25+cur*50,my-30,4);
 }
 else
 {
  setfillstyle(1,6);
  floodfill(580,my-35,4);

  cur=0;
  setfillstyle(1,1);
  floodfill(25,my-30,4);
 }
}
tooltext();
break;


case 72:
if(t==1)
{
keysound();
cur=10;
}
toolbar();
break;

case 80:
if(t==1)
{
keysound();
cur=0;
}
toolbar();
break;
case '\r':
keysound();
if(cur==9)
{
pointer(0);
move();
}
else if(cur==8)
select(0);
else if(cur==7)
connect();
else if(cur==10)
tt();
else if(cur==11)
simulate();
else if(cur==12)
boolean(0);

else
{
node *n=getn();
n->gate=cur;
n->link=NULL;

if(start==NULL)
{
n->x=80;
n->y=120;
n->prev_link=NULL;
start=n;
last=start;
}
else
{
if(nog>29)
{
 overflow();
 break;
}
 n->prev_link=last;
 if(current->y<my-120)
 {
  n->x=last->x;
  n->y=last->y+50;
 }
 else
 {
 n->x=last->x+100;
 n->y=120;
 }
}
last->link=n;
last=n;

current=last;

current->sno=nog;
nog++;
draw_gate(n,cur,0);

}
break;
}
}
void redraw()
{
 clrscr();
 cleardevice();
 border();
 toolbar();
 int i;
 node*n=start;
 for(i=0;i<nog;i++)
 {
  draw_gate(n,n->gate,0);
  n=n->link;
 }

  stack*nn=strt;
  while(nn!=NULL)
  {
   setcolor(nn->col);
   switch(nn->dir)
   {
    case 75:
    line(nn->x,nn->y,nn->x-5,nn->y);
    break;
    case 72:
    line(nn->x,nn->y,nn->x,nn->y-5);
    break;
    case 77:
    line(nn->x,nn->y,nn->x+5,nn->y);
    break;
    case 80:
    line(nn->x,nn->y,nn->x,nn->y+5);
    break;
   }
   nn=nn->link;
  }
  disp();
}
void man()
{
int j,k,q,c;
int gd=DETECT,gm;
initgraph(&gd,&gm,"C:\\turboc3\\bgi");
mx=getmaxx();
my=getmaxy()-55;
midx=mx/2;
midy=my/2;

setbkcolor(0);
border();
toolbar();
for(j=0;j<90;j++)
strcpy(va[j],"?");
for(;;)
{
act();
}
}
void main()
{
man();
}
