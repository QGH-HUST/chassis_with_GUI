//#include "stdafx.h"
#include "speed_planning.h"
#include <cmath>
using   namespace   std;

POINT_3D obs_0 = { 0, 0, 0 }; //障碍物坐标
POINT_3D obs_1 = { 0, 0, 0 }; //障碍物坐标
mobile_chassis chassis;
POINT_chassis  CPP[5000];//路径规划点信息数组
float  NGPara1 = 0.00006F;
float  NGPara2 = 3;
int CPP_num = 10;//规划得到点数量
int aim_num = 0;//底盘当前跟踪点，虚拟目标点
/********************************/
//name:float chassis_speed_k_v(float S,float T,float v_s,float v_g)
//function:三段式速度规划函数中，起始段与结束段比例系数校准
//input:
//      float S:轨迹长度
//      float T:轨迹消耗时间
//      float v_s: 轨迹起始速度
//      float v_g: 轨迹结束速度
//output:
//      float k_v: -1：中间速度与初速相同
//                 -2：中间速度与末速相同
//                  0：中间速度与初速、末速相同
//                 >0：正常校准
/********************************/
float chassis_speed_k_v(float S,float T,float v_s,float v_g)
{
    float T_1,T_2,T_3;//起始段/中间段、结束段所占时间
    float A_1,A_3;
    float v_m,k_v_m,k_v;

    // v_m与v_s,v_g不相等,T_1,T_3>0,T_2>=0,T_2<0
    T_2 = 0.0;
    k_v_m = KVM;
    while (T_2<T)
    {
        T_1 = (T-T_2) * 1.0 /( k_v_m + 1 );
        T_3 = (T-T_2) * k_v_m/( k_v_m + 1 );
        v_m = (1.0/(T + T_2)) * ( 2 * S -T_1*v_s -T_3*v_g);
        A_1 = (PI / 2) * ((v_m - v_s)/T_1);
        A_3 = (PI / 2) * ((v_g - v_m)/T_3);
        //得到合适的中间速度
        if (v_m <= V_MAX && v_m >= V_MIN)
        {
            if (abs(A_1)<= A_MAX && abs(A_3)<= A_MAX)
                break;
            else
                T = T + DT; //T 太小
        }
        if (v_m > V_MAX)
        {
            if (abs(A_1)<= A_MAX && abs(A_3)<= A_MAX)
            T_2 = T_2 + DT;
            else T = T + DT; //T 太小
        }
        // else if (v_m < V_MIN)
        // {
        //     S = S + DS; //S 太小
        // }


    }
    /* //分段式
    if (v_m == v_s && v_m == v_g)
        k_v = 0; //中间速度与初速、末速相同
    else if (v_m == v_s )
        k_v = -1; //中间速度与初速相同
    else if (v_m == v_g)
        k_v = -2;//中间速度与末速相同
    else
        k_v = k_v_m * abs((v_g - v_m) / (v_m - v_s));
    */
    if (v_m == v_s || v_m == v_g)
        k_v = k_v_m; //中间速度与初速、末速相同
    else
        k_v = k_v_m * abs((v_g - v_m) / (v_m - v_s));
    return k_v;
}

