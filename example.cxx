#include <iostream>
#include "TLorentzVector.h"
#include "llg_angles.hpp"

int main() {
  TLorentzVector gamma_p4 (0.0525693, 1.88992, 4.74705, 5.1097);
  TLorentzVector lep_minus_p4 (-10.3256, -67.0069, 134.937, 151.012);
  TLorentzVector lep_plus_p4 (24.8959, 25.1421, 80.0613, 87.5314);
  TLorentzVector llg_p4 = lep_minus_p4 + lep_plus_p4 + gamma_p4;
  // cosTheta should be -0.253116
  double cosTheta = llg::get_cosTheta(llg_p4, lep_minus_p4, lep_plus_p4);
  std::cout<<"cosTheta: "<<cosTheta<<std::endl;
  // costheta should be -0.867113
  double costheta = llg::get_costheta(llg_p4, lep_minus_p4, lep_plus_p4);
  std::cout<<"costheta: "<<costheta<<std::endl;
  // phi should be -1.55389
  double phi = llg::get_phi(llg_p4, lep_minus_p4, lep_plus_p4);
  std::cout<<"phi: "<<phi<<std::endl;
  return 0;
}
