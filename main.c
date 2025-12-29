#include <unistd.h>
void	write_int(int n)
{
	char	c;

	c = n + '0';
	write(1, &c, 1);
}

int	visibility(int arr[4])
{
	int	max;
	int	count;
	int	i;

	max = arr[0];
	count = 1;
	i = 1;
	while (i < 4)
	{
		if (arr[i] > max)
		{
			max = arr[i];
			count++;
		}
		i++;
	}
	return (count);
}

int	visibility_rev(int arr[4])
{
	int	max;
	int	count;
	int	i;

	max = arr[3];
	count = 1;
	i = 2;
	while (i >= 0)
	{
		if (arr[i] > max)
		{
			max = arr[i];
			count++;
		}
		i--;
	}
	return (count);
}

int grid[4][4];

int perms[24][4] = {
    {1,2,3,4},{1,2,4,3},{1,3,2,4},{1,3,4,2},{1,4,2,3},{1,4,3,2},
    {2,1,3,4},{2,1,4,3},{2,3,1,4},{2,3,4,1},{2,4,1,3},{2,4,3,1},
    {3,1,2,4},{3,1,4,2},{3,2,1,4},{3,2,4,1},{3,4,1,2},{3,4,2,1},
    {4,1,2,3},{4,1,3,2},{4,2,1,3},{4,2,3,1},{4,3,1,2},{4,3,2,1}
};

int top[4], bottom[4], left[4], right[4];


int	check_column_unique(int row_index)
{
	int	col;
	int	used[5];
	int	row;

	col = 0;
	while (col < 4)
	{
		used[0] = 0;
		used[1] = 0;
		used[2] = 0;
		used[3] = 0;
		used[4] = 0;
		row = 0;
		while (row <= row_index)
		{
			if (used[grid[row][col]])
				return (0);
			used[grid[row][col]] = 1;
			row++;
		}
		col++;
	}
	return (1);
}

int	check_column_visibility(void)
{
	int	col;
	int	col_arr[4];

	col = 0;
	while (col < 4)
	{
		col_arr[0] = grid[0][col];
		col_arr[1] = grid[1][col];
		col_arr[2] = grid[2][col];
		col_arr[3] = grid[3][col];
		if (visibility(col_arr) != top[col])
			return (0);
		if (visibility_rev(col_arr) != bottom[col])
			return (0);
		col++;
	}
	return (1);
}

int	solve(int row)
{
	int	p;
	int	i;

	if (row == 4)
	{
		return (check_column_visibility());
	}
	p = 0;
	while (p < 24)
	{
		i = 0;
		while (i < 4)
		{
			grid[row][i] = perms[p][i];
			i++;	
		}
		if (left[row] != 0 && visibility(grid[row]) != left[row])
		{
			p++;
			continue;
		}
		if (right[row] != 0 && visibility_rev(grid[row]) != right[row])
		{
			p++;
			continue;
		}
		if (!check_column_unique(row))
		{
			p++;
			continue;
		}
		if (solve(row + 1))
			return (1);
		p++;
	}
	return (0);
}

int fill_from_string(char *str)
{
    int values[16];
    int i = 0;

    while (*str)
    {
        if (*str >= '1' && *str <= '4')
        {
            if (i >= 16)
                return (0); 
            values[i++] = *str - '0';
        }
        str++;
    }
    if (i != 16)
        return (0); 

    top[0]    = values[0];
    top[1]    = values[1];
    top[2]    = values[2];
    top[3]    = values[3];

    bottom[0] = values[4];
    bottom[1] = values[5];
    bottom[2] = values[6];
    bottom[3] = values[7];

    left[0]   = values[8];
    left[1]   = values[9];
    left[2]   = values[10];
    left[3]   = values[11];

    right[0]  = values[12];
    right[1]  = values[13];
    right[2]  = values[14];
    right[3]  = values[15];

    return (1);
}


int	main(int argc, char **argv) 
{
	int	row;
	int	col;

	
    if (!fill_from_string(argv[1]))
    {
        write(1, "Error\n", 6);
        return (1);
    }
    
	if (solve(0))
	{
		row = 0;
		while (row < 4)
		{
			col = 0;
			while (col < 4)
			{
				write_int(grid[row][col]);
				if (col != 3) write(1, " ", 1);
				col++;
			}
			write(1, "\n", 1);
			row++;
		}
	}
	else
	{
		write(1, "No solution!\n", 13);
	}
	return (0);
}