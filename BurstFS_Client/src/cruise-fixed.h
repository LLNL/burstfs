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

#ifndef CRUISE_FIXED_H
#define CRUISE_FIXED_H

#include "cruise-internal.h"

/* if length is greater than reserved space,
 * reserve space up to length */
int cruise_fid_store_fixed_extend(
  int fid,                 /* file id to reserve space for */
  cruise_filemeta_t* meta, /* meta data for file */
  off_t length             /* number of bytes to reserve for file */
);

/* if length is shorter than reserved space,
 * give back space down to length */
int cruise_fid_store_fixed_shrink(
  int fid,                 /* file id to free space for */
  cruise_filemeta_t* meta, /* meta data for file */
  off_t length             /* number of bytes to reserve for file */
);

/* read data from file stored as fixed-size chunks,
 * returns CRUISE error code */
int cruise_fid_store_fixed_read(
  int fid,                 /* file id to read from */
  cruise_filemeta_t* meta, /* meta data for file */
  off_t pos,               /* position within file to read from */
  void* buf,               /* user buffer to store data in */
  size_t count             /* number of bytes to read */
);

/* write data to file stored as fixed-size chunks,
 * returns CRUISE error code */
int cruise_fid_store_fixed_write(
  int fid,                 /* file id to write to */
  cruise_filemeta_t* meta, /* meta data for file */
  off_t pos,               /* position within file to write to */
  const void* buf,         /* user buffer holding data */
  size_t count             /* number of bytes to write */
);

#endif /* CRUISE_FIXED_H */
