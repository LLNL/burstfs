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

#include "arraylist.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

arraylist_t * arraylist_create() {
	arraylist_t *arr = (arraylist_t *)malloc(sizeof(arraylist_t));
	if (!arr)
		return NULL;

	arr->cap = DEF_ARR_CAP;
	arr->size = 0;
	arr->elems = (void **)malloc(arr->cap * sizeof(void *));

	if (!arr->elems)
		return NULL;

	int i;
	for (i = 0; i < arr->cap; i++) {
		arr->elems[i] = NULL;
	}

	return arr;
}

int arraylist_capacity(arraylist_t *arr) {
	return arr->cap;
}

int arraylist_size(arraylist_t *arr) {
	return arr->size;
}

void * arraylist_get(arraylist_t *arr, int pos) {
	if (pos >= arr->size)
		return NULL;
	return arr->elems[pos];
};

int arraylist_insert(arraylist_t *arr, int pos, void *elem) {
	if (pos >= arr->cap){
		arr->elems = (void **)realloc(arr->elems, \
				2 * pos * sizeof(void *));
		if (!arr->elems)
			return -1;

		long i;
		for (i = arr->cap; i < 2 * pos; i++) {
			arr->elems[i] = NULL;
		}
		arr->cap = 2 * pos;
	}

	if (arr->elems[pos] != NULL)
		free(arr->elems[pos]);
	arr->elems[pos] = elem;
	arr->size = pos + 1;
	return 0;

}


int arraylist_add(arraylist_t *arr, void *elem) {
	if (arr->size == arr->cap){
		arr->elems = (void **)realloc(arr->elems, 2 * arr->cap * sizeof(void *));
		if (!arr->elems)
			return -1;

		long i;
		for (i = arr->cap; i < 2 * arr->cap; i++) {
			arr->elems[i] = NULL;
		}
		arr->cap = arr->cap * 2;
	}

	if (arr->elems[arr->size] != NULL) {
		free(arr->elems[arr->size]);
	}
	arr->elems[arr->size] = elem;
	arr->size = arr->size + 1;
	return 0;

}

int arraylist_reset(arraylist_t *arr) {
	if (!arr)
		return -1;

	arr->size = 0;
	return 0;
}

int arraylist_free(arraylist_t *arr) {
	long i;
	for (i = 0; i < arr->cap; i++) {
		if (arr->elems[i] != NULL)
			free(arr->elems[i]);
	}

	free(arr);
	return 0;
}
