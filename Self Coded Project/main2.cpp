#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

class Admin
{
public:
    string username = "admin";
    string password = "123";

    void showInfo()
    {
        cout << "Admin Username: " << username << ", Password: " << password << endl;
    }

    void editInfo()
    {
        cout << "Enter new username: ";
        cin >> username;
        cout << "Enter new password: ";
        cin >> password;
        cout << "Admin information updated!" << endl;
    }
};

class Class
{
public:
    string className;

    void showClasses()
    {
        ifstream file("classes.txt");
        if (!file.is_open())
        {
            cout << "No classes found!" << endl;
            return;
        }
        string line;
        while (getline(file, line))
        {
            cout << line << endl;
        }
        file.close();
    }

    void addClass()
    {
        cout << "Enter class name: ";
        cin >> className;
        ofstream file("classes.txt", ios::app);
        if (file.is_open())
        {
            file << className << endl;
            file.close();
            cout << "Class added!" << endl;
        }
    }

    void updateClass()
    {
        string oldClassName, newClassName;
        cout << "Enter the class name to update: ";
        cin >> oldClassName;
        cout << "Enter the new class name: ";
        cin >> newClassName;

        ifstream file("classes.txt");
        ofstream tempFile("temp.txt");
        string line;
        bool found = false;
        while (getline(file, line))
        {
            if (line == oldClassName)
            {
                tempFile << newClassName << endl;
                found = true;
            }
            else
            {
                tempFile << line << endl;
            }
        }
        file.close();
        tempFile.close();
        remove("classes.txt");
        rename("temp.txt", "classes.txt");

        if (found)
        {
            cout << "Class updated!" << endl;
        }
        else
        {
            cout << "Class not found!" << endl;
        }
    }

    void deleteClass()
    {
        string deleteClassName;
        cout << "Enter the class name to delete: ";
        cin >> deleteClassName;

        ifstream file("classes.txt");
        ofstream tempFile("temp.txt");
        string line;
        bool found = false;
        while (getline(file, line))
        {
            if (line == deleteClassName)
            {
                found = true;
            }
            else
            {
                tempFile << line << endl;
            }
        }
        file.close();
        tempFile.close();
        remove("classes.txt");
        rename("temp.txt", "classes.txt");

        if (found)
        {
            cout << "Class deleted!" << endl;
        }
        else
        {
            cout << "Class not found!" << endl;
        }
    }
};

class Teacher
{
public:
    string username, password, name, id, className;

    void registerTeacher()
    {
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;
        cout << "Enter name: ";
        cin >> name;
        cout << "Enter ID: ";
        cin >> id;
        cout << "Choose class: " << endl;
        Class cls;
        cls.showClasses();
        cin >> className;
        ofstream file("teachers.txt", ios::app);
        if (file.is_open())
        {
            file << username << " " << password << " " << name << " " << id << " " << className << endl;
            file.close();
            cout << "Teacher registered!" << endl;
        }
    }

    void showTeachers()
    {
        ifstream file("teachers.txt");
        if (!file.is_open())
        {
            cout << "No teachers found!" << endl;
            return;
        }
        string line;
        while (getline(file, line))
        {
            cout << line << endl;
        }
        file.close();
    }

    void updateTeacher()
    {
        string searchUsername;
        cout << "Enter teacher username to update: ";
        cin >> searchUsername;

        ifstream inFile("teachers.txt");
        ofstream outFile("temp.txt");
        string line, newUsername, newPassword, newName, newId, newClassName;
        bool found = false;
        while (getline(inFile, line))
        {
            size_t pos = line.find(' ');
            string currentUsername = line.substr(0, pos);
            if (currentUsername == searchUsername)
            {
                found = true;
                cout << "1. Change Username and Password\n2. Change General Info\n3. Exit\nChoose an option: ";
                int subChoice;
                cin >> subChoice;
                if (subChoice == 1)
                {
                    cout << "Enter new username: ";
                    cin >> newUsername;
                    cout << "Enter new password: ";
                    cin >> newPassword;
                    size_t pos1 = line.find(' ', pos + 1);
                    size_t pos2 = line.find(' ', pos1 + 1);
                    size_t pos3 = line.find(' ', pos2 + 1);
                    size_t pos4 = line.find(' ', pos3 + 1);
                    string remainingInfo = line.substr(pos3);
                    outFile << newUsername << " " << newPassword << remainingInfo << endl;
                }
                else if (subChoice == 2)
                {
                    cout << "Enter new name: ";
                    cin >> newName;
                    cout << "Enter new ID: ";
                    cin >> newId;
                    cout << "Choose new class: " << endl;
                    Class cls;
                    cls.showClasses();
                    cin >> newClassName;
                    size_t pos1 = line.find(' ', pos + 1);
                    size_t pos2 = line.find(' ', pos1 + 1);
                    size_t pos3 = line.find(' ', pos2 + 1);
                    outFile << currentUsername << " " << password << " " << newName << " " << newId << " " << newClassName << endl;
                }
            }
            else
            {
                outFile << line << endl;
            }
        }
        inFile.close();
        outFile.close();
        remove("teachers.txt");
        rename("temp.txt", "teachers.txt");

        if (!found)
        {
            cout << "Teacher not found!" << endl;
        }
    }

