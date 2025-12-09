#include "MainWindow.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    app.setApplicationName("C++ Learning IDE");
    app.setOrganizationName("CppLearn");
    
    MainWindow window;
    window.show();
    
    return app.exec();
}
