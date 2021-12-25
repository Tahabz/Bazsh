char arr_length(char **arr)
{
	int i;

	i = 0;

	while (arr[i++])
		;
	return (i);
}