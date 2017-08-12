//#include "stdafx.h"
#include "PID.h"
//#include <iostream>

float PID:: PID_Regulator(float Reference, float PresentFeedback)
{
    float error;
    float error_inc;
    float pTerm;
    float iTerm;
    float dTerm;
    float dwAux;
    float output;
    /*error computation*/
    error = Reference - PresentFeedback;
    /*proportional term computation*/
    pTerm = error * this->Kp;
    /*Integral term computation*/
    if (this->Ki == 0)
    {
        this->Integral = 0;
    }
    else
    {
        iTerm = error * this->Ki;
        dwAux = this->Integral + iTerm;
        /*limit integral*/
        if (dwAux > this->UpperLimitIntegral)
        {
            this->Integral = this->UpperLimitIntegral;
        } else if (dwAux < this->LowerLimitIntegral)
        {
            this->Integral = this->LowerLimitIntegral;
        } else
        {
            this->Integral = dwAux;
        }
    }
    /*differential term computation*/
    error_inc = error - this->PreError;
    dTerm = error_inc * this->Kd;
    this->PreError = error;

    output = pTerm + this->Integral + dTerm;

    /*limit output*/
    if (output >= this->UpperLimitOutput)
    {
        return (this->UpperLimitOutput);
    } else if (output < this->LowerLimitOutput)
    {
        return (this->LowerLimitOutput);
    } else
    {
        return output;
    }
}
