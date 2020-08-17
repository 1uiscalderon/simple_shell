#include "shell.h"

int token_counter(char *str, char *delim) /*APROBADO*/
{
	int i, j;
	int str_delim = 0, flag = 0, count = 0;
	for (i = 0; str[i]; i++)
	{
		for (j = 0; delim[j]; j++)
		{
			if (str[i] == delim[j])
			{
				str_delim = 1;
				flag = 0;
				break;
			}
			str_delim = 0;
		}
		if (str_delim == 0 && flag == 0)
		{
			flag = 1;
			count++;
		}
	}
	return (count);
}

char **strtok_arr(char *str, char *delim)
{
	char *copy = NULL, **token_array = NULL;
	int i = 0, j = 0, k = 0, len = 0, count = 0, str_delim = 0, copy_delim = 0;

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
		for (k = 0; delim[k]; k++)
		{
			if (*str == delim[k])
			{
				str_delim = 1;
				break;
			}
			str_delim = 0;
		}
		if (str_delim == 1)
			str++;
		else
		{
			copy = str;
			while (str_delim == 0 && *str)
			{
				for (k = 0; delim[k]; k++)
				{
					if (*str == delim[k])
					{
						str_delim = 1;
						break;
					}
					str_delim = 0;
				}
				len++;
				str++;
			}
			token_array[i] = malloc(sizeof(char) * (len + 1));
			if (!token_array[i])
				return (NULL);
			while (*copy && *copy != '\n')
			{
				for (k = 0; delim[k]; k++)
				{
					if (*copy == delim[k])
					{
						copy_delim = 1;
						break;
					}
					copy_delim = 0;
				}
				if (copy_delim == 0)
					token_array[i][j] = *copy, copy++, j++;
				else
					break;
			}
			token_array[i][j] = '\0', i++, j = 0, len = 0;
		}
	}
	token_array[i] = NULL;
	return (token_array);
}