    void deleteTeacher()
    {
        string deleteUsername;
        cout << "Enter teacher username to delete: ";
        cin >> deleteUsername;

        ifstream inFile("teachers.txt");
        ofstream outFile("temp.txt");
        string line;
        bool found = false;
        while (getline(inFile, line))
        {
            size_t pos = line.find(' ');
            string currentUsername = line.substr(0, pos);
            if (currentUsername == deleteUsername)
            {
                found = true;
            }
            else
            {
                outFile << line << endl;
            }
        }
        inFile.close();
        outFile.close();
        remove("teachers.txt");
        rename("temp.txt", "teachers.txt");

        if (found)
        {
            cout << "Teacher deleted!" << endl;
        }
        else
        {
            cout << "Teacher not found!" << endl;
        }
    }
};

class Student
{
public:
    string username, password, name, fatherName, id, className;

    void signUp()
    {
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;
        cout << "Enter name: ";
        cin >> name;
        cout << "Enter father name: ";
        cin >> fatherName;
        cout << "Enter ID: ";
        cin >> id;
        cout << "Choose class: " << endl;
        Class cls;
        cls.showClasses();
        cin >> className;
        ofstream file("students.txt", ios::app);
        if (file.is_open())
        {
            file << username << " " << password << " " << name << " " << fatherName << " " << id << " " << className << endl;
            file.close();
            cout << "Student registered!" << endl;
        }
    }

    void updateInfo()
    {
        string searchUsername;
        cout << "Enter student username to update: ";
        cin >> searchUsername;

        ifstream inFile("students.txt");
        ofstream outFile("temp.txt");
        string line, newUsername, newPassword, newName, newFatherName, newId, newClassName;
        bool found = false;
        while (getline(inFile, line))
        {
            size_t pos = line.find(' ');
            string currentUsername = line.substr(0, pos);
            if (currentUsername == searchUsername)
            {
                found = true;
                cout << "1. Change Username and Password\n2. Change General Info\n3. Exit\nChoose an option: ";
                int subChoice;
                cin >> subChoice;
                if (subChoice == 1)
                {
                    cout << "Enter new username: ";
                    cin >> newUsername;
                    cout << "Enter new password: ";
                    cin >> newPassword;
                    size_t pos1 = line.find(' ', pos + 1);
                    size_t pos2 = line.find(' ', pos1 + 1);
                    size_t pos3 = line.find(' ', pos2 + 1);
                    size_t pos4 = line.find(' ', pos3 + 1);
                    string remainingInfo = line.substr(pos3);
                    outFile << newUsername << " " << newPassword << remainingInfo << endl;
                }
                else if (subChoice == 2)
                {
                    cout << "Enter new name: ";
                    cin >> newName;
                    cout << "Enter new father name: ";
                    cin >> newFatherName;
                    cout << "Enter new ID: ";
                    cin >> newId;
                    cout << "Choose new class: " << endl;
                    Class cls;
                    cls.showClasses();
                    cin >> newClassName;
                    size_t pos1 = line.find(' ', pos + 1);
                    size_t pos2 = line.find(' ', pos1 + 1);
                    size_t pos3 = line.find(' ', pos2 + 1);
                    outFile << currentUsername << " " << password << " " << newName << " " << newFatherName << " " << newId << " " << newClassName << endl;
                }
            }
            else
            {
                outFile << line << endl;
            }
        }
        inFile.close();
        outFile.close();
        remove("students.txt");
        rename("temp.txt", "students.txt");

        if (!found)
        {
            cout << "Student not found!" << endl;
        }
    }

