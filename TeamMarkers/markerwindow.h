#ifndef MARKERWINDOW_H
#define MARKERWINDOW_H

#include <QMainWindow>
#include <memory>

QT_BEGIN_NAMESPACE
namespace Ui { class MarkerWindow; }
QT_END_NAMESPACE

class MarkerWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MarkerWindow(QWidget *parent = nullptr);
    ~MarkerWindow();

private slots:
    void markerClicked(int);
    void ShowContextMenu(const QPoint &pos);
    void addMarker();
    void removeMarker();

private:
    Ui::MarkerWindow *ui;

    struct sImpl;
    sImpl *mImpl = nullptr;
};
#endif // MARKERWINDOW_H
