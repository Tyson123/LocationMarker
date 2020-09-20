#include "markerwindow.h"
#include "ui_markerwindow.h"
#include "Test/MarkersParser.cpp"
#include "Test/MarkerManager.h"
#include <QPushButton>
#include <QLabel>
#include <QButtonGroup>
#include <QtMath>
#include <QGridLayout>

struct MarkerWindow::sImpl
{
    QPushButton *button[100];
    QButtonGroup* buttongroup;
    QLabel *markerLabel;
    MarkerManager mm;
    int markerNo=0;
    int buttonCount = 7;
    QPoint menuClickPos;
    int pos;
    QAbstractButton * storeRemovingMarker;
};

MarkerWindow::MarkerWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MarkerWindow),
      mImpl( new sImpl )
{

    ui->setupUi(this);
    this->centralWidget()->setLayout(new QGridLayout);
    this->centralWidget()->layout()->addWidget(ui->exteriorwidget);

    mImpl->markerLabel = new QLabel(ui->centralwidget);

    mImpl->buttongroup = new QButtonGroup(this);
    mImpl->markerLabel->setFixedSize(150,20);

    for (int i = 0; i < 8; ++i)
    {
         mImpl->button[i] = new QPushButton(ui->centralwidget);
         mImpl->button[i]->move(mImpl->mm.getMarker(i).startPosition.x,mImpl->mm.getMarker(i).startPosition.y);
         mImpl->button[i]->setFixedSize(35,35);
         mImpl->button[i]->setCheckable(true);
         mImpl->button[i]->setStyleSheet("QPushButton{background-color: transparent;border-image: url(:/Resources/unmarked.png);background: none;border: none;background-repeat: none; }");
         mImpl->buttongroup->addButton(mImpl->button[i],i);

    }
    connect(mImpl->buttongroup, SIGNAL(buttonClicked(int)),
                this, SLOT(markerClicked(int)));

    ui->backgroundmap->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(ui->backgroundmap, SIGNAL(customContextMenuRequested(const QPoint &)),
            this, SLOT(ShowContextMenu(const QPoint &)));


}

MarkerWindow::~MarkerWindow()
{
    delete ui;
    delete mImpl;
}

void MarkerWindow::markerClicked(int marker)
{

    if(mImpl->button[mImpl->markerNo])
    {
        mImpl->button[mImpl->markerNo]->setStyleSheet("QPushButton{background-color: transparent;border-image: url(:/Resources/unmarked.png);background: none;border: none;background-repeat: none; }");
        mImpl->markerLabel->setText("");
    }

    if(mImpl->button[marker]->isCheckable())
    {
       mImpl->button[marker]->setStyleSheet("QPushButton{background-color: transparent;border-image: url(:/Resources/marked.png);background: none;border: none;background-repeat: none; }");
       mImpl->markerLabel->move(mImpl->button[marker]->pos().x(),mImpl->button[marker]->pos().y()-20);
       mImpl->markerLabel->setText("X : "+QString::number(mImpl->button[marker]->pos().x())+", Y: "+QString::number(mImpl->button[marker]->pos().y()));
    }
    else
    {
       mImpl->button[marker]->setStyleSheet("QPushButton{background-color: transparent;border-image: url(:/Resources/unmarked.png);background: none;border: none;background-repeat: none; }");
       mImpl->markerLabel->setText("");
    }
    mImpl->button[marker]->setCheckable(!mImpl->button[marker]->isCheckable());
    mImpl->markerNo = marker;
}

void MarkerWindow::ShowContextMenu(const QPoint &pos)
{
   QMenu contextMenu(tr("action menu"), this);

   QAction add("Add Marker", this);
   QAction remove("Remove Marker", this);
   contextMenu.addAction(&add);
   contextMenu.addAction(&remove);

   mImpl->menuClickPos = pos;

   connect(&add, SIGNAL(triggered()), this, SLOT(addMarker()));
   connect(&remove, SIGNAL(triggered()), this, SLOT(removeMarker()));

   contextMenu.exec(mapToGlobal(pos));
}

void MarkerWindow::addMarker()
{
    Marker marker;
    marker.startPosition.x = mImpl->menuClickPos.x();
    marker.startPosition.y = mImpl->menuClickPos.y();
    marker.type = marker.ARROW;

    mImpl->mm.addMarker(marker);

    auto count = ++mImpl->buttonCount;

    mImpl->button[count] = new QPushButton(ui->centralwidget);
    mImpl->button[count]->move(marker.startPosition.x,marker.startPosition.y);
    mImpl->button[count]->setFixedSize(35,35);
    mImpl->button[count]->setCheckable(true);
    mImpl->button[count]->setStyleSheet("QPushButton{background-color: transparent;border-image: url(:/Resources/unmarked.png);background: none;border: none;background-repeat: none; }");
    mImpl->buttongroup->addButton(mImpl->button[count],count);
    mImpl->button[count]->show();

}

void MarkerWindow::removeMarker()
{

    QObjectList childs = ui->centralwidget->children();

    std::vector<QAbstractButton *> list;
    auto trackCount = 7;

    for(int i = 0; i < childs.size(); i++)
    {
        QAbstractButton * pushButton = qobject_cast<QAbstractButton *>(childs[i]);
        if(pushButton)
        {
                    list.emplace_back(pushButton);
        }

    }
    for (size_t i = 0;i<list.size();i++) {

            auto calcDist = qSqrt(qPow(mImpl->menuClickPos.x() - list[i]->pos().x(),2) + qPow(mImpl->menuClickPos.y() - list[i]->pos().y(),2));

            if(calcDist < 40 and i > 7)
            {

                for (auto &k : mImpl->button)
                {

                    if(k == list[i])
                    {
                        ++trackCount;
                        list[i]->deleteLater();
                        mImpl->buttongroup->removeButton(k);
                        delete k;
                        k = nullptr;
                        mImpl->mm.removeMarker(i);
                        --mImpl->buttonCount;
                        mImpl->markerLabel->setText("");
                    }
                }

            }

    }

}
