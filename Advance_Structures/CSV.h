//
// Created by ht on 11/30/24.
//

#ifndef CSV_H
#define CSV_H

#include "../STL_STRUCTURES/MyString.h"
#include <fstream>

using std::fstream;
using std::endl;

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

     friend fstream& operator<<(fstream &file_stream, const csv_row &row) {
         file_stream << row.name << endl;
         file_stream << row.age << endl;
         file_stream << row.gender << endl;
         file_stream << row.blood_group << endl;
         file_stream << row.medical_condition << endl;
         file_stream << row.date << endl;
         file_stream << row.doctor << endl;
         file_stream << row.hospital << endl;
         file_stream << row.insurance_provider << endl;
         file_stream << row.billing_sum << endl;
         file_stream << row.room_no << endl;
         file_stream << row.admission_type << endl;
         file_stream << row.discharge_date << endl;
         file_stream << row.medication << endl;
         file_stream << row.test_result << endl;
         return file_stream;
     }
    friend fstream& operator>>(fstream &file_stream, csv_row &row)
     {
         file_stream >> row.name;
         file_stream >> row.age;
         file_stream >> row.gender;
         file_stream >> row.blood_group;
         file_stream >> row.medical_condition;
         file_stream >> row.date;
         file_stream >> row.doctor;
         file_stream >> row.hospital;
         file_stream >> row.insurance_provider;
         file_stream >> row.billing_sum;
         file_stream >> row.room_no;
         file_stream >> row.admission_type;
         file_stream >> row.discharge_date;
         file_stream >> row.medication;
         file_stream >> row.test_result;
         return file_stream;
     }
};


#endif //CSV_H
