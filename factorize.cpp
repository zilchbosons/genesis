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
#include "pi.hpp"
#include "e.hpp"

using namespace std;
#define OPTLEN 5
#define PREC 4096

int sequence[5] = {-1, 2, 3, 1, -3};

char* factorizeEQ5(char* nn) {
	char* pivot = new char[6];
	pivot[5] = '\0';
	for (int i = 0; i < OPTLEN; ++i) {
		int nk = nn[i] - '0';
		int sk = sequence[i];
		if ((nk + sk)>10) {
			pivot[i] = '0' + ((nk + sk) % 7);
		} else if ((nk+sk)==0) {
			pivot[i] = '0' + 7;
		} else {
			pivot[i] = '0' + (nk + sk);
		}
	}
	mpfr_t pt;
	mpfr_init2(pt, PREC);
	mpfr_set_str(pt, pivot, 10, MPFR_RNDN);
	mpfr_log(pt, pt, MPFR_RNDN);
	mpfr_t cons;
	mpfr_init(cons);
	mpfr_set_ui(cons, 69384, MPFR_RNDN);        
	mpfr_log(cons, cons, MPFR_RNDN);
	mpfr_mul(cons, cons, pt, MPFR_RNDN);
	mpfr_add_ui(cons, cons, 1, MPFR_RNDN);
	mpfr_printf("\n%.2RNf\n",cons);
	return 0;
}

char* factorizeLT5(char* nn) {
}

char* factorizeGT5(char* nn) {
}

bool divisibleBy7(char* nn) {
	mpz_t nt;
	mpz_init(nt);
	mpz_set_str(nt, nn, 10);
	mpz_mod_ui(nt, nt, 7);
	if (mpz_cmp_si(nt, 7)==0) {
		return true;
	} else {
		return false;
	}
}

int fits(int offset, int start, char* nn) {
	int sum = 0;
int cnt = 0;
	for (int i = start; i < strlen(nn); ++i, ++cnt) {
int nk = nn[i]-'0';
if (cnt % 3 == 0) {
    cnt  = 0;
sum %= 7;
}
		sum =sum*10 + (nk);
	}
	long long int acc = 0;
	int index = offset;
	while (acc < sum) {
		int pk = pi[index]-'0';
		acc += pk;
++index;
	}
	if (acc ==sum) {
		cout << "\nsum=\t"<<sum<<"\noffset=\t"<<offset<<"\nend:\t"<<index<<"\n";
return 1;
	}
return 0;

}

//#if 0
int main() {
	/* Step 1: Reading the Number to be factorized */
	FILE* fp = fopen("./input.txt", "r");
	std::string num = "";
	char n[1024];
	int ret = 0;
	while ((ret=fscanf(fp, "%s", n))!= EOF) {
		num += n;
	}
	char* nn = strdup((char*) num.c_str());
	cout <<"\nNumber read was:\t"<<nn<<"\n";
	int l = strlen(nn);
	for (int j = l-1; j >=0; --j) {
		for (int i = 0; i < 10; ++i) {
	int fit =		fits(i, j, nn);
if (fit) break;
		}
	}
	fclose(fp);
	free(nn);
	return 0;
}
//#endif
