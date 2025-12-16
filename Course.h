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

    StatusType insert_student(const std::shared_ptr<Student>& student) {
        StatusType res = this->students->insert(student->get_Id(),student);
        if (res != StatusType::SUCCESS) return res;
        student->add_Enrolled_course(1);
        return res;
    }
    bool has_students() const{
        return students->is_empty();
    }
    std::shared_ptr<Student> find_student(const int& studentId) {
        shared_ptr<Student>* student_ptr = students->find(studentId);
        if (student_ptr == nullptr) return nullptr;
        return *student_ptr;
    }


    StatusType finish_course(const int& studId) { // find O(logn) ,remove O(logn) other: O(1) total O(log(n_students))
        if (studId <=0) return StatusType::INVALID_INPUT;

        shared_ptr<Student> student = find_student(studId);
        if (student == nullptr) return StatusType::FAILURE;

        StatusType rem_res = students->remove(studId);
        if (rem_res!= StatusType::SUCCESS) return rem_res;

        student->add_Enrolled_course(-1);
        student->add_points(this->Points);
        return StatusType::SUCCESS;

    }
};
