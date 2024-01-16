#ifndef PUBLIC_H
#define PUBLIC_H

#include <QWidget>
#include<QMediaPlayer>
#include<QMediaPlaylist>
#include<QAudioOutput>
#include<QUrl>
#include<QFile>
#include<QTime>

//从存档内读取的内容
extern int money;
extern int level;
extern int unlockedrole;
extern int addhp;
extern int addspeed;
extern int addzone;
extern int subintrval;
extern int maxhp;
extern int addduration;

extern QFile file;//存档地址
extern int read;

//公共变量，便于每个界面使用
extern int chosenrole;
extern int chosenmap;
extern QMediaPlayer *player;
extern QMediaPlaylist *playerlist;
extern QMediaPlayer *music;
extern QMediaPlaylist *musiclist;

extern int playerhp;//血量
extern int shootnumber;//发射物数量
extern int kill;//击杀数
extern int gain;//获取的金币
extern int zone;//拾取范围
extern QTime gametime;

extern void update();//更新存档
extern void addmoney(int amount);
extern void submoney(int amount);


#endif // PUBLIC_H
