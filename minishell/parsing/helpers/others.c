#include "../../minishell.h"

char	*handle_escape(char *line, t_data *data)
{
	char *sub;

	data->i++;
	sub = ft_substr(line, data->i, 1);
	return (sub);
}

char	*unquoted_str(char *line, int *i)
{
	char	*substr;
	int		j;

	j = 0;
	while ((line[*i + j] != ';' && line[*i + j] != '|' &&
			line[*i + j] != '>' && line[*i + j] != '<' && line[*i + j] &&
			line[*i + j] != ' ' && line[*i + j] != '"' &&
			line[*i + j] != '\'') || line[*i + j - 1] == '\\')
		j++;
	substr = ft_substr(line, *i, j);
	*i += j;
	return (substr);
}

char	*get_str(char *line, int *i)
{
	char	*substr;
	char	*str;

	str = ft_calloc(1, 1);
	while (line[*i] != ';' && line[*i] != '|' &&
			line[*i] != '>' && line[*i] != '<' &&
			line[*i] != ' ' && line[*i])
	{
		if (line[*i] == '"')
			substr = dquoted_str(line, i);
		else if (line[*i] == '\'')
			substr = squoted_str(line, i);
		else
			substr = unquoted_str(line, i);
		str = ft_strjoin(str, substr);
	}
	return (str);
}
