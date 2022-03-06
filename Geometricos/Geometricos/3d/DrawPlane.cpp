
/* 
 * File:   DrawPlane.cpp
 * Author: lidia
 * 
 * Created on 28 de enero de 2021, 17:11
 */


#include "DrawPlane.h"




DrawPlane::DrawPlane (Plane &t): dt (t), Draw(){
    
    
    //XXXX


     buildVAO ();
    
}


void DrawPlane::drawIt (TypeColor c){
    setColorActivo (c);
    drawIt();
}


void DrawPlane::drawIt (){
    setShaderProgram ( "algeom" );
    setDrawMode(TypeDraw::PolygonGeo);
    Scene::getInstance ()->addModel ( this );
    
}

