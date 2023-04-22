//
// Created by firesin on 30.01.23.
//

#include <QException>
#include "trainPreferensWebWidget.hpp"

trainPreferensWebWidget::trainPreferensWebWidget(NeuralNetworkManager *pWeb, std::vector<int> &topology, QLabel *labelSt, QWidget *parent)
        : QDialog(parent), topology(topology){
    this->web = pWeb;
    this->labelStatus = labelSt;
    setupUi(this);
}

void trainPreferensWebWidget::setupUi(QWidget *twin) {
    setWindow(twin);
    setRadioButtons();
    setLayers();
    numberEpochGroups();
    setButtons();
    layoutElements();
}

void trainPreferensWebWidget::setWindow(QWidget *twin) {
    win = twin;
    lineEditPath = new QLineEdit(win);
    lineEditPath->setPlaceholderText("Set path of file sample");
    lineEditPath->setReadOnly(true);
    win->setWindowTitle("MLP learn");
    gridLayout = new QGridLayout;
    this->setLayout(gridLayout);
}

void trainPreferensWebWidget::setLayers() {
    layers = std::vector<QSpinBox>(7);
    layers[0].setRange(1, 999);
    layers[0].setValue(784);
    layers[0].setEnabled(false);
    for (int i = 1; i < layers.size()-1; i++){
        layers[i].setRange(0, 999);
        layers[i].setSingleStep(1);
    }
    layers[1].setValue(120);
    layers[2].setValue(120);
    layers[6].setValue(26);
    layers[6].setEnabled(false);
    groupLayers = new QGroupBox(tr("Topology"));
    hBoxLayers = new QHBoxLayout;
    for (int i = 0; i < layers.size(); i++){
        hBoxLayers->addWidget(&layers[i]);
    }
    groupLayers->setLayout(hBoxLayers);
}

void trainPreferensWebWidget::numberEpochGroups() {
    sliderEpoch = new QSpinBox(win);
    sliderGroups = new QSpinBox(win);
    sliderEpoch->setRange(1, 99);
    sliderEpoch->setSingleStep(1);
    sliderGroups->setRange(1, 99);
    sliderGroups->setSingleStep(1);
    formLayout = new QFormLayout;
    formLayout->addRow(tr("Epoch:"), sliderEpoch);
    formLayout->addRow(tr("Groups:"), sliderGroups);
    groupRadioButton = new QGroupBox(tr("View"));
    vView = new QVBoxLayout;
    vView->addWidget(radioButtonMatrix);
    vView->addWidget(radioButtonGraph);
    groupRadioButton->setLayout(vView);
}

void trainPreferensWebWidget::setButtons() {
    QCommonStyle style;
    buttonOpenFile = new QPushButton(style.standardIcon(QStyle::SP_DialogOpenButton), "Open", win);
    buttonLearn = new QPushButton(style.standardIcon(QStyle::SP_DialogOkButton), "Learn", win);
    buttonCancel = new QPushButton(style.standardIcon(QStyle::SP_DialogCancelButton), "Cancel",win);
    buttonLoadWeights = new QPushButton(style.standardIcon(QStyle::SP_ArrowUp), "Load weights", win);
    buttonOpenFile->connect(buttonOpenFile, &QPushButton::clicked, [this]{ clickOpenButton();});
    buttonCancel->connect(buttonCancel, &QPushButton::clicked, [this]{this->close();});
    buttonLearn->connect(buttonLearn, &QPushButton::clicked, [this]{this->clickLearnButton();});

    buttonLoadWeights->connect(buttonLoadWeights, &QPushButton::clicked, [this]{ clickLoadWeightsButton();});
    hOpenFile = new QHBoxLayout;
    hOpenFile->addWidget(lineEditPath);
    hOpenFile->addWidget(buttonOpenFile);
}

void trainPreferensWebWidget::setRadioButtons() {
    radioButtonGraph = new QRadioButton("Graph view");
    radioButtonMatrix = new QRadioButton("Matrix view");
    radioButtonMatrix->setChecked(true);
}

void trainPreferensWebWidget::layoutElements() {
    gridLayout->addLayout(hOpenFile, 0, 0, 1, 0);
    gridLayout->addLayout(formLayout, 1, 0);
    gridLayout->addWidget(groupRadioButton, 1, 1);
    gridLayout->addWidget(groupLayers, 2, 0, 1, 0);
    gridLayout->addWidget(buttonLoadWeights, 3, 0);
    gridLayout->addWidget(buttonLearn, 3, 1);
    gridLayout->addWidget(buttonCancel, 3, 2);
    this->setFixedSize(this->sizeHint());
}

void trainPreferensWebWidget::clickLoadWeightsButton() {
    std::string filepath = QFileDialog::getOpenFileName(win, "Open file", "~", "Weights files(*.weights)").toStdString();
    if (filepath.empty())
        return;
    web->LoadWeightToNetwork(filepath);
    labelStatus->setText("Is learned");
    labelStatus->setStyleSheet("QLabel { color: green; }");
    this->close();
}

void trainPreferensWebWidget::clickLearnButton() {
    topology = std::vector<int>(layers.size());
    for (int i = 0; i < layers.size(); i++) {
        topology[i] = layers[i].value();
    }
    for (auto i = topology.begin(); i != topology.end(); i++) {
        while (*i == 0 && i != topology.end())
            topology.erase(i);
    }
    std::string filePath = lineEditPath->text().toStdString();
    if (filePath.empty()){
        QMessageBox::warning(win, "Error", "Write or or select the path to the file");
        return;
    }
    if (topology.size() < 4){
        QMessageBox::warning(win, "Error", "You need from 2 to 5 hidden layers");
        return;
    }
    trainDialog *train = new trainDialog(web, topology, sliderEpoch->value(), filePath, this);
    train->exec();
    delete train;
    labelStatus->setText("Is learned");
    labelStatus->setStyleSheet("QLabel { color: green; }");
    this->close();
}

void trainPreferensWebWidget::clickOpenButton(){
    QString filepath = QFileDialog::getOpenFileName(win, "Open file", "~", "CSV files(*.csv)");
    lineEditPath->setText(filepath);
}

trainPreferensWebWidget::~trainPreferensWebWidget() {
    delete lineEditPath;
    delete sliderEpoch;
    delete sliderGroups;
    delete buttonOpenFile;
    delete buttonLearn;
    delete buttonCancel;
    delete buttonLoadWeights;
    delete radioButtonMatrix;
    delete radioButtonGraph;
    delete hOpenFile;
    delete vView;
    delete groupRadioButton;
    delete hBoxLayers;
    delete formLayout;
    delete gridLayout;
}

