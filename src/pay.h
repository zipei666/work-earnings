#ifndef PAY_H
#define PAY_H
static double clamp(double x,double a,double b){return x<a?a:x>b?b:x;}
/* Daytime shifts only. Lunch must lie within the shift. */
static double worked(double minute,double start,double hours,double lunch,double rest){
 double end=start+hours*60+rest;
 double elapsed=clamp(minute-start,0,end-start);
 return clamp(elapsed-clamp(minute-lunch,0,rest),0,hours*60);
}
#endif
