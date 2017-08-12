#include "chassis_display.h"
#include "ui_chassis_display.h"

#include <iostream>
#include <fstream>
#include "speed_planning.h"
#include "my_chassis_init.h"
#include "ethercat_init.h"
#include <pthread.h>
#include <stdlib.h>
pthread_t thread_a,thread_b;
int res_a,res_b;
void *realtask(void *arg);

QString str_FLCPOS;
QString str_BLCPOS;
QString str_FLTPOS;
QString str_BLTPOS;

QString str_FLCVEL;
QString str_BLCVEL;
QString str_FLTVEL;
QString str_BLTVEL;

QString str_FLPVEL;
QString str_BLPVEL;
QString str_FLEVEL;
QString str_BLEVEL;

QString str_FLPACC;
QString str_BLPACC;
QString str_FLPDEC;
QString str_BLPDEC;

QString str_CURRENTX;
QString str_CURRENTY;
QString str_CURRENTS;

QString str_TRACKX;
QString str_TRACKY;
QString str_TRACKS;

QString str_DESTX;
QString str_DESTY;
QString str_DESTS;

QString str_CPPNUM;
QString str_AIMNUM;

chassis_display::chassis_display(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::chassis_display)
{
    ui->setupUi(this);
    ui->STARTButton->setEnabled(false);
    ui->STOPButton->setEnabled(false);
    ui->CLOSEButton->setEnabled(false);
    ui->PLANButton->setEnabled(false);
    ui->TRACKButton->setEnabled(false);
}

chassis_display::~chassis_display()
{
    delete ui;
}



//对话框数据实时更新
void chassis_display::timerupdate()
{
    //数据更新
    str_FLCPOS=QString::number(chassis.motorFL.actpos);
    str_FLCVEL=QString::number(chassis.motorFL.actvel);
    str_BLCPOS=QString::number(chassis.motorBL.actpos);
    str_BLCVEL=QString::number(chassis.motorBL.actvel);

    str_FLTPOS=QString::number(chassis.motorFL.tarpos);
    str_FLTVEL=QString::number(chassis.motorFL.tarvel);
    str_FLPVEL=QString::number(chassis.motorFL.provel);
    str_FLPACC=QString::number(chassis.motorFL.proacc);
    str_FLPDEC=QString::number(chassis.motorFL.prodec);

    str_BLTPOS=QString::number(chassis.motorBL.tarpos);
    str_BLTVEL=QString::number(chassis.motorBL.tarvel);
    str_BLPVEL=QString::number(chassis.motorBL.provel);
    str_BLPACC=QString::number(chassis.motorBL.proacc);
    str_BLPDEC=QString::number(chassis.motorBL.prodec);

    str_CURRENTX=QString::number(chassis.actstatus.x);
    str_CURRENTY=QString::number(chassis.actstatus.y);
    str_CURRENTS=QString::number(chassis.actstatus.sita);

    str_TRACKX=QString::number(chassis.objstatus.x);
    str_TRACKY=QString::number(chassis.objstatus.y);
    str_TRACKS=QString::number(chassis.objstatus.sita);
    //motor info
    ui->FLCPOS->setText(str_FLCPOS);
    ui->FLCVEL->setText(str_FLCVEL);

    ui->BLCPOS->setText(str_BLCPOS);
    ui->BLCVEL->setText(str_BLCVEL);

    ui->FLTPOS->setText(str_FLTPOS);
    ui->FLTVEL->setText(str_FLTVEL);
    ui->FLPVEL->setText(str_FLPVEL);
    ui->FLPACC->setText(str_FLPACC);
    ui->FLPDEC->setText(str_FLPDEC);

    ui->BLTPOS->setText(str_BLTPOS);
    ui->BLTVEL->setText(str_BLTVEL);
    ui->BLPVEL->setText(str_BLPVEL);
    ui->BLPACC->setText(str_BLPACC);
    ui->BLPDEC->setText(str_BLPDEC);

    //chassis info
    ui->CURRENTX->setText(str_CURRENTX);
    ui->CURRENTY->setText(str_CURRENTY);
    ui->CURRENTS->setText(str_CURRENTS);

    //ui->DESTX->setText(str_DESTX);
    //ui->DESTY->setText(str_DESTY);
    //ui->DESTS->setText(str_DESTS);

    ui->TRACKX->setText(str_TRACKX);
    ui->TRACKY->setText(str_TRACKY);
    ui->TRACKS->setText(str_TRACKS);

    ui->CPPNUM->setText(str_CPPNUM);
    //ui->AIMNUM->setText(str_AIMNUM);
}

