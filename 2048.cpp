#include <ctime>
#include <cstdio>
#include <cstring>
#include <conio.h>
#include <tchar.h>
#include <windows.h>

bool win;
int s0, s = 1;
char a0[4][4], a[4][4];
const HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
const unsigned char c[12] = { 240,120,135,179,59,162,42,230,110,213,93,206 };

void dprint(char dchar[])
{
	CONSOLE_SCREEN_BUFFER_INFO i;
	GetConsoleScreenBufferInfo(h, &i);
	printf("%s", dchar);
	SetConsoleCursorPosition(h, { i.dwCursorPosition.X + 2, i.dwCursorPosition.Y });
}

void p(char x, char y)
{
	const unsigned char n = a[x][y];
	SetConsoleCursorPosition(h, { y = y * 12 + 3,x = x * 6 + 2 });
	if (n < 12) SetConsoleTextAttribute(h, c[n]); else SetConsoleTextAttribute(h, 15);
	if (n == 11)
	{
		printf("%5d%5c", 2, 0);
		SetConsoleCursorPosition(h, { y,++x }); printf(" ★%3d%4c", 0, 0);
		SetConsoleCursorPosition(h, { y,++x }); printf("%6d%4c", 4, 0);
		SetConsoleCursorPosition(h, { y,++x }); printf("%5d%5c", 8, 0);
		SetConsoleCursorPosition(h, { y,++x }); printf("%10c", 0);
		if (!win) s0 = 1; return;
	}
	printf("%10c", 0);
	SetConsoleCursorPosition(h, { y,++x }); printf("%10c", 0);
	SetConsoleCursorPosition(h, { y,++x });
	switch (n)
	{
	case 0:printf("%10c", 0); break;
	case 1:case 2:case 3:printf("%5d%5c", 1 << n, 0); break;
	case 4:case 5:case 6:printf("%6d%4c", 1 << n, 0); break;
	case 7:case 8:case 9:case 10:printf("%7d   ", 1 << n); break;
	default:printf("   2^%d   ", n);
	}
	SetConsoleCursorPosition(h, { y,++x }); printf("%10c", 0);
	SetConsoleCursorPosition(h, { y,++x }); printf("%10c", 0);
}

void tab()
{
	SetConsoleCursorPosition(h, { 2,0 }); printf("时间: 00:00%31d :成绩\n ", 0);
	for (s = 4; s; s--)
	{
		for (s0 = 4; s0; s0--)
		{
			if (s == 4) { if (s0 == 4) dprint("╔"); else dprint("╦"); }
			else { if (s0 == 4) dprint("╠"); else dprint("╬"); }
			for (char k = 5; k; k--) dprint("═");
		}
		if (s == 4) printf("╗\n "); else printf("╣\n ");
		for (s0 = 5; s0; s0--)
		{
			for (int k = 4; k; k--)
			{
				dprint("║");
				printf("%10c", 0);
			}
			printf("║\n ");
		}
	}
	for (s = 4; s; s--)
	{
		if (s == 4) dprint("╚"); else dprint("╩");
		for (s0 = 5; s0; s0--) dprint("═");
	}
	printf("╝");
}

void add()
{
	char k = 0, b[16][2];
	for (char i = 0; i < 4; i++)
		for (char j = 0; j < 4; j++)
			if (!a[i][j])
			{
				b[k][0] = i;
				b[k++][1] = j;
			}
	if (k)
	{
		a[b[k = rand() % k][0]][b[k][1]] = rand() % 10 ? 1 : 2;
		p(b[k][0], b[k][1]);
	}
}

