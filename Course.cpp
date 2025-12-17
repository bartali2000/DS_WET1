//
// Created by Bar Tali on 17/12/2025.
//
#include "Course.h"

StatusType Course::insert_student(const std::shared_ptr<Student>& student) {
    StatusType res = this->students->insert(student->get_Id(),student);
    if (res != StatusType::SUCCESS) return res;
    student->add_Enrolled_course(1);
    return res;
}
StatusType Course::finish_course(const int& studId) { // find O(logn) ,remove O(logn) other: O(1) total O(log(n_students))
    if (studId <=0) return StatusType::INVALID_INPUT;

    shared_ptr<Student> student = find_student(studId);
    if (student == nullptr) return StatusType::FAILURE;

    StatusType rem_res = students->remove(studId);
    if (rem_res!= StatusType::SUCCESS) return rem_res;

    student->add_Enrolled_course(-1);
    student->add_points(this->Points);
    return StatusType::SUCCESS;

}    std::shared_ptr<Student> Course::find_student(const int& studentId) {
    shared_ptr<Student>* student_ptr = students->find(studentId);
    if (student_ptr == nullptr) return nullptr;
    return *student_ptr;
}