#include "atkmath/matrix3.h"
#include "atkmath/quaternion.h"

namespace atkmath {

Vector3 Matrix3::toEulerAnglesXYZ() const
{
   Vector3* results;
   if(this->m13 != 1 && this->m13 != -1){
      results = new Vector3(-1*atan2(this->m23, this->m33),  asin((this->m13)), -1*atan2(this->m12, this->m11));
   }
   else{
      if(this->m13 == 1){
         double ang = atan2(this->m21, this->m22);
         results = new Vector3(0, (90*3.14159265)/180.0, ang);
      }
      else if(this->m13 == -1){
         double ang = atan2(this->m21,this->m22);
         results = new Vector3(0, -1*(90*3.14159265)/180.0, ang );
      }
   }

   return *results;
}

Vector3 Matrix3::toEulerAnglesXZY() const
{
    Vector3* results;
   if(this->m12 != 1 && this->m12 != -1){
      results = new Vector3(atan2(this->m32, this->m22),  atan2(this->m13, this->m11), asin((-1*this->m12)));
   }
   else{
      if(this->m12 == 1){
         double ang = atan2(-1*this->m31, this->m33);
         results = new Vector3(0, ang, -1*(90*3.14159265)/180.0);
      }
      else if(this->m12 == -1){
         double ang = atan2(-1*this->m31,this->m33);
         results = new Vector3(0, ang, (90*3.14159265)/180.0);
      }
   }

   return *results;
}

Vector3 Matrix3::toEulerAnglesYXZ() const
{
   Vector3* results;
   if(this->m23 != 1 && this->m23 != -1){
      results = new Vector3(asin((-1*this->m23)), atan2(this->m13, this->m33),  atan2(this->m21, this->m22));
   }
   else{
      if(this->m23 == 1){
         double ang = atan2(-1*this->m12, this->m11);
         results = new Vector3(-1*(90*3.14159265)/180.0, 0, ang);
      }
      else if(this->m23 == -1){
         double ang = atan2(-1*this->m12,this->m11);
         results = new Vector3((90*3.14159265)/180.0, 0, ang);
      }
   }

   return *results;
}

Vector3 Matrix3::toEulerAnglesYZX() const
{
    Vector3* results;
   if(this->m21 != 1 && this->m21 != -1){
      results = new Vector3(-1*atan2(this->m23, this->m22), -1*atan2(this->m31, this->m11), asin((this->m21)));
   }
   else{
      if(this->m21 == 1){
         double ang = atan2(this->m32, this->m33);
         results = new Vector3(0, ang, (90*3.14159265)/180.0);
      }
      else if(this->m21 == -1){
         double ang = -1*atan2(this->m32,this->m33);
         results = new Vector3(0, ang, -1*(90*3.14159265)/180.0);
      }
   }

   return *results;
}

Vector3 Matrix3::toEulerAnglesZXY() const
{
   Vector3* results;
   if(this->m32 != 1 && this->m32 != -1){
      results = new Vector3( asin((this->m32)), -1*atan2(this->m31, this->m33), -1*atan2(this->m12, this->m22));
   }
   else{
      if(this->m32 == 1){
         double ang = atan2(this->m13, this->m11);
         results = new Vector3((90*3.14159265)/180.0, 0, ang);
      }
      else if(this->m32 == -1){
         double ang = -1*atan2(this->m13,this->m11);
         results = new Vector3(-1*(90*3.14159265)/180.0, 0, ang);
      }
   }

   return *results;
}

Vector3 Matrix3::toEulerAnglesZYX() const
{
   Vector3* results;
   if(this->m31 != 1 && this->m31 != -1){
      results = new Vector3( atan2(this->m32, this->m33), asin(-1* (this->m31)), atan2(this->m21, this->m11));
   }
   else{
      if(this->m31 == 1){
         double ang = atan2(-1*this->m12,-1*this->m13);
         results = new Vector3(ang, -1*(90*3.14159265)/180.0 , 0);
      }
      else if(this->m31 == -1){
         double ang = atan2(this->m12,this->m13);
         results = new Vector3(ang, (90*3.14159265)/180.0, 0);
      }
   }

   return *results;
   
}

void Matrix3::fromEulerAnglesXYZ(const Vector3& angleRad)
{
    Matrix3* Rx = computeRx(angleRad[0]);
   
   Matrix3* Ry = computeRy(angleRad[1]);
   
   Matrix3* Rz = computeRz(angleRad[2]);

   double result[3][3] = {{0,0,0},{0,0,0},{0,0,0}};

   for(int i=0;i<3;i++){
      for(int j=0;j<3;j++){
         double product = 0.0;
         for(int k = 0;k<3;k++){
            product +=  (*Rx)[i][k] * (*Ry)[k][j];
         }
         result[i][j] = product;
      }
   }
  
   
  Matrix3* results = new Matrix3(0, 0, 0,
                                 0, 0, 0,
                                 0, 0, 0);

   for(int i=0;i<3;i++){
      for(int j=0;j<3;j++){
         for(int k = 0;k<3;k++){
            (*results)[i][j] +=  result[i][k] * (*Rz)[k][j];
         }
      }
   }

   *this = (*results);
}

void Matrix3::fromEulerAnglesXZY(const Vector3& angleRad)
{
   Matrix3* Rx = computeRx(angleRad[0]);
   
   Matrix3* Ry = computeRy(angleRad[1]);
   
   Matrix3* Rz = computeRz(angleRad[2]);

   double result[3][3] = {{0,0,0},{0,0,0},{0,0,0}};

   for(int i=0;i<3;i++){
      for(int j=0;j<3;j++){
         double product = 0.0;
         for(int k = 0;k<3;k++){
            product +=  (*Rx)[i][k] * (*Rz)[k][j];
         }
         result[i][j] = product;
      }
   }
  
   
  Matrix3* results = new Matrix3(0, 0, 0,
                                 0, 0, 0,
                                 0, 0, 0);

   for(int i=0;i<3;i++){
      for(int j=0;j<3;j++){
         for(int k = 0;k<3;k++){
            (*results)[i][j] +=  result[i][k] * (*Ry)[k][j];
         }
      }
   }

   *this = (*results);
}

void Matrix3::fromEulerAnglesYXZ(const Vector3& angleRad)
{
   Matrix3* Rx = computeRx(angleRad[0]);
   
   Matrix3* Ry = computeRy(angleRad[1]);
   
   Matrix3* Rz = computeRz(angleRad[2]);

   double result[3][3] = {{0,0,0},{0,0,0},{0,0,0}};

   for(int i=0;i<3;i++){
      for(int j=0;j<3;j++){
         double product = 0.0;
         for(int k = 0;k<3;k++){
            product +=  (*Ry)[i][k] * (*Rx)[k][j];
         }
         result[i][j] = product;
      }
   }
  
   
  Matrix3* results = new Matrix3(0, 0, 0,
                                 0, 0, 0,
                                 0, 0, 0);

   for(int i=0;i<3;i++){
      for(int j=0;j<3;j++){
         for(int k = 0;k<3;k++){
            (*results)[i][j] +=  result[i][k] * (*Rz)[k][j];
         }
      }
   }

   *this = (*results);
}

void Matrix3::fromEulerAnglesYZX(const Vector3& angleRad)
{
   Matrix3* Rx = computeRx(angleRad[0]);
   
   Matrix3* Ry = computeRy(angleRad[1]);
   
   Matrix3* Rz = computeRz(angleRad[2]);

   double result[3][3] = {{0,0,0},{0,0,0},{0,0,0}};

   for(int i=0;i<3;i++){
      for(int j=0;j<3;j++){
         double product = 0.0;
         for(int k = 0;k<3;k++){
            product +=  (*Ry)[i][k] * (*Rz)[k][j];
         }
         result[i][j] = product;
      }
   }
  
   
  Matrix3* results = new Matrix3(0, 0, 0,
                                 0, 0, 0,
                                 0, 0, 0);

   for(int i=0;i<3;i++){
      for(int j=0;j<3;j++){
         for(int k = 0;k<3;k++){
            (*results)[i][j] +=  result[i][k] * (*Rx)[k][j];
         }
      }
   }

   *this = (*results);
}

void Matrix3::fromEulerAnglesZXY(const Vector3& angleRad)
{
   Matrix3* Rx = computeRx(angleRad[0]);
   
   Matrix3* Ry = computeRy(angleRad[1]);
   
   Matrix3* Rz = computeRz(angleRad[2]);

   double result[3][3] = {{0,0,0},{0,0,0},{0,0,0}};

   for(int i=0;i<3;i++){
      for(int j=0;j<3;j++){
         double product = 0.0;
         for(int k = 0;k<3;k++){
            product +=  (*Rz)[i][k] * (*Rx)[k][j];
         }
         result[i][j] = product;
      }
   }
  
   
  Matrix3* results = new Matrix3(0, 0, 0,
                                 0, 0, 0,
                                 0, 0, 0);

   for(int i=0;i<3;i++){
      for(int j=0;j<3;j++){
         for(int k = 0;k<3;k++){
            (*results)[i][j] +=  result[i][k] * (*Ry)[k][j];
         }
      }
   }

   *this = (*results);
}

void Matrix3::fromEulerAnglesZYX(const Vector3& angleRad)
{
   Matrix3* Rx = computeRx(angleRad[0]);
   
   Matrix3* Ry = computeRy(angleRad[1]);
   
   Matrix3* Rz = computeRz(angleRad[2]);

   double result[3][3] = {{0,0,0},{0,0,0},{0,0,0}};

   for(int i=0;i<3;i++){
      for(int j=0;j<3;j++){
         double product = 0.0;
         for(int k = 0;k<3;k++){
            product +=  (*Rz)[i][k] * (*Ry)[k][j];
         }
         result[i][j] = product;
      }
   }
  
   
  Matrix3* results = new Matrix3(0, 0, 0,
                                 0, 0, 0,
                                 0, 0, 0);

   for(int i=0;i<3;i++){
      for(int j=0;j<3;j++){
         for(int k = 0;k<3;k++){
            (*results)[i][j] +=  result[i][k] * (*Rx)[k][j];
         }
      }
   }

   *this = (*results);
}

void Matrix3::toAxisAngle(Vector3& axis, double& angleRad) const
{
   // TODO
}

void Matrix3::fromAxisAngle(const Vector3& axis, double angleRad)
{
   // TODO
   *this = Identity;
}

Matrix3* Matrix3::computeRx(float angle){
   return new Matrix3(1.0, 0.0, 0.0,
                              0.0, cos(angle), -(sin(angle)),
                              0.0, sin(angle), cos(angle));
   
}

Matrix3* Matrix3::computeRy(float angle){
   return new Matrix3(cos(angle), 0.0, sin(angle),
                              0.0, 1.0, 0.0,
                              -sin(angle), 0.0, cos(angle));
   
}

Matrix3* Matrix3::computeRz(float angle){
   return new Matrix3(cos(angle), -sin(angle),0.0,
                              sin(angle), cos(angle), 0.0,
                              0.0, 0.0, 1.0);
   
}

}