    void showInfo()
    {
        string searchUsername;
        cout << "Enter student username to show info: ";
        cin >> searchUsername;

        ifstream inFile("students.txt");
        string line;
        bool found = false;
        while (getline(inFile, line))
        {
            size_t pos = line.find(' ');
            string currentUsername = line.substr(0, pos);
            if (currentUsername == searchUsername)
            {
                found = true;
                cout << line << endl;
            }
        }
        inFile.close();

        if (!found)
        {
            cout << "Student not found!" << endl;
        }
    }
};

void adminMenu(Admin &admin)
{
    while (true)
    {
        int choice;
        cout << "1. Admin Information\n2. Class\n3. Teacher\n4. Exit\nChoose an option: ";
        cin >> choice;

        if (choice == 1)
        {
            while (true)
            {
                int subChoice;
                cout << "1. Show Information\n2. Edit Information\n3. Exit\nChoose an option: ";
                cin >> subChoice;
                if (subChoice == 1)
                {
                    admin.showInfo();
                }
                else if (subChoice == 2)
                {
                    admin.editInfo();
                }
                else if (subChoice == 3)
                {
                    break;
                }
                else
                {
                    cout << "Invalid choice!" << endl;
                }
            }
        }
        else if (choice == 2)
        {
            Class cls;
            while (true)
            {
                int subChoice;
                cout << "1. Show Class Info\n2. Add Class\n3. Update Class\n4. Delete Class\n5. Exit\nChoose an option: ";
                cin >> subChoice;
                if (subChoice == 1)
                {
                    cls.showClasses();
                }
                else if (subChoice == 2)
                {
                    cls.addClass();
                }
                else if (subChoice == 3)
                {
                    cls.updateClass();
                }
                else if (subChoice == 4)
                {
                    cls.deleteClass();
                }
                else if (subChoice == 5)
                {
                    break;
                }
                else
                {
                    cout << "Invalid choice!" << endl;
                }
            }
        }
        else if (choice == 3)
        {
            Teacher teacher;
            while (true)
            {
                int subChoice;
                cout << "1. Show Teacher Info\n2. Register Teacher\n3. Update Teacher Info\n4. Delete Teacher\n5. Exit\nChoose an option: ";
                cin >> subChoice;
                if (subChoice == 1)
                {
                    teacher.showTeachers();
                }
                else if (subChoice == 2)
                {
                    teacher.registerTeacher();
                }
                else if (subChoice == 3)
                {
                    teacher.updateTeacher();
                }
                else if (subChoice == 4)
                {
                    teacher.deleteTeacher();
                }
                else if (subChoice == 5)
                {
                    break;
                }
                else
                {
                    cout << "Invalid choice!" << endl;
                }
            }
        }
        else if (choice == 4)
        {
            break;
        }
        else
        {
            cout << "Invalid choice!" << endl;
        }
    }
}

void teacherMenu()
{
    string username, password;
    cout << "Enter teacher username: ";
    cin >> username;
    cout << "Enter teacher password: ";
    cin >> password;

    Teacher teacher;
    ifstream file("teachers.txt");
    string line;
    bool found = false;
    while (getline(file, line))
    {
        size_t pos = line.find(' ');
        string currentUsername = line.substr(0, pos);
        size_t pos1 = line.find(' ', pos + 1);
        string currentPassword = line.substr(pos + 1, pos1 - pos - 1);
        size_t pos2 = line.find(' ', pos1 + 1);
        size_t pos3 = line.find(' ', pos2 + 1);
        size_t pos4 = line.find(' ', pos3 + 1);
        string remainingInfo = line.substr(pos3 + 1);
        if (currentUsername == username && currentPassword == password)
        {
            teacher.username = currentUsername;
            teacher.password = currentPassword;
            teacher.name = line.substr(pos1 + 1, pos2 - pos1 - 1);
            teacher.id = line.substr(pos2 + 1, pos3 - pos2 - 1);
            teacher.className = line.substr(pos3 + 1);
            found = true;
            break;
        }
    }
    file.close();

    if (!found)
    {
        cout << "Invalid username or password!" << endl;
        return;
    }

    while (true)
    {
        int choice;
        cout << "1. Add Questions\n2. Delete Questions\n3. Exit\nChoose an option: ";
        cin >> choice;
        if (choice == 1)
        {
            ofstream file("questions.txt", ios::app);
            string question, correctAnswer;
            cout << "Enter question: ";
            cin.ignore();
            getline(cin, question);
            cout << "Enter correct answer: ";
            getline(cin, correctAnswer);
            file << teacher.className << " " << question << endl;
            file << teacher.className << " " << correctAnswer << endl;
            file.close();
            cout << "Question added!" << endl;
        }
        else if (choice == 2)
        {
            string deleteQuestion;
            cout << "Enter question to delete: ";
            cin.ignore();
            getline(cin, deleteQuestion);
            ifstream inFile("questions.txt");
            ofstream outFile("temp.txt");
            string line;
            bool found = false;
            while (getline(inFile, line))
            {
                if (line.find(teacher.className + " " + deleteQuestion) == 0)
                {
                    found = true;
                    getline(inFile, line); // Skip the answer line
                }
                else
                {
                    outFile << line << endl;
                }
            }
            inFile.close();
            outFile.close();
            remove("questions.txt");
            rename("temp.txt", "questions.txt");

            if (found)
            {
                cout << "Question deleted!" << endl;
            }
            else
            {
                cout << "Question not found!" << endl;
            }
        }
        else if (choice == 3)
        {
            break;
        }
        else
        {
            cout << "Invalid choice!" << endl;
        }
    }
}

