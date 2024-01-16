#include "game.h"
#include "ui_game.h"
#include<QDebug>

game::game(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::game)
{
    gain=0;

    ui->setupUi(this);
    this->setFixedSize(1920,1200);



    ui->hp->setMaximum(hpmax);
    ui->hp->setValue(hpnow);

    if(chosenmap==1){
        musiclist->setCurrentIndex(1);
        music->play();
    }
    else if (chosenmap==2) {
        musiclist->setCurrentIndex(2);
        music->play();
    }

    gameview.setSceneRect(0,0,1920,1200);
    scene.setSceneRect(0,0,1920,1200);
    gameview.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    gameview.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


    if(chosenmap==1)
    {
        QPixmap map(":/new/prefix1/resourses/map1.png");
        map = map.scaled(QSize(1920,1200));
        background1.setPixmap(map);
        background1.setPos(0,0);

        background2.setPixmap(map);
        background2.setPos(-1920,-1200);

        background3.setPixmap(map);
        background3.setPos(0,-1200);

        background4.setPixmap(map);
        background4.setPos(1920,-1200);

        background5.setPixmap(map);
        background5.setPos(-1920,0);

        background6.setPixmap(map);
        background6.setPos(1920,0);

        background7.setPixmap(map);
        background7.setPos(-1920,1200);

        background8.setPixmap(map);
        background8.setPos(0,1200);

        background9.setPixmap(map);
        background9.setPos(1920,1200);
    }
    else if (chosenmap==2) {
        QPixmap map(":/new/prefix1/resourses/map2.png");
        map = map.scaled(QSize(1920,2600));

        background1.setPixmap(map);
        background1.setPos(0,-700);

        background2.setPixmap(map);
        background2.setPos(-1920,-700);

        background3.setPixmap(map);
        background3.setPos(1920,-700);
    }

    if(chosenrole==1){
        ropelevel=1;
        rope();

        QPixmap pixmap(":/new/prefix1/resourses/role1_.png");
        pixmap = pixmap.scaled(QSize(90,90));
        role.setPixmap(pixmap);
        role.setPos(915,555);
    }
    else if (chosenrole==2) {
        bulletlevel=1;
        bullet();
        QPixmap pixmap(":/new/prefix1/resourses/role2_.png");
        pixmap = pixmap.scaled(QSize(90,90));
        role.setPixmap(pixmap);
        role.setPos(915,555);
    }else if (chosenrole==3) {
        knifelevel=1;
        knife();
        knifenumber++;
        bulletnumber++;
        QPixmap pixmap(":/new/prefix1/resourses/role3_.png");
        pixmap = pixmap.scaled(QSize(90,90));
        role.setPixmap(pixmap);
        role.setPos(915,555);
    }

    //图片元素添加场景
    scene.addItem(&background1);
    scene.addItem(&background2);
    scene.addItem(&background3);
    scene.addItem(&background4);
    scene.addItem(&background5);
    scene.addItem(&background6);
    scene.addItem(&background7);
    scene.addItem(&background8);
    scene.addItem(&background9);
    scene.addItem(&role);
    scene.addItem(&collectzone);
    //设置视图场景
    gameview.setScene(&scene);
    //设置视图父窗口
    scene.setParent(this);
    gameview.setParent(this);
    gameview.show();


    //进度条
    ui->exp->raise();
    ui->exp->setValue(0);

    ui->label->raise();
    ui->level->raise();
    ui->time->raise();
    ui->pause->raise();
    ui->hp->raise();
    ui->gain->raise();
    ui->gain2->raise();
    ui->kill2->raise();
    ui->kill->raise();
    ui->continue_2->setEnabled(false);
    ui->quit->setEnabled(false);
    ui->gameover2->setEnabled(false);
    ui->choose1->setEnabled(false);
    ui->choose2->setEnabled(false);
    ui->choose3->setEnabled(false);
    ui->draw7->setEnabled(false);
    ui->draw10->setEnabled(false);

    //计时器
    gametime.setHMS(0,0,0,0);//设置初始值
    ui->time->setText("00:00");
    gametimer = new QTimer(this);//创建一个定时器
    connect(gametimer, SIGNAL(timeout()), this, SLOT(updatetime()));
    gametimer->start(1000);

    movetimer=new QTimer(this);
    movetimer->start(20);
    connect(movetimer,&QTimer::timeout,this,&game::move);

    if(addhp!=0||addhplevel!=0)
    {
        addtimer=new QTimer(this);
        addtimer->start(10000/(addhp+2*addhplevel));
        connect(addtimer, &QTimer::timeout, [this](){
            if(hpnow<hpmax)hpnow++;
        });
    }

    hptimer=new QTimer(this);
    hptimer->start(200);
    connect(hptimer, SIGNAL(timeout()), this, SLOT(updatehp()));

    collecttimer=new QTimer(this);
    collecttimer->start(20);
    connect(collecttimer, SIGNAL(timeout()), this, SLOT(collectcollision()));

    enemycollisontimer=new QTimer(this);
    enemycollisontimer->start(200);
    connect(enemycollisontimer, SIGNAL(timeout()), this, SLOT(enemycollision()));

    enemycreate();
    if(chosenmap==1){
        enemycreatetimer=new QTimer(this);
        enemycreatetimer->start(1000);
    }
    else {
        enemycreatetimer=new QTimer(this);
        enemycreatetimer->start(5000);
    }
    connect(enemycreatetimer, SIGNAL(timeout()), this, SLOT(enemycreate()));

    enemymovetimer=new QTimer(this);
    enemymovetimer->start(20);
    connect(enemymovetimer, SIGNAL(timeout()), this, SLOT(enemymove()));

    bosscreatetimer=new QTimer(this);
    bosscreatetimer->start(10000);
    connect(bosscreatetimer, SIGNAL(timeout()), this, SLOT(bosscreate()));

    if(read>0)readfile();
}

void game::updatetime()
{
        gametime=gametime.addSecs(1);
        ui->time->setText(gametime.toString("mm:ss"));
        barriercreate();
}

void game::updatehp()
{
    ui->kill->setText(QString::number(kill));
    ui->gain->setText(QString::number(gain));
    ui->hp->setMaximum(hpmax);
    ui->hp->setValue(hpnow);
}

void game::enemymove()
{
    for(auto bullet:bossbulletlist)
    {
        bossbulletcollision();
        if(bullet->move()==true){
            scene.removeItem(bullet);
            delete bullet;
            bossbulletlist.removeOne(bullet);
        }
    }
    for(auto enemy:enemylist){
        if(enemy->barrier==false)
        {
            enemy->move();
            if(enemy->death==false)
            {
                for(auto enemy1:enemylist)
                {
                    if(enemy!=enemy1&&enemy1->death==false){
                        if(enemy->collidesWithItem(enemy1)){
                            QPointF p(enemy->x(),enemy->y());
                            QRectF r(enemy1->x(),enemy1->y(),enemy1->width,enemy1->height);
                            if(r.contains(p))
                            {
                                enemy->movedown();
                                enemy->moveright();
                            }
                            p=QPointF(enemy->x()+enemy->width,enemy->y());
                            if(r.contains(p))
                            {
                                enemy->moveleft();
                                enemy->movedown();
                            }
                            p=QPointF(enemy->x(),enemy->y()+enemy->height);
                            if(r.contains(p))
                            {
                                enemy->moveright();
                                enemy->moveup();
                            }
                            p=QPointF(enemy->x()+enemy->width,enemy->y()+enemy->height);
                            if(r.contains(p))
                            {
                                enemy->moveleft();
                                enemy->moveup();
                            }
                        }
                    }
                }
            }
        }

    }
}

void game::rope()
{
    ropetimer=new QTimer(this);
    connect(ropetimer, SIGNAL(timeout()), this, SLOT(ropeattack()));
    ropetimer->start(1500-40*subintrval-15*subintervallevel);

    ropecollisontimer=new QTimer(this);
    connect(ropecollisontimer, SIGNAL(timeout()), this, SLOT(ropecollision()));

    ropeattacktimer=new QTimer(this);
    connect(ropeattacktimer, SIGNAL(timeout()), this, SLOT(roperemove()));
}

void game::ropeattack()
{
        if(turn==true)
        {
            QPixmap rope_picture(":/new/prefix1/resourses/rope.png");
            rope_picture = rope_picture.scaled(QSize(350,50));
            rope1.setPixmap(rope_picture);
            rope1.setPos(610,550);
            scene.addItem(&rope1);

            if(ropelevel>1)
            {
                QPixmap rope_picture2(":/new/prefix1/resourses/rope2.png");
                rope_picture2 = rope_picture2.scaled(QSize(350,50));
                rope2.setPixmap(rope_picture2);
                rope2.setPos(970,600);
                scene.addItem(&rope2);
                if(ropelevel>2)
                {
                    ropedamage=22;
                    if(ropelevel>3)
                    {
                        ropedamage=29;
                        if(ropelevel>4)
                        {
                            ropedamage=36;
                            if(ropelevel>5)
                            {
                                ropedamage=43;
                            }
                        }
                    }
                }
            }
        }
        else {
            QPixmap rope_picture(":/new/prefix1/resourses/rope_.png");
            rope_picture = rope_picture.scaled(QSize(350,50));
            rope1.setPixmap(rope_picture);
            rope1.setPos(970,550);
            scene.addItem(&rope1);

            if(ropelevel>1)
            {
                QPixmap rope_picture2(":/new/prefix1/resourses/rope2_.png");
                rope_picture2 = rope_picture2.scaled(QSize(350,50));
                rope2.setPixmap(rope_picture2);
                rope2.setPos(590,600);
                scene.addItem(&rope2);
            }
        }
        ropecollisontimer->start(20);
        ropeattacktimer->start(200);
}

void game::roperemove()
{
    scene.removeItem(&rope1);
    if(ropelevel>1)scene.removeItem(&rope2);
    ropecollisontimer->stop();
    ropeattacktimer->stop();
}

