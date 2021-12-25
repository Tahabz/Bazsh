#include "executor.h"

bool keys_cmp(char *str, char *key)
{
	char **key_value;
	char * str_key;
	int    is_matching;
	key_value = ft_split(str, '=');
	str_key = key_value[0];
	is_matching = str_match(key, str_key);
	free_double_pointer(key_value);
	return (is_matching);
}

void waitpids(int pids[], size_t i)
{
	if (!*pids)
		return;
	while (i--)
	{
		int pid = waitpid(pids[i], &code, 0);
		if (pid == -1)
			perror("wait() error");
		else if (pid == 0)
		{
			printf("child is still running at");
		}
	}
}