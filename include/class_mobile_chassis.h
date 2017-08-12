#ifndef CLASS_MOBILE_CHASSIS_H
#define CLASS_MOBILE_CHASSIS_H

#include "class_servo_motor.h"
#include "PID.h"
#include "MyTypedef.h"

//底盘类宏定义
#define MCW 1.0 //the width of mobile chassis:m
#define MCL 3.0 //the length of mobile chassis:m
#define MCWR 0.18 //the radius of the wheel of mobile chassis:m
#define CIDLE 0//chassis move mode 空闲状态
#define COPEN 1//chassis move mode 位置开环模式
#define CPOS 2//chassis move mode 位置环模式
#define CVEL 3//chassis move mode 速度环加位置环



//static mobile_chassis chassis;

class mobile_chassis
{
    public:
    servo_motor motorFL;
    servo_motor motorFR;
    servo_motor motorBL;
    servo_motor motorBR;

    POINT_chassis actstatus;
    POINT_chassis objstatus;

    int mode; //chassis move mode

    PID pid_x,pid_y,pid_sita;
    PID pid_v_x,pid_v_y,pid_w;

    //functions
    //void mobile_chassis();
    void init(int md, POINT_chassis status);
    void getstatus();
    void setstatus();
    //void kinetic_compute();
    //void dynamic_compute();
    void positionctrl();
    void velocityctrl();
    void movectrl();
};

#endif // CLASS_MOBILE_CHASSIS_H