void studentMenu()
{
    while (true)
    {
        int choice;
        cout << "1. Sign Up\n2. Login\n3. Exit\nChoose an option: ";
        cin >> choice;

        if (choice == 1)
        {
            Student student;
            student.signUp();
        }
        else if (choice == 2)
        {
            string username, password;
            cout << "Enter student username: ";
            cin >> username;
            cout << "Enter student password: ";
            cin >> password;

            Student student;
            ifstream file("students.txt");
            string line;
            bool found = false;
            while (getline(file, line))
            {
                size_t pos = line.find(' ');
                string currentUsername = line.substr(0, pos);
                size_t pos1 = line.find(' ', pos + 1);
                string currentPassword = line.substr(pos + 1, pos1 - pos - 1);
                if (currentUsername == username && currentPassword == password)
                {
                    student.username = currentUsername;
                    student.password = currentPassword;
                    size_t pos2 = line.find(' ', pos1 + 1);
                    size_t pos3 = line.find(' ', pos2 + 1);
                    size_t pos4 = line.find(' ', pos3 + 1);
                    student.name = line.substr(pos1 + 1, pos2 - pos1 - 1);
                    student.fatherName = line.substr(pos2 + 1, pos3 - pos2 - 1);
                    student.id = line.substr(pos3 + 1, pos4 - pos3 - 1);
                    student.className = line.substr(pos4 + 1);
                    found = true;
                    break;
                }
            }
            file.close();

            if (!found)
            {
                cout << "Invalid username or password!" << endl;
                return;
            }

            while (true)
            {
                int subChoice;
                cout << "1. Show Info\n2. Update Info\n3. Exit\nChoose an option: ";
                cin >> subChoice;
                if (subChoice == 1)
                {
                    student.showInfo();
                }
                else if (subChoice == 2)
                {
                    student.updateInfo();
                }
                else if (subChoice == 3)
                {
                    break;
                }
                else
                {
                    cout << "Invalid choice!" << endl;
                }
            }
        }
        else if (choice == 3)
        {
            break;
        }
        else
        {
            cout << "Invalid choice!" << endl;
        }
    }
}

void examMenu()
{
    string username, password;
    cout << "Enter student username: ";
    cin >> username;
    cout << "Enter student password: ";
    cin >> password;

    Student student;
    ifstream file("students.txt");
    string line;
    bool found = false;
    while (getline(file, line))
    {
        size_t pos = line.find(' ');
        string currentUsername = line.substr(0, pos);
        size_t pos1 = line.find(' ', pos + 1);
        string currentPassword = line.substr(pos + 1, pos1 - pos - 1);
        if (currentUsername == username && currentPassword == password)
        {
            student.username = currentUsername;
            student.password = currentPassword;
            size_t pos2 = line.find(' ', pos1 + 1);
            size_t pos3 = line.find(' ', pos2 + 1);
            size_t pos4 = line.find(' ', pos3 + 1);
            student.name = line.substr(pos1 + 1, pos2 - pos1 - 1);
            student.fatherName = line.substr(pos2 + 1, pos3 - pos2 - 1);
            student.id = line.substr(pos3 + 1, pos4 - pos3 - 1);
            student.className = line.substr(pos4 + 1);
            found = true;
            break;
        }
    }
    file.close();

    if (!found)
    {
        cout << "Invalid username or password!" << endl;
        return;
    }

    ifstream qfile("questions.txt");
    if (!qfile.is_open())
    {
        cout << "No questions found!" << endl;
        return;
    }

    string question, correctAnswer;
    ofstream ansFile("answers.txt", ios::app);
    while (getline(qfile, line))
    {
        if (line.find(student.className + " ") == 0)
        {
            question = line.substr(student.className.length() + 1);
            getline(qfile, line);
            correctAnswer = line.substr(student.className.length() + 1);
            string studentAnswer;
            cout << question << endl;
            cout << "Your answer: ";
            cin.ignore();
            getline(cin, studentAnswer);
            ansFile << student.username << " " << question << " " << studentAnswer << endl;
        }
    }
    ansFile.close();
    qfile.close();

    cout << "Exam completed!" << endl;
}

