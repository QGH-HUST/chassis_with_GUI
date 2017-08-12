#ifndef MYTYPEDEF_H
#define MYTYPEDEF_H

#include <iostream>
//using namespace std;
//自定义数据类型
//底盘状态信息结构
#define PI  3.1415          //圆周率

#define SMDT  0.005         //伺服电机速度规划时间间隔，s
#define CPDT  5           //底盘路径规划点采样间隔，单位ms
#define BCDU 0.05 //底盘路径规划点u采样间隔


//#define uint8_t int
//#define uint16_t int
//#define uint32_t long


struct  POINT_chassis
{
    float x ;       //底盘x方向坐标
    float y ;       //底盘y方向坐标
    float sita;     //底盘姿态角
    float v_x ;     //底盘x方向速度分量
    float v_y ;     //底盘y方向速度量
    float w;        //底盘自转速度
    float a_x ;     //底盘x方向加速度分量
    float a_y ;     //底盘y方向加速度分量
    float a_s;      //底盘自转加速度
    float r;        //底盘运动曲线曲率半径
};
//底盘Bezier曲线规划信息
struct  Bezier_chassis
{
    float x ;       //底盘x方向坐标
    float y ;       //底盘y方向坐标
    float c;        //底盘平动方向角
    float sita;     //底盘姿态角
    float r;        //底盘运动曲线曲率半径

};

struct POINT_3D
{
    float x ;
    float y ;
    float sita;
};

struct POINT_2D
{
    float x ;
    float y ;
};

//三段式速度规划参数结构
struct Chassis_speed_parameter
{
    float T ;//总时间
    float v_m;//中间段速度
    float T_1;//起始段用时
    float T_2;//中间段用时
    float T_3;//结束段段用时
    float A_1;//起始段最大加速度
    float A_3;//结束段最大加速度
};
typedef Chassis_speed_parameter Motor_speed_parameter;


#endif // MYTYPEDEF_H
