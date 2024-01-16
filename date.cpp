
#include <iostream>
#include <string>

using namespace std;

class Date {
public:
    int year_{ 1960 };
    int month_{ 1 };
    int day_{ 1 };
    int hour_{ 0 };
    int minute_{ 0 };
    int second_{ 0 };
    bool isOurEra_{ true };

    Date() {}

    Date(int year, int month, int day_standard, int hour, int minute, int second, bool isOurEra_) {
        this->year_ = year;
        this->month_ = month;
        this->day_ = day_standard;
        this->hour_ = hour;
        this->minute_ = minute;
        this->second_ = second;
        this->isOurEra_ = isOurEra_;
        normalize();
    }

    Date& operator=(const Date& other) {
        if (this != &other) {
            year_ = other.year_;
            month_ = other.month_;
            day_ = other.day_;
            hour_ = other.hour_;
            minute_ = other.minute_;
            second_ = other.second_;
            isOurEra_ = other.isOurEra_;
        }

        return *this;
    }

    Date operator+(const Date& other) const {
        Date result = *this;
        return result.increaseBy(other);
    }

    Date& operator+=(const Date& other) {
        second_ += other.second_;
        minute_ += other.minute_;
        hour_ += other.hour_;
        day_ += other.day_;
        month_ += other.month_;
        year_ += other.year_;

        normalize();

        return *this;
    }

    Date operator-(const Date& other) const {
        Date result = *this;
        return result.decreaseBy(other);
    }

    Date& operator-=(const Date& other) {
        second_ -= other.second_;
        minute_ -= other.minute_;
        hour_ -= other.hour_;
        day_ -= other.day_;
        month_ -= other.month_;
        year_ -= other.year_;

        if (year_ < 0) {
            isOurEra_ = false;
            year_ = -year_;
        }

        normalize();

        return *this;
    }

    bool operator<(const Date& other) {
        if (isOurEra_ != other.isOurEra_) return isOurEra_ > other.isOurEra_;
        else if (year_ != other.year_) return year_ < other.year_;
        else if (month_ != other.month_) return month_ < other.month_;
        else if (day_ != other.day_) return day_ < other.day_;
        else if (hour_ != other.hour_) return hour_ < other.hour_;
        else if (minute_ != other.minute_) return minute_ < other.minute_;
        else if (second_ != other.second_) return second_ < other.second_;
        else return false;
    }

    bool operator>(const Date& other) {
        if (isOurEra_ != other.isOurEra_) return isOurEra_ > other.isOurEra_;
        else if (year_ != other.year_) return year_ > other.year_;
        else if (month_ != other.month_) return month_ > other.month_;
        else if (day_ != other.day_) return day_ > other.day_;
        else if (hour_ != other.hour_) return hour_ > other.hour_;
        else if (minute_ != other.minute_) return minute_ > other.minute_;
        else if (second_ != other.second_) return second_ > other.second_;
        else return false;
    }

    bool operator==(const Date& other) {
        return ((year_ == other.year_) &&
            (month_ == other.month_) &&
            (day_ == other.day_) &&
            (hour_ == other.hour_) &&
            (minute_ == other.minute_) &&
            (second_ == other.second_) &&
            (isOurEra_ == other.isOurEra_));
    }

    friend ostream& operator<<(ostream& os, const Date& date) {
        bool flag = date.isOurEra_;
        os << date.year_ << "-" << date.month_ << "-" << date.day_ << " " << date.hour_ << ":" << date.minute_ << ":" << date.second_;
        if (flag == true) os << " Our era";
        else os << " before our era";
        return os;
    }

    Date add(int years, int months, int days, int hours, int minutes, int seconds) const {
        Date result = *this;
        result.year_ += years;
        result.month_ += months;
        result.day_ += days;
        result.hour_ += hours;
        result.minute_ += minutes;
        result.second_ += seconds;

        result.normalize();
        return result;
    }

    Date substract(int year, int month, int day_standard, int hour, int minute, int second) {
        Date date_result = *this;
        date_result.year_ -= year;
        date_result.month_ -= month;
        date_result.day_ -= day_standard;
        date_result.hour_ -= hour;
        date_result.minute_ -= minute;
        date_result.second_ -= second;
        date_result.normalize();
        return date_result;
    }

