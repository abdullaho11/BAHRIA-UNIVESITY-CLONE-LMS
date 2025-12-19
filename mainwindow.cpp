#include "mainwindow.h"
#include "lms.h"  // ADD THIS LINE
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QHeaderView>
#include <QInputDialog>
#include <QFileDialog>
#include <QDateTime>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , lms(new LMS())
    , currentUser(nullptr)
{
    setWindowTitle("Bahria University LMS");
    setFixedSize(1000, 700);

    // Create stacked widget for different pages
    stackedWidget = new QStackedWidget(this);
    setCentralWidget(stackedWidget);

    // Setup all pages
    setupLoginPage();
    setupAdminDashboard();
    setupTeacherDashboard();
    setupStudentDashboard();

    // Show login page initially
    switchToPage(0);
}

MainWindow::~MainWindow()
{
    delete lms;
}

void MainWindow::setupLoginPage()
{
    loginPage = new QWidget();
    QVBoxLayout *mainLayout = new QVBoxLayout(loginPage);

    QLabel *titleLabel = new QLabel("BAHRIA UNIVERSITY LMS\n(Developed by Abdullah & Dur-e-Shahwar)");
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 18px; font-weight: bold; margin: 20px; color: #2c3e50;");

    QLabel *loginLabel = new QLabel("LOGIN");
    loginLabel->setAlignment(Qt::AlignCenter);
    loginLabel->setStyleSheet("font-size: 16px; margin: 10px; color: #34495e;");

    QWidget *formWidget = new QWidget();
    QFormLayout *formLayout = new QFormLayout(formWidget);

    userTypeCombo = new QComboBox();
    userTypeCombo->addItem("Admin");
    userTypeCombo->addItem("Teacher");
    userTypeCombo->addItem("Student");
    userTypeCombo->setStyleSheet("padding: 5px;");

    loginIdEdit = new QLineEdit();
    loginIdEdit->setPlaceholderText("Enter ID");
    loginIdEdit->setStyleSheet("padding: 5px;");

    loginPasswordEdit = new QLineEdit();
    loginPasswordEdit->setPlaceholderText("Enter password");
    loginPasswordEdit->setEchoMode(QLineEdit::Password);
    loginPasswordEdit->setStyleSheet("padding: 5px;");

    formLayout->addRow("User Type:", userTypeCombo);
    formLayout->addRow("ID:", loginIdEdit);
    formLayout->addRow("Password:", loginPasswordEdit);

    loginButton = new QPushButton("Login");
    loginButton->setFixedSize(100, 30);
    loginButton->setStyleSheet("QPushButton { background-color: #3498db; color: white; border: none; border-radius: 5px; }"
                               "QPushButton:hover { background-color: #2980b9; }");

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    buttonLayout->addWidget(loginButton);
    buttonLayout->addStretch();

    mainLayout->addStretch();
    mainLayout->addWidget(titleLabel);
    mainLayout->addWidget(loginLabel);
    mainLayout->addWidget(formWidget, 0, Qt::AlignCenter);
    mainLayout->addLayout(buttonLayout);
    mainLayout->addStretch();

    connect(loginButton, &QPushButton::clicked, this, &MainWindow::onLoginButtonClicked);

    stackedWidget->addWidget(loginPage);
}

