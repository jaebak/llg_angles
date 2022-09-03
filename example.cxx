#include <iostream>
#include "TLorentzVector.h"
#include "llg_angles.hpp"

int main() {
  TLorentzVector gamma_p4 (0.0525693, 1.88992, 4.74705, 5.1097);
  TLorentzVector lep_minus_p4 (-10.3256, -67.0069, 134.937, 151.012);
  TLorentzVector lep_plus_p4 (24.8959, 25.1421, 80.0613, 87.5314);
  // cosTheta should be -0.253116
  double cosTheta = llg::get_cosTheta(lep_minus_p4, lep_plus_p4, gamma_p4);
  // costheta should be -0.867113
  double costheta = llg::get_costheta(lep_minus_p4, lep_plus_p4, gamma_p4);
  // phi should be -1.55389
  double phi = llg::get_phi(lep_minus_p4, lep_plus_p4, gamma_p4);
  std::cout<<"cosTheta: "<<cosTheta<<std::endl;
  std::cout<<"costheta: "<<costheta<<std::endl;
  std::cout<<"cosphi: "<<cos(phi)<<std::endl;
  std::cout<<"sinphi: "<<sin(phi)<<std::endl;

  // Alternative method 1. Gives same result.
  double cosTheta_alt1 = llg::get_cosTheta_alt1(lep_minus_p4, lep_plus_p4, gamma_p4);
  double costheta_alt1 = llg::get_costheta_alt1(lep_minus_p4, lep_plus_p4, gamma_p4);
  double cosphi_alt1 = llg::get_cosphi_alt1(lep_minus_p4, lep_plus_p4, gamma_p4);
  std::cout<<"[alt1] cosTheta: "<<cosTheta_alt1<<std::endl;
  std::cout<<"[alt1] costheta: "<<costheta_alt1<<std::endl;
  std::cout<<"[alt1] cosphi: "<<cosphi_alt1<<std::endl;

  // Alternative method 2. Gives same result.
  double cosTheta_alt2 = llg::get_cosTheta_alt2(lep_minus_p4, lep_plus_p4, gamma_p4);
  double costheta_alt2 = llg::get_costheta_alt2(lep_minus_p4, lep_plus_p4, gamma_p4);
  double phi_alt2 = llg::get_phi_alt2(lep_minus_p4, lep_plus_p4, gamma_p4);
  std::cout<<"[alt2] cosTheta: "<<cosTheta_alt2<<std::endl;
  std::cout<<"[alt2] costheta: "<<costheta_alt2<<std::endl;
  std::cout<<"[alt2] cosphi: "<<cos(phi_alt2)<<std::endl;
  std::cout<<"[alt2] sinphi: "<<sin(phi_alt2)<<std::endl;
  return 0;
}
