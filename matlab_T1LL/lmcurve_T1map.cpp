/*
 * Project:  LevenbergMarquardtLeastSquaresFitting
 *
 * File:     lmcurve.c
 *
 * Contents: Simplified wrapper for one-dimensional curve fitting,
 *           using Levenberg-Marquardt least-squares minimization.
 *
 * Usage:    see application sample demo/curve1.c
 *
 * Author:   Joachim Wuttke 2010
 *
 * Homepage: www.messen-und-deuten.de/lmfit
 */
#include "mex.h"
#include "lmcurve.h"


//#include <stdlib.h>
//#include <stdio.h>
#include <math.h>
//#include <float.h>

//#define double float //if use single precision card

//#define LMFIT_DEBUG_MESSAGES
// function for curve fit
double f( double t, const double *p ) {
    return abs(p[0]-p[1]*exp(-t/p[2]));
}


void mexFunction(int nlhs,
        mxArray *plhs[],
        int nrhs,
        const mxArray *prhs[]) {

    int n_par = 3; // number of parameters in model function f
    //   double *par = (double *)mxGetData(prhs[0]); // relatively bad starting value
    double par[3];
    /* data pairs: slightly distorted standard parabola */

    int m_dat = 11; // number of data pairs
    int i;
    double *t =(double *)mxGetData(prhs[0]);
    double *y =(double *)mxGetData(prhs[1]);

    int  resultdim[2];
    int  m_y;



    m_y = mxGetN(prhs[1]); //spatial data
    m_dat = mxGetM(prhs[1]); //time domain



    /* auxiliary parameters */

    lm_status_struct status;
    lm_control_struct control = {1.e-7, 1.e-7, 1.e-7, 1.e-7, 100., 100, 0, 0 };


    /* perform the fit */
    double *coef ;
    resultdim[0]=1;
    resultdim[1]=3*m_y;
    plhs[0] = mxCreateNumericArray(2, resultdim , mxDOUBLE_CLASS, mxREAL);
    coef = (double*)mxGetData(plhs[0]);

    double *new_y ;
    resultdim[0]=1;
    resultdim[1]=m_dat*m_y;
    plhs[1] = mxCreateNumericArray(2, resultdim , mxDOUBLE_CLASS, mxREAL);
    new_y = (double*)mxGetData(plhs[1]);



    double max_y;
    int max_y_index;
    for (int ii=0; ii<m_y;ii++) {
        max_y_index=0;
        max_y=*(y+ii*m_dat);


                //find minimum y
          for (int t_count=0;t_count< m_dat;t_count++)
          {
           if (max_y < *(y+t_count+ii*m_dat) )
            {
                max_y=*(y+t_count+ii*m_dat);
                max_y_index=t_count;
            }

       }


        par[0]=*(y+(ii+1)*m_dat-1);
        par[1]=par[0]*2;
        par[2]=1;



         // initial guess
    /*
        //find minimum y
          for (int t_count=0;t_count< m_dat;t_count++)
          {
           if (min_y > *(y+t_count+ii*m_dat) )
            {
                min_y=*(y+t_count+ii*m_dat);
                min_y_index=t_count;
            }

       }

        par[2]=t[min_y_index]/0.45;  // initilize the first guess
        if (par[2] < 0.5 || par[2]> 1.5) par[2]=1;

          printf( "\nOrig:%f\n", par[2] );
      */


          if (max_y>50)
          {
             lmcurve( n_par, par, m_dat, t, y+ii*m_dat,f, &control, &status );
        coef[ii*3+0]=par[0];coef[ii*3+1]=par[1];  coef[ii*3+2]=(par[2]);}
          else
      {
        coef[ii*3+0]=0;coef[ii*3+1]=0;  coef[ii*3+2]=1e-5;}

//       if  (par[2]<=0)
//           coef[ii*3+2]=1e-5;


       // printf( "\nObtained:%f\n", par[2]  );
        for (int t_count=0;t_count< m_dat;t_count++)
            new_y[ii*m_dat+t_count]=f(*(t+t_count), par);
    }
    /* print results */

//     printf( "\nResults:\n" );
//
//
//     printf("obtained parameters:\n");
//     for ( i = 0; i < n_par; ++i)
// 	printf("  par[%i] = %12g\n", i, par[i]);
//     printf("obtained norm:\n  %12g\n", status.fnorm );
//
//     printf("fitting data as follows:\n");
//     for ( i = 0; i < m_dat; ++i)
//         printf( "  t[%2d]=%12g y=%12g fit=%12g residue=%12g A=%12g B=%12g T1* = %12g\n",
//                 i, t[i], y[i], f(t[i],par), y[i] - f(t[i],par),par[0],par[1],par[2] );
//








//
}
