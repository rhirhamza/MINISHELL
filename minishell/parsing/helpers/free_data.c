/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrhirha <hrhirha@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 09:52:13 by hrhirha           #+#    #+#             */
/*   Updated: 2021/03/01 09:52:14 by hrhirha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_redir(t_list *redirs)
{
	t_list			*tmp;
	t_redirection	redir;

	while (redirs)
	{
		redir = *(t_redirection *)redirs->content;
		free(redir.file_name);
		tmp = redirs->next;
		free(redirs->content);
		free(redirs);
		redirs = tmp;
	}
}

void	free_cmd(t_command *command, t_data *data)
{
	int				j;
	t_list			*tmp_redir;

	(void)data;
	tmp_redir = command->redirections;
	free_redir(tmp_redir);
	if (command->full_args)
	{
		j = 0;
		while (command->full_args[j])
			free(command->full_args[j++]);
		free(command->full_args);
	}
}

void	free_pipes(t_list *pipes, t_data *data)
{
	t_command		command;
	t_list			*tmp;

	while (pipes)
	{
		command = *(t_command *)pipes->content;
		free_cmd(&command, data);
		tmp = pipes->next;
		free(pipes->content);
		free(pipes);
		pipes = tmp;
	}
}

void	free_data(t_data *data)
{
	t_list			*tmp;
	t_list			*tmp_cmds;
	t_list			*tmp_pipes;

	if (!data->command->cmds)
	{
		free(data->cmd);
		free(data->simple_cmd);
	}
	tmp_cmds = data->command->cmds;
	while (tmp_cmds)
	{
		tmp_pipes = tmp_cmds->content;
		free_pipes(tmp_pipes, data);
		tmp = tmp_cmds->next;
		free(tmp_cmds);
		tmp_cmds = tmp;
	}
}
