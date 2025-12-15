//
// Created by Bar Tali on 15/12/2025.
//
#include "Student.h"
int Student::awarded = 0;
void Student::Dean_award(const int &amount) {
    awarded += amount;
}

