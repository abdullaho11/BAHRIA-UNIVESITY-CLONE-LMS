#ifndef LMS_H
#define LMS_H

#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <ctime>

using namespace std;

const int MAXSTUDENTS = 50;
const int MAXTEACHERS = 20;
const int MAXADMINS = 5;
const int MAXCOURSES = 30;
const int MAXASSIGNMENTSPERCOURSE = 30;
const int MAXMATERIALSPERCOURSE = 50;
const int MAXSUBMISSIONSPERASSIGNMENT = 50;

string nowdate();

class User {
protected:
    string name, Id, password;
public:
    User() :name(""), Id(""), password("") {};
    User(string n, string i, string p) :name(n), Id(i), password(p) {};
    virtual ~User() {};
    string getname() { return name; }
    string getid() { return Id; }
    string getpass() { return password; }
    bool login(string id, string pass) const {
        return (Id == id && password == pass);
    }
    virtual void Dispmenu() = 0;
};

class Student : public User {
protected:
    string Program;
    string Enrolledcourse[10];
    int enrollcoursecount;
public:
    Student() :User("", "", ""), Program(""), enrollcoursecount(0) {};
    Student(string n, string i, string p, string pr) :User(n, i, p), Program(pr), enrollcoursecount(0) {};
    void enrollcourse(string coursecode) {
        if (enrollcoursecount < 10) {
            Enrolledcourse[enrollcoursecount++] = coursecode;
        }
    }
    bool courseisenroll(string& course) {
        for (int i = 0;i < enrollcoursecount;i++) {
            if (Enrolledcourse[i] == course) { return true; }
        }
        return false;
    }
    string getprogram() { return Program; }
    void Dispmenu() override {}

    vector<string> getEnrolledCourses() {
        vector<string> courses;
        for (int i = 0; i < enrollcoursecount; i++) {
            courses.push_back(Enrolledcourse[i]);
        }
        return courses;
    }

    int getEnrollCourseCount() { return enrollcoursecount; }
};

class Teacher : public User {
protected:
    string department;
public:
    Teacher() :User("", "", ""), department("") {};
    Teacher(string n, string i, string p, string d) :User(n, i, p), department(d) {};
    string getdepart() { return department; }
    void setdepart(const string dep) { department = dep; }
    void setteacher(string id, string n, string dep) {
        Id = id;
        name = n;
        department = dep;
    }
    void Dispmenu() override {}
};

class Admin : public User {
protected:
    string department;
public:
    Admin() :User("", "", ""), department("") {};
    Admin(string n, string id, string pass, string dep) :User(n, id, pass), department(dep) {};
    void Dispmenu() override {}
};

class Submission {
    string sID;
    string content;
    string submitat;
    string grade;
public:
    Submission() :sID(""), content(""), submitat(""), grade("") {};
    Submission(string id, string c) :sID(id), content(c), submitat(nowdate()), grade("") {};
    string getSID() { return sID; }
    string getcontent() { return content; }
    string getsubmitat() { return submitat; }
    string getgrade() { return grade; }
    void setgrade(string g) { grade = g; }
};

class Assignment {
    Submission submissions[MAXSUBMISSIONSPERASSIGNMENT];
    string id;
    string title;
    string description;
    string duedate;
    int submissioncount;
public:
    Assignment() :id(""), title(""), description(""), duedate(""), submissioncount(0) {};
    Assignment(string i, string t, string d, string de) :id(i), title(t), description(d), duedate(de), submissioncount(0) {};
    void setassig(string i, string t, string d, string de) {
        id = i;
        title = t;
        description = d;
        duedate = de;
    }
    string getid() const { return id; }
    string gettitle() const { return title; }
    string getdescription() const { return description; }
    string getduedate() const { return duedate; }
    void addsubmission(const Submission s) {
        if (submissioncount < MAXSUBMISSIONSPERASSIGNMENT) {
            submissions[submissioncount++] = s;
        }
    }
    int findsubmissionind(string sid) {
        for (int i = 0;i < submissioncount;i++) {
            if (submissions[i].getSID() == sid) return i;
        }
        return -1;
    }
    void gradesubmission(int ind, string grade) {
        if (ind >= 0 && ind < submissioncount) {
            submissions[ind].setgrade(grade);
        }
    }
    int getSubmissionCount() { return submissioncount; }
    Submission getSubmission(int index) {
        if (index >= 0 && index < submissioncount)
            return submissions[index];
        return Submission();
    }
};

