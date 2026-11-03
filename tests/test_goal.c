#include <assert.h>
#include <stdio.h>
#include "../src/goal.h"
static time_t at(int y,int m,int d,int h,int min){struct tm t={0};t.tm_year=y-1900;t.tm_mon=m-1;t.tm_mday=d;t.tm_hour=h;t.tm_min=min;t.tm_isdst=-1;return mktime(&t);}
static void near(double a,double b){assert(fabs(a-b)<0.00001);}
int main(void){Schedule s={4500,7.5,540,720,60,0};double daily=4500.0/25,rate=daily/450;
 assert(workdays(local_copy(at(2026,11,2,9,0)),0)==25);
 assert(workdays(local_copy(at(2026,12,1,9,0)),0)==27);
 near(accumulated(at(2026,11,2,9,0),at(2026,11,2,17,30),s),daily);
 near(accumulated(at(2026,11,2,12,0),at(2026,11,2,13,0),s),0);
 near(accumulated(at(2026,11,1,0,0),at(2026,11,2,0,0),s),0);
 near(accumulated(at(2026,11,2,17,30),at(2026,11,3,9,0),s),0);
 assert(goal_eta(at(2026,11,2,11,0),rate*60,s)==at(2026,11,2,12,0));
 assert(goal_eta(at(2026,11,2,12,30),rate*60,s)==at(2026,11,2,14,0));
 assert(goal_eta(at(2026,11,7,17,30),daily,s)==at(2026,11,9,17,30));
 assert(goal_eta(at(2026,11,30,17,30),4500.0/27,s)==at(2026,12,1,17,30));
 assert(goal_eta(at(2026,11,2,8,0),rate*60,s)==at(2026,11,2,10,0));
 assert(goal_eta(at(2026,11,2,10,0),0,s)==at(2026,11,2,10,0));
 near(accumulated(at(2026,11,1,0,0),at(2026,12,1,0,0),s),4500);
 time_t from=at(2026,11,2,11,20),finish=goal_eta(from,600,s);near(accumulated(from,finish,s),600);
 near(accumulated(from,from-60,s),0);
 assert(month_days(2028,2)==29);assert(month_days(2100,2)==28);
 puts("17 goal checks passed: lunch, weekends, month transitions, exact ETA and accumulated salary");
}
