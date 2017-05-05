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
 * Copyright (c) 2013, Lawrence Livermore National Security, LLC.
 * Produced at the Lawrence Livermore National Laboratory.
 * code Written by
 *   Raghunath Rajachandrasekar <rajachan@cse.ohio-state.edu>
 *   Kathryn Mohror <kathryn@llnl.gov>
 *   Adam Moody <moody20@llnl.gov>
 * All rights reserved.
 * This file is part of CRUISE.
 * For details, see https://github.com/hpc/cruise
 * Please also read this file COPYRIGHT
*/

#ifndef CRUISE_SYSIO_H
#define CRUISE_SYSIO_H

#include "cruise-internal.h"

/* read count bytes info buf from file starting at offset pos,
 * returns number of bytes actually read in retcount,
 * retcount will be less than count only if an error occurs
 * or end of file is reached */
int cruise_fd_read(int fd, off_t pos, void* buf, size_t count, size_t* retcount);

/* write count bytes from buf into file starting at offset pos,
 * allocates new bytes and updates file size as necessary,
 * fills any gaps with zeros */
int cruise_fd_write(int fd, off_t pos, const void* buf, size_t count);
int cruise_fd_logreadlist(read_req_t *read_req, int count);
int compare_read_req(const void *a, const void *b);
int compare_index_entry(const void *a, const void *b);

#endif /* CRUISE_SYSIO_H */
