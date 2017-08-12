//class of mobile chassis
//#include "stdafx.h"
#include "class_mobile_chassis.h"
//#include <PID.h>
//#include <MyTypedef.h>

/********************************/
//name:init();
//function:initial the parameter
//input:
//      int md:底盘初始化工作模式
//      POINT_chassis status：底盘初始化目标状态信息
//output:
//
/********************************/
void mobile_chassis::init(int md , POINT_chassis status )
{
    mode = md;
    objstatus = status;
    motorFL.init(motor_IDLE , 20*PI , 0.0 ,
             PI/4 , 0 , PI/4 , PI/4 , 1.0 ,
             PI/2,PI/2);
    motorFR.init(motor_IDLE , 20*PI , 0.0 ,
             PI/4 , 0 , PI/4 , PI/4 , 1.0 ,
             PI/2,PI/2);
    motorBL.init(motor_IDLE , 20*PI , 0.0 ,
             PI/4 , 0 , PI/4 , PI/4 , 1.0 ,
             PI/2,PI/2);
    motorBR.init(motor_IDLE , 20*PI , 0.0 ,
             PI/4 , 0 , PI/4 , PI/4 , 1.0 ,
             PI/2,PI/2);

    motorFR.setstatus(motor_POS);
    motorFL.setstatus(motor_POS);
    motorBR.setstatus(motor_POS);
    motorBL.setstatus(motor_POS);
}

/********************************/
//name:getstatus();
//function:获取底盘各电机当前状态信息，并转换成底盘的当前状态信息
//input:
//output:
/********************************/
void mobile_chassis::getstatus()
{
    motorFR.getstatus();
    motorFL.getstatus();
    motorBR.getstatus();
    motorBL.getstatus();
    //presume that the datium are accurate.
    actstatus.x = ( motorFR.actposition - motorFL.actposition - motorBR.actposition + motorBL.actposition ) * MCWR / 4.0;
    actstatus.y = ( motorFR.actposition + motorFL.actposition + motorBR.actposition + motorBL.actposition ) * MCWR / 4.0;
    actstatus.v_x = ( motorFR.actvelocity - motorFL.actvelocity - motorBR.actvelocity + motorBL.actvelocity ) * MCWR / 4.0;
    actstatus.v_y = ( motorFR.actvelocity + motorFL.actvelocity + motorBR.actvelocity + motorBL.actvelocity ) * MCWR / 4.0;
}

