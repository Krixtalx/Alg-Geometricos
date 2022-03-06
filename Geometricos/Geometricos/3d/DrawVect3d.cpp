#include "DrawVect3d.h"



DrawVect3d::DrawVect3d (Vect3d &p): dp (p), Draw(){
    
    _vertices.push_back (glm::vec3(p.getX(), p.getY(), p.getZ()));
    _normals.push_back ( glm::vec3 ( 0, 0, 1 ) );
    _indices.push_back(0);
    
    buildVAO ();
    
}

void DrawVect3d::drawIt (TypeColor c){
    setColorActivo (c);
    drawIt();
}



void DrawVect3d::drawIt (){
    setShaderProgram ( "algeom" );
    setDrawMode(TypeDraw::POINT );
    Scene::getInstance ()->addModel ( this );
    
}
