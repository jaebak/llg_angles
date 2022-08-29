#ifndef ANGLES_ZGAMMA_H
#define ANGLES_ZGAMMA_H

#include "TLorentzVector.h"

namespace llg {

  // Variables used for defining kinematic angles presented in https://arxiv.org/pdf/1108.2274.pdf
  
  // Returns 4-momentum of q1 (quark from gluon-gluon fusion)
  //  Defined in Equation 4
  TLorentzVector get_q1(TLorentzVector const & llg_in) {
    TLorentzVector llg_p4 = llg_in;
    TVector3 htran = llg_p4.BoostVector();
    htran.SetZ(0);
    llg_p4.Boost(-1*htran);
    double pz, E;
    pz = llg_p4.Pz() + llg_p4.E();
    E  = llg_p4.E()  + llg_p4.Pz();
    TLorentzVector k1;
    k1.SetPxPyPzE(0,0,pz/2,E/2);
    k1.Boost(htran);
    return k1;
  }
  
  // Returns 4-momentum of q2 (quark from gluon-gluon fusion)
  //  Defined in Equation 5
  TLorentzVector get_q2(TLorentzVector const & llg_in) {
    TLorentzVector llg_p4 = llg_in;
    TVector3 htran = llg_p4.BoostVector();
    htran.SetZ(0);
    llg_p4.Boost(-1*htran);
    double pz, E;
    pz = llg_p4.Pz() - llg_p4.E();
    E  = llg_p4.E()  - llg_p4.Pz();
    TLorentzVector k2;
    k2.SetPxPyPzE(0,0,pz/2,E/2);
    k2.Boost(htran);
    return k2;
  }
  
  // Returns magnitude of Z candidate 3-momentum 
  //  Defined in Equation 7
  double get_lambdaZ(TLorentzVector const & llg_p4, TLorentzVector const & lep_minus_p4, TLorentzVector const & lep_plus_p4) {
    TLorentzVector ll_p4 = lep_minus_p4 + lep_plus_p4;
    return sqrt(pow(llg_p4.Dot(ll_p4)/llg_p4.M(),2)-pow(ll_p4.M(),2));
  }
  
  // Cosine of angle between lepton 1 and parent Z in Higgs frame 
  //  Defined in Equation 13
  double get_costheta(TLorentzVector const & llg, TLorentzVector const & lep_minus, TLorentzVector const & lep_plus) {
    double lambdaZ = get_lambdaZ(llg, lep_minus, lep_plus);
    double ctheta = llg.Dot(lep_plus-lep_minus)/(llg.M()*lambdaZ);
    if(ctheta > 1) ctheta = 0.999;
    if(ctheta <-1) ctheta = -0.999;
    return ctheta;
  }
  
  // Cosine of angle between incoming quarks and outgoing Zs in higgs frame 
  //  Defined in Equation 8
  double get_cosTheta(TLorentzVector const & llg, TLorentzVector const & lep_minus, TLorentzVector const & lep_plus) {
    TLorentzVector ll = lep_minus + lep_plus;
    TLorentzVector q1 = get_q1(llg);
    TLorentzVector q2 = get_q2(llg);
    double lambdaZ = get_lambdaZ(llg, lep_minus, lep_plus);
    double cosTheta = ll.Dot(q1-q2)/(llg.M()*lambdaZ);
    if(abs(cosTheta) > 1.01) std::cout << "ERROR: cTheta = " << cosTheta <<  std::endl;
    return cosTheta;
  }
  
  // Angle of the Z decay plane from the z-axis (defined in Equation 1) in the higgs frame
  //  Defined in Equation 21+22
  double get_phi(TLorentzVector const & llg, TLorentzVector const & lep_minus, TLorentzVector const & lep_plus) {
    TLorentzVector q1_p4 = get_q1(llg);
    TLorentzVector l1_p4 = lep_minus;
    TLorentzVector l2_p4 = lep_plus;
    TLorentzVector ll_p4 = lep_minus + lep_plus;
  
    // Boost l1, l2, q1, ll to llg frame
    TVector3 llgBoost = llg.BoostVector();
    l1_p4.Boost(-1*llgBoost);
    l2_p4.Boost(-1*llgBoost);
    q1_p4.Boost(-1*llgBoost);
    ll_p4.Boost(-1*llgBoost);
  
    TVector3 l1 = l1_p4.Vect();
    TVector3 l2 = l2_p4.Vect();
    TVector3 q1 = q1_p4.Vect();
    TVector3 ll  = ll_p4.Vect();
  
    double sinTheta = sqrt(1-pow(get_cosTheta(llg, lep_minus, lep_plus),2));
    double cosphi, sinphi;
    cosphi = -1*l1.Cross(l2).Dot(q1.Cross(ll))/l1.Cross(l2).Mag()/q1.Cross(ll).Mag();
    sinphi = -1*l1.Cross(l2).Dot(q1)/l1.Cross(l2).Mag()/q1.Mag()/sinTheta;
    double phi(0);
    if(abs(cosphi) > 1.01) std::cout << "ERROR: cphi = " << cosphi <<  std::endl;
    if(cosphi > 1) cosphi = 1;
    if(cosphi < -1) cosphi = -1;
    if(sinphi < 0) phi = -1*acos(cosphi);
    else           phi = acos(cosphi);
    return phi;
  }

}

#endif
