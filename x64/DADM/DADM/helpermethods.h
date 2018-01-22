#ifndef HELPERMETHODS_H
#define HELPERMETHODS_H
#include <QMainWindow>

typedef enum FilteringType { LMMSE, UNLM, NONE } FilteringType;

class HelperMethods{
    public:
        HelperMethods();
        static void SetCenterPosition(QMainWindow *window);
};
#endif // HELPERMETHODS_H
