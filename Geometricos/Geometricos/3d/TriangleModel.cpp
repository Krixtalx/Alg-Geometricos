
/*
 * File:   TriangleModel.cpp
 * Author: lidia
 *
 * Created on 20 de febrero de 2021, 10:41
 */

#include "TriangleModel.h"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <stdexcept>
#include <string>
#include <iostream>
#include "../BasicGeometry.h"




TriangleModel::TriangleModel(const TriangleModel& orig) : vv(orig.vv), vn(orig.vn), vi(orig.vi) {
}

TriangleModel::~TriangleModel() {
}



TriangleModel::TriangleModel(std::string pathFile) {

	try {
		loadFile(pathFile);
	} catch (std::runtime_error& e) {
		std::string mensaje = "Model -> ";
		throw std::runtime_error(mensaje + e.what());
	}

}


void TriangleModel::loadFile(std::string pathfile) {
	//cleaning ();
	vv.clear();
	vi.clear();
	vn.clear();

	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(pathfile,
		aiProcess_JoinIdenticalVertices
		| aiProcess_Triangulate
		| aiProcess_GenSmoothNormals);
	//                                                 | aiProcess_GenNormals);

	   // Carga todo lo que haya en el archivo como un único modelo
	if (!scene || !scene->mRootNode
		|| (scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE)) {
		std::string mensaje = "cargarArchivo: error cargando el archivo "
			+ pathfile + " -> " + importer.GetErrorString();
		throw std::runtime_error(mensaje);
	}

	processNodeAssimp(scene->mRootNode, scene);

	//buildVAO ();

	//return *this;
}


/**
 * Método para procesar de manera recursiva un nodo de la estructura creada por
 * Assimp al cargar un archivo
 * @param nodo Nodo de la estructura de Assimp a procesar
 * @param escena Escena de Assimp con todo el contenido cargado del archivo
 * @note Al procesar el nodo de manera recursiva, no se garantiza que se llegue
 *       a un desbordamiento de pila
 */
void TriangleModel::processNodeAssimp(aiNode* node, const aiScene* scene) {
	for (int i = 0; i < node->mNumMeshes; i++) {
		//aiMesh* malla = scene->mMeshes[node->mMeshes[i]];
		// processMeshAssimp (malla, scene );
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		processMeshAssimp(mesh, scene);
	}

	for (int i = 0; i < node->mNumChildren; i++) {
		processNodeAssimp(node->mChildren[i], scene);
	}

}


/**
 * Carga en el modelo la geometría de una malla creada por Assimp al importar
 * un archivo
 * @param malla Malla creada por Assimp
 * @param escena Escena de Assimp con todo el contenido cargado del archivo
 * @post Carga vértices, normales, coordenadas de textura (si hubiera) e índices
 */
 //void TriangleModel::processMeshAssimp (  aiMesh* mesh, const aiScene* scene )
void TriangleModel::processMeshAssimp(aiMesh* mesh, const aiScene* scene) {
	Vect3d ve, no;
	//unsigned ind;

	std::cout << "mNumVertices" << mesh->mNumVertices << std::endl;
	for (int i = 0; i < mesh->mNumVertices; i++) {
		//      glm::vec3 v;
		//      v.x = mesh->mVertices[i].x;
		//      v.y = mesh->mVertices[i].y;
		//      v.z = mesh->mVertices[i].z;
		//      _vertices.push_back ( v );

		ve.setX(mesh->mVertices[i].x);
		ve.setY(mesh->mVertices[i].y);
		ve.setZ(mesh->mVertices[i].z);
		vv.push_back(ve);

		//      glm::vec3 n;
		//      n.x = mesh->mNormals[i].x;
		//      n.y = mesh->mNormals[i].y;
		//      n.z = mesh->mNormals[i].z;
		//      _normals.push_back ( n );
		no.setX(mesh->mNormals[i].x);
		no.setY(mesh->mNormals[i].y);
		no.setZ(mesh->mNormals[i].z);
		vn.push_back(no);



		//      if ( malla->mTextureCoords[0] )
		//      {
		//         glm::vec2 ct;
		//         ct.x = malla->mTextureCoords[0][i].x;
		//         ct.y = malla->mTextureCoords[0][i].y;
		//         _cTextura.push_back ( ct );
		//      }
	}

	std::cout << "mNumFaces: " << mesh->mNumFaces << std::endl;
	for (int i = 0; i < mesh->mNumFaces; i++) {
		aiFace cara = mesh->mFaces[i];
		for (int j = 0; j < cara.mNumIndices; j++) {
			//_indices.push_back ( cara.mIndices[j] );
			 //ind = cara.mIndices[j];
			vi.push_back(cara.mIndices[j]);
		}
	}

	//   for (int i=0; i<vi.size(); i++){
	//       std::cout << i << "->" ; 
	//       std::cout << vi[i*9]<< "/"   << vi[i*9+1]<< "/" <<  vi[i*9+1]<< " "; 
	//       std::cout << vi[i*9+3]<< "/" << vi[i*9+4]<< "/" <<  vi[i*9+5]<< " ";
	//       std::cout << vi[i*9+6]<< "/" << vi[i*9+7]<< "/" <<  vi[i*9+8]<< std::endl;
	//       
	//       Triangle3d t (ve[])
	//   }   

	std::cout << "tamaño de ve: " << vv.size() << std::endl;
	std::cout << "tamaño de vn: " << vn.size() << std::endl;
	std::cout << "tamaño de vi: " << vi.size() << std::endl;

}


