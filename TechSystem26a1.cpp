// You can edit anything you want in this file.
// However you need to implement all public StudentCourseManager function, as provided below as a template

#include "TechSystem26a1.h"


TechSystem::TechSystem(){};//defult

TechSystem::~TechSystem(){};//defult

StatusType TechSystem::addStudent(int studentId)
{
    //invalid input checked at wrap function Insert
    return this->students.Insert(studentId, Student(studentId, -this->points_award));
}

StatusType TechSystem::removeStudent(int studentId)
{
    output_t<Student*> res = students.Find(studentId);
    if(studentId<=0){
        return StatusType::INVALID_INPUT;
    }
    if (res.status() != StatusType::SUCCESS) {
        return res.status();
    }
    if (res.ans()->Get__Num_Of_course_now() > 0) {
        return StatusType::FAILURE;
    }
    //invalid input checked at wrap function Remove
    return this->students.Remove(studentId);
}

StatusType TechSystem::addCourse(int courseId, int points){
    if (points <= 0 || courseId <= 0){
        return StatusType::INVALID_INPUT;
    }
    return this->courses.Insert(courseId,Course(courseId,points));
}

StatusType TechSystem::removeCourse(int courseId){
    output_t<Course*> res = courses.Find(courseId);
    if (res.status() == StatusType::SUCCESS) {
        if(res.ans()->Get_Num_Of_Registered_Students() > 0){
            return StatusType::FAILURE;
        }
    }
    // invalid ERROR at Wrapped function remove
    return this->courses.Remove(courseId);
}

StatusType TechSystem::enrollStudent(int studentId, int courseId){
    if (studentId <= 0 || courseId <=0){
        return StatusType::INVALID_INPUT;
    }
    output_t<Student*> hasStudent = students.Find(studentId);
    output_t<Course*> hasCoures = courses.Find(courseId);
    // chack if there is student and course with that ID
    if(hasStudent.status() != StatusType::SUCCESS || hasCoures.status()!= StatusType::SUCCESS){
        return StatusType::FAILURE;
    }
    // check if there is that student in that course
    output_t<Student**> studentInCourse = hasCoures.ans()->Get_Students().Find(studentId);
    if(studentInCourse.status() == StatusType::SUCCESS){
        return StatusType::FAILURE;
    } else{
        StatusType inCourse = hasCoures.ans()->Get_Students().Insert(studentId, hasStudent.ans());
        if(inCourse != StatusType::SUCCESS){
            return inCourse;
        } else{
            hasStudent.ans()->Set_Num_Of_course_now(hasStudent.ans()->Get__Num_Of_course_now()+1);
            hasCoures.ans()->Set_Num_Of_Registered_Students(hasCoures.ans()->Get_Num_Of_Registered_Students()+1);
            return inCourse;
        }
    }
    return StatusType::FAILURE;
}

StatusType TechSystem::completeCourse(int studentId, int courseId)
{
    if (studentId <= 0 || courseId <=0){
        return StatusType::INVALID_INPUT;
    }
    output_t<Student*> hasStudent = students.Find(studentId);
    output_t<Course*> hasCoures = courses.Find(courseId);
    // chaeck if there is student and course with that ID
    if(hasStudent.status() != StatusType::SUCCESS || hasCoures.status()!= StatusType::SUCCESS){
        return StatusType::FAILURE;
    }
    // check if there is that student in that course
    output_t<Student**> studentInCourse = hasCoures.ans()->Get_Students().Find(studentId);
    if(studentInCourse.status() != StatusType::SUCCESS){
        return studentInCourse.status();
    } else{// the student exist in that course
        StatusType didRemoved = hasCoures.ans()->Get_Students().Remove(studentId);
        if(didRemoved != StatusType::SUCCESS){
            return didRemoved;
        } else{ // removed successfully
            hasStudent.ans()->Set_Num_Of_course_now(hasStudent.ans()->Get__Num_Of_course_now()-1);
            hasStudent.ans()->Set_Points(hasStudent.ans()->Get_Points() + hasCoures.ans()->Get_Points());
            hasCoures.ans()->Set_Num_Of_Registered_Students(hasCoures.ans()->Get_Num_Of_Registered_Students()-1);
            return didRemoved;
        }
    }
    return StatusType::FAILURE;
}

StatusType TechSystem::awardAcademicPoints(int points)
{
    if (points<=0){
        return StatusType::INVALID_INPUT;
    } else{
        this->points_award +=points;
        return StatusType::SUCCESS;
    }
}

output_t<int> TechSystem::getStudentPoints(int studentId){
    if(studentId <= 0){
        return  StatusType::INVALID_INPUT;
    } else{
        output_t<Student*> hasStudent = students.Find(studentId);
        if(hasStudent.status()!=StatusType::SUCCESS){
            return hasStudent.status();
        } else{//there is student
            return output_t<int>(hasStudent.ans()->Get_Points()+ this->points_award);
        }
    }
}

int Get_points_award(){
    return 5;
}