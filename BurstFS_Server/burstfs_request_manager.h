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

#ifndef BURSTFS_REQUEST_MANAGER_H
#define BURSTFS_REQUEST_MANAGER_H
#include "burstfs_const.h"
#include "burstfs_global.h"
#include "arraylist.h"

typedef struct {
	int src_fid;
	long offset;
	long length;
}shm_meta_t; /*metadata format in the shared memory*/

int rm_delegate_request(cli_signature_t *my_sig);
int rm_read_remote_data(int sock_id, int num);
int rm_send_remote_requests(thrd_ctrl_t *thrd_ctrl,\
		int thrd_tag, long *tot_sz);
int rm_pack_send_requests(char *req_msg_buf,\
		send_msg_t *send_metas, int req_num,\
	 long *tot_sz);

int compare_delegators(void *a, void *b);
int rm_pack_send_msg(int rank, char *send_msg_buf,\
		send_msg_t *send_metas, int meta_num,\
	 long *tot_sz);
int rm_receive_remote_message(int app_id,\
		int sock_id, long tot_sz);
void print_recv_msg(int app_id,\
		int cli_id, int dbg_rank, int thrd_id, shm_meta_t *msg);
int rm_process_received_msg(int app_id, int sock_id,\
		char *recv_msg_buf, long *ptr_tot_sz);
void print_remote_del_reqs(int app_id, int cli_id, \
		int dbg_rank, del_req_stat_t *del_req_stat);
void print_send_msgs(send_msg_t *send_metas,\
		long msg_cnt, int dbg_rank);
#endif
