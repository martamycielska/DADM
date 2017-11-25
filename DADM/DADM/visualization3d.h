#ifndef VISUALIZATION3D_H
#define VISUALIZATION3D_H
#include <QMainWindow>

namespace Ui {
    class Visualization3D;
}

class Visualization3D : public QMainWindow
{
    Q_OBJECT

    public:
        explicit Visualization3D(QWidget *parent = 0);

    private:
        Ui::Visualization3D *ui;
        QString processDescString;

    private slots:
        void brain3D();
};

#endif // VISUALIZATION3D_H