void game::knife()
{
    knifetimer=new QTimer(this);
    connect(knifetimer, &QTimer::timeout, [this](){
        knifeshoot();
        if(knifenumber>=2){
            interval=new QTimer(this);
            interval->start(100);
            connect(interval, &QTimer::timeout, [this](){
                interval->stop();
                delete interval;
                interval=nullptr;
                knifeshoot();
                if(knifenumber>=3){
                    interval=new QTimer(this);
                    interval->start(100);
                    connect(interval, &QTimer::timeout, [this](){
                        interval->stop();
                        delete interval;
                        interval=nullptr;
                        knifeshoot();
                        if(knifenumber>=4){
                            interval=new QTimer(this);
                            interval->start(100);
                            connect(interval, &QTimer::timeout, [this](){
                                interval->stop();
                                delete interval;
                                interval=nullptr;
                                knifeshoot();
                            });
                        }
                    });
                }
            });
        }
    });

    knifetimer->start(1000-25*subintrval-10*subintervallevel);

    knifemovetimer=new QTimer(this);
    knifemovetimer->start(10);
    connect(knifemovetimer, &QTimer::timeout, [this](){
        for(auto knife:knifelist){
            if(knife->move()==true){
                scene.removeItem(knife);
                delete knife;
                knifelist.removeOne(knife);
            }
            knifecollision();
        }
        collectcollision();
    });
}

void game::knifeshoot()
{
    Knife *knife=new Knife(right,up,knifelevel);
    scene.addItem(knife);
    knifelist.append(knife);
}

void game::bullet()
{
    bullettimer=new QTimer(this);
    connect(bullettimer, &QTimer::timeout, [this](){
        bulletshoot();
        if(bulletnumber>=2){
                bulletshoot();
                if(bulletnumber>=3){
                        bulletshoot();
                        if(bulletnumber>=4){
                                bulletshoot();
                            }
                    }
                }
    });

    bullettimer->start(1500-40*subintrval-15*subintervallevel);

    bulletmovetimer=new QTimer(this);
    bulletmovetimer->start(10);
    connect(bulletmovetimer, &QTimer::timeout, [this](){
        for(auto bullet:bulletlist){
            if(bullet->move()==true){
                scene.removeItem(bullet);
                delete bullet;
                bulletlist.removeOne(bullet);
            }
            bulletcollision();
        }
    });
}

void game::bulletshoot()
{
    Bulletstone *bullet=new Bulletstone(right,up,addduration,bulletlevel);
    scene.addItem(bullet);
    bulletlist.append(bullet);
}

void game::garlic()
{
    scene.removeItem(&role);
    scene.addItem(&garlic_);
    scene.addItem(&role);
    garlicattacktimer=new QTimer(this);
    garlicattacktimer->start(700);
    connect(garlicattacktimer, SIGNAL(timeout()), this, SLOT(garliccollisionion()));
}

void game::enemycreate()
{
    if(chosenmap==1){
        if(enemylist.size()<80){
            for(int i=0;i<1;i++)
            {
                Enemy*enemy=new Enemy(1,chosenmap,1920,rand()%1200);
                scene.addItem(enemy);
                enemylist.append(enemy);
            }
            for(int i=0;i<1;i++)
            {
                Enemy*enemy=new Enemy(1,chosenmap,-100,rand()%1200);
                scene.addItem(enemy);
                enemylist.append(enemy);
            }
            for(int i=0;i<1;i++)
            {
                Enemy*enemy=new Enemy(1,chosenmap,rand()%1920,-50);
                scene.addItem(enemy);
                enemylist.append(enemy);
            }
            for(int i=0;i<1;i++)
            {
                Enemy*enemy=new Enemy(1,chosenmap,rand()%1920,1200);
                scene.addItem(enemy);
                enemylist.append(enemy);
            }
        }
    }
    else if (chosenmap==2) {
        int x=rand()%2+1;
        if(enemylist.size()<30){
            for(int i=0;i<12;i++)
            {
                Enemy*enemy=new Enemy(x,chosenmap,1920,100*i);
                scene.addItem(enemy);
                enemylist.append(enemy);
            }
            for(int i=0;i<12;i++)
            {
                Enemy*enemy=new Enemy(x,chosenmap,2000,100*i);
                scene.addItem(enemy);
                enemylist.append(enemy);
            }
            for(int i=0;i<12;i++)
            {
                Enemy*enemy=new Enemy(x,chosenmap,-100,100*i);
                scene.addItem(enemy);
                enemylist.append(enemy);
            }
            for(int i=0;i<12;i++)
            {
                Enemy*enemy=new Enemy(x,chosenmap,-200,100*i);
                scene.addItem(enemy);
                enemylist.append(enemy);
            }
        }
    }
}

void game::bosscreate()
{
    if(bossdead==true){
        bossdead=false;
        boss=new Enemy(3,chosenmap,1920,rand()%1200);
        scene.addItem(boss);
        enemylist.append(boss);

        bossattacktimer=new QTimer(this);
        connect(bossattacktimer, SIGNAL(timeout()), this, SLOT(bossattack()));
        bossattacktimer->start(2000);
    }
}

void game::barriercreate()
{
    if(barriernum<5)
    {
        int z=rand()%4;
        int x;
        int y;
        switch(z)
        {
        case 0:{
            x=rand()%3840-960;
            y=-49;
            break;
        }
        case 1:{
            x=rand()%3840-960;
            y=1200;
            break;
        }
        case 2:{
            y=rand()%2400-600;
            x=-40;
            break;
        }
        case 3:{
            y=rand()%2400-600;
            x=1920;
            break;
        }
        }
        Enemy *barrier=new Enemy(4,chosenmap,x,y);
        scene.addItem(barrier);
        enemylist.append(barrier);
        barriernum++;
    }
}

void game::readfile()
{
    if(chosenmap==1){
        QFile gamefile("D://QTgame//1//1//resourses//1.txt");
        if(!gamefile.open(QIODevice::ReadOnly))return; //判断文件是否正常打开
        QTextStream text_stream(&gamefile);
        QString str;
        str=gamefile.readLine();
        gametime=gametime.addMSecs(str.toInt());
        str=gamefile.readLine();
        gametime=gametime.addSecs(str.toInt());
        str=gamefile.readLine();
        exp=str.toInt();
        str=gamefile.readLine();
        max=str.toInt();
        str=gamefile.readLine();
        ui->exp->setValue(str.toInt());
        str=gamefile.readLine();
        ui->exp->setMaximum(str.toInt());
        str=gamefile.readLine();
        level=str.toInt();
        ui->level->setText(str);
        str=gamefile.readLine();
        gain=str.toInt();
        str=gamefile.readLine();
        kill=str.toInt();
        str=gamefile.readLine();
        ropelevel=str.toInt();
        if(ropelevel>0)rope();
        str=gamefile.readLine();
        knifelevel=str.toInt();
        str=gamefile.readLine();
        knifenumber=str.toInt();
        if(knifelevel>0)knife();
        str=gamefile.readLine();
        bulletlevel=str.toInt();
        str=gamefile.readLine();
        bulletnumber=str.toInt();
        if(bulletlevel>0)bullet();
        str=gamefile.readLine();
        garliclevel=str.toInt();
        if(garliclevel>0){
            garlic();
            garlic_.upgrade(garliclevel);
        }
        str=gamefile.readLine();
        maxhplevel=str.toInt();
        str=gamefile.readLine();
        addhplevel=str.toInt();
        str=gamefile.readLine();
        addspeedlevel=str.toInt();
        str=gamefile.readLine();
        subintervallevel=str.toInt();
        str=gamefile.readLine();
        adddurationlevel=str.toInt();
        str=gamefile.readLine();
        addzonelevel=str.toInt();
        while(!gamefile.atEnd()){
            int t;
            double x,y;
            str=gamefile.readLine();
            t=str.toInt();
            str=gamefile.readLine();
            x=str.toDouble();
            str=gamefile.readLine();
            y=str.toDouble();
            Enemy*enemy=new Enemy(t,chosenmap,x,y);
            scene.addItem(enemy);
            enemylist.append(enemy);
        }
    }
    else if(chosenmap==2){
        QFile gamefile("D://QTgame//1//1//resourses//1.txt");
        if(!gamefile.open(QIODevice::ReadOnly))return; //判断文件是否正常打开
        QTextStream text_stream(&gamefile);
        QString str;
        str=gamefile.readLine();
        gametime=gametime.addMSecs(str.toInt());
        str=gamefile.readLine();
        gametime=gametime.addSecs(str.toInt());
        str=gamefile.readLine();
        exp=str.toInt();
        str=gamefile.readLine();
        max=str.toInt();
        str=gamefile.readLine();
        ui->exp->setValue(str.toInt());
        str=gamefile.readLine();
        ui->exp->setMaximum(str.toInt());
        str=gamefile.readLine();
        level=str.toInt();
        ui->level->setText(str);
        str=gamefile.readLine();
        gain=str.toInt();
        str=gamefile.readLine();
        kill=str.toInt();
        str=gamefile.readLine();
        ropelevel=str.toInt();
        if(ropelevel>0)rope();
        str=gamefile.readLine();
        knifelevel=str.toInt();
        str=gamefile.readLine();
        knifenumber=str.toInt();
        if(knifelevel>0)knife();
        str=gamefile.readLine();
        bulletlevel=str.toInt();
        str=gamefile.readLine();
        bulletnumber=str.toInt();
        if(bulletlevel>0)bullet();
        str=gamefile.readLine();
        garliclevel=str.toInt();
        if(garliclevel>0){
            garlic();
            garlic_.upgrade(garliclevel);
        }
        str=gamefile.readLine();
        maxhplevel=str.toInt();
        str=gamefile.readLine();
        addhplevel=str.toInt();
        str=gamefile.readLine();
        addspeedlevel=str.toInt();
        str=gamefile.readLine();
        subintervallevel=str.toInt();
        str=gamefile.readLine();
        adddurationlevel=str.toInt();
        str=gamefile.readLine();
        addzonelevel=str.toInt();
        while(!gamefile.atEnd()){
            int t;
            double x,y;
            str=gamefile.readLine();
            t=str.toInt();
            str=gamefile.readLine();
            x=str.toDouble();
            str=gamefile.readLine();
            y=str.toDouble();
            Enemy*enemy=new Enemy(t,chosenmap,x,y);
            scene.addItem(enemy);
            enemylist.append(enemy);
        }
    }
    updatetime();
}

