//
// Created by ht on 11/30/24.
//

#ifndef CSV_H
#define CSV_H

#include "../STL_STRUCTURES/MyString.h"

struct csv_row {
     MyString name;
     int age {};
     int gender{};
     int blood_group{};
     MyString medical_condition;
     MyString date;
     MyString doctor;
     MyString hospital;
     MyString insurance_provider;
     float billing_sum{};
     int room_no{};
     int admission_type{};
     MyString discharge_date;
     MyString medication;
     int test_result{};
};


#endif //CSV_H
