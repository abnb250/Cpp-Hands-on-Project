#include "date.h"

void Date::update(){
    int m = month;
    int d = day;
    int y = year;
    while (1)
    {
        if (m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12)
        {
            if (d > 31)
            {
                m += 1;
                d -= 31;
            }
            else break;
        }
        else if (m == 2)
        {
            if (Date::isleap(y) && d > 29)
            {
                m += 1;
                d -= 29;
            }
            else if (!Date::isleap(y) && d > 28)
            {
                m += 1;
                d -= 28;
            }
            else break;
        }
        else
        {
            if (d > 30)
            {
                m += 1;
                d -= 30;
            }
            else break;
        }
    }
    y += m/12;
    m %= 12;
    year = y;
    month = m;
    day = d;
}

bool Date::isleap(int y){
    if(y % 400 == 0 || (y % 4 == 0 && y % 100 != 0)) return true;
    return false;
}

int Date::get_y() const{
    return year;
}

int Date::get_m() const{
    return month;
}

int Date::get_d() const{
    return day;
}

Date& Date::operator +=(int addday){
    day += addday;
    update();
}

Date& Date::operator -=(int subday){
    
}

bool okdate(int y, int m, int d){
    if(y < 0 || m < 0 || m > 12 || m > 31) return false;
    if(m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12){
        if(d > 31) return false;
    }
    else if(m == 2){
        if(Date::isleap(y) && d > 29) return false;
        if(!Date::isleap(y) && d > 28) return false;
    }
    else{
        if(d > 30) return false;
    }
    return true;
}
