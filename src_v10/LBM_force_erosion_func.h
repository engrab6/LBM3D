#pragma once
#include "LBM_input.h"
#include "LBM_classes.h"

void computestress(FILE * eronumb, momentum_direction& e, direction_density& ftemp, direction_density& f, EDF& feq, Solid_list& solid_list, Stresstensor& stresstensor, Normalvector& nhat, Wall_force& tau_stress, vector3Ncubed& F_sum, density& masschange, vectorNcubed& F_vdw, int i_er, int i_Fvdw, density& rho);
void computeVDWforce(int ix, int iy, int iz, momentum_direction& e, Solid_list& solid_list, vectorNcubed& F_vdw);
double VDWforce(int x, int y, int z);

void computetorque(Solid_list& solid_list, Wall_force& tau_stress, vector3Ncubed& torque);
dvec crossproduct(Wall_force& tau_stress, double r[3], int ix, int iy, int iz);

void erosion(Solid_list& solid_list, momentum_direction& e, vector3Ncubed& F_sum, density& rho, direction_density& f, int forcedirection, FILE * solfile, density& erodelist, Normalvector& nhat, vectorNcubed& ero_reso_check, vectorNcubed& F_vdw, FILE * errorfile);
void erodepoint(int ix, int iy, int iz, density& masschange, Solid_list& solid_list, density& rho, Normalvector& nhat, direction_density& f, momentum_direction& e);
int IsForeverAlone(int ix, int iy, int iz, Solid_list& solid_list, momentum_direction& e);