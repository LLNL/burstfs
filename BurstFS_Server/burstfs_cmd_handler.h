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

#ifndef BURSTFS_CMD_HANDLER_H
#define BURSTFS_CMD_HANDLER_H
int delegator_handle_command(char *ptr_cmd, int sock_id);
int sync_with_client(char *buf, int client_id);
int open_log_file(app_config_t *app_config,\
		int app_id, int client_id);
int attach_to_shm(app_config_t *app_config,\
		int app_id, int sock_id);
int pack_ack_msg(char *ptr_cmd, int cmd,\
		int rc, void *val,\
		int val_len);
int burstfs_broadcast_exit(int sock_id);
int sync_with_client(char *cmd_buf, int sock_id);
int open_log_file(app_config_t *app_config,\
		int app_id, int sock_id);
int attach_to_shm(app_config_t *app_config,\
		int app_id, int sock_id);
int pack_ack_msg(char *ptr_cmd, int cmd,\
		int rc, void *val, int val_len);
int burstfs_broadcast_exit(int sock_id);
#endif
