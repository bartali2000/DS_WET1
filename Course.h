//
// Created by barak on 12/14/2025.
//

# pragma once
#include <memory>
#include <algorithm>
#include <iostream>
#include "wet1util.h"
#include "AVL_Tree_1.h"
#include "student.h"

using std::shared_ptr;


class Course{
private:
    int course_id;
    int points;
    int num_of_registered_student;
    shared_ptr<AVL_Tree<Student*>> students_in_course;
public:
    Course(int course_id, int points);
    ~Course() = default;

    Course(const Course& c);

    Course& operator=(const Course& c);
    friend bool operator< (const Course& c1,const Course& c2);
    friend bool operator> (const Course& c1,const Course& c2);
    friend bool operator== (const Course& c1,const Course& c2);

     bool operator< (const Course& c1)const;
     bool operator> (const Course& c1)const;
     bool operator== (const Course& c1)const;

    void Set_Points(const int& points);
    void Set_Num_Of_Registered_Students(const int& num_of_registered_student);
    int Get_Points()const;
    int Get_Num_Of_Registered_Students()const;
    int Get_Course_Id()const;
    AVL_Tree<Student*>& Get_Students();

    };