void game::bossattack()
{
    if(boss->death==false)
    {
        int x=rand()%2;
        if(x==0)
        {
            QPoint p1(1,0);
            bossbullet*bullet1=new bossbullet(p1,boss->pos());
            scene.addItem(bullet1);
            bossbulletlist.append(bullet1);

            QPoint p2(-1,0);
            bossbullet*bullet2=new bossbullet(p2,boss->pos());
            scene.addItem(bullet2);
            bossbulletlist.append(bullet2);

            QPoint p3(0,1);
            bossbullet*bullet3=new bossbullet(p3,boss->pos());
            scene.addItem(bullet3);
            bossbulletlist.append(bullet3);

            QPoint p4(0,-1);
            bossbullet*bullet4=new bossbullet(p4,boss->pos());
            scene.addItem(bullet4);
            bossbulletlist.append(bullet4);
        }
        else {
            QPoint p1(1,1);
            bossbullet*bullet1=new bossbullet(p1,boss->pos());
            scene.addItem(bullet1);
            bossbulletlist.append(bullet1);

            QPoint p2(-1,-1);
            bossbullet*bullet2=new bossbullet(p2,boss->pos());
            scene.addItem(bullet2);
            bossbulletlist.append(bullet2);

            QPoint p3(-1,1);
            bossbullet*bullet3=new bossbullet(p3,boss->pos());
            scene.addItem(bullet3);
            bossbulletlist.append(bullet3);

            QPoint p4(1,-1);
            bossbullet*bullet4=new bossbullet(p4,boss->pos());
            scene.addItem(bullet4);
            bossbulletlist.append(bullet4);
        }
    }
}

void game::ropecollision(){
    for(auto enemy:enemylist){
        if(rope1.collidesWithItem(enemy)||rope2.collidesWithItem(enemy)){
            if(enemy->death==false)
            {
                if(enemy->hurt(ropedamage)==true){
                    if(enemy->boss==true){
                        bossdead=true;
                        bossattacktimer->stop();
                        delete bossattacktimer;
                        bossattacktimer=nullptr;
                    }
                    enemy->change();
                }
            }
        }
    }
}

void game::knifecollision(){
    for (auto knife:knifelist) {
        for(auto enemy:enemylist){
            if(knife->collidesWithItem(enemy)){
                if(enemy->death==false&&knife->beremoved==false)
                {
                    knife->beremoved=true;
                    if(enemy->hurt(knife->damage)==true){
                        if(enemy->boss==true){
                            bossdead=true;
                            bossattacktimer->stop();
                            delete bossattacktimer;
                            bossattacktimer=nullptr;
                        }
                        enemy->change();
                    }
                    break;
                }
            }
        }
    }
}

void game::bulletcollision()
{
    for (auto bullet:bulletlist) {
        for(auto enemy:enemylist){
            if(bullet->collidesWithItem(enemy)){
                if(enemy->death==false)
                {
                    if(enemy->hurt(bullet->damage)==true){
                        if(enemy->boss==true){
                            bossdead=true;
                            bossattacktimer->stop();
                            delete bossattacktimer;
                            bossattacktimer=nullptr;
                        }
                        enemy->change();
                    }
                }
            }
        }
    }
}

void game::garliccollisionion()
{
    for(auto enemy:enemylist){
        if(garlic_.collidesWithItem(enemy)){
            if(enemy->death==false)
            {
                if(enemy->hurt(garlic_.damage)==true){
                    if(enemy->boss==true){
                        bossdead=true;
                        bossattacktimer->stop();
                        delete bossattacktimer;
                        bossattacktimer=nullptr;
                    }
                    enemy->change();
                }
            }
        }
    }
}

void game::enemycollision()
{
    for(auto enemy:enemylist){
        if((enemy->x()>=(960-30)&&enemy->x()<=(960+30)&&enemy->y()>=(600-30)&&enemy->y()<=(600+30))||
                (enemy->x()+enemy->width>=(960-30)&&enemy->x()<=(960+30)&&enemy->y()>=(600-30)&&enemy->y()<=(600+30))||
                (enemy->x()>=(960-30)&&enemy->x()<=(960+30)&&enemy->y()>=(600-30)&&enemy->y()+enemy->height<=(600+30))||
                (enemy->x()+enemy->width>=(960-30)&&enemy->x()+enemy->width<=(960+30)&&enemy->y()+enemy->height>=(600-30)&&enemy->y()+enemy->height<=(600+30))){
            if(enemy->death==false&&enemy->barrier==false)
            {
                hpnow=hpnow-enemy->attack;
                if(hpnow<=0){
                    gameover();
                    break;
                }
            }
        }
    }
}

void game::bossbulletcollision()
{
    for(auto bossbullet:bossbulletlist){
        if(bossbullet->collidesWithItem(&role)){
                if(bossbullet->beremoved==false){
                hpnow=hpnow-bossbullet->damage;
                bossbullet->beremoved=true;
                if(hpnow<=0){
                    gameover();
                    break;
                }
            }
        }
    }
}

void game::collectcollision()
{
    for(auto enemy:enemylist){
        if(enemy->x()>=(960-(zone*(1+0.25*addzone+0.1*addzonelevel))/2)&&enemy->x()<=(960+(zone*(1+0.25*addzone+0.1*addzonelevel))/2)&&enemy->y()>=(600-(zone*(1+0.25*addzone+0.1*addzonelevel))/2)&&enemy->y()<=(600+(zone*(1+0.25*addzone+0.1*addzonelevel))/2)){
            if(enemy->death==true)
            {
                enemy->becollected=true;
            }
            if(role.collidesWithItem(enemy)&&enemy->death==true)
            {
                collect(enemy->type,enemy->turkey);
                if(enemy->barrier==true)barriernum--;
                scene.removeItem(enemy);
                delete enemy;
                enemylist.removeOne(enemy);
            }
        }
        if(enemy->x()>=2600||enemy->x()<=-680||enemy->y()>=1800||enemy->y()<=-600){
            if(enemy->boss==false)
            {
                scene.removeItem(enemy);
                if(enemy->barrier==true)barriernum--;
                delete enemy;
                enemylist.removeOne(enemy);
            }
            else {
                if(enemy->x()>=2600)enemy->setX(2020);
                if(enemy->x()<=-680)enemy->setX(-100);
                if(enemy->y()>=1800)enemy->setY(1300);
                if(enemy->y()<=-600)enemy->setY(-100);
            }
            }
    }
}

void game::quit()
{
    addmoney(gain);
    music->stop();
    pause();
    o=new over;
    o->show();
    this->close();
    connect(this->o,&over::Over,this,[=](){
        emit Over();
           });
}

void game::moveup(){
    if(candown==true)
    {
        if(chosenmap==1){
            background1.moveBy(0,-speed);
            background2.moveBy(0,-speed);
            background3.moveBy(0,-speed);
            background4.moveBy(0,-speed);
            background5.moveBy(0,-speed);
            background6.moveBy(0,-speed);
            background7.moveBy(0,-speed);
            background8.moveBy(0,-speed);
            background9.moveBy(0,-speed);
            if(background1.y()<=-1200){
                background1.setY(background1.y()+2400);
            }
            if(background2.y()<=-1200){
                background2.setY(background2.y()+2400);
            }
            if(background3.y()<=-1200){
                background3.setY(background3.y()+2400);
            }
            if(background4.y()<=-1200){
                background4.setY(background4.y()+2400);
            }
            if(background5.y()<=-1200){
                background5.setY(background5.y()+2400);
            }
            if(background6.y()<=-1200){
                background6.setY(background6.y()+2400);
            }
            if(background7.y()<=-1200){
                background7.setY(background7.y()+2400);
            }
            if(background8.y()<=-1200){
                background8.setY(background8.y()+2400);
            }
            if(background9.y()<=-1200){
                background9.setY(background9.y()+2400);
            }
            for(auto enemy:enemylist){
                enemy->bemoved(QPoint(0,-1),speed);
            }
            for(auto enemy:bossbulletlist){
                enemy->bemoved(QPoint(0,-1),speed);
            }
            for(auto knife:knifelist){
                knife->bemoved(QPoint(0,-1),speed);
            }
            for(auto bullet:bulletlist){
                bullet->bemoved(QPoint(0,-1),speed);
            }
        }
        else if (chosenmap==2) {
            if(background1.y()>=-1355){
                background1.moveBy(0,-speed);
                for(auto enemy:enemylist){
                    enemy->bemoved(QPoint(0,-1),speed);
                }
                for(auto enemy:bossbulletlist){
                    enemy->bemoved(QPoint(0,-1),speed);
                }
                for(auto knife:knifelist){
                    knife->bemoved(QPoint(0,-1),speed);
                }
                for(auto bullet:bulletlist){
                    bullet->bemoved(QPoint(0,-1),speed);
                }
            }
            if(background2.y()>=-1355){
                background2.moveBy(0,-speed);
            }
            if(background3.y()>=-1355){
                background3.moveBy(0,-speed);
            }
        }
    }
    for(auto enemy:enemylist){
        if(enemy->collidesWithItem(&role)&&enemy->barrier==true){
            candown=false;
            canup=true;
            canleft=true;
            canright=true;
            break;
        }
        else {
            candown=true;
        }
    }
}

void game::movedown(){
    if(canup==true)
    {
        if(chosenmap==1){
            background1.moveBy(0,speed);
            background2.moveBy(0,speed);
            background3.moveBy(0,speed);
            background4.moveBy(0,speed);
            background5.moveBy(0,speed);
            background6.moveBy(0,speed);
            background7.moveBy(0,speed);
            background8.moveBy(0,speed);
            background9.moveBy(0,speed);
            if(background1.y()>=1200){
                background1.setY(background1.y()-2400);
            }
            if(background2.y()>=1200){
                background2.setY(background2.y()-2400);
            }
            if(background3.y()>=1200){
                background3.setY(background3.y()-2400);
            }
            if(background4.y()>=1200){
                background4.setY(background4.y()-2400);
            }
            if(background5.y()>=1200){
                background5.setY(background5.y()-2400);
            }
            if(background6.y()>=1200){
                background6.setY(background6.y()-2400);
            }
            if(background7.y()>=1200){
                background7.setY(background7.y()-2400);
            }
            if(background8.y()>=1200){
                background8.setY(background8.y()-2400);
            }
            if(background9.y()>=1200){
                background9.setY(background9.y()-2400);
            }
            for(auto enemy:enemylist){
                enemy->bemoved(QPoint(0,1),speed);
            }
            for(auto enemy:bossbulletlist){
                enemy->bemoved(QPoint(0,1),speed);
            }
            for(auto knife:knifelist){
                knife->bemoved(QPoint(0,1),speed);
            }
            for(auto bullet:bulletlist){
                bullet->bemoved(QPoint(0,1),speed);
            }
        }
        else if (chosenmap==2) {
            if(background1.y()<=0){
                background1.moveBy(0,speed);
                for(auto enemy:enemylist){
                    enemy->bemoved(QPoint(0,1),speed);
                }
                for(auto enemy:bossbulletlist){
                    enemy->bemoved(QPoint(0,1),speed);
                }
                for(auto knife:knifelist){
                    knife->bemoved(QPoint(0,1),speed);
                }
                for(auto bullet:bulletlist){
                    bullet->bemoved(QPoint(0,1),speed);
                }
            }
            if(background2.y()<=0){
                background2.moveBy(0,speed);
            }
            if(background3.y()<=0){
                background3.moveBy(0,speed);
            }
        }
    }
    for(auto enemy:enemylist){
        if(enemy->collidesWithItem(&role)&&enemy->barrier==true){
            canup=false;
            candown=true;
            canleft=true;
            canright=true;
            break;
        }
        else {
            canup=true;
        }
    }
}

