//#include "stdafx.h"
#include "Bezier.h"
#include <math.h>

/********************************/
//name:Bezier_chassis Bezier0(POINT_chassis c_s,POINT_chassis c_g,float u);
//function:无障碍物条件下底盘起点到终点的贝塞尔曲线路径规划
//input:
//      POINT_chassis c_s:底盘运动贝塞尔规划曲线起点信息
//      POINT_chassis c_g:底盘运动贝塞尔规划曲线终点信息
//      float u: 贝塞尔曲线变量因子
//output:
//      Bezier_chassis b:变量因子u对应的贝塞尔曲线上的底盘规划信息
/********************************/
Bezier_chassis Bezier0(POINT_chassis c_s, POINT_chassis c_g, float u)
{
    float x_2, x_3, y_2, y_3, sita_2, sita_3;
    float x, y;
    float dx, dy;
    float ddx, ddy;
    Bezier_chassis b;
    x_2 = c_s.x + LAME_x_s * c_s.v_x;
    x_3 = c_g.x + LAME_x_g * c_g.v_x;
    x = 1.0 * c_s.x * ((1 - u)*(1 - u)*(1 - u))
        + 3.0 * x_2 * u * ((1 - u)*(1 - u))
        + 3.0 * x_3 * u * u * (1 - u)
        + 1.0 * c_g.x * u * u * u;
    dx = -3.0 * c_s.x * ((1 - u)*(1 - u))
        + 3.0 * x_2 * ((1 - u)*(1 - 3.0*u))
        + 3.0 * x_3 * u * (2.0 - 3.0*u)
        + 3.0 * c_g.x * u * u;
    ddx = 6.0 * c_s.x * (1 - u)
        - 6.0 * x_2 * (2.0 - 3.0*u)
        + 6.0 * x_3 * (1 - 3.0*u)
        + 6.0 * c_g.x * u;

    y_2 = c_s.y + LAME_y_s * c_s.v_y;
    y_3 = c_g.y + LAME_y_g * c_g.v_y;
    y = 1.0 * c_s.y * ((1 - u)*(1 - u)*(1 - u))
        + 3.0 * y_2 * u * ((1 - u)*(1 - u))
        + 3.0 * y_3 * u * u * (1 - u)
        + 1.0 * c_g.y * u * u * u;
    dy = -3.0 * c_s.y * ((1 - u)*(1 - u))
        + 3.0 * y_2 * ((1 - u)*(1 - 3.0*u))
        + 3.0 * y_3 * u * (2.0 - 3.0*u)
        + 3.0 * c_g.y * u * u;
    ddy = 6.0 * c_s.y * (1 - u)
        - 6.0 * y_2 * (2.0 - 3.0*u)
        + 6.0 * y_3 * (1 - 3.0*u)
        + 6.0 * c_g.y * u;
    b.x = x;
    b.y = y;
    b.c = atan2(dy, dx);
    b.r = 1.0*sqrt((dx*dx + dy*dy)*(dx*dx + dy*dy)*(dx*dx + dy*dy)) / (ddy*dx - dy*ddx);
    if (b.r>MAXR)
        b.r = MAXR;
    else if (b.r<-MAXR)
        b.r = -MAXR;
    return b;
}

/********************************/
//name:POINT_chassis Bezier1(POINT_chassis c_s,POINT_chassis c_g,float u,POINT_3D obs_1);
//function:1个障碍物点条件下底盘起点到终点的贝塞尔曲线路径规划
//input:
//      POINT_chassis c_s:底盘运动贝塞尔规划曲线起点信息
//      POINT_chassis c_g:底盘运动贝塞尔规划曲线终点信息
//      float u: 贝塞尔曲线变量因子
//      POINT_3D obs:底盘运动需要避开的障碍物信息
//output:
//      POINT_chassis b:变量因子u对应的贝塞尔曲线上的底盘规划信息
/********************************/
Bezier_chassis Bezier1(POINT_chassis c_s, POINT_chassis c_g, float u, POINT_3D obs)
{
    float x_2, x_3, y_2, y_3, sita_2, sita_3;
    float x_4, y_4, sita_4;
    Bezier_chassis b;
    x_2 = c_s.x + LAME_x_s * c_s.v_x;
    x_3 = c_g.x + LAME_x_g * c_g.v_x;
    x_4 = obs.x;
    b.x = 1.0 * c_s.x * ((1 - u)*(1 - u)*(1 - u)*(1 - u))
        + 4.0 * x_2 * u * ((1 - u)*(1 - u)*(1 - u))
        + 6.0 * x_4 * u * u * ((1 - u)*(1 - u))
        + 4.0 * x_3 * u * u * u * (1 - u)
        + 1.0 * c_g.x * u * u * u * u;
    y_2 = c_s.y + LAME_y_s * c_s.v_y;
    y_3 = c_g.y + LAME_y_g * c_g.v_y;
    y_4 = obs.y;
    b.y = 1.0 * c_s.y * ((1 - u)*(1 - u)*(1 - u)*(1 - u))
        + 4.0 * y_2 * u * ((1 - u)*(1 - u)*(1 - u))
        + 6.0 * y_4 * u * u * ((1 - u)*(1 - u))
        + 4.0 * y_3 * u * u * u * (1 - u)
        + 1.0 * c_g.y * u * u * u * u;
    sita_2 = c_s.sita + LAME_w_s * c_s.w;
    sita_3 = c_g.sita + LAME_w_g * c_g.w;
    sita_4 = obs.sita;
    b.sita = 1.0 *c_s.sita * ((1 - u)*(1 - u)*(1 - u)*(1 - u))
        + 4.0 * sita_2 * u * ((1 - u)*(1 - u)*(1 - u))
        + 6.0 * sita_4 * u * u * ((1 - u)*(1 - u))
        + 4.0 * sita_3 * u * u * u * (1 - u)
        + 1.0 * c_g.sita * u * u * u * u;

    return b;
}

