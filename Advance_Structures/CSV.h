//
// Created by ht on 11/30/24.
//

#ifndef CSV_H
#define CSV_H

#include "../STL_STRUCTURES/MyString.h"
#include <fstream>

#include "../Utils/file_operations.h"

using std::fstream;
using std::endl;

struct csv_row {
     MyString name;
     int age {};
     MyString gender{};
     MyString blood_group{};
     MyString medical_condition;
     MyString date;
     MyString doctor;
     MyString hospital;
     MyString insurance_provider;
     float billing_sum{};
     int room_no{};
     MyString admission_type{};
     MyString discharge_date;
     MyString medication;
     MyString test_result{};

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
         move_pointer_ahead(file_stream);
         file_stream >> row.gender;
         file_stream >> row.blood_group;
         file_stream >> row.medical_condition;
         file_stream >> row.date;
         file_stream >> row.doctor;
         file_stream >> row.hospital;
         file_stream >> row.insurance_provider;
         file_stream >> row.billing_sum;
         move_pointer_ahead(file_stream);
         file_stream >> row.room_no;
         move_pointer_ahead(file_stream);
         file_stream >> row.admission_type;
         file_stream >> row.discharge_date;
         file_stream >> row.medication;
         file_stream >> row.test_result;
         return file_stream;
     }
    friend std::ostream& operator<<(std::ostream &os, const csv_row &row) {
         os << "Name: " << row.name << std::endl;
         os << "Age: " << row.age << std::endl;
         os << "Gender: " << row.gender << std::endl;
         os << "Blood Group: " << row.blood_group << std::endl;
         os << "Medical Condition: " << row.medical_condition << std::endl;
         os << "Date: " << row.date << std::endl;
         os << "Doctor: " << row.doctor << std::endl;
         os << "Hospital: " << row.hospital << std::endl;
         os << "Insurance Provider: " << row.insurance_provider << std::endl;
         os << "Billing Sum: " << row.billing_sum << std::endl;
         os << "Room No: " << row.room_no << std::endl;
         os << "Admission Type: " << row.admission_type << std::endl;
         os << "Discharge Date: " << row.discharge_date << std::endl;
         os << "Medication: " << row.medication << std::endl;
         os << "Test Result: " << row.test_result << std::endl;
         os << "-------------------------------------------------------" << std::endl;
         return os;
     }

};

inline void map_str_row_to_csv_row(char str_row[], csv_row &row) {

        int i = 0;
        while (str_row[i] != ',') {
            row.name.insert_char(str_row[i]);
            i++;
        }
        row.name.to_lower();
        i++;
        while (str_row[i] != ',') {
            row.age = row.age * 10 + (str_row[i] - '0');
            i++;
        }
        i++;
        while (str_row[i] != ',') {
            row.gender.insert_char(str_row[i]);
            i++;
        }
        i++;
        while (str_row[i] != ',') {
            row.blood_group.insert_char(str_row[i]);
            i++;
        }
        i++;
        while (str_row[i] != ',') {
            row.medical_condition.insert_char(str_row[i]);
            i++;
        }
        i++;
        while (str_row[i] != ',') {
            row.date.insert_char(str_row[i]);
            i++;
        }
        i++;
        while (str_row[i] != ',') {
            row.doctor.insert_char(str_row[i]);
            i++;
        }
        i++;
        while (str_row[i] != ',') {
            row.hospital.insert_char(str_row[i]);
            i++;
        }
        i++;
        while (str_row[i] != ',') {
            row.insurance_provider.insert_char(str_row[i]);
            i++;
        }
        i++;
        bool decimal = false;
        int mul = 10;
        while (str_row[i] != ',') {
            // billing sum is float

            if (str_row[i] == '.') {
                decimal = true;
                i++;
                continue;
            }
            if (decimal) {
                int temp = str_row[i] - '0';
                double temp2 = double(temp) / mul;
                row.billing_sum = row.billing_sum + temp2;
                mul *= 10;
            }
            else {
                row.billing_sum = row.billing_sum * 10 + (str_row[i] - '0');
            }
            i++;
        }
        i++;
        while (str_row[i] != ',') {
            row.room_no = row.room_no * 10 + (str_row[i] - '0');
            i++;
        }
        i++;
        while (str_row[i] != ',') {
            row.admission_type.insert_char(str_row[i]);
            i++;
        }
        i++;
        while (str_row[i] != ',') {
            row.discharge_date.insert_char(str_row[i]);
            i++;
        }
        i++;
        while (str_row[i] != ',') {
            row.medication.insert_char(str_row[i]);
            i++;
        }
        i++;
        while (str_row[i] != '\0') {
            row.test_result.insert_char(str_row[i]);
            i++;
        }
    }

#endif //CSV_H
