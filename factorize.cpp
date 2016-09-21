/*********************************************************************************
 * Permission is hereby granted, free of charge, to any person obtaining a copy	 *
 * of this software and associated documentation files (the "Software"), to deal  *
 * in the Software without restriction, including without limitation the rights   *
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell	 *
 * copies of the Software, and to permit persons to whom the Software is		 *
 * furnished to do so, subject to the following conditions:			 *
 * 										 *
 * The above copyright notice and this permission notice shall be included in	 *
 * all copies or substantial portions of the Software.				 *
 * 										 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR	 *
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,	 *
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE	 *
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER	 *
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,  *
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN	 *	
 * THE SOFTWARE.									 *
 **********************************************************************************/

#include <stdio.h>
#include <iostream>
#include <string>
#include <gmp.h>
#include <mpfr.h>
#include <vector>
#include "common.hpp"

using namespace std;
double  logT[5] = {1.69384, 1.93846, 1.38469, 1.84693, 1.46938 };

//#define logT 7
void generate(char* nn, double logT, FILE* fout) {
	mpfr_t nt;
	mpfr_init2(nt, 4096) ;
	mpfr_t logt;
	mpfr_init2(logt, 4096);
	mpz_t tmp;
	mpz_init(tmp);
	mpfr_t term;
	mpfr_init2(term, 4096);
	mpfr_set_str(nt, nn, 10, MPFR_RNDN);
	unsigned long long int idx = 0;
	mpfr_t special;
	mpfr_init2(special, 4096);
	mpfr_set_d(special, logT, MPFR_RNDN);
	mpfr_t tmp2;
	mpfr_init2(tmp2, 4096);
	mpfr_set(tmp2, special, MPFR_RNDN);
	mpfr_log(special, special, MPFR_RNDN);
	fprintf(fout, "\n%f\n", logT);
	fprintf(fout, "\n========================\n");
	while (mpfr_cmp_si(nt, 1)  >= 0)  {
		mpfr_log(logt, nt, MPFR_RNDN);
		mpfr_div(logt, logt, special, MPFR_RNDN);
		mpfr_trunc(logt, logt);
		mpfr_get_z(tmp, logt, MPFR_RNDN);
		char* logval = mpz_get_str(0, 10, tmp);
		mpz_mod_ui(tmp, tmp, 7);
		int r1 = mpz_get_ui(tmp);
		mpfr_pow(term, tmp2, logt, MPFR_RNDN);
		mpfr_sub(nt, nt, term, MPFR_RNDN);
		mpfr_get_z(tmp, nt, MPFR_RNDN);
		char* residue = mpz_get_str(0, 10, tmp);
		mpz_mod_ui(tmp, tmp, 7);
		int r2 = mpz_get_ui(tmp);
		fprintf(fout, "%s\t%d\t%s\t%d\n", logval, r1, residue, r2);
		++idx;
	}
	fprintf(fout, "\n========================\n");
	mpz_clear(tmp);
	mpfr_clear(term);
	mpfr_clear(nt);
	mpfr_clear(logt);
	return;
}

int main() {
	/* Step 1: Reading the Number to be factorized */
	FILE* fp = fopen("./input.txt", "r");
	std::string num = "";
	char n[1024];
	int ret = 0;
	while ((ret=fscanf(fp, "%s", n))!= EOF) {
		num += n;
	}
	cout << "\nNumber read was : \t" << num <<"\n";
	char* nn = strdup((char*) num.c_str());

	FILE* fout = fopen("out.txt", "w");
	for (int i = 0; i < 5 ; ++i) {
		generate(nn, logT[i], fout);
	}
	fclose(fout);
	fclose(fp);
	free(nn);
	return 0;
}

