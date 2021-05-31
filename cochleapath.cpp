#include "cochleapath.h"
#include <QString>
#include <QStringList>
#include <QFile>
#include <QDebug>


// This class is used to build a visual display of the path and field

CochleaPath::CochleaPath(QString file_path_name, chai3d::cVector3d &pos, chai3d::cWorld *world, chai3d::cMatrix3d &global_frame)
{
    path = new chai3d::cShapeSphere(.25);
    world->addChild(path); // Add the path to the world
    path->setLocalPos(pos);
    path->setUseTransparency(true, true);
    path->setTransparencyLevel(1);// 1 is fully visible
    filename = file_path_name;

    global_base_frame_rot_mat = global_frame;

    readPathFile();
    buildPath();

}

CochleaPath::~CochleaPath(){

}

void CochleaPath::readPathFile(){

    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
       qDebug() << "ERROR LOADING FILE!";
       return;
    }

    // Load and read the file
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString full_line = in.readLine();
        QStringList linevals = full_line.split(',');

        // Transform into the table frame
        chai3d::cVector3d cur_points_loc = global_base_frame_rot_mat*chai3d::cVector3d(linevals[0].toDouble(),linevals[1].toDouble(),linevals[2].toDouble());
        chai3d::cVector3d cur_Field = global_base_frame_rot_mat*chai3d::cVector3d(linevals[3].toDouble(),linevals[4].toDouble(),linevals[5].toDouble());
        point_locs.push_back(cur_points_loc);
        field.push_back(cur_Field);
    }

//    center;

}

void CochleaPath::createPathFieldArrow(chai3d::cVector3d point_loc, chai3d::cVector3d field){

    // Field point
    chai3d::cShapeSphere *arrow_loc_point = new chai3d::cShapeSphere(0.15);
    arrow_loc_point->setLocalPos(point_loc);
    arrow_loc_point->setUseTransparency(true, false);
    arrow_loc_point->setTransparencyLevel(1);
    arrow_loc_point->m_material->setRed();
    path->addChild(arrow_loc_point);


    // Field arrow
    chai3d::cMesh *arrow = new chai3d::cMesh();
    chai3d::cCreateArrow(arrow, 0.55, 0.05, 0.2, 0.12, false, 32, field, point_loc);
    arrow->setUseTransparency(true, false);
    arrow->setTransparencyLevel(1);
    path->addChild(arrow);
}

void CochleaPath::buildPath(){
    for (int i=0; i<point_locs.size();i++){
        createPathFieldArrow(point_locs[i], field[i]);
    }
}

void CochleaPath::scaleSize(double scale_factor){
   path->scale(scale_factor);
}

void CochleaPath::scaleOriginal(){
   path->scale(1);
}
