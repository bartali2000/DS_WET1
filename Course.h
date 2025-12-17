//
// Created by Bar Tali on 15/12/2025.
//
#pragma once

#include "AVL_tree.h"
#include "Student.h"

class Course {
    int Points;
    int Course_Id;
    shared_ptr<AVL_tree<shared_ptr<Student>>> students;
public:
    Course(const int& points, const int& Id): Points(points),Course_Id(Id),students(std::make_shared<AVL_tree<shared_ptr<Student>>>()){}
    ~Course() = default;
    Course& operator=(const Course&) = default;
    Course(const Course&) = default;
    StatusType insert_student(const std::shared_ptr<Student>& student);
    bool has_students() const{
        return !students->is_empty();
    }
    StatusType finish_course(const int& studId);
};
