//
// Created by barak on 12/14/2025.
//
#include <memory>
#include <algorithm>
#include <iostream>
#include "wet1util.h"
#include "Course.h"

/*Course::Course(int course_id, int points):course_id(course_id),points(points),students_in_course(),
num_of_registered_student(0){};*/

Course::Course(int course_id, int points): course_id(course_id),
          points(points),
          num_of_registered_student(0),
          students_in_course(std::make_shared<AVL_Tree<Student*>>()){};


//Course::Course(const Course& c)=delete;
// Copy Constructor
Course::Course(const Course& c) :
        course_id(c.course_id),
        points(c.points),
        num_of_registered_student(c.num_of_registered_student)
{
    if (c.students_in_course!= nullptr) {
        this->students_in_course = std::make_unique<AVL_Tree<Student*>>(*c.students_in_course);
    } else {
        this->students_in_course = std::make_unique<AVL_Tree<Student*>>();
    }
}


/*Course& Course::operator=(const Course& c){
    if (this->course_id ==c.course_id){
        return *this;
    }
    this->course_id = c.course_id;
    this->points = c.points;
    this->num_of_registered_student = c.num_of_registered_student;
    return *this;
}
*/

Course& Course::operator=(const Course& c) {
    if (this == &c) {
        return *this;
    }
    this->course_id = c.course_id;
    this->points = c.points;
    this->num_of_registered_student = c.num_of_registered_student;

    if (c.students_in_course) {
        this->students_in_course = std::make_unique<AVL_Tree<Student*>>(*c.students_in_course);
    } else {
        this->students_in_course = std::make_unique<AVL_Tree<Student*>>();
    }

    return *this;
}

bool operator< (const Course& c1,const Course& c2){
    return c1.course_id < c2.course_id;
}
 bool operator> (const Course& c1,const Course& c2) {
     return c1.course_id > c2.course_id;
 }
 bool operator== (const Course& c1,const Course& c2){
     return c1.course_id == c2.course_id;

 }

bool Course::operator< (const Course& c1)const{
    return this->course_id<c1.course_id;
}
bool Course::operator> (const Course& c1)const{
    return this->course_id>c1.course_id;

}
bool Course::operator== (const Course& c1)const{
    return this->course_id==c1.course_id;

}

void Course::Set_Points(const int& points){
    this->points=points;
}
void Course::Set_Num_Of_Registered_Students(const int& num_of_registered_student){
    this->num_of_registered_student = num_of_registered_student;
}
int Course::Get_Points()const{
    return this->points;
}
int Course::Get_Num_Of_Registered_Students()const{
   return this->num_of_registered_student;
}
int Course::Get_Course_Id()const{
    return this->course_id;
}
AVL_Tree<Student*>& Course::Get_Students(){
    return *(this->students_in_course);
}

/*
void Course::manualSwap(Course& other) {
    // 1. החלפת ה-ID (עם משתנה זמני פשוט)
    int tempID = this->course_id;
    this->course_id = other.course_id;
    other.course_id = tempID;

    // 2. החלפת ה-unique_ptr ידנית
    // release() -> משחרר את המצביע מהאובייקט ומחזיר את הכתובת הגולמית
    // reset() -> לוקח מצביע גולמי חדש ושם אותו בתוך האובייקט

    AVL_Tree<Student*>* myPtr = this->students_in_course.release();
    AVL_Tree<Student*>* otherPtr = other.students_in_course.release();

    this->students_in_course.reset(otherPtr);
    other.students_in_course.reset(myPtr);
}*/