void MainWindow::setupAdminDashboard()
{
    adminPage = new QWidget();
    QVBoxLayout *mainLayout = new QVBoxLayout(adminPage);

    QLabel *titleLabel = new QLabel("Admin Dashboard");
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 18px; font-weight: bold; margin: 10px; color: #2c3e50;");

    // Button Layout
    QGridLayout *buttonGrid = new QGridLayout();
    btnCreateStudent = new QPushButton("Create Student");
    btnCreateTeacher = new QPushButton("Create Teacher");
    btnCreateCourse = new QPushButton("Create Course");
    btnAssignCourseTeacher = new QPushButton("Assign Course to Teacher");
    btnEnrollStudent = new QPushButton("Enroll Student to Course");
    btnListCourses = new QPushButton("List All Courses");
    btnListStudents = new QPushButton("List All Students");
    btnListTeachers = new QPushButton("List All Teachers");
    btnAdminLogout = new QPushButton("Logout");

    // Set button styles
    QString buttonStyle = "QPushButton { background-color: #2ecc71; color: white; border: none; border-radius: 5px; padding: 8px; margin: 2px; }"
                          "QPushButton:hover { background-color: #27ae60; }";
    btnAdminLogout->setStyleSheet("QPushButton { background-color: #e74c3c; color: white; border: none; border-radius: 5px; padding: 8px; margin: 2px; }"
                                  "QPushButton:hover { background-color: #c0392b; }");

    btnCreateStudent->setStyleSheet(buttonStyle);
    btnCreateTeacher->setStyleSheet(buttonStyle);
    btnCreateCourse->setStyleSheet(buttonStyle);
    btnAssignCourseTeacher->setStyleSheet(buttonStyle);
    btnEnrollStudent->setStyleSheet(buttonStyle);
    btnListCourses->setStyleSheet(buttonStyle);
    btnListStudents->setStyleSheet(buttonStyle);
    btnListTeachers->setStyleSheet(buttonStyle);

    buttonGrid->addWidget(btnCreateStudent, 0, 0);
    buttonGrid->addWidget(btnCreateTeacher, 0, 1);
    buttonGrid->addWidget(btnCreateCourse, 0, 2);
    buttonGrid->addWidget(btnAssignCourseTeacher, 1, 0);
    buttonGrid->addWidget(btnEnrollStudent, 1, 1);
    buttonGrid->addWidget(btnListCourses, 1, 2);
    buttonGrid->addWidget(btnListStudents, 2, 0);
    buttonGrid->addWidget(btnListTeachers, 2, 1);
    buttonGrid->addWidget(btnAdminLogout, 2, 2);

    // Table for displaying data
    adminTable = new QTableWidget();
    adminTable->setColumnCount(5);
    adminTable->setHorizontalHeaderLabels({"ID", "Name", "Type", "Details", "Actions"});
    adminTable->horizontalHeader()->setStretchLastSection(true);
    adminTable->setStyleSheet("QTableWidget { background-color: white; alternate-background-color: #f8f9fa; }"
                              "QHeaderView::section { background-color: #3498db; color: white; }");

    mainLayout->addWidget(titleLabel);
    mainLayout->addLayout(buttonGrid);
    mainLayout->addWidget(adminTable);

    // Connect signals
    connect(btnCreateStudent, &QPushButton::clicked, this, &MainWindow::onCreateStudentClicked);
    connect(btnCreateTeacher, &QPushButton::clicked, this, &MainWindow::onCreateTeacherClicked);
    connect(btnCreateCourse, &QPushButton::clicked, this, &MainWindow::onCreateCourseClicked);
    connect(btnAssignCourseTeacher, &QPushButton::clicked, this, &MainWindow::onAssignCourseTeacherClicked);
    connect(btnEnrollStudent, &QPushButton::clicked, this, &MainWindow::onEnrollStudentCourseClicked);
    connect(btnListCourses, &QPushButton::clicked, this, &MainWindow::onListCoursesClicked);
    connect(btnListStudents, &QPushButton::clicked, this, &MainWindow::onListStudentsClicked);
    connect(btnListTeachers, &QPushButton::clicked, this, &MainWindow::onListTeachersClicked);
    connect(btnAdminLogout, &QPushButton::clicked, this, &MainWindow::onAdminLogoutClicked);

    stackedWidget->addWidget(adminPage);
}

