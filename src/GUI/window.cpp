//
// Created by firesin on 24.12.22.
//
#include <QtWidgets/qprogressdialog.h>
#include "window.hpp"

window::window() {
    topology = {784, 500, 405, 26};
    setupUi(this);
}

void window::setupUi(QWidget *twin){
    setWindow(twin);
    setButtons();
    setLineEditAndLabels();
    setGraphic();
    newNeuralNetwork();
    layoutElements();
}

window::~window() {
    delete loadFileButton;
    delete fileDialogButton;
    delete learnWebButton;
    delete saveWeightsButton;
    delete startButton;
    delete testSampleButton;
    delete partTest;
    delete clearPictButton;
    delete lineEditPath;
    delete graphicsView;
    delete timer;
    delete scene;
    delete web;
    delete labelLearnStatus;
    delete testPartLayout;
    delete hbload;
    delete vblearn;
    delete vbcapt;
    delete box;
    delete gridLayout;
}

void window::setWindow(QWidget *twin) {
    this->win = twin;
    win->setWindowTitle("MLP");
    gridLayout = new QGridLayout(this);
    this->setLayout(gridLayout);
    lww = nullptr;
}

void window::setButtons() {
    QCommonStyle style;
    loadFileButton = new QPushButton(style.standardIcon(QStyle::SP_ArrowDown), "Load file", win);
    loadFileButton->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    fileDialogButton = new QPushButton(style.standardIcon(QStyle::SP_DialogOpenButton), "Open", win);
    fileDialogButton->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    clearPictButton = new QPushButton(style.standardIcon(QStyle::SP_LineEditClearButton), "Clear picture", win);
    clearPictButton->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    learnWebButton = new QPushButton(style.standardIcon(QStyle::SP_DialogYesButton), "Training", win);
    learnWebButton->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    startButton = new QPushButton(style.standardIcon(QStyle::SP_DialogApplyButton), "Predict", win);
    startButton->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    testSampleButton = new QPushButton(style.standardIcon(QStyle::SP_DialogApplyButton), "Run on a test sample", win);
    testSampleButton->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    newWebButton = new QPushButton(style.standardIcon(QStyle::SP_BrowserReload), "Create new MLP", win);
    newWebButton->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    saveWeightsButton = new QPushButton(style.standardIcon(QStyle::SP_DialogSaveButton), "Save weights", win);
    saveWeightsButton->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    connect(loadFileButton, &QPushButton::clicked, [this] { clickLoadFileButton();});
    connect(fileDialogButton, &QPushButton::clicked, [this]{ clickOpenFileButton();});
    connect(clearPictButton, &QPushButton::clicked, [this]{scene->clear();});
    connect(startButton, &QPushButton::clicked, this, [this]{ clickPredictButton();});
    connect(learnWebButton, &QPushButton::clicked, this, &window::clickLearnButton);
    connect(testSampleButton, &QPushButton::clicked, this, &window::clickTestSample);
    connect(newWebButton, &QPushButton::clicked, this, [this]{delete web; newNeuralNetwork();});
    connect(saveWeightsButton, &QPushButton::clicked, this, [this]{web->SaveWeightFromNetwork(web->getAccuracy(), 0, "");});
}

void window::setLineEditAndLabels() {
    lineEditPath = new QLineEdit(win);
    lineEditPath->setPlaceholderText("Click Open and select the file");
    lineEditPath->setReadOnly(true);
    lineEditPath->setMaximumWidth(280);
    labelLearnStatus = new QLabel(win);
    partTest = new QDoubleSpinBox(win);
    partTest->setRange(0, 1);
    partTest->setSingleStep(0.1);
    partTest->setValue(1.0);
}


void window::setGraphic() {
    graphicsView = new QGraphicsView(win);
    graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    timer = new QTimer();
    scene = new paintScene();
    graphicsView->setFixedSize(280, 280);
    scene->setSceneRect(graphicsView->rect());
    graphicsView->setScene(scene);
    scene->setBackgroundBrush(QBrush(Qt::white));
    connect(timer, &QTimer::timeout, this, [this]{slotTimer();});
    timer->start(100);
}

void window::slotTimer() {
    timer->stop();
    scene->setSceneRect(graphicsView->x() + 10,graphicsView->y() + 10,graphicsView->width() - 20, graphicsView->height() - 20);
}

void window::layoutElements() {

    box = new QHBoxLayout;
    hbload = new QHBoxLayout;
    vbcapt = new QVBoxLayout;
    vblearn = new QVBoxLayout;
    testPartLayout = new QHBoxLayout;
    hbload->addWidget(lineEditPath);
    hbload->addWidget(fileDialogButton);
    hbload->addWidget(loadFileButton);
    vblearn->addWidget(labelLearnStatus);
    vblearn->addWidget(learnWebButton);
    vblearn->addWidget(newWebButton);
    vblearn->addWidget(saveWeightsButton);
    testPartLayout->addWidget(testSampleButton);
    testPartLayout->addWidget(partTest);
    vblearn->addLayout(testPartLayout);
    vbcapt->addLayout(vblearn);
    vbcapt->addWidget(clearPictButton);
    vbcapt->addWidget(startButton);
    box->addWidget(graphicsView);
    box->addLayout(vbcapt);
    gridLayout->addLayout(hbload, 0, 0, Qt::AlignLeft);
    gridLayout->addLayout(box, 1, 0, Qt::AlignLeft);
    win->setFixedSize(win->sizeHint());
}

