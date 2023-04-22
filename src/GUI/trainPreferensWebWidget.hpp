//
// Created by firesin on 30.01.23.
//

#ifndef MLP_TRAINPREFERENSWEBWIDGET_HPP
#define MLP_TRAINPREFERENSWEBWIDGET_HPP

#include <QDialog>
#include <QGuiApplication>
#include <QLineEdit>
#include <QLabel>
#include <QComboBox>
#include <QtWidgets/QPushButton>
#include <QFileDialog>
#include <QMessageBox>
#include <QDoubleSpinBox>
#include <QGridLayout>
#include <QProcess>
#include <QDialogButtonBox>
#include <QtWidgets/QCommonStyle>
#include <QRadioButton>
#include <QGroupBox>
#include <QFormLayout>
#include "../NeuralNetworkCPP/NeuralNetworkManager.h"
#include "TrainingNN/trainDialog.hpp"

class trainPreferensWebWidget: public QDialog{
    Q_OBJECT

public:
    trainPreferensWebWidget(NeuralNetworkManager *pWeb, std::vector<int> &topology, QLabel *labelSt, QWidget *parent = nullptr);

    ~trainPreferensWebWidget();

private:
    void setupUi(QWidget *twin);
    void setWindow(QWidget *twin);
    void setLayers();
    void setRadioButtons();
    void numberEpochGroups();
    void setButtons();
    void layoutElements();
    void clickOpenButton();
    void clickLearnButton();
    void clickLoadWeightsButton();

    NeuralNetworkManager *web;
    std::vector<int>& topology;
    QWidget *win;
    QLineEdit *lineEditPath;
    std::vector<QSpinBox> layers;
    QLabel *labelStatus;
    QSpinBox *sliderEpoch;
    QSpinBox *sliderGroups;
    QPushButton *buttonOpenFile;
    QPushButton *buttonLearn;
    QPushButton *buttonCancel;
    QPushButton *buttonLoadWeights;
    QRadioButton *radioButtonMatrix;
    QRadioButton *radioButtonGraph;
    QHBoxLayout *hBoxLayers;
    QHBoxLayout *hOpenFile;
    QVBoxLayout *vView;
    QGroupBox *groupRadioButton;
    QGroupBox *groupLayers;
    QFormLayout *formLayout;
    QGridLayout *gridLayout;
};

#endif //MLP_TRAINPREFERENSWEBWIDGET_HPP
