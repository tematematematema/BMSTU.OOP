#include "mainwindow.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

static void showModelProj(QGraphicsScene *const graphicsScene, const modelProjT *const modelProj)
{
    QPen outlinePen(Qt::white);

    double dX = SCENE_WIDTH / 2 - modelProj->center.x;
    double dZ = SCENE_HEIGHT / 2 - modelProj->center.z;

    for (int i = 0; i < modelProj->pointsProjNumber; i++)
    {
        for (int j = 0; j < modelProj->pointsProjNumber; j++)
        {
            if (modelProj->linksMatrix[i][j])
            {
                double xB = modelProj->pointsProjArray[i].x + dX;
                double xE = modelProj->pointsProjArray[j].x + dX;
                double zB = modelProj->pointsProjArray[i].z + dZ;
                double zE = modelProj->pointsProjArray[j].z + dZ;
                graphicsScene->addLine(xB, zB, xE, zE, outlinePen);;
            }
        }
    }
}

void MainWindow::uploadModelWithFileData()
{
    int errorCode = 0;

    QString filePath = QFileDialog::getOpenFileName(this, "Open file", QDir::homePath());
    string fileName = filePath.toStdString();
    operParamsT operParams = {fileName, UPLOAD, 0};

    errorCode = handler(&model, &modelProj, &operParams);
    ui->graphicsView->setSceneRect(0, 0, SCENE_WIDTH, SCENE_HEIGHT);
    if (errorCode == SUCCESS)
    {
        QGraphicsScene *graphicsScene = new QGraphicsScene();
        showModelProj(graphicsScene, &modelProj);
        ui->graphicsView->setScene(graphicsScene);
    }
}

void MainWindow::on_pushButton_clicked()
{
    int errorCode = 0;

    QString filePath = QFileDialog::getOpenFileName(this, "Open file", QDir::homePath());
    string fileName = filePath.toStdString();
    operParamsT operParams = {fileName, UPLOAD, 0};

    errorCode = handler(&model, &modelProj, &operParams);
    ui->graphicsView->setSceneRect(0, 0, SCENE_WIDTH, SCENE_HEIGHT);
    if (errorCode == SUCCESS)
    {
        cout << "\n\n" << "SUCCESS";
        QGraphicsScene *graphicsScene = new QGraphicsScene();
        showModelProj(graphicsScene, &modelProj);
        ui->graphicsView->setScene(graphicsScene);
    }
}
