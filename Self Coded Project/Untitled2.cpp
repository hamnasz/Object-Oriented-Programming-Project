#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <limits>

using namespace std;

class Admin
{
public:
    string username;
    string password;
    Admin() : username("admin"), password("123") {}

    void showInfo()
    {
        cout << "Admin Username: " << username << endl;
        cout << "Admin Password: " << password << endl;
    }

    void editInfo()
    {
        cout << "Enter new username: ";
        cin >> username;
        cout << "Enter new password: ";
        cin >> password;
        saveAdminInfo();
    }

    void saveAdminInfo()
    {
        ofstream adminFile("admin.txt");
        adminFile << username << " " << password;
        adminFile.close();
    }

    void loadAdminInfo()
    {
        ifstream adminFile("admin.txt");
        if (adminFile.is_open())
        {
            adminFile >> username >> password;
            adminFile.close();
        }
    }
};

class Class
{
public:
    string className;
    int classID;

    Class(string name, int id) : className(name), classID(id) {}

    void showClassInfo()
    {
        cout << "Section: " << className << ", Class Number: " << classID << endl;
    }
};

class Teacher
{
public:
    string username;
    string password;
    string name;
    int id;
    int classID;

    Teacher(string uname, string pass, string tname, int tid, int cid)
        : username(uname), password(pass), name(tname), id(tid), classID(cid) {}

    void showTeacherInfo()
    {
        cout << "Teacher Name: " << name << ", Teacher ID: " << id
             << ", Class Number: " << classID << endl;
    }
};

class Student
{
public:
    string username;
    string password;
    string name;
    string fatherName;
    int id;
    int classID;

    Student(string uname, string pass, string sname, string fname, int sid, int cid)
        : username(uname), password(pass), name(sname), fatherName(fname), id(sid), classID(cid) {}

    void showStudentInfo()
    {
        cout << "Student Name: " << name << ", Father Name: " << fatherName
             << ", Student ID: " << id << ", Class Number: " << classID << endl;
    }
};

class Question
{
public:
    string questionText;
    vector<string> options;
    int correctOption;

    void loadFromStream(ifstream &input)
    {
        getline(input, questionText);
        options.resize(4);
        for (int i = 0; i < 4; i++)
        {
            getline(input, options[i]);
        }
        input >> correctOption;
        input.ignore();
    }

    void saveToStream(ofstream &output) const
    {
        output << questionText << endl;
        for (const auto &option : options)
        {
            output << option << endl;
        }
        output << correctOption << endl;
    }
};

class Exam
{
public:
    map<int, vector<Question>> quizQuestions;
    map<int, vector<Question>> midQuestions;
    map<int, vector<Question>> finalQuestions;

    void addQuestion(int classID, int examType, Question question)
    {
        if (examType == 1)
        {
            quizQuestions[classID].push_back(question);
        }
        else if (examType == 2)
        {
            midQuestions[classID].push_back(question);
        }
        else if (examType == 3)
        {
            finalQuestions[classID].push_back(question);
        }
        saveQuestions();
    }

    void deleteQuestion(int classID, int examType, int questionIndex)
    {
        if (examType == 1)
        {
            quizQuestions[classID].erase(quizQuestions[classID].begin() + questionIndex);
        }
        else if (examType == 2)
        {
            midQuestions[classID].erase(midQuestions[classID].begin() + questionIndex);
        }
        else if (examType == 3)
        {
            finalQuestions[classID].erase(finalQuestions[classID].begin() + questionIndex);
        }
        saveQuestions();
    }

    void saveQuestions()
    {
        saveToFile("quizQuestions.txt", quizQuestions);
        saveToFile("midQuestions.txt", midQuestions);
        saveToFile("finalQuestions.txt", finalQuestions);
    }

