//
// Created by barak on 12/14/2025.
//
#include <memory>
#include <algorithm>
#include <iostream>
#include "wet1util.h"
# include "student.h"

Student::Student(int id):student_num(id) {};
Student::Student(int id, int points):student_num(id), points(points){};

Student::Student(const Student& s){
    this->student_num = s.student_num;
    this->points = s.points;
    this->num_of_course_now = s.num_of_course_now;
}
Student& Student::operator=(const Student& s){
    if (this == &s) {
        return *this;
    }
        this->student_num = s.student_num;
        this->points = s.points;
        this->num_of_course_now = s.num_of_course_now;
    return *this;
}

bool operator< (const Student& s1,const Student& s2){
    return s1.student_num <s2.student_num;
}
bool operator> (const Student& s1,const Student& s2){
    return s1.student_num>s2.student_num;
}
bool operator == (const Student& s1,const Student& s2){
    return s1.student_num== s2.student_num;
}

bool Student::operator< (const Student& s1)const{
    return this->student_num < s1.student_num;
}
bool Student::operator> (const Student& s1)const{
    return this->student_num > s1.student_num;

}
bool Student::operator== (const Student& s1)const{
    return this->student_num == s1.student_num;
}

void Student::Set_Points(const int& points){
    this->points = points;
}
void Student::Set_Num_Of_course_now(const int& num_of_course_now){
    this->num_of_course_now = num_of_course_now;
}
int Student::Get_Points()const{
    return this->points;
}
int Student::Get__Num_Of_course_now()const{
    return this->num_of_course_now;
}
int Student::Get_Student_num()const{
    return this->student_num;
}