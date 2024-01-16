#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setFixedSize(1920,1200);

    //音频
    music=new QMediaPlayer(this);
    musiclist=new QMediaPlaylist(this);
    musiclist->addMedia(QUrl::fromLocalFile("D:\\QTgame\\1\\1\\resourses\\beginning.mp3"));
    musiclist->addMedia(QUrl::fromLocalFile("D:\\QTgame\\1\\1\\resourses\\forest.mp3"));
    musiclist->addMedia(QUrl::fromLocalFile("D:\\QTgame\\1\\1\\resourses\\library.mp3"));
    musiclist->addMedia(QUrl::fromLocalFile("D:\\QTgame\\1\\1\\resourses\\start.mp3"));
    musiclist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    music->setPlaylist(musiclist);
    music->setVolume(50); //0~100音量范围,默认是100
    musiclist->setCurrentIndex(3);
    music->play();

    player=new QMediaPlayer(this);
    player->setMedia(QUrl::fromLocalFile("D:\\QTgame\\1\\1\\resourses\\draw.mp3"));
    player->setVolume(50);
}

void Widget::mousePressEvent(QMouseEvent *event){
    QString filename=QFileDialog::getOpenFileName(this,"选择存档","*.txt");
    file.setFileName(filename);
    this->in=new interface;
    this->in->show();
    this->close();
}

void Widget::keyPressEvent(QKeyEvent *event){
    QString filename=QFileDialog::getOpenFileName(this,"选择存档");
    file.setFileName(filename);
    this->in=new interface;
    this->in->show();
    this->close();
}

Widget::~Widget()
{
    delete ui;
}
