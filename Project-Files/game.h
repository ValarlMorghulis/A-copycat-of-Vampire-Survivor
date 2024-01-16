#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include"public.h"
#include "knife.h"
#include "bullet_stone.h"
#include "garlic.h"
#include "enemy.h"
#include "bossbullet.h"
#include "over.h"
#include<QMessageBox>
#include<QGraphicsPixmapItem>//图形元素
#include<QGraphicsView>//视图
#include<QGraphicsScene>//场景
#include<QKeyEvent>
#include<QList>
#include<QTimer>
#include<QTime>
#include<QProgressBar>

namespace Ui {
class game;
}

class game : public QWidget
{
    Q_OBJECT

public:
    //装备等级
    int ropelevel=0;
    int knifelevel=0;
    int bulletlevel=0;
    int garliclevel=0;
    int maxhplevel=0;
    int addhplevel=0;
    int addspeedlevel=0;
    int subintervallevel=0;
    int adddurationlevel=0;
    int addzonelevel=0;

    int ropedamage=15;
    int speed=15+2*addspeed;
    bool ifpause=false;//暂停
    bool turn=false;//是否转身
    int right=1;//0为垂直，1为右，2为左
    int up=0;//0为水平，1为上，2为下

    bool canup=true;//上方遇到障碍物则为false
    bool candown=true;//下方遇到障碍物则为false
    bool canright=true;//右方遇到障碍物则为false
    bool canleft=true;//左方遇到障碍物则为false

    //角色属性
    int exp=0;
    int max=100;
    int hpnow=playerhp;
    int hpmax=playerhp;
    int knifenumber=shootnumber;
    int bulletnumber=shootnumber;
    int level=1;

    //升级选择
    int choose1;
    int choose2;
    int choose3;

    //抽奖
    int drawmoney;//抽奖所得
    int drawupgrade;


    explicit game(QWidget *parent = 0);
    ~game();
    //键盘事件
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void keyReleaseEvent(QKeyEvent *event);
    //运动
    void move();
    void moveup();//背景向上
    void movedown();//背景向下
    void moveright();//背景向右
    void moveleft();//背景向左
    void collect(int type,bool turkey);//拾取经验/火鸡
    void levelup();//升级
    void draw();//抽奖
    void pause();//暂停
    void continue_();//继续
    void gameover();//游戏结束
    void quit();//退出

    //障碍物
    int barriernum=0;
    void barriercreate();

    void readfile();//读取存档

    over* o;

signals:
    void Over();//游戏结束信号

private slots:
    void drawrand();//随机抽奖

    void ropecollision();//神鞭碰撞检测

    void knifecollision();//飞刀碰撞检测

    void bulletcollision();//子弹碰撞检测

    void garliccollisionion();//大蒜碰撞检测

    void enemycollision();//敌人碰撞检测

    void bossbulletcollision();//boss子弹碰撞检测

    void collectcollision();//拾取检测

    void updatetime();//更新时间

    void updatehp();//更新血量

    void enemymove();//敌人运动

    void rope();//神鞭

    void ropeattack();//神鞭攻击

    void roperemove();//神鞭攻击结束

    void knife();//飞刀

    void knifeshoot();//飞刀发射

    void bullet();//子弹

    void bulletshoot();//子弹发射

    void garlic();//大蒜

    void enemycreate();//生成敌人

    void bosscreate();//生成boss

    void bossattack();//boss攻击

    void on_pause_clicked();

    void on_continue_2_clicked();

    void on_quit_clicked();

    void on_gameover2_clicked();

    void on_choose1_clicked();

    void on_choose2_clicked();

    void on_choose3_clicked();

    void on_draw7_clicked();

    void on_draw10_clicked();

    void on_save_clicked();

private:
    Ui::game *ui;
    QGraphicsView gameview;//游戏视图
    QGraphicsScene scene;//游戏场景

    QGraphicsPixmapItem role;
    QGraphicsPixmapItem collectzone;
    QGraphicsPixmapItem background1;
    QGraphicsPixmapItem background2;
    QGraphicsPixmapItem background3;
    QGraphicsPixmapItem background4;
    QGraphicsPixmapItem background5;
    QGraphicsPixmapItem background6;
    QGraphicsPixmapItem background7;
    QGraphicsPixmapItem background8;
    QGraphicsPixmapItem background9;

    QGraphicsPixmapItem rope1;
    QGraphicsPixmapItem rope2;

    Garlic garlic_;


    //定时器
    QTimer *interval=nullptr;
    QTimer *addtimer=nullptr;
    QTimer *hptimer=nullptr;
    QTimer *gametimer=nullptr;
    QTimer *movetimer=nullptr;
    QTimer *collecttimer=nullptr;
    QTimer *ropetimer=nullptr;
    QTimer *ropeattacktimer=nullptr;
    QTimer *knifetimer=nullptr;
    QTimer *knifemovetimer=nullptr;
    QTimer *bullettimer=nullptr;
    QTimer *bulletmovetimer=nullptr;
    QTimer *garlicattacktimer=nullptr;
    QTimer *enemycreatetimer=nullptr;
    QTimer *enemymovetimer=nullptr;
    QTimer *enemycollisontimer=nullptr;
    QTimer *ropecollisontimer=nullptr;
    QTimer *drawtimer=nullptr;

    QList<int> Mkeylist;//按键组合
    QList<Knife*> knifelist;//飞刀容器
    QList<Bulletstone*> bulletlist;//子弹容器
    QList<Enemy*> enemylist;//敌人容器

    Enemy *boss;
    bool bossdead=true;
    QTimer *bosscreatetimer=nullptr;
    QTimer *bossattacktimer=nullptr;
    QList<bossbullet*> bossbulletlist;//boss子弹容器
};

#endif // GAME_H