void resultMenu()
{
    string username, password;
    cout << "Enter student username: ";
    cin >> username;
    cout << "Enter student password: ";
    cin >> password;

    Student student;
    ifstream file("students.txt");
    string line;
    bool found = false;
    while (getline(file, line))
    {
        size_t pos = line.find(' ');
        string currentUsername = line.substr(0, pos);
        size_t pos1 = line.find(' ', pos + 1);
        string currentPassword = line.substr(pos + 1, pos1 - pos - 1);
        if (currentUsername == username && currentPassword == password)
        {
            student.username = currentUsername;
            student.password = currentPassword;
            size_t pos2 = line.find(' ', pos1 + 1);
            size_t pos3 = line.find(' ', pos2 + 1);
            size_t pos4 = line.find(' ', pos3 + 1);
            student.name = line.substr(pos1 + 1, pos2 - pos1 - 1);
            student.fatherName = line.substr(pos2 + 1, pos3 - pos2 - 1);
            student.id = line.substr(pos3 + 1, pos4 - pos3 - 1);
            student.className = line.substr(pos4 + 1);
            found = true;
            break;
        }
    }
    file.close();

    if (!found)
    {
        cout << "Invalid username or password!" << endl;
        return;
    }

    ifstream ansFile("answers.txt");
    ifstream qfile("questions.txt");
    if (!ansFile.is_open() || !qfile.is_open())
    {
        cout << "No answers or questions found!" << endl;
        return;
    }

    string question, correctAnswer, studentAnswer;
    int score = 0;
    int numQuestion = 0;

    while (getline(qfile, question) && getline(qfile, correctAnswer))
    {
        if (question.empty() || correctAnswer.empty())
            continue;

        question = question.substr(2);
        correctAnswer = correctAnswer.substr(2);

        while (getline(ansFile, studentAnswer))
        {
            if (studentAnswer.empty())
                continue;

            istringstream iss(studentAnswer);
            string studentName, studentQ, studentA;

            iss >> studentName;
            getline(iss, studentQ, '?');
            if (studentQ.empty())
                continue;
            studentQ += '?';
            getline(iss, studentA);
            if (studentA.size() > 0)
            {
                studentA = studentA.substr(1);
            }
            else
            {
                continue;
            }
            studentQ = studentQ.substr(1);
            if (studentQ == question && studentA == correctAnswer)
            {
                score++;
                break;
            }
        }
        numQuestion++;
        ansFile.clear();
    }

    qfile.close();
    ansFile.close();

    cout << "\nNumber of questions: " << numQuestion << endl;
    cout << "Correct questions: " << score << endl;
    cout << "Your score: " << (score / numQuestion) * 100 << endl
         << endl;
}

int main()
{
    Admin admin;
    while (true)
    {
        int choice;
        cout << "1. Admin\n2. Teacher\n3. Student\n4. Exam\n5. Result\n6. Exit\nChoose an option: ";
        cin >> choice;

        if (choice == 1)
        {
            string username, password;
            cout << "Enter admin username: ";
            cin >> username;
            cout << "Enter admin password: ";
            cin >> password;

            if (username == admin.username && password == admin.password)
            {
                adminMenu(admin);
            }
            else
            {
                cout << "Invalid admin credentials!" << endl;
            }
        }
        else if (choice == 2)
        {
            teacherMenu();
        }
        else if (choice == 3)
        {
            studentMenu();
        }
        else if (choice == 4)
        {
            examMenu();
        }
        else if (choice == 5)
        {
            resultMenu();
        }
        else if (choice == 6)
        {
            break;
        }
        else
        {
            cout << "Invalid choice!" << endl;
        }
    }

    return 0;
}