/********************************/
//name:setstatus();
//function:将底盘的目标状态信息转换成各电机的状态信息
//input:
//output:
/********************************/
void mobile_chassis::setstatus()
{
    int motor_mode;
    switch(mode)
    {
    case CIDLE:
        {

            motor_mode = motor_IDLE;///缺少电机设置
            break;
        }
        case CVEL:
        {
            //accelerate
            motorFR.objaccelerate = (  1 * objstatus.a_x + 1 * objstatus.a_y - ( MCL - MCW ) * 0.5 * objstatus.a_s ) / MCWR;
            motorFL.objaccelerate = ( -1 * objstatus.a_x + 1 * objstatus.a_y + ( MCL - MCW ) * 0.5 * objstatus.a_s ) / MCWR;
            motorBR.objaccelerate = ( -1 * objstatus.a_x + 1 * objstatus.a_y - ( MCL - MCW ) * 0.5 * objstatus.a_s ) / MCWR;
            motorBL.objaccelerate = (  1 * objstatus.a_x + 1 * objstatus.a_y + ( MCL - MCW ) * 0.5 * objstatus.a_s ) / MCWR;
            //velocity
            motorFR.objvelocity = (  1 * objstatus.v_x + 1 * objstatus.v_y - ( MCL - MCW ) * 0.5 * objstatus.w ) / MCWR;
            motorFL.objvelocity = ( -1 * objstatus.v_x + 1 * objstatus.v_y + ( MCL - MCW ) * 0.5 * objstatus.w ) / MCWR;
            motorBR.objvelocity = ( -1 * objstatus.v_x + 1 * objstatus.v_y - ( MCL - MCW ) * 0.5 * objstatus.w ) / MCWR;
            motorBL.objvelocity = (  1 * objstatus.v_x + 1 * objstatus.v_y + ( MCL - MCW ) * 0.5 * objstatus.w ) / MCWR;

            motor_mode = motor_VEL;
            break;
        }
        case CPOS:
        {
            //velocity
            motorFR.objvelocity = (  1 * objstatus.v_x + 1 * objstatus.v_y - ( MCL - MCW ) * 0.5 * objstatus.w ) / MCWR;
            motorFL.objvelocity = ( -1 * objstatus.v_x + 1 * objstatus.v_y + ( MCL - MCW ) * 0.5 * objstatus.w ) / MCWR;
            motorBR.objvelocity = ( -1 * objstatus.v_x + 1 * objstatus.v_y - ( MCL - MCW ) * 0.5 * objstatus.w ) / MCWR;
            motorBL.objvelocity = (  1 * objstatus.v_x + 1 * objstatus.v_y + ( MCL - MCW ) * 0.5 * objstatus.w ) / MCWR;
        }
        case COPEN:
        {
            //position
            motorFR.objposition = (  1 * objstatus.x + 1 * objstatus.y - ( MCL - MCW ) * 0.5 * objstatus.sita ) / MCWR;
            motorFL.objposition = ( -1 * objstatus.x + 1 * objstatus.y + ( MCL - MCW ) * 0.5 * objstatus.sita ) / MCWR;
            motorBR.objposition = ( -1 * objstatus.x + 1 * objstatus.y - ( MCL - MCW ) * 0.5 * objstatus.sita ) / MCWR;
            motorBL.objposition = (  1 * objstatus.x + 1 * objstatus.y + ( MCL - MCW ) * 0.5 * objstatus.sita ) / MCWR;
            motor_mode = motor_POS;
            break;
        }
        default :
        {
            mode = CIDLE;
            motor_mode = motor_IDLE;
            //
        }
    }
    motorFR.setstatus(motor_mode);
    motorFL.setstatus(motor_mode);
    motorBR.setstatus(motor_mode);
    motorBL.setstatus(motor_mode);

}

/********************************/
//name:positionctrl();
//function:get the actual parameter and the target,then compute the new
//         parameter of the motor,and set them to the motor.
//input:
//output:
/********************************/
void mobile_chassis::positionctrl()
{
    objstatus.w  = pid_sita.PID_Regulator(objstatus.sita,actstatus.sita);
    objstatus.v_x = pid_x.PID_Regulator(objstatus.x,actstatus.x);
    objstatus.v_y = pid_y.PID_Regulator(objstatus.y,actstatus.y);
}

/********************************/
//name:velocityctrl();
//function:get the actual parameter and the target,then compute the new
//         parameter of the motor,and set them to the motor.
//input:
//output:
/********************************/
void mobile_chassis::velocityctrl()
{
    objstatus.a_s  = pid_w.PID_Regulator(objstatus.w,actstatus.w);
    objstatus.a_x = pid_v_x.PID_Regulator(objstatus.v_x,actstatus.v_x);
    objstatus.a_y = pid_v_y.PID_Regulator(objstatus.v_y,actstatus.v_y);
}

/********************************/
//name:movectrl();
//function:get the actual parameter and the target,then compute the new
//         parameter of the motor,and set them to the motor.
//input:
//output:
/********************************/
void mobile_chassis::movectrl()
{
    getstatus();
    switch(mode)
    {
        //compute the parameter for the position mode with the actual
        //and objective position and velocity
        //dynamic? kinetic?
        case CVEL:
        {
            velocityctrl();
            break;
        }

        case CPOS:
        {
            positionctrl();
            break;
        }
    }
    setstatus();
}

