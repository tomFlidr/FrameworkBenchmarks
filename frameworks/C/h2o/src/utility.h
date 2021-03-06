/*
 Copyright (c) 2016 Anton Valentinov Kirilov

 Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
 associated documentation files (the "Software"), to deal in the Software without restriction,
 including without limitation the rights to use, copy, modify, merge, publish, distribute,
 sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all copies or
 substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
 NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT
 OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef UTILITY_H_

#define UTILITY_H_

#include <h2o.h>
#include <stdint.h>
#include <openssl/ssl.h>
#include <stdbool.h>
#include <yajl/yajl_gen.h>
#include <mustache.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(*(a)))
// mainly used to silence compiler warnings about unused function parameters
#define IGNORE_FUNCTION_PARAMETER(p) ((void) (p))
#define MIN(x, y) ((x) < (y) ? (x) : (y))
#define MKSTR(x) TOSTRING(x)
#define TOSTRING(x) # x
#define YAJL_STRLIT(s) (const unsigned char *) (s), sizeof(s) - 1

typedef struct global_thread_data_t global_thread_data_t;

typedef struct {
	const char *bind_address;
	const char *cert;
	const char *db_host;
	const char *key;
	const char *log;
	const char *root;
	const char *template_path;
	size_t max_accept;
	size_t max_db_conn_num;
	size_t max_query_num;
	size_t thread_num;
	uint16_t port;
} config_t;

typedef struct {
	h2o_logger_t *file_logger;
	mustache_template_t *fortunes_template;
	h2o_socket_t *signals;
	SSL_CTX *ssl_ctx;
	global_thread_data_t *global_thread_data;
	size_t memory_alignment;
	int listener_sd;
	int signal_fd;
	bool shutdown;
	h2o_globalconf_t h2o_config;
} global_data_t;

// Call yajl_gen_free() on the result, even though the JSON generator
// uses a memory pool; in this way the code remains correct if the
// underlying memory allocator is changed (e.g. for debugging purposes).
yajl_gen get_json_generator(h2o_mem_pool_t *pool);

uint32_t get_random_number(uint32_t max_rand, unsigned int *seed);

#endif // UTILITY_H_
