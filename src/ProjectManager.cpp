#include "ProjectManager.h"
#include <QFile>
#include <QTextStream>
#include <QDir>

ProjectManager::ProjectManager(QObject *parent) : QObject(parent) {}

void ProjectManager::setProjectPath(const QString &path) {
    m_projectPath = path;
}

void ProjectManager::createProject(const QString &path, const QString &templateName) {
    m_projectPath = path;
    
    QDir dir(path);
    if (!dir.exists()) {
        dir.mkpath(".");
    }
    
    QString mainFilePath = path + "/main.cpp";
    QFile file(mainFilePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << getTemplateCode(templateName);
        file.close();
    }
    
    QString cmakeFilePath = path + "/CMakeLists.txt";
    QFile cmakeFile(cmakeFilePath);
    if (cmakeFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&cmakeFile);
        out << "cmake_minimum_required(VERSION 3.16)\n";
        out << "project(MyProject)\n\n";
        out << "set(CMAKE_CXX_STANDARD 20)\n";
        out << "set(CMAKE_CXX_STANDARD_REQUIRED ON)\n\n";
        out << "add_executable(${PROJECT_NAME} main.cpp)\n";
        cmakeFile.close();
    }
}

QString ProjectManager::getTemplateCode(const QString &templateName) {
    if (templateName == "Hello World") {
        return R"(#include <iostream>

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
)";
    }
    else if (templateName == "Basic IO") {
        return R"(#include <iostream>
#include <string>

int main() {
    std::string name;
    std::cout << "Enter your name: ";
    std::cin >> name;
    std::cout << "Hello, " << name << "!" << std::endl;
    return 0;
}
)";
    }
    else if (templateName == "Loops & Conditionals") {
        return R"(#include <iostream>

int main() {
    for (int i = 1; i <= 10; i++) {
        if (i % 2 == 0) {
            std::cout << i << " is even" << std::endl;
        } else {
            std::cout << i << " is odd" << std::endl;
        }
    }
    return 0;
}
)";
    }
    else if (templateName == "Classes & Objects") {
        return R"(#include <iostream>
#include <string>

class Person {
private:
    std::string name;
    int age;

public:
    Person(std::string n, int a) : name(n), age(a) {}
    
    void introduce() {
        std::cout << "Hi, I'm " << name << " and I'm " << age << " years old." << std::endl;
    }
};

int main() {
    Person person("Alice", 25);
    person.introduce();
    return 0;
}
)";
    }
    else if (templateName == "Vectors & Strings") {
        return R"(#include <iostream>
#include <vector>
#include <string>

int main() {
    std::vector<std::string> fruits = {"Apple", "Banana", "Cherry"};
    
    std::cout << "Fruits list:" << std::endl;
    for (const auto& fruit : fruits) {
        std::cout << "- " << fruit << std::endl;
    }
    
    return 0;
}
)";
    }
    
    return R"(#include <iostream>

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
)";
}
