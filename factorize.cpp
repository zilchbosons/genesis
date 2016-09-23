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

#define PREC 4096
#define GODS_CONSTANT 7 //69384


using namespace std;
#define SZ 5
#define LS 4
//int golden_sequence[LS] = { 3, 1, 4, 1, 5 };
//int golden_sequence[LS] = { 2, 3, 1, 2, 1 };
int sequence[LS] = { 1, 3, 1, 2 };
int limit[SZ] = {6,9,3,8,4};
int baseT[SZ] = {312, 231, 132, 321, 213 };
double  logT[SZ] = {0.69384, 0.93846, 0.38469, 0.84693, 0.46938};

char* transformSlope(char* s, mpfr_exp_t* expt) {
	if (strlen(s)==6 && strstr("Inf", s)) {
		return 0;
	}
	char f = s[0];
	if (f == '-') {
		++s;
	}
	char* tr = new char[strlen(s)+2];
	int idx = 0;
	if (f == '-') {
		tr[idx++] = '-';
	}
	int i = idx;
	for (i = idx; i < *expt+idx; ++i) {
		tr[i] = s[i-idx];
	}
	tr[i++] = '.';
	for (int j = i-1; j < strlen(s); ++j) {
		tr[i++]=s[j];
	}
	tr[i] = '\0';
	return tr;
}

char* rotate(char* tSlope, int index, int l) {
	char f1 = tSlope[0];
	char* ts = 0;
	char* ts_frac = new char[3];
	ts_frac[0] = '.';
#ifdef _DEBUG
	cout <<"\nTslope:\t"<<tSlope<<"\n";
#endif
	char* result = 0;
	if (f1 == '.') {
		ts = new char[l+2];
		strncpy(ts, tSlope+1, l+1); 
		ts[l+1] = '\0';
		std::string tst = ts;
		std::rotate(tst.begin(), tst.begin()+index, tst.end()); 
		ts = strdup((char*)tst.c_str());
		char* ts2 = new char[l+1];
		strncpy(ts2, ts, l);
		ts2[l] = '\0';
		ts_frac[1] =ts[l];
		ts_frac[2] ='\0';
#ifdef _DEBUG
		cout <<"\nInteger Part: \t"<<ts2<<"\n";
		cout <<"\nFractional Part: \t"<<ts_frac<<"\n";
#endif
		tst = strdup(ts2);
		tst += ts_frac;
		result = strdup((char*) tst.c_str());
	} else {
		ts_frac[1] = tSlope[0];
		ts_frac[2] = '\0';
		ts = new char[l+1];
		strncpy(ts, tSlope+2, l); 
		ts[l] = '\0';
		char* ts2 = common::reverse_string(ts);
		//delete [] ts;
		std::string tst = strdup(ts2);
		std::rotate(tst.begin(), tst.begin()+(index % l), tst.end()); 
		tst += ts_frac;
		result = strdup((char*) tst.c_str());
	}
	return result;
}

//#define logT 7
void generate(char* nn, double logT, /*FILE* fout,*/ vector<char*>& slopes,  int index) {
	mpfr_t nt;
	mpfr_init2(nt, PREC) ;
	mpfr_t logt;
	mpfr_init2(logt, PREC);
	mpz_t tmp;
	mpz_init(tmp);
	mpfr_t term;
	mpfr_init2(term, PREC);
	mpfr_set_str(nt, nn, 10, MPFR_RNDN);
	unsigned long long int idx = 0;
	int l = strlen(nn);
	mpfr_t special;
	mpfr_init2(special, PREC);
	mpfr_set_d(special, logT, MPFR_RNDN);
	mpfr_t tmp2;
	mpfr_init2(tmp2, PREC);
	mpfr_set(tmp2, special, MPFR_RNDN);
	mpfr_log(special, special, MPFR_RNDN);
	//fprintf(fout, "\n%f\n", logT);
	//fprintf(fout, "\n========================\n");
	bool first = true;
	mpz_t logvalt;
	mpz_init(logvalt);
	mpz_t residuet;
	mpz_init(residuet);
	mpz_t prev_logvalt;
	mpz_init(prev_logvalt);
	mpz_t prev_residuet;
	mpz_init(prev_residuet);
	mpz_t termt;
	mpz_init(termt);
	mpz_t divt;
	mpz_init(divt);
	mpfr_t termtf;
	mpfr_init2(termtf, PREC);
	mpfr_t divtf;
	mpfr_init2(divtf, PREC);
	mpfr_t acctf;
	mpfr_init2(acctf, PREC);
	mpfr_set_si(acctf, 0, MPFR_RNDN);
	while (mpfr_cmp_si(nt, 1)  >= 0)  {
		mpfr_log(logt, nt, MPFR_RNDN);
		mpfr_div(logt, logt, special, MPFR_RNDN);
		mpfr_trunc(logt, logt);
		mpfr_get_z(tmp, logt, MPFR_RNDN);
		mpz_set(logvalt, tmp);
		char* logval = mpz_get_str(0, 10, tmp);
		mpz_mod_ui(tmp, tmp, 7);
		int r1 = mpz_get_ui(tmp);
		mpfr_pow(term, tmp2, logt, MPFR_RNDN);
		mpfr_sub(nt, nt, term, MPFR_RNDN);
		mpfr_get_z(tmp, nt, MPFR_RNDN);
		mpz_set(residuet, tmp);
		char* residue = mpz_get_str(0, 10, tmp);
		mpz_mod_ui(tmp, tmp, 7);
		int r2 = mpz_get_ui(tmp);
		//		fprintf(fout, "%s\t%s\n", logval, residue);
		++idx;
		if (first) {
			first = false;
		} else {
			mpz_sub(termt , prev_logvalt, logvalt);
			mpz_sub(divt, prev_residuet, residuet);
			mpfr_set_z(termtf,termt, MPFR_RNDN);
			mpfr_set_z(divtf, divt, MPFR_RNDN);
			mpfr_div(termtf, termtf, divtf, MPFR_RNDN);
			mpfr_add(acctf, acctf, termtf, MPFR_RNDN);
		}
		mpz_set(prev_logvalt, logvalt);
		mpz_set(prev_residuet, residuet);
	}
	//	fprintf(fout, "\n========================\n");
	//	mpfr_printf("\nSlope :%.2048RNf\n",acctf);
	mpfr_exp_t expt;
	char* acctStr = mpfr_get_str(0, &expt, 10, 0, acctf, MPFR_RNDN);
	char* transformed_slope = transformSlope(acctStr, &expt);
#ifdef _DEBUG
	cout << "\nTransformed Slope: \t"<<transformed_slope<<"\tindex:\t"<<index<<"\n";
#endif
	char* rotated_slope = rotate(transformed_slope, index % 5, l);
#ifdef _DEBUG
	cout << "\nRotated Slope: \t"<<rotated_slope<<"\n";
#endif
	slopes.push_back(rotated_slope);
	mpz_clear(tmp);
	mpfr_clear(term);
	mpfr_clear(nt);
	mpfr_clear(logt);
	mpfr_clear(special);
	mpfr_clear(tmp2);
	mpfr_clear(termtf);
	mpfr_clear(divtf);
	mpfr_clear(acctf);
	mpz_clear(logvalt);
	mpz_clear(residuet);
	mpz_clear(prev_logvalt);
	mpz_clear(prev_residuet);
	mpz_clear(termt);
	mpz_clear(divt);
	return;
}

