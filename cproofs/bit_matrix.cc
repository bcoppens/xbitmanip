/*
 *  Copyright (C) 2018  Clifford Wolf <clifford@clifford.at>
 *
 *  Permission to use, copy, modify, and/or distribute this software for any
 *  purpose with or without fee is hereby granted, provided that the above
 *  copyright notice and this permission notice appear in all copies.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 *  WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 *  MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 *  ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 *  WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 *  ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 *  OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 */

#include "common.h"
using namespace rv64b;

// ---------------------------------------------------------

void identity_check(uint64_t src)
{
	uint64_t p = 0x8040201008040201LL;
	uint64_t a = bmatxor(src, p);
	uint64_t b = bmatxor(p, src);
	uint64_t c = bmator(src, p);
	uint64_t d = bmator(p, src);

	assert(a == src);
	assert(b == src);
	assert(c == src);
	assert(d == src);
}

void bswap_check(uint64_t src)
{
	uint64_t p = 0x0102040810204080LL;
	uint64_t a = bmatxor(p, src);
	uint64_t b = bmator(p, src);
	uint64_t c = grev(src, 56);

	assert(a == c);
	assert(b == c);
}

void brevb_check(uint64_t src)
{
	uint64_t p = 0x0102040810204080LL;
	uint64_t a = bmatxor(src, p);
	uint64_t b = bmator(src, p);
	uint64_t c = grev(src, 7);

	assert(a == c);
	assert(b == c);
}

// ---------------------------------------------------------
