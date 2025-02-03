#include <iostream>
#include <string>
#include <algorithm> // برای sort
using namespace std;

// ساختمان برای دروس رشته صنایع
struct Sub_ISE {
    string name_of_sub;
    double score;
    int courseID;

    Sub_ISE() : name_of_sub(""), score(0), courseID(0) {}
    Sub_ISE(string e, double f, int g) : name_of_sub(e), score(f), courseID(g) {}
};

// ساختمان برای دروس رشته کامپیوتر
struct Sub_IT {
    string name_of_sub;
    double score;
    int courseID;

    Sub_IT() : name_of_sub(""), score(0), courseID(0) {}
    Sub_IT(string e, double f, int g) : name_of_sub(e), score(f), courseID(g) {}
};

// ساختمان برای اطلاعات دانشجویان
struct Student {
    string firstName;
    string lastName;
    string major;
    int studentID;
    double GPA;

    Sub_ISE subISE[6];
    Sub_IT subIT[6];

    Student() : firstName(""), lastName(""), major(""), studentID(0), GPA(0) {}

    Student(string a, string b, string c, int d, Sub_ISE s1, Sub_ISE s2, Sub_ISE s3, Sub_ISE s4, Sub_ISE s5, Sub_ISE s6)
        : firstName(a), lastName(b), major(c), studentID(d), subISE{ s1, s2, s3, s4, s5, s6 } {
        calculate_GPA();
    }

    Student(string a, string b, string c, int d, Sub_IT s1, Sub_IT s2, Sub_IT s3, Sub_IT s4, Sub_IT s5, Sub_IT s6)
        : firstName(a), lastName(b), major(c), studentID(d), subIT{ s1, s2, s3, s4, s5, s6 } {
        calculate_GPA();
    }

    // محاسبه معدل بر اساس نمره و تعداد واحد هر درس
    void calculate_GPA() {
        double totalWeightedScore = 0;
        int totalCourseUnits = 0;

        if (major == "ISE") {
            for (int i = 0; i < 6; i++) {
                totalWeightedScore += subISE[i].score * subISE[i].courseID;
                totalCourseUnits += subISE[i].courseID;
            }
        } else if (major == "IT") {
            for (int i = 0; i < 6; i++) {
                totalWeightedScore += subIT[i].score * subIT[i].courseID;
                totalCourseUnits += subIT[i].courseID;
            }
        }

        GPA = (totalCourseUnits > 0) ? (totalWeightedScore / totalCourseUnits) : 0;
    }

    // نمایش اطلاعات دانشجو
    void displaying_info() {
        cout << "Student: " << firstName << " " << lastName << ", Major: " << major << ", ID: " << studentID << ", GPA: " << GPA << endl;
        cout << "---------------------------------------\n";
    }

