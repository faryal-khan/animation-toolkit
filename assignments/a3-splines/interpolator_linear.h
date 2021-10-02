#ifndef _interpolator_linear_H_
#define _interpolator_linear_H_

#include <string>
#include <vector>
#include <iostream> 
#include "interpolator.h"

//--------------------------------
// Linear 
//--------------------------------

class InterpolatorLinear : public Interpolator
{
public:
    InterpolatorLinear() : Interpolator("Linear") {}
    virtual glm::vec3 interpolate(int segment, double u) const {
       glm::vec3 pos1 = mCtrlPoints.at(segment);
       glm::vec3 pos2 = mCtrlPoints.at(segment+1);
       return pos1 *(1-((float)u)) + pos2 *(float)u;
       
    }

    virtual void computeControlPoints(const std::vector<glm::vec3>& keys) {
       
       if(keys.size() == 0 || keys.size() == 1){
         mCtrlPoints.clear();
       }
       else{
          for(glm::vec3 i : keys){
            mCtrlPoints.push_back(i);
          }
       }
     
    }


};

#endif
