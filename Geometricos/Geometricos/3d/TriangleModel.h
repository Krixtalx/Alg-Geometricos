
/*
 * File:   TriangleModel.h
 * Author: lidia
 *
 * Created on 20 de febrero de 2021, 10:41
 */

#ifndef TRIANGLEMODEL_H
#define TRIANGLEMODEL_H

#include <assimp/scene.h>
#include <assimp/mesh.h>

#include <string>
#include <vector>
#include "Triangle3d.h"
#include "PointCloud3d.h"
#include "Vect3d.h"

class TriangleModel {

	friend class DrawTriangleModel;

private:
	//aiMesh* vmesh;
	std::vector<Vect3d> vv;  // vector de vértices
	std::vector<Vect3d> vn;  // vector de normales
	std::vector<unsigned> vi; //vector de índices

	void loadFile(std::string pathfile);
	void processMeshAssimp(aiMesh* mesh, const aiScene* scene);
	void processNodeAssimp(aiNode* node, const aiScene* scene);

public:
	TriangleModel(std::string pathfile);
	TriangleModel(const TriangleModel& orig);
	virtual ~TriangleModel();
	Triangle3d getFace(int i);
	unsigned numTriangulos();
	std::vector<Triangle3d> getFaces();
	PointCloud3d getCloud();
	AABB getAABB();
};

#endif /* TRIANGLEMODEL_H */