void game::moveright(){
    scene.removeItem(&role);
    turn=true;
    if(chosenrole==1)
    {
        QPixmap pixmap(":/new/prefix1/resourses/role1_2.png");
                pixmap = pixmap.scaled(QSize(90,90));
                role.setPixmap(pixmap);
                role.setPos(915,555);
                scene.addItem(&role);
    }
    else if (chosenrole==2) {
        QPixmap pixmap(":/new/prefix1/resourses/role2_2.png");
        pixmap = pixmap.scaled(QSize(90,90));
        role.setPixmap(pixmap);
        role.setPos(915,555);
        scene.addItem(&role);
    }
    else if (chosenrole==3) {
        QPixmap pixmap(":/new/prefix1/resourses/role3_2.png");
        pixmap = pixmap.scaled(QSize(90,90));
        role.setPixmap(pixmap);
        role.setPos(915,555);
        scene.addItem(&role);
    }
    if(canleft==true)
    {
        if(chosenmap==1){
            background1.moveBy(speed,0);
            background2.moveBy(speed,0);
            background3.moveBy(speed,0);
            background4.moveBy(speed,0);
            background5.moveBy(speed,0);
            background6.moveBy(speed,0);
            background7.moveBy(speed,0);
            background8.moveBy(speed,0);
            background9.moveBy(speed,0);
            if(background1.x()>=1920){
                background1.setX(background1.x()-3840);
            }
            if(background2.x()>=1920){
                background2.setX(background2.x()-3840);
            }
            if(background3.x()>=1920){
                background3.setX(background3.x()-3840);
            }
            if(background4.x()>=1920){
                background4.setX(background4.x()-3840);
            }
            if(background5.x()>=1920){
                background5.setX(background5.x()-3840);
            }
            if(background6.x()>=1920){
                background6.setX(background6.x()-3840);
            }
            if(background7.x()>=1920){
                background7.setX(background7.x()-3840);
            }
            if(background8.x()>=1920){
                background8.setX(background8.x()-3840);
            }
            if(background9.x()>=1920){
                background9.setX(background9.x()-3840);
            }
        }
        else if (chosenmap==2) {
            background1.moveBy(speed,0);
            background2.moveBy(speed,0);
            background3.moveBy(speed,0);
            if(background1.x()>=1920){
                background1.setX(background1.x()-3840);
            }
            if(background2.x()>=1920){
                background2.setX(background2.x()-3840);
            }
            if(background3.x()>=1920){
                background3.setX(background3.x()-3840);
            }
        }

        for(auto enemy:enemylist){
            enemy->bemoved(QPoint(1,0),speed);
        }
        for(auto enemy:bossbulletlist){
            enemy->bemoved(QPoint(1,0),speed);
        }
        for(auto knife:knifelist){
            knife->bemoved(QPoint(1,0),speed);
        }
        for(auto bullet:bulletlist){
            bullet->bemoved(QPoint(1,0),speed);
        }
    }

    for(auto enemy:enemylist){
        if(enemy->collidesWithItem(&role)&&enemy->barrier==true){
            canleft=false;
            candown=true;
            canup=true;
            canright=true;
            break;
        }
        else {
            canleft=true;
        }
    }

}

void game::moveleft(){
    scene.removeItem(&role);
    turn=false;
    if(chosenrole==1)
    {
        QPixmap pixmap(":/new/prefix1/resourses/role1_.png");
                pixmap = pixmap.scaled(QSize(90,90));
                role.setPixmap(pixmap);
                role.setPos(915,555);
                scene.addItem(&role);
    }
    else if (chosenrole==2) {
        QPixmap pixmap(":/new/prefix1/resourses/role2_.png");
        pixmap = pixmap.scaled(QSize(90,90));
        role.setPixmap(pixmap);
        role.setPos(915,555);
        scene.addItem(&role);
    }
    else if (chosenrole==3) {
        QPixmap pixmap(":/new/prefix1/resourses/role3_.png");
        pixmap = pixmap.scaled(QSize(90,90));
        role.setPixmap(pixmap);
        role.setPos(915,555);
        scene.addItem(&role);
    }
    if(canright==true)
    {
        if(chosenmap==1){

            background1.moveBy(-speed,0);
            background2.moveBy(-speed,0);
            background3.moveBy(-speed,0);
            background4.moveBy(-speed,0);
            background5.moveBy(-speed,0);
            background6.moveBy(-speed,0);
            background7.moveBy(-speed,0);
            background8.moveBy(-speed,0);
            background9.moveBy(-speed,0);
            if(background1.x()<=-1920){
                background1.setX(background1.x()+3840);
            }
            if(background2.x()<=-1920){
                background2.setX(background2.x()+3840);
            }
            if(background3.x()<=-1920){
                background3.setX(background3.x()+3840);
            }
            if(background4.x()<=-1920){
                background4.setX(background4.x()+3840);
            }
            if(background5.x()<=-1920){
                background5.setX(background5.x()+3840);
            }
            if(background6.x()<=-1920){
                background6.setX(background6.x()+3840);
            }
            if(background7.x()<=-1920){
                background7.setX(background7.x()+3840);
            }
            if(background8.x()<=-1920){
                background8.setX(background8.x()+3840);
            }
            if(background9.x()<=-1920){
                background9.setX(background9.x()+3840);
            }
        }
        else if (chosenmap==2) {
            background1.moveBy(-speed,0);
            background2.moveBy(-speed,0);
            background3.moveBy(-speed,0);
            if(background1.x()<=-1920){
                background1.setX(background1.x()+3840);
            }
            if(background2.x()<=-1920){
                background2.setX(background2.x()+3840);
            }
            if(background3.x()<=-1920){
                background3.setX(background3.x()+3840);
            }
        }

        for(auto enemy:enemylist){
            enemy->bemoved(QPoint(-1,0),speed);
        }
        for(auto enemy:bossbulletlist){
            enemy->bemoved(QPoint(-1,0),speed);
        }
        for(auto knife:knifelist){
            knife->bemoved(QPoint(-1,0),speed);
        }
        for(auto bullet:bulletlist){
            bullet->bemoved(QPoint(-1,0),speed);
        }
    }

    for(auto enemy:enemylist){
        if(enemy->collidesWithItem(&role)&&enemy->barrier==true){
            canright=false;
            candown=true;
            canup=true;
            canleft=true;
            break;
        }
        else {
            canright=true;
        }
    }
}

void game::move()
{
    if(ifpause==false){
        if(Mkeylist.contains(Qt::Key_W)){
            up=1;
            right=0;
            if(Mkeylist.contains(Qt::Key_D))right=1;
            else if (Mkeylist.contains(Qt::Key_A))right=2;
        }
        else if (Mkeylist.contains(Qt::Key_S)) {
            up=2;
            right=0;
            if(Mkeylist.contains(Qt::Key_D))right=1;
            else if (Mkeylist.contains(Qt::Key_A))right=2;
        }
        else if (Mkeylist.contains(Qt::Key_A)){
            right=2;
            up=0;
        }
        else if (Mkeylist.contains(Qt::Key_D)) {
            right=1;
            up=0;
        }
        for(int keycode:Mkeylist)
        {
            switch(keycode){
                case Qt::Key_W:{
                movedown();
                break;
            }
            case Qt::Key_S:{
                moveup();
                break;
            }
            case Qt::Key_A:{
                moveright();
                break;
            }
            case Qt::Key_D:{
                moveleft();
                break;
            }

                }
        }
    }

}

void game::collect(int type,bool turkey)
{
    if(turkey==true)
    {
        hpnow=hpnow+30;
        if(hpnow>hpmax)hpnow=hpmax;
    }
    else {
        if(type==3){
            draw();
        }
        else if (type==4) {
            gain++;
        }
        else {
            int num;
            switch (type) {
            case 1:num=15;break;
            case 2:num=30;break;
            }
            exp=exp+num;
            ui->exp->setValue(exp);
            if(exp>=max){
                levelup();
                exp=exp-max;
                max=max+200;
                ui->exp->setValue(exp);
                ui->exp->setMaximum(max);
            }
        }
    }
}

