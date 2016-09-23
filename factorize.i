%module factorize

%{

  char* _Factor(char* nn);
  bool isPrime(char* nn);
%}
extern char* _Factor(char* nn);
extern bool isPrime(char* nn);
