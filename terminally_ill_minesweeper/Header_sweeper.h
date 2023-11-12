#pragma once
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

int dirx[] = {-1, 0, 1, 1, 1, 0, -1, -1};
int diry[] = {-1, -1, -1, 0, 1, 1, 1, 0};

typedef struct
{
	char mine; //0-no mine; 1-mine
	char state; // 1-visible 0 no visible 2 flag
	char selection;
	char value; //mine adjacency
}TILE;

bool okm(int x, int y, int n)//valid position to move to
{
	if (x < 0 || x >= n || y < 0 || y >= n)
		return false;
	return true;
}

TILE** generate(int n, int mnum)
{
	int i, j, k, ok;
	TILE** table;
	table = (TILE**)malloc(n * sizeof(TILE*));

	for (i = 0; i < n; i++)
		table[i] = (TILE*)malloc(n * sizeof(TILE));

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			if (i == 0 && j == 0) table[i][j].selection = 1;
			else table[i][j].selection = 0;
			table[i][j].mine = 0;
			table[i][j].state = 0;
			table[i][j].value = 0;
		}
			
	}
	srand(time(0));
	for (k = 0; k < mnum; k++)
	{
		ok = 0;
		while (ok == 0)
		{
			i = rand() % n;
			j = rand() % n;
			if (table[i][j].mine == 0)
			{
				table[i][j].mine = 1;
				ok = 1;
			}
		}
	}

	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			if (table[i][j].mine == 0)
				for (k = 0; k < 8; k++)
					if (okm(i + dirx[k], j + diry[k], n) && (table[i + dirx[k]][j + diry[k]].mine == 1))
						table[i][j].value += 1;
	printf("\nDone\n");
	return table;
}

void write(TILE** table, int n, int* x, int* y)
{
	system("cls");
	int i, j;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			switch (table[i][j].state)
			{
			case 0:
				if (table[i][j].selection == 1)
				{
					printf("[.]");
					*x = i;
					*y = j;
				}
				else
					printf(" . ");
				break;
			case 1:
				if (table[i][j].selection == 1)
				{
					if(table[i][j].mine == 1)printf("[b]");
					else
						printf("[%hhi]", table[i][j].value);
					*x = i;
					*y = j;
				}
				else if (table[i][j].mine == 1)printf(" b ");
				else
					printf(" %hhi ", table[i][j].value);
				break;
			case 2:
				if (table[i][j].selection == 1)
				{
					printf("[f]");
					*x = i;
					*y = j;
				}
				else
					printf(" f ");
				break;
			}
		}
			
		printf("\n");
	}
}

void flood_fill(TILE** table, int n, int x, int y)
{
	int k;
	if (table[x][y].value != 0)
		table[x][y].state = 1;
	else
	{
		if (table[x][y].state == 0)
		{
			table[x][y].state = 1;
			for (k = 0; k < 8; k++)
				if (okm(x + dirx[k], y + diry[k], n))
					flood_fill(table, n, x + dirx[k], y + diry[k]);
			
		}
			
	}
}


void selection(TILE** table, int n, int x, int y)
{
	switch (_getch())
	{
	case KEY_UP:
		if (okm(x - 1, y, n))
		{
			table[x][y].selection = 0;
			table[x - 1][y].selection = 1;
		}
		break;
	case KEY_LEFT:
		if (okm(x, y - 1, n))
		{
			table[x][y].selection = 0;
			table[x][y - 1].selection = 1;
		}
		break;
	case KEY_DOWN:
		if (okm(x + 1, y, n))
		{
			table[x][y].selection = 0;
			table[x + 1][y].selection = 1;
		}
		break;
	case KEY_RIGHT:
		if (okm(x, y + 1, n))
		{
			table[x][y].selection = 0;
			table[x][y + 1].selection = 1;
		}
		break;
	case 's':
		if (table[x][y].state == 0)
			flood_fill(table, n, x, y);
		break;
	case 'f':
		if (table[x][y].state == 0)
			table[x][y].state = 2;
		else if(table[x][y].state == 2)
			table[x][y].state = 0;
		break;
	}
}

int winning_condition(TILE** table, int n)
{
	int i, j, k = 0;
	for(i = 0; i < n; i++)
		for (j = 0; j < n; j++)
		{
			if (table[i][j].state == 2 && table[i][j].mine == 1)
				k++;
		}
	return k;
}

void game_loss(TILE** table, int n)
{
	int i, j;
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			table[i][j].state = 1;
	write(table, n, &i, &j);
	printf("\nIs this loss?");
}