void MainWindow::setupTeacherDashboard()
{
    teacherPage = new QWidget();
    QVBoxLayout *mainLayout = new QVBoxLayout(teacherPage);

    QLabel *titleLabel = new QLabel("Teacher Dashboard");
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 18px; font-weight: bold; margin: 10px; color: #2c3e50;");

    // Button Layout
    QGridLayout *buttonGrid = new QGridLayout();
    btnTeacherCourses = new QPushButton("List Assigned Courses");
    btnUploadMaterial = new QPushButton("Upload Material");
    btnCreateAssignment = new QPushButton("Create Assignment");
    btnViewSubmissions = new QPushButton("View Submissions");
    btnGradeSubmission = new QPushButton("Grade Submission");
    btnTeacherLogout = new QPushButton("Logout");

    QString buttonStyle = "QPushButton { background-color: #9b59b6; color: white; border: none; border-radius: 5px; padding: 8px; margin: 2px; }"
                          "QPushButton:hover { background-color: #8e44ad; }";
    btnTeacherLogout->setStyleSheet("QPushButton { background-color: #e74c3c; color: white; border: none; border-radius: 5px; padding: 8px; margin: 2px; }"
                                    "QPushButton:hover { background-color: #c0392b; }");

    btnTeacherCourses->setStyleSheet(buttonStyle);
    btnUploadMaterial->setStyleSheet(buttonStyle);
    btnCreateAssignment->setStyleSheet(buttonStyle);
    btnViewSubmissions->setStyleSheet(buttonStyle);
    btnGradeSubmission->setStyleSheet(buttonStyle);

    buttonGrid->addWidget(btnTeacherCourses, 0, 0);
    buttonGrid->addWidget(btnUploadMaterial, 0, 1);
    buttonGrid->addWidget(btnCreateAssignment, 0, 2);
    buttonGrid->addWidget(btnViewSubmissions, 1, 0);
    buttonGrid->addWidget(btnGradeSubmission, 1, 1);
    buttonGrid->addWidget(btnTeacherLogout, 1, 2);

    // Table for displaying data
    teacherTable = new QTableWidget();
    teacherTable->setColumnCount(5);
    teacherTable->setHorizontalHeaderLabels({"Course Code", "Course Name", "Students", "Assignments", "Actions"});
    teacherTable->horizontalHeader()->setStretchLastSection(true);
    teacherTable->setStyleSheet("QTableWidget { background-color: white; alternate-background-color: #f8f9fa; }"
                                "QHeaderView::section { background-color: #9b59b6; color: white; }");

    mainLayout->addWidget(titleLabel);
    mainLayout->addLayout(buttonGrid);
    mainLayout->addWidget(teacherTable);

    // Connect signals
    connect(btnTeacherCourses, &QPushButton::clicked, this, &MainWindow::onTeacherListCoursesClicked);
    connect(btnUploadMaterial, &QPushButton::clicked, this, &MainWindow::onUploadMaterialClicked);
    connect(btnCreateAssignment, &QPushButton::clicked, this, &MainWindow::onCreateAssignmentClicked);
    connect(btnViewSubmissions, &QPushButton::clicked, this, &MainWindow::onViewSubmissionsClicked);
    connect(btnGradeSubmission, &QPushButton::clicked, this, &MainWindow::onGradeSubmissionClicked);
    connect(btnTeacherLogout, &QPushButton::clicked, this, &MainWindow::onTeacherLogoutClicked);

    stackedWidget->addWidget(teacherPage);
}

