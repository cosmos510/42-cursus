#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>

int extract_message(char **buf, char **msg)
{
	char	*newbuf;
	int	i;

	*msg = 0;
	if (*buf == 0)
		return (0);
	i = 0;
	while ((*buf)[i])
	{
		if ((*buf)[i] == '\n')
		{
			newbuf = calloc(1, sizeof(*newbuf) * (strlen(*buf + i + 1) + 1));
			if (newbuf == 0)
				return (-1);
			strcpy(newbuf, *buf + i + 1);
			*msg = *buf;
			(*msg)[i + 1] = 0;
			*buf = newbuf;
			return (1);
		}
		i++;
	}
	return (0);
}

char *str_join(char *buf, char *add)
{
	char	*newbuf;
	int		len;

	if (buf == 0)
		len = 0;
	else
		len = strlen(buf);
	newbuf = malloc(sizeof(*newbuf) * (len + strlen(add) + 1));
	if (newbuf == 0)
		return (0);
	newbuf[0] = 0;
	if (buf != 0)
		strcat(newbuf, buf);
	free(buf);
	strcat(newbuf, add);
	return (newbuf);
}

int client_id[65536], max_fd, client_count;
char *client_buf[65536], tmp_msg[99], recv_buf[4096];
fd_set read_set, write_set, all_clients;

void fatal(char *s) { write(2, s, strlen(s)); exit(1); }

void broadcast(int sender_fd, char *msg)
{
	for (int i = 0; i <= max_fd; i++)
		if (FD_ISSET(i, &write_set) && i != sender_fd)
			send(i, msg, strlen(msg), 0);
}

int main(int ac, char **av)
{
	int client_fd, server_fd, addr_len;
	struct sockaddr_in server_addr, client_addr;

	if (ac != 2) fatal("Wrong number of arguments\n");
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) fatal("Fatal error\n");
	bzero(&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(2130706433);
	server_addr.sin_port = htons(atoi(av[1]));
	if (bind(server_fd, (void *)&server_addr, sizeof(server_addr))) fatal("Fatal error\n");
	if (listen(server_fd, 128)) fatal("Fatal error\n");
	FD_ZERO(&all_clients); FD_SET(server_fd, &all_clients);
	max_fd = server_fd;

	while (1)
	{
		read_set = write_set = all_clients;
		if (select(max_fd + 1, &read_set, &write_set, 0, 0) < 0) fatal("Fatal error\n");
		for (int i = 0; i <= max_fd; i++)
		{
			if (!FD_ISSET(i, &read_set)) continue;
			if (i == server_fd)
			{
				addr_len = sizeof(client_addr);
				if ((client_fd = accept(server_fd, (void *)&client_addr, (socklen_t *)&addr_len)) < 0) continue;
				if (client_fd > max_fd) max_fd = client_fd;
				client_id[client_fd] = client_count++;
				FD_SET(client_fd, &all_clients);
				client_buf[client_fd] = 0;
				sprintf(tmp_msg, "server: client %d just arrived\n", client_id[client_fd]);
				broadcast(client_fd, tmp_msg);
			}
			else
			{
				int bytes = recv(i, recv_buf, 4000, 0);
				if (bytes <= 0)
				{
					sprintf(tmp_msg, "server: client %d just left\n", client_id[i]);
					FD_CLR(i, &all_clients);
					broadcast(i, tmp_msg);
					free(client_buf[i]);
					close(i);
					client_buf[i] = 0;
				}
				else
				{
					recv_buf[bytes] = 0;
					client_buf[i] = str_join(client_buf[i], recv_buf);
					char *msg;
					while (extract_message(&client_buf[i], &msg))
					{
						sprintf(tmp_msg, "client %d: ", client_id[i]);
						broadcast(i, tmp_msg);
						broadcast(i, msg);
						free(msg);
					}
				}
			}
		}
	}
}
