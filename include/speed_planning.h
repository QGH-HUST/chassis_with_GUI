#ifndef SPEED_PLANNING_H
#define SPEED_PLANNING_H

#include "MyTypedef.h"
#include "class_mobile_chassis.h"
#include "Bezier.h"
//速度规划函数

#define DT  0.05            //底盘速度规划时间间隔，s
#define A_MAX  3.0*1000     //底盘平动最大加速度，mm/s~2
#define A_S_MAX  PI/5       //底盘旋转最大旋转加速度，rad/s~2
#define V_MAX  500.0        //底盘平动最大线速度，mm/s
#define V_MIN  0            //底盘平动最小线速度
#define W_MAX  PI/5         //底盘旋转最大自转速度，rad/s
#define W_MIN  -PI/5        //底盘旋转最小自转速度
#define KVM  1.1            //底盘平动起始段与结束段平动速度响应快慢因子
#define KWM  1.1;           //底盘旋转起始段与结束段自转速度响应快慢因子

//底盘路径规划宏定义
#define CPMIN 50.0  //底盘路径规划下限,单位mm
#define CPMAX 3000.0 //底盘路径规划上线，单位mm
//#define CPDT 0.005 //底盘路径规划点采样间隔，单位ms

//路径规划变量定义
extern POINT_3D obs_0; //障碍物坐标
extern POINT_3D obs_1; //障碍物坐标
extern POINT_chassis  CPP[5000];//路径规划点信息数组
extern int CPP_num;//规划得到点数量
extern int aim_num;//底盘当前跟踪点，虚拟目标点
//导航变量
extern float  NGPara1;
extern float  NGPara2;

extern mobile_chassis chassis;



float chassis_speed_k_v(float S, float T, float v_s, float v_g);
Chassis_speed_parameter chassis_speed_parameter(float S, float T, float v_s, float v_g, float k_v);

float chassis_rotate_k_w(float Sita, float T, float w_s, float w_g);
Chassis_speed_parameter chassis_rotate_parameter(float Sita, float T, float w_s, float w_g, float k_w);

int chassis_planning(POINT_chassis c_s, POINT_chassis c_g, int obs_num, float T);
int chassis_tracking();

#endif // SPEED_PLANNING_H
