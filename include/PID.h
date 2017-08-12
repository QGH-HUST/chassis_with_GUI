#ifndef PID_H
#define PID_H

//#include <iostream>


class PID
{
    public:
    double Kp; //比例常数Proportional Const
    double Ki; //积分常数 IntegralConst
    double Kd; //微分常数Derivative Const
    double LowerLimitOutput;  //Lower Limit for Output limitation
    double UpperLimitOutput;  //Upper Limit for Output limitation
    double LowerLimitIntegral; //Lower Limit for Integral term limitation
    double UpperLimitIntegral; //Upper Limit for Integral term limitation
    double Integral; //»ý·ÖÏî,´æ´¢»ý·ÖÎó²î¡ÁKI
    double PreError;
    void PID_init();
    float PID_Regulator(float Reference, float PresentFeedback);
};


#endif // PID_H
