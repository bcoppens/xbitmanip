#include <stdio.h>
#include "../cproofs/common.h"
using namespace rv32b;

int main()
{
	FILE *f;

	f = fopen("testdata_clz.hex", "w");
	for (int i = 0; i < 1000; i++) {
		uint32_t din = xorshift32();
		uint32_t dout = clz(din);
		fprintf(f, "%08x%08x\n", din, dout);
	}
	fclose(f);

	f = fopen("testdata_ctz.hex", "w");
	for (int i = 0; i < 1000; i++) {
		uint32_t din = xorshift32();
		uint32_t dout = ctz(din);
		fprintf(f, "%08x%08x\n", din, dout);
	}
	fclose(f);

	f = fopen("testdata_pcnt.hex", "w");
	for (int i = 0; i < 1000; i++) {
		uint32_t din = xorshift32();
		uint32_t dout = pcnt(din);
		fprintf(f, "%08x%08x\n", din, dout);
	}
	fclose(f);

	f = fopen("testdata_grev.hex", "w");
	for (int i = 0; i < 1000; i++) {
		uint32_t din = xorshift32();
		uint32_t shamt = xorshift32() & 31;
		uint32_t dout = grev32(din, shamt);
		fprintf(f, "%08x%02x%08x\n", din, shamt, dout);
	}
	fclose(f);

	f = fopen("testdata_gzip.hex", "w");
	for (int i = 0; i < 1000; i++) {
		uint32_t din = xorshift32();
		uint32_t mode = xorshift32() & 31;
		while (1) {
			bool mode_inv = mode & 1;
			uint32_t mode_upper = mode >> 1;
			if (pcnt(mode_upper) == 1 && mode_inv) {
				mode = xorshift32() & 31;
				continue;
			}
			if (clz(mode_upper) + pcnt(mode_upper) + ctz(mode_upper) != 32) {
				mode = xorshift32() & 31;
				continue;
			}
			break;
		}
		uint32_t dout = ((mode & 1) ? unshfl : shfl)(din, mode >> 1);
		fprintf(f, "%08x%02x%08x\n", din, mode, dout);
	}
	fclose(f);

	f = fopen("testdata_bfxp.hex", "w");
	for (int i = 0; i < 1000; i++) {
		uint32_t din1 = xorshift32();
		uint32_t din2 = xorshift32();
		uint32_t start = xorshift32() & 31;
		uint32_t len = xorshift32() & 31;
		uint32_t dest = xorshift32() & 31;
		if (len == 0 || start+len > 32 || dest+len > 32) {
			i--; continue;
		}
		uint32_t dout = bfxp(din1, din2, start, len, dest);
		fprintf(f, "%08x%08x%02x%02x%02x%08x\n", din1, din2, start, len, dest, dout);
	}
	fclose(f);

	f = fopen("testdata_bfxpc.hex", "w");
	for (int i = 0; i < 1000; i++) {
		uint32_t din1 = xorshift32();
		uint32_t din2 = xorshift32();
		uint32_t start = xorshift32() & 31;
		uint32_t len = xorshift32() & 31;
		uint32_t dest = xorshift32() & 31;
		if (len == 0 || start+len > 32 || dest+len > 32) {
			i--; continue;
		}
		uint32_t dout = bfxpc(din1, din2, start, len, dest);
		fprintf(f, "%08x%08x%02x%02x%02x%08x\n", din1, din2, start, len, dest, dout);
	}
	fclose(f);

	f = fopen("testdata_bext.hex", "w");
	for (int i = 0; i < 1000; i++) {
		uint32_t din1 = xorshift32();
		uint32_t din2 = xorshift32();
		uint32_t dout = bext(din1, din2);
		fprintf(f, "%08x%08x%08x\n", din1, din2, dout);
	}
	fclose(f);

	f = fopen("testdata_bdep.hex", "w");
	for (int i = 0; i < 1000; i++) {
		uint32_t din1 = xorshift32();
		uint32_t din2 = xorshift32();
		uint32_t dout = bdep(din1, din2);
		fprintf(f, "%08x%08x%08x\n", din1, din2, dout);
	}
	fclose(f);

	f = fopen("testdata_clmul.hex", "w");
	for (int i = 0; i < 1000; i++) {
		uint64_t din1 = xorshift32();
		uint64_t din2 = xorshift32();
		bool op_mul = xorshift32() & 1;
		uint64_t dout = op_mul ? din1 * din2 : ((uint64_t)clmulh(din1, din2) << 32) | clmul(din1, din2);
		fprintf(f, "%1x%08llx%08llx%016llx\n", op_mul, (long long)din1, (long long)din2, (long long)dout);
	}
	fclose(f);

	f = fopen("testdata_bmat.hex", "w");
	for (int i = 0; i < 1000; i++) {
		uint64_t din1 = xorshift64();
		uint64_t din2 = xorshift64();
		bool op_xor = xorshift32() & 1;
		uint64_t dout = op_xor ? rv64b::bmatxor(din1, din2) : rv64b::bmator(din1, din2);
		fprintf(f, "%1x%016llx%016llx%016llx\n", op_xor, (long long)din1, (long long)din2, (long long)dout);
	}
	fclose(f);

	return 0;
}
