#include <stdio.h>
#include <unistd.h>
#include<stdlib.h>


int main(int argc, char **argv)
{
	if (argc != 4)
		return 1;
	int W = atoi(argv[1]);
	int H = atoi(argv[2]);
	int iter = atoi(argv[3]);
	if (W<= 0|| H<= 0|| iter <0)
		return 1;
	
	if ((size_t)W*H / H!= (size_t)W)
		return 1;
	char *board = calloc((size_t) W*H, 1);
	if (!board)
		return 1;
	
	char c;
	int px = 0, py=0, pen = 0;
	while (read(0, &c, 1) > 0)
	{
		if (c =='w' && py>0) py--;
		else if(c =='s' && py< H -1)py++;
		else if (c == 'a' && px >0)px--;
		else if(c == 'd' && px <W-1)px++;
		else if(c == 'x') { pen^=1; if(pen) board[py * W + px] = 1;continue;}
		if (pen) board[py * W + px] = 1;
	}

	for (int i = 0; i<iter; i++)
	{
		char *next = calloc((size_t)W*H, 1);
		if (!next){free(board); return 1;}
		for (int y = 0; y < H; y++)
			for (int x = 0; x <W; x++)
			{
				int n = 0;
				for(int dy = -1; dy <= 1;dy++)
					for (int dx = -1;dx<= 1;dx++)
						if(( dx || dy) && x+dx >= 0 && x+dx <W && y+dy >= 0 && y+dy <H)
							n+= board[(y+dy) *W +(x+dx)];
				if ((board[y*W + x] && n == 2) || n ==3)
					next[y *W +x] = 1;
			}
		free(board);
		board = next;
	}
	for (int y = 0; y<H; y++)
	{
		for(int x = 0; x <W; x++)
			putchar(board[y*W +x] ? 'O' :' ');
		putchar('\n');
	}
	free(board);
	return 0;

}