//
// Created by barak on 12/14/2025.
# pragma once
#include <memory>
#include <algorithm>
#include <iostream>
#include "wet1util.h"

class Student{
private:
    int student_num;
    int points;
    int num_of_course_now;

public:
    Student(int id);
    Student(int id, int points);
    ~Student() = default;

    Student(const Student& s);
    Student& operator=(const Student& s);
    friend bool operator< (const Student& s1,const Student& s2);
    friend bool operator> (const Student& s1,const Student& s2);
    friend bool operator== (const Student& s1,const Student& s2);

     bool operator< (const Student& s1)const;
     bool operator> (const Student& s1)const;
     bool operator== (const Student& s1)const;

     void Set_Points(const int& points);
     void Set_Num_Of_course_now(const int& num_of_course_now);
     int Get_Points()const;
     int Get__Num_Of_course_now()const;
     int Get_Student_num()const;



};
