/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qabdel-r <qabdel-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 12:00:00 by qabdel-r          #+#    #+#             */
/*   Updated: 2026/03/10 17:29:24 by qabdel-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <stdio.h>

static int	update_pwd(t_shell *sh, const char *oldpwd)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		return (1);
	if (oldpwd != NULL)
		ms_env_set(&sh->env, "OLDPWD", oldpwd, 1);
	ms_env_set(&sh->env, "PWD", cwd, 1);
	free(cwd);
	return (0);
}

static char	*get_cd_target(t_shell *sh, char **argv)
{
	if (argv[1] == NULL)
		return (ms_env_get(sh->env, "HOME"));
	return (argv[1]);
}

static int	do_chdir(const char *target, char *oldpwd)
{
	if (chdir(target) != 0)
	{
		perror("minishell: cd");
		free(oldpwd);
		return (1);
	}
	return (0);
}

int	ms_builtin_cd(t_shell *sh, char **argv)
{
	char	*target;
	char	*oldpwd;

	if (sh == NULL)
		return (1);
	oldpwd = getcwd(NULL, 0);
	target = get_cd_target(sh, argv);
	if (target == NULL)
	{
		ms_putendl_fd("minishell: cd: HOME not set", 2);
		free(oldpwd);
		return (1);
	}
	if (do_chdir(target, oldpwd) != 0)
		return (1);
	update_pwd(sh, oldpwd);
	free(oldpwd);
	return (0);
}
