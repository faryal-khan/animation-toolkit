#include "ik_controller.h"
#include <cmath>
#include <iostream>

using namespace atk;
using namespace glm;
using namespace std;

bool IKController::solveIKAnalytic(Skeleton& skeleton, 
    int jointid, const vec3& goalPos, float epsilon) {
  if (jointid == -1) return true;

  Joint* ankle = skeleton.getByID(jointid);
  if (!ankle->getParent()) {
    std::cout << "Warning: solveIKAnalytic() needs joint "
      "with parent and grandparent\n";
    return false;
  }

  Joint* knee = ankle->getParent();
  if (!knee->getParent()) {
    std::cout << "Warning: solveIKAnalytic() needs joint "
      "with parent and grandparent\n";
    return false;
  }

  Joint* hip = knee->getParent();

  // TODO: Your code here
  return true;
}
void lookAtTarget(Joint* end, Joint* current, const vec3& target, float nudge) {
      // TODO: Your code here

      vec3 r = end->getGlobalTranslation()-current->getGlobalTranslation();
      vec3 e = target-end->getGlobalTranslation();
      
      vec3 cross = vec3(glm::cross(r, e));

      float angle = nudge * atan2(length(cross), dot(r, e)+dot(r, r));

      current->setLocalRotation(glm::angleAxis(angle, inverse(current->getParent()->getGlobalRotation()) *(cross/length(cross))) *current->getLocalRotation());
      current->fk();

   }

bool IKController::solveIKCCD(Skeleton& skeleton, int jointid, 
    const vec3& goalPos, const std::vector<Joint*>& chain, 
    float threshold, int maxIters, float nudgeFactor) {
  // There are no joints in the IK chain for manipulation
  if (chain.size() == 0) return true;
  int iters = 0;
  vec3 p = (skeleton.getByID(jointid)->getGlobalTranslation());
  while(length(goalPos-p) > threshold && iters<maxIters){
    for(int i=1;i<chain.size();i++){
      lookAtTarget(chain[0], chain[i],goalPos, nudgeFactor);
    }
    iters++;
    p = skeleton.getByID(jointid)->getGlobalTranslation();
  }

  return false;
}
