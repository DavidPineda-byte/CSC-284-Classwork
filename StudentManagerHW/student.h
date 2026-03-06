#include <string>

using namespace std; 
class Student {

public:
    void setId(int newId) { id = newId; }
    int getId() const { return id; }

    void setName(const string& newName) { name = newName; }
    string getName() const { return name; }

    void setAge(int newAge) { age = newAge; }
    int getAge() const { return age; }

    void setMajor(const string& newMajor) { major = newMajor; }
    string getMajor() const { return major; }

    void setEmail(const string& newEmail) { email = newEmail; }
    string getEmail() const { return email; }

    private:
        int id; 
        static int nextId;
        string name;
        int age; 
        string major; 
        string email; 

    public:
        Student(): id(nextId++) {}
        Student(const string& newName, int newAge, const string& newMajor, const string& newEmail) 
            : id(nextId++), name(newName), age(newAge), major(newMajor), email(newEmail) {}
    
};