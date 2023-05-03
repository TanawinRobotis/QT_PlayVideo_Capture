#include "mainwindow.h"
#include "ui_mainwindow.h"


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

void MainWindow::playVideo()
{
    videoCapture = cv::VideoCapture("D:/AI-Center/Computing/QT/Lab11-CaptureVideo/resource/Japan traffic.mp4");
    if (!videoCapture.isOpened()) {
        qDebug() << "Error opening video file";
        return;
    }
    cv::Mat frame;
    while (videoCapture.read(frame)) {
        cv::cvtColor(frame, frame, cv::COLOR_BGR2RGB);
        QImage qimg(frame.data, frame.cols, frame.rows, QImage::Format_RGB888);
        ui->label->setPixmap(QPixmap::fromImage(qimg));
        ui->label->setScaledContents(true);
        QCoreApplication::processEvents();
    }
}



void MainWindow::on_pushButton_clicked()
{
    playVideo();
}


void MainWindow::on_pushButton_2_clicked()
{
    // Read a frame from the video capture
    cv::Mat frame;
    bool success = videoCapture.read(frame);

    if(success)
    {
        // Get the current date and time to use as part of the file name
        QDateTime currentDateTime = QDateTime::currentDateTime();
        QString fileName = "D:/AI-Center/Computing/QT/Lab11-CaptureVideo/resource/output/capture_" + currentDateTime.toString("yyyy-MM-dd_HH-mm-ss") + ".jpg";

        // Save the image to the file system
        cv::imwrite(fileName.toStdString(), frame);

        // Display a message in the text browser indicating that the image was saved
        ui->textBrowser->append(tr("Image saved to %1").arg(fileName));
    }
    else
    {
        ui->textBrowser->append(tr("Failed to capture image"));
    }
}