void game::levelup()
{
    pause();
    level++;
    QString str=QString::number(level);
    ui->level->setText(str);

    ui->levelup1->raise();
    ui->levelup2->raise();
    ui->levelup3->raise();
    ui->levelup4->raise();
    ui->levelup->raise();
    ui->choose1->raise();
    ui->choose2->raise();
    ui->choose3->raise();
    ui->choose1_2->raise();
    ui->choose2_2->raise();
    ui->choose3_2->raise();

    ui->choose1->setEnabled(true);
    ui->choose2->setEnabled(true);
    ui->choose3->setEnabled(true);

    int total=ropelevel+knifelevel+bulletlevel+garliclevel+maxhplevel+addhplevel+addspeedlevel+subintervallevel+adddurationlevel+addzonelevel;
    int x,y,z;
    if(total<48){
loop1:x=rand()%10+1;
    switch(x)
    {
    case 1:{
        if(ropelevel>5)goto loop1;
        else {
            ui->choose1->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/resourses/1.png);}");
            ui->choose1_2->setText("神鞭");
            if(ropelevel==0){
                ui->levelup2->setText("水平攻击，可贯穿敌人");
            }
            else if(ropelevel==1){
                ui->levelup2->setText("等级2：发射数+1");
            }
            else if(ropelevel==2){
                ui->levelup2->setText("等级3：伤害+7");
            }
            else if(ropelevel==3){
                ui->levelup2->setText("等级4：伤害+7");
            }
            else if(ropelevel==4){
                ui->levelup2->setText("等级5：伤害+7");
            }
            else if(ropelevel==5){
                ui->levelup2->setText("等级6：伤害+7");
            }
        }
        break;
    }
    case 2:{
        if(knifelevel>5)goto loop1;
        else {
            ui->choose1->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/resourses/2.png);}");
            ui->choose1_2->setText("飞刀");
            if(knifelevel==0){
                ui->levelup2->setText("朝面对的对象快速发射");
            }
            else if(knifelevel==1){
                ui->levelup2->setText("等级2：发射数+1");
            }
            else if(knifelevel==2){
                ui->levelup2->setText("等级3：伤害+5");
            }
            else if(knifelevel==3){
                ui->levelup2->setText("等级4：发射数+1");
            }
            else if(knifelevel==4){
                ui->levelup2->setText("等级5：伤害+5");
            }
            else if(knifelevel==5){
                ui->levelup2->setText("等级6：伤害+5");
            }
        }
        break;
    }
    case 3:{
        if(bulletlevel>5)goto loop1;
        else {
            ui->choose1->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/resourses/3.png);}");
            ui->choose1_2->setText("痕印石");
            if(bulletlevel==0){
                ui->levelup2->setText("贯穿攻击，可四处反弹");
            }
            else if(bulletlevel==1){
                ui->levelup2->setText("等级2：伤害+5，速度+20%");
            }
            else if(bulletlevel==2){
                ui->levelup2->setText("等级3：贯穿攻击，持续时间+30%");
            }
            else if(bulletlevel==3){
                ui->levelup2->setText("等级4：发射数+1");
            }
            else if(bulletlevel==4){
                ui->levelup2->setText("等级5：伤害+5，速度+20%");
            }
            else if(bulletlevel==5){
                ui->levelup2->setText("等级6：贯穿攻击，持续时间+30%");
            }
        }
        break;
    }
    case 4:{
        if(garliclevel>5)goto loop1;
        else {
            ui->choose1->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/resourses/4.png);}");
            ui->choose1_2->setText("大蒜");
            if(garliclevel==0){
                ui->levelup2->setText("对附近的敌人造成伤害");
            }
            else if(garliclevel==1){
                ui->levelup2->setText("等级2：攻击范围+20%");
            }
            else if(garliclevel==2){
                ui->levelup2->setText("等级3：伤害+0.2");
            }
            else if(garliclevel==3){
                ui->levelup2->setText("等级4：攻击范围+20%");
            }
            else if(garliclevel==4){
                ui->levelup2->setText("等级5：伤害+0.2");
            }
            else if(garliclevel==5){
                ui->levelup2->setText("等级6：伤害+0.2");
            }
        }
        break;
    }
    case 5:{
        if(maxhplevel>3)goto loop1;
        else {
            ui->choose1->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/resourses/5.png);}");
            ui->choose1_2->setText("空虚之心");
            if(maxhplevel==0){
                ui->levelup2->setText("生命上限+20%");
            }
            else if(maxhplevel==1){
                ui->levelup2->setText("等级2：生命上限+20%");
            }
            else if(maxhplevel==2){
                ui->levelup2->setText("等级3：生命上限+20%");
            }
            else if(maxhplevel==3){
                ui->levelup2->setText("等级4：生命上限+20%");
            }
        }
        break;
    }
    case 6:{
        if(addhplevel>3)goto loop1;
        else {
            ui->choose1->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/resourses/6.png);}");
            ui->choose1_2->setText("愈伤番茄");
            if(addhplevel==0){
                ui->levelup2->setText("角色每秒生命恢复0.2");
            }
            else if(addhplevel==1){
                ui->levelup2->setText("等级2：角色每秒生命恢复0.4");
            }
            else if(addhplevel==2){
                ui->levelup2->setText("等级3：角色每秒生命恢复0.6");
            }
            else if(addhplevel==3){
                ui->levelup2->setText("等级4：角色每秒生命恢复0.8");
            }
        }
        break;
    }
    case 7:{
        if(addspeedlevel>3)goto loop1;
        else {
            ui->choose1->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/resourses/7.png);}");
            ui->choose1_2->setText("翅膀");
            if(addspeedlevel==0){
                ui->levelup2->setText("速度+20%");
            }
            else if(addspeedlevel==1){
                ui->levelup2->setText("等级2：速度+20%");
            }
            else if(addspeedlevel==2){
                ui->levelup2->setText("等级3：速度+20%");
            }
            else if(addspeedlevel==3){
                ui->levelup2->setText("等级4：速度+20%");
            }
        }
        break;
    }
    case 8:{
        if(subintervallevel>3)goto loop1;
        else {
            ui->choose1->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/resourses/8.png);}");
            ui->choose1_2->setText("空白之书");
            if(subintervallevel==0){
                ui->levelup2->setText("武器冷却时间-8%");
            }
            else if(subintervallevel==1){
                ui->levelup2->setText("等级2：武器冷却时间-8%");
            }
            else if(subintervallevel==2){
                ui->levelup2->setText("等级3：武器冷却时间-8%");
            }
            else if(subintervallevel==3){
                ui->levelup2->setText("等级4：武器冷却时间-8%");
            }
        }
        break;
    }
    case 9:{
        if(adddurationlevel>3)goto loop1;
        else {
            ui->choose1->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/resourses/9.png);}");
            ui->choose1_2->setText("咒缚盒");
            if(adddurationlevel==0){
                ui->levelup2->setText("武器的持续时间+10%");
            }
            else if(adddurationlevel==1){
                ui->levelup2->setText("等级2：武器的持续时间+10%");
            }
            else if(adddurationlevel==2){
                ui->levelup2->setText("等级3：武器的持续时间+10%");
            }
            else if(adddurationlevel==3){
                ui->levelup2->setText("等级4：武器的持续时间+10%");
            }
        }
        break;
    }
    case 10:{
        if(addzonelevel>3)goto loop1;
        else {
            ui->choose1->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/resourses/10.png);}");
            ui->choose1_2->setText("念力法球");
            if(addzonelevel==0){
                ui->levelup2->setText("拾取范围+10%");
            }
            else if(addzonelevel==1){
                ui->levelup2->setText("等级2：拾取范围+10%");
            }
            else if(addzonelevel==2){
                ui->levelup2->setText("等级3：拾取范围+10%");
            }
            else if(addzonelevel==3){
                ui->levelup2->setText("等级4：拾取范围+10%");
            }
        }
        break;
    }
    }
    choose1=x;

    if(total<47){
loop2:y=rand()%10+1;
    if(y==x)goto loop2;
    switch(y)
    {
    case 1:{
        if(ropelevel>5)goto loop1;
        else {
            ui->choose2->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/resourses/1.png);}");
            ui->choose2_2->setText("神鞭");
            if(ropelevel==0){
                ui->levelup3->setText("水平攻击，可贯穿敌人");
            }
            else if(ropelevel==1){
                ui->levelup3->setText("等级2：发射数+1");
            }
            else if(ropelevel==2){
                ui->levelup3->setText("等级3：伤害+7");
            }
            else if(ropelevel==3){
                ui->levelup3->setText("等级4：伤害+7");
            }
            else if(ropelevel==4){
                ui->levelup3->setText("等级5：伤害+7");
            }
            else if(ropelevel==5){
                ui->levelup3->setText("等级6：伤害+7");
            }
        }
        break;
    }
    case 2:{
        if(knifelevel>5)goto loop1;
        else {
            ui->choose2->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/resourses/2.png);}");
            ui->choose2_2->setText("飞刀");
            if(knifelevel==0){
                ui->levelup3->setText("朝面对的对象快速发射");
            }
            else if(knifelevel==1){
                ui->levelup3->setText("等级2：发射数+1");
            }
            else if(knifelevel==2){
                ui->levelup3->setText("等级3：伤害+5");
            }
            else if(knifelevel==3){
                ui->levelup3->setText("等级4：发射数+1");
            }
            else if(knifelevel==4){
                ui->levelup3->setText("等级5：伤害+5");
            }
            else if(knifelevel==5){
                ui->levelup3->setText("等级6：伤害+5");
            }
        }
        break;
    }
    case 3:{
        if(bulletlevel>5)goto loop1;
        else {
            ui->choose2->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/resourses/3.png);}");
            ui->choose2_2->setText("痕印石");
            if(bulletlevel==0){
                ui->levelup3->setText("贯穿攻击，可四处反弹");
            }
            else if(bulletlevel==1){
                ui->levelup3->setText("等级2：伤害+5，速度+20%");
            }
            else if(bulletlevel==2){
                ui->levelup3->setText("等级3：贯穿攻击，持续时间+30%");
            }
            else if(bulletlevel==3){
                ui->levelup3->setText("等级4：发射数+1");
            }
            else if(bulletlevel==4){
                ui->levelup3->setText("等级5：伤害+5，速度+20%");
            }
            else if(bulletlevel==5){
                ui->levelup3->setText("等级6：贯穿攻击，持续时间+30%");
            }
        }
        break;
    }
    case 4:{
        if(garliclevel>5)goto loop1;
        else {
            ui->choose2->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/resourses/4.png);}");
            ui->choose2_2->setText("大蒜");
            if(garliclevel==0){
                ui->levelup3->setText("对附近的敌人造成伤害");
            }
            else if(garliclevel==1){
                ui->levelup3->setText("等级2：攻击范围+20%");
            }
            else if(garliclevel==2){
                ui->levelup3->setText("等级3：伤害+0.2");
            }
            else if(garliclevel==3){
                ui->levelup3->setText("等级4：攻击范围+20%");
            }
            else if(garliclevel==4){
                ui->levelup3->setText("等级5：伤害+0.2");
            }
            else if(garliclevel==5){
                ui->levelup3->setText("等级6：伤害+0.2");
            }
        }
        break;
    }
    case 5:{
        if(maxhplevel>3)goto loop1;
        else {
            ui->choose2->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/resourses/5.png);}");
            ui->choose2_2->setText("空虚之心");
            if(maxhplevel==0){
                ui->levelup3->setText("生命上限+20%");
            }
            else if(maxhplevel==1){
                ui->levelup3->setText("等级2：生命上限+20%");
            }
            else if(maxhplevel==2){
                ui->levelup3->setText("等级3：生命上限+20%");
            }
            else if(maxhplevel==3){
                ui->levelup3->setText("等级4：生命上限+20%");
            }
        }
        break;
    }
    case 6:{
        if(addhplevel>3)goto loop1;
        else {
            ui->choose2->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/resourses/6.png);}");
            ui->choose2_2->setText("愈伤番茄");
            if(addhplevel==0){
                ui->levelup3->setText("角色每秒生命恢复0.2");
            }
            else if(addhplevel==1){
                ui->levelup3->setText("等级2：角色每秒生命恢复0.4");
            }
            else if(addhplevel==2){
                ui->levelup3->setText("等级3：角色每秒生命恢复0.6");
            }
            else if(addhplevel==3){
                ui->levelup3->setText("等级4：角色每秒生命恢复0.8");
            }
        }
        break;
    }
    case 7:{
        if(addspeedlevel>3)goto loop1;
        else {
            ui->choose2->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/resourses/7.png);}");
            ui->choose2_2->setText("翅膀");
            if(addspeedlevel==0){
                ui->levelup3->setText("速度+20%");
            }
            else if(addspeedlevel==1){
                ui->levelup3->setText("等级2：速度+20%");
            }
            else if(addspeedlevel==2){
                ui->levelup3->setText("等级3：速度+20%");
            }
            else if(addspeedlevel==3){
                ui->levelup3->setText("等级4：速度+20%");
            }
        }
        break;
    }
    case 8:{
        if(subintervallevel>3)goto loop1;
        else {
            ui->choose2->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/resourses/8.png);}");
            ui->choose2_2->setText("空白之书");
            if(subintervallevel==0){
                ui->levelup3->setText("武器冷却时间-8%");
            }
            else if(subintervallevel==1){
                ui->levelup3->setText("等级2：武器冷却时间-8%");
            }
            else if(subintervallevel==2){
                ui->levelup3->setText("等级3：武器冷却时间-8%");
            }
            else if(subintervallevel==3){
                ui->levelup3->setText("等级4：武器冷却时间-8%");
            }
        }
        break;
    }
    case 9:{
        if(adddurationlevel>3)goto loop1;
        else {
            ui->choose2->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/resourses/9.png);}");
            ui->choose2_2->setText("咒缚盒");
            if(adddurationlevel==0){
                ui->levelup3->setText("武器的持续时间+10%");
            }
            else if(adddurationlevel==1){
                ui->levelup3->setText("等级2：武器的持续时间+10%");
            }
            else if(adddurationlevel==2){
                ui->levelup3->setText("等级3：武器的持续时间+10%");
            }
            else if(adddurationlevel==3){
                ui->levelup3->setText("等级4：武器的持续时间+10%");
            }
        }
        break;
    }
    case 10:{
        if(addzonelevel>3)goto loop1;
        else {
            ui->choose2->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/resourses/10.png);}");
            ui->choose2_2->setText("念力法球");
            if(addzonelevel==0){
                ui->levelup3->setText("拾取范围+10%");
            }
            else if(addzonelevel==1){
                ui->levelup3->setText("等级2：拾取范围+10%");
            }
            else if(addzonelevel==2){
                ui->levelup3->setText("等级3：拾取范围+10%");
            }
            else if(addzonelevel==3){
                ui->levelup3->setText("等级4：拾取范围+10%");
            }
        }
        break;
    }
    }
    choose2=y;

    if(total<46){
loop3:z=rand()%10+1;
    if(z==x||z==y)goto loop3;
    switch(z)
    {
    case 1:{
        if(ropelevel>5)goto loop1;
        else {
            ui->choose3->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/resourses/1.png);}");
            ui->choose3_2->setText("神鞭");
            if(ropelevel==0){
                ui->levelup4->setText("水平攻击，可贯穿敌人");
            }
            else if(ropelevel==1){
                ui->levelup4->setText("等级2：发射数+1");
            }
            else if(ropelevel==2){
                ui->levelup4->setText("等级3：伤害+7");
            }
            else if(ropelevel==3){
                ui->levelup4->setText("等级4：伤害+7");
            }
            else if(ropelevel==4){
                ui->levelup4->setText("等级5：伤害+7");
            }
            else if(ropelevel==5){
                ui->levelup4->setText("等级6：伤害+7");
            }
        }
        break;
    }
    case 2:{
        if(knifelevel>5)goto loop1;
        else {
            ui->choose3->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/resourses/2.png);}");
            ui->choose3_2->setText("飞刀");
            if(knifelevel==0){
                ui->levelup4->setText("朝面对的对象快速发射");
            }
            else if(knifelevel==1){
                ui->levelup4->setText("等级2：发射数+1");
            }
            else if(knifelevel==2){
                ui->levelup4->setText("等级3：伤害+5");
            }
            else if(knifelevel==3){
                ui->levelup4->setText("等级4：发射数+1");
            }
            else if(knifelevel==4){
                ui->levelup4->setText("等级5：伤害+5");
            }
            else if(knifelevel==5){
                ui->levelup4->setText("等级6：伤害+5");
            }
        }
        break;
    }
    case 3:{
        if(bulletlevel>5)goto loop1;
        else {
            ui->choose3->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/resourses/3.png);}");
            ui->choose3_2->setText("痕印石");
            if(bulletlevel==0){
                ui->levelup4->setText("贯穿攻击，可四处反弹");
            }
            else if(bulletlevel==1){
                ui->levelup4->setText("等级2：伤害+5，速度+20%");
            }
            else if(bulletlevel==2){
                ui->levelup4->setText("等级3：贯穿攻击，持续时间+30%");
            }
            else if(bulletlevel==3){
                ui->levelup4->setText("等级4：发射数+1");
            }
            else if(bulletlevel==4){
                ui->levelup4->setText("等级5：伤害+5，速度+20%");
            }
            else if(bulletlevel==5){
                ui->levelup4->setText("等级6：贯穿攻击，持续时间+30%");
            }
        }
        break;
    }
    case 4:{
        if(garliclevel>5)goto loop1;
        else {
            ui->choose3->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/resourses/4.png);}");
            ui->choose3_2->setText("大蒜");
            if(garliclevel==0){
                ui->levelup4->setText("对附近的敌人造成伤害");
            }
            else if(garliclevel==1){
                ui->levelup4->setText("等级2：攻击范围+20%");
            }
            else if(garliclevel==2){
                ui->levelup4->setText("等级3：伤害+0.2");
            }
            else if(garliclevel==3){
                ui->levelup4->setText("等级4：攻击范围+20%");
            }
            else if(garliclevel==4){
                ui->levelup4->setText("等级5：伤害+0.2");
            }
            else if(garliclevel==5){
                ui->levelup4->setText("等级6：伤害+0.2");
            }
        }
        break;
    }
    case 5:{
        if(maxhplevel>3)goto loop1;
        else {
            ui->choose3->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/resourses/5.png);}");
            ui->choose3_2->setText("空虚之心");
            if(maxhplevel==0){
                ui->levelup4->setText("生命上限+20%");
            }
            else if(maxhplevel==1){
                ui->levelup4->setText("等级2：生命上限+20%");
            }
            else if(maxhplevel==2){
                ui->levelup4->setText("等级3：生命上限+20%");
            }
            else if(maxhplevel==3){
                ui->levelup4->setText("等级4：生命上限+20%");
            }
        }
        break;
    }
    case 6:{
        if(addhplevel>3)goto loop1;
        else {
            ui->choose3->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/resourses/6.png);}");
            ui->choose3_2->setText("愈伤番茄");
            if(addhplevel==0){
                ui->levelup4->setText("角色每秒生命恢复0.2");
            }
            else if(addhplevel==1){
                ui->levelup4->setText("等级2：角色每秒生命恢复0.4");
            }
            else if(addhplevel==2){
                ui->levelup4->setText("等级3：角色每秒生命恢复0.6");
            }
            else if(addhplevel==3){
                ui->levelup4->setText("等级4：角色每秒生命恢复0.8");
            }
        }
        break;
    }
    case 7:{
        if(addspeedlevel>3)goto loop1;
        else {
            ui->choose3->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/resourses/7.png);}");
            ui->choose3_2->setText("翅膀");
            if(addspeedlevel==0){
                ui->levelup4->setText("速度+20%");
            }
            else if(addspeedlevel==1){
                ui->levelup4->setText("等级2：速度+20%");
            }
            else if(addspeedlevel==2){
                ui->levelup4->setText("等级3：速度+20%");
            }
            else if(addspeedlevel==3){
                ui->levelup4->setText("等级4：速度+20%");
            }
        }
        break;
    }
    case 8:{
        if(subintervallevel>3)goto loop1;
        else {
            ui->choose3->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/resourses/8.png);}");
            ui->choose3_2->setText("空白之书");
            if(subintervallevel==0){
                ui->levelup4->setText("武器冷却时间-8%");
            }
            else if(subintervallevel==1){
                ui->levelup4->setText("等级2：武器冷却时间-8%");
            }
            else if(subintervallevel==2){
                ui->levelup4->setText("等级3：武器冷却时间-8%");
            }
            else if(subintervallevel==3){
                ui->levelup4->setText("等级4：武器冷却时间-8%");
            }
        }
        break;
    }
    case 9:{
        if(adddurationlevel>3)goto loop1;
        else {
            ui->choose3->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/resourses/9.png);}");
            ui->choose3_2->setText("咒缚盒");
            if(adddurationlevel==0){
                ui->levelup4->setText("武器的持续时间+10%");
            }
            else if(adddurationlevel==1){
                ui->levelup4->setText("等级2：武器的持续时间+10%");
            }
            else if(adddurationlevel==2){
                ui->levelup4->setText("等级3：武器的持续时间+10%");
            }
            else if(adddurationlevel==3){
                ui->levelup4->setText("等级4：武器的持续时间+10%");
            }
        }
        break;
    }
    case 10:{
        if(addzonelevel>3)goto loop1;
        else {
            ui->choose3->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/resourses/10.png);}");
            ui->choose3_2->setText("念力法球");
            if(addzonelevel==0){
                ui->levelup4->setText("拾取范围+10%");
            }
            else if(addzonelevel==1){
                ui->levelup4->setText("等级2：拾取范围+10%");
            }
            else if(addzonelevel==2){
                ui->levelup4->setText("等级3：拾取范围+10%");
            }
            else if(addzonelevel==3){
                ui->levelup4->setText("等级4：拾取范围+10%");
            }
        }
        break;
    }
    }
    choose3=z;
    }
    else {
        choose3=0;
        ui->levelup4->lower();
        ui->choose3->lower();
        ui->choose3_2->lower();
    }
    }
    else {
        choose3=0;
        choose2=0;
        ui->levelup3->lower();
        ui->levelup4->lower();
        ui->choose2->lower();
        ui->choose3->lower();
        ui->choose2_2->lower();
        ui->choose3_2->lower();
    }
    }
    else {
        choose3=0;
        choose2=0;
        choose1=0;
    }

}

