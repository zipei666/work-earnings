#ifndef GOAL_H
#define GOAL_H
#include <time.h>
#include <math.h>
#include "pay.h"
typedef struct { double salary,hours; int start,lunch,rest,off; } Schedule;
static int month_days(int y,int m){static const int a[]={31,28,31,30,31,30,31,31,30,31,30,31};return a[m-1]+(m==2&&y%4==0&&(y%100!=0||y%400==0));}
static struct tm local_copy(time_t t){struct tm *p=localtime(&t);return *p;}
static int workdays(struct tm date,int offday){int n=0;for(int d=1;d<=month_days(date.tm_year+1900,date.tm_mon+1);d++){struct tm x=date;x.tm_mday=d;x.tm_hour=12;x.tm_min=x.tm_sec=0;x.tm_isdst=-1;mktime(&x);if(x.tm_wday!=offday)n++;}return n;}
static double day_rate(struct tm d,Schedule s){return s.salary/workdays(d,s.off)/(s.hours*60);}
static time_t midnight(time_t t){struct tm d=local_copy(t);d.tm_hour=d.tm_min=d.tm_sec=0;d.tm_isdst=-1;return mktime(&d);}
static time_t next_day(time_t t){struct tm d=local_copy(t);d.tm_mday++;d.tm_isdst=-1;return mktime(&d);}
static double minute_of(time_t t){struct tm d=local_copy(t);return d.tm_hour*60+d.tm_min+d.tm_sec/60.0;}
static double accumulated(time_t from,time_t to,Schedule s){if(to<=from)return 0;double sum=0;time_t day=midnight(from);for(int i=0;i<36600&&day<to;i++){struct tm d=local_copy(day);time_t next=next_day(day);if(d.tm_wday!=s.off){double a=day<from?minute_of(from):0,b=next>to?minute_of(to):1440;sum+=(worked(b,s.start,s.hours,s.lunch,s.rest)-worked(a,s.start,s.hours,s.lunch,s.rest))*day_rate(d,s);}day=next;}return sum;}
/* Return 0 when the estimate exceeds the supported 100-year horizon. */
static time_t goal_eta(time_t now,double remaining,Schedule s){if(remaining<=0.000001)return now;time_t day=midnight(now);for(int i=0;i<36600;i++){struct tm d=local_copy(day);if(d.tm_wday!=s.off){double a=day<now?minute_of(now):0,used=worked(a,s.start,s.hours,s.lunch,s.rest),rate=day_rate(d,s),available=(s.hours*60-used)*rate;if(remaining<=available+1e-8){double target=used+remaining/rate;double minute=s.start+target;if(target>s.lunch-s.start+1e-8)minute+=s.rest;int seconds=(int)ceil(minute*60-1e-7);d.tm_hour=seconds/3600;d.tm_min=seconds/60%60;d.tm_sec=seconds%60;d.tm_isdst=-1;return mktime(&d);}remaining-=available;}day=next_day(day);}return 0;}
#endif
