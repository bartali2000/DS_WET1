//
// Created by Bar Tali on 15/12/2025.
//
#pragma once

#include <memory>

class Student {
    int student_Id;
    int points = 0;
    static int awarded;
    int Enrolled_courses_num = 0;
public:
    static void Dean_award(const int& amount);
    explicit Student(const int& ID) : student_Id(ID) {
        this->points = -awarded;
    }
    ~Student() = default;
    Student(const Student& student) = default;
    Student& operator=(const Student&)= default;
    int get_points() const {
        return this->points + awarded;
    }
    int get_Id() const {
        return student_Id;
    }
    int get_Enrolled() const {
        return Enrolled_courses_num;
    }
    void add_points(const int& amount) {
        points += amount;
    }
    void add_Enrolled_course(const int& amount) {
        Enrolled_courses_num+= amount;
    }
};
