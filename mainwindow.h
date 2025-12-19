#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QTableWidget>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>
#include <QMessageBox>

// Forward declarations for LMS classes
class User;
class LMS;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // Login Page
    void onLoginButtonClicked();

    // Admin Dashboard
    void onCreateStudentClicked();
    void onCreateTeacherClicked();
    void onCreateCourseClicked();
    void onAssignCourseTeacherClicked();
    void onEnrollStudentCourseClicked();
    void onListCoursesClicked();
    void onListStudentsClicked();
    void onListTeachersClicked();
    void onAdminLogoutClicked();

    // Teacher Dashboard
    void onTeacherListCoursesClicked();
    void onUploadMaterialClicked();
    void onCreateAssignmentClicked();
    void onViewSubmissionsClicked();
    void onGradeSubmissionClicked();
    void onTeacherLogoutClicked();

    // Student Dashboard
    void onStudentViewCoursesClicked();
    void onViewMaterialsClicked();
    void onViewAssignmentsClicked();
    void onSubmitAssignmentClicked();
    void onStudentLogoutClicked();

private:
    void setupLoginPage();
    void setupAdminDashboard();
    void setupTeacherDashboard();
    void setupStudentDashboard();
    void showMessage(const QString& message, bool isError = false);
    void switchToPage(int index);

    // LMS System
    LMS* lms;

    // Current user
    User* currentUser;

    // UI Components
    QStackedWidget *stackedWidget;

    // Login Page Widgets
    QWidget *loginPage;
    QComboBox *userTypeCombo;
    QLineEdit *loginIdEdit;
    QLineEdit *loginPasswordEdit;
    QPushButton *loginButton;

    // Admin Dashboard Widgets
    QWidget *adminPage;
    QTableWidget *adminTable;
    QPushButton *btnCreateStudent;
    QPushButton *btnCreateTeacher;
    QPushButton *btnCreateCourse;
    QPushButton *btnAssignCourseTeacher;
    QPushButton *btnEnrollStudent;
    QPushButton *btnListCourses;
    QPushButton *btnListStudents;
    QPushButton *btnListTeachers;
    QPushButton *btnAdminLogout;

    // Teacher Dashboard Widgets
    QWidget *teacherPage;
    QTableWidget *teacherTable;
    QPushButton *btnTeacherCourses;
    QPushButton *btnUploadMaterial;
    QPushButton *btnCreateAssignment;
    QPushButton *btnViewSubmissions;
    QPushButton *btnGradeSubmission;
    QPushButton *btnTeacherLogout;

    // Student Dashboard Widgets
    QWidget *studentPage;
    QTableWidget *studentTable;
    QPushButton *btnStudentCourses;
    QPushButton *btnViewMaterials;
    QPushButton *btnViewAssignments;
    QPushButton *btnSubmitAssignment;
    QPushButton *btnStudentLogout;
};

#endif // MAINWINDOW_H
