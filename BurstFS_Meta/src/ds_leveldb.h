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

#ifndef      __LEVELDB_H
#define      __LEVELDB_H

#ifndef      LEVELDB_SUPPORT
#include <rocksdb/c.h>
#else
#include <leveldb/c.h>
#endif

#include "mdhim.h"
#include "partitioner.h"
#include "data_store.h"

#define BURSTFS_FID(key) *(long *)key
#define BURSTFS_OFFSET(key) *((long *)key + 1)
#define BURSTFS_ADDR(val) *((long *)val + 2)
#define BURSTFS_LEN(val) *((long *)val + 1)

/* Function pointer for comparator in C */
typedef int (*mdhim_store_cmp_fn_t)(void* arg, const char* a, size_t alen,
				    const char* b, size_t blen);

struct mdhim_leveldb_t {
	leveldb_t *db;
	leveldb_options_t *options;
	leveldb_comparator_t* cmp;
	leveldb_filterpolicy_t *filter;
	leveldb_cache_t *cache;
	leveldb_env_t *env;
	leveldb_writeoptions_t *write_options;
	leveldb_readoptions_t *read_options;
	mdhim_store_cmp_fn_t compare;
};
int mdhim_leveldb_open(void **dbh, void **dbs, char *path, int flags, int key_type, struct mdhim_options_t	*opts);
int mdhim_leveldb_put(void *dbh, void *key, int key_len, void *data, int32_t data_len);
int mdhim_leveldb_get(void *dbh, void *key, int key_len, void **data, int32_t *data_len);
int mdhim_leveldb_get_next(void *dbh, void **key, int *key_len, 
			   void **data, int32_t *data_len);
int mdhim_leveldb_get_prev(void *dbh, void **key, int *key_len, 
			   void **data, int32_t *data_len);
int mdhim_leveldb_close(void *dbh, void *dbs);
int mdhim_leveldb_del(void *dbh, void *key, int key_len);
int mdhim_leveldb_commit(void *dbh);
int mdhim_leveldb_batch_put(void *dbh, void **key, int32_t *key_lens, 
			    void **data, int32_t *data_lens, int num_records);
int mdhim_levedb_batch_next(void *dbh, char **key,\
		int *key_len, char **data, int32_t *data_len, \
			int tot_records, int *num_records);
int levedb_batch_ranges(void *dbh, char **key, int *key_len,\
		char ***out_key, int **out_key_len,\
			char ***out_val, int **out_val_len,\
				int tot_records, int *out_records_cnt);
int leveldb_process_range(leveldb_iterator_t *iter,\
		char *start_key, char *end_key, \
			int key_len, char ***out_key, int **out_key_len, \
				char ***out_val, int **out_val_len, int *tmp_records_cnt, \
					int *tmp_out_cap);
int handle_next_half(leveldb_iterator_t *iter,\
		char *start_key, char *end_key, \
			char ***out_key, int **out_key_len, \
				char ***out_val, int **out_val_len, int *tmp_records_cnt, \
					int *tmp_out_cap);
int add_kv(char ***out_key, int **out_key_len, char ***out_val,\
		int **out_val_len, int *tmp_records_cnt, int *tmp_out_cap, \
			char *ret_key, char *ret_val, int key_len, int val_len);
#endif
