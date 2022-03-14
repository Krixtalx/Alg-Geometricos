
/* 
 * File:   DrawCloud3d.cpp
 * Author: lidia
 * 
 * Created on 28 de enero de 2021, 12:27
 */

#include "DrawCloud3d.h"


DrawCloud3d::DrawCloud3d (PointCloud3d &t): dt (t), Draw(){
    auto v = t.getPoints();
    for (auto el : v) {
        _vertices.push_back(el.toGLM());
    }
    
    for (size_t i = 0; i < _vertices.size(); i++) {
        _indices.push_back(i);
        _normals.push_back({ 1, 0, 0 });
    }

    buildVAO ();
    
}



void DrawCloud3d::drawIt (TypeColor c){
    setColorActivo (c);
    drawIt();
}


void DrawCloud3d::drawIt (){
    setShaderProgram ( "algeom" );
    setDrawMode(TypeDraw::POINT );
    Scene::getInstance ()->addModel ( this );
    
}