/********************************/
//name:POINT_chassis Bezier2(POINT_chassis c_s,POINT_chassis c_g,float u,POINT_3D obs_1,POINT_3D obs_2);
//function:2个障碍物点条件下底盘起点到终点的贝塞尔曲线路径规划
//input:
//      POINT_chassis c_s:底盘运动贝塞尔规划曲线起点信息
//      POINT_chassis c_g:底盘运动贝塞尔规划曲线终点信息
//      float u: 贝塞尔曲线变量因子
//      POINT_3D obs_1:底盘运动需要避开的第1个障碍物信息
//      POINT_3D obs_2:底盘运动需要避开的第2个障碍物信息
//output:
//      POINT_chassis b:变量因子u对应的贝塞尔曲线上的底盘规划信息
/********************************/
Bezier_chassis Bezier2(POINT_chassis c_s, POINT_chassis c_g, float u, POINT_3D obs_1, POINT_3D obs_2)
{
    float x_2, x_3, y_2, y_3, sita_2, sita_3;
    float x_4, y_4, sita_4;
    float x_5, y_5, sita_5;
    Bezier_chassis b;
    x_2 = c_s.x + LAME_x_s * c_s.v_x;
    x_3 = c_g.x + LAME_x_g * c_g.v_x;
    x_4 = obs_1.x;
    x_5 = obs_2.x;
    b.x = 1.0 * c_s.x * ((1 - u)*(1 - u)*(1 - u)*(1 - u)*(1 - u))
        + 5.0 * x_2 * u * ((1 - u)*(1 - u)*(1 - u)*(1 - u))
        + 10.0 * x_4 * u * u * ((1 - u)*(1 - u)*(1 - u))
        + 10.0 * x_4 * u * u * u * ((1 - u)*(1 - u))
        + 5.0 * x_3 * u * u * u * u * (1 - u)
        + 1.0 * c_g.x * u * u * u * u * u;
    y_2 = c_s.y + LAME_y_s * c_s.v_y;
    y_3 = c_g.y + LAME_y_g * c_g.v_y;
    y_4 = obs_1.y;
    y_5 = obs_2.y;
    b.y = 1.0 * c_s.y * ((1 - u)*(1 - u)*(1 - u)*(1 - u)*(1 - u))
        + 5.0 * y_2 * u * ((1 - u)*(1 - u)*(1 - u)*(1 - u))
        + 10.0 * y_4 * u * u * ((1 - u)*(1 - u)*(1 - u))
        + 10.0 * y_4 * u * u * u * ((1 - u)*(1 - u))
        + 5.0 * y_3 * u * u * u * u * (1 - u)
        + 1.0 * c_g.y * u * u * u * u * u;
    sita_2 = c_s.sita + LAME_w_s * c_s.w;
    sita_3 = c_g.sita + LAME_w_g * c_g.w;
    sita_4 = obs_1.sita;
    sita_5 = obs_2.sita;
    b.sita = 1.0 * c_s.sita * ((1 - u)*(1 - u)*(1 - u)*(1 - u)*(1 - u))
        + 5.0 * sita_2 * u * ((1 - u)*(1 - u)*(1 - u)*(1 - u))
        + 10.0 * sita_4 * u * u * ((1 - u)*(1 - u)*(1 - u))
        + 10.0 * sita_4 * u * u * u * ((1 - u)*(1 - u))
        + 5.0 * sita_3 * u * u * u * u * (1 - u)
        + 1.0 * c_g.sita * u * u * u * u * u;

    return b;
}
