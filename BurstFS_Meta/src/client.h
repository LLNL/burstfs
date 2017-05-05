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
 *
 * Copyright (c) 2014, Los Alamos National Laboratory
 *	All rights reserved.
 *
 */

/*
 * MDHIM TNG
 * 
 * Client specific implementation
 */

#ifndef      __CLIENT_H
#define      __CLIENT_H

#include "messages.h"

struct mdhim_rm_t *client_put(struct mdhim_t *md, struct mdhim_putm_t *pm);
struct mdhim_brm_t *client_bput(struct mdhim_t *md, struct index_t *index, 
				struct mdhim_bputm_t **bpm_list);
struct mdhim_bgetrm_t *client_bget(struct mdhim_t *md, struct index_t *index, 
				   struct mdhim_bgetm_t **bgm_list);
struct mdhim_bgetrm_t *client_bget_op(struct mdhim_t *md, struct mdhim_getm_t *gm);
struct mdhim_rm_t *client_delete(struct mdhim_t *md, struct mdhim_delm_t *dm);
struct mdhim_brm_t *client_bdelete(struct mdhim_t *md, struct index_t *index, 
				   struct mdhim_bdelm_t **bdm_list);

#endif
