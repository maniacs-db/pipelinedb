/*
 * Miscellaneous utilities
 *
 * Copyright (c) 2013-2016, PipelineDB
 *
 * src/include/pipeline/pipelineutils.h
 */
#ifndef PIPELINEUTILS_H
#define PIPELINEUTILS_H

#include "postgres.h"

#include "access/htup_details.h"
#include "catalog/pg_type.h"
#include "executor/tuptable.h"
#include "miscadmin.h"
#include "lib/stringinfo.h"
#include "storage/dsm.h"
#include "utils/typcache.h"

extern double continuous_query_proc_priority;

#define ptr_difference(begin, end) ((void *) (((char *) end) - ((char *) begin)))
#define ptr_offset(begin, offset) ((void *) (((char *) begin) + ((uintptr_t) offset)))

/* strings related */
extern void append_suffix(char *str, char *suffix, int max_len);
extern int skip_token(const char *str, char* substr, int start);
extern char *random_hex(int len);

/* hash functions */
extern void MurmurHash3_128(const void *key, const Size len, const uint64_t seed, void *out);
extern uint64_t MurmurHash3_64(const void *key, const Size len, const uint64_t seed);
extern void SlotAttrsToBytes(TupleTableSlot *slot, int num_attrs, AttrNumber *attrs, StringInfo buf);
extern void DatumToBytes(Datum d, TypeCacheEntry *typ, StringInfo buf);

/* for backends / bg workers to yield cpu */
extern int SetNicePriority(void);
extern int SetDefaultPriority(void);

/* fast in-memory logging */
#define DLOG_SIZE 8192 /* 8k */

typedef struct dlog_t
{
	uint64 head;
	uint64 tail;
	char buf[DLOG_SIZE];
	char scratch[DLOG_SIZE];
} dlog_t;

extern dlog_t my_dlog;

extern void dlog_init(void);
extern void dlog(const char *format, ...) pg_attribute_printf(1, 0);
extern void dlog_dump(void);

#endif   /* PIPELINEUTILS_H */
