//
// Created by Rogelio Rast on 3/1/23.
//

#ifndef MLP_TRAINDIALOG_HPP
#define MLP_TRAINDIALOG_HPP

#include <QDialog>
#include <QtCore/QThread>
#include <QLabel>
#include <QProgressBar>
#include <QFormLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QCommonStyle>
#include <QChart>
#include <QSplineSeries>
#include <QChartView>
#include "../../NeuralNetworkCPP/NeuralNetworkManager.h"
#include "Worker.hpp"

class trainDialog: public QDialog {
    Q_OBJECT
public:
    trainDialog(NeuralNetworkManager *web, std::vector<int>  topology, int epochs, std::string filepathData,
                QWidget *parent = nullptr);
    virtual ~trainDialog();

private:
    void setupUI(QWidget* win);
    void setWindow();
    void setProgress();
    void layoutElements();
    void setChart();
    void setLabels();

    QWidget *win;
    NeuralNetworkManager *network;
    Worker *worker;
    QThread *thread;
    int epochs;
    int curEpoch;
    QGridLayout *gridLayout;
    QLabel *labelTopology;
    QLabel *labelFilepath;
    QChartView *chartView;
    QChart *chart;
    QSplineSeries *series;
    std::vector<int> topology;
    std::string filepath;

    signals:
    void startWorker();

private slots:
    void onAccuracyChanged(double error);
    void onFileLoaded();

protected:
    void closeEvent(QCloseEvent *event) override {
        thread->requestInterruption();
        thread->sleep(1);
        thread->terminate();
        thread->wait();
        QWidget::closeEvent(event);
    }

};


#endif //MLP_TRAINDIALOG_HPP
