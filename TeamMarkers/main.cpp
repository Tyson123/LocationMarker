#include "markerwindow.h"

#include <QApplication>

#include <QDir>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MarkerWindow w;
    w.maximumSize();
    w.show();
    return a.exec();
}
