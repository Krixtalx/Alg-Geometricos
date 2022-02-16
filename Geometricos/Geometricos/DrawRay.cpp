
#include "Point.h"
#include "DrawRay.h"



DrawRay::DrawRay (RayLine &t): dt (t), Draw(){
    Point orig = t.getA();
    Point dest = t.getPoint(this->MAXVAL_T);
    _vertices.push_back(glm::vec3(orig.getX(), orig.getY(), 0));
    _vertices.push_back(glm::vec3(dest.getX(), dest.getY(), 0));

    _normals.push_back(glm::vec3(0, 0, 1));
    _normals.push_back(glm::vec3(0, 0, 1));


    _indices.push_back(0);
    _indices.push_back(1);
    buildVAO ();
    
}


void DrawRay::drawIt (TypeColor c){
    setColorActivo (c);
    drawIt();
}


void DrawRay::drawIt (){
    setShaderProgram ( "algeom" );
    setDrawMode(TypeDraw::LINE );
    Scene::getInstance ()->addModel ( this );
}