/********************************/
//name:Chassis_speed_parameter chassis_speed_parameter(float S,float T,float v_s,float v_g,float k_v)
//function:三段式速度规划参数计算
//input:
//      float S:轨迹长度
//      float T:轨迹消耗时间
//      float v_s: 轨迹起始速度
//      float v_g: 轨迹结束速度
//      float k_v: 起始段与结束段响应快慢因子
//output:
//      Chassis_speed_parameter：三段式速度规划参数
//          CSP.T   :总时间
//          CSP.v_m :中间段速度
//          CSP.T_1 :起始段用时
//          CSP.T_2 :中间段用时
//          CSP.T_3 :结束段段用时
//          CSP.A_1 :起始段最大加速度
//          CSP.A_3 :结束段最大加速度
/********************************/
Chassis_speed_parameter chassis_speed_parameter(float S,float T,float v_s,float v_g,float k_v)
{
    float T_1,T_2,T_3;//起始段/中间段、结束段所占时间
    float A_1,A_3;
    float v_m;
    Chassis_speed_parameter CSP;
    // v_m与v_s,v_g不相等,T_1,T_3>0,T_2>=0,T_2<0
    T_2 = 0.0;
    if(k_v >0) //正常三段式规划
    {
        while (T_2<T)
        {
            T_1 = (T-T_2) * 1.0 /( k_v + 1 );
            T_3 = (T-T_2) * k_v/( k_v + 1 );
            v_m = (1.0/(T + T_2)) * ( 2 * S -T_1*v_s -T_3*v_g);
            A_1 = (PI / 2) * ((v_m - v_s)/T_1);
            A_3 = (PI / 2) * ((v_g - v_m)/T_3);
            //得到合适的中间速度
            if (v_m <= V_MAX && v_m >= V_MIN)
            {
                if (abs(A_1)<= A_MAX && abs(A_3)<= A_MAX)
                    break;
                else
                    T = T + DT; //T 太小
            }
            if (v_m > V_MAX)
            {
                if (abs(A_1)<= A_MAX && abs(A_3)<= A_MAX)
                T_2 = T_2 + DT;
                else T = T + DT; //T 太小
            }
            //  else if (v_m < V_MIN)
            //  {
            //      S = S + DS; //S 太小
            //  }
        }
    }
    else if(k_v == 0 ) //一段式规划，无起始段、结束段
    {
            T_1 = 0;
            T_2 = T;
            T_3 = 0;
            v_m = v_s;
            A_1 = 0;
            A_3 = 0;
    }
    else if(k_v == -1) //两段式规划，无起始段
    {
        while (T_2<T)
        {
            T_1 = 0;
            T_3 = (T-T_2);
            v_m = (1.0/(T + T_2)) * ( 2 * S -T_1*v_s -T_3*v_g);
            A_1 = 0;
            A_3 = (PI / 2) * ((v_g - v_m)/T_3);
            //得到合适的中间速度
            if (v_m <= V_MAX && v_m >= V_MIN)
            {
                if (abs(A_1)<= A_MAX && abs(A_3)<= A_MAX)
                    break;
                else
                    T = T + DT; //T 太小
            }
            if (v_m > V_MAX)
            {
                if (abs(A_1)<= A_MAX && abs(A_3)<= A_MAX)
                T_2 = T_2 + DT;
                else T = T + DT; //T 太小
            }
            //  else if (v_m < V_MIN)
            //  {
            //      S = S + DS; //S 太小
            //  }
        }
    }
    else if(k_v == -2) //两段式规划，无结束段
    {
        while (T_2<T)
        {
            T_1 = (T-T_2);
            T_3 = 0;
            v_m = (1.0/(T + T_2)) * ( 2 * S -T_1*v_s -T_3*v_g);
            A_1 = (PI / 2) * ((v_m - v_s)/T_1);
            A_3 = 0;
            //得到合适的中间速度
            if (v_m <= V_MAX && v_m >= V_MIN)
            {
                if (abs(A_1)<= A_MAX && abs(A_3)<= A_MAX)
                    break;
                else
                    T = T + DT; //T 太小
            }
            if (v_m > V_MAX)
            {
                if (abs(A_1)<= A_MAX && abs(A_3)<= A_MAX)
                T_2 = T_2 + DT;
                else T = T + DT; //T 太小
            }
            //  else if (v_m < V_MIN)
            //  {
            //      S = S + DS; //S 太小
            //  }
        }
    }
    CSP.T   = T ;
    CSP.v_m = v_m;
    CSP.T_1 = T_1;
    CSP.T_2 = T_2;
    CSP.T_3 = T_3;
    CSP.A_1 = A_1;
    CSP.A_3 = A_3;
    return CSP;
}