    int daysInM(int year_standard, int month_standard) {
        if (month_standard == 1 || month_standard == 3 || month_standard == 5 || month_standard == 7 || month_standard == 8 || month_standard == 10 || month_standard == 12) {
            return 31;
        }
        else if (month_standard == 4 || month_standard == 6 || month_standard == 9 || month_standard == 11) {
            return 30;
        }
        else if (month_standard == 2) {
            return isYear366(year_standard) ? 29 : 28;
        }
        else {
            return 0;
        }
    }

    void normalize() {
        if (isOurEra_ && day_ == 0) {
            day_++;
        }
        if (isOurEra_ && month_ == 0) {
            month_++;
        }
        if (isOurEra_ && year_ == 0) {
            year_++;
        }
        if (!isOurEra_ && day_ == 0) {
            day_++;
        }
        if (!isOurEra_ && month_ == 0) {
            month_++;
        }
        if (!isOurEra_ && year_ == 0) {
            year_++;
        }
        while (month_ > 12) {
            month_ -= 12;
            year_++;
        }
        while (month_ <= 0) {
            month_ += 12;
            year_--;
        }
        while (day_ > daysInM(year_, month_)) {
            day_ -= daysInM(year_, month_);
            month_++;
        }
        if (day_ <= 0) {
            month_--;
            day_ += daysInM(year_, month_);
        }
        while (hour_ >= 24) {
            hour_ -= 24;
            day_++;
        }
        while (hour_ < 0) {
            hour_ += 24;
            day_--;
        }
        while (minute_ >= 60) {
            minute_ -= 60;
            hour_++;
        }
        while (minute_ < 0) {
            minute_ += 60;
            hour_--;
        }
        while (second_ < 0) {
            second_ += 60;
            minute_--;
        }
        if (year_ < 0) {
            isOurEra_ = false;
            year_ = abs(year_);
        }
    }

    int compare(const Date& other) const {
        if (year_ != other.year_) {
            return year_ - other.year_;
        }
        if (month_ != other.month_) {
            return month_ - other.month_;
        }
        if (day_ != other.day_) {
            return day_ - other.day_;
        }
        if (hour_ != other.hour_) {
            return hour_ - other.hour_;
        }
        if (minute_ != other.minute_) {
            return minute_ - other.minute_;
        }
        if (second_ != other.second_) {
            return second_ - other.second_;
        }
        if (isOurEra_ != other.isOurEra_) {
            return isOurEra_ ? 1 : -1;
        }
        return 0;
    }

    bool isYear366(int year) const {
        return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    }

    string toString() const {
        string era = isOurEra_ ? "our Era" : "before our Era";
        return to_string(year_) + "-" + addZero(month_) + "-" + addZero(day_) + " " +
            addZero(hour_) + ":" + addZero(minute_) + ":" + addZero(second_) + " " + era;
    }

    string addZero(int num) const {
        if (num < 10) {
            return "0" + to_string(num);
        }
        else {
            return to_string(num);
        }
    }

    Date increaseBy(const Date& other) const {
        Date result = *this;
        result.second_ += other.second_;
        result.minute_ += other.minute_;
        result.hour_ += other.hour_;
        result.day_ += other.day_;
        result.month_ += other.month_;
        result.year_ += other.year_;
        result.normalize();
        return result;
    }

    Date decreaseBy(const Date& other) const {
        Date result = *this;
        result.second_ -= other.second_;
        result.minute_ -= other.minute_;
        result.hour_ -= other.hour_;
        result.day_ -= other.day_;
        result.month_ -= other.month_;
        result.year_ -= other.year_;
        result.normalize();
        return result;
    }
};

int main() {
    Date d1;
    cout << d1 << endl;
    Date d2(2060, 1, 1, 0, 0, 0, true);
    cout << (d1 > d2) << endl;
    cout << (d1 < d2) << endl;
    cout << (d1 == d2) << endl;
    Date d3 = d2.substract(2060, 1, 1, 0, 0, 0);
    Date d4(d3 + d2 - d1);
    Date d5(d4);
    d4 += d5 - d4.add(40, 1, 1, 0, 0, 0);

    cout << d3 << endl;
    cout << d4 << endl;
    cout << d5 << endl;

    return 0;
}