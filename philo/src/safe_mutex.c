/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_mutex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 19:06:18 by maximemarti       #+#    #+#             */
/*   Updated: 2025/05/28 11:24:42 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	handle_mutex_error(int status, t_opcode opcode)
{
	if (status == 0)
		return ;
	if (EINVAL == status && (LOCK == opcode || UNLOCK == opcode))
		print_error("the value specified by mutex is invalid");
	else if (EINVAL == status && INIT == opcode)
		print_error("the value specified by attre is invalid");
	else if (EDEADLK == status)
		print_error("a deadlock would occur if the thread \
			bloacked waiting for mutex");
	else if (EPERM == status)
		print_error("the current thread does not hold a lock on mutex");
	else if (ENOMEM == status)
		print_error("the process cannot allocate enough memory \
			to create another mutex");
	else if (EBUSY == status)
		print_error("Mutex is locked");
}

void	safe_mutex_handle(t_mtx *mutex, t_opcode opcode)
{
	if (LOCK == opcode)
		handle_mutex_error(pthread_mutex_lock(mutex), opcode);
	else if (UNLOCK == opcode)
		handle_mutex_error(pthread_mutex_unlock(mutex), opcode);
	else if (INIT == opcode)
		handle_mutex_error(pthread_mutex_init(mutex, NULL), opcode);
	else if (DESTROY == opcode)
		handle_mutex_error(pthread_mutex_destroy(mutex), opcode);
	else
		print_error("wrong opcode for mutex handle");
}
