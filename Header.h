#ifndef HEADER_H
#define HEADER_H
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <fstream>
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
	User();
	User(string n, string i, string p);
	virtual ~User();
	string getname();
	string getid();
	string getpass();
	bool login(string id, string pass) const;
	virtual void Dispmenu() = 0;
};
class Course;
class LMS;
class Student :public User {
protected:
	string Program;
	string Enrolledcourse[10];
	int enrollcoursecount;
public:
	Student();
	Student(string n, string i, string p, string pr);
	void enrollcourse(string coursecode);
	bool courseisenroll(string& course);
	void listofcourse();
	string getprogram();
	void Dispmenu() override;
	friend ostream& operator<<(ostream& out, Student s);
	friend istream& operator>>(istream& in, Student& s);
};
ostream& operator<<(ostream& out, Student s);
istream& operator>>(istream& in, Student& s);
class Teacher :public User {
protected:
	string department;
public:
	Teacher();
	Teacher(string n, string i, string p, string d);
	string getdepart();
	void setdepart(const string dep);
	void setteacher(string id, string n, string dep);
	void Dispmenu() override;
	friend ostream& operator<<(ostream& out, Teacher t);
	friend istream& operator>>(istream& in, Teacher& t);
};
ostream& operator<<(ostream& out, Teacher t);
istream& operator>>(istream& in, Teacher& t);
class Submission {
	string sID;
	string content;
	string submitat;
	string grade;
public:
	Submission();
	Submission(string id, string c);
	string getSID();
	string getcontent();
	string getsubmitat();
	string getgrade();
	void setgrade(string g);
	friend ostream& operator<<(ostream& out, Submission s);
};
ostream& operator<<(ostream& out, Submission s);
class Assignment {
	Submission submissions[MAXSUBMISSIONSPERASSIGNMENT];
	string id;
	string title;
	string description;
	string duedate;
	int submissioncount;
public:
	Assignment();
	Assignment(string i, string t, string d, string de);
	void setassig(string i, string t, string d, string de);
	string getid() const;
	string gettitle() const;
	string getdescription() const;
	string getduedate() const;
	void addsubmission(const Submission s);
	int findsubmissionind(string sid);
	void gradesubmission(int ind, string grade);
	void showsubmission();
	friend ostream& operator<<(ostream& out, Assignment a);
	friend istream& operator>>(istream& in, Assignment& a);
};
ostream& operator<<(ostream& out, Assignment a);
istream& operator>>(istream& in, Assignment& a);
class Material {
	string title;
	string description;
	string uploadat;
public:
	Material();
	Material(string t, string d);
	string gettitle();
	string getdesp();
	void setmaterial(string t, string des);
	string getuploadat();
	friend ostream& operator<<(ostream& out, Material m);
	friend istream& operator>>(istream& in, Material& m);
};
ostream& operator<<(ostream& out, Material m);
istream& operator>>(istream& in, Material& m);
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
	Course();
	Course(string code, string name, string tid);
	void setcourse(string code, string name);
	string getcoursecode();
	string getcoursename();
	string getteacherid();
	void assignteacher(string tid);
	Assignment* getassignment();
	Material* getmaterial();
	void enrollstudent(string sid);
	bool studentisenroll(string sid);
	void addmaterial(const Material m);
	void listmaterial();
	void createassignment(const Assignment a);
	int findassignmentind(string aid);
	void addtosubmission(string aid, Submission& s);
	void listassignments();
	void showassigsubmission(string id);
	void gradeassignment(string id, int subind, string grade);
	friend ostream& operator<<(ostream& out, Course c);
	friend istream& operator>>(istream& in, Course& c);
};
ostream& operator<<(ostream& out, Course c);
istream& operator>>(istream& in, Course& c);
class Admin :public User {
protected:
	string department;
public:
	Admin();
	Admin(string n, string id, string pass, string dep);
	void Dispmenu() override;
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
	LMS();
	void loadstd();
	void loadteach();
	void loadcourse();
	void loadmaterial();
	void loadassignments();
	void loadassignCtoT();
	void loadassignStoC();
	void loadgrade();
	void addadmin(string name, string id, string pass, string dep);
	void addteacher(Teacher t);
	void addstudent(Student s);
	void addcourse(Course c);
	Teacher* findteacher(string id);
	Admin* findadmin(string id);
	Student* findstudent(string id);
	Course* findcourse(string code);
	User* loginadmin(const string id, const string pass);
	User* loginteacher(const string id, const string pass);
	User* loginstudent(const string id, const string pass);
	Student* getstudent();
	int getstudentcount();
	Teacher* getteacher();
	int getteachercount();
	Course* getcourse();
	int getcoursecount();
	void createstudent();
	void createteacher();
	void createcourse();
	void assigncoursetoteacher();
	void enrollstudenttocourse();
	void listteachers();
	void liststudents();
	void listcourses();
};
#endif