void MainWindow::setupStudentDashboard()
{
    studentPage = new QWidget();
    QVBoxLayout *mainLayout = new QVBoxLayout(studentPage);

    QLabel *titleLabel = new QLabel("Student Dashboard");
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 18px; font-weight: bold; margin: 10px; color: #2c3e50;");

    // Button Layout
    QGridLayout *buttonGrid = new QGridLayout();
    btnStudentCourses = new QPushButton("View Enrolled Courses");
    btnViewMaterials = new QPushButton("View Course Materials");
    btnViewAssignments = new QPushButton("View Assignments");
    btnSubmitAssignment = new QPushButton("Submit Assignment");
    btnStudentLogout = new QPushButton("Logout");

    QString buttonStyle = "QPushButton { background-color: #e67e22; color: white; border: none; border-radius: 5px; padding: 8px; margin: 2px; }"
                          "QPushButton:hover { background-color: #d35400; }";
    btnStudentLogout->setStyleSheet("QPushButton { background-color: #e74c3c; color: white; border: none; border-radius: 5px; padding: 8px; margin: 2px; }"
                                    "QPushButton:hover { background-color: #c0392b; }");

    btnStudentCourses->setStyleSheet(buttonStyle);
    btnViewMaterials->setStyleSheet(buttonStyle);
    btnViewAssignments->setStyleSheet(buttonStyle);
    btnSubmitAssignment->setStyleSheet(buttonStyle);

    buttonGrid->addWidget(btnStudentCourses, 0, 0);
    buttonGrid->addWidget(btnViewMaterials, 0, 1);
    buttonGrid->addWidget(btnViewAssignments, 0, 2);
    buttonGrid->addWidget(btnSubmitAssignment, 1, 0);
    buttonGrid->addWidget(btnStudentLogout, 1, 1);

    // Table for displaying data
    studentTable = new QTableWidget();
    studentTable->setColumnCount(4);
    studentTable->setHorizontalHeaderLabels({"Course Code", "Course Name", "Teacher", "Actions"});
    studentTable->horizontalHeader()->setStretchLastSection(true);
    studentTable->setStyleSheet("QTableWidget { background-color: white; alternate-background-color: #f8f9fa; }"
                                "QHeaderView::section { background-color: #e67e22; color: white; }");

    mainLayout->addWidget(titleLabel);
    mainLayout->addLayout(buttonGrid);
    mainLayout->addWidget(studentTable);

    // Connect signals
    connect(btnStudentCourses, &QPushButton::clicked, this, &MainWindow::onStudentViewCoursesClicked);
    connect(btnViewMaterials, &QPushButton::clicked, this, &MainWindow::onViewMaterialsClicked);
    connect(btnViewAssignments, &QPushButton::clicked, this, &MainWindow::onViewAssignmentsClicked);
    connect(btnSubmitAssignment, &QPushButton::clicked, this, &MainWindow::onSubmitAssignmentClicked);
    connect(btnStudentLogout, &QPushButton::clicked, this, &MainWindow::onStudentLogoutClicked);

    stackedWidget->addWidget(studentPage);
}

// ==================== SLOT IMPLEMENTATIONS ====================

void MainWindow::onLoginButtonClicked()
{
    QString userType = userTypeCombo->currentText();
    QString id = loginIdEdit->text().trimmed();
    QString password = loginPasswordEdit->text();

    if (id.isEmpty() || password.isEmpty()) {
        showMessage("Please enter both ID and password", true);
        return;
    }

    if (userType == "Admin") {
        currentUser = lms->loginadmin(id.toStdString(), password.toStdString());
    } else if (userType == "Teacher") {
        currentUser = lms->loginteacher(id.toStdString(), password.toStdString());
    } else if (userType == "Student") {
        currentUser = lms->loginstudent(id.toStdString(), password.toStdString());
    }

    if (currentUser) {
        if (userType == "Admin") {
            switchToPage(1); // Admin dashboard
            showMessage("Welcome Admin! Login successful!");
        } else if (userType == "Teacher") {
            switchToPage(2); // Teacher dashboard
            showMessage("Welcome Teacher! Login successful!");
        } else if (userType == "Student") {
            switchToPage(3); // Student dashboard
            showMessage("Welcome Student! Login successful!");
        }
        loginIdEdit->clear();
        loginPasswordEdit->clear();
    } else {
        showMessage("Invalid credentials. Please try again.", true);
    }
}

void MainWindow::onCreateStudentClicked()
{
    bool ok;
    QString name = QInputDialog::getText(this, "Create Student", "Enter Student Name:",
                                         QLineEdit::Normal, "", &ok);
    if (!ok || name.isEmpty()) return;

    QString id = QInputDialog::getText(this, "Create Student", "Enter Student ID:",
                                       QLineEdit::Normal, "", &ok);
    if (!ok || id.isEmpty()) return;

    QString password = QInputDialog::getText(this, "Create Student", "Enter Password:",
                                             QLineEdit::Normal, "", &ok);
    if (!ok || password.isEmpty()) return;

    QString program = QInputDialog::getText(this, "Create Student", "Enter Program:",
                                            QLineEdit::Normal, "", &ok);
    if (!ok || program.isEmpty()) return;

    Student student(name.toStdString(), id.toStdString(), password.toStdString(), program.toStdString());
    lms->addstudent(student);
    showMessage("Student created successfully!");
}

