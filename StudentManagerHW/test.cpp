#include <format>
#include <iostream>
#include "studentManager.h"


int main() {

studentManager manager;

Student student1("Alice", 20, "Computer Science", "alice@bhcc.edu");
Student student2("David", 24, "English", "david@bhcc.edu");
Student student3("Teresa", 20, "Computer Science", "teresa@umassb.edu");

manager.add(student1);
manager.add(student2);
manager.add(student3);

manager.display();
manager.studentsByMajor();

}