void game::draw()
{
    ui->draw1->raise();
    ui->draw2->raise();
    ui->draw3->raise();
    ui->draw4->raise();
    ui->draw5->raise();
    ui->draw6->raise();
    ui->draw7->raise();
    ui->draw7->setEnabled(true);
    ui->draw8->raise();
    ui->draw9->raise();
    pause();
    drawtimer=new QTimer(this);
    drawtimer->start(100);
    connect(drawtimer, SIGNAL(timeout()), this, SLOT(drawrand()));
    player->play();
    music->pause();
}

void game::drawrand()
{
    drawmoney=rand()%200+50;
    ui->draw6->setText(QString::number(drawmoney));
loop4:    drawupgrade=rand()%10+1;
    switch(drawupgrade)
    {
    case 1:{
        if(ropelevel>5)goto loop4;
        else {
            ui->draw3->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/resourses/1.png);}");
            if(ropelevel==0){
                            ui->draw9->setText("水平攻击，可贯穿敌人");
                        }
                        else if(ropelevel==1){
                            ui->draw9->setText("等级2：发射数+1");
                        }
                        else if(ropelevel==2){
                            ui->draw9->setText("等级3：伤害+7");
                        }
                        else if(ropelevel==3){
                            ui->draw9->setText("等级4：伤害+7");
                        }
                        else if(ropelevel==4){
                            ui->draw9->setText("等级5：伤害+7");
                        }
                        else if(ropelevel==5){
                            ui->draw9->setText("等级6：伤害+7");
                        }
        }
        break;
    }
    case 2:{
        if(knifelevel>5)goto loop4;
        else {
            ui->draw3->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/resourses/2.png);}");
            if(knifelevel==0){
                            ui->draw9->setText("朝面对的对象快速发射");
                        }
                        else if(knifelevel==1){
                            ui->draw9->setText("等级2：发射数+1");
                        }
                        else if(knifelevel==2){
                            ui->draw9->setText("等级3：伤害+5");
                        }
                        else if(knifelevel==3){
                            ui->draw9->setText("等级4：发射数+1");
                        }
                        else if(knifelevel==4){
                            ui->draw9->setText("等级5：伤害+5");
                        }
                        else if(knifelevel==5){
                            ui->draw9->setText("等级6：伤害+5");
                        }
        }
        break;
    }
    case 3:{
        if(bulletlevel>5)goto loop4;
        else {
            ui->draw3->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/resourses/3.png);}");
            if(bulletlevel==0){
                            ui->draw9->setText("贯穿攻击，可四处反弹");
                        }
                        else if(bulletlevel==1){
                            ui->draw9->setText("等级2：伤害+5，速度+20%");
                        }
                        else if(bulletlevel==2){
                            ui->draw9->setText("等级3：贯穿攻击，持续时间+30%");
                        }
                        else if(bulletlevel==3){
                            ui->draw9->setText("等级4：发射数+1");
                        }
                        else if(bulletlevel==4){
                            ui->draw9->setText("等级5：伤害+5，速度+20%");
                        }
                        else if(bulletlevel==5){
                            ui->draw9->setText("等级6：贯穿攻击，持续时间+30%");
                        }
        }
        break;
    }
    case 4:{
        if(garliclevel>5)goto loop4;
        else {
            ui->draw3->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/resourses/4.png);}");
            if(garliclevel==0){
                            ui->draw9->setText("对附近的敌人造成伤害");
                        }
                        else if(garliclevel==1){
                            ui->draw9->setText("等级2：攻击范围+20%");
                        }
                        else if(garliclevel==2){
                            ui->draw9->setText("等级3：伤害+0.2");
                        }
                        else if(garliclevel==3){
                            ui->draw9->setText("等级4：攻击范围+20%");
                        }
                        else if(garliclevel==4){
                            ui->draw9->setText("等级5：伤害+0.2");
                        }
                        else if(garliclevel==5){
                            ui->draw9->setText("等级6：伤害+0.2");
                        }
        }
        break;
    }
    case 5:{
        if(maxhplevel>3)goto loop4;
        else {
            ui->draw3->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/resourses/5.png);}");
            if(maxhplevel==0){
                            ui->draw9->setText("生命上限+20%");
                        }
                        else if(maxhplevel==1){
                            ui->draw9->setText("等级2：生命上限+20%");
                        }
                        else if(maxhplevel==2){
                            ui->draw9->setText("等级3：生命上限+20%");
                        }
                        else if(maxhplevel==3){
                            ui->draw9->setText("等级4：生命上限+20%");
                        }
        }
        break;
    }
    case 6:{
        if(addhplevel>3)goto loop4;
        else {
            ui->draw3->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/resourses/6.png);}");
            if(addhplevel==0){
                            ui->draw9->setText("角色每秒生命恢复0.2");
                        }
                        else if(addhplevel==1){
                            ui->draw9->setText("等级2：角色每秒生命恢复0.4");
                        }
                        else if(addhplevel==2){
                            ui->draw9->setText("等级3：角色每秒生命恢复0.6");
                        }
                        else if(addhplevel==3){
                            ui->draw9->setText("等级4：角色每秒生命恢复0.8");
                        }
        }
        break;
    }
    case 7:{
        if(addspeedlevel>3)goto loop4;
        else {
            ui->draw3->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/resourses/7.png);}");
            if(addspeedlevel==0){
                           ui->draw9->setText("速度+20%");
                       }
                       else if(addspeedlevel==1){
                           ui->draw9->setText("等级2：速度+20%");
                       }
                       else if(addspeedlevel==2){
                           ui->draw9->setText("等级3：速度+20%");
                       }
                       else if(addspeedlevel==3){
                           ui->draw9->setText("等级4：速度+20%");
                       }
        }
        break;
    }
    case 8:{
        if(subintervallevel>3)goto loop4;
        else {
            ui->draw3->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/resourses/8.png);}");
            if(subintervallevel==0){
                            ui->draw9->setText("武器冷却时间-8%");
                        }
                        else if(subintervallevel==1){
                            ui->draw9->setText("等级2：武器冷却时间-8%");
                        }
                        else if(subintervallevel==2){
                            ui->draw9->setText("等级3：武器冷却时间-8%");
                        }
                        else if(subintervallevel==3){
                            ui->draw9->setText("等级4：武器冷却时间-8%");
                        }
        }
        break;
    }
    case 9:{
        if(adddurationlevel>3)goto loop4;
        else {
            ui->draw3->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/resourses/9.png);}");
            if(adddurationlevel==0){
                            ui->draw9->setText("武器的持续时间+10%");
                        }
                        else if(adddurationlevel==1){
                            ui->draw9->setText("等级2：武器的持续时间+10%");
                        }
                        else if(adddurationlevel==2){
                            ui->draw9->setText("等级3：武器的持续时间+10%");
                        }
                        else if(adddurationlevel==3){
                            ui->draw9->setText("等级4：武器的持续时间+10%");
                        }
        }
        break;
    }
    case 10:{
        if(addzonelevel>3)goto loop4;
        else {
            ui->draw3->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/resourses/10.png);}");
            if(addzonelevel==0){
                            ui->draw9->setText("拾取范围+10%");
                        }
                        else if(addzonelevel==1){
                            ui->draw9->setText("等级2：拾取范围+10%");
                        }
                        else if(addzonelevel==2){
                            ui->draw9->setText("等级3：拾取范围+10%");
                        }
                        else if(addzonelevel==3){
                            ui->draw9->setText("等级4：拾取范围+10%");
                        }
        }
        break;
    }
    }
}