void MainWindow::onCreateTeacherClicked()
{
    bool ok;
    QString name = QInputDialog::getText(this, "Create Teacher", "Enter Teacher Name:",
                                         QLineEdit::Normal, "", &ok);
    if (!ok || name.isEmpty()) return;

    QString id = QInputDialog::getText(this, "Create Teacher", "Enter Teacher ID:",
                                       QLineEdit::Normal, "", &ok);
    if (!ok || id.isEmpty()) return;

    QString password = QInputDialog::getText(this, "Create Teacher", "Enter Password:",
                                             QLineEdit::Normal, "", &ok);
    if (!ok || password.isEmpty()) return;

    QString department = QInputDialog::getText(this, "Create Teacher", "Enter Department:",
                                               QLineEdit::Normal, "", &ok);
    if (!ok || department.isEmpty()) return;

    Teacher teacher(name.toStdString(), id.toStdString(), password.toStdString(), department.toStdString());
    lms->addteacher(teacher);
    showMessage("Teacher created successfully!");
}

void MainWindow::onCreateCourseClicked()
{
    bool ok;
    QString code = QInputDialog::getText(this, "Create Course", "Enter Course Code:",
                                         QLineEdit::Normal, "", &ok);
    if (!ok || code.isEmpty()) return;

    QString name = QInputDialog::getText(this, "Create Course", "Enter Course Name:",
                                         QLineEdit::Normal, "", &ok);
    if (!ok || name.isEmpty()) return;

    Course course(code.toStdString(), name.toStdString(), "");
    lms->addcourse(course);
    showMessage("Course created successfully!");
}

void MainWindow::onAssignCourseTeacherClicked()
{
    QString courseCode = QInputDialog::getText(this, "Assign Course", "Enter Course Code:");
    if (courseCode.isEmpty()) return;

    QString teacherId = QInputDialog::getText(this, "Assign Course", "Enter Teacher ID:");
    if (teacherId.isEmpty()) return;

    Course* course = lms->findcourse(courseCode.toStdString());
    Teacher* teacher = lms->findteacher(teacherId.toStdString());

    if (course && teacher) {
        course->assignteacher(teacherId.toStdString());
        showMessage("Course assigned to teacher successfully!");
    } else {
        showMessage("Course or teacher not found!", true);
    }
}

void MainWindow::onEnrollStudentCourseClicked()
{
    QString courseCode = QInputDialog::getText(this, "Enroll Student", "Enter Course Code:");
    if (courseCode.isEmpty()) return;

    QString studentId = QInputDialog::getText(this, "Enroll Student", "Enter Student ID:");
    if (studentId.isEmpty()) return;

    Course* course = lms->findcourse(courseCode.toStdString());
    Student* student = lms->findstudent(studentId.toStdString());

    if (course && student) {
        course->enrollstudent(studentId.toStdString());
        student->enrollcourse(courseCode.toStdString());
        showMessage("Student enrolled in course successfully!");
    } else {
        showMessage("Course or student not found!", true);
    }
}

void MainWindow::onListCoursesClicked()
{
    adminTable->clearContents();
    adminTable->setRowCount(0);

    Course* courses = lms->getcourse();
    int count = lms->getcoursecount();

    adminTable->setRowCount(count);
    for (int i = 0; i < count; i++) {
        adminTable->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(courses[i].getcoursecode())));
        adminTable->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(courses[i].getcoursename())));
        adminTable->setItem(i, 2, new QTableWidgetItem("Course"));
        adminTable->setItem(i, 3, new QTableWidgetItem(QString("Teacher: %1").arg(QString::fromStdString(courses[i].getteacherid()))));

        QPushButton *viewBtn = new QPushButton("View");
        adminTable->setCellWidget(i, 4, viewBtn);
    }

    showMessage(QString("Listed %1 courses").arg(count));
}