class Material {
    string title;
    string description;
    string uploadat;
public:
    Material() :title(""), description(""), uploadat("") {};
    Material(string t, string d) :title(t), description(d), uploadat(nowdate()) {};
    string gettitle() { return title; }
    string getdesp() { return description; }
    void setmaterial(string t, string des) { title = t;description = des; }
    string getuploadat() { return uploadat; }
};

class Course {
    string coursecode;
    string coursename;
    string teacherid;
    string enrolledstd[MAXSTUDENTS];
    int enrolledcount;
    Material material[MAXMATERIALSPERCOURSE];
    int materialpercourse;
    Assignment assignments[MAXASSIGNMENTSPERCOURSE];
    int assignmentpercourse;
public:
    Course() :coursecode(""), coursename(""), teacherid(""), enrolledcount(0), materialpercourse(0), assignmentpercourse(0) {};
    Course(string code, string name, string tid) :coursecode(code), coursename(name), teacherid(tid), enrolledcount(0), materialpercourse(0), assignmentpercourse(0) {};
    void setcourse(string code, string name) { coursecode = code;coursename = name; }
    string getcoursecode() { return coursecode; }
    string getcoursename() { return coursename; }
    string getteacherid() { return teacherid; }
    void assignteacher(string tid) { teacherid = tid; }
    Assignment* getassignment() {
        return assignments;
    }
    Material* getmaterial() {
        return material;
    }
    void enrollstudent(string sid) {
        if (enrolledcount < MAXSTUDENTS) {
            enrolledstd[enrolledcount++] = sid;
        }
    }
    bool studentisenroll(string sid) {
        for (int i = 0;i < enrolledcount;i++) {
            if (enrolledstd[i] == sid) {
                return true;
            }
        }
        return false;
    }
    void addmaterial(const Material m) {
        if (materialpercourse < MAXMATERIALSPERCOURSE) {
            material[materialpercourse++] = m;
        }
    }
    void createassignment(const Assignment a) {
        if (assignmentpercourse < MAXASSIGNMENTSPERCOURSE) {
            assignments[assignmentpercourse++] = a;
        }
    }
    int findassignmentind(string aid) {
        for (int i = 0;i < assignmentpercourse;i++) {
            if (assignments[i].getid() == aid) return i;
        }
        return -1;
    }
    void addtosubmission(string aid, Submission& s) {
        int ind = findassignmentind(aid);
        if (ind != -1) {
            assignments[ind].addsubmission(s);
        }
    }
    void gradeassignment(string id, int subind, string grade) {
        int ind = findassignmentind(id);
        if (ind != -1) {
            assignments[ind].gradesubmission(subind, grade);
        }
    }

    int getAssignmentCount() { return assignmentpercourse; }
    Assignment getAssignment(int index) {
        if (index >= 0 && index < assignmentpercourse)
            return assignments[index];
        return Assignment();
    }

    int getMaterialCount() { return materialpercourse; }
    Material getMaterial(int index) {
        if (index >= 0 && index < materialpercourse)
            return material[index];
        return Material();
    }

    int getEnrolledCount() { return enrolledcount; }
    string getEnrolledStudent(int index) {
        if (index >= 0 && index < enrolledcount)
            return enrolledstd[index];
        return "";
    }
};

class LMS {
    Student students[MAXSTUDENTS];
    int studentscount;
    Teacher teachers[MAXTEACHERS];
    int teacherscount;
    Admin admin[MAXADMINS];
    int admincount;
    Course course[MAXCOURSES];
    int coursecount;
public:
    LMS() :studentscount(0), teacherscount(0), admincount(0), coursecount(0) {
        if (admincount < MAXADMINS) {
            admin[admincount++] = Admin("Bahria", "admin", "admin", "CS");
            loadstd();
            loadteach();
            loadcourse();
        }
    }

