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

#include "burstfs_const.h"

const char * ULFS_str_errno(int rc)
{
    switch(rc) {
    	case ULFS_ERROR_DBG:     	return ULFS_STR_ERROR_DBG;
    	case ULFS_ERROR_MDHIM:		return ULFS_STR_ERROR_MDHIM;
    	case ULFS_ERROR_THRD:		return ULFS_STR_ERROR_THRDINIT;
		case ULFS_ERROR_GENERAL:  	return ULFS_STR_ERROR_GENERAL;
		case ULFS_ERROR_NOENV:		return ULFS_STR_ERROR_NOENV;
		case ULFS_ERROR_NOMEM:		return ULFS_STR_ERROR_NOMEM;
		case ULFS_ERROR_TIMEOUT:	return ULFS_STR_ERROR_TIMEOUT;
		case ULFS_ERROR_EXIT:		return ULFS_STR_ERROR_EXIT;
		case ULFS_ERROR_POLL:		return ULFS_STR_ERROR_POLL;
		case ULFS_ERROR_SHMEM:		return ULFS_STR_ERROR_SHMEM;
		case ULFS_ERROR_ROUTE:		return ULFS_STR_ERROR_ROUTE;
		case ULFS_ERROR_EVENT_UNKNOWN: return ULFS_STR_ERROR_EVENT_UNKNOWN;
		case ULFS_ERROR_CONTEXT:	return ULFS_STR_ERROR_CONTEXT;
		case ULFS_ERROR_QP:			return ULFS_STR_ERROR_QP;
		case ULFS_ERROR_REGMEM:		return ULFS_STR_ERROR_REGMEM;
		case ULFS_ERROR_PD:			return ULFS_STR_ERROR_PD;
		case ULFS_ERROR_CHANNEL:	return ULFS_STR_ERROR_CHANNEL;
		case ULFS_ERROR_POSTSEND:	return ULFS_STR_ERROR_POSTSEND ;
		case ULFS_ERROR_ACCEPT:		return ULFS_STR_ERROR_ACCEPT;
		case ULFS_ERROR_POSTRECV:	return  ULFS_STR_ERROR_POSTRECV;
		case ULFS_ERROR_CQ:			return ULFS_STR_ERROR_CQ;
		case ULFS_ERROR_MDINIT:		return ULFS_STR_ERROR_MDINIT;
		case ULFS_ERROR_THRDINIT:	return ULFS_STR_ERROR_THRDINIT;
		case ULFS_ERROR_FILE:		return ULFS_STR_ERROR_FILE;
	//	case ULFS_ERROR_META:		return ULFS_STR_ERROR_META;

		case ULFS_ERROR_SOCKET_FD_EXCEED: return ULFS_STR_ERROR_SOCKET_FD_EXCEED;
		case ULFS_ERROR_SOCK_DISCONNECT: return ULFS_STR_ERROR_SOCK_DISCONNECT;
		case ULFS_ERROR_SOCK_CMD: return ULFS_STR_ERROR_SOCK_CMD;
		case ULFS_ERROR_SOCK_LISTEN: return ULFS_STR_ERROR_SOCK_LISTEN;
		case ULFS_ERROR_APPCONFIG: return ULFS_STR_ERROR_APPCONFIG;
		case ULFS_ERROR_ARRAY_EXCEED: return ULFS_STR_ERROR_ARRAY_EXCEED;
		case ULFS_ERROR_RM_INIT: return ULFS_STR_ERROR_RM_INIT;
		case ULFS_ERROR_READ: return ULFS_STR_ERROR_READ;
		case ULFS_ERROR_SEND: return ULFS_STR_ERROR_SEND;
		case ULFS_ERROR_WRITE: return ULFS_STR_ERROR_WRITE;
		default:                 		return ULFS_STR_ERROR_DEFAULT;

    }
}
