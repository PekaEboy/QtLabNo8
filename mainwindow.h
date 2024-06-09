#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPainter>


#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void DrawPol(const std::vector <QPointF>& points);
    void clear(QPixmap& image, const QColor& color);
    void on_Input_clicked();
    void point(const std::vector <QPointF>& points);
    void massiv();
    void step(std::vector <QPointF>& points);
    void turn(std::vector <QPointF>& points, QPointF point);
    void size(std::vector<QPointF>& points, QPointF point);


private:
    Ui::MainWindow *ui;
    int n;

    QPointF Point1;

    std::vector <QPointF> points;
    std::vector <QPointF> t;
    std::vector <QPointF> g;
    std::vector <QPointF> k;

    QPen linePen1;
    QGraphicsScene *scene;
    QGraphicsPixmapItem *pmi;
};
#endif // MAINWINDOW_H
