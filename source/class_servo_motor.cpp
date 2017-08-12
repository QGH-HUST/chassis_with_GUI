//#include "stdafx.h"
#include "class_servo_motor.h"
#include <cmath>
using   namespace   std;
/********************************/
//name:init();
//function:initial the parameter
//input:
//      mode:the initial mode of the motor running
//      position:the initial position where the motor shuold be when it starts.
//      velocity:the initial velocity where the motor shuold be when it starts.
//output:
/********************************/
void servo_motor::init(int mode , float position , float velocity ,
             float prov , float endv , float proa , float prod , float ra ,
             float s_a_max,float s_w_max)
{
    modop = mode;
    objposition = position;
    objvelocity = velocity;
    objprovel = prov;
    objendvel = endv;
    objproacc = proa;
    objprodec = prod;
    ratio = ra;
    S_A_MAX = s_a_max;
    S_W_MAX = s_w_max;
}

/********************************/
//name:getstatus();
//function:get the last motor state and datum of velocity and position,
//         then translate them into the real data,in the form of metric
//         system,which can be directly used later.
//input:
//output:
/********************************/
void servo_motor::getstatus()
{
    actposition = ( actpos / CSMP - OFFSET_SMP) / ratio;
    actvelocity = ( actvel / CSMV ) / ratio;
}

/********************************/
//name:float servo_motor_k_w(float Sita,float T,float w_s,float w_g)
//function:伺服电机梯形角速度规划函数中，起始段与结束段比例系数校准
//input:
//      float Sita:角度变化大小
//      float T:轨迹消耗时间
//      float w_s: 轨迹起始速度
//      float w_g: 轨迹结束速度
//output:
//      float k_w: -1：中间速度与初速相同
//                 -2：中间速度与末速相同
//                  0：中间速度与初速、末速相同
//                 >0：正常校准
/********************************/
float servo_motor::servo_motor_k_w(float Sita,float T,float w_s,float w_g)
{
    float T_1,T_2,T_3;//起始段/中间段、结束段所占时间
    float A_1,A_3;
    float w_m,k_w_m,k_w;

    // v_m与v_s,v_g不相等,T_1,T_3>0,T_2>=0,T_2<0
    T_2 = 0.0;
    k_w_m = KSWM;
    while (T_2<T)
    {
        T_1 = (T-T_2) * 1.0 /( k_w_m + 1 );
        T_3 = (T-T_2) * k_w_m/( k_w_m + 1 );
        w_m = (1.0/(T + T_2)) * ( 2 * Sita -T_1*w_s -T_3*w_g);
        A_1 = 1.0 * ((w_m - w_s)/T_1);
        A_3 = 1.0 * ((w_g - w_m)/T_3);
        //得到合适的中间速度
        if (abs(w_m) <= S_W_MAX )
        {
            if (abs(A_1)<= S_A_MAX && abs(A_3)<= S_A_MAX)
                break;
            else
                T = T + SMDT; //T 太小
        }
        else
        {
            if (abs(A_1)<= S_A_MAX && abs(A_3)<= S_A_MAX)
            T_2 = T_2 + SMDT;
            else T = T + SMDT; //T 太小
        }



    }
    /* //分段式
    if (w_m == w_s && w_m == w_g)
        k_w = 0; //中间速度与初速、末速相同
    else if (w_m == w_s )
        k_w = -1; //中间速度与初速相同
    else if (w_m == w_g)
        k_w = -2;//中间速度与末速相同
    else
        k_w = k_w_m * abs((w_g - w_m) / (w_m - w_s));
    */
    if (w_m == w_s || w_m == w_g)
        k_w = k_w_m; //中间速度与初速、末速相同
    else
        k_w = k_w_m * abs((w_g - w_m) / (w_m - w_s));
    return k_w;
}