void game::pause()
{
    ifpause=true;
    if(interval!=nullptr)interval->stop();
    if(addtimer!=nullptr)addtimer->stop();
    if(hptimer!=nullptr)hptimer->stop();
    if(gametimer!=nullptr)gametimer->stop();
    if(movetimer!=nullptr)movetimer->stop();
    if(collecttimer!=nullptr)collecttimer->stop();
    if(ropetimer!=nullptr)ropetimer->stop();
    if(ropeattacktimer!=nullptr)ropeattacktimer->stop();
    if(knifetimer!=nullptr)knifetimer->stop();
    if(knifemovetimer!=nullptr)knifemovetimer->stop();
    if(bullettimer!=nullptr)bullettimer->stop();
    if(bulletmovetimer!=nullptr)bulletmovetimer->stop();
    if(garlicattacktimer!=nullptr)garlicattacktimer->stop();
    if(enemycreatetimer!=nullptr)enemycreatetimer->stop();
    if(enemymovetimer!=nullptr)enemymovetimer->stop();
    if(enemycollisontimer!=nullptr)enemycollisontimer->stop();
    if(ropecollisontimer!=nullptr)ropecollisontimer->stop();
    if(bosscreatetimer!=nullptr)bosscreatetimer->stop();
    if(bossattacktimer!=nullptr)bossattacktimer->stop();
    if(drawtimer!=nullptr)drawtimer->stop();
}

void game::continue_()
{
    ifpause=false;
    if(interval!=nullptr)interval->start();
    if(addtimer!=nullptr)addtimer->start();
    if(hptimer!=nullptr)hptimer->start();
    if(gametimer!=nullptr)gametimer->start();
    if(movetimer!=nullptr)movetimer->start();
    if(collecttimer!=nullptr)collecttimer->start();
    if(ropetimer!=nullptr)ropetimer->start();
    if(ropeattacktimer!=nullptr)ropeattacktimer->start();
    if(knifetimer!=nullptr)knifetimer->start();
    if(knifemovetimer!=nullptr)knifemovetimer->start();
    if(bullettimer!=nullptr)bullettimer->start();
    if(bulletmovetimer!=nullptr)bulletmovetimer->start();
    if(garlicattacktimer!=nullptr)garlicattacktimer->start();
    if(enemycreatetimer!=nullptr)enemycreatetimer->start();
    if(enemymovetimer!=nullptr)enemymovetimer->start();
    if(enemycollisontimer!=nullptr)enemycollisontimer->start();
    if(ropecollisontimer!=nullptr)ropecollisontimer->start();
    if(bosscreatetimer!=nullptr)bosscreatetimer->start();
    if(bossattacktimer!=nullptr)bossattacktimer->start();
    if(drawtimer!=nullptr)drawtimer->start();

    ui->levelup->lower();
    ui->levelup1->lower();
    ui->levelup2->lower();
    ui->levelup3->lower();
    ui->levelup4->lower();
    ui->choose1->lower();
    ui->choose2->lower();
    ui->choose3->lower();
    ui->choose1_2->lower();
    ui->choose2_2->lower();
    ui->choose3_2->lower();
    ui->continue_2->lower();
    ui->quit->lower();
    ui->draw1->lower();
    ui->draw2->lower();
    ui->draw3->lower();
    ui->draw4->lower();
    ui->draw5->lower();
    ui->draw6->lower();
    ui->draw7->lower();
    ui->draw8->lower();
    ui->draw9->lower();
    ui->draw10->lower();
    ui->save->lower();

    ui->choose1->setEnabled(false);
    ui->choose2->setEnabled(false);
    ui->choose3->setEnabled(false);
    ui->continue_2->setEnabled(false);
    ui->quit->setEnabled(false);
    ui->draw7->setEnabled(false);
    ui->draw10->setEnabled(false);
}