    void loadQuestions()
    {
        loadFromFile("quizQuestions.txt", quizQuestions);
        loadFromFile("midQuestions.txt", midQuestions);
        loadFromFile("finalQuestions.txt", finalQuestions);
    }
    void saveStudentAnswers(int studentID, int classID, int examType, const vector<int> &studentAnswers)
    {
        string filename = "key_" + to_string(studentID) + "_" + to_string(classID) + "_" + to_string(examType) + ".txt";
        ofstream file(filename);
        file << "Student ID: " << studentID << endl;
        file << "Class ID: " << classID << endl;
        file << "Exam Type: " << examType << endl;
        file << "Student Answers: ";
        for (int answer : studentAnswers)
        {
            file << answer << " ";
        }
        file << endl;
        file << "Correct Answers: ";
        vector<Question> questions;
        if (examType == 1)
        {
            questions = quizQuestions[classID];
        }
        else if (examType == 2)
        {
            questions = midQuestions[classID];
        }
        else if (examType == 3)
        {
            questions = finalQuestions[classID];
        }
        for (const Question &question : questions)
        {
            file << question.correctOption << " ";
        }
        file << endl;
        file.close();
    }

private:
    void saveToFile(const string &filename, const map<int, vector<Question>> &questions)
    {
        ofstream file(filename);
        for (const auto &pair : questions)
        {
            int classID = pair.first;
            for (const auto &question : pair.second)
            {
                file << classID << endl;
                file << question.questionText << endl;
                for (const auto &option : question.options)
                {
                    file << option << endl;
                }
                file << question.correctOption << endl;
            }
        }
        file.close();
    }

    void loadFromFile(const string &filename, map<int, vector<Question>> &questions)
    {
        ifstream file(filename);
        if (file.is_open())
        {
            int classID;
            while (file >> classID)
            {
                file.ignore();
                Question question;
                getline(file, question.questionText);
                for (int i = 0; i < 4; ++i)
                {
                    string option;
                    getline(file, option);
                    question.options.push_back(option);
                }
                file >> question.correctOption;
                file.ignore();
                questions[classID].push_back(question);
            }
            file.close();
        }
    }
};

vector<Class> classes;
vector<Teacher> teachers;
vector<Student> students;
Admin admin;
Exam exam;

void loadClasses()
{
    ifstream classFile("classes.txt");
    if (classFile.is_open())
    {
        string name;
        int id;
        while (classFile >> id >> name)
        {
            classes.push_back(Class(name, id));
        }
        classFile.close();
    }
}

void saveClasses()
{
    ofstream classFile("classes.txt");
    for (auto &cls : classes)
    {
        classFile << cls.classID << " " << cls.className << endl;
    }
    classFile.close();
}

void loadTeachers()
{
    ifstream teacherFile("teachers.txt");
    if (teacherFile.is_open())
    {
        string uname, pass, name;
        int id, cid;
        while (teacherFile >> uname >> pass >> name >> id >> cid)
        {
            teachers.push_back(Teacher(uname, pass, name, id, cid));
        }
        teacherFile.close();
    }
}

void saveTeachers()
{
    ofstream teacherFile("teachers.txt");
    for (auto &teacher : teachers)
    {
        teacherFile << teacher.username << " " << teacher.password << " "
                    << teacher.name << " " << teacher.id << " " << teacher.classID << endl;
    }
    teacherFile.close();
}

void loadStudents()
{
    ifstream studentFile("students.txt");
    if (studentFile.is_open())
    {
        string uname, pass, name, fname;
        int id, cid;
        while (studentFile >> uname >> pass >> name >> fname >> id >> cid)
        {
            students.push_back(Student(uname, pass, name, fname, id, cid));
        }
        studentFile.close();
    }
}

void saveStudents()
{
    ofstream studentFile("students.txt");
    for (auto &student : students)
    {
        studentFile << student.username << " " << student.password << " "
                    << student.name << " " << student.fatherName << " "
                    << student.id << " " << student.classID << endl;
    }
    studentFile.close();
}

void saveExams()
{
    // Assuming you have a save function in your Exam class already.
    exam.saveQuestions();
    // Additional saving logic specific to exams if needed.
}

