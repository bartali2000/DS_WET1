// You can edit anything you want in this file.
// However you need to implement all public StudentCourseManager function, as provided below as a template

#include "TechSystem26a1.h"

#include <memory>

#include "../../../../usr/include/complex.h"


TechSystem::TechSystem() = default;

TechSystem::~TechSystem() = default;

StatusType TechSystem::addStudent(int studentId)
{
    if(studentId<= 0) return StatusType::INVALID_INPUT;
    return students.insert(studentId,std::make_shared<Student>(studentId));
}

StatusType TechSystem::removeStudent(int studentId)
{
    if(studentId<= 0) return StatusType::INVALID_INPUT;
    shared_ptr<Student>* student = students.find(studentId);
    if (student == nullptr) return StatusType::FAILURE;
    int enrolled = (*student)->get_Enrolled();
    if(enrolled != 0) return StatusType::FAILURE;
    return students.remove(studentId);
}

StatusType TechSystem::addCourse(int courseId, int points)
{
    if(courseId <=0 || points <= 0) return StatusType::INVALID_INPUT;
    return courses.insert(courseId,Course(points,courseId));
}

StatusType TechSystem::removeCourse(int courseId)
{
    if(courseId<= 0) return StatusType::INVALID_INPUT;
    Course* course = courses.find(courseId);
    if (course == nullptr) return StatusType::FAILURE;
    if((*course).has_students()) return StatusType::FAILURE;
    return courses.remove(courseId);
}

StatusType TechSystem::enrollStudent(int studentId, int courseId)
{
    if(courseId <=0 || studentId <= 0) return StatusType::INVALID_INPUT;
    shared_ptr<Student>* student_ptr= students.find(studentId);
    if(student_ptr == nullptr) return StatusType::FAILURE; //the student do not exsist
    Course* course_ptr = courses.find(courseId);
    if(course_ptr == nullptr) return StatusType::FAILURE; // the course doesnt exsist
    return (*course_ptr).insert_student(*student_ptr);

}

StatusType TechSystem::completeCourse(int studentId, int courseId)
{
    if(courseId <=0 || studentId <= 0) return StatusType::INVALID_INPUT;
    Course* course_ptr = courses.find(courseId);
    if(course_ptr == nullptr) return StatusType::FAILURE; // the course doesnt exsist
    return course_ptr->finish_course(studentId);
}

StatusType TechSystem::awardAcademicPoints(int points)
{
    if(points <=0) return StatusType::INVALID_INPUT;
    Student::Dean_award(points);
    return StatusType::SUCCESS;
}

output_t<int> TechSystem::getStudentPoints(int studentId)
{
    if(studentId <=0) return output_t<int>(StatusType::INVALID_INPUT);
    shared_ptr<Student>* student_ptr = students.find(studentId);
    if(student_ptr == nullptr) return output_t<int>(StatusType::FAILURE);
    return output_t<int>((*student_ptr)->get_points());
}