void game::gameover()
{
    pause();
    ui->gameover3->raise();
    ui->gameover1->raise();
    ui->gameover2->setEnabled(true);
    ui->gameover2->raise();
}

void game::keyPressEvent(QKeyEvent *event)
{
    switch(event->key()){
    case Qt::Key_W:
    case Qt::Key_S:
    case Qt::Key_A:
    case Qt::Key_D:
        Mkeylist.append(event->key());
        break;
    }
}


void game::keyReleaseEvent(QKeyEvent *event)
{
    if(Mkeylist.contains(event->key()))
    {
        Mkeylist.removeOne(event->key());
    }
}

game::~game()
{
    delete ui;
}

void game::on_pause_clicked()
{
    pause();
    ui->save->raise();
    ui->continue_2->raise();
    ui->continue_2->setEnabled(true);
    ui->quit->setEnabled(true);
    ui->quit->raise();
}


void game::on_continue_2_clicked()
{
    continue_();
}

void game::on_quit_clicked()
{
    quit();
}

void game::on_gameover2_clicked()
{
    quit();
}

void game::on_choose1_clicked()
{
    switch (choose1) {
    case 1:{
        ropelevel++;
        if(ropelevel==1)rope();
        break;
    }
    case 2:{
        knifelevel++;
        if(knifelevel==1)knife();
        else if(knifelevel==2||knifelevel==4)knifenumber++;
        break;
    }
    case 3:{
        bulletlevel++;
        if(bulletlevel==1)bullet();
        else if(bulletlevel==4)bulletnumber++;
        break;
    }
    case 4:{
        garliclevel++;
        if(garliclevel==1)garlic();
        else {
            scene.removeItem(&garlic_);
            scene.removeItem(&role);
            garlic_.upgrade(garliclevel);
            scene.addItem(&garlic_);
            scene.addItem(&role);
            if(garliclevel==3){
                garlicattacktimer->stop();
                garlicattacktimer->start(900);
            }
            else if(garliclevel==5){
                garlicattacktimer->stop();
                garlicattacktimer->start(800);
            }
            else if(garliclevel==7){
                garlicattacktimer->stop();
                garlicattacktimer->start(700);
            }
        }
        break;
    }
    case 5:maxhplevel++;hpmax=hpmax+20;break;
    case 6:addhplevel++;break;
    case 7:addspeedlevel++;speed=speed+2*addspeedlevel;break;
    case 8:subintervallevel++;break;
    case 9:adddurationlevel++;break;
    case 10:addzonelevel++;break;
    }
    continue_();
}

void game::on_choose2_clicked()
{
    switch (choose2) {
    case 1:{
        ropelevel++;
        if(ropelevel==1)rope();
        break;
    }
    case 2:{
        knifelevel++;
        if(knifelevel==1)knife();
        else if(knifelevel==2||knifelevel==4)knifenumber++;
        break;
    }
    case 3:{
        bulletlevel++;
        if(bulletlevel==1)bullet();
        else if(bulletlevel==4)bulletnumber++;
        break;
    }
    case 4:{
        garliclevel++;
        if(garliclevel==1)garlic();
        else {
            scene.removeItem(&garlic_);
            scene.removeItem(&role);
            garlic_.upgrade(garliclevel);
            scene.addItem(&garlic_);
            scene.addItem(&role);
            if(garliclevel==3){
                garlicattacktimer->stop();
                garlicattacktimer->start(900);
            }
            else if(garliclevel==5){
                garlicattacktimer->stop();
                garlicattacktimer->start(800);
            }
            else if(garliclevel==7){
                garlicattacktimer->stop();
                garlicattacktimer->start(700);
            }
        }
        break;
    }
    case 5:maxhplevel++;hpmax=hpmax+20;break;
    case 6:addhplevel++;break;
    case 7:addspeedlevel++;speed=speed+2*addspeedlevel;break;
    case 8:subintervallevel++;break;
    case 9:adddurationlevel++;break;
    case 10:addzonelevel++;break;
    }
    continue_();
}

void game::on_choose3_clicked()
{
    switch (choose3) {
    case 1:{
        ropelevel++;
        if(ropelevel==1)rope();
        break;
    }
    case 2:{
        knifelevel++;
        if(knifelevel==1)knife();
        else if(knifelevel==2||knifelevel==4)knifenumber++;
        break;
    }
    case 3:{
        bulletlevel++;
        if(bulletlevel==1)bullet();
        else if(bulletlevel==4)bulletnumber++;
        break;
    }
    case 4:{
        garliclevel++;
        if(garliclevel==1)garlic();
        else {
            scene.removeItem(&garlic_);
            scene.removeItem(&role);
            garlic_.upgrade(garliclevel);
            scene.addItem(&garlic_);
            scene.addItem(&role);
            if(garliclevel==3){
                garlicattacktimer->stop();
                garlicattacktimer->start(900);
            }
            else if(garliclevel==5){
                garlicattacktimer->stop();
                garlicattacktimer->start(800);
            }
            else if(garliclevel==7){
                garlicattacktimer->stop();
                garlicattacktimer->start(700);
            }
        }
        break;
    }
    case 5:maxhplevel++;hpmax=hpmax+20;break;
    case 6:addhplevel++;break;
    case 7:addspeedlevel++;speed=speed+2*addspeedlevel;break;
    case 8:subintervallevel++;break;
    case 9:adddurationlevel++;break;
    case 10:addzonelevel++;break;
    }
    continue_();
}

void game::on_draw7_clicked()
{
    drawtimer->stop();
    delete drawtimer;
    drawtimer=nullptr;
    ui->draw7->lower();
    ui->draw10->raise();
    ui->draw10->setEnabled(true);
}

void game::on_draw10_clicked()
{
    continue_();
    music->play();
    player->stop();
    gain=gain+drawmoney;
    switch (drawupgrade) {
    case 1:{
        ropelevel++;
        if(ropelevel==1)rope();
        break;
    }
    case 2:{
        knifelevel++;
        if(knifelevel==1)knife();
        else if(knifelevel==2||knifelevel==4)knifenumber++;
        break;
    }
    case 3:{
        bulletlevel++;
        if(bulletlevel==1)bullet();
        else if(bulletlevel==4)bulletnumber++;
        break;
    }
    case 4:{
        garliclevel++;
        if(garliclevel==1)garlic();
        else {
            scene.removeItem(&garlic_);
            scene.removeItem(&role);
            garlic_.upgrade(garliclevel);
            scene.addItem(&garlic_);
            scene.addItem(&role);
            if(garliclevel==3){
                garlicattacktimer->stop();
                garlicattacktimer->start(900);
            }
            else if(garliclevel==5){
                garlicattacktimer->stop();
                garlicattacktimer->start(800);
            }
            else if(garliclevel==7){
                garlicattacktimer->stop();
                garlicattacktimer->start(700);
            }
        }
        break;
    }
    case 5:maxhplevel++;hpmax=hpmax+20;break;
    case 6:addhplevel++;break;
    case 7:addspeedlevel++;speed=speed+2*addspeedlevel;break;
    case 8:subintervallevel++;break;
    case 9:adddurationlevel++;break;
    case 10:addzonelevel++;break;
    }
}

void game::on_save_clicked()
{
    if(chosenmap==1){
        QFile gamefile("D://QTgame//1//1//resourses//1.txt");
        gamefile.open(QIODevice::WriteOnly|QFile::Truncate); //判断文件是否正常打开
        QTextStream text_stream(&gamefile);
        text_stream<<gametime.toString("mm")<<endl;
        text_stream<<gametime.toString("ss")<<endl;
        text_stream<<exp<<endl;
        text_stream<<max<<endl;
        text_stream<<ui->exp->value()<<endl;
        text_stream<<ui->exp->maximum()<<endl;
        text_stream<<level<<endl;
        text_stream<<gain<<endl;
        text_stream<<kill<<endl;
        text_stream<<ropelevel<<endl;
        text_stream<<knifelevel<<endl;
        text_stream<<knifenumber<<endl;
        text_stream<<bulletlevel<<endl;
        text_stream<<bulletnumber<<endl;
        text_stream<<garliclevel<<endl;
        text_stream<<maxhplevel<<endl;
        text_stream<<addhplevel<<endl;
        text_stream<<addspeedlevel<<endl;
        text_stream<<subintervallevel<<endl;
        text_stream<<adddurationlevel<<endl;
        text_stream<<addzonelevel<<endl;
        for(auto enemy:enemylist){
            text_stream<<enemy->type<<endl;
            text_stream<<enemy->x()<<endl;
            text_stream<<enemy->y()<<endl;
        }
        gamefile.flush();
        gamefile.close();
        QMessageBox::information(this,"提示","存档成功！");
    }
    else if(chosenmap==2){
        QFile gamefile("D://QTgame//1//1//resourses//1.txt");
        gamefile.open(QIODevice::WriteOnly|QFile::Truncate); //判断文件是否正常打开
        QTextStream text_stream(&gamefile);
        text_stream<<gametime.toString("mm")<<endl;
        text_stream<<gametime.toString("ss")<<endl;
        text_stream<<exp<<endl;
        text_stream<<max<<endl;
        text_stream<<ui->exp->value()<<endl;
        text_stream<<ui->exp->maximum()<<endl;
        text_stream<<level<<endl;
        text_stream<<gain<<endl;
        text_stream<<kill<<endl;
        text_stream<<ropelevel<<endl;
        text_stream<<knifelevel<<endl;
        text_stream<<knifenumber<<endl;
        text_stream<<bulletlevel<<endl;
        text_stream<<bulletnumber<<endl;
        text_stream<<garliclevel<<endl;
        text_stream<<maxhplevel<<endl;
        text_stream<<addhplevel<<endl;
        text_stream<<addspeedlevel<<endl;
        text_stream<<subintervallevel<<endl;
        text_stream<<adddurationlevel<<endl;
        text_stream<<addzonelevel<<endl;
        for(auto enemy:enemylist){
            text_stream<<enemy->type<<endl;
            text_stream<<enemy->x()<<endl;
            text_stream<<enemy->y()<<endl;
        }
        gamefile.flush();
        gamefile.close();
        QMessageBox::information(this,"提示","存档成功！");
    }
}