void adminMenu()
{
    admin.loadAdminInfo();
    string uname, pass;
    cout << "Admin Login\nUsername: ";
    cin >> uname;
    cout << "Password: ";
    cin >> pass;
    if (uname == admin.username && pass == admin.password)
    {
        while (true)
        {
            cout << "\nAdmin Menu\n1. Admin Information\n2. Class\n3. Teacher\n4. Exit\nChoice: ";
            int choice;
            cin >> choice;
            if (choice == 1)
            {
                while (true)
                {
                    cout << "\nAdmin Information\n1. Show Information\n2. Edit Information\n3. Exit\nChoice: ";
                    cin >> choice;
                    if (choice == 1)
                    {
                        admin.showInfo();
                    }
                    else if (choice == 2)
                    {
                        admin.editInfo();
                    }
                    else if (choice == 3)
                    {
                        break;
                    }
                }
            }
            else if (choice == 2)
            {
                while (true)
                {
                    cout << "\nClass Management\n1. Show Class Info\n2. Add Class\n3. Update Class\n4. Delete Class\n5. Exit\nChoice: ";
                    cin >> choice;
                    if (choice == 1)
                    {
                        for (auto &cls : classes)
                        {
                            cls.showClassInfo();
                        }
                    }
                    else if (choice == 2)
                    {
                        string name;
                        int id;
                        cout << "Enter Class Number: ";
                        cin >> id;
                        cout << "Enter Section: ";
                        cin >> name;
                        classes.push_back(Class(name, id));
                        saveClasses();
                    }
                    else if (choice == 3)
                    {
                        int id;
                        cout << "Enter Class Number to update: ";
                        cin >> id;
                        for (auto &cls : classes)
                        {
                            if (cls.classID == id)
                            {
                                cout << "Enter new Section: ";
                                cin >> cls.className;
                                saveClasses();
                                break;
                            }
                        }
                    }
                    else if (choice == 4)
                    {
                        int id;
                        cout << "Enter Class Number to delete: ";
                        cin >> id;
                        for (auto it = classes.begin(); it != classes.end(); ++it)
                        {
                            if (it->classID == id)
                            {
                                classes.erase(it);
                                saveClasses();
                                break;
                            }
                        }
                    }
                    else if (choice == 5)
                    {
                        break;
                    }
                }
            }
            else if (choice == 3)
            {
                while (true)
                {
                    cout << "\nTeacher Management\n1. Show Teacher Info\n2. Register Teacher\n3. Update Teacher Info\n4. Delete Teacher\n5. Exit\nChoice: ";
                    cin >> choice;
                    if (choice == 1)
                    {
                        for (auto &teacher : teachers)
                        {
                            teacher.showTeacherInfo();
                        }
                    }
                    else if (choice == 2)
                    {
                        string uname, pass, name;
                        int id, cid;
                        cout << "Enter teacher username: ";
                        cin >> uname;
                        cout << "Enter teacher password: ";
                        cin >> pass;
                        cout << "Enter teacher name: ";
                        cin >> name;
                        cout << "Enter teacher ID: ";
                        cin >> id;
                        cout << "Available classes: " << endl;
                        for (auto &cls : classes)
                        {
                            cout << "Class Number: " << cls.classID << ", Section: " << cls.className << endl;
                        }
                        cout << "Enter Class Number: ";
                        cin >> cid;
                        teachers.push_back(Teacher(uname, pass, name, id, cid));
                        saveTeachers();
                    }
                    else if (choice == 3)
                    {
                        cout << "\nUpdate Teacher Info\n1. Change Username and Password\n2. Change General Info\n3. Exit\nChoice: ";
                        cin >> choice;
                        if (choice == 1)
                        {
                            string uname;
                            cout << "Enter teacher username to update: ";
                            cin >> uname;
                            for (auto &teacher : teachers)
                            {
                                if (teacher.username == uname)
                                {
                                    cout << "Enter new username: ";
                                    cin >> teacher.username;
                                    cout << "Enter new password: ";
                                    cin >> teacher.password;
                                    saveTeachers();
                                    break;
                                }
                            }
                        }
                        else if (choice == 2)
                        {
                            int id;
                            cout << "Enter teacher ID to update: ";
                            cin >> id;
                            for (auto &teacher : teachers)
                            {
                                if (teacher.id == id)
                                {
                                    cout << "Enter new teacher name: ";
                                    cin >> teacher.name;
                                    cout << "Enter new Class Number: ";
                                    cin >> teacher.classID;
                                    saveTeachers();
                                    break;
                                }
                            }
                        }
                        else if (choice == 3)
                        {
                            break;
                        }
                    }
                    else if (choice == 4)
                    {
                        int id;
                        cout << "Enter teacher ID to delete: ";
                        cin >> id;
                        for (auto it = teachers.begin(); it != teachers.end(); ++it)
                        {
                            if (it->id == id)
                            {
                                teachers.erase(it);
                                saveTeachers();
                                break;
                            }
                        }
                    }
                    else if (choice == 5)
                    {
                        break;
                    }
                }
            }
            else if (choice == 4)
            {
                break;
            }
        }
    }
    else
    {
        cout << "Invalid admin login!" << endl;
    }
}

