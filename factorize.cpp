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
int sequence[4] = {1, 3, 1, 2};


void print(vector<int> _passage) {
	for (int i = 0; i < _passage.size(); ++i ) {
		cout << _passage[i]<<"\t,\t";
	}
	cout << "\n";
}

void print(vector<char*> passage) {
	for (int i = 0; i < passage.size(); ++i ) {
		cout << passage[i]<<"\t,\t";
	}
	cout << "\n";
}

bool _isFit(int off, int sum) {
	unsigned long long int acc = 0;
	int index1 = off, index2 = off;
	while (acc < sum) {
		int term= (e[index1]-'0');
		acc+=term;
		++index1;++index2;
	}
	if (acc == sum) { 
		return true;
	} else {
		return false;
	}
}

bool isFit(int off, int sum) {
	unsigned long long int acc = 0;
	int index1 = off, index2 = off;
	while (acc < sum) {
		int term= (pi[index1]-'0');
		acc+=term;
		++index1;++index2;
	}
	if (acc == sum) { 
		return true;
	} else {
		return false;
	}
}

char* _isPrime(char* nn) {
	for (int i = 0; i<30; ++i) {
		bool fits = isFit(i,atoi(nn));
		if (fits) {
			cout <<"\n"<<i<<"\tFit.\n";
		} else {
			cout <<"\n"<<i<<"\tNot Fit.\n";
		}
		bool _fits = _isFit(i,atoi(nn));
		if (_fits) {
			cout <<"\n"<<i<<"\t_Fit.\n";
		} else {
			cout <<"\n"<<i<<"\t_Not Fit.\n";
		}
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
	char* is_prime = _isPrime(nn);
	if (is_prime) {
		cout <<"\nRoot:\t"<<is_prime<<"\n";
	} else {
		cout << "\nNumber \t"<<nn<<"\t is prime.\n";
	}
	fclose(fp);
	free(nn);
	return 0;
}
//#endif