/********************************/
//name:float chassis_rotate_k_w(float Sita,float T,float w_s,float w_g)
//function:三段式角速度规划函数中，起始段与结束段比例系数校准
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
float chassis_rotate_k_w(float Sita,float T,float w_s,float w_g)
{
    float T_1,T_2,T_3;//起始段/中间段、结束段所占时间
    float A_1,A_3;
    float w_m,k_w_m,k_w;

    // v_m与v_s,v_g不相等,T_1,T_3>0,T_2>=0,T_2<0
    T_2 = 0.0;
    k_w_m = KWM;
    while (T_2<T)
    {
        T_1 = (T-T_2) * 1.0 /( k_w_m + 1 );
        T_3 = (T-T_2) * k_w_m/( k_w_m + 1 );
        w_m = (1.0/(T + T_2)) * ( 2 * Sita -T_1*w_s -T_3*w_g);
        A_1 = (PI / 2) * ((w_m - w_s)/T_1);
        A_3 = (PI / 2) * ((w_g - w_m)/T_3);
        //得到合适的中间速度
        if (w_m <= W_MAX && w_m >= W_MIN)
        {
            if (abs(A_1)<= A_S_MAX && abs(A_3)<= A_S_MAX)
                break;
            else
                T = T + DT; //T 太小
        }
        if (w_m > W_MAX)
        {
            if (abs(A_1)<= A_S_MAX && abs(A_3)<= A_S_MAX)
            T_2 = T_2 + DT;
            else T = T + DT; //T 太小
        }
        else if (w_m < W_MIN)
        {
            T = T + DT; //T 太小
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
//name:Chassis_speed_parameter chassis_rotate_parameter(float Sita,float T,float w_s,float w_g,float k_w)
//function:三段式速度规划参数计算
//input:
//      float Sita:轨迹长度
//      float T:轨迹消耗时间
//      float w_s: 轨迹起始速度
//      float w_g: 轨迹结束速度
//      float k_w: 起始段与结束段响应快慢因子
//output:
//      Chassis_speed_parameter：三段式速度规划参数
//          CSP.T   :总时间
//          CSP.v_m :中间段速度
//          CSP.T_1 :起始段用时
//          CSP.T_2 :中间段用时
//          CSP.T_3 :结束段段用时
//          CSP.A_1 :起始段最大加速度
//          CSP.A_3 :结束段最大加速度
/********************************/
Chassis_speed_parameter chassis_rotate_parameter(float Sita,float T,float w_s,float w_g,float k_w)
{
    float T_1,T_2,T_3;//起始段/中间段、结束段所占时间
    float A_1,A_3;
    float w_m;
    Chassis_speed_parameter CSP;
    // v_m与v_s,v_g不相等,T_1,T_3>0,T_2>=0,T_2<0
    T_2 = 0.0;
    if(k_w >0) //正常三段式规划
    {
        while (T_2<T)
        {
            T_1 = (T-T_2) * 1.0 /( k_w + 1 );
            T_3 = (T-T_2) * k_w/( k_w + 1 );
            w_m = (1.0/(T + T_2)) * ( 2 * Sita -T_1*w_s -T_3*w_g);
            A_1 = (PI / 2) * ((w_m - w_s)/T_1);
            A_3 = (PI / 2) * ((w_g - w_m)/T_3);
            //得到合适的中间速度
            if (w_m <= W_MAX && w_m >= W_MIN)
            {
                if (abs(A_1)<= A_S_MAX && abs(A_3)<= A_S_MAX)
                    break;
                else
                    T = T + DT; //T 太小
            }
            if (w_m > W_MAX)
            {
                if (abs(A_1)<= A_S_MAX && abs(A_3)<= A_S_MAX)
                T_2 = T_2 + DT;
                else T = T + DT; //T 太小
            }
            else if (w_m < W_MIN)
            {
                T = T + DT; //T 太小
            }
        }
    }
    else if(k_w == 0 ) //一段式规划，无起始段、结束段
    {
            T_1 = 0;
            T_2 = T;
            T_3 = 0;
            w_m = w_s;
            A_1 = 0;
            A_3 = 0;
    }
    else if(k_w == -1) //两段式规划，无起始段
    {
        while (T_2<T)
        {
            T_1 = 0;
            T_3 = (T-T_2);
            w_m = (1.0/(T + T_2)) * ( 2 * Sita -T_1*w_s -T_3*w_g);
            A_1 = 0;
            A_3 = (PI / 2) * ((w_g - w_m)/T_3);
            //得到合适的中间速度
            if (w_m <= W_MAX && w_m >= W_MIN)
            {
                if (abs(A_1)<= A_S_MAX && abs(A_3)<= A_S_MAX)
                    break;
                else
                    T = T + DT; //T 太小
            }
            if (w_m > W_MAX)
            {
                if (abs(A_1)<= A_S_MAX && abs(A_3)<= A_S_MAX)
                T_2 = T_2 + DT;
                else T = T + DT; //T 太小
            }
            else if (w_m < W_MIN)
            {
                T = T + DT; //T 太小
            }
        }
    }
    else if(k_w == -2) //两段式规划，无结束段
    {
        while (T_2<T)
        {
            T_1 = (T-T_2);
            T_3 = 0;
            w_m = (1.0/(T + T_2)) * ( 2 * Sita -T_1*w_s -T_3*w_g);
            A_1 = (PI / 2) * ((w_m - w_s)/T_1);
            A_3 = 0;
            //得到合适的中间速度
            if (w_m <= W_MAX && w_m >= W_MIN)
            {
                if (abs(A_1)<= A_S_MAX && abs(A_3)<= A_S_MAX)
                    break;
                else
                    T = T + DT; //T 太小
            }
            if (w_m > W_MAX)
            {
                if (abs(A_1)<= A_S_MAX && abs(A_3)<= A_S_MAX)
                T_2 = T_2 + DT;
                else T = T + DT; //T 太小
            }
            else if (w_m < W_MIN)
            {
                T = T + DT; //T 太小
            }
        }
    }
    CSP.T   = T ;
    CSP.v_m = w_m;
    CSP.T_1 = T_1;
    CSP.T_2 = T_2;
    CSP.T_3 = T_3;
    CSP.A_1 = A_1;
    CSP.A_3 = A_3;
    return CSP;
}


/********************************/
//name:int chassis_planning( POINT_chassis c_s,POINT_chassis c_g,int obs_num )
//function:根据起始点、目标点以及障碍物坐标进行路径规划,包含坐标点以及相应角度、速度、角速度、加速度、角加速度
//
//input:
//      POINT_chassis c_s：路径规划起点状态信息
//      POINT_chassis c_g：路径规划终点状态信息
//      int obs_num:障碍物数量
//      float T:起点到终点的运动时间
//output:
//      1:目标点太近，不需要规划
//      2:目标点太远，不适合规划
//      3:规划完成
//      CPP[]:路径规划点信息数组
//      CPP_num:路径规划点总数量
/********************************/
int chassis_planning(POINT_chassis c_s, POINT_chassis c_g, int obs_num, float T)
{
    //平动路径规划所需变量
    float ds, S;
    float u = 0;
    int num = 0;
    int BCP_num = 0;
    Bezier_chassis BCP[5000], BCP_t;//Bezier规划平动路径信息
    float BCP_S[5000];

    //平动速度规划所需变量
    //POINT_3D c_speed_t;
    Chassis_speed_parameter c_speed_p, c_rotate_p;
    float a_t, v_t, s_t;
    float a_s_t, w_t, sita_t;
    float k_v, k_w;
    float v_s, v_g;

    ds = sqrt((c_s.x - c_g.x) * (c_s.x - c_g.x) + (c_s.y - c_g.y) * (c_s.y - c_g.y));//计算起始点到目标点的直线距离

    if (ds < CPMIN)
        return 1; //目标点距离太近，不需要进行路径规划
    else if (ds > CPMAX)
        return 2; //目标距离太远，超出路径规划范围
    //以下进行正常的路径规划
    while (u <= 1.0)
    {
        switch (obs_num) //选择合适的贝塞尔函数
        {
        case 0:BCP[num] = Bezier0(c_s, c_g, u); break;
        case 1:BCP[num] = Bezier1(c_s, c_g, u, obs_0); break;
        case 2:BCP[num] = Bezier2(c_s, c_g, u, obs_0, obs_1); break;
        }
        u = u + BCDU;
        num++;
        if (u >= 1.0)
        {
            u = 1.0;
            switch (obs_num) //选择合适的贝塞尔函数
            {
            case 0:BCP[num] = Bezier0(c_s, c_g, u); break;
            case 1:BCP[num] = Bezier1(c_s, c_g, u, obs_0); break;
            case 2:BCP[num] = Bezier2(c_s, c_g, u, obs_0, obs_1); break;
            }
            BCP_num = num;
            break;
        }
    }
    //计算Bezier规划点在路径上对应点的距离起点的路径值
    BCP_S[0] = 0;
    for (int i = 0; i <= BCP_num - 1; i++)
    {
        ds = sqrt((BCP[i + 1].x - BCP[i].x)*(BCP[i + 1].x - BCP[i].x) + (BCP[i + 1].y - BCP[i].y)*(BCP[i + 1].y - BCP[i].y));
        BCP_S[i + 1] = BCP_S[i] + ds;
    }
    //平动速度规划
    S = BCP_S[BCP_num];
    s_t = 0;
    v_s = sqrt(c_s.v_x * c_s.v_x + c_s.v_y * c_s.v_y);
    v_g = sqrt(c_g.v_x * c_g.v_x + c_g.v_y * c_g.v_y);
    k_v = chassis_speed_k_v(S, T, v_s, v_g);
    c_speed_p = chassis_speed_parameter(S, T, v_s, v_g, k_v);
    k_w = chassis_rotate_k_w((c_g.sita - c_s.sita), c_speed_p.T, c_s.w, c_g.w);
    c_rotate_p = chassis_rotate_parameter((c_g.sita - c_s.sita), c_speed_p.T, c_s.w, c_g.w, k_w);
    //更新最新运动周期
    if ((c_rotate_p.T) > (c_speed_p.T))//自转时间不够
    {
        //以新的周期重新规划平动速度参数
        k_v = chassis_speed_k_v(S, c_rotate_p.T, v_s, v_g);
        c_speed_p = chassis_speed_parameter(S, c_rotate_p.T, v_s, v_g, k_v);
    }
    s_t = -v_s * CPDT;//距离超前
    num = 0;
    float t = 0;
    while (t <= c_speed_p.T)
    {
        //t时刻下平动速度计算
        if (t <= c_speed_p.T_1)             //T_1段
        {
            a_t = c_speed_p.A_1 * sin(PI / c_speed_p.T_1 * t);
            v_t = (c_speed_p.v_m + v_s) / 2 - (c_speed_p.v_m - v_s) / 2 * cos(PI / c_speed_p.T_1 * t);
            s_t = ((c_speed_p.v_m + v_s) / 2) * t - (c_speed_p.v_m - v_s) / 2 * (c_speed_p.T_1 / PI) * sin(PI / c_speed_p.T_1 * t);
        }
        else if (t <= c_speed_p.T_1 + c_speed_p.T_2)   //T_2段
        {
            a_t = 0;
            v_t = c_speed_p.v_m;
            s_t = c_speed_p.v_m * (t - c_speed_p.T_1)
                + ((c_speed_p.v_m + v_s) / 2) * c_speed_p.T_1;
        }
        else                      //T_3段
        {
            a_t = c_speed_p.A_3 * sin(PI / c_speed_p.T_3 * (t - c_speed_p.T_1 - c_speed_p.T_2));
            v_t = (c_speed_p.v_m + v_g) / 2 - (v_g - c_speed_p.v_m) / 2 * cos(PI / c_speed_p.T_3 * (t - c_speed_p.T_1 - c_speed_p.T_2));
            s_t = ((c_speed_p.v_m + v_g) / 2) * (t - c_speed_p.T_1 - c_speed_p.T_2)
                - (v_g - c_speed_p.v_m) / 2 * (c_speed_p.T_3 / PI) * sin(PI / c_speed_p.T_3 * (t - c_speed_p.T_1 - c_speed_p.T_2))
                + c_speed_p.v_m * c_speed_p.T_2
                + ((c_speed_p.v_m + v_s) / 2) * c_speed_p.T_1;
        }
        //t时刻下自转速度计算
        if (t <= c_rotate_p.T_1)             //T_1段
        {
            a_s_t = c_rotate_p.A_1 * sin(PI / c_rotate_p.T_1 * t);
            w_t = (c_rotate_p.v_m + c_s.w) / 2 - (c_rotate_p.v_m - c_s.w) / 2 * cos(PI / c_rotate_p.T_1 * t);
            sita_t = ((c_rotate_p.v_m + c_s.w) / 2) * t - (c_rotate_p.v_m - c_s.w) / 2 * (c_rotate_p.T_1 / PI) * sin(PI / c_rotate_p.T_1 * t);
        }
        else if (t <= c_rotate_p.T_1 + c_rotate_p.T_2)   //T_2段
        {
            a_s_t = 0;
            w_t = c_rotate_p.v_m;
            sita_t = c_rotate_p.v_m * (t - c_rotate_p.T_1)
                + ((c_rotate_p.v_m + c_s.w) / 2) * c_rotate_p.T_1;
        }
        else                      //T_3段
        {
            a_s_t = c_rotate_p.A_3 * sin(PI / c_rotate_p.T_3 * (t - c_rotate_p.T_1 - c_rotate_p.T_2));
            w_t = (c_rotate_p.v_m + c_g.w) / 2 - (c_g.w - c_rotate_p.v_m) / 2 * cos(PI / c_rotate_p.T_3 * (t - c_rotate_p.T_1 - c_rotate_p.T_2));
            sita_t = ((c_rotate_p.v_m + c_g.w) / 2) * (t - c_rotate_p.T_1 - c_rotate_p.T_2)
                - (c_g.w - c_rotate_p.v_m) / 2 * (c_rotate_p.T_3 / PI) * sin(PI / c_rotate_p.T_3 * (t - c_rotate_p.T_1 - c_rotate_p.T_2))
                + c_rotate_p.v_m * c_rotate_p.T_2
                + ((c_rotate_p.v_m + c_s.w) / 2) * c_rotate_p.T_1;
        }

        t = t + CPDT;
        //简化版s_t计算方法，降低计算量,但是存在误差
        //s_t = s_t + v_t * DT;
        //插值法查找匹配s_t对应的u值，进而计算曲线对应点的位置信息
        {
            int match_num = 0;
            u = 0;
            while (BCP_S[match_num] < s_t)
            {
                u = u + BCDU;
                match_num = match_num + 1;
                if (match_num >= BCP_num)
                {
                    match_num = BCP_num;
                    break;
                }
            }
            if (match_num < BCP_num&&match_num > 0)
                u = u + BCDU* (s_t - BCP_S[match_num - 1]) / (BCP_S[match_num] - BCP_S[match_num - 1]);
            else if (match_num == BCP_num)
                u = 1;
            else if (match_num == 0)
                u = 0;
        }

        switch (obs_num) //选择合适的贝塞尔函数
        {
        case 0:BCP_t = Bezier0(c_s, c_g, u); break;
        case 1:BCP_t = Bezier1(c_s, c_g, u, obs_0); break;
        case 2:BCP_t = Bezier2(c_s, c_g, u, obs_0, obs_1); break;
        }
        CPP[num].x = BCP_t.x;
        CPP[num].y = BCP_t.y;
        CPP[num].r = BCP_t.r;
        CPP[num].v_x = v_t * cos(BCP_t.c);
        CPP[num].v_y = v_t * sin(BCP_t.c);
        CPP[num].a_x = a_t * cos(BCP_t.c);
        CPP[num].a_y = a_t * sin(BCP_t.c);
        CPP[num].sita = c_s.sita + sita_t;
        CPP[num].w = w_t;
        CPP[num].a_s = a_s_t;
        num++;
    }
    CPP_num = num - 1;
    //接来下进行姿态角规划

    return 3;
}

/********************************/
//name:int chassis_tracking()
//function:对底盘路径规划结果进行跟踪运动
//
//input:
//output:
//      1:导航至最后最后一个点，完成轨迹跟踪
//      2:更新导航点
/********************************/
int chassis_tracking()
{
    float NGDis, NGDisLimit;//导航点距离
    float Error_x, Error_y;
    float dx, dy, sita;
    int NG_num; //实际目标点
    POINT_chassis TAP;
    chassis.getstatus();//更新底盘当前状态信息

    //寻找虚拟目标点
    while (aim_num < CPP_num)
    {
        TAP = CPP[aim_num];
        Error_x = chassis.actstatus.x - TAP.x;
        if (Error_x >= 0)
        {
            aim_num = aim_num + 1;
        }
        else break;
    }
    if (aim_num >= CPP_num) //路径跟踪完成
    {
        aim_num = CPP_num;
        return 2;
    }
    //计算当前点与当前导航点的距离，根据距离大小更新导航点，设置当前状态下底盘运动的目标点及速度信息
    NGDisLimit = (fabs(CPP[aim_num].r) - 100)*NGPara1 + NGPara2;//跟轨迹曲率相关的导航距离限制
    NG_num = aim_num;
    Error_x = chassis.actstatus.x - CPP[NG_num].x;
    Error_y = chassis.actstatus.y - CPP[NG_num].y;
    NGDis = Error_x*Error_x + Error_y*Error_y;//距离平方值，避免开方，减少运算量
    while (NGDis < NGDisLimit && NG_num < CPP_num)
    {
        NG_num++;
        Error_x = chassis.actstatus.x - CPP[NG_num].x;
        Error_y = chassis.actstatus.y - CPP[NG_num].y;
        NGDis = Error_x*Error_x + Error_y*Error_y;
        if (NG_num == CPP_num)
            break;
    }
    //sita = atan2(Error_y,Error_x);

    chassis.objstatus = CPP[NG_num];
    chassis.movectrl();
    return 1;
}