/********************************/
//name:Motor_speed_parameter servo_motor_parameter(float Sita,float T,float w_s,float w_g,float k_w)
//function:伺服电机梯形角速度规划函数
//input:
//      float Sita:角度变化大小
//      float T:轨迹消耗时间
//      float w_s: 轨迹起始速度
//      float w_g: 轨迹结束速度
//      float k_w: 起始段与结束段响应快慢因子
//output:
//      Motor_speed_parameter：三段式速度规划参数
//          MSP.T   :总时间
//          MSP.v_m :中间段速度
//          MSP.T_1 :起始段用时
//          MSP.T_2 :中间段用时
//          MSP.T_3 :结束段段用时
//          MSP.A_1 :起始段加速度
//          MSP.A_3 :结束段加速度
/********************************/
Motor_speed_parameter servo_motor::servo_motor_parameter(float Sita,float T,float w_s,float w_g,float k_w)
{
    float T_1,T_2,T_3;//起始段/中间段、结束段所占时间
    float A_1,A_3;
    float w_m;
    Motor_speed_parameter MSP;
    // v_m与v_s,v_g不相等,T_1,T_3>0,T_2>=0,T_2<0
    T_2 = 0.0;
    while (T_2<T)
    {
        T_1 = (T-T_2) * 1.0 /( k_w + 1 );
        T_3 = (T-T_2) * k_w/( k_w + 1 );
        w_m = (1.0/(T + T_2)) * ( 2 * Sita -T_1*w_s -T_3*w_g);
        A_1 = 1.0 * ((w_m - w_s)/T_1);
        A_3 = 1.0 * ((w_g - w_m)/T_3);
        //得到合适的中间速度
        if (abs(w_m) <= S_W_MAX )
        {
            if (abs(A_1)<= S_A_MAX && abs(A_3)<= S_A_MAX)
                break;
            else
                T = T + SMDT; //T 太小
        }
        else
        {
            if (abs(A_1)<= S_A_MAX && abs(A_3)<= S_A_MAX)
            T_2 = T_2 + SMDT;
            else T = T + SMDT; //T 太小
        }
    }

    MSP.T   = T ;
    MSP.v_m = w_m;
    MSP.T_1 = T_1;
    MSP.T_2 = T_2;
    MSP.T_3 = T_3;
    MSP.A_1 = A_1;
    MSP.A_3 = A_3;
    return MSP;
}

/********************************/
//name:setstatus();
//function:set the last motor state and datum of velocity and position,
//         then translate them into the parameter,in the form of motor
//         system,which can be directly used later.
//input:
//output:
/********************************/
void servo_motor::setstatus(int md)
{
    float k_w;
    Motor_speed_parameter MSP;
    modop = md;
    getstatus();
    switch(modop)
    {
        case motor_IDLE:
            objposition = actposition;
            objvelocity = actvelocity;
        break;
        case motor_POS:
            k_w = servo_motor_k_w((objposition-actposition),CPDT,actvelocity,objvelocity);
            MSP = servo_motor_parameter((objposition-actposition),CPDT,actvelocity,objvelocity,k_w);
            objprovel = MSP.v_m;
            objendvel = objvelocity;
            objproacc = MSP.A_1;
            objprodec = MSP.A_3;   
        break;
        case motor_VEL:
        tarvel = (int)objvelocity * CSMV * ratio;
        break;
    }
    int var_pos = (int)( objposition * ratio + OFFSET_SMP ) * CSMP;
    if(var_pos>2147000000) var_pos = 2147000000;
    else if(var_pos<100000) var_pos = 100000;
    tarpos = var_pos;
    provel = abs((int)(objprovel * CSMV * ratio));
    endvel = abs((int)(objendvel * CSMV * ratio));
    proacc = abs((int)(objproacc * CSMV * ratio));
    prodec = abs((int)(objprodec * CSMV * ratio));

    provel = 5000;
    endvel = 0;
    proacc = 50000;
    prodec = 50000;
}
