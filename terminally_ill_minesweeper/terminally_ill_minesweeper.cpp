#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>
#include "Header_sweeper.h"


void main()
{
start:
	system("cls");
	TILE** table;
	int n, x, y, i, mnum, life = 1;
	printf("Terminally ill Minesweeper\nPress any key to start...");
	_getch();

	printf("\nTable size: ");
	scanf("%d", &n);
	printf("Number of mines: ");
	scanf("%d", &mnum);
	
	system("cls");
	table = generate(n, mnum);
	while (life == 1 && (winning_condition(table, n) != mnum))
	{
		write(table, n, &x, &y);
		selection(table, n, x, y);
		if (table[x][y].mine == 1 && table[x][y].state == 1)
		{
			life = 0;
			game_loss(table, n);
		}	
	}
	if (winning_condition(table, n) == mnum)
	{
		write(table, n, &x, &y);
		printf("\nEasy win");
	}

	for (i = 0; i < n; i++)
		free(table[i]);
	free(table);
	printf("\nNew game?(y/n)");
	switch (_getch())
	{
	case 'y':
		goto start;
		break;
	}
}