void chassis_display::on_AIMNUM_editingFinished()
{
    str_AIMNUM = ui->AIMNUM->text();
}

void chassis_display::on_OPENButton_clicked()
{

    //打开ethercat通信
    system("/home/qgh/chassis_control_test/chassis_test_001/estun-config.sh");
    res_a = pthread_create(&thread_a, NULL, EtherCAT_comm, NULL);
    while(ethercat_state == 0)
    {
        sleep(1);
    }
    ui->OPENButton->setEnabled(false);
    ui->CLOSEButton->setEnabled(true);
    ui->STARTButton->setEnabled(true);
    //开启定时器，实时更新对话框数据
    QTimer *timer0=new QTimer(this);
    connect(timer0,SIGNAL(timeout()),this,SLOT(timerupdate()));
    timer0->start(50);
}

void chassis_display::on_CLOSEButton_clicked()
{
    pthread_cancel(thread_a);
    //pthread_exit (&EtherCAT_comm);
}

void chassis_display::on_STARTButton_clicked()
{
    //底盘参数初始化
    chassis.init(COPEN, chassis_init_status);
    ui->PLANButton->setEnabled(true);
}

void chassis_display::on_STOPButton_clicked()
{
    pthread_cancel(thread_b);
}

void chassis_display::on_PLANButton_clicked()
{
    int planning_state = 0;
    POINT_chassis chassis_obj_status;
    //获取目标信息
    str_DESTX = ui->DESTX->text();
    str_DESTY = ui->DESTY->text();
    str_DESTS = ui->DESTS->text();
    chassis_obj_status.x = str_DESTX.toFloat();
    chassis_obj_status.y = str_DESTY.toFloat();
    chassis_obj_status.sita = str_DESTS.toFloat();
    CPP_num = 0;
    planning_state = chassis_planning(chassis_init_status, chassis_obj_status, 0,20);
    str_CPPNUM=QString::number(CPP_num);
    switch (planning_state)
    {
    case 1:
        printf("The obj is too close,don't need to planning!\n");
        break;
    case 2:
        printf("The obj is too far,please choose the suitable point!\n");
        break;
    case 3:
        if (1)
        {
            ofstream outfile("planning.txt");
            for (int i = 0; i <= CPP_num; i++)
            {
                outfile << CPP[i].x << "  "
                    << CPP[i].y << "  "
                    << CPP[i].sita << "  "
                    << CPP[i].v_x << "  "
                    << CPP[i].v_y << "  "
                    << CPP[i].w << "  "
                    << CPP[i].a_x << "  "
                    << CPP[i].a_y << "  "
                    << CPP[i].a_s << "  "
                    << CPP[i].r << "  "
                    << endl;
            }
        }
        ui->TRACKButton->setEnabled(true);
        break;
    }
}

void chassis_display::on_TRACKButton_clicked()
{
    res_b = pthread_create(&thread_b, NULL, realtask, NULL);
    ui->STOPButton->setEnabled(true);
}

