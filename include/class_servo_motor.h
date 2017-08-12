#ifndef CLASS_SERVO_MOTOR_H
#define CLASS_SERVO_MOTOR_H

#define CSMP 131072 //coeffient_servo_motor_position:17 bits encoder P/R
#define OFFSET_SMP 0 //OFFSET_servo_motor_position偏置
#define CSMV 1 //coeffient_servo_motor_velocity:rpm
//the running mode of the motor
#define motor_IDLE 0
#define motor_POS 1
#define motor_VEL 3

#define KSWM  1.1           //伺服电机起始段与结束段自转速度响应快慢因子

//#define S_A_MAX  PI/5;     //伺服电机最大加速度
//#define S_W_MAX  PI/5;     //伺服电机最大速度

#include "MyTypedef.h"
//#include <unistd.h>
//#include <cstdint>

class servo_motor
{
    public:
    // offsets for PDO entries
    int off_ctrlwd;        //control word   0x6040
    int off_statwd;        //state word 0x6041
    int off_modop;         //mode of operation 0x6060
    int off_modds;         //mode of operation dispaly 0x6061
    int off_tarvel;        //target velocity 0x60ff
    int off_actvel;        //actual velocity 0x606c
    int off_tarpos;        //target position 0x607a
    int off_actpos;        //actual position 0x6064
    int off_provel;        //profile velocity 0x6081
    int off_endvel;        //end velocity 0x6082
    int off_proacc;        //profile acceleration 0x6083
    int off_prodec;        //profile deceleration 0x6084
    //parameter of estun control
    unsigned short int ctrlwd;
    unsigned short int statwd;
    signed char modop;
    signed char modds;
    int tarvel;
    int actvel;
    int tarpos;
    int actpos;
    unsigned int provel;
    unsigned int endvel;
    unsigned int proacc;
    unsigned int prodec;

    //real datum
    float actposition; //angle
    float actvelocity; //rmp
    float objposition;
    float objvelocity;
    float objaccelerate;
    float objprovel; //rpm
    float objendvel; //rpm
    float objproacc; //rpm/s
    float objprodec; //rpm/s
    float ratio; //mechanical reduction ratio
    //速度规划参数
    float S_A_MAX;       //伺服电机最大加速度
    float S_W_MAX;       //伺服电机最大速度

    //functions
    //void servo_motor();
    void init(int mode , float position , float velocity ,
             float prov , float endv , float proa , float prod , float ra ,
             float s_a_max,float s_w_max);
    void getstatus();
    float servo_motor_k_w(float Sita,float T,float w_s,float w_g);
    Motor_speed_parameter servo_motor_parameter(float Sita,float T,float w_s,float w_g,float k_w);
    void setstatus(int md);
};

#endif // CLASS_SERVO_MOTOR_H
