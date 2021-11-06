#ifndef PERSON_H_
#define PERSON_H_

#include "atkui/framework.h"

using namespace atk;
using namespace glm;

class Person
{
public:
   Person() {}
   Person(const vec3& p, const vec3& c, float s) {
      _pos = p;
      _size = vec3(s);
      _color = c;
   }
   virtual ~Person() {}

   void draw(const Skeleton& skeleton, atkui::Framework& f) {

      f.push();
      f.translate(_pos);
      f.scale(_size);
      f.setColor(_color);

      float jointRadius = 15;
      for (int i = 0; i < skeleton.getNumJoints(); i++) {
         Joint* joint = skeleton.getByID(i);
         if (joint->getParent() == 0) continue;
         if (joint->getParent()->getName().find("Hand") != std::string::npos) continue; // skip hands

         vec3 p1 = joint->getGlobalTranslation();
         vec3 p2 = joint->getParent()->getGlobalTranslation();
         f.drawEllipsoid(p1, p2, jointRadius);
         f.drawSphere(p2, jointRadius);
         f.drawSphere(p1, jointRadius);
      }

      Joint* head = skeleton.getByName("HeadTop_End");
      assert(head);

      // Use joint's global position and rotation to convert 
      // from local head coordinates to global coordinates
      Joint* pParent = head->getParent();
      Transform xform = pParent->getLocal2Global();

      float headLength = glm::distance(
         pParent->getGlobalTranslation(), 
         head->getGlobalTranslation());

      // eyes
      float pupilSize = jointRadius * 0.3;
      f.setColor(vec3(0));

      vec3 pupilPosL(jointRadius*0.3, headLength * 0.75, pupilSize); 
      f.drawSphere(xform.transformPoint(pupilPosL), pupilSize);

      vec3 pupilPosR(-jointRadius*0.3, headLength * 0.75, pupilSize); 
      f.drawSphere(xform.transformPoint(pupilPosR), pupilSize);

   f.setColor(vec3(211, 211, 211));

       vec3 toothPosL(jointRadius*0.2, headLength * 0.25, pupilSize); 
      f.drawCube(xform.transformPoint(toothPosL), vec3(6, 6, 6));

      vec3 toothPosR(-jointRadius*0.2, headLength * 0.25, pupilSize); 
      f.drawCube(xform.transformPoint(toothPosR), vec3(6, 6, 6));

      // horns
      f.setColor(_color);
      float hs = jointRadius;
      vec3 hornPosL(jointRadius*0.25, 2*headLength, 0);
      mat3 hornRotL = eulerAngleRO(ZYX, glm::radians(vec3(-100, 0, -10)));

      f.push();
      f.transform(xform*Transform(hornRotL, hornPosL));
      f.scale(vec3(0.5*hs,0.5*hs,2*hs));
      f.drawSphere(vec3(0), 1.0f);
      f.pop();

      vec3 hornPosR(-jointRadius*0.25, 2*headLength, 0);
      mat3 hornRotR = eulerAngleRO(ZYX, glm::radians(vec3(-100, 0, 10)));

      f.push();
      f.transform(xform*Transform(hornRotR, hornPosR));
      f.scale(vec3(0.5*hs,0.5*hs,2*hs));
      f.drawSphere(vec3(0), 1.0f);
      f.pop();

      // pitch fork
      Joint* hand = skeleton.getByName("RightHand");
      assert(hand);
      xform = hand->getLocal2Global();

      hs = jointRadius*0.25;
      float len = 100;
      f.setColor(vec3(1.0f, 0.5f, 0.31f));
      vec3 spearPos(0, 0, 0);
      mat3 spearRot = eulerAngleRO(ZYX, glm::radians(vec3(0, 0, 0)));

      f.push();
      f.transform(xform*Transform(spearRot, spearPos));
      f.scale(vec3(10,10,len));
      f.drawCone(vec3(0), 1.0f);
      f.pop();

       f.setColor(vec3(0,1,0));

      mat3 tipRot = eulerAngleRO(ZYX, glm::radians(vec3(180, 0, 0)));   
      mat3 tipRotL = eulerAngleRO(ZYX, glm::radians(vec3(170, 0, 0)));
      mat3 tipRotR = eulerAngleRO(ZYX, glm::radians(vec3(-170, 0, 0)));
      vec3 tipPosL(0, 0, -len*0.5);

      f.push();
      f.transform(xform*Transform(tipRot, tipPosL));
      f.scale(vec3(hs,hs,15*hs));
      f.drawSphere(vec3(0), 1.0f);
      f.pop();

      vec3 tipPosR(0, 0, -len*0.5);


      f.push();
      f.transform(xform*Transform(tipRotL, tipPosR));
      f.scale(vec3(hs,hs,15*hs));
      f.drawSphere(vec3(0), 1.0f);

      f.push();
      f.transform(xform*Transform(tipRotR, tipPosR));
      f.scale(vec3(hs,hs,15*hs));
      f.drawSphere(vec3(0), 1.0f);
      

      f.pop();

      // vec3 tipPos(0, 0, -len*0.5);
       //mat3 tipRot = eulerAngleRO(ZYX, glm::radians(vec3(180, 0, 0)));
      // f.push();
      // f.transform(xform*Transform(tipRot, tipPos));
      // f.scale(4.0f*vec3(hs,hs,hs*1.0f));
      // f.drawCone(vec3(0), 1.0f);
      // f.pop();
      
      f.pop();
   }

   virtual void keyUp(int key, int mods) {
      if (key == 'P') _paused = !_paused;
   }

protected:
   Motion _motion;
   Skeleton _skeleton;
   bool _paused = false;
   vec3 _color = vec3(128.0,128.0,128.0);
   vec3 _size = vec3(1.0);
   vec3 _pos = vec3(0);

};

#endif
