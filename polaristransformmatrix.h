#ifndef POLARISTRANSFORMMATRIX_H
#define POLARISTRANSFORMMATRIX_H

#pragma once
#include <chai3d.h>
#include <Eigen/Dense>
#include <Eigen/Core>
struct polarisTransformMatrix{
    chai3d::cMatrix3d rot_mat = chai3d::cMatrix3d(1.0,0,0,0,1.0,0,0,0,1.0);
    chai3d::cMatrix3d inv_rot_mat = chai3d::cMatrix3d(1.0,0,0,0,1.0,0,0,0,1.0);
    chai3d::cVector3d pos = chai3d::cVector3d(-1000.0,-1000.0,-1000.0);
    Eigen::Matrix4d trans_mat = Eigen::MatrixXd::Identity(4,4);
    Eigen::Matrix4d inv_trans_mat = Eigen::MatrixXd::Identity(4,4);
    int polaris_num = -1;
};

#endif // POLARISTRANSFORMMATRIX_H
