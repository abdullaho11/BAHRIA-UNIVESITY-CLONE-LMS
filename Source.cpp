#include "Header.h"
string nowdate() {
	time_t t = time(nullptr);
	tm* tm_ptr = localtime(&t);
	char buf[64];
	strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", tm_ptr);
	return string(buf);
}
User::User() :name(""), Id(""), password("") {};
User::User(string n, string i, string p) :name(n), Id(i), password(p) {};
User::~User() {};
string User::getname() { return name; }
string User::getid() { return Id; }
string User::getpass() { return password; }
bool User::login(string id, string pass) const {
	return (Id == id && password == pass);
}
Student::Student() :User("", "", ""), Program(""), enrollcoursecount(0) {};
Student::Student(string n, string i, string p, string pr) :User(n, i, p), Program(pr), enrollcoursecount(0) {};
void Student::enrollcourse(string coursecode) {
	if (enrollcoursecount < 10) {
		Enrolledcourse[enrollcoursecount++] = coursecode;
	}
}
bool Student::courseisenroll(string& course) {
	for (int i = 0;i < enrollcoursecount;i++) {
		if (Enrolledcourse[i] == course) { return true; }
	}
	return false;
}
void Student::listofcourse() {
	if (enrollcoursecount == 0) {
		cout << "NO COURSE ENROLLED" << endl;
	}
	else {
		for (int i = 0;i < enrollcoursecount;i++)
		{
			cout << "ENROLLED COURSES\n" << Enrolledcourse[i] << endl;
		}
	}
}
string Student::getprogram() { return Program; }
ostream& operator<<(ostream& out, Student s) {
	cout << "STUDENT'S NAME : " << s.name << endl;
	cout << "STUDENTS'S ID : " << s.Id << endl;
	cout << "STUDENTS'S PASS : " << s.password << endl;
	cout << "STUDENT'S PROGRAM : " << s.Program << endl;
	cout << "ENROLLED COURSES : " << endl;
	for (int i = 0;i < s.enrollcoursecount;i++) {
		cout << s.Enrolledcourse[i] << endl;
	}
	cout << "STUDENT'S COURSE COUNT : " << s.enrollcoursecount << endl;
	return out;
}
istream& operator>>(istream& in, Student& s) {
	cout << "Enter Student's Name : ";
	cin.ignore();
	getline(in, s.name);
	cout << "Enter Student's ID : ";
	getline(in, s.Id);
	cout << "Enter Student's PASSWORD : ";
	getline(in, s.password);
	cout << "Enter Student's Program: ";
	getline(in, s.Program);
	return in;
}
Teacher::Teacher() :User("", "", ""), department("") {};
Teacher::Teacher(string n, string i, string p, string d) :User(n, i, p), department(d) {};
string Teacher::getdepart() { return department; }
void Teacher::setdepart(const string dep) { department = dep; }
void Teacher::setteacher(string id, string n, string dep) {
	Id = id;
	name = n;
	department = dep;
}
ostream& operator<<(ostream& out, Teacher t) {
	cout << "TEACHER'S ID : " << t.Id << endl;
	cout << "TEACHER'S PASS : " << t.password << endl;
	cout << "TEACHER'S NAME : " << t.name << endl;
	cout << "TEACHER'S DEPARTMENT : " << t.department << endl;
	return out;
}
istream& operator>>(istream& in, Teacher& t) {
	cout << "Enter Teachers Name : ";
	cin.ignore();
	getline(in, t.name);
	cout << "Enter Teachers ID : ";
	getline(in, t.Id);
	cout << "Enter Teachers Password : ";
	getline(in, t.password);
	cout << "Enter Teachers Department : ";
	getline(in, t.department);
	return in;
}
Submission::Submission() :sID(""), content(""), submitat(""), grade("") {};
Submission::Submission(string id, string c) :sID(id), content(c), submitat(nowdate()), grade("") {};
string Submission::getSID() { return sID; }
string Submission::getcontent() { return content; }
string Submission::getsubmitat() { return submitat; }
string Submission::getgrade() { return grade; }
void Submission::setgrade(string g) { grade = g; }
ostream& operator<<(ostream& out, Submission s) {
	cout << ". Title : " << s.sID << endl;
	cout << "Uploaded At : " << s.submitat << endl;
	cout << "Content : " << s.content << endl;
	cout << "Grade : " << s.grade << endl;
	return out;
}
Assignment::Assignment() :id(""), title(""), description(""), duedate(""), submissioncount(0) {};
Assignment::Assignment(string i, string t, string d, string de) :id(i), title(t), description(d), duedate(de), submissioncount(0) {};
void Assignment::setassig(string i, string t, string d, string de) {
	id = i;
	title = t;
	description = d;
	duedate = de;
}
string Assignment::getid() const { return id; }
string Assignment::gettitle() const { return title; }
string Assignment::getdescription() const { return description; }
string Assignment::getduedate() const { return duedate; }
void Assignment::addsubmission(const Submission s) {
	if (submissioncount < MAXSUBMISSIONSPERASSIGNMENT) {
		submissions[submissioncount++] = s;
	}
	else cout << "SUBMISSION LIMIT REACHED" << endl;
}
int Assignment::findsubmissionind(string sid) {
	for (int i = 0;i < submissioncount;i++) {
		if (submissions[i].getSID() == sid) return i;
	}
	return -1;
}
void Assignment::gradesubmission(int ind, string grade) {
	if (ind >= 0 && ind < submissioncount) {
		submissions[ind].setgrade(grade);
	}
}
void Assignment::showsubmission() {
	if (submissioncount == 0) {
		cout << "NO SUBMISSIONS FOR ASSIGNMENT";
	}
	else {
		cout << "SUBMISSIONS\n";
		for (int i = 0;i < submissioncount;i++) {
			cout << submissions[i] << endl;
		}
	}
}
ostream& operator<<(ostream& out, Assignment a) {
	cout << "Assignment ID : " << a.id << endl;
	cout << "Assignment TITLE : " << a.title << endl;
	cout << "Assignment DESCRIPTION : " << a.description << endl;
	cout << "Assignment DUE DATE : " << a.duedate << endl;
	return out;
}
istream& operator>>(istream& in, Assignment& a) {
	cout << "Enter assignment ID (e.g., A1): ";
	cin.ignore();
	cin >> a.id;
	cout << "Enter title: ";
	cin.ignore(); getline(cin, a.title);
	cout << "Enter description: ";
	getline(cin, a.description);
	cout << "Enter due date (e.g., 2025-12-01): ";
	getline(cin, a.duedate);
	return in;
}
Material::Material() :title(""), description(""), uploadat("") {};
Material::Material(string t, string d) :title(t), description(d), uploadat(nowdate()) {};
string Material::gettitle() { return title; }
string Material::getdesp() { return description; }
void Material::setmaterial(string t, string des) { title = t;description = des; }
string Material::getuploadat() { return uploadat; }
ostream& operator<<(ostream& out, Material m) {
	cout << "Title : " << m.title << endl;
	cout << "Description : " << m.description << endl;
	return out;
}
istream& operator>>(istream& in, Material& m) {
	cout << "Enter Title : " << endl;
	cin >> m.title;
	cout << "Description : " << endl;
	cin.ignore();
	getline(cin, m.description);
	return in;
}
Course::Course() :coursecode(""), coursename(""), teacherid(""), enrolledcount(0), materialpercourse(0), assignmentpercourse(0) {};
Course::Course(string code, string name, string tid) :coursecode(code), coursename(name), teacherid(tid), enrolledcount(0), materialpercourse(0), assignmentpercourse(0) {};
void Course::setcourse(string code, string name) { coursecode = code;coursename = name; }
string Course::getcoursecode() { return coursecode; }
string Course::getcoursename() { return coursename; }
string Course::getteacherid() { return teacherid; }
void Course::assignteacher(string tid) { teacherid = tid; }
Assignment* Course::getassignment() {
	return assignments;
}
Material* Course::getmaterial() {
	return material;
}
void Course::enrollstudent(string sid) {
	if (enrolledcount < MAXSTUDENTS) {
		enrolledstd[enrolledcount++] = sid;
	}
	else {
		cout << "COURSE IS FULL, CAN'T ENROLL MORE STUDENTS\n";
	}
}
bool Course::studentisenroll(string sid) {
	for (int i = 0;i < enrolledcount;i++) {
		if (enrolledstd[i] == sid) {
			return true;
		}
	}
	return false;
}
void Course::addmaterial(const Material m) {
	if (materialpercourse < MAXMATERIALSPERCOURSE) {
		material[materialpercourse++] = m;
	}
	else cout << "MATERIAL LIMIT REACHED\n";
}
void Course::listmaterial() {
	if (materialpercourse == 0) {
		cout << "NO MATERIAL FOR THIS COURSE\n";
	}
	else {
		cout << "MATERIAL FOR THIS COURSE : \n";
		for (int i = 0;i < materialpercourse;i++) {
			cout << i + 1 << material[i] << endl;
		}
	}
}
void Course::createassignment(const Assignment a) {
	if (assignmentpercourse < MAXASSIGNMENTSPERCOURSE) {
		assignments[assignmentpercourse++] = a;
	}
	else cout << "Assignment Limit Reached\n";
}
int Course::findassignmentind(string aid) {
	for (int i = 0;i < assignmentpercourse;i++) {
		if (assignments[i].getid() == aid) return i;
	}
	return -1;
}
void Course::addtosubmission(string aid, Submission& s) {
	int ind = findassignmentind(aid);
	if (ind == -1) {
		cout << "NO ASSIGNMENT FOUND\n";
	}
	else {
		assignments[ind].addsubmission(s);
	}
}
void Course::listassignments() {
	if (assignmentpercourse == 0) {
		cout << "No Assignments Uploaded\n";
	}
	else {
		cout << "Assignments for Course : \n";
		for (int i = 0;i < assignmentpercourse;i++) {
			cout << assignments[i] << endl;
		}
	}
}
void Course::showassigsubmission(string id) {
	int ind = findassignmentind(id);
	if (ind == -1) {
		cout << "No Assignment found\n";
	}
	else {
		assignments[ind].showsubmission();
	}
}
void Course::gradeassignment(string id, int subind, string grade) {
	int ind = findassignmentind(id);
	if (ind == -1) {
		cout << "No Assignment found\n";
	}
	else {
		assignments[ind].gradesubmission(subind, grade);
	}
}
ostream& operator<<(ostream& out, Course c) {
	cout << "COURSE CODE : " << c.coursecode << endl;
	cout << "COURSE NAME : " << c.coursename << endl;
	return out;
}
istream& operator>>(istream& in, Course& c) {
	cout << "ENTER COURSE CODE : ";
	in >> ws;
	getline(in, c.coursecode);
	cout << "ENTER COURSE NAME : ";
	getline(in, c.coursename);
	return in;
}
Admin::Admin() :User("", "", ""), department("") {};
Admin::Admin(string n, string id, string pass, string dep) :User(n, id, pass), department(dep) {};
LMS::LMS() :studentscount(0), teacherscount(0), admincount(0), coursecount(0) {
	if (admincount < MAXADMINS) {
		admin[admincount++] = Admin("Bahria", "admin", "admin", "CS");
		loadstd();
		loadteach();
		loadcourse();
		loadmaterial();
		loadassignments();
		loadassignCtoT();
		loadassignStoC();
		loadgrade();
	}
}
void LMS::loadstd() {
	ifstream fin("students.txt");
	if (!fin) { return; }
	string id, name, pass, pr;
	while (fin>>name>>id>>pass>>pr) {
		students[studentscount] = Student(name, id, pass, pr);
		studentscount++;
	}
	fin.close();
}
void LMS::loadteach() {
	ifstream fin("teachers.txt");
	if (!fin) { return; }
	string id, name, pass, dep;
	while (fin>>name>>id>>pass>>dep) {
		teachers[teacherscount] = Teacher(name, id, pass, dep);
		teacherscount++;
	}
	fin.close();
}
void LMS::loadcourse() {
	ifstream fin("course.txt");
	if (!fin) { return; }
	string code, name;
	while (fin >> code >> name) {
		course[coursecount].setcourse(code, name);
		coursecount++;
	}
	fin.close();
}
void LMS::loadmaterial() {
	ifstream fin("materials.txt");
	if (!fin) { return; }
	string title, des;
	while (fin >> title >> des) {
		course[coursecount].getmaterial()->setmaterial(title, des);
	}
	fin.close();
}
void LMS::loadassignments() {
	ifstream fin("assignments.txt");
	if (!fin) { return; }
	string id, title, des, due;
	while (fin >> id >> title >> des >> due) {
		course[coursecount].getassignment()->setassig(id, title, des, due);
	}
	fin.close();
}
void LMS::loadassignCtoT() {
	ifstream fin("assignCtoT.txt");
	if (!fin) { return; }
	string id, name, dep, code, coursename;
	while (fin >> id >> name >> dep >> code >> coursename) {
		teachers[teacherscount].setteacher(id, name, dep);
		course[coursecount].setcourse(code, coursename);
		course->assignteacher(teachers->getid());
	}
	fin.close();
}
void LMS::loadassignStoC() {
	ifstream fin("assignStoC.txt");
	if (!fin) { return; }
	string id, name, pass, pr, code, coursename;
	while (fin >> id >> name >> pass >> pr >> code >> coursename) {
		students[studentscount] = Student(name, id, pass, pr);
		course[coursecount].setcourse(code, coursename);
		course->enrollstudent(students->getid());
		students->enrollcourse(course->getcoursecode());
	}
	fin.close();
}
void LMS::loadgrade() {
	ifstream fin("grades.txt");
	if (!fin) { return; }
	string aid, grade;
	int ind;
	while (fin >> aid >> ind >> grade) {
		course[coursecount].gradeassignment(aid, ind, grade);
	}
	fin.close();
}
void LMS::addadmin(string name, string id, string pass, string dep) {
	admin[admincount++] = Admin(name, id, pass, dep);
}
void LMS::addteacher(Teacher t) {
	teachers[teacherscount++] = t;
	ofstream fout("teachers.txt", ios::app);
	if (!fout)
		cout << "file Not created ";
	fout << t.getname() << " " << t.getid() << " " << t.getpass() << " " << t.getdepart() << endl;
	fout.close();
	cout << "Student saved permanently\n";
}
void LMS::addstudent(Student s) {
	students[studentscount++] = s;
	ofstream fout("students.txt", ios::app);
	if (!fout)
		cout << "file Not created ";
	fout << s.getname() << " " << s.getid() << " " << s.getpass() << " " << s.getprogram() << endl;
	fout.close();
	cout << "Faculty saved permanently\n";
}
void LMS::addcourse(Course c) {
	course[coursecount++] = c;
	ofstream fout("course.txt", ios::app);
	if (!fout)
		cout << "file Not created ";
	fout << c.getcoursecode() << " " << c.getcoursename() << endl;
	fout.close();
	cout << "Course saved permanently\n";
}
Teacher* LMS::findteacher(string id) {
	for (int i = 0;i < teacherscount;i++) {
		if (teachers[i].getid() == id) {
			return &teachers[i];
		}
	}
	return nullptr;
}
Admin* LMS::findadmin(string id) {
	for (int i = 0;i < admincount;i++) {
		if (admin[i].getid() == id) {
			return &admin[i];
		}
	}
	return nullptr;
}
Student* LMS::findstudent(string id) {
	for (int i = 0;i < studentscount;i++) {
		if (students[i].getid() == id) {
			return &students[i];
		}
	}
	return nullptr;
}
Course* LMS::findcourse(string code) {
	for (int i = 0;i < coursecount;i++) {
		if (course[i].getcoursecode() == code) {
			return &course[i];
		}
	}
	return nullptr;
}
User* LMS::loginadmin( string id,  string pass) {
	for (int i = 0;i < admincount;i++) {
		if (admin[i].login(id, pass)) return &admin[i];
	}
	return nullptr;
}
User* LMS::loginteacher(string id,string pass) {
	for (int i = 0;i < teacherscount;i++) {
		if (teachers[i].login(id, pass)) return &teachers[i];
	}
	return nullptr;
}
User* LMS::loginstudent( string id, string pass) {
	for (int i = 0;i < studentscount;i++) {
		if (students[i].login(id, pass)) return &students[i];
	}
	return nullptr;
}
Student* LMS::getstudent() { return students; }
int LMS::getstudentcount() { return studentscount; }
Teacher* LMS::getteacher() { return teachers; }
int LMS::getteachercount() { return teacherscount; }
Course* LMS::getcourse() { return course; }
int LMS::getcoursecount() { return coursecount; }
void LMS::createstudent() {
	Student s;
	cin >> s;
	if (studentscount < MAXSTUDENTS) {
		addstudent(s);
	}
	else cout << "FALIED TO CREATE STUDENT \n";
}
void LMS::createteacher() {
	Teacher t;
	cin >> t;
	if (teacherscount < MAXTEACHERS) {
		addteacher(t);
	}
	else cout << "FALIED TO CREATE TEACHER \n";
}
void LMS::createcourse() {
	Course c;
	cin >> c;
	try {
		if (coursecount < MAXCOURSES) {
			addcourse(c);
		}
		else {
			throw string("limit reached. Cannot create more courses.");
		}
	}
	catch (string& error) {
		cout << "EXCEPTION: " << error << endl;
		cout << "FALIED TO CREATE COURSE \n";
	}
}
void LMS::assigncoursetoteacher() {
	string code, tid;
	cout << "Enter Course Code : ";
	cin.ignore();
	getline(cin, code);
	Course* c = findcourse(code);
	if (!c) {
		cout << "COURSE NOT AVAILABLE";
		return;
	}
	cout << "Enter Teacher ID to assign Course : ";
	getline(cin, tid);
	Teacher* t = findteacher(tid);
	if (!t) {
		cout << "TEACHER NOT AVAILABLE";
		return;
	}
	c->assignteacher(tid);
	cout << "COURSE ASSIGNED TO TEACHER\n";//dynamic binding
	ofstream fout("assignCtoT.txt", ios::app);
	if (!fout)cout << "file Not created ";
	fout << t->getid() << " " << t->getname() << " " << t->getdepart() << endl;
	fout << c->getcoursecode() << " " << c->getcoursename() << endl;
	fout.close();
	cout << "Saved permanently\n";
}
void LMS::enrollstudenttocourse() {
	string code, sid;
	cout << "Enter Course Code : ";
	cin.ignore();
	getline(cin, code);
	Course* c = findcourse(code);
	if (!c) {
		cout << "COURSE NOT AVAILABLE";
		return;
	}
	cout << "Enter Student ID to Enroll in a Course : ";
	getline(cin, sid);
	Student* s = findstudent(sid);
	if (!s) {
		cout << "TEACHER NOT AVAILABLE";
		return;
	}
	c->enrollstudent(sid);
	s->enrollcourse(code);
	cout << "STUDENT ENROLLED IN A COURSE\n";//dynamic binding
	ofstream fout("assignStoC.txt", ios::app);
	if (!fout)cout << "file Not created ";
	fout << s->getid() << " " << s->getname() << " " << s->getprogram() << endl;
	fout << c->getcoursecode() << " " << c->getcoursename() << endl;
	fout.close();
	cout << "Saved permanently\n";
}
void LMS::listteachers() {
	if (teacherscount == 0) { cout << "No Teachers .\n"; return; }
	else {
		for (int i = 0;i < teacherscount;i++) {
			cout << i + 1 << ". Teacher Data \n";
			cout << teachers[i] << endl;
		}
	}
}
void LMS::liststudents() {
	if (studentscount == 0) { cout << "No Students .\n"; return; }
	else {
		for (int i = 0;i < studentscount;i++) {
			cout << i + 1 << ". Student Data \n";
			cout << students[i] << endl;
		}
	}
}
void LMS::listcourses() {
	if (coursecount == 0) { cout << "No Course .\n"; return; }
	else {
		for (int i = 0;i < coursecount;i++) {
			cout << i + 1 << ". Course Data \n";
			cout << course[i] << endl;
			cout << "ASSIGNED TEACHER ID : " << course[i].getteacherid() << endl;
		}
	}
}
extern LMS lms;
void Student::Dispmenu() {
	Student* ich = this;
	while (true) {
		cout << "----DASHBOARD FOR STUDENT (" << ich->getname() << ")----\n";
		cout << "1. View enrolled courses\n";
		cout << "2. View materials for a course\n";
		cout << "3. View assignments for a course\n";
		cout << "4. Submit assignment\n";
		cout << "5. Logout\n";
		cout << "Choose an option: ";
		int ch;
		cin >> ch;
		switch (ch) {
		case 1: {
			ich->listofcourse();
			break;
		}
		case 2: {
			string code;
			cout << "Enter Course Code:";
			cin >> code;
			Course* c = lms.findcourse(code);
			try {
				if (!c) {
					throw 1;
				}
				if (!c->studentisenroll(ich->Id)) {
					throw 2;
				}
				c->listmaterial();
			}
			catch (int error) {
				if (error == 1) {
					cout << "EXCEPTION: COURSE NOT FOUND\n";
				}
				else if (error == 2) {
					cout << "EXCEPTION: STUDENT IS NOT ENROLLED IN THIS COURSE\n";
				}
				else {
					cout << "EXCEPTION: An unknown error occurred while viewing materials.\n";
				}
			}
			break;
		}
		case 3: {
			string code;
			cout << "Enter Course Code:";
			cin >> code;
			Course* c = lms.findcourse(code);
			if (!c) {
				cout << "COURSE NOT FOUND\n";
			}
			if (!c->studentisenroll(ich->Id)) {
				cout << "STUDENT IS NOT ENROLLED\n";
			}
			c->listassignments();
			break;
		}
		case 4: {
			string code;
			cout << "Enter Course Code:";
			cin >> code;
			Course* c = lms.findcourse(code);
			if (!c) {
				cout << "COURSE NOT FOUND\n";
			}
			if (!c->studentisenroll(ich->Id)) {
				cout << "STUDENT IS NOT ENROLLED\n";
			}
			cout << "Enter Assignment ID:";
			string aid; cin >> ws; getline(cin, aid);
			cout << "Enter Content for Submission : \n";
			string content; getline(cin, content);
			Submission s(ich->getid(), content);
			c->addtosubmission(aid, s);
			cout << "Submission Completed\n";
			break;
		}
		case 5: {
			cout << "Logging Out\n";
			return;
		}
		default:
			cout << "Invalid Option\n";
			continue;
		}
	}
}
void Teacher::Dispmenu() {
	Teacher* ich = this;
	while (true) {
		cout << "----DASHBOARD FOR FACULTY (" << ich->getname() << ")----\n";
		cout << "1. List assigned courses\n";
		cout << "2. Upload material to course\n";
		cout << "3. Create assignment in course\n";
		cout << "4. View submissions for an assignment\n";
		cout << "5. Grade a submission\n";
		cout << "6. Logout\n";
		cout << "Choose an option: ";
		int ch;
		cin >> ch;
		switch (ch) {
		case 1: {
			int cc = lms.getcoursecount();
			for (int i = 0;i < cc;i++) {
				Course* c = lms.getcourse();
				if (c->getteacherid() == ich->getid()) {
					cout << *c << endl;
				}
				else cout << "Course not Assigned\n";
				break;
			}
		}
		case 2: {
			string code;
			cout << "Enter Course Code:";
			cin >> code;
			Course* c = lms.findcourse(code);
			if (!c) {
				cout << "COURSE NOT FOUND\n";
			}
			if (c->getteacherid() != ich->getid()) {
				cout << "NOT ASSIGNED TO THIS COURSE\n";
			}
			Material m;
			cin >> m;
			c->addmaterial(m);
			cout << "MATERIAL UPLOADED\n";
			ofstream fout("materials.txt", ios::app);
			if (!fout)cout << "file Not created ";
			fout << m.gettitle() << " " << m.getdesp() << endl;
			fout.close();
			cout << "Material saved permanently\n";
			break;
		}
		case 3: {
			string code;
			cout << "Enter Course Code:";
			cin >> code;
			Course* c = lms.findcourse(code);
			if (!c) {
				cout << "COURSE NOT FOUND\n";
			}
			if (c->getteacherid() != ich->getid()) {
				cout << "NOT ASSIGNED TO THIS COURSE\n";
			}
			Assignment a;
			cin >> a;
			c->createassignment(a);
			cout << "ASSIGNMENT CREATED\n";
			ofstream fout("Assignments.txt", ios::app);
			if (!fout)cout << "file Not created ";
			fout << a.getid() << " " << a.gettitle() << " " << a.getdescription() << " " << a.getduedate() << endl;
			fout.close();
			cout << "Assignment saved permanently\n";
			break;
		}
		case 4: {
			string code;
			cout << "Enter Course Code:";
			cin >> code;
			Course* c = lms.findcourse(code);
			if (!c) {
				cout << "COURSE NOT FOUND\n";
			}
			if (c->getteacherid() != ich->getid()) {
				cout << "NOT ASSIGNED TO THIS COURSE\n";
			}
			string aid;
			cout << "Enter Assignment ID : ";
			cin >> aid;
			c->showassigsubmission(aid);
			break;
		}
		case 5: {
			string code;
			cout << "Enter Course Code:";
			cin >> code;
			Course* c = lms.findcourse(code);
			if (!c) {
				cout << "COURSE NOT FOUND\n";
			}
			if (c->getteacherid() != ich->getid()) {
				cout << "NOT ASSIGNED TO THIS COURSE\n";
			}
			string aid;
			cout << "Enter Assignment ID : ";
			cin >> aid;
			c->showassigsubmission(aid);
			int ind;string grade;
			cout << "Enter Submission Index to be Graded: ";
			cin >> ind;ind--;//0 array index conversion;
			cout << "Enter Grade for Assignment : ";
			cin >> grade;
			c->gradeassignment(aid, ind, grade);
			cout << "Graded";
			ofstream fout("Grades.txt", ios::app);
			if (!fout)cout << "file Not created ";
			fout << aid << " " << ind << " " << grade << endl;
			fout.close();
			cout << "Assignment saved permanently\n";
			break;
		}
		case 6: {
			cout << "Logging out\n";
			return;
		}
		default:
			cout << "Invalid Option\n";
			continue;
		}
	}
}
void Admin::Dispmenu() {
	Admin* ich = this;
	while (true) {
		cout << "----DASHBOARD FOR ADMIN (" << ich->getname() << ")----\n";
		cout << "1. Create Student\n";
		cout << "2. Create Teacher\n";
		cout << "3. Create Course\n";
		cout << "4. Assign Teacher to Course\n";
		cout << "5. Enroll Student to Course\n";
		cout << "6. List all Courses\n";
		cout << "7. List all Students\n";
		cout << "8. List all Teachers\n";
		cout << "9. Logout\n";
		cout << "Choose an option: ";
		int ch;
		cin >> ch;
		switch (ch) {
		case 1: {
			lms.createstudent();
			break;
		}
		case 2: {
			lms.createteacher();
			break;
		}
		case 3: {
			lms.createcourse();
			break;
		}
		case 4: {
			lms.assigncoursetoteacher();
			break;
		}
		case 5: {
			lms.enrollstudenttocourse();
			break;
		}
		case 6: {
			lms.listcourses();
			break;
		}
		case 7: {
			lms.liststudents();
			break;
		}
		case 8: {
			lms.listteachers();
			break;
		}
		case 9: {
			cout << "Logged Out\n";
			return;
		}
		default:
			cout << "Invalid Option\n";
			continue;
		}
	}
}