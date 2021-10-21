#include "atkmath/quaternion.h"
#include "atkmath/matrix3.h"
#include "atkmath/vector3.h"

namespace atkmath {

Quaternion Quaternion::Slerp(const Quaternion& q0, const Quaternion& q1, double t)
{
	// TODO
	return Quaternion(1,0,0,0);
}

void Quaternion::toAxisAngle (Vector3& axis, double& angleRad) const
{
	angleRad = acos(this->mW)*2;
	Vector3 *current = new Vector3(this->mX/(sin(angleRad/2)), this->mY/(sin(angleRad/2)), this->mZ/(sin(angleRad/2)));
	axis = *current;
}

void Quaternion::fromAxisAngle (const Vector3& axis, double angleRad)
{
	Vector3 a = sin(angleRad/2)*axis;
	double b = cos(angleRad/2);

	this->mX = a.x();
	this->mY = a.y();
	this->mZ = a.z();
	this->mW = b;
	

}

Matrix3 Quaternion::toMatrix () const
{
	double x = this->mX;
	double y = this->mY;
	double z = this->mZ;
	double w = this->mW;
	
	Matrix3 result = Matrix3(1 - 2*(pow(y, 2)+pow(z, 2)), 2*(x*y-w*z),  2*(x*z+w*y),
	 2*(x*y+w*z),  1-2*(pow(x, 2)+pow(z, 2)),  2*(y*z-w*x),  2*(x*z-w*y), 2*(y*z+w*x),  1-2*(pow(x, 2)+pow(y, 2)));

	return result;
}

void Quaternion::fromMatrix(const Matrix3& rot)
{
	float w, x, y, z;

	w = sqrt(0.25*(rot[0][0]+rot[1][1]+rot[2][2] +1));
	x =  sqrt(0.25*(1+rot[0][0]-rot[1][1]-rot[2][2]));
	y =  sqrt(0.25*(1-rot[0][0]+rot[1][1]-rot[2][2]));
	z = sqrt(0.25*(1-rot[0][0]-rot[1][1]+rot[2][2]));

	if(w>x && w>y && w>z){

		x = (rot[2][1]-rot[1][2])*0.25*(1/w);
		y = (rot[0][2]-rot[2][0])*0.25*(1/w);
		z = (rot[1][0]-rot[0][1])*0.25*(1/w);
		
		this->mX = x;
		this->mY = y;
		this->mZ = z;
		this->mW = w;
		return;
	}

	if(x>w && x>y && x>z){

		w = (rot[2][1]-rot[1][2])*0.25*(1/x);
		y = (rot[1][0]+rot[0][1])*0.25*(1/x);
		z = (rot[0][2]+rot[2][0])*0.25*(1/x);

		this->mX = x;
		this->mY = y;
		this->mZ = z;
		this->mW = w;
		return;
	}

	if(y>w && y>x && y>z){

		w = (rot[0][2]-rot[2][0])*0.25*(1/y);
		x = (rot[1][0]+rot[0][1])*0.25*(1/y);
		z = (rot[1][2]+rot[2][1])*0.25*(1/y);
		
		this->mX = x;
		this->mY = y;
		this->mZ = z;
		this->mW = w;
		return;
	}

	if(z>w && z>x && z>y){
		
		x = (rot[0][2]+rot[2][0])*0.25*(1/z);
		y = (rot[1][2]+rot[2][1])*0.25*(1/z);
		w = (rot[1][0]-rot[0][1])*0.25*(1/z);

		this->mX = x;
		this->mY = y;
		this->mZ = z;
		this->mW = w;
		return;
	}

}

}