void teacherMenu()
{
    string uname, pass;
    cout << "Teacher Login\nUsername: ";
    cin >> uname;
    cout << "Password: ";
    cin >> pass;
    for (auto &teacher : teachers)
    {
        if (teacher.username == uname && teacher.password == pass)
        {
            while (true)
            {
                cout << "\nTeacher Menu\n1. Add Questions\n2. Delete Questions\n3. Exit\nChoice: ";
                int choice;
                cin >> choice;
                if (choice == 1)
                {
                    cout << "\nAdd Questions\n1. Quiz\n2. Mid Exam\n3. Final Exam\nChoice: ";
                    int examType;
                    cin >> examType;
                    Question question;
                    cout << "Enter question: ";
                    cin.ignore();
                    getline(cin, question.questionText);
                    cout << "Enter options (4 options, separated by enter): " << endl;
                    for (int i = 0; i < 4; i++)
                    {
                        string option;
                        getline(cin, option);
                        question.options.push_back(option);
                    }
                    cout << "Enter correct option (1-4): ";
                    cin >> question.correctOption;
                    exam.addQuestion(teacher.classID, examType, question);
                }
                else if (choice == 2)
                {
                    cout << "\nDelete Questions\n1. Quiz\n2. Mid Exam\n3. Final Exam\nChoice: ";
                    int examType;
                    cin >> examType;
                    int classID = teacher.classID;
                    if (examType == 1)
                    {
                        for (size_t i = 0; i < exam.quizQuestions[classID].size(); ++i)
                        {
                            cout << i + 1 << ". " << exam.quizQuestions[classID][i].questionText << endl;
                        }
                        int questionIndex;
                        cout << "Enter question number to delete: ";
                        cin >> questionIndex;
                        exam.deleteQuestion(classID, examType, questionIndex - 1);
                    }
                    else if (examType == 2)
                    {
                        for (size_t i = 0; i < exam.midQuestions[classID].size(); ++i)
                        {
                            cout << i + 1 << ". " << exam.midQuestions[classID][i].questionText << endl;
                        }
                        int questionIndex;
                        cout << "Enter question number to delete: ";
                        cin >> questionIndex;
                        exam.deleteQuestion(classID, examType, questionIndex - 1);
                    }
                    else if (examType == 3)
                    {
                        for (size_t i = 0; i < exam.finalQuestions[classID].size(); ++i)
                        {
                            cout << i + 1 << ". " << exam.finalQuestions[classID][i].questionText << endl;
                        }
                        int questionIndex;
                        cout << "Enter question number to delete: ";
                        cin >> questionIndex;
                        exam.deleteQuestion(classID, examType, questionIndex - 1);
                    }
                }
                else if (choice == 3)
                {
                    break;
                }
            }
            return;
        }
    }
    cout << "Invalid teacher login!" << endl;
}
void takeExam(Student &student);
void studentMenu()
{
    while (true)
    {
        cout << "\nStudent Menu\n1. Sign Up\n2. Login\n3. Take Exam\n4. Exit\nChoice: ";
        int choice;
        cin >> choice;

        if (choice == 1)
        {
            string uname, pass, name, fname;
            int id, cid;
            cout << "Enter student username: ";
            cin >> uname;
            cout << "Enter student password: ";
            cin >> pass;
            cout << "Enter student name: ";
            cin >> name;
            cout << "Enter father name: ";
            cin >> fname;
            cout << "Enter student ID: ";
            cin >> id;

            cout << "Available classes: " << endl;
            for (auto &cls : classes)
            {
                cout << "Class Number: " << cls.classID << ", Section: " << cls.className << endl;
            }
            cout << "Enter Class Number: ";
            cin >> cid;
            students.push_back(Student(uname, pass, name, fname, id, cid));
            saveStudents();
        }
        else if (choice == 2)
        {
            string uname, pass;
            cout << "Student Login\nUsername: ";
            cin >> uname;
            cout << "Password: ";
            cin >> pass;
            for (auto &student : students)
            {
                if (student.username == uname && student.password == pass)
                {
                    while (true)
                    {
                        cout << "\nStudent Menu\n1. Show Info\n2. Update Info\n3. Take Exam\n4. Exit\nChoice: ";
                        cin >> choice;
                        if (choice == 1)
                        {
                            student.showStudentInfo();
                            cout << "Teachers for this class: " << endl;
                            for (auto &teacher : teachers)
                            {
                                if (teacher.classID == student.classID)
                                {
                                    teacher.showTeacherInfo();
                                }
                            }
                        }
                        else if (choice == 2)
                        {
                            cout << "Enter new username: ";
                            cin >> student.username;
                            cout << "Enter new password: ";
                            cin >> student.password;
                            saveStudents();
                        }
                        else if (choice == 3)
                        {
                            takeExam(student); // Function to start exam taking process
                        }
                        else if (choice == 4)
                        {
                            break;
                        }
                    }
                    return;
                }
            }
            cout << "Invalid student login!" << endl;
        }
        else if (choice == 3)
        {
            break;
        }
    }
}

