#include "shell.h"

int token_counter(char *str, char delim)
{
	int count = 0, i;
	int flag = 0;
	for (i = 0; str[i]; i++)
	{
		if (str[i] == delim)
			flag = 0;
		else if (flag == 0)
		{
			flag = 1;
			count++;
		}
	}
	return (count);
}

char **strtok_arr(char *str, char delim)
{
	char *copy = NULL, **token_array = NULL;
	int i = 0, j = 0, len = 0, count = 0;

	if (str == 0 || *str == 0)
		return (NULL);
	count = token_counter(str, delim);
	if (count == 0)
		return (NULL);
	token_array = malloc((count + 1) * sizeof(char *));
	if (token_array == NULL)
		return (NULL);
	while (*str && i < count)
	{
		if (*str == delim)
			str++;
		else
		{
			copy = str;
			while (*str != delim && *str)
			{
				len++;
				str++;
			}
			token_array[i] = malloc(sizeof(char) * (len + 1));
			if (!token_array[i])
				return (NULL);
			while (*copy != delim && *copy && *copy != '\n')
			{
				token_array[i][j] = *copy;
				copy++;
				j++;
			}
			token_array[i][j] = '\0';
			i++;
			j = 0;
			len = 0;
		}
	}
	token_array[i] = NULL;
	return (token_array);
}
