#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <stdexcept>

using namespace std;

struct Student {
    string name;
    int age;
    char gender;
    float score;
};

class StudentManager {
private:
    vector<Student> students;
    const string dataFile = "students.txt";

    void saveData() {
        ofstream file(dataFile);
        if (!file.is_open()) {
            throw runtime_error("无法打开文件进行写入！");
        }
        for (const auto& student : students) {
            file << student.name << "," << student.age << "," << student.gender << "," << student.score << endl;
        }
        file.close();
    }

    void loadData() {
        ifstream file(dataFile);
        if (!file.is_open()) {
            throw runtime_error("无法打开文件进行读取！");
        }
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            Student student;
            getline(ss, student.name, ',');
            ss >> student.age;
            ss.ignore(); // 忽略逗号
            ss >> student.gender;
            ss.ignore(); // 忽略逗号
            ss >> student.score;
            students.push_back(student);
        }
        file.close();
    }

public:
    StudentManager() {
        loadData();
    }

    void addStudent(const Student& student) {
        students.push_back(student);
        saveData();
        cout << "学生信息添加成功！" << endl;
    }

    void displayStudents() {
        cout << "姓名\t年龄\t性别\t成绩" << endl;
        for (const auto& student : students) {
            cout << student.name << "\t" << student.age << "\t" << student.gender << "\t" << student.score << endl;
        }
    }

    void findStudentByName(const string& name) {
        for (const auto& student : students) {
            if (student.name == name) {
                cout << "姓名\t年龄\t性别\t成绩" << endl;
                cout << student.name << "\t" << student.age << "\t" << student.gender << "\t" << student.score << endl;
                return;
            }
        }
        cout << "未找到该学生信息！" << endl;
    }

    void deleteStudentByName(const string& name) {
        auto it = remove_if(students.begin(), students.end(), [&name](const Student& student) {
            return student.name == name;
        });
        if (it != students.end()) {
            students.erase(it, students.end());
            saveData();
            cout << "学生信息删除成功！" << endl;
        } else {
            cout << "未找到该学生信息！" << endl;
        }
    }

    void editStudentByName(const string& name) {
        for (auto& student : students) {
            if (student.name == name) {
                cout << "找到学生 " << name << ". 输入新的信息：" << endl;
                cout << "请输入学生年龄：";
                cin >> student.age;
                cout << "请输入学生性别（M/F）：";
                char gender;
                cin >> gender;
                if (!isValidGender(gender)) {
                    cout << "性别输入错误，请重新输入！" << endl;
                    continue;
                }
                student.gender = gender;
                cout << "请输入学生成绩：";
                cin >> student.score;
                saveData();
                cout << "学生信息更新成功！" << endl;
                return;
            }
        }
        cout << "未找到该学生信息！" << endl;
    }

    void sortStudentsByScore(bool ascending = true) {
        auto compare = [ascending](const Student& a, const Student& b) {
            return ascending ? a.score < b.score : a.score > b.score;
        };
        sort(students.begin(), students.end(), compare);
        saveData();
        cout << "学生信息按成绩排序完成！" << endl;
    }

    void sortStudentsByAge(bool ascending = true) {
        auto compare = [ascending](const Student& a, const Student& b) {
            return ascending ? a.age < b.age : a.age > b.age;
        };
        sort(students.begin(), students.end(), compare);
        saveData();
        cout << "学生信息按年龄排序完成！" << endl;
    }

    void displayGenderStatistics() {
        int maleCount = 0, femaleCount = 0;
        for (const auto& student : students) {
            if (student.gender == 'M') {
                ++maleCount;
            } else if (student.gender == 'F') {
                ++femaleCount;
            }
        }
        cout << "男生数量: " << maleCount << ", 女生数量: " << femaleCount << endl;
    }

    bool isValidGender(char gender) {
        return gender == 'M' || gender == 'F';
    }
};

int main() {
    StudentManager manager;
    int choice;
    Student student;
    string name;
    char gender;

    while (true) {
        cout << "学生信息管理系统" << endl;
        cout << "1. 添加学生信息" << endl;
        cout << "2. 显示所有学生信息" << endl;
        cout << "3. 查找学生信息" << endl;
        cout << "4. 删除学生信息" << endl;
        cout << "5. 编辑学生信息" << endl;
        cout << "6. 按成绩排序学生信息" << endl;
        cout << "7. 按年龄排序学生信息" << endl;
        cout << "8. 显示性别统计" << endl;
        cout << "9. 退出" << endl;
        cout << "请输入您的选择：";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "请输入学生姓名：";
                cin >> student.name;
                cout << "请输入学生年龄：";
                cin >> student.age;
                cout << "请输入学生性别（M/F）：";
                cin >> gender;
                if (!manager.isValidGender(gender)) {
                    cout << "性别输入错误，请重新输入！" << endl;
                    continue;
                }
                student.gender = gender;
                cout << "请输入学生成绩：";
                cin >> student.score;
                manager.addStudent(student);
                break;
            case 2:
                manager.displayStudents();
                break;
            case 3:
                cout << "请输入要查找的学生姓名：";
                cin >> name;
                manager.findStudentByName(name);
                break;
            case 4:
                cout << "请输入要删除的学生姓名：";
                cin >> name;
                manager.deleteStudentByName(name);
                break;
            case 5:
                cout << "请输入要编辑的学生姓名：";
                cin >> name;
                manager.editStudentByName(name);
                break;
            case 6:
                cout << "按成绩排序（1为升序，2为降序）：";
                int order;
                cin >> order;
                manager.sortStudentsByScore(order == 1);
                break;
            case 7:
                cout << "按年龄排序（1为升序，2为降序）：";
                cin >> order;
                manager.sortStudentsByAge(order == 1);
                break;
            case 8:
                manager.displayGenderStatistics();
                break;
            case 9:
                cout << "退出系统" << endl;
                return 0;
            default:
                cout << "无效选择，请重新输入！" << endl;
                break;
        }
    }

    return 0;
}