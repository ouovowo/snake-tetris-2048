#include<ctime>
#include<string>
#include<vector>
#include<cstdio>
#include<cstring>
#include<conio.h>
#include<tchar.h>
#include<windows.h>

using namespace std;

int s=1,v;
bool tick=0;
unsigned char backup=32;
HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
char a[25][25][2],sx,sy,sl=1,u,w,vol,preX=22,preY=9;
const unsigned char c[8] = { 240,249,250,254,252,247,112,196 };

struct three
{
	char x,y,z;
};

//vector<three> mapx[26],mapy[26];

unsigned char buff[25][51],buf[25][51]=
{
	"                                                  ",
	"                                                  ",
	"    ┌─┬─┬─┬─┬─┬─┬─┬─┬─┬─┐    ",
	"    │Ｑ│Ｗ│Ｅ│Ｒ│Ｔ│Ｙ│Ｕ│Ｉ│Ｏ│Ｐ│    ",
	"    └┬┴┬┴┬┴┬┴┬┴┬┴┬┴┬┴┬┴┬┘    ",
	"      │Ａ│Ｓ│Ｄ│Ｆ│Ｇ│Ｈ│Ｊ│Ｋ│Ｌ│      ",
	"      └┬┴┬┴┬┴┬┴┬┴┬┴┬┴┬┴─┘      ",
	"        │Ｚ│Ｘ│Ｃ│Ｖ│Ｂ│Ｎ│Ｍ│咒:         ",
	"        └─┴─╆━┷━┷━┷━┷━┪bin         ",
	"                ┃                  ┃diy         ",
	"                ┗━━━━━━━━━┛out         ",
	"    ┌─┐                      ↖                ",
	"    │  │  ┌──┐  ┌──────────┐    ",
	"    │  │  │以按│  │请按以上的键盘按键，│    ",
	"    │  │↙│调︻│  │来选择对应游戏界面。│    ",
	"    │  │  │整↑│  ╰──────────╯    ",
	"    │  │  │蛇︼│  ┌──────────┐    ",
	"    │  │  │的︻│  │【←】【→】选择有无│    ",
	"    │  │  │速↓│  │边框，按回车键确认。│    ",
	"    │  │  │度︼│  ╰──────────╯    ",
	"    │  │  │。，│      ↘┌───┲━━━┓    ",
	"    │  │  ╰──╯        │  √  ┃  ×  ┃    ",
	"    └─┛                  └───┺━━━┛    ",
	"                                                  ",
	"                                                  "
};

inline void p(char x,char y)
{
	x=x*2;
	y=y*2;
}

inline void go(char x,char y)
{
	SetConsoleCursorPosition(h, { x,y });
}

void f5()
{
	go(2,0);
	char tmp[3]="";
	for(char i=0;i<25;++i)
		for(char j=0;j<49;j+=2)
			if(buff[i][j]!=a[i][j>>1][0]+128||buff[i][j+1]!=buf[i][j+1])
			{
				SetConsoleTextAttribute(h,a[i][j>>1][0]==127?c[6]:c[0]);
				tmp[1]=buff[i][j+1]=buf[i][j+1];
				buff[i][j]=a[i][j>>1][0]+128;
				tmp[0]=buf[i][j];
				go(j+1,i+1);
				printf("  ");
				go(j+1,i+1);
				printf("%s",tmp);
			}
}

void top(char* arg)
{
	HWND hwnd,hwnd0 = GetConsoleWindow();
	SMALL_RECT rect={0,0,3,0};
	char cmd[10]={0};
	DWORD id;
	system("title →");
	sscanf(arg,"%x",&hwnd);
	sprintf(arg,"%x",hwnd0);
	SetWindowText(hwnd,arg);
	system("mode con lines=1");
	SetConsoleWindowInfo(h,1,&rect);
	GetWindowThreadProcessId(hwnd,&id);
	h=OpenProcess(PROCESS_ALL_ACCESS,0,id);
	SetWindowLong(hwnd0,GWL_STYLE,GetWindowLong(hwnd0,GWL_STYLE)&~WS_CAPTION);
	SetWindowLong(hwnd,GWL_STYLE,GetWindowLong(hwnd,GWL_STYLE)&~WS_MAXIMIZEBOX);
	system("mode con lines=1 cols=4");
	do
	{
		GetWindowText(hwnd0,arg,3);
		if(!strstr(cmd,arg))
		{
			sprintf(cmd,"title %s",arg);
			system(cmd);
			system("cls");
			printf(" %s",arg);
		}
		if(!IsIconic(hwnd)&&IsIconic(hwnd0)) ShowWindow(hwnd0,SW_SHOWNOACTIVATE);
		if(IsIconic(hwnd)) ShowWindow(hwnd0,SW_SHOWMINNOACTIVE);
		if(GetForegroundWindow()==hwnd)
		{
			SetWindowPos(hwnd0,HWND_TOPMOST,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
			SetWindowPos(hwnd0,HWND_NOTOPMOST,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
		}
		if(GetForegroundWindow()==hwnd0)
		{
			SetWindowPos(hwnd,HWND_TOP,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
			SetWindowPos(hwnd0,HWND_TOP,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
			SetForegroundWindow(hwnd);
		}
		POINT p;
		GetCursorPos(&p);
		SetWindowPos(hwnd0,0,p.x+5,p.y+5,0,0,SWP_NOZORDER|SWP_NOSIZE);
		Sleep(1);
		GetExitCodeProcess(h,&id);
	}
	while(id==STILL_ACTIVE);
	exit(0);
}

void btm(char* arg)
{
	DWORD id;
	char cmd[256];
	HWND hwnd0,hwnd = GetConsoleWindow();//ImmAssociateContext(hwnd, NULL);
	sprintf(cmd,"start %s %x",arg,hwnd);system(cmd);
	do
	{
		Sleep(1);
		GetWindowText(hwnd,cmd,255);
	}
	while(strstr(cmd,"贪吃蛇"));
	sscanf(cmd,"%x",&hwnd0);
	system("title 贪吃蛇");
	GetWindowThreadProcessId(hwnd0,&id);
	HANDLE hp=OpenProcess(PROCESS_ALL_ACCESS,0,id);
	do
	{
		if(_kbhit()) switch(getch())
		{
		case 72:SetWindowText(hwnd0,"↑");break;
		case 80:SetWindowText(hwnd0,"↓");break;
		case 75:SetWindowText(hwnd0,"←");break;
		case 77:SetWindowText(hwnd0,"→");break;
		case 27:exit(0);
		}
		Sleep(1);
		GetExitCodeProcess(hp,&id);
	}
	while(id==STILL_ACTIVE);
	exit(0);
}

void dfs(char x,char y)
{
	if(x==25) x=0;
	if(y==25) y=0;
	if(x==-1) x=24;
	if(y==-1) y=24;
	if(a[x][y][0]>-127) return;
	a[x][y][0]=-1;
	dfs(x-1,y);
	dfs(x+1,y);
	dfs(x,y-1);
	dfs(x,y+1);
}

void add()
{
	if(sl<0)
	{
		if(--sl==-5) sl=-1;
		go(sy*2+1,sx+1);
		SetConsoleTextAttribute(h,c[-sl]);
		switch(sl)
		{
		case -1:printf("●");break;
		case -2:printf("▲");break;
		case -3:printf("◆");break;
		case -4:printf("★");
		}
		SetConsoleTextAttribute(h, c[0]);
		return;
	}
	short k=0;
	char b[625][2];
	for(char i=0;i<25;i++)
		for(char j=0;j<25;j++)
			if(a[i][j][0]==-1)
			{
				b[k][0]=i;
				b[k++][1]=j;
			}
	if(!k)
	{
		sl=0;
		return;
	}
	sx=b[k=rand()%k][0];sy=b[k][1];sl=rand()%11;
	SetConsoleCursorPosition(h,{(sy)*2+1,sx+1});
	if(!sl)					{SetConsoleTextAttribute(h, c[-(sl=-1)]);printf("●");}
	else if(sl==1)			{SetConsoleTextAttribute(h, c[  sl= 4 ]);printf("★");}
	else if(sl==2||sl==3)	{SetConsoleTextAttribute(h, c[  sl= 3 ]);printf("◆");}
	else if(sl>6)			{SetConsoleTextAttribute(h, c[  sl= 1 ]);printf("●");}
	else					{SetConsoleTextAttribute(h, c[  sl= 2 ]);printf("▲");}
	SetConsoleTextAttribute(h, c[0]);
}

void read(char ch)
{
	char fname[6]="a.bin";
	fname[0]=ch-'A'+'a';
	FILE *fp=fopen(fname,"rb");
	char i=0,j=0,t;
	for(char loop=25*25/8;loop;loop--)
	{
		fread(&t,1,1,fp);
		for(char k=7;k>=0;k--)
		{
			char x=i,y=j+k;
			if(y>=25)
			{
				y-=25;
				x++;
			}
			a[x][y][0]=(t&1)||tick&&(x==0||x==24||y==0||y==24)?127:-127;
			t>>=1;
		}
		if((j+=8)>=25)
		{
			j-=25;
			i++;
		}
	}
	fread(&t,1,1,fp);
	a[24][24][0]=(t>>7&1)||tick?127:-127;
	fclose(fp);
}

void save()
{
	char str[15];
	int loop=0;
	FILE *fp;
	do
	{
		memset(str,0,sizeof(str));
		sprintf(str,"%d.bin",loop++);
	}
	while(GetFileAttributes(str)!=-1);
	fp=fopen(str,"wb");
	unsigned char k=0,t=0;
	for(char i=0;i<25;i++)
		for(char j=0;j<25;j++)
		{
			t=(t<<1)+(a[i][j][0]==127);
			if(++k==8)
			{
				fwrite(&t,1,1,fp);
				//fprintf(fp,"%d",t);
				k=t=0;
			}
		}
	//fprintf(fp,"%d",t<<3);
	t=t<<7;
	fwrite(&t,1,1,fp);
	fclose(fp);
}

void diy()
{
	CONSOLE_CURSOR_INFO cci = { 20,1 };
	SetConsoleCursorInfo(h, &cci);
	memset(a,-127,sizeof(a));
	go( 1,0 );
	printf("方向键移动 空格键放置或清除 回车键开始 【S】键保存");
	for(char i=0;i<25;++i)
	{
		printf("\n ");
		for(char j=0;j<25;++j) printf("·");
	}
	go(23,13);printf("■■□");
	go((sy=12)*2+1,(sx=12)+1);
	while(1)
	{
		Sleep(1); 
		if (_kbhit()) switch (_getch())
		{
		case 72:if(sx)		go(sy*2+1,--sx+1);break;
		case 80:if(sx!=24)	go(sy*2+1,++sx+1);break;
		case 75:if(sy)		go(--sy*2+1,sx+1);break;
		case 77:if(sy!=24)	go(++sy*2+1,sx+1);break;
		case 83:case 115:	save();break;
		case 13:
			a[12][12][0]=-1;
			dfs(12,13);
			if(a[12][11][0]==-1) return;
			MessageBox(GetConsoleWindow(), _T("这路能走？不存在的！"), _T("来自蛇的消息"), 0);
			for(char i=0;i<25;++i)
				for(char j=0;j<25;++j)
					if(a[i][j][0]==-1)
						a[i][j][0]=-127;
			break;
		case 32:
			if(sx==12&&(sy==11||sy==12||sy==13)) break;
			if(a[sx][sy][0]==127) printf("·");
			else printf("▓");
			a[sx][sy][0]=-a[sx][sy][0];
			go(sy*2+1,sx+1);
			break;
		case 27:switch (MessageBox(GetConsoleWindow(), _T("点击【中止】，退出游戏\n点击【重试】，重新开始\n点击【忽略】，继续游戏"), _T("暂停中"), 2))
		{
		case 3:exit(0);
		case 4:return;
		}
		}
	}
}

inline void markV()
{
	buf[20][29]+=3;buf[20][37]--;buf[20][45]-=3;
	buf[21][29]++;buf[21][45]--;
	buf[22][29]+=3;buf[22][37]--;buf[22][45]-=3;
	buf[20][31]=buf[22][31]=buf[20][33]=buf[22][33]=buf[20][35]=++buf[22][35];
	buf[20][39]=buf[22][39]=buf[20][41]=buf[22][41]=buf[20][43]=--buf[22][43];
}

inline void markX()
{
	buf[20][29]-=3;buf[20][37]++;buf[20][45]+=3;
	buf[21][29]--;buf[21][45]++;
	buf[22][29]-=3;buf[22][37]++;buf[22][45]+=3;
	buf[20][31]=buf[22][31]=buf[20][33]=buf[22][33]=buf[20][35]=--buf[22][35];
	buf[20][39]=buf[22][39]=buf[20][41]=buf[22][41]=buf[20][43]=++buf[22][43];
}

inline void volUp()
{
	vol++;
	if(vol%8)
	{
		if(vol%8==1)
		{
			buf[21-vol/8][6]=168;
			buf[21-vol/8][7]=120;
		}
		else buf[21-vol/8][7]++;
	}
	else buf[22-vol/8][7]+=2;
	v=3000/(vol+10);
}

inline void volDown()
{
	vol--;
	if(vol%8)
	{
		if(vol%8==7) buf[21-vol/8][7]-=2;
		else buf[21-vol/8][7]--;
	}
	else
	{
		buf[21-vol/8][6]=32;
		buf[21-vol/8][7]=32;
	}
	v=3000/(vol+10);
}

inline void clearSpace(char m)
{
	buf[10][17]+=3*m;buf[10][37]+=3*m;
	buf[9][17]+=m;buf[9][37]+=m;
	for(char k=19;k<36;k+=2)
	{
		if(k>>1&1) buf[8][k]+=m;
		else buf[8][k]+=3*m;
		buf[10][k]+=m;
	}
	buf[8][17]+=10*m;
	buf[8][37]+=6*m;
}

inline void preView(char &x,char &y)
{
	if(buf[x][y]==165||buf[x][y]==167) buf[x][y]--;
	else buf[x][y]-=3;
	if(x==11&&y<9) y+=2;
	else if(x==22&&y>5) y-=2;
	else if(y==5) x--;
	else x++;
	if(buf[x][y]==164||buf[x][y]==166) buf[x][y]++;
	else buf[x][y]+=3;
}

inline void keyDown(unsigned char backup,unsigned char ch)
{
	if(backup==' ') clearSpace(-1);
	else
	{
		backup+=128;
		for(char i=1;i<=10;i++)
		{
			if(backup)
				for(char j=1;j<=50;j++)
				{
					if(buf[i][j-1]==163&&buf[i][j]==backup)
					{
						buf[i-1][j-2]=buf[i-1][j-2]==179?176:208;
						buf[i-1][j]=buf[i-1][j]==165?164:216;
						buf[i-1][j+2]=buf[i-1][j+2]==183?180:208;
						buf[i][j-2]=--buf[i][j+2];
						if(buf[i+1][j-2]==187) buf[i+1][j-2]=184;
						else if(buf[i+1][j-2]==222) buf[i+1][j-2]=216;
						else buf[i+1][j-2]=224;
						buf[i+1][j]=buf[i+1][j]==165?164:208;
						if(buf[i+1][j+2]==191) buf[i+1][j+2]=188;
						else if(buf[i+1][j+2]==221) buf[i+1][j+2]=216;
						else if(buf[i+1][j+2]==231) buf[i+1][j+2]=224;
						else buf[i+1][j+2]=200;
						backup=0;
						break;
					}
				}
			else break;
		}
	}
	if(ch==' ') clearSpace(1);
	else
	{
		ch+=128;
		for(char i=1;i<=20;i++)
		{
			if(ch)
				for(char j=1;j<=50;j++)
				{
					if(buf[i][j-1]==163&&buf[i][j]==ch)
					{
						buf[i-1][j-2]=(buf[i-1][j-2]==176?179:214);
						buf[i-1][j]=buf[i-1][j]==164?165:219;
						buf[i-1][j+2]=buf[i-1][j+2]==180?183:213;
						buf[i][j-2]=++buf[i][j+2];
						if(buf[i+1][j-2]==184) buf[i+1][j-2]=187;
						else if(buf[i+1][j-2]==216) buf[i+1][j-2]=222;
						else buf[i+1][j-2]=232;
						buf[i+1][j]=buf[i+1][j]==164?165:211;
						if(buf[i+1][j+2]==188) buf[i+1][j+2]=191;
						else if(buf[i+1][j+2]==216) buf[i+1][j+2]=221;
						else if(buf[i+1][j+2]==224) buf[i+1][j+2]=231;
						else buf[i+1][j+2]=205;
						ch=0;
						break;
					}
				}
			else break;
		}
	}
}

void set(char *arg)
{
	CONSOLE_CURSOR_INFO cci = { 20,0 };
	SetConsoleCursorInfo(h, &cci);
	SetConsoleTextAttribute(h,c[5]);
	go(2,0);
	printf("时间: 00:00%31d :成绩", 0);
	SetConsoleTextAttribute(h,c[0]);
	f5();
	clock_t ct=clock();
	bool flag=0;
	char ch,cmd[4]={0};
	v=3000/(vol+10);
	while(1)
	{
		if(clock()-ct>v)
		{
			preView(preX,preY);
			ct=clock();
			f5();
		}
		Sleep(1);
		if (_kbhit())
		{
			ch=getch();
			if(ch==27) switch (MessageBox(GetConsoleWindow(), _T("点击【中止】，退出游戏\n点击【重试】，重新开始\n点击【忽略】，继续游戏"), _T("暂停中"), 2))
			{
			case 3:exit(0);
			case 4:memset(a,-1,sizeof(a));
			}
			if(ch<0) flag=1;
			if(flag&&_kbhit())
			{
				flag=0;
				switch(ch=getch())
				{
				case 72:if(vol!=80)volUp();f5();break;
				case 80:if(vol)volDown();f5();break;
				case 75:
					if(!tick)
					{
						tick=1;
						markV();
						for(char k=0;k<25;k++)
							a[0][k][0]=a[24][k][0]=a[k][0][0]=a[k][24][0]=127;
						f5();
					}
					break;
				case 77:
					if(tick)
					{
						tick=0;
						markX();
						for(char k=0;k<25;k++)
							a[0][k][0]=a[24][k][0]=a[k][0][0]=a[k][24][0]=-127;
						f5();
					}
				}
			}
			else if(isalpha(ch)||ch==' ')
			{
				keyDown(backup,ch=toupper(ch));
				read(ch); 
				f5();
				cmd[0]=cmd[1];
				cmd[1]=cmd[2];
				cmd[2]=backup=ch;
				//if(strstr(cmd,"BIN")) open(arg);
				if(strstr(cmd,"DIY"))
				{
					diy();
					return;
				}
				if(strstr(cmd,"OUT")) btm(arg);
			}
			else if(ch=='\r')
			{
				dfs(12,13);
				return;
			}
		}
	}
}

void play(char *arg)
{
	memset(buff,0,sizeof(buff));
	set(arg);
	system("color f0");
	system("cls");
	for(char i=0;i<25;i++)
	{
		printf("\n ");
		for(char j=0;j<25;j++)
			if(a[i][j][0]==127) printf("▓");
				else printf("  ");
	}
	go(2,0);
	printf("时间: 00:00%31d :成绩\n", 0);
	clock_t ct=clock();
	time_t t0 = time(0), t = 0;
	char e=0,x=0,y=1,hx=12,hy=13,tx=12,ty=11,x0=0,y0;
	a[12][11][0]=a[12][11][1]=a[12][12][0]=12;a[12][12][1]=13;a[12][13][0]=-127;
	go(23,13);
	printf("■■□");
	add();
	
	while(1)
	{
		if (t != time(0))
		{
			go(8,0);
			printf("%02d:%02d", ((t = time(0)) - t0) / 60, (time(0) - t0) % 60);
		}
		if (_kbhit()) switch (x0=_getch())
		{
		case 72:case 80:if(x) x0=0;break;
		case 75:case 77:if(y) x0=0;break;
		case 27:
			t = time(0);
			switch (MessageBox(GetConsoleWindow(), _T("点击【中止】，退出游戏\n点击【重试】，重新开始\n点击【忽略】，继续游戏"), _T("暂停中"), 2))
			{
			case 3:exit(0);
			case 4:t0 = time(0);break;
			default:t0 += time(0) - t;
			}
			break;
		default:x0=0;
		}
		if(clock()-ct>v)
		{
			switch(x0)
			{
			case 72:x=-1;y= 0;break;
			case 80:x= 1;y= 0;break;
			case 75:x= 0;y=-1;break;
			case 77:x= 0;y= 1;
			}
			ct=clock();
			if(sl<0) add();
			a[hx][hy][0]=hx+x;
			a[hx][hy][1]=hy+y;
			if(a[hx][hy][0]==25) a[hx][hy][0]=0;
			if(a[hx][hy][1]==25) a[hx][hy][1]=0;
			if(a[hx][hy][0]==-1) a[hx][hy][0]=24;
			if(a[hx][hy][1]==-1) a[hx][hy][1]=24;
			go(hy*2+1,hx+1);printf("■");
			hx=a[x0=hx][hy][0];if(a[hx][hy=a[x0][hy][1]][0]==-1) a[hx][hy][0]=-127;
			if(hx==sx&&hy==sy)
			{
				go( 34,0 );
				printf("%10d",s+=sl*sl);
				e+=sl>0?sl:(sl=-sl);
				add();
			}
			if(!e)
			{
				go(ty*2+1,tx+1);printf("  ");
				tx=a[x0=tx][ty][0];
				ty=a[x0][y0=ty][1];
				a[x0][y0][0]=-1;
			}
			else --e;
			go(hy*2+1,hx+1);
			if(a[hx][hy][0]>=0)
			{
				SetConsoleTextAttribute(h,c[7]);
				if(a[hx][hy][0]==127) printf("▓");else printf("■");
				SetConsoleTextAttribute(h,c[0]);
				if(!sl) MessageBox(GetConsoleWindow(), _T("小生无言以对…Orz"), _T("膜拜大佬"), 0);
				else MessageBox(GetConsoleWindow(), _T("打败自己的不是敌人，而是膨胀的自己。:)"), _T("游戏结束"), 0);
				for(s=0;s<25;s++)
					for(t=0;t<25;t++)
						if(a[s][t][0]!=127)
							a[s][t][0]=a[s][t][1]=-127;
				s=1;
				return;
			}
			else printf("□");
		}
		Sleep(1);
	}
}

void dprint(char dchar[])
{
	CONSOLE_SCREEN_BUFFER_INFO i;
	GetConsoleScreenBufferInfo(h, &i);
	printf("%s", dchar);
	SetConsoleCursorPosition(h, { i.dwCursorPosition.X + 2, i.dwCursorPosition.Y });
}

void help()
{
	SetConsoleCursorPosition(h, { 1,1 }); dprint("┏"); for (s = 23; s; s--) dprint("━"); SetConsoleTextAttribute(h, 207); printf("×\n");
	SetConsoleTextAttribute(h, c[0]); printf(" "); for (s = 23; s; s--) { dprint("┃"); printf("%46c┃\n ", 0); }
	dprint("┗"); for (s = 23; s; s--) dprint("━"); printf("┛");
	go(5,4 ); printf("① 按【↑】【↓】【←】【→】控制蛇的移动，");
	go(8,6 ); printf("使蛇吃到果实，获得长度与积分；");
	go(5,9 ); printf("② 在游戏过程中，可以按【ESC】来暂停游戏；");
	go(5,12); printf("③ 游戏结束后，点击对话框的确定，返回首页；");
	go(5,15); printf("④ 按【↑】【↓】来移动光标，以选择选项，并");
	go(8,17); printf("且按下【ENTER】回车键，以确认；");
	go(5,20); printf("⑤ 当蛇头碰壁或撞到自身时，游戏结束。");
	go(26,24); printf("Presented by zhujun.xin");
	go(51,1); while (_getch() != 13);
}

void welc()
{
	const unsigned char m[7]="███";
	system("cls"); SetConsoleCursorPosition(h, { 7,7 });
	printf("%s █%4c█%4c█%4c█  █ %s\n%7c█%5c██  █   ██   █ █  █\n%13s █ █ █  █  █  ██   ██\n%11c█ █  ██ %s█ █ █  █\n%13s █%4c█ █%4c█ █  █ %s\n\n\n\n%20c【开始游戏】\n\n%20c【游戏帮助】\n\n%20c【退出游戏】",m,0,0,0,m,0,0,m,0,m,m,0,0,m,0,0,0);
	FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE)); s = !s;
	CONSOLE_CURSOR_INFO i = { 20,1 }; SetConsoleCursorInfo(h, &i);
	while (1)
	{
		SetConsoleCursorPosition(h,{32,15+s*2});
		switch (_getch())
		{
		case 13:if (s == 2) exit(0);return;
		case 72:s = s ? s - 1 : 2; break;
		case 80:s = s == 2 ? 0 : s + 1;
		}
	}
}

int main(int argc, char* argv[])
{
	system("color f0");
	if(argc==2) top(argv[1]);
	system("mode con lines=27 cols=52");
	system("title 贪吃蛇");
	srand(time(0));
	memset(a,-127,sizeof(a));
	while (1)
	{
		welc();
		s ? help() : play(argv[0]);
	}
}
