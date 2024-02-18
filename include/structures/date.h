//
// Created by kello on 18/02/24.
//

#ifndef DATE_H
#define DATE_H


#include <string>

class date {
public:
    /**
     * Class constructor.
     * Date is initialized as today's date
     */
    date();

    /**
     * Class constructor.
     * Date is initialized with provided input
     * @param year year number
     * @param month month number
     * @param day day number
     */
    date(unsigned int year, unsigned int month, unsigned int day);

    /**
     * Date is returned in string from
     * @return date string
     */
    [[nodiscard]] std::string toString() const;

private:
    /**
     * Year number
     */
    unsigned int year;

    /**
     * Month number
     */
    unsigned int month;

    /**
     * Day number
     */
    unsigned int day;
};


#endif //DATE_H
