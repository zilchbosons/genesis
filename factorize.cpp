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

void generate(char* nn) {
	std::string str= "";
	str = "out.txt";
	FILE* fout = fopen(str.c_str(), "w");
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
	while (mpfr_cmp_si(nt, 1)  > 0)  {
		mpfr_log2(logt, nt, MPFR_RNDN);
		mpfr_trunc(logt, logt);
		mpfr_get_z(tmp, logt, MPFR_RNDN);
		char* logval = mpz_get_str(0, 10, tmp);
		fprintf(fout, "%s\n", logval);
		mpfr_ui_pow(term, 2, logt, MPFR_RNDN);
		mpfr_sub(nt, nt, term, MPFR_RNDN);
		++idx;
	}
	fclose(fout);
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

	generate(nn);
	fclose(fp);
	free(nn);
	return 0;
}

