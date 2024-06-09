#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "QGenericMatrix"
#include "cmath"
#include "QString"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(
            ui->Drawgraphic, &QPushButton::clicked,
            this, &MainWindow::massiv
        );
    connect(
            ui->left, &QPushButton::clicked,
            this, [=]() {
        step(points);
    }

        );
    connect(
            ui->right, &QPushButton::clicked,
            this, [=](){
                    step(points);
                }
        );
    connect(
            ui->Upward, &QPushButton::clicked,
            this, [=]() {
        step(points);
    }

        );
    connect(
            ui->Downward, &QPushButton::clicked,
            this, [=]() {
        step(points);
    }
        );
    connect(
            ui->compX, &QPushButton::clicked,
                this, [=]() {
        size(points, Point1);
    }
        );
    connect(
            ui->compY, &QPushButton::clicked,
            this, [=]() {
        size(points, Point1);
    }
        );
    connect(
            ui->stretX, &QPushButton::clicked,
            this,[=]() {
        size(points, Point1);
    }
        );
    connect(
            ui->stretY, &QPushButton::clicked,
            this, [=]() {
        size(points, Point1);
    }
        );
    connect(
            ui->turnFirst, &QPushButton::clicked,
                this, [=]() {
        turn(points, Point1);
    }
    );
    connect(
            ui->turnSecond, &QPushButton::clicked,
            this, [=]() {
        turn(points, Point1);
    }
    );
    connect(
            ui->input2, &QPushButton::clicked,
            this, [=]() {
        point(points);
    }
    );


    QGraphicsScene* scene = new QGraphicsScene(this);
    pmi = scene->addPixmap(QPixmap());
    ui->gvPlotter->setScene(scene);

    linePen1 = QPen(QColor::fromRgb(0,0,255));
    linePen1.setWidth(2);
    //scene->addEllipse(0, 0, 10, 10, Qt::NoPen, QColor(Qt::black));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::massiv(){
    points.clear();
        int n = ui->QTable->rowCount();
        points.reserve(n);
        for(int i = 0; i < n; i++){
            QTableWidgetItem *itemX = ui->QTable->item(i,0);
            QTableWidgetItem *itemY = ui->QTable->item(i,1);
            if(itemX && itemY){
                double x = itemX->text().toDouble();
                double y = itemY->text().toDouble();
                points.push_back(QPointF(x,y));
            }
        }
        DrawPol(points);

}
void MainWindow::DrawPol(const std::vector<QPointF>& points){
    QPixmap image(ui->gvPlotter->rect().size().shrunkBy(QMargins(0, 0, 0, 0)));
    clear(image,QColor :: fromRgb(255,255,255));
    QPainter p(&image);
    p.setPen(linePen1);
    p.drawPolygon(points.data(),points.size());
    p.drawEllipse(ui->gvPlotter->width()/2,ui->gvPlotter->height()/2, 10, 10);
    pmi->setPixmap(image);

}

void MainWindow::clear(QPixmap& image, const QColor& color)
{
    QPainter p(&image);
    p.fillRect(image.rect(), color);
}

void MainWindow::step(std::vector<QPointF>& points){
    QPushButton* pb = qobject_cast<QPushButton*>(sender());
    QString comand = pb->objectName();
    if(comand == "right"){
    for(int i = 0; i < points.size();i++){
        points[i].setX(points[i].x() + 20);
    }
    }
    if(comand == "left"){
        for(int i = 0; i < points.size();i++){
            points[i].setX(points[i].x() - 20);
        }
    }
    if(comand == "Upward"){
        for(int i = 0; i < points.size();i++){
            points[i].setY(points[i].y() - 20);
        }
    }
    if(comand == "Downward"){
        for(int i = 0; i < points.size();i++){
            points[i].setY(points[i].y() + 20);
        }
    }
    point(points);
    DrawPol(points);
}

void MainWindow::turn(std::vector<QPointF>& points, QPointF point){
    QPushButton* pb = qobject_cast<QPushButton*>(sender());
    QString comand = pb->objectName();
    //point(points);
    t.clear();
    t.reserve(1);
    if(comand == "turnFirst"){
        QGenericMatrix <2,2,double> Matrix;
        Matrix(0,0) = cos((10*M_PI)/180);
        Matrix(0,1) = -sin((10*M_PI)/180);
        Matrix(1,0) = sin((10*M_PI)/180);
        Matrix(1,1) = cos((10*M_PI)/180);
        for(int i = 0 ; i<points.size(); i++){
            double x1 = points[i].x() - point.x();
            double y1 = points[i].y() - point.y();
            double t1 = x1;
            x1 = Matrix(0,0)*x1 + Matrix(0,1)*y1;
            y1 = Matrix(1,0)*t1 + Matrix(1,1)*y1;
            t.push_back(QPointF(x1,y1));
            points[i].setX(t[i].x() + point.x());
            points[i].setY(t[i].y() + point.y());
        }
    }
    if(comand == "turnSecond"){
        QGenericMatrix <2,2,double> Matrix;
        Matrix(0,0) = cos(-(10*M_PI)/180);
        Matrix(0,1) = -sin(-(10*M_PI)/180);
        Matrix(1,0) = sin(-(10*M_PI)/180);
        Matrix(1,1) = cos(-(10*M_PI)/180);
        for(int i = 0 ; i<points.size(); i++){

        double x1 = points[i].x() - point.x();
        double y1 = points[i].y() - point.y();
        double t1 = x1;
        x1 = Matrix(0,0)*x1 + Matrix(0,1)*y1;
        y1 = Matrix(1,0)*t1 + Matrix(1,1)*y1;
        t.push_back(QPointF(x1,y1));
        points[i].setX(t[i].x() + point.x());
        points[i].setY(t[i].y() + point.y());
        }
    }

    DrawPol(points);
}

void MainWindow::size(std::vector<QPointF>& points, QPointF point){
    QPushButton* pb = qobject_cast<QPushButton*>(sender());
    QString comand = pb->objectName();
    g.clear();
    g.reserve(1);
    double k = 0.5;
    if(comand == "compX"){
        for(int i = 0; i < points.size(); i++){
            g[i].setX(points[i].x() - point.x());
            points[i].setX(point.x() + k*g[i].x());
        }
    }
    if(comand == "stretX"){
        for(int i = 0; i < points.size(); i++){
            g[i].setX(points[i].x() - point.x());
            points[i].setX(point.x() + (1.0/k)*g[i].x());
        }
    }
    if(comand == "compY"){
        for(int i = 0; i < points.size(); i++){
            g[i].setY(points[i].y() - point.y());
            points[i].setY(point.y() + k*g[i].y());
        }
    }
    if(comand == "stretY"){
        for(int i = 0; i < points.size(); i++){
            g[i].setY(points[i].y() - point.y());
            points[i].setY(point.y() + (1.0/k)*g[i].y());
        }
    }
    DrawPol(points);
}

void MainWindow::point(const std::vector<QPointF>& points){
    QString a = ui->leInput2->text();
    bool ok;
    int k;
    k = a.toInt(&ok);
    if(k == 0){
        Point1.setX(ui->gvPlotter->rect().width()/2.0);
        Point1.setY(ui->gvPlotter->rect().height()/2.0);
    }
    else{
    Point1.setX(points[k-1].x());
    Point1.setY(points[k-1].y());

    }

}



void MainWindow::on_Input_clicked(){
    QString s = ui->LeInput->text();
    bool ok;
    n = s.toInt(&ok);
    ui->QTable->setRowCount(n);
}