void MainWindow::onListStudentsClicked()
{
    adminTable->clearContents();
    adminTable->setRowCount(0);

    Student* students = lms->getstudent();
    int count = lms->getstudentcount();

    adminTable->setRowCount(count);
    for (int i = 0; i < count; i++) {
        adminTable->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(students[i].getid())));
        adminTable->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(students[i].getname())));
        adminTable->setItem(i, 2, new QTableWidgetItem("Student"));
        adminTable->setItem(i, 3, new QTableWidgetItem(QString("Program: %1").arg(QString::fromStdString(students[i].getprogram()))));

        QPushButton *viewBtn = new QPushButton("View");
        adminTable->setCellWidget(i, 4, viewBtn);
    }

    showMessage(QString("Listed %1 students").arg(count));
}

void MainWindow::onListTeachersClicked()
{
    adminTable->clearContents();
    adminTable->setRowCount(0);

    Teacher* teachers = lms->getteacher();
    int count = lms->getteachercount();

    adminTable->setRowCount(count);
    for (int i = 0; i < count; i++) {
        adminTable->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(teachers[i].getid())));
        adminTable->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(teachers[i].getname())));
        adminTable->setItem(i, 2, new QTableWidgetItem("Teacher"));
        adminTable->setItem(i, 3, new QTableWidgetItem(QString("Dept: %1").arg(QString::fromStdString(teachers[i].getdepart()))));

        QPushButton *viewBtn = new QPushButton("View");
        adminTable->setCellWidget(i, 4, viewBtn);
    }

    showMessage(QString("Listed %1 teachers").arg(count));
}

void MainWindow::onTeacherListCoursesClicked()
{
    teacherTable->clearContents();
    teacherTable->setRowCount(0);

    QString teacherId = QString::fromStdString(currentUser->getid());
    Course* courses = lms->getcourse();
    int count = lms->getcoursecount();

    int row = 0;
    for (int i = 0; i < count; i++) {
        if (courses[i].getteacherid() == teacherId.toStdString()) {
            teacherTable->insertRow(row);
            teacherTable->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(courses[i].getcoursecode())));
            teacherTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(courses[i].getcoursename())));

            // Get enrolled student count
            int studentCount = 0;
            for (int j = 0; j < MAXSTUDENTS; j++) {
                if (!courses[i].getEnrolledStudent(j).empty()) {
                    studentCount++;
                }
            }

            teacherTable->setItem(row, 2, new QTableWidgetItem(QString::number(studentCount)));
            teacherTable->setItem(row, 3, new QTableWidgetItem(QString::number(courses[i].getAssignmentCount())));

            QPushButton *viewBtn = new QPushButton("View Details");
            teacherTable->setCellWidget(row, 4, viewBtn);
            row++;
        }
    }

    showMessage(QString("Found %1 assigned courses").arg(row));
}

void MainWindow::onUploadMaterialClicked()
{
    bool ok;
    QString courseCode = QInputDialog::getText(this, "Upload Material", "Enter Course Code:",
                                               QLineEdit::Normal, "", &ok);
    if (!ok || courseCode.isEmpty()) return;

    Course* course = lms->findcourse(courseCode.toStdString());
    if (!course || course->getteacherid() != currentUser->getid()) {
        showMessage("Course not found or not assigned to you!", true);
        return;
    }

    QString title = QInputDialog::getText(this, "Upload Material", "Enter Material Title:",
                                          QLineEdit::Normal, "", &ok);
    if (!ok || title.isEmpty()) return;

    QString description = QInputDialog::getText(this, "Upload Material", "Enter Description:",
                                                QLineEdit::Normal, "", &ok);
    if (!ok || description.isEmpty()) return;

    Material material(title.toStdString(), description.toStdString());
    course->addmaterial(material);
    showMessage("Material uploaded successfully!");
}

