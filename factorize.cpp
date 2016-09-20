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
	bool first = true;
	mpz_t t_logval;
	mpz_t t_residue;
	mpz_init(t_logval);
	mpz_init(t_residue);
	mpz_t prev_logval;
	mpz_t prev_residue;
	mpz_init(prev_logval);
	mpz_init(prev_residue);
	mpfr_t fr_residue;
	mpfr_init2(fr_residue, 4096);
	mpfr_t log7;
	mpfr_init2(log7, 4096);
	mpfr_set_ui(log7, 7, MPFR_RNDN);
	mpfr_log(log7, log7, MPFR_RNDN);
	mpfr_t acc;
	mpfr_init2(acc, 4096);
	mpfr_set_si(acc, 0, MPFR_RNDN);
	mpz_t _logval;
	mpz_t _residue;
	mpz_init(_logval);
	mpz_init(_residue);
	mpfr_t divisor;
	mpfr_init2(divisor, 4096);
	while (mpfr_cmp_si(nt, 0)  > 0)  {
		mpfr_log2(logt, nt, MPFR_RNDN);
		mpfr_trunc(logt, logt);
		mpfr_get_z(tmp, logt, MPFR_RNDN);
		mpz_set(_logval, tmp);
		char* logval = mpz_get_str(0, 10, tmp);
		mpfr_ui_pow(term, 2, logt, MPFR_RNDN);
		mpfr_sub(nt, nt, term, MPFR_RNDN);
		mpfr_get_z(tmp, nt, MPFR_RNDN);
		mpz_set(_residue, tmp);
		char* residue = mpz_get_str(0, 10, tmp);
		if (first) {
			first = false;
			mpz_set(prev_logval, _logval);
			mpz_set(prev_residue, _residue);
		} else {
			mpz_sub(t_logval, prev_logval, _logval);
			mpz_sub(t_residue, prev_residue, _residue);
			mpfr_set_z(fr_residue, t_residue, MPFR_RNDN);
			mpfr_log(fr_residue, fr_residue, MPFR_RNDN);
			mpfr_div(fr_residue, fr_residue, log7, MPFR_RNDN);
			mpfr_set_z(divisor, t_residue, MPFR_RNDN);
			mpfr_div(fr_residue, fr_residue, divisor,MPFR_RNDN);
			mpfr_add(acc, acc, fr_residue, MPFR_RNDN);
			mpz_set(prev_logval, _logval);
			mpz_set(prev_residue, _residue);
		}
		fprintf(fout, "%s\t%s\n", logval, residue);
		++idx;
	}
	mpz_clear(tmp);
	mpfr_clear(term);
	mpz_clear(prev_residue);
	mpz_clear(prev_logval);
	mpfr_clear(fr_residue);
	mpfr_clear(nt);
	mpz_clear(_residue);
	mpz_clear(_logval);
	mpfr_clear(logt);
	mpfr_clear(acc);
	mpfr_clear(divisor);
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

