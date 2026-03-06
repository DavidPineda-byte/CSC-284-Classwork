#include "abstractManager.h"
#include <map> 


class studentManager : public abstractManager {

public:
    studentManager(){
    majors.insert({"Computer Science", 0});
    majors.insert({"English", 0});
    majors.insert({"Mathematics", 0});
    majors.insert({"Biology", 0});}

    void add(Student student) override;
    void display() override;
    Student search(int id) override;
    void studentsByMajor() override;
    vector<Student> searchByName(string name) override;
    map<string, int> getMajors() const { return majors; } // Getter for majors map


private: 
    vector<Student> students; // Vector to store student records
    static map<string, int> majors; // map to store number of students for each major     
};