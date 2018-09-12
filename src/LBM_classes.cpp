#include "LBM_classes.h"
//#include "LBM_globvar.h"


Grid::~Grid() {
	cout << "\n Grid deleted. \n";
}

Solid_list::Solid_list(int choice, Grid& grid, double rotation_x, momentum_direction& e, FILE * parfile) {
	element.resize(Ncubedtot);
	fill(element.begin(), element.end(), 0);
	double xpos = 0.3;
	double ypos = 0.5;
	fprintf(parfile, "%e %e ", xpos, ypos);
	//for case 7-----
	double funcvalue = 0;
	int i = 0;
	double triangle_like = 16;
	double y_stretch = 0.6;
	double length = 20;
	double sizelimit = 10000;
	//--------------
	int ix = 0;
	int iy = 0;
	int iz = 0;
	int a = 0;
	int n = 0;
	int nnext;
	double xmid = 0;
	double ymid = 0;
	int surfacecheck = 0;
	string tempstr;
	double radius1;
	double radius2;
	double radiussq;
	double radiussqh;
	double distsq;
	//	dvec center;
	//	center.resize(3);
	//	Rotmat Rx;
	//	Rx(0, 0) = 1; Rx(0, 1) = 0; Rx(0, 2) = 0;
	//	Rx(1, 0) = 0; Rx(1, 1) = cos(rotation_x); Rx(2, 1) = -sin(rotation_x);
	//	Rx(2, 0) = 0; Rx(2, 1) = sin(rotation_x); Rx(2, 2) = sin(rotation_x);

	switch (choice) {
	case 1:	//sphere
		cout << "\n Sphere chosen! \n";
		cout << "\n Input radius: ";
		//cin >> radius1;
		radius1 = 11.;
		//		stringstream(tempstr) >> radius;
		//		if (radius1 * 2 > 1) {
		//			cout << "Radius too large! must be between 0 and 1";
		//			break;
		//		}
		cout << "\n Input center (x,y,z goes from (0,0,0) to (1,1,1)): ";
		//cin >> center[0];
		//cin >> center[1];
		//cin >> center[2];
		center[0] = (Nx - 1)*xpos;
		center[1] = (Ny - 1)*ypos;
		center[2] = (Nz - 1)*0.5;
		/*		getline(cin, tempstr);
		stringstream(tempstr) >> center[0];
		getline(cin, tempstr);
		stringstream(tempstr) >> center[1];
		getline(cin, tempstr);
		stringstream(tempstr) >> center[2];*/
		//		if ((center[0] > 1) || (center[1] > 1) || (center[2] > 1)) {
		//			cout << "Center outside of grid! must be between 0 and 1";
		//			break;
		//		}


		radiussq = radius1*radius1;
		radiussqh = (radius1 - sq3*latspace)*(radius1 - sq3*latspace);
		for (iz = 0; iz < Nz; iz++) {
			for (iy = 0; iy < Ny; iy++) {
				for (ix = 0; ix < Nx; ix++) {
					distsq = (grid.x[ix] - center[0])*(grid.x[ix] - center[0]) + (grid.y[iy] - center[1])*(grid.y[iy] - center[1]) + (grid.z[iz] - center[2])*(grid.z[iz] - center[2]);
					n = (ix + 1) + (iy + 1)*Nxtot + (iz + 1)*Nxtot*Nytot;
					if (distsq > radiussq)
						element[n] = -1;
					else
						element[n] = 1;
				}
			}
		}
		cout << "\n Created obstacle: Sphere! \n";
		n = 0;
		break;

	case 2:
		cout << "Cylinder chosen! \n Input radius: ";
		getline(cin, tempstr);
		stringstream(tempstr) >> radius1;
		if (radius1 * 2 > 1) {
			cout << "Radius too large! must be between 0 and 1";
			break;
		}
		radiussq = radius1*radius1;
		radiussqh = (radius1 + sq3*latspace)*(radius1 + sq3*latspace);
		xmid = floor(((double)Nx - 1.)*0.5);
		ymid = floor(((double)Ny - 1.)*0.5);
		n = 0;
		for (iz = 0; iz < Nz; iz++) {	// can optimize by doing this for 1 iz, then just copiyng it to all other places in the vector.
			for (iy = 0; iy < Ny; iy++) {
				for (ix = 0; ix < Nx; ix++) {
					distsq = (grid.x[ix] - grid.x[xmid])*(grid.x[ix] - grid.x[xmid]) + (grid.y[iy] - grid.y[ymid])*(grid.y[iy] - grid.y[ymid]);
					n = (ix + 1) + (iy + 1)*Nxtot + (iz + 1)*Nxtot*Nytot;
					if (distsq < radiussq)
						element[n] = -1;
					else
						element[n] = 1;
				}
			}
		}
		n = 0;
		break;
	case 3:
		cout << "\n Square pipe chosen! \n";
		cout << "flow in z direction \n";
		for (iz = 0; iz < Nz; iz++) {
			for (iy = 0; iy < Ny; iy++) {
				for (ix = 0; ix < Nx; ix++) {
					n = (ix + 1) + (iy + 1)*Nxtot + (iz + 1)*Nxtot*Nytot;
					if ((ix == 0) || (ix == Nx - 1) || (iy == 0) || (iy == Ny - 1))
						element[n] = 1;
					else
						element[n] = -1;
				}
			}
		}
		n = 0;
		break;

	case 4:
		cout << "Cylinder chosen! \n Input radius: ";
		getline(cin, tempstr);
		stringstream(tempstr) >> radius1;
		if (radius1 * 2 > 1) {
			cout << "Radius too large! must be between 0 and 1";
			break;
		}
		radiussq = radius1*radius1;
		radiussqh = (radius1 + sq3*latspace)*(radius1 + sq3*latspace);
		xmid = floor(((double)Nx - 1.)*0.5);
		ymid = floor(((double)Ny - 1.)*0.5);
		n = 0;
		for (iz = 0; iz < Nz; iz++) {	// can optimize by doing this for 1 iz, then just copiyng it to all other places in the vector.
			for (iy = 0; iy < Ny; iy++) {
				for (ix = 0; ix < Nx; ix++) {
					distsq = (grid.x[ix] - grid.x[xmid])*(grid.x[ix] - grid.x[xmid]) + (grid.y[iy] - grid.y[ymid])*(grid.y[iy] - grid.y[ymid]);
					n = (ix + 1) + (iy + 1)*Nxtot + (iz + 1)*Nxtot*Nytot;
					if (distsq < radiussq)
						element[n] = -1;
					else
						element[n] = 1;
				}
			}
		}

		cout << "\n Sphere chosen! \n";
		cout << "\n Input radius: ";
		cin >> radius2;
		//		stringstream(tempstr) >> radius;
		if (radius2 * 2 > radius1 * 2) {
			cout << "Radius too large! must be between 0 and " << radius1 * 2 << "\n";
			break;
		}
		cout << "\n Input center (x,y,z goes from (0,0,0) to (1,1,1)): ";
		cin >> center[0];
		cin >> center[1];
		cin >> center[2];
		if ((center[0] > 1) || (center[1] > 1) || (center[2] > 1)) {
			cout << "Center outside of grid! must be between 0 and 1";
			break;
		}

		n = 0;
		radiussq = radius2*radius2;
		radiussqh = (radius2 - sq3*latspace)*(radius2 - sq3*latspace);
		for (iz = 0; iz < Nz; iz++) {
			for (iy = 0; iy < Ny; iy++) {
				for (ix = 0; ix < Nx; ix++) {
					distsq = (grid.x[ix] - center[0])*(grid.x[ix] - center[0]) + (grid.y[iy] - center[1])*(grid.y[iy] - center[1]) + (grid.z[iz] - center[2])*(grid.z[iz] - center[2]);
					n = (ix + 1) + (iy + 1)*Nxtot + (iz + 1)*Nxtot*Nytot;
					if (distsq > radiussq)
						if (element[n] != 1)
							element[n] = -1;
						else
							element[n] = 1;
				}
			}
		}
		cout << "\n Created obstacle: Sphere! \n";
		break;

	case 5:
		cout << "Cylinder object chosen! \n Input radius: ";
		getline(cin, tempstr);
		stringstream(tempstr) >> radius1;
		//		if (radius1 * 2 > 1) {
		//			cout << "Radius too large! must be between 0 and 1";
		//			break;
		//		}
		radiussq = radius1*radius1;
		radiussqh = (radius1 + sq3*latspace)*(radius1 + sq3*latspace);
		xmid = ((double)Nx - 1.)*xpos;
		ymid = ((double)Ny - 1.)*ypos;
		n = 0;
		for (iz = 0; iz < Nz; iz++) {	// can optimize by doing this for 1 iz, then just copiyng it to all other places in the vector.
			for (iy = 0; iy < Ny; iy++) {
				for (ix = 0; ix < Nx; ix++) {
					distsq = ((double)grid.x[ix] - xmid)*((double)grid.x[ix] - xmid) + ((double)grid.y[iy] - ymid)*((double)grid.y[iy] - ymid);
					n = (ix + 1) + (iy + 1)*Nxtot + (iz + 1)*Nxtot*Nytot;
					if (distsq > radiussq)
						element[n] = -1;
					else
						element[n] = 1;
				}
			}
		}
		break;
	case 6:
		n = 0;
		for (iz = 0; iz < Nz; iz++) {
			for (iy = 0; iy < Ny; iy++) {
				for (ix = 0; ix < Nx; ix++) {
					n = (ix + 1) + (iy + 1)*Nxtot + (iz + 1)*Nxtot*Nytot;
					element[n] = -1;
				}
			}
		}
		n = 0;
		break;
	case 7: //dolphin case
		n = 0;
		double iytemp;
		double iztemp;
		center[0] = (Nx - 1)*0.5;
		center[1] = (Ny - 1)*0.5;
		center[2] = (Nz - 1)*0.5;
		for (iz = 0; iz < Nz; iz++) {
			for (iy = 0; iy < Ny; iy++) {
				for (ix = 0; ix < Nx; ix++) {
					n = (ix + 1) + (iy + 1)*Nxtot + (iz + 1)*Nxtot*Nytot;
					if (ix < (center[0] + length*0.5) && ix >(center[0] - length*0.5)) {
						funcvalue = 0;
						iytemp = (double(iy) - center[1])*cos(rotation_x) - (double(iz) - center[2])*sin(rotation_x);
						iztemp = (double(iy) - center[1])*sin(rotation_x) + (double(iz) - center[2])*cos(rotation_x);
						for (i = 1; i < 4; i++) { // changed from i = 0; i < 3 to i = 1; i < 4.
												  // deforms a sphere continuously to a triangle. higher m = more triangle:y.
							funcvalue += 1e-7*pow(abs(y_stretch*(iytemp)*cos(2. * pi*i / 3. + pi / 2) + (iztemp)*sin(2. * pi*i / 3. + pi / 2) - 1. / 3.), triangle_like);
						}
						if (funcvalue > sizelimit)
							element[n] = -1;
						else
							element[n] = 1;
					}
					else
						element[n] = -1;
				}
			}
		}


	default:
		cout << "\n Error. incorrect input for obstacle type. \n";
	}



	// Placing out surface points.
	for (iz = 0; iz < Nz; iz++) {	// can optimize by doing this for 1 iz, then just copiyng it to all other places in the vector.
		for (iy = 0; iy < Ny; iy++) {
			for (ix = 0; ix < Nx; ix++) {
				n = (ix + 1) + (iy + 1)*Nxtot + (iz + 1)*Nxtot*Nytot;
				if (element[n] == 1) {
					for (a = 0; a < 27; a++) {
						if (((ix + e(a, 0)) >= 0) && ((ix + e(a, 0)) < Nx) && ((iy + e(a, 1)) >= 0) && ((iy + e(a, 1)) < Ny) && ((iz + e(a, 2)) >= 0) && ((iz + e(a, 2)) < Nz)) {
							nnext = (ix + 1 + e(a, 0)) + (iy + 1 + e(a, 1))*Nxtot + (iz + 1 + e(a, 2))*Nxtot*Nytot;
							if (element[nnext] == -1) {
								element[n] = 0;
								break;
							}
						}
					}
				}
			}
		}
	}
}

Solid_list::~Solid_list() {
	//	element.clear;
	cout << "Object deleted. \n";
}
