#include <ctime>
#include <cstdio>
#include <cstring>
#include <conio.h>
#include <tchar.h>
#include <windows.h>

bool done;
float cx, cy, x0, y0;
int s = 1, ls, lv0, lv;
char a[28][12], b[4][2], b0[4][2], n, n0, sp;
const HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
const unsigned char c[8] = { 240,135,59,42,110,93,25,76 };

void dprint(char dchar[])
{
	CONSOLE_SCREEN_BUFFER_INFO i;
	GetConsoleScreenBufferInfo(h, &i);
	printf("%s", dchar);
	SetConsoleCursorPosition(h, { i.dwCursorPosition.X + 2, i.dwCursorPosition.Y });
}

void p(char x, char y, char z)
{
	if (x < 4) return;
	SetConsoleTextAttribute(h, c[z]);
	SetConsoleCursorPosition(h, { y * 2 + 1,x - 2 });
	if (z) printf("��");else printf("  ");
}

void add()
{
	char max = 0;
	const char block[7][4][2] =
	{
		{ { 0,5 },{ 1,5 },{ 2,5 },{ 3,5 } },
		{ { 1,5 },{ 2,5 },{ 3,4 },{ 3,5 } },
		{ { 1,5 },{ 2,5 },{ 3,5 },{ 3,6 } },
		{ { 2,5 },{ 2,6 },{ 3,5 },{ 3,6 } },
		{ { 2,5 },{ 2,6 },{ 3,4 },{ 3,5 } },
		{ { 2,4 },{ 2,5 },{ 2,6 },{ 3,5 } },
		{ { 2,4 },{ 2,5 },{ 3,5 },{ 3,6 } }
	};
	if (x0) for (char k = 0; k < 4; ++k) p(b0[k][0] + 4, b0[k][1] + 11, 0);
	memcpy(b0, block[n0 = rand() % 7], 8);
	if (!n0)			{ x0 = 1.5; y0 = 5.5; }
	else if (n0 == 3)	{ x0 = 2.5; y0 = 5.5; }
	else				{ x0 = 2.0; y0 = 5.0; }
	for (char i = rand() % 4; i; --i)
		for (char j = 0; j < 4; ++j)
		{
			char t = b0[j][0];
			b0[j][0] = b0[j][1] + x0 - y0;
			b0[j][1] = x0 + y0 - t;
			if (i == 1 && b0[j][0] > max) max = b0[j][0];
		}
	if (max) max -= 3;
	x0 -= max;
	++n0;
	for (char k = 0; k < 4; ++k) p((b0[k][0] -= max) + 4, b0[k][1] + 11, n0);
}

void rev()
{
	char t[4][2];
	for (char k = 0; k < 4; ++k)
	{
		t[k][0] = b[k][1] + cx - cy;
		t[k][1] = cx + cy - b[k][0];
		if (a[t[k][0]][t[k][1]]) return;
	}
	for (char k = 0; k < 4; ++k) p(b[k][0], b[k][1], 0);
	memcpy(b, t, sizeof(t));
	for (char k = 0; k < 4; ++k) p(b[k][0], b[k][1], n);
}

void face()
{
	char k = 9;
	for (; k <= 13; ++k) { SetConsoleCursorPosition(h, { 28,k }); printf("%10c", 0); }
	if (cx < 9) k = -1;
	else if (cx > 16) k = 1;
	else k = 0;
	if (!sp || sp == 4 || sp == -3) SetConsoleCursorPosition(h, { 28,10 });
	else SetConsoleCursorPosition(h, { 28,10 + k });
	switch (sp)
	{
	case 0:printf(" "); dprint("��"); dprint("��"); printf("  "); dprint("��"); printf("��"); break;
	case 3:printf("��%6c��", 0); break;
	case 4:printf(" ��%6c��", 0); break;
	case -3:printf(" �w%6c�w", 0); break;
	default:printf("��%6c��", 0);
	}
	if (!sp || sp == 4 || sp == -3) SetConsoleCursorPosition(h, { 32,12 });
	else SetConsoleCursorPosition(h, { 32,12 + k });
	switch (sp)
	{
	case 0:printf(" ��"); break;
	case 1:printf("��"); break;
	case 4:printf(" ��"); break;
	case -1:printf("��"); break;
	case -2:printf("�n"); break;
	case -3:printf(" �n"); break;
	default:printf("��");
	}
	if (!sp) { SetConsoleCursorPosition(h, { 33,9 }); printf("��"); }
}

