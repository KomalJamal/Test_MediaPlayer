#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    player = new QMediaPlayer(this);
    video_widget = new QVideoWidget(this);
    player->setVideoOutput(video_widget);
    this->setCentralWidget(video_widget);

    //Slider
    slider = new QSlider(this);
    slider->setOrientation(Qt::Horizontal);
    ui->statusBar->addPermanentWidget(slider);

    //Slider Connection
    connect(player,&QMediaPlayer::durationChanged,slider,&QSlider::setMaximum);
    connect(player,&QMediaPlayer::positionChanged,slider,&QSlider::setValue);
    connect(slider,&QSlider::sliderMoved,player,&QMediaPlayer::setPosition);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{
    QString fileName =QFileDialog::getOpenFileName(this,"Open a File","","Video File(*.*)");
    on_actionStop_triggered();
    player->setMedia(QUrl::fromLocalFile(fileName));
    on_actionPlay_triggered();

}

void MainWindow::on_actionPlay_triggered()
{
   player->play();
   ui->statusBar->showMessage("Playing....!!!!");
}

void MainWindow::on_actionPause_triggered()
{
    player->pause();
    ui->statusBar->showMessage("Paused....!!!!");
}

void MainWindow::on_actionStop_triggered()
{
    player->stop();
    ui->statusBar->showMessage("Stoped....!!!!");
}
