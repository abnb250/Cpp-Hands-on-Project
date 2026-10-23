#include "date.h"

bool Date::isleap(int y){
    if(y % 400 == 0 || (y % 4 == 0 && y % 100 !=0)) return true;
    return false;
}

int getdom(int yea, int mon){
    int md[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if(mon == 2){
        if(Date::isleap(yea)) return 29;
        return 28;
    }
    return md[mon];
}

bool Date::isok() const {
    if(day < 1 || month < 1 || month > 12) {
        std::cout << "date is error" << '\n';
        return false;
    }
    int dom = getdom(year, month);  
    if(day > dom ){
        std::cout << "date is error" << '\n';
        return false;
    }
    return true;
}

Date Date::addday(int num) const{
    if(num < 0) return subday(-num);
    int y = year;
    int m = month;
    int d = day+num;
    while(d > getdom(y, m)){
        int dom = getdom(y,m);
        d -= dom;
        m += 1;
        if(m >  12){
            m = 1;
            y += 1;
        }
    }
    Date res(y, m, d);
    return res;
}

Date Date::subday(int num) const{
    if(num < 0) return addday(-num);
    int y = year;
    int m = month;
    int d = day-num;
    while(d <= 0){
        m -= 1;
        if(m < 1){
            m = 12;
            y -= 1;
        }
        int dom = getdom(y, m);
        d += dom;
    }
    Date res(y, m, d);
    return res;
}

int Date::getyear() const{
    return year;
}

int Date::getmonth() const{
    return month;
}

int Date::getday() const{
    return day;
}

std::string Date::getdate() const{
    using namespace std;
    string ye = to_string(year);
    string mo = to_string(month);
    string da = to_string(day);
    while(mo.size() < 2){
        mo = "0" + mo;
    }
    while(da.size() < 2){
        da = "0" + da;
    }
    string res;
    res = ye + "-" + mo + "-" + da;
    return res;
}

std::ostream& operator<<(std::ostream& os, const Date& a){
    os << a.getdate();
    return os;
}

bool Date::operator==(const Date& b) const{
    if(year != b.year) return false;
    if(month != b.month) return false;
    if(day != b.day) return false;
    return true;
}
bool Date::operator!=(const Date& b) const{
    if(*this == b) return false;
    return true;
}
bool Date::operator<(const Date& b) const{
    if(*this == b) return false;
    if(year < b.year) return true;
    else if(year == b.year){
        if(month < b.month) return true;
        else if(month == b.month){
            if(day < b.day) return true;
            else return false;
        }
    }
    return false;
}