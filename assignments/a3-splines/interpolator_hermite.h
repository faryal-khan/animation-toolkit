#ifndef _interpolator_hermite_
#define _interpolator_hermite_

#include <string>
#include <vector>
#include <Eigen/Dense>
#include "interpolator.h"

//--------------------------------
// Hermite 
//--------------------------------

class InterpolatorHermite : public Interpolator
{
public:
    InterpolatorHermite() : Interpolator("Hermite"), mClampDir(glm::vec3(1,0,0)) {}

    virtual glm::vec3 interpolate(int segment, double u) const {
 
       float first = (2*pow(u, 3));
       float second = (3*pow(u, 2)+ 1);
       float third = u*pow((1-u),2);
       float fourth = -pow(u, 2) + pow(u, 3);
       float fifth = 3*pow(u, 2) - 2*pow(u, 3);

       glm::vec3 result = (first - second) * mCtrlPoints.at(segment) + third * mCtrlPoints.at(segment+1) + fourth * mCtrlPoints.at(segment+3) + fifth *mCtrlPoints.at(segment+2);
       return result;
    }

    virtual void computeControlPoints(const std::vector<glm::vec3>& keys) {

        for(int i=0;i<keys.size()-4;i+=4){

            Eigen::MatrixXd A(keys.size(), keys.size());
            Eigen::MatrixXd p(keys.size(), keys.size());
            Eigen::MatrixXd pPrime(keys.size(), 3); 

            A(0,0) =  2; A(0,1) = 1; A(0,2) = 0; A(0,3) = 0; A(0,4) = 0; 
            A(1,0) =  1; A(1,1) = 4; A(1,2) = 1; A(1,3) = 0; A(1,4) = 0; 
            A(2,0) =  0; A(2,1) = 1; A(2,2) = 4; A(2,3) = 1; A(2,4) = 0; 
            A(3,0) =  0; A(3,1) = 0; A(3,2) = 1; A(3,3) = 4; A(3,4) = 1; 
            A(4,0) =  0; A(4,1) = 0; A(4,2) = 0; A(4,3) = 1; A(4,4) = 2;

            glm::vec3 v0 = 3.0f *(keys[i+1] - keys[i]);
            glm::vec3 v1 = 3.0f *(keys[i+2] - keys[i]);
            glm::vec3 v2 = 3.0f *(keys[i+3] - keys[i+1]);
            glm::vec3 v3 = 3.0f *(keys[i+4] - keys[i+2]);
            glm::vec3 v4 = 3.0f *(keys[i+4] - keys[i+3]);
            p(0,0) = v0[0]; p(0,1) = v0[1];
            p(1,0) = v1[0]; p(1,1) = v1[1]; 
            p(2,0) = v2[0]; p(2,1) = v2[1]; 
            p(3,0) = v3[0]; p(3,1) = v3[1]; 
            p(4,0) = v4[0]; p(4,1) = v4[1]; 

            pPrime = A.inverse() * p;
            for(int j=i;j<=i+4;j++){
                glm::vec3 result = glm::vec3(pPrime(j, 0), pPrime(j, 1), 0);
                mCtrlPoints.push_back(keys[j]);
                mCtrlPoints.push_back(result);
            }

        }


    }

    void setClamped(bool c) { mIsClamped = c; }
    bool isClamped() const { return mIsClamped; }

    void setClampedDirection(const glm::vec3& v) { mClampDir = v; }
    glm::vec3 getClampDirection() const { return mClampDir; }

private:
    bool mIsClamped = true;
    glm::vec3 mClampDir;
};

#endif
