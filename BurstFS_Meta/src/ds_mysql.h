/*
 *
 * Copyright (c) 2014, Los Alamos National Laboratory
 *	All rights reserved.
 *
 */

#include <my_global.h>
#include <mysql.h>
#include "mdhim.h"
#include "data_store.h"

//Struct for MYSQL Handling
//MDI = Mysql Database Info
//Too lazy to Edit name 
struct MDI {
	MYSQL *msqdb; //Database connection 
	int msqht; //Handle's specfication, whether it's the original or stat
	int msqkt;
	char *host;
	char *user;
	char *pswd;
	char *table;
	char *database;
};

int mdhim_mysql_open(void **dbh, void **dbs, char *path, int flags, int key_type, struct mdhim_options_t *opts);
int mdhim_mysql_put(void *dbh, void *key, int key_len, void *data, int32_t data_len);
int mdhim_mysql_get(void *dbh, void *key, int key_len, void **data, int32_t *data_len);
int mdhim_mysql_get_next(void *dbh, void **key, int *key_len, 
			   void **data, int32_t *data_len);
int mdhim_mysql_get_prev(void *dbh, void **key, int *key_len, 
			   void **data, int32_t *data_len);
int mdhim_mysql_close(void *dbh, void *dbs);
int mdhim_mysql_del(void *dbh, void *key, int key_len);
int mdhim_mysql_commit(void *dbh);
int mdhim_mysql_batch_put(void *dbh, void **key, int32_t *key_lens, 
			    void **data, int32_t *data_lens, int num_record);