void takeExam(Student &student)
{
    cout << "\nChoose Exam Type:\n1. Quiz\n2. Midterm\n3. Final\nChoice: ";
    int examType;
    cin >> examType;

    vector<Question> questions;
    if (examType == 1)
    {
        questions = exam.quizQuestions[student.classID];
    }
    else if (examType == 2)
    {
        questions = exam.midQuestions[student.classID];
    }
    else if (examType == 3)
    {
        questions = exam.finalQuestions[student.classID];
    }
    else
    {
        cout << "Invalid Exam Type" << endl;
        return;
    }

    vector<int> studentAnswers;
    for (const Question &question : questions)
    {
        cout << question.questionText << endl;
        for (int i = 0; i < question.options.size(); ++i)
        {
            cout << i + 1 << ". " << question.options[i] << endl;
        }
        int answer;
        cin >> answer;
        studentAnswers.push_back(answer);
    }

    exam.saveStudentAnswers(student.id, student.classID, examType, studentAnswers);
    cout << "Answers saved to key file." << endl;
}

void examMenu()
{
    string uname, pass;
    cout << "Student Login\nUsername: ";
    cin >> uname;
    cout << "Password: ";
    cin >> pass;
    for (auto &student : students)
    {
        if (student.username == uname && student.password == pass)
        {
            while (true)
            {
                cout << "\nExam Menu\n1. Quiz\n2. Mid Exam\n3. Final\nChoice: ";
                int choice;
                cin >> choice;
                int classID = student.classID;
                if (choice == 1)
                {
                    for (auto &question : exam.quizQuestions[classID])
                    {
                        cout << question.questionText << endl;
                        for (size_t i = 0; i < question.options.size(); ++i)
                        {
                            cout << i + 1 << ". " << question.options[i] << endl;
                        }
                        int answer;
                        cout << "Your answer: ";
                        cin >> answer;
                    }
                }
                else if (choice == 2)
                {
                    for (auto &question : exam.midQuestions[classID])
                    {
                        cout << question.questionText << endl;
                        for (size_t i = 0; i < question.options.size(); ++i)
                        {
                            cout << i + 1 << ". " << question.options[i] << endl;
                        }
                        int answer;
                        cout << "Your answer: ";
                        cin >> answer;
                    }
                }
                else if (choice == 3)
                {
                    for (auto &question : exam.finalQuestions[classID])
                    {
                        cout << question.questionText << endl;
                        for (size_t i = 0; i < question.options.size(); ++i)
                        {
                            cout << i + 1 << ". " << question.options[i] << endl;
                        }
                        int answer;
                        cout << "Your answer: ";
                        cin >> answer;
                    }
                }
                break;
            }
            return;
        }
    }
    cout << "Invalid student login!" << endl;
}