    void loadstd() {
        ifstream fin("students.txt");
        if (!fin) { return; }
        string id, name, pass, pr;
        while (fin >> name >> id >> pass >> pr) {
            students[studentscount] = Student(name, id, pass, pr);
            studentscount++;
        }
        fin.close();
    }

    void loadteach() {
        ifstream fin("teachers.txt");
        if (!fin) { return; }
        string id, name, pass, dep;
        while (fin >> name >> id >> pass >> dep) {
            teachers[teacherscount] = Teacher(name, id, pass, dep);
            teacherscount++;
        }
        fin.close();
    }

    void loadcourse() {
        ifstream fin("course.txt");
        if (!fin) { return; }
        string code, name;
        while (fin >> code >> name) {
            course[coursecount].setcourse(code, name);
            coursecount++;
        }
        fin.close();
    }

    void addadmin(string name, string id, string pass, string dep) {
        admin[admincount++] = Admin(name, id, pass, dep);
    }

    void addteacher(Teacher t) {
        teachers[teacherscount++] = t;
        ofstream fout("teachers.txt", ios::app);
        if (fout) {
            fout << t.getname() << " " << t.getid() << " " << t.getpass() << " " << t.getdepart() << endl;
            fout.close();
        }
    }

    void addstudent(Student s) {
        students[studentscount++] = s;
        ofstream fout("students.txt", ios::app);
        if (fout) {
            fout << s.getname() << " " << s.getid() << " " << s.getpass() << " " << s.getprogram() << endl;
            fout.close();
        }
    }

    void addcourse(Course c) {
        course[coursecount++] = c;
        ofstream fout("course.txt", ios::app);
        if (fout) {
            fout << c.getcoursecode() << " " << c.getcoursename() << endl;
            fout.close();
        }
    }

    Teacher* findteacher(string id) {
        for (int i = 0;i < teacherscount;i++) {
            if (teachers[i].getid() == id) {
                return &teachers[i];
            }
        }
        return nullptr;
    }

    Admin* findadmin(string id) {
        for (int i = 0;i < admincount;i++) {
            if (admin[i].getid() == id) {
                return &admin[i];
            }
        }
        return nullptr;
    }

    Student* findstudent(string id) {
        for (int i = 0;i < studentscount;i++) {
            if (students[i].getid() == id) {
                return &students[i];
            }
        }
        return nullptr;
    }

    Course* findcourse(string code) {
        for (int i = 0;i < coursecount;i++) {
            if (course[i].getcoursecode() == code) {
                return &course[i];
            }
        }
        return nullptr;
    }

    User* loginadmin(const string id, const string pass) {
        for (int i = 0;i < admincount;i++) {
            if (admin[i].login(id, pass)) return &admin[i];
        }
        return nullptr;
    }

    User* loginteacher(const string id, const string pass) {
        for (int i = 0;i < teacherscount;i++) {
            if (teachers[i].login(id, pass)) return &teachers[i];
        }
        return nullptr;
    }

    User* loginstudent(const string id, const string pass) {
        for (int i = 0;i < studentscount;i++) {
            if (students[i].login(id, pass)) return &students[i];
        }
        return nullptr;
    }

    Student* getstudent() { return students; }
    int getstudentcount() { return studentscount; }
    Teacher* getteacher() { return teachers; }
    int getteachercount() { return teacherscount; }
    Course* getcourse() { return course; }
    int getcoursecount() { return coursecount; }

    vector<Course> getCoursesByTeacher(string teacherId) {
        vector<Course> teacherCourses;
        for (int i = 0; i < coursecount; i++) {
            if (course[i].getteacherid() == teacherId) {
                teacherCourses.push_back(course[i]);
            }
        }
        return teacherCourses;
    }
};

#endif // LMS_H
