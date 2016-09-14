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
#include <vector>
#include <pthread.h>

using namespace std;

void factorizeByTrialDivision(void* _nn) {
	char* nn = (char*) _nn;
	mpz_t nt;
	mpz_init(nt);
	mpz_set_str(nt, nn, 10);
	mpz_t ct;
	mpz_init(ct);
	mpz_set_si(ct, 0);
	mpz_t st;
	mpz_init(st);
	mpz_sqrt(st, nt);
	mpz_set(ct, st);
	mpz_t rt;
	mpz_init(rt);
	while ( mpz_cmp_si(ct, 1) > 0) {
		mpz_mod(rt, nt, ct);
		if (mpz_cmp_si(rt, 0)==0) {
			cout << "\nFactor1:\t"<< strdup(mpz_get_str(0,10,ct))<<"\n";
			exit(0);
		}
		mpz_sub_ui(ct, ct, 1);
	}
	return;
}

void factorizeByTrialMultiplication(void* _nn)  {
	char* nn = (char*) _nn;
	mpz_t nt;
	mpz_init(nt);
	mpz_set_str(nt, nn, 10);
	mpz_t st;
	mpz_init(st);
	mpz_mul(st, nt, nt);
	mpz_t ct;
	mpz_init(ct);
	mpz_set(ct, nt);
	mpz_add_ui(ct,ct, 1);
	mpz_t rt;
	mpz_init(rt);
	mpz_t sqt;
	mpz_init(sqt);
	mpz_t term;
	mpz_init(term);
	mpz_t term2;
	mpz_init(term2);
	while (1) {
		mpz_mul(term, ct,ct);
		mpz_sub(rt, term, st);
		mpz_sqrt(sqt, rt);
		mpz_set(term2, sqt);
		mpz_mul(sqt, sqt, sqt);
		mpz_sub(sqt, rt, sqt);
		mpz_abs(sqt, sqt);
		if (mpz_cmp_si(sqt, 0)==0) {
			mpz_sub(ct, ct, nt);
			mpz_sub(term2, term2, nt);
			gmp_printf("\n%Zd\t%Zd\n", ct, term2);
			mpz_add(ct, ct, term2);
			cout << "\nFactor2:\t"<< strdup((char*) mpz_get_str(0,10, ct))<<"\n";
			exit(0);
		}
		mpz_add_ui(ct,ct, 1);
	}
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

	int l = strlen(nn);

	pthread_t thread1, thread2;
	pthread_create(&thread1, NULL, (void*(*)(void*) ) &factorizeByTrialDivision,  nn);
	pthread_create(&thread2, NULL, (void*(*)(void*) ) &factorizeByTrialMultiplication, nn);
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	fclose(fp);
	free(nn);
	return 0;
}