void print(vector<char*> slopes) {
	for (int i = 0; i < slopes.size(); ++i) {
		cout << slopes.at(i)<<"\t,\t";
	}
	cout <<"\n";
}


char* calculateHarmonicMean(vector<char*> slopes) {
	int sz = slopes.size();
	mpfr_t acc;
	mpfr_init2(acc, PREC);
	mpfr_t term;
	mpfr_init2(term, PREC);
	mpfr_set_si(acc, 0, MPFR_RNDN);
	mpfr_t one;
	mpfr_init(one);
	mpfr_set_ui(one, 1, MPFR_RNDN);
	for (int i = 0; i < sz;++i) {
		mpfr_set_str(term, slopes.at(i), 10, MPFR_RNDN);
		mpfr_div(term, one, term,MPFR_RNDN);
		mpfr_add(acc, acc, term, MPFR_RNDN);
	}
	mpfr_set_ui(one, sz, MPFR_RNDN);
	mpfr_div(term, one, acc, MPFR_RNDN);
	mpfr_printf("\nHarmonic Mean calculated is :%.2RNf\n",term);
	mpfr_sqrt(term, term, MPFR_RNDN);
	mpz_t termt;
	mpz_init(termt);
	mpfr_get_z(termt, term, MPFR_RNDN);
#if 0
	mpfr_exp_t expt;
	char* ts = mpfr_get_str(0, &expt, 10, 0, term, MPFR_RNDN);
	char* tone = transformSlope(ts, &expt);
#endif
	char* tone = strdup(mpz_get_str(0, 10, termt));
	return tone;

}

char* calculateArithmeticMean(vector<char*> hmeans) {
	int sz = hmeans.size();
	mpz_t term;
	mpz_init(term);
	mpz_t acc;
	mpz_init(acc);
	mpz_set_si(acc, 0);
	for (int i =0; i < sz; ++i) {
		mpz_set_str(term, hmeans.at(i), 10);
		mpz_add(acc, acc, term);
	}
	mpz_div_ui(acc, acc, sz);
	return strdup((char*) mpz_get_str(0, 10, acc));

}

char* _Factor(char* nn) {
	//	FILE* fout = fopen("out.txt", "w");
	cout << "\nNumber read was : \t" << nn <<"\n";
	vector<char*> slopes;
	int l = strlen(nn);
	int ek =2, pk =3;
	vector<char*> hmeans;
	for (int j = 0; j < 5; ++j) {
                double base = 1;
		for (int i = 0; i < l; ++i ) {
			pk = pi[(i)*3+(j)*5] - '0';
			ek = e[(i)*3+(j)*5]  -'0';
                        int nk1 = nn[pk % l ] - '0';
                        int nk2 = nn[(9-ek) % l ] - '0';
			base = (nk1/nk2) + (nk2/nk1); 
			double logbase = (base + logT[i % SZ]);
			generate(nn, logbase, /*fout,*/ slopes,  i % SZ );
		}
		cout <<"\nSlopes Recorded are:\t\n";
		print(slopes);
		char* hmean = calculateHarmonicMean(slopes);
		hmeans.push_back(hmean);
		slopes.clear();
	}
	char* ahmean = calculateArithmeticMean(hmeans);
	//	slopes.clear();
	//	fclose(fout);
	cout <<"\nAHMean:\t"<<ahmean<<"\n";
	return ahmean;
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
	cout << "\nNumber read was : \t" << num <<"\n";
	char* nn = strdup((char*) num.c_str());
	char* hmean = _Factor(nn);
	cout <<"\nRoot:\t"<<hmean<<"\n";
	fclose(fp);
	free(nn);
	return 0;
}
//#endif
