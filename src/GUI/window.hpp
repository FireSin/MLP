#ifndef WIN_HPP
#define WIN_HPP

#include <QtWidgets/QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include <QFileDialog>
#include <QMessageBox>
#include <QTimer>
#include <QColor>
#include <QtWidgets/QCommonStyle>
#include "paintScene.hpp"
#include "../NeuralNetworkCPP/NeuralNetworkManager.h"
#include "trainPreferensWebWidget.hpp"

class window: public QWidget
{
Q_OBJECT
public:
    window();
    void setupUi(QWidget *twin);
    virtual ~window();

private:
    QWidget *win;
    QPushButton *loadFileButton;
    QPushButton *fileDialogButton;
    QLineEdit *lineEditPath;
    QGraphicsView *graphicsView;
    QPushButton *learnWebButton;
    QPushButton *startButton;
    QPushButton *clearPictButton;
    QPushButton *testSampleButton;
    QDoubleSpinBox *partTest;
    QPushButton *newWebButton;
    QPushButton *saveWeightsButton;
    QTimer *timer;
    QGraphicsScene *scene;
    NeuralNetworkManager *web;
    trainPreferensWebWidget *lww;
    QLabel  *labelLearnStatus;
    QGridLayout *gridLayout;
    QHBoxLayout *testPartLayout;
    QHBoxLayout *box;
    QHBoxLayout *hbload;
    QVBoxLayout *vbcapt;
    QVBoxLayout *vblearn;
    std::vector<int> topology;

    void setLineEditAndLabels();
    void setButtons();
    void setWindow(QWidget *twin);
    void setGraphic();
    void clickOpenFileButton();
    void clickLoadFileButton();
    void clickTestSample();
    void slotTimer();
    void clickPredictButton();
    void clickLearnButton();
    void newNeuralNetwork();
    void layoutElements();
    void writeAnswer(QString answer);
};

#endif // WIN_H