void MainWindow::onCreateAssignmentClicked()
{
    bool ok;
    QString courseCode = QInputDialog::getText(this, "Create Assignment", "Enter Course Code:",
                                               QLineEdit::Normal, "", &ok);
    if (!ok || courseCode.isEmpty()) return;

    Course* course = lms->findcourse(courseCode.toStdString());
    if (!course || course->getteacherid() != currentUser->getid()) {
        showMessage("Course not found or not assigned to you!", true);
        return;
    }

    QString id = QInputDialog::getText(this, "Create Assignment", "Enter Assignment ID:",
                                       QLineEdit::Normal, "", &ok);
    if (!ok || id.isEmpty()) return;

    QString title = QInputDialog::getText(this, "Create Assignment", "Enter Title:",
                                          QLineEdit::Normal, "", &ok);
    if (!ok || title.isEmpty()) return;

    QString description = QInputDialog::getText(this, "Create Assignment", "Enter Description:",
                                                QLineEdit::Normal, "", &ok);
    if (!ok || description.isEmpty()) return;

    QString dueDate = QInputDialog::getText(this, "Create Assignment", "Enter Due Date (YYYY-MM-DD):",
                                            QLineEdit::Normal, "", &ok);
    if (!ok || dueDate.isEmpty()) return;

    Assignment assignment(id.toStdString(), title.toStdString(), description.toStdString(), dueDate.toStdString());
    course->createassignment(assignment);
    showMessage("Assignment created successfully!");
}

void MainWindow::onViewSubmissionsClicked()
{
    bool ok;
    QString courseCode = QInputDialog::getText(this, "View Submissions", "Enter Course Code:",
                                               QLineEdit::Normal, "", &ok);
    if (!ok || courseCode.isEmpty()) return;

    QString assignmentId = QInputDialog::getText(this, "View Submissions", "Enter Assignment ID:",
                                                 QLineEdit::Normal, "", &ok);
    if (!ok || assignmentId.isEmpty()) return;

    Course* course = lms->findcourse(courseCode.toStdString());
    if (!course || course->getteacherid() != currentUser->getid()) {
        showMessage("Course not found or not assigned to you!", true);
        return;
    }

    showMessage("Viewing submissions for assignment: " + assignmentId);
}

void MainWindow::onGradeSubmissionClicked()
{
    bool ok;
    QString courseCode = QInputDialog::getText(this, "Grade Submission", "Enter Course Code:",
                                               QLineEdit::Normal, "", &ok);
    if (!ok || courseCode.isEmpty()) return;

    QString assignmentId = QInputDialog::getText(this, "Grade Submission", "Enter Assignment ID:",
                                                 QLineEdit::Normal, "", &ok);
    if (!ok || assignmentId.isEmpty()) return;

    QString studentId = QInputDialog::getText(this, "Grade Submission", "Enter Student ID:",
                                              QLineEdit::Normal, "", &ok);
    if (!ok || studentId.isEmpty()) return;

    QString grade = QInputDialog::getText(this, "Grade Submission", "Enter Grade:",
                                          QLineEdit::Normal, "", &ok);
    if (!ok || grade.isEmpty()) return;

    Course* course = lms->findcourse(courseCode.toStdString());
    if (!course || course->getteacherid() != currentUser->getid()) {
        showMessage("Course not found or not assigned to you!", true);
        return;
    }

    showMessage("Grade submitted for student " + studentId + ": " + grade);
}

void MainWindow::onStudentViewCoursesClicked()
{
    studentTable->clearContents();
    studentTable->setRowCount(0);

    Student* student = dynamic_cast<Student*>(currentUser);
    if (!student) return;

    Course* courses = lms->getcourse();
    int count = lms->getcoursecount();

    int row = 0;
    for (int i = 0; i < count; i++) {
        string courseCode = courses[i].getcoursecode();
        if (student->courseisenroll(courseCode)) {
            studentTable->insertRow(row);
            studentTable->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(courses[i].getcoursecode())));
            studentTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(courses[i].getcoursename())));
            studentTable->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(courses[i].getteacherid())));

            QPushButton *viewBtn = new QPushButton("View Details");
            studentTable->setCellWidget(row, 3, viewBtn);
            row++;
        }
    }

    if (row == 0) {
        showMessage("You are not enrolled in any courses.", true);
    } else {
        showMessage(QString("You are enrolled in %1 courses").arg(row));
    }
}

void MainWindow::onViewMaterialsClicked()
{
    bool ok;
    QString courseCode = QInputDialog::getText(this, "View Materials", "Enter Course Code:",
                                               QLineEdit::Normal, "", &ok);
    if (!ok || courseCode.isEmpty()) return;

    Course* course = lms->findcourse(courseCode.toStdString());
    if (!course) {
        showMessage("Course not found!", true);
        return;
    }

    Student* student = dynamic_cast<Student*>(currentUser);
    if (!student) return;

    string courseCodeStr = courseCode.toStdString();
    if (!student->courseisenroll(courseCodeStr)) {
        showMessage("You are not enrolled in this course!", true);
        return;
    }

    showMessage("Viewing materials for course: " + courseCode);
}

void MainWindow::onViewAssignmentsClicked()
{
    bool ok;
    QString courseCode = QInputDialog::getText(this, "View Assignments", "Enter Course Code:",
                                               QLineEdit::Normal, "", &ok);
    if (!ok || courseCode.isEmpty()) return;

    Course* course = lms->findcourse(courseCode.toStdString());
    if (!course) {
        showMessage("Course not found!", true);
        return;
    }

    Student* student = dynamic_cast<Student*>(currentUser);
    if (!student) return;

    string courseCodeStr = courseCode.toStdString();
    if (!student->courseisenroll(courseCodeStr)) {
        showMessage("You are not enrolled in this course!", true);
        return;
    }

    showMessage("Viewing assignments for course: " + courseCode);
}

void MainWindow::onSubmitAssignmentClicked()
{
    bool ok;
    QString courseCode = QInputDialog::getText(this, "Submit Assignment", "Enter Course Code:",
                                               QLineEdit::Normal, "", &ok);
    if (!ok || courseCode.isEmpty()) return;

    QString assignmentId = QInputDialog::getText(this, "Submit Assignment", "Enter Assignment ID:",
                                                 QLineEdit::Normal, "", &ok);
    if (!ok || assignmentId.isEmpty()) return;

    QString content = QInputDialog::getText(this, "Submit Assignment", "Enter Submission Content:",
                                            QLineEdit::Normal, "", &ok);
    if (!ok || content.isEmpty()) return;

    Course* course = lms->findcourse(courseCode.toStdString());
    if (!course) {
        showMessage("Course not found!", true);
        return;
    }

    Student* student = dynamic_cast<Student*>(currentUser);
    if (!student) return;

    string courseCodeStr = courseCode.toStdString();
    if (!student->courseisenroll(courseCodeStr)) {
        showMessage("You are not enrolled in this course!", true);
        return;
    }

    Submission submission(currentUser->getid(), content.toStdString());
    course->addtosubmission(assignmentId.toStdString(), submission);
    showMessage("Assignment submitted successfully!");
}

// ==================== LOGOUT FUNCTIONS ====================

void MainWindow::onAdminLogoutClicked()
{
    currentUser = nullptr;
    switchToPage(0);
    showMessage("Logged out successfully!");
}

void MainWindow::onTeacherLogoutClicked()
{
    currentUser = nullptr;
    switchToPage(0);
    showMessage("Logged out successfully!");
}

void MainWindow::onStudentLogoutClicked()
{
    currentUser = nullptr;
    switchToPage(0);
    showMessage("Logged out successfully!");
}

// ==================== HELPER FUNCTIONS ====================

void MainWindow::switchToPage(int index)
{
    stackedWidget->setCurrentIndex(index);
    if (index == 0) {
        setWindowTitle("Bahria University LMS - Login");
    } else if (index == 1) {
        setWindowTitle("Bahria University LMS - Admin Dashboard");
    } else if (index == 2) {
        setWindowTitle("Bahria University LMS - Teacher Dashboard");
    } else if (index == 3) {
        setWindowTitle("Bahria University LMS - Student Dashboard");
    }
}

void MainWindow::showMessage(const QString& message, bool isError)
{
    QMessageBox msgBox;
    msgBox.setText(message);
    if (isError) {
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setWindowTitle("Error");
        msgBox.setStyleSheet("QMessageBox { background-color: white; }");
    } else {
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setWindowTitle("Information");
        msgBox.setStyleSheet("QMessageBox { background-color: white; }");
    }
    msgBox.exec();
}