void window::clickLearnButton() {
    lww = new trainPreferensWebWidget(web, topology, labelLearnStatus);
    lww->exec();
    delete lww;
}

void window::clickOpenFileButton(){
    QString filepath = QFileDialog::getOpenFileName(win, "Open file", "~", "BMP files(*.bmp)");
    lineEditPath->setText(filepath);
}

void window::clickLoadFileButton() {
    QFile file(lineEditPath->text());
    if (lineEditPath->text().isEmpty()) {
        QMessageBox::warning(win, "Error", "Write or or select the path to the file");
        return;
    }
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(win, "Error", "File can't open");
        return;
    }
    QImage image(file.fileName());
    if (image.width() > 512 || image.width() < 28 || image.height() > 512 || image.height() < 28){
        QMessageBox::warning(win, "Error", "Bad size picture");
        file.close();
        return;
    }
    file.close();
    scene->clear();
    image = image.scaled(scene->width(), scene->height(), Qt::KeepAspectRatio);
    QPixmap pixmap = QPixmap::fromImage(image);
    QGraphicsPixmapItem* item = scene->addPixmap(pixmap);
    item->setPos(scene->sceneRect().x() + ((scene->width() - image.width()) / 2), scene->sceneRect().y());
}


void window::clickPredictButton() {
    QImage image(28, 28, QImage::Format_Grayscale16);
    QPainter painter(&image);
    scene->render(&painter);
    painter.end();
    image = image.transformed(QTransform().rotate(-90));
    std::vector<double> in;
    in.reserve(28 * 28);
    for (int j = image.width()-1; j >= 0; j--) {
        for (int i = 0; i < image.height(); i++) {
            in.push_back(255 - image.pixelColor(i, j).lightness());
            std::cout << 255 - image.pixelColor(i, j).lightness() << "\t";
        }
        std::cout << std::endl;
    }
    scene->clear();
    int ans = web->Predict(in, 1, true);
    writeAnswer("Answer: " + QString::fromStdString(std::string(1, ans + 64)));
}

void window::clickTestSample() {
    QString filepath = QFileDialog::getOpenFileName(win, "Open file", "~", "CSV files(*.csv)");
    std::string path = filepath.toStdString();
    if (path.empty()){
        QMessageBox::warning(win, "Error", "File can't open");
        return;
    }
    QProgressDialog dialog("Processing...", nullptr, 0, 0, this);
    dialog.setWindowModality(Qt::WindowModal);
    dialog.setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::CustomizeWindowHint);
    dialog.setLabelText("Please wait...");
    dialog.setRange(0,0);
    dialog.show();
    web->SetValidationPartOfTrainingDataset(0);
    //TODO Загрузить при передачи части тестовой выборки и вырожденую ситуацию при 0
//    web->testSet->LoadFromCSV(path, ',', 0, false);
//    web->testSet->MoveToValidationSet(partTest->value());
    QMessageBox *msgBox = new QMessageBox(this);
    msgBox->deleteLater();
    msgBox->setWindowTitle("Result");
    msgBox->setWindowFlags(msgBox->windowFlags() | Qt::WindowStaysOnTopHint);
    web->LoadTrainSet(path, 784, 26);
    StopWatch* timer = new StopWatch;
    timer->Start();
    std::thread myTread(&NeuralNetworkManager::CalculateMetricsForTestSet, web, web->trainingSet->trainInputs, web->trainingSet->trainTargets, 10);
    myTread.join();
    timer->Stop();
    QString result = QString::fromStdString("average accuracy:\t" + std::to_string(web->getAccuracy()) +
                                                "\nprecision:\t\t" + std::to_string(web->getPrecision()) +
                                                "\n recall:\t\t" + std::to_string(web->getRecall()) +
                                                "\n f-measure:\t\t" + std::to_string(web->getFscore()) +
                                                "\n time:\t\t" + timer->Stop());
    msgBox->setText(result);
    delete timer;
    msgBox->exec();
}

void window::newNeuralNetwork() {
    web = new NeuralNetworkManager;
    web->LoadMatrixNN(topology);
    labelLearnStatus->setText("MLP is not trained");
    labelLearnStatus->setStyleSheet("QLabel { color: red; }");
}

void window::writeAnswer(QString answer) {
    QMessageBox msgBox;
    msgBox.setWindowTitle("Result");
    msgBox.setWindowFlags(msgBox.windowFlags() | Qt::WindowStaysOnTopHint);
    msgBox.setText(answer);
    msgBox.exec();
}