void move(char x, char y)
{
	char t[4][2];
	if (x) done = 1;
	for (char k = 0; k < 4; ++k)
	{
		t[k][0] = b[k][0] + x;
		t[k][1] = b[k][1] + y;
		if (a[t[k][0]][t[k][1]]) return;
	}
	done = 0;
	cx += x; cy += y;
	for (char k = 0; k < 4; ++k) p(b[k][0], b[k][1], 0);
	memcpy(b, t, sizeof(t));
	for (char k = 0; k < 4; ++k) p(b[k][0], b[k][1], n);
	if (x && sp && sp != -3 && sp != 4 && (cx < 5 || int(cx) == 9 || cx == 16.5 || cx == 17))
	{
		SetConsoleTextAttribute(h, c[0]);
		face();
	}
}

bool over()
{
	char i = 26, k = 0, m, prev;
	for (; i >= 0; --i)
	{
		m = 0;
		for (char j = 10; j; --j) if (a[i][j]) ++m;
		if (!m || m == 10)
		{
			if (k)
				for (char i0 = prev - 1; i0 > i; --i0)
					for (char j0 = 10; j0; --j0)
						p(i0 + k, j0, a[i0 + k][j0] = a[i0][j0]);
			if (!m)
			{
				for (char i0 = i + k; i0 > i; --i0)
					for (char j0 = 10; j0; --j0)
						p(i0, j0, a[i0][j0] = 0);
				break;
			}
			prev = i;
			++k;
		}
	}
	SetConsoleTextAttribute(h, c[0]);
	if (k) { SetConsoleCursorPosition(h, { 45,17 }); printf("%d", ls += k); }
	SetConsoleCursorPosition(h, { 34,0 }); printf("%10d", s += (lv + 1)*k*k * 10 + 4);
	if ((lv0 + 2)*(lv0 + 1) * 2 <= ls && lv0 < 11 && ++lv0 > lv) { SetConsoleCursorPosition(h, { 45,16 }); printf("%d", lv = lv0); }
	if (sp > 0) --sp;
	if ((prev = i + k + !m) < 6) sp = -3;
	else if (prev < 9) sp = -2;
	else if (prev < 12) sp = -1;
	if (k&&k > sp) sp = k;
	face();
	if (i + k + !m < 4)
	{
		MessageBox(GetConsoleWindow(), _T("���µĴ�����ۻ�����õĳɹ�����ʧ��:)"), _T("��Ϸ����"), 0);
		return 1;
	}
	return 0;
}

void init()
{
	s = ls = lv0 = lv = sp = 0;
	memset(a, 0, sizeof(a));
	char buf[26*52],tmp[52],p=0;
	SetConsoleCursorPosition(h, { 2,0 });
	const unsigned char e[21] = "�T�T�T�T�T�T�T�T�T�T";
	for (char k = 26; k; --k) a[k][0] = a[k][11] = a[27][k % 11] = 1;
	sprintf_s(buf, "ʱ��: 00:00%31d :�ɼ�\n �X%s�j�T%s�T�[\n �U%20c�U%24c�U\n �U%20c�U%24c�U\n �U%20c�U%24c�U\n �U%20c�U%24c�U\n �U%20c�U�t�֩թ������֩ըs%6c�U\n �U%20c�U�����ߩ��������ߩ�%6c�U\n �U%20c�U������������������%6c�U\n �U%20c�U��%6c��%6c��%6c�U\n �U%20c�U��  �ש�  ����  ��%6c�U\n �U%20c�U��%14c��%6c�U\n �U%20c�U��%6c��%6c��%6c�U\n �U%20c�U��%14c��%6c�U\n �U%20c�U������%6c�ש���%6c�U\n �U%20c�U%4c��%6c��%10c�U\n �U%20c�U%4c��%6c���ȼ�: 0   �U\n �U%20c�U%4c��%6c������: 0   �U\n �U%20c�U%4c��%6c��%10c�U\n �U%20c�U%4c��%6c����������  �U\n �U%20c�U%4c��%14c�ǩ��U\n �U%20c�U%4c��%14c�ǩ��U\n �U%20c�U%4c���ש������ש�����  �U\n �U%20c�U%6c���ϩ�  ���ϩ�%4c�U\n �U%20c�U%6c���ߩ�  ���ߩ�%4c�U\n �^%s�m�T%s�T�a", 0, e, e, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, e, e);
	for (short k = 0; k < 26 * 52; k++)
	{
		if (buf[k] > 0) tmp[p++] = buf[k];
		if (!buf[k]) tmp[p++] = 32;
		if (buf[k] < 0)
		{
			tmp[p] = 0;
			printf("%s", tmp);
			tmp[0] = buf[k];
			tmp[1] = buf[++k];
			tmp[2] = p = 0;
			dprint(tmp);
		}
	}
	add();
}

