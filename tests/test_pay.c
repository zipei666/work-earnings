#include <assert.h>
#include <math.h>
#include <stdio.h>
#include "../src/pay.h"
int main(void){
 assert(worked(480,540,7.5,720,60)==0);
 assert(worked(540,540,7.5,720,60)==0);
 assert(worked(600,540,7.5,720,60)==60);
 assert(worked(720,540,7.5,720,60)==180);
 assert(worked(750,540,7.5,720,60)==180);
 assert(worked(780,540,7.5,720,60)==180);
 assert(worked(840,540,7.5,720,60)==240);
 assert(worked(1050,540,7.5,720,60)==450);
 assert(worked(1200,540,7.5,720,60)==450);
 assert(worked(600,540,7.5,720,0)==60);
 assert(fabs(worked(600.5,540,7.5,720,60)-60.5)<1e-9);
 double rate=4500.0/26/(7.5*3600);
 assert(fabs(worked(1050,540,7.5,720,60)*60*rate-4500.0/26)<1e-9);
 puts("12 checks passed: shift boundaries, lunch, cap, fractional time, daily pay");return 0;
}
