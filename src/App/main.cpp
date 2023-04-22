#include <thread>
#include "main.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    window x;
    x.show();
    return a.exec();
}