void over()
{
	const HWND w = GetConsoleWindow();
	if (s0 == 2)
	{
		if (MessageBox(w, _T("你行，你牛逼！^3^\n是否继续挑战？^0^"), _T("你赢了"), 4) == 6) win = 1;
		return;
	}
	for (char i = 0; i < 4; i++)
		for (char j = 0; j < 4; j++)
			if (a[i][j] > s0) s0 = a[i][j];
	switch (s0)
	{
	case 2:case 3:case 4:MessageBox(w, _T("无语，沉默中。O_O"), _T("你输了"), 0); return;
	case 5:case 6:MessageBox(w, _T("够低，这成绩。X_X"), _T("你输了"), 0); return;
	case 7:MessageBox(w, _T("就这，还想赢？=_="), _T("你输了"), 0); return;
	case 8:MessageBox(w, _T("继续，努力吧。^_^"), _T("你输了"), 0); return;
	case 9:MessageBox(w, _T("不错，加把劲。^0^"), _T("你输了"), 0); return;
	case 10:MessageBox(w, _T("可惜，还差点。T_T"), _T("你输了"), 0); return;
	case 11:MessageBox(w, _T("你行，你牛逼！^3^"), _T("你赢了"), 0); return;
	default:MessageBox(w, _T("膜拜，神犇啊！Orz"), _T("你赢了"), 0); win = 0;
	}
}

void move(char d)
{
	char i, j, k, *x = &i, *y = &j, *up, b[4][4];
	memcpy(b, a, 16);
	const int t = s;
	if (d < 3)
	{
		x = &j;
		y = &i;
	}
	d = !(d & 1) * 3;
	for (i = d; d ? i >= 0 : i < 4; d ? i-- : i++)
	{
		up = 0;
		for (j = d; d ? j >= 0 : j < 4; d ? j-- : j++)
		{
			if (!a[*x][*y]) continue;
			if (!up)
			{
				up = &a[*x][*y];
				continue;
			}
			if (*up == a[*x][*y])
			{
				s += 1 << ++(*up);
				a[*x][*y] = 0;
				up = 0;
			}
			else up = &a[*x][*y];
		}
		for (j = d; d ? j >= 0 : j < 4; d ? j-- : j++) if (a[*x][*y])
		{
			up = &a[*x][*y];
			x == &i ? y = &k : x = &k;
			for (k = d ? j + 1 : j - 1; d ? k < 4 : k >= 0; d ? k++ : k--)
			{
				if (a[*x][*y]) break;
				a[*x][*y] = *up;
				*up = 0;
				up = &a[*x][*y];
			}
			x == &i ? y = &j : x = &j;
		}
	}
	k = 0;
	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
			if (a[i][j] != b[i][j])
			{
				k = 1;
				p(i, j);
			}
	if (k)
	{
		add();
		memcpy(a0, b, 16); if (s0 != 1) s0 = t;
		SetConsoleTextAttribute(h, c[0]); SetConsoleCursorPosition(h, { 34,0 }); printf("%10d", s);
		for (i = 0; i < 4; i++)
			for (j = 0; j < 4; j++)
				if (!a[i][j] || i&&a[i][j] == a[i - 1][j] || j&&a[i][j] == a[i][j - 1])
				{
					if (s0 == 1) s0 = 2;
					return;
				}
		s0 = 1;
	}
}

void play()
{
	memset(a, 0, 16); tab(); add(); add(); memcpy(a0, a, 16);
	SetConsoleTextAttribute(h, c[0]);
	time_t t0 = time(0), t = 0;
	while (1)
	{
		if (t != time(0))
		{
			SetConsoleCursorPosition(h, { 8,0 });
			printf("%02d:%02d", ((t = time(0)) - t0) / 60, (time(0) - t0) % 60);
		}
		if (s0 == 1 || s0 == 2)
		{
			over();
			if (!win) return;
			t0 += time(0) - t; s0 = s; memcpy(a0, a, 16);
		}
		if (_kbhit()) switch (_getch())
		{
		case 72:move(1); break;
		case 80:move(2); break;
		case 75:move(3); break;
		case 77:move(4); break;
		case 8:
			memcpy(a, a0, 16);
			for (char i = 0; i < 4; i++) for (char j = 0; j < 4; j++) p(i, j);
			SetConsoleTextAttribute(h, c[0]); SetConsoleCursorPosition(h, { 34,0 }); printf("%10d", s = s0);
			break;
		case 27:
			t = time(0);
			switch (MessageBox(GetConsoleWindow(), _T("点击【中止】，退出游戏\n点击【重试】，重新开始\n点击【忽略】，继续游戏"), _T("暂停中"), 2))
			{
			case 3:exit(0);
			case 4:
				t0 = time(0); memset(a, 0, 16); tab(); add(); add(); memcpy(a0, a, 16); win = 0;
				SetConsoleTextAttribute(h, c[0]); break;
			default:t0 += time(0) - t;
			}
		}
		Sleep(1);
	}
}

