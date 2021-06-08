// This is a functions file with various functions related to debugging and polaris transformation matrices

#include <QDebug>
#include <eigen3/Eigen/Dense>
#include <polaristransformmatrix.h>
#include <chai3d.h>
#include <cmath>
#include <iostream>
#include <string>


//#################### DEBUGGING ############################
static void printMatrix3d(chai3d::cMatrix3d matrix, std::string name)
{
    std::cout << "-------MATRIX: "<< name << " :---- " << std::endl;
    std::cout << matrix.getCol0().x() << ", " << matrix.getCol1().x() << ", " << matrix.getCol2().x() << std::endl;
    std::cout << matrix.getCol0().y() << ", " << matrix.getCol1().y() << ", " << matrix.getCol2().y() << std::endl;
    std::cout << matrix.getCol0().z() << ", " << matrix.getCol1().z() << ", " << matrix.getCol2().z() << std::endl;
    std::cout << "----------------" << std::endl;
}

static void printVector3d(chai3d::cVector3d vec, QString name)
{
    qDebug() << "Pos of " <<  name <<  " X: " << vec.x() << " Y: " << vec.y() << " Z: " << vec.z();
//    std::cout << "Pos of " <<  name.toStdString() <<  " X: " << vec.x() << " Y: " << vec.y() << " Z: " << vec.z() << std::endl;
}


//#################### CONVERTING TYPES ####################
static Eigen::Matrix3d chai3dToMatrix3d(chai3d::cMatrix3d matrix){
    Eigen::Matrix3d mat_out;
    mat_out << matrix(0,0), matrix(0,1),matrix(0,2),
            matrix(1,0), matrix(1,1), matrix(1,2),
            matrix(2,0), matrix(2,1), matrix(2,2);
    return mat_out;
}

static Eigen::Vector3d cVector3dToVector3d(chai3d::cVector3d vec){
    Eigen::Vector3d vec_out = Eigen::Vector3d(vec.x(), vec.y(),vec.z());
    return vec_out;
}

// ################### POLARIS TRACKING #####################

static Eigen::Matrix4d buildTransMatrix(chai3d::cMatrix3d rot, chai3d::cVector3d pos){
    Eigen::Matrix4d trans_mat;

    trans_mat << rot(0,0), rot(0,1), rot(0,2), pos(0),
                 rot(1,0), rot(1,1), rot(1,2), pos(1),
                 rot(2,0), rot(2,1), rot(2,2), pos(2),
                 0,           0,           0,      1;
    return trans_mat;
}

static void breakTransMat(Eigen::Matrix4d &trans_mat, chai3d::cMatrix3d rot, chai3d::cVector3d pos){
    // Rotation Matrix
    Eigen::Matrix3d rot_eig = trans_mat.topLeftCorner(3,3);
    rot = chai3d::cMatrix3d(rot_eig(0,0), rot_eig(0,1),rot_eig(0,2),rot_eig(1,0),rot_eig(1,1),rot_eig(1,2),rot_eig(2,0),rot_eig(2,1),rot_eig(2,2));

    // Position Vector
    pos = chai3d::cVector3d(rot_eig(3,0), rot_eig(3,1), rot_eig(3,2));
}

static Eigen::Matrix4d inverseTransformationMatrix(const Eigen::Matrix4d &trans_mat){
    // Remove the rotation and position matrices
    Eigen::Matrix3d rot = trans_mat.topLeftCorner(3,3);
    Eigen::Vector4d pos = trans_mat.col(3);

    // transpose of the rotation
    Eigen::Matrix3d rot_t = rot.transpose();

    // Generate inverse transformation matrix and return
    Eigen::Vector3d inv_pos = -rot_t*pos.head(3);
    Eigen::Matrix4d inv_trans_mat;
    inv_trans_mat << rot_t(0,0), rot_t(0,1), rot_t(0,2), inv_pos(0),
                     rot_t(1,0), rot_t(1,1), rot_t(1,2), inv_pos(1),
                     rot_t(2,0), rot_t(2,1), rot_t(2,2), inv_pos(2),
                     0,           0,           0,           1;

    return inv_trans_mat;
}

static polarisTransformMatrix* buildStructfromTransMatrix(Eigen::Matrix4d &trans_mat, int polaris_num){
    polarisTransformMatrix* pose_struct = new polarisTransformMatrix();

    // Rotation
    Eigen::Matrix3d rot_eig = trans_mat.topLeftCorner(3,3);
    pose_struct->rot_mat = chai3d::cMatrix3d(rot_eig(0,0), rot_eig(0,1),rot_eig(0,2),rot_eig(1,0),rot_eig(1,1),rot_eig(1,2),rot_eig(2,0),rot_eig(2,1),rot_eig(2,2));

    // Inverse Rotation
    chai3d::cMatrix3d inv_rot_mat;
    inv_rot_mat.copyfrom(pose_struct->rot_mat); //copy
    inv_rot_mat.trans();
    pose_struct->inv_rot_mat = inv_rot_mat;

    //Position
    Eigen::Vector4d pos_vec = trans_mat.col(3);
    pose_struct->pos = chai3d::cVector3d(pos_vec(0), pos_vec(1), pos_vec(2));

    // Transformation matrix and Inverse Transformation matrix
    pose_struct->trans_mat = trans_mat;
    pose_struct->inv_trans_mat = inverseTransformationMatrix(trans_mat);

    pose_struct->polaris_num = polaris_num;
    // Return and delete
    return pose_struct;
    delete pose_struct;
}
