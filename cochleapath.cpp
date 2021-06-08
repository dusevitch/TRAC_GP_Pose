#pragma once
#include "cochleapath.h"
#include <QString>
#include <QStringList>
#include <QFile>
#include <QDebug>
#include "functions.cpp"

// This class is used to build a visual display of the path and field

CochleaPath::CochleaPath(QString file_path_name)
{
    filename = file_path_name;
    readPathFile();
}

CochleaPath::CochleaPath(QString file_path_name, chai3d::cVector3d &pos, chai3d::cWorld *world, polarisTransformMatrix *input_mag_frame, chai3d::cVector3d mag_offset)
{
    path = new chai3d::cShapeSphere(.25);
    world->addChild(path); // Add the path to the world
    path->setLocalPos(pos);
    path->setUseTransparency(true, true);
    path->setTransparencyLevel(1);// 1 is fully visible
    filename = file_path_name;

    mag_frame = input_mag_frame;
    mag_frame_rot_mat = mag_frame->rot_mat;

    mag_offset_vec = mag_offset;

    readPathFile();
    buildPath();

}

CochleaPath::~CochleaPath(){

}

void CochleaPath::readPathFile()
{
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
       qDebug() << "ERROR LOADING FILE!";
       return;
    }
    // Load and read the file
    QTextStream in(&file);
    //printMatrix3d(mag_frame_rot_mat, "mag_frame_rot_mat");
    //printMatrix3d(global_frame_rot_mat, "global_frame_rot_mat");

    while (!in.atEnd()) {
        QString full_line = in.readLine();
        QStringList linevals = full_line.split(',');


        // TODO -> this transformation should be in terms of the magnet frame, not the global base frame, this will make it more accurate
        // Transform into the table frame
//        chai3d::cVector3d cur_points_loc = global_frame_rot_mat*chai3d::cVector3d(linevals[0].toDouble(),linevals[1].toDouble(),linevals[2].toDouble());
//        chai3d::cVector3d cur_Field = global_frame_rot_mat*chai3d::cVector3d(linevals[3].toDouble(),linevals[4].toDouble(),linevals[5].toDouble());


        // load the init position
        chai3d::cVector3d cur_points_loc_init = chai3d::cVector3d(linevals[0].toDouble(),linevals[1].toDouble(),linevals[2].toDouble());
        chai3d::cVector3d cur_Field_init = chai3d::cVector3d(linevals[3].toDouble(),linevals[4].toDouble(),linevals[5].toDouble());

        Eigen::Vector3d cur_points_loc_eig = Eigen::Vector3d(cur_points_loc_init.x(),cur_points_loc_init.y(),cur_points_loc_init.z());
        Eigen::Vector3d cur_Field_eig = Eigen::Vector3d(cur_Field_init.x(),cur_Field_init.y(),cur_Field_init.z());
        init_point_locs.push_back(cur_points_loc_eig);
        init_field.push_back(cur_Field_eig);


        //update current position with frame rotation

        current_point_locs.push_back(cur_points_loc_eig);
        current_field.push_back(cur_Field_eig);
    }
    updateFieldPath(mag_frame);
}

void CochleaPath::updateFieldPath(polarisTransformMatrix *mag_frame){

    //Update Path position based on mag rotation
    path->setLocalRot(mag_frame->rot_mat);
    path->setLocalPos(mag_frame->pos + mag_offset_vec);

    // Compute the current point locs and field path
    for(int i=0;i<init_point_locs.size();i++){
        current_point_locs[i] = cVector3dToVector3d(mag_frame->rot_mat*init_point_locs[i]);
        current_field[i] = cVector3dToVector3d(mag_frame->rot_mat*init_field[i]);
    }

}

void CochleaPath::exportFieldArrowCSV(QString textFile) // Assuming the magnet is already in position
{
    QFile file(textFile);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream stream(&file);

    // Export the current field to file
    for (int i =0;i<current_field.size();i++){
        qDebug() << current_field[i][0]<< "," << current_field[i][1]<< "," <<current_field[i][2]<< "," << 0.25+(i*0.25)  << "," <<0.25+(i*0.25) << endl;
        stream << current_field[i][0]<< "," << current_field[i][1]<< "," <<current_field[i][2]<< "," << 0.25+(i*0.25)  << "," <<0.25+(i*0.25) << endl;
    }
    file.close();
}

void CochleaPath::createPathFieldArrow(chai3d::cVector3d point_loc, chai3d::cVector3d field){

    // Field point
    chai3d::cShapeSphere *arrow_loc_point = new chai3d::cShapeSphere(0.15);
    arrow_loc_point->setLocalPos(point_loc);
    arrow_loc_point->setUseTransparency(true, false);
    arrow_loc_point->setTransparencyLevel(1);
    arrow_loc_point->m_material->setRed();
    path->addChild(arrow_loc_point);
    arrow_point.push_back(arrow_loc_point);

    // Field arrow
    chai3d::cMesh *arrow = new chai3d::cMesh();
    //chai3d::cCreateArrow(arrow, 0.55, 0.05, 0.2, 0.12, false, 32, field, point_loc);
    chai3d::cCreateArrow(arrow, 5, 0.5, 2, 1.2, false, 32, field, point_loc);
    arrow->setUseTransparency(true, false);
    arrow->setTransparencyLevel(1);
    path->addChild(arrow);
    arrow_vector.push_back(arrow);
}

void CochleaPath::buildPath(){
    for (int i=0; i<init_point_locs.size();i++){
        createPathFieldArrow(init_point_locs[i], init_field[i]);
    }

//    qDebug() << "Point LOCS";
//    for (int i=0; i<point_locs.size();i++){
//        printVector3d(point_locs[i],QString::number(i));
//    }

//    // print all children
//    qDebug() << "CHILDREN OF PATH";
//    for (int i=0; i<point_locs.size();i++){
//        printVector3d(path->getChild(i)->getLocalPos(),QString::number(i));
//    }
}

void CochleaPath::scaleSize(double scale_factor){
   path->scale(scale_factor);
}

void CochleaPath::scaleOriginal(){
   path->scale(1);
}
