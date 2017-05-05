 /*
 * Copyright (c) 2017, Lawrence Livermore National Security, LLC.
 * Produced at the Lawrence Livermore National Laboratory.
 * Copyright (c) 2017, Florida State University. Contributions from
 * the Computer Architecture and Systems Research Laboratory (CASTL)
 * at the Department of Computer Science.
 * Written by
 * 	Teng Wang tw15g@my.fsu.edu
 * 	Adam Moody moody20@llnl.gov
 * 	Weikuan Yu wyu3@fsu.edu
 * 	Kento Sato kento@llnl.gov
 * 	Kathryn Mohror. kathryn@llnl.gov
 * 	LLNL-CODE-728877.
 * All rights reserved.
 *
 * This file is part of BurstFS For details, see https://github.com/llnl/burstfs.
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#include <poll.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include "burstfs_global.h"
#include "burstfs_sock.h"
#include "arraylist.h"
#include "burstfs_setup.h"
#include "burstfs_const.h"

int server_sockfd;
int num_fds = 0;

int thrd_pipe_fd[2] = {0};

struct pollfd poll_set[MAX_NUM_CLIENTS];
struct sockaddr_un server_address;
char cmd_buf[MAX_NUM_CLIENTS][GEN_STR_LEN];
char ack_buf[MAX_NUM_CLIENTS][GEN_STR_LEN];
int ack_msg[3] = {0};
int detached_sock_id = -1;
int cur_sock_id = -1;

/**
* initialize the listening socket on this delegator
* @return success/error code
*/
int sock_init_server(int local_rank_idx) {
	int rc;

    char tmp_str[GEN_STR_LEN];

    sprintf(tmp_str, "%s%d", DEF_SOCK_PATH, local_rank_idx);
	server_sockfd = socket(AF_UNIX, SOCK_STREAM, 0);

    memset(&server_address, 0, sizeof(server_address));
    server_address.sun_family = AF_UNIX;
    strcpy(server_address.sun_path, tmp_str);
    int server_len = sizeof(server_address);
	unlink(tmp_str);

    rc = bind(server_sockfd, (struct sockaddr *)&server_address,\
    		(socklen_t)server_len);
    if (rc != 0)
    	return -1;

    rc = listen(server_sockfd, MAX_NUM_CLIENTS);
    if (rc != 0)
    	return -1;

	int flag = fcntl(server_sockfd, F_GETFL);
    fcntl(server_sockfd, F_SETFL, flag|O_NONBLOCK);
    poll_set[0].fd = server_sockfd; //add
    poll_set[0].events = POLLIN|POLLHUP;
    poll_set[0].revents = 0;
    num_fds++;

    return 0;


}

int sock_add(int fd) {
	if (num_fds == MAX_NUM_CLIENTS)
		return -1;
	int flag = fcntl(fd, F_GETFL);
    fcntl(fd, F_SETFL, flag|O_NONBLOCK);
	poll_set[num_fds].fd = fd;
	poll_set[num_fds].events = POLLIN|POLLHUP;
	poll_set[num_fds].revents = 0;
	num_fds++;
	return 0;
}

void sock_reset() {
	int i;

	for (i = 0; i < num_fds; i++) {
		poll_set[i].events = POLLIN|POLLPRI;
		poll_set[i].revents = 0;
	}
}

int sock_remove(int idx) {
	/* in this case, we simply disable the disconnected
	 * file descriptor. */
	poll_set[idx].fd = -1;
	return 0;
}

/*
 * send command to the client to let the client digest the
 * data in the shared receive buffer
 * @param: sock_id: socket index in poll_set
 * @param: cmd: command type
 *
 * */
int sock_notify_cli(int sock_id, int cmd) {
	memcpy(ack_buf[sock_id], &cmd, sizeof(int));
	int rc = write(poll_set[sock_id].fd,\
		 ack_buf[sock_id], sizeof(ack_buf[sock_id]));

	if (rc < 0)
		return ULFS_ERROR_WRITE;
	return ULFS_SUCCESS;
}


/*
 * wait for the client-side command
 * */

int sock_wait_cli_cmd() {
	int rc, i;

	sock_reset();
	rc = poll(poll_set, num_fds, -1);
	if (rc <= 0) {
		return ULFS_ERROR_TIMEOUT;
	}
	else {
			for (i = 0; i < num_fds; i++) {
				if (poll_set[i].fd != -1 && poll_set[i].revents != 0) {
					if (i == 0 && poll_set[i].revents == POLLIN) {
	                    int client_len = sizeof(struct sockaddr_un);

	                    struct sockaddr_un client_address;
	                    int client_sockfd = accept(server_sockfd, \
	                    		(struct sockaddr *)&client_address,\
									(socklen_t *)&client_len);
	                    rc = sock_add(client_sockfd);
	                    if (rc < 0) {
	                    	return ULFS_SOCKETFD_EXCEED;
	                    } else {
	                    	cur_sock_id = i;
	                    	return ULFS_SUCCESS;
	                    }
					} else
						if(i != 0 && poll_set[i].revents == POLLIN) {
							int bytes_read = read(poll_set[i].fd,\
									cmd_buf[i], GEN_STR_LEN);
							if (bytes_read == 0) {
								sock_remove(i);
								detached_sock_id = i;
								return ULFS_SOCK_DISCONNECT;
							}
							cur_sock_id = i;
							return ULFS_SUCCESS;
						} else {
							if (i == 0) {
								return ULFS_SOCK_LISTEN;
							} else {
								detached_sock_id = i;
								if (i != 0 && poll_set[i].revents == POLLHUP) {
									sock_remove(i);
									return ULFS_SOCK_DISCONNECT;
								} else {
									sock_remove(i);
									return ULFS_SOCK_OTHER;

								}
							}
						}
					}
				}
	}

	return ULFS_SUCCESS;

}

int sock_ack_cli(int sock_id, int ret_sz) {
	int rc = write(poll_set[sock_id].fd,\
		 ack_buf[sock_id], ret_sz);
	if (rc < 0)
		return ULFS_SOCK_OTHER;
	return ULFS_SUCCESS;
}

int sock_handle_error(int sock_error_no) {
	return ULFS_SUCCESS;
}

int sock_get_error_id() {
	return detached_sock_id;
}

char *sock_get_cmd_buf(int sock_id) {
	return cmd_buf[sock_id];
}

char *sock_get_ack_buf(int sock_id) {
	return (char *)ack_buf[sock_id];
}

int sock_get_id() {
	return cur_sock_id;
}

int sock_sanitize() {
	int i;
	for (i = 0; i < num_fds; i++) {
		if (poll_set[i].fd > 0)
			close(poll_set[i].fd);
	}

    char tmp_str[GEN_STR_LEN] = {0};
    sprintf(tmp_str, "%s%d", DEF_SOCK_PATH, local_rank_idx);
    unlink(tmp_str);
    return 0;
}