void *realtask(void *arg)
{

    //printf("The ethercat is working!\n");

    int tracking_state = 0;
    aim_num = 0;
    while (tracking_state < 2)
    {
        //EtherCAT_comm_int();
        //cout << "Please input the tracking point!" << endl;
        //cin >> chassis_obj_status.x >> chassis_obj_status.y >> chassis_obj_status.sita;
        //printf("Please input the number of ec_state:\n");
        //cin >> ec_state;//input the number comm_int
        /*
        printf("ESTUN_CTRL data is now: %04x\n", chassis.motorBL.ctrlwd);
        printf("ESTUN_STAT data is now: %04x\n", chassis.motorBL.statwd);
        printf("ESTUN_CTRL data is now: %02x\n", chassis.motorBL.modds);
        printf("ESTUN_CTRL data is now: %02x\n", chassis.motorFL.modds);
        printf("ESTUN_CTRL data is now: %04x\n", coe_state_machine(chassis.motorFL.statwd,chassis.motorFL.ctrlwd,chassis.motorFL.modop));
        printf("ESTUN_CTRL data is now: %04x\n", chassis.motorFL.ctrlwd);
        printf("ESTUN_STAT data is now: %04x\n", chassis.motorFL.statwd);
        */
        check_slave_config_states();

        //printf("Please input the tracking point's number!\n");
        //scanf("%d",&aim_num);
        aim_num = str_AIMNUM.toInt();
        tracking_state = chassis_tracking();
        /*
        cout << "The actaul motor info of the chassis : FR,FL,BR,BL" << endl;
        cout << chassis.motorFR.actposition << " " << chassis.motorFL.actposition << " " << chassis.motorBR.actposition << " " << chassis.motorBL.actposition << endl;
        cout << chassis.motorFR.actpos << " " << chassis.motorFL.actpos << " " << chassis.motorBR.actpos << " " << chassis.motorBL.actpos << endl;
        cout << chassis.motorFL.provel << endl;
        cout << chassis.motorBL.provel << endl;
        cout << "The actaul info of the chassis : x,y,sita" << endl;
        cout << chassis.actstatus.x << " " << chassis.actstatus.y << " " << chassis.actstatus.sita << endl;
        cout << "The actaul obj is : x,y,sita" << endl;
        cout << chassis.objstatus.x << " "<<chassis.objstatus.y << " "<<chassis.objstatus.sita << endl;
        cout << "The actaul obj motor info of the chassis : FR,FL,BR,BL" << endl;
        cout << chassis.motorFR.objposition << " " << chassis.motorFL.objposition << " " << chassis.motorBR.objposition << " " << chassis.motorBL.objposition << endl;
        cout << chassis.motorFR.tarpos << " " << chassis.motorFL.tarpos << " " << chassis.motorBR.tarpos << " " << chassis.motorBL.tarpos << endl;
        cout << chassis.motorFL.provel <<  " " << chassis.motorBL.provel << endl;
        cout << chassis.motorFL.proacc <<  " " << chassis.motorBL.proacc << endl;
        */
        //if((chassis.motorFL.actpos-chassis.motorFL.tarpos)<1000&&(chassis.motorFL.actpos-chassis.motorFL.tarpos)>-1000
        //        &&(chassis.motorBL.actpos-chassis.motorBL.tarpos)<1000&&(chassis.motorBL.actpos-chassis.motorBL.tarpos)>-1000)
        if(0)
        {

            printf("Please input the new motor obj position!\n");
            scanf("%d",&(chassis.motorFL.tarpos));
            chassis.motorBL.tarpos = chassis.motorFL.tarpos;
            /*
            printf("Please input the new motor obj velocity!\n");
            scanf("%d",&(chassis.motorFL.tarvel));
            chassis.motorBL.tarvel = chassis.motorFL.tarvel;
            */
        }
        //对话框数据显示
        /*
        str_FLCPOS=QString::number(chassis.motorFL.actpos);
        str_FLCVEL=QString::number(chassis.motorFL.actvel);
        str_BLCPOS=QString::number(chassis.motorBL.actpos);
        str_BLCVEL=QString::number(chassis.motorBL.actvel);

        str_FLTPOS=QString::number(chassis.motorFL.tarpos);
        str_FLTVEL=QString::number(chassis.motorFL.tarvel);
        str_FLPVEL=QString::number(chassis.motorFL.provel);
        str_FLPACC=QString::number(chassis.motorFL.proacc);
        str_FLPDEC=QString::number(chassis.motorFL.prodec);

        str_BLTPOS=QString::number(chassis.motorBL.tarpos);
        str_BLTVEL=QString::number(chassis.motorBL.tarvel);
        str_BLPVEL=QString::number(chassis.motorBL.provel);
        str_BLPACC=QString::number(chassis.motorBL.proacc);
        str_BLPDEC=QString::number(chassis.motorBL.prodec);

        str_CURRENTX=QString::number(chassis.actstatus.x);
        str_CURRENTY=QString::number(chassis.actstatus.y);
        str_CURRENTS=QString::number(chassis.actstatus.sita);

        //str_DESTX=QString::number(chassis_obj_status.x);
        //str_DESTY=QString::number(chassis_obj_status.y);
        //str_DESTS=QString::number(chassis_obj_status.sita);

        str_TRACKX=QString::number(chassis.objstatus.x);
        str_TRACKY=QString::number(chassis.objstatus.y);
        str_TRACKS=QString::number(chassis.objstatus.sita);
        */

        usleep(500000);
        //sleep(2);
    }
}





