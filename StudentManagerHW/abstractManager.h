#include "student.h"
#include <vector>
#include <string>

class abstractManager{
public: 
    virtual void add(Student student)=0;
    virtual void display()=0;
    virtual Student search(int id)=0; 
    virtual std::vector<Student> searchByName(std::string name)=0;
    virtual void studentsByMajor()=0;
    virtual ~abstractManager() = default;
};