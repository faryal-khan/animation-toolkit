#ifndef _interpolator_catmullrom_
#define _interpolator_catmullrom_

#include <string>
#include <vector>
#include "interpolator.h"

//--------------------------------
// Catmull-Rom 
//--------------------------------

class InterpolatorCatmullRom : public Interpolator
{
public:
    InterpolatorCatmullRom() : Interpolator("Catmull-Rom") {}

    virtual glm::vec3 interpolate(int segment, double u) const {
       
       int firstIndex = 0;
       if(segment!=0){
         firstIndex = 4*segment-1;
       }
       glm::vec3 B0, B1, B2, B3;
       
       B0 = mCtrlPoints[firstIndex];
       B1 = mCtrlPoints[firstIndex+1];
       B2 = mCtrlPoints[firstIndex+2];
       B3 = mCtrlPoints[firstIndex+3];
       

      float current = 1-u;
      float first = std::pow(current,3);
      float second = 3*u* std::pow(current,2) ;
      float third = 3* std::pow(u, 2) * current;
      float fourth = std::pow(u, 3);
      glm::vec3 pos = (first * B0) + (second *B1) + (third *B2) + (fourth *B3);
      return pos;

    }

    virtual void computeControlPoints(const std::vector<glm::vec3>& keys) {
       
      mCtrlPoints.clear();

      mCtrlPoints.push_back(keys[0]);
      glm::vec3 first = keys[0] + (1.0f/6)*(keys[1] - keys[0]);
      mCtrlPoints.push_back(first);

      for(int i=1;i<keys.size()-1;i++){
         if(!(i==keys.size()-2))
         {
            glm::vec3 b2 = keys[i+1] - (1.0f/6)*(keys[i+2] - keys[i]);
            mCtrlPoints.push_back(b2);
         }
         else{
            glm::vec3 b2 = keys[i] -(1.0f/6)*(keys[i+1] - keys[i-1]);
            mCtrlPoints.push_back(b2);
            
         }

         mCtrlPoints.push_back(keys[i]);
         glm::vec3 b1 = keys[i] + (1.0f/6)*(keys[i+1] - keys[i-1]);
         mCtrlPoints.push_back(b1);
      }
      glm::vec3 last = keys[keys.size()-1] -(1.0f/6)*(keys[keys.size()-1] - keys[keys.size()-2]);
      mCtrlPoints.push_back(last);
      mCtrlPoints.push_back(keys[keys.size()-1]);


       
    }
};

#endif
