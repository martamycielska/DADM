#include "dadm.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DADM w;
    w.show();

    return a.exec();
}
