#ifndef BEZIER_H
#define BEZIER_H

#define LAME_x_s 1.0 //起点x方向速度影响系数
#define LAME_y_s 1.0 //起点y方向速度影响系数
#define LAME_w_s 1.0 //起点自转速度影响系数
#define LAME_x_g 1.0 //终点x方向速度影响系数
#define LAME_y_g 1.0 //终点y方向速度影响系数
#define LAME_w_g 1.0 //终点自转速度影响系数
#define MAXR 1000 //曲率最大限制

#include "MyTypedef.h"

Bezier_chassis Bezier0(POINT_chassis c_s, POINT_chassis c_g, float u);

Bezier_chassis Bezier1(POINT_chassis c_s, POINT_chassis c_g, float u, POINT_3D obs);

Bezier_chassis Bezier2(POINT_chassis c_s, POINT_chassis c_g, float u, POINT_3D obs_1, POINT_3D obs_2);


#endif // BEZIER_H