void resultMenu()
{
    string uname, pass;
    cout << "Student Login\nUsername: ";
    cin >> uname;
    cout << "Password: ";
    cin >> pass;
    for (auto &student : students)
    {
        if (student.username == uname && student.password == pass)
        {
            int score = 0;
            int total = 0;
            int classID = student.classID;

            // Opening a file to save results
            ofstream resultFile("result_" + to_string(student.id) + "_" + to_string(classID) + ".txt");

            if (!resultFile)
            {
                cout << "Error opening result file!" << endl;
                return;
            }

            for (auto &question : exam.quizQuestions[classID])
            {
                cout << question.questionText << endl;
                for (size_t i = 0; i < question.options.size(); ++i)
                {
                    cout << i + 1 << ". " << question.options[i] << endl;
                }
                int answer;
                cout << "Your answer: ";
                cin >> answer;
                resultFile << question.questionText << endl;
                resultFile << "Your answer: " << answer << endl;
                resultFile << "Correct answer: " << question.correctOption << endl;
                if (answer == question.correctOption)
                {
                    score++;
                }
                total++;
            }
            for (auto &question : exam.midQuestions[classID])
            {
                cout << question.questionText << endl;
                for (size_t i = 0; i < question.options.size(); ++i)
                {
                    cout << i + 1 << ". " << question.options[i] << endl;
                }

                int answer;
                cout << "Your answer: ";
                cin >> answer;
                resultFile << question.questionText << endl;
                resultFile << "Your answer: " << answer << endl;
                resultFile << "Correct answer: " << question.correctOption << endl;
                if (answer == question.correctOption)
                {
                    score++;
                }
                total++;
            }
            for (auto &question : exam.finalQuestions[classID])
            {
                cout << question.questionText << endl;
                for (size_t i = 0; i < question.options.size(); ++i)
                {
                    cout << i + 1 << ". " << question.options[i] << endl;
                }
                int answer;
                cout << "Your answer: ";
                cin >> answer;
                resultFile << question.questionText << endl;
                resultFile << "Your answer: " << answer << endl;
                resultFile << "Correct answer: " << question.correctOption << endl;
                if (answer == question.correctOption)
                {
                    score++;
                }
                total++;
            }
            resultFile << "Total score: " << score << " out of " << total << endl;

            // Closing the result file
            resultFile.close();

            cout << "Results saved to file." << endl;
            return;
        }
    }
    cout << "Invalid student login!" << endl;
}

int main()
{
    loadClasses();
    loadTeachers();
    loadStudents();
    exam.loadQuestions();

    while (true)
    {
        cout << "\nMain Menu\n1. Admin\n2. Teacher\n3. Student\n4. Exam\n5. Result\n6. Exit\nChoice: ";
        int choice;
        cin >> choice;

        if (cin.fail())
        {                                                        // input operation failed
            cin.clear();                                         // clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ignore rest of line
            cout << "Invalid input. Please enter a number." << endl;
            continue; // skip to next iteration
        }

        switch (choice)
        {
        case 1:
            adminMenu();
            break;
        case 2:
            teacherMenu();
            break;
        case 3:
            studentMenu();
            break;
        case 4:
            examMenu();
            break;
        case 5:
            resultMenu();
            break;
        case 6:
            saveStudents(); // Save students before exiting
            saveTeachers(); // Save teachers before exiting
            saveClasses();  // Save classes before exiting
            saveExams();    // Save exams before exiting
            cout << "Exiting program..." << endl;
            return 0;
        default:
            cout << "Invalid choice. Please choose from 1 to 6." << endl;
            break;
        }
    }

    return 0;
}