void help()
{
	SetConsoleCursorPosition(h, { 1,1 }); dprint("┏"); for (s = 23; s; s--) dprint("━"); SetConsoleTextAttribute(h, 207); printf("×\n");
	SetConsoleTextAttribute(h, c[0]); printf(" "); for (s = 23; s; s--) { dprint("┃"); printf("%46c┃\n ", 0); }
	dprint("┗"); for (s = 23; s; s--) dprint("━"); printf("┛");
	SetConsoleCursorPosition(h, { 5,4 }); printf("① 按【↑】【↓】【←】【→】控制方块移动，");
	SetConsoleCursorPosition(h, { 8,6 }); printf("按【BACKSPACE】退格键可返回上一步；");
	SetConsoleCursorPosition(h, { 5,9 }); printf("② 在游戏过程中，可以按【ESC】来暂停游戏；");
	SetConsoleCursorPosition(h, { 5,12 }); printf("③ 游戏结束后，点击对话框的确定，返回首页；");
	SetConsoleCursorPosition(h, { 5,15 }); printf("④ 按【↑】【↓】来移动光标，以选择选项，并");
	SetConsoleCursorPosition(h, { 8,17 }); printf("且按下【ENTER】回车键，以确认；");
	SetConsoleCursorPosition(h, { 5,20 }); printf("⑤ 当有一方块数值达到2048，即视为胜利。");
	SetConsoleCursorPosition(h, { 26,24 }); printf("Presented by zhujun.xin");
	SetConsoleCursorPosition(h, { 51,1 }); while (_getch() != 13);
}

void welc()
{
	system("cls"); SetConsoleCursorPosition(h, { 8,7 });
	const unsigned char n[7] = "█  █", m[7] = "███";
	printf("%s%4c%s%4c%s%4c%s\n%12c█%4c%s%4c%s%4c%s\n%8c%s%4c%s%4c%s%4c%s\n%8c█%8c%s%8c█%4c%s\n%8c%s%4c%s%8c█%4c%s\n\n\n\n%20c【开始游戏】\n\n%20c【游戏帮助】\n\n%20c【退出游戏】", m, 0, m, 0, n, 0, m, 0, 0, n, 0, n, 0, n, 0, m, 0, n, 0, m, 0, m, 0, 0, n, 0, 0, n, 0, m, 0, m, 0, 0, m, 0, 0, 0);
	CONSOLE_CURSOR_INFO i = { 20,1 }; SetConsoleCursorInfo(h, &i); i.bVisible = 0;
	FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE)); s = !s;
	while (1)
	{
		SetConsoleCursorPosition(h, { 32,15 + short(s) * 2 });
		switch (_getch())
		{
		case 13:if (s == 2) exit(0); if (!s) SetConsoleCursorInfo(h, &i); return;
		case 72:s = s ? s - 1 : 2; break;
		case 80:s = s == 2 ? 0 : s + 1;
		}
	}
}

int main()
{
	system("mode con lines=27 cols=52");
	system("title 2048");
	system("color f0");
	srand(time(0));
	while (1)
	{
		welc();
		s ? help() : play();
	}
}