void play()
{
	init();
	clock_t ct = clock();
	time_t t0 = time(0), t = 0;
	while (1)
	{
		memcpy(b, b0, sizeof(b0));
		cx = x0; cy = y0; n = n0;
		done = 0;
		add();
		while (1)
		{
			if (t != time(0))
			{
				SetConsoleTextAttribute(h, c[0]);
				SetConsoleCursorPosition(h, { 8,0 });
				printf("%02d:%02d", ((t = time(0)) - t0) / 60, (time(0) - t0) % 60);
			}
			if (_kbhit()) switch (_getch())
			{
			case 72:rev(); break;
			case 80:move(1, 0); break;
			case 75:move(0,-1); break;
			case 77:move(0, 1); break;
			case 32:
				SetConsoleTextAttribute(h, c[0]);
				SetConsoleCursorPosition(h, { 45,16 });
				printf("%d ", lv < 11 ? ++lv : lv = lv0);
				break;
			case 27:
				t = time(0);
				switch (MessageBox(GetConsoleWindow(), _T("�������ֹ�����˳���Ϸ\n��������ԡ������¿�ʼ\n��������ԡ���������Ϸ"), _T("��ͣ��"), 2))
				{
				case 3:exit(0);
				case 4:SetConsoleTextAttribute(h, c[0]); init(); t0 = time(0); n = 0; break;
				default:t0 += time(0) - t;
				}
			}
			if (clock() - ct > 500 - lv * 40)
			{
				move(1, 0);
				ct = clock();
			}
			if (done || !n)
			{
				for (char k = 0; k < 4; ++k) a[b[k][0]][b[k][1]] = n;
				if (over()) return;
				break;
			}
			Sleep(1);
		}
	}
}

void help()
{
	SetConsoleCursorPosition(h, { 1,1 }); dprint("��"); for (s = 23; s; s--) dprint("��"); SetConsoleTextAttribute(h, 207); printf("��\n");
	SetConsoleTextAttribute(h, c[0]); printf(" "); for (s = 23; s; s--) { dprint("��"); printf("%46c��\n ", 0); }
	dprint("��"); for (s = 23; s; s--) dprint("��"); printf("��");
	SetConsoleCursorPosition(h, { 5,4 }); printf("�� �����������������Ʒ��������ƶ�����������");
	SetConsoleCursorPosition(h, { 8,6 }); printf("ʹ֮˳ʱ����ת�����������������䣻");
	SetConsoleCursorPosition(h, { 5,9 }); printf("�� ����Ϸ�����У����԰���ESC������ͣ��Ϸ��");
	SetConsoleCursorPosition(h, { 5,12 }); printf("�� ��Ϸ�����󣬵���Ի����ȷ����������ҳ��");
	SetConsoleCursorPosition(h, { 5,15 }); printf("�� �����������������ƶ���꣬��ѡ��ѡ���");
	SetConsoleCursorPosition(h, { 8,17 }); printf("�Ұ��¡�ENTER���س�������ȷ�ϣ�");
	SetConsoleCursorPosition(h, { 5,20 }); printf("�� ����ͷ����һ���飬�����鳬������Ϸ������");
	SetConsoleCursorPosition(h, { 26,24 }); printf("Presented by zhujun.xin");
	SetConsoleCursorPosition(h, { 51,1 }); while (_getch() != 13);
}

void welc()
{
	const unsigned char m[7] = "������";
	system("cls"); SetConsoleCursorPosition(h, { 7,7 });
	printf("%s %s %s %s �� %s\n%9c��   ��%7c��   ��  �� �� ��\n%9c��   ����%5c��   %s �� %s\n%9c��   ��%7c��   �� ��  ��%5c��\n%9c��   %s   ��   ��  �� �� %s\n\n\n\n%20c����ʼ��Ϸ��\n\n%20c����Ϸ������\n\n%20c���˳���Ϸ��", m, m, m, m, m, 0, 0, 0, 0, m, m, 0, 0, 0, 0, m, m, 0, 0, 0);
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
	SetConsoleTitleW(_T("����˹����"));
	system("color f0");
	srand(time(0));
	while (1)
	{
		welc();
		s ? help() : play();
	}
}