    // ویرایش اطلاعات دانشجو
    void edit_info() {
        cout << "\033[36mEdit First Name: ";
        getline(cin, firstName);
        cout << "\033[36mEdit Last Name: ";
        getline(cin, lastName);
        cout << "\033[36mEdit Major (ISE/IT): ";
        getline(cin, major);
        cout << "\033[36mEdit Student ID: ";
        cin >> studentID;
        cin.ignore();

        if (major == "ISE") {
            for (int j = 0; j < 6; j++) {
                string subject;
                double score;
                int courseID;
                cout << "\033[33mEnter details for course " << (j + 1) << ":\n";
                cout << "Course Name: ";
                getline(cin, subject);
                cout << "Course Score: ";
                cin >> score;
                cout << "Course ID (units): ";
                cin >> courseID;
                cin.ignore();
                subISE[j] = Sub_ISE(subject, score, courseID);
            }
        } else if (major == "IT") {
            for (int j = 0; j < 6; j++) {
                string subject;
                double score;
                int courseID;
                cout << "\033[33mEnter details for course " << (j + 1) << ":\n";
                cout << "Course Name: ";
                getline(cin, subject);
                cout << "Course Score: ";
                cin >> score;
                cout << "Course ID (units): ";
                cin >> courseID;
                cin.ignore();
                subIT[j] = Sub_IT(subject, score, courseID);
            }
        }
        calculate_GPA();
    }

};
 // ** تابع حذف دانشجو **
    void delete_student(Student*& students, int& numStudents, int studentID) {
        int index = -1;
        for (int i = 0; i < numStudents; i++) {
                if (students[i].studentID == studentID) {
                    index = i;
        break;
        }
    }

    if (index != -1) { // اگر دانشجو پیدا شد
        for (int i = index; i < numStudents - 1; i++) {
            students[i] = students[i + 1]; // جابجایی عناصر
        }
        numStudents--;

        // تخصیص دوباره حافظه برای دانشجویان جدید
        Student* newStudents = new Student[numStudents];
        for (int i = 0; i < numStudents; i++) {
            newStudents[i] = students[i];
        }
        delete[] students;
        students = newStudents;

        cout << "Student with ID " << studentID << " has been deleted.\n";
    } else {
        cout << "Student not found.\n";
    }
}
int main() {
    int numStudents;
    cout << "\033[34mEnter number of students: ";
    cin >> numStudents;
    cin.ignore();

    Student* students = new Student[numStudents];

    for (int i = 0; i < numStudents; i++) {
        string firstName, lastName, major;
        int studentID;

        cout << "\033[32mEnter details for student " << (i + 1) << ":\n";
        cout << "\033[36mFirst Name: ";
        getline(cin, firstName);
        cout << "\033[36mLast Name: ";
        getline(cin, lastName);
        cout << "\033[36mMajor (ISE/IT): ";
        getline(cin, major);
        cout << "\033[36mStudent ID: ";
        cin >> studentID;
        cin.ignore();

        if (major == "ISE") {
            Sub_ISE subISE[6];
            for (int j = 0; j < 6; j++) {
                string subject;
                double score;
                int courseID;

                cout << "\033[33mEnter details for course " << (j + 1) << ":\n";
                cout << "Course Name: ";
                getline(cin, subject);
                cout << "Course Score: ";
                cin >> score;
                cout << "Course ID (units): ";
                cin >> courseID;
                cin.ignore();

                subISE[j] = Sub_ISE(subject, score, courseID);
            }
            students[i] = Student(firstName, lastName, major, studentID, subISE[0], subISE[1], subISE[2], subISE[3], subISE[4], subISE[5]);
        } else if (major == "IT") {
            Sub_IT subIT[6];
            for (int j = 0; j < 6; j++) {
                string subject;
                double score;
                int courseID;

                cout << "\033[33mEnter details for course " << (j + 1) << ":\n";
                cout << "Course Name: ";
                getline(cin, subject);
                cout << "Course Score: ";
                cin >> score;
                cout << "Course ID (units): ";
                cin >> courseID;
                cin.ignore();

                subIT[j] = Sub_IT(subject, score, courseID);
            }
            students[i] = Student(firstName, lastName, major, studentID, subIT[0], subIT[1], subIT[2], subIT[3], subIT[4], subIT[5]);
        }
    }

    // مرتب‌سازی بر اساس رشته و سپس معدل (از بیشترین به کمترین)
    sort(students, students + numStudents, [](const Student& a, const Student& b) {
        if (a.major == b.major) {
            return a.GPA > b.GPA; // اگر رشته یکسان است، معدل را مقایسه کن
        }
        return a.major < b.major; // رشته را به ترتیب الفبایی مرتب کن (ISE قبل از IT)
    });

    // نمایش اطلاعات دانشجویان پس از مرتب‌سازی
    cout << "\nSorted Students List:\n";
    for (int i = 0; i < numStudents; i++) {
        students[i].displaying_info();
    }

    int choice;
    cout << "\nDo you want to edit or delete a student? (1 = Edit, 2 = Delete, 0 = No): ";
    cin >> choice;
    if (choice == 1) {
        int studentID;
        cout << "\nEnter Student ID to edit: ";
        cin >> studentID;
        cin.ignore();

        for (int i = 0; i < numStudents; i++) {
            if (students[i].studentID == studentID) {
                students[i].edit_info();
                break;
                }
            }
        }else if (choice == 2){
             int studentID;
             cout << "\nEnter Student ID to delete: ";
             cin >> studentID;
             cin.ignore();
             delete_student(students, numStudents, studentID);
        }

     if (choice != 0){
           // نمایش لیست جدید دانشجویان
           cout << "\nUpdated Student List:\n";
           for (int i = 0; i < numStudents; i++) {
                students[i].displaying_info();
           }
           }


    // آزادسازی حافظه
    delete[] students;

    return 0;
}
