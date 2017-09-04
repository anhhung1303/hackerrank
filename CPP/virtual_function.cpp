#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class Person {
protected:
    std::string name;
    unsigned age;
public:
    Person() = default;
    ~Person() = default;
    virtual void getdata() = 0;
    virtual void putdata() = 0;
};

class Professor : public Person {
private:
    int publications_;
    static int cur_id_;
    int id_;
public:
    Professor() {
        id_ = ++cur_id_;
    }
    ~Professor() = default;
    void getdata() override {
        cin >> name >> age >> publications_;
    }
    void putdata() override {
        std::cout << name << " " << age << " " << publications_ << " " << id_ << std::endl;
    }
};

int Professor::cur_id_ = 0;

class Student : public Person {
private:
    int marks_[6];
    static int cur_id_;
    int id_;
public:
    Student() {
        id_ = ++cur_id_;
    }
    ~Student() = default;
    void getdata() override {
        cin >> name >> age;
        for (int i = 0; i < 6; i++) {
            cin >> marks_[i];
        }
    }
    void putdata() override {
        int sum = 0;
        for (int i = 0; i < 6; i++) {
            sum += marks_[i];
        }
        cout << name << " " << age << " " << sum << " " << id_ << std::endl;
    }
};

int Student::cur_id_ = 0;

int main(){

    int n, val;
    cin>>n; //The number of objects that is going to be created.
    Person *per[n];

    for(int i = 0;i < n;i++){

        cin>>val;
        if(val == 1){
            // If val is 1 current object is of type Professor
            per[i] = new Professor;

        }
        else per[i] = new Student; // Else the current object is of type Student

        per[i]->getdata(); // Get the data from the user.

    }

    for(int i=0;i<n;i++)
        per[i]->putdata(); // Print the required output for each object.

    return 0;

}
