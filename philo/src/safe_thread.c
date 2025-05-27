/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 19:08:06 by maximemarti       #+#    #+#             */
/*   Updated: 2025/05/27 19:19:14 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	handle_thread_error(int status, t_opcode opcode)
{
	if (status == 0)
		return ;
	else if (EAGAIN == status)
		print_error("No ressources to create another thread");
	else if ((EPERM == status))
		print_error("The caller does not have appropriate permission");
	else if (EINVAL == status && CREATE == opcode)
		print_error("The value specified by attr is invalid");
	else if (EINVAL == status && (JOIN == opcode || DETACH == opcode))
		print_error("The value specified by thread is not joinable");
	else if (ESRCH == status)
		print_error("No thread could be found corresponding to that\
			specified by the given thread ID");
	else if (EDEADLK == status)
		print_error("A deadlock was detected or the value of \
			thread specifies the calling thread");
}

void	safe_thread_handle(pthread_t *thread, void *(*foo)(void *), void *data, \
		t_opcode opcode)
{
	if (CREATE == opcode)
		handle_thread_error(pthread_create(thread, NULL, foo, data), opcode);
	else if (JOIN == opcode)
		handle_mutex_error(pthread_join(*thread, NULL), opcode);
	else if (DETACH == opcode)
		handle_mutex_error(pthread_detach(*thread), opcode);
	else
		print_error("Wrong opcode for thread_handle");
}
