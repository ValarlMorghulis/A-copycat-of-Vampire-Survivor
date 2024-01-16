#include"public.h"

int money;
int level;
int unlockedrole;
int addhp;
int addspeed;
int addzone;
int subintrval;
int maxhp;
int addduration;
int chosenrole;
int chosenmap;
QMediaPlayer *player;
QMediaPlaylist *playerlist;
QMediaPlayer *music;
QMediaPlaylist *musiclist;
int playerhp=100;
int shootnumber=1;
int kill=0;
int gain=0;
int zone=300;
QTime gametime;
int read=0;

QFile file;


void update(){
    file.open(QIODevice::WriteOnly|QFile::Truncate); //判断文件是否正常打开
    QTextStream text_stream(&file);
    text_stream<<"money"<<endl<<money<<endl<<"level"<<endl<<level<<endl<<"role3 unlocked"<<endl<<unlockedrole<<endl<<"maxhp++"<<endl<<maxhp<<endl<<"hp++"<<endl<<addhp<<endl<<"speed++"<<endl<<addspeed<<endl<<"collextzone++"<<endl<<addzone<<endl<<"intrval--"<<endl<<subintrval<<endl<<"duration++"<<endl<<addduration<<endl;
    file.flush();
    file.close();
}


void addmoney(int amount){
    money=money+amount;
    update();
}


void submoney(int amount){
    money=money-amount;
    update();
}