Triangle3d TriangleModel::getFace(int i) {

	if (i > numTriangulos()) return (Triangle3d());

	Vect3d a = vv[vi[i * 3]];
	Vect3d b = vv[vi[i * 3 + 1]];
	Vect3d c = vv[vi[i * 3 + 2]];

	return Triangle3d(a, b, c);
}


std::vector<Triangle3d> TriangleModel::getFaces() {

	std::vector<Triangle3d> result;

	for (int i = 0; i < numTriangulos(); i++) {
		Vect3d a = vv[vi[i * 3]];
		Vect3d b = vv[vi[i * 3 + 1]];
		Vect3d c = vv[vi[i * 3 + 2]];

		Triangle3d tri(a, b, c);
		result.push_back(tri);
	}
	return result;
}


unsigned TriangleModel::numTriangulos() {

	return (unsigned)vi.size() / 3;

	std::cout << (unsigned)vi.size() / 3 << std::endl;
	//    std::cout << "vn " << vn.size() << std::endl;
	//    std::cout << "vv " << vv.size() << std::endl;
	//    
	//    return vi.size();

}



PointCloud3d TriangleModel::getCloud() {
	PointCloud3d pc(vv);
	return pc;
}

AABB TriangleModel::getAABB() {
	Vect3d min(FLT_MAX, FLT_MAX, FLT_MAX);
	Vect3d max(-FLT_MAX, -FLT_MAX, -FLT_MAX);
	for (auto p : vv) {
		min = { BasicGeometry::min2(min.getX(), p.getX()), BasicGeometry::min2(min.getY(), p.getY()) , BasicGeometry::min2(min.getZ(), p.getZ()) };
		max = { BasicGeometry::max2(max.getX(), p.getX()), BasicGeometry::max2(max.getY(), p.getY()) , BasicGeometry::max2(max.getZ(), p.getZ()) };
	}
	return AABB(min, max);
}

bool TriangleModel::rayTraversalExh(const Ray3d& r, Vect3d& point, Triangle3d& triangle) {
	float distance = FLT_MAX;
	Vect3d orig = r.getOrigin();
	Vect3d intersectPoint;
	bool result = false;
	auto triangles = this->getFaces();
	for (auto& t : triangles) {
		if (t.rayTri(r, intersectPoint)) {
			float newDistance = orig.distance(intersectPoint);
			if (newDistance < distance) {
				distance = newDistance;
				point = intersectPoint;
				triangle = t;
				result = true;
			}
		}
	}
	return result;
}

bool TriangleModel::rayTraversalExh(const Ray3d& r, std::vector<Vect3d>& points, std::vector<Triangle3d>& triangle) {
	Vect3d intersectPoint;
	bool result = false;
	auto triangles = this->getFaces();
	for (auto& t : triangles) {
		if (t.rayTri(r, intersectPoint)) {
			points.push_back(intersectPoint);
			triangle.push_back(t);
			result = true;
		}
	}
	return result;
}

bool TriangleModel::pointIntoMesh(const Vect3d& point) {
	int resultA, resultB, resultC;
	std::vector<Vect3d> points;
	std::vector<Triangle3d> triangles;
	Vect3d p(point);
	Vect3d newPoint(point.add(BasicGeometry::randomVector()));
	Ray3d ray(p, newPoint);
	rayTraversalExh(ray, points, triangles);
	resultA = points.size();
	points.clear();
	newPoint = (point.add(BasicGeometry::randomVector()));
	ray.setDestination(newPoint);
	rayTraversalExh(ray, points, triangles);
	resultB = points.size();

	if (resultA % 2 == resultB % 2)
		return resultA % 2;

	newPoint = (point.add(BasicGeometry::randomVector()));
	ray.setDestination(newPoint);
	points.clear();
	rayTraversalExh(ray, points, triangles);
	resultC = points.size();

	return resultC % 2;
}
