/**
 * @file main.cpp
 *
 * @author lidia
 *
 * @brief Función main y callbacks
 */

#include <iostream>
#include <cstdlib>
#include <chrono>
#include "windows.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
 //#include <glm/gtx/transform.hpp>
#include "Scene.h"

#include "InclGeom2D.h"
#include "InclDraw2D.h"
#include "Bezier.h"
#include "DrawBezier.h"
#include "3d/Plane.h"
#include "3d/DrawPlane.h"
#include "3d/DrawLine3d.h"
#include "3d/DrawVect3d.h"
#include "3d/PointCloud3d.h"
#include "3d/DrawSegment3d.h"
#include "3d/DrawCloud3d.h"
#include "3d/DrawAABB.h"
#include "3d/TriangleModel.h"
#include "3d/DrawTriangleModel.h"
#include "3d/DrawTriangle3d.h"
#include "VoxelModel.h"
#include "DrawVoxelModel.h"
#include <pcl/ModelCoefficients.h>
#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>
#include <pcl/io/ply_io.h>
#include <pcl/filters/extract_indices.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/features/normal_3d.h>
#include <pcl/search/kdtree.h>
#include <pcl/sample_consensus/method_types.h>
#include <pcl/sample_consensus/model_types.h>
#include <pcl/segmentation/sac_segmentation.h>
#include <pcl/segmentation/extract_clusters.h>
#include "TDelaunay.h"
#include "DrawTDelaunay.h"
#include "ConvexHull3D.h"
#include "DrawConvexHull3D.h"


Movements movimientoActivo = Movements::NONE;
bool botonPulsado = false;
double ratonX = 0;
double ratonY = 0;
int modeloActivo = -1;
PointCloud3d* loadedCloud;

void mostrarAyuda() {
	std::cout << "Ayuda" << std::endl
		<< "================" << std::endl
		<< "S -> Esfera benchmark" << std::endl
		<< "M -> Esfera naive" << std::endl
		<< "N -> Esfera grid" << std::endl
		<< "P -> Olivos benchmark" << std::endl
		<< "K -> Olivos naive" << std::endl
		<< "L -> Olivos grid" << std::endl
		<< "Y -> PCL clustering" << std::endl
		<< "r -> Resetea la escena" << std::endl
		<< "Cursores y rueda ratón -> Rotación" << std::endl
		<< "h -> Muestra esta ayuda" << std::endl
		<< "q -> Cierra la aplicación" << std::endl;
}


void loadPointCloud() {
	Scene::getInstance()->clearScene();
	if (!loadedCloud) {
		loadedCloud = new PointCloud3d("olivosSubsample.ply");
	}
}


void refreshWindow(GLFWwindow* ventana) {
	try {
		Scene::getInstance()->refresh();
	} catch (std::runtime_error& e) {
		std::cout << "Exception on refeshWindow"
			<< std::endl
			<< "=============================================="
			<< std::endl
			<< e.what() << std::endl;
	}

	glfwSwapBuffers(ventana);
}


void callbackTamFB(GLFWwindow* ventana, int ancho, int alto) {
	Scene::getInstance()->changeTamViewport(ancho, alto);
}


// Implementado después de la función main
void callbackKey(GLFWwindow* ventana, int tecla, int scancode, int accion,
	int modificadores);


void callbackMouseButton(GLFWwindow* ventana, int boton, int accion,
	int modificadores) {
	if (boton == 0) {
		if (accion == GLFW_PRESS) {
			botonPulsado = true;
			glfwGetCursorPos(ventana, &ratonX, &ratonY);
		}

		if (accion == GLFW_RELEASE) {
			botonPulsado = false;
			ratonX = 0;
			ratonY = 0;
		}
	}
}


void callbackMouseMovevent(GLFWwindow* ventana, double posX, double posY) {
	static clock_t ultimaEjecucion = clock();   // Se inicializa una única vez

	movimientoActivo = Movements::ORBIT;

	if (botonPulsado)
		if ((clock() - ultimaEjecucion) > 10) {
			double incX = posX - ratonX;
			double incY = posY - ratonY;

			Scene::getInstance()->moveCamera(movimientoActivo, incY, incX);

			ratonX = posX;
			ratonY = posY;
			refreshWindow(ventana);
			ultimaEjecucion = clock();
			movimientoActivo = Movements::NONE;
		}
}


void callbackMouseWheel(GLFWwindow* ventana, double incX, double incY) {
	movimientoActivo = Movements::ZOOM;
	Scene::getInstance()->moveCamera(movimientoActivo, -incY);
	refreshWindow(ventana);
	movimientoActivo = Movements::NONE;
}


int main(int argc, char** argv) {
	std::cout << "Prácticas de algoritmos Geométricos" << std::endl;

	if (glfwInit() != GLFW_TRUE) {
		std::cout << "Fallo al inicializar GLFW" << std::endl;
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

	GLFWwindow* miVentana;
	miVentana = glfwCreateWindow(1024, 576, "Algoritmos Geométricos", nullptr, nullptr);

	if (miVentana == nullptr) {
		std::cout << "Fail wheb initializing GLFW" << std::endl;
		glfwTerminate();
		return -2;
	}

	glfwMakeContextCurrent(miVentana);

	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		std::cout << "Fail wheb initializing GLEW" << std::endl;
		glfwDestroyWindow(miVentana);
		glfwTerminate();
		return -3;
	}

	std::cout << glGetString(GL_RENDERER) << std::endl
		<< glGetString(GL_VENDOR) << std::endl
		<< glGetString(GL_VERSION) << std::endl
		<< glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

	glfwSetWindowRefreshCallback(miVentana, refreshWindow);
	glfwSetFramebufferSizeCallback(miVentana, callbackTamFB);
	glfwSetKeyCallback(miVentana, callbackKey);
	glfwSetMouseButtonCallback(miVentana, callbackMouseButton);
	glfwSetScrollCallback(miVentana, callbackMouseWheel);
	glfwSetCursorPosCallback(miVentana, callbackMouseMovevent);

	mostrarAyuda();

	try {
		Scene::getInstance()->setScene(1024, 576);


		while (!glfwWindowShouldClose(miVentana)) {
			glfwPollEvents();
		}
	} catch (std::runtime_error& e) {
		std::cout << "Excepction captured: " << e.what() << std::endl;
		glfwWindowShouldClose(miVentana);
	}

	std::cout << "End of application" << std::endl;
	glfwDestroyWindow(miVentana);
	miVentana = nullptr;
	glfwTerminate();
}


void callbackKey(GLFWwindow* ventana, int tecla, int scancode, int accion,
	int modificadores) {
	GLfloat f = 0;

	switch (tecla) {
	case GLFW_KEY_Q:
		if (accion == GLFW_PRESS) {
			glfwSetWindowShouldClose(ventana, GLFW_TRUE);
		}
		break;

	case GLFW_KEY_M:
		if (accion == GLFW_PRESS) {
			try {
				/*PointCloud p(1000, 20, 20);
				DrawPointCloud* cloud = new DrawPointCloud(p);
				cloud->drawIt({ 1, 0, 0, 1 });
				TDelaunay dt(p);*/
				TDelaunay dt("olivosSubsample.ply");
				DrawTDelaunay* draw = new DrawTDelaunay(dt);
				draw->drawIt({ 0, 0, 0, 1 });
			} catch (std::exception& e) {
				std::cout << "Exception captured in callbackKey"
					<< std::endl
					<< "===================================="
					<< std::endl
					<< e.what() << std::endl;
			}

			refreshWindow(ventana);
		}
		break;

	case GLFW_KEY_N:
		if (accion == GLFW_PRESS) {
			try {
				TriangleModel tri("vaca.obj");
				DrawTriangleModel* drawTM = new DrawTriangleModel(tri);
				drawTM->drawItPlain();
				ConvexHull3D convexHull(tri);
				DrawConvexHull3D* draw = new DrawConvexHull3D(convexHull);
				draw->drawIt({ 1,0,0,1 });
			} catch (std::exception& e) {
				std::cout << "Exception captured in callbackKey"
					<< std::endl
					<< "===================================="
					<< std::endl
					<< e.what() << std::endl;
			}

			refreshWindow(ventana);
		}
		break;

	case GLFW_KEY_S:
		if (accion == GLFW_PRESS) {
			try {
				int k = 27;
				int maxIteration = 500;
				int cloudSize = 5000;
				PointCloud3d cloud(cloudSize, 8);
				DrawCloud3d* drawCloud;

				//----------------------Naive---------------------------------

				auto start = std::chrono::high_resolution_clock::now();

				auto result = cloud.kmeans_naive(k, maxIteration);
				int id = 0;
				for (auto& cluster : result) {
					PointCloud3d c(cluster);
					drawCloud = new DrawCloud3d(c);
					drawCloud->drawIt(PointCloud3d::getClusterColor(id++, k));
				}

				auto end = std::chrono::high_resolution_clock::now();

				auto int_s = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

				std::cout << "Naive: " << int_s.count() << " ms" << std::endl << std::endl;

				refreshWindow(ventana);

				//----------------------Grid---------------------------------

				start = std::chrono::high_resolution_clock::now();
				auto result2 = cloud.kmeans_grid(k, maxIteration);
				id = 0;
				for (auto& cluster : result2) {
					PointCloud3d c(cluster);
					drawCloud = new DrawCloud3d(c);
					drawCloud->drawIt(PointCloud3d::getClusterColor(id++, k));
				}

				end = std::chrono::high_resolution_clock::now();

				int_s = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

				std::cout << "Grid: " << int_s.count() << " ms" << std::endl << std::endl;

			} catch (std::exception& e) {
				std::cout << "Exception captured on callbackKey"
					<< std::endl
					<< "===================================="
					<< std::endl
					<< e.what() << std::endl;
			}

			refreshWindow(ventana);
		}
		break;


	case GLFW_KEY_P:
		if (accion == GLFW_PRESS) {
			try {
				int k = 87;
				int maxIteration = 100;
				std::cout << "Comenzando lectura del fichero" << std::endl;
				loadPointCloud();

				int cloudSize = loadedCloud->size();

				DrawCloud3d* drawCloud;

				//----------------------Naive---------------------------------

				auto start = std::chrono::high_resolution_clock::now();

				auto result = loadedCloud->kmeans_naive(k, maxIteration);
				int id = 0;
				for (auto& cluster : result) {
					PointCloud3d c(cluster);
					drawCloud = new DrawCloud3d(c);
					drawCloud->drawIt(PointCloud3d::getClusterColor(id++, k));
				}

				auto end = std::chrono::high_resolution_clock::now();

				auto int_s = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

				std::cout << "Naive: " << int_s.count() << " ms" << std::endl << std::endl;

				refreshWindow(ventana);

				//----------------------Grid---------------------------------

				start = std::chrono::high_resolution_clock::now();
				auto result2 = loadedCloud->kmeans_grid(k, maxIteration);
				id = 0;
				for (auto& cluster : result2) {
					PointCloud3d c(cluster);
					drawCloud = new DrawCloud3d(c);
					drawCloud->drawIt(PointCloud3d::getClusterColor(id++, k));
				}

				end = std::chrono::high_resolution_clock::now();

				int_s = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

				std::cout << "Grid: " << int_s.count() << " ms" << std::endl << std::endl;

			} catch (std::exception& e) {
				std::cout << "Exception captured on callbackKey"
					<< std::endl
					<< "===================================="
					<< std::endl
					<< e.what() << std::endl;
			}

			refreshWindow(ventana);
		}
		break;
	case GLFW_KEY_K:
		if (accion == GLFW_PRESS) {
			try {
				int k = 87;
				int maxIteration = 100;
				std::cout << "Comenzando lectura del fichero" << std::endl;
				loadPointCloud();

				int cloudSize = loadedCloud->size();

				//----------------------Naive---------------------------------

				auto start = std::chrono::high_resolution_clock::now();

				loadedCloud->kmeans_naive_auto_update(k, maxIteration, ventana);

				auto end = std::chrono::high_resolution_clock::now();

				auto int_s = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

				std::cout << "Naive: " << int_s.count() << " ms" << std::endl << std::endl;

			} catch (std::exception& e) {
				std::cout << "Exception captured on callbackKey"
					<< std::endl
					<< "===================================="
					<< std::endl
					<< e.what() << std::endl;
			}

			refreshWindow(ventana);
		}
		break;

	case GLFW_KEY_L:
		if (accion == GLFW_PRESS) {
			try {
				int k = 87;
				int maxIteration = 100;
				std::cout << "Comenzando lectura del fichero" << std::endl;
				loadPointCloud();

				int cloudSize = loadedCloud->size();

				//----------------------Grid---------------------------------

				auto start = std::chrono::high_resolution_clock::now();

				loadedCloud->kmeans_grid_auto_update(k, maxIteration, ventana);

				auto end = std::chrono::high_resolution_clock::now();

				auto int_s = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

				std::cout << "Grid: " << int_s.count() << " ms" << std::endl << std::endl;

			} catch (std::exception& e) {
				std::cout << "Exception captured on callbackKey"
					<< std::endl
					<< "===================================="
					<< std::endl
					<< e.what() << std::endl;
			}

			refreshWindow(ventana);
		}
		break;

	case GLFW_KEY_Y:
		if (accion == GLFW_PRESS) {
			try {
				std::cout << "Comienzo lectura fichero PCL" << std::endl;
				// Read in the cloud data
				pcl::PLYReader reader;
				pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>), cloud_f(new pcl::PointCloud<pcl::PointXYZ>);
				reader.read("olivosSubsample.ply", *cloud);
				std::cout << "Cloud points number:" << cloud->size() << std::endl;
				// Creating the KdTree object for the search method of the extraction
				pcl::search::KdTree<pcl::PointXYZ>::Ptr tree(new pcl::search::KdTree<pcl::PointXYZ>);
				tree->setInputCloud(cloud);

				std::vector<pcl::PointIndices> cluster_indices;
				pcl::EuclideanClusterExtraction<pcl::PointXYZ> ec;
				ec.setClusterTolerance(1.0f);
				ec.setMinClusterSize(50);
				ec.setMaxClusterSize(1000);
				ec.setSearchMethod(tree);
				ec.setInputCloud(cloud);

				std::cout << "Comienzo clustering PCL" << std::endl;
				ec.extract(cluster_indices);

				std::cout << "Clustering PCL: " << cluster_indices.size() << " clusters" << std::endl;
				int j = 0;
				for (std::vector<pcl::PointIndices>::const_iterator it = cluster_indices.begin(); it != cluster_indices.end(); ++it) {
					pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_cluster(new pcl::PointCloud<pcl::PointXYZ>);
					for (const auto& idx : it->indices)
						cloud_cluster->push_back((*cloud)[idx]);
					cloud_cluster->width = cloud_cluster->size();
					cloud_cluster->height = 1;
					cloud_cluster->is_dense = true;

					std::cout << "PointCloud representing the Cluster: " << cloud_cluster->size() << " data points." << std::endl;
					std::stringstream ss;
					ss << "cloud_cluster_" << j << ".ply";
					pcl::io::savePLYFileBinary(ss.str(), *cloud_cluster);
					j++;
				}

			} catch (std::exception& e) {
				std::cout << "Exception captured on callbackKey"
					<< std::endl
					<< "===================================="
					<< std::endl
					<< e.what() << std::endl;
			}

			refreshWindow(ventana);
		}
		break;

	case GLFW_KEY_R:
		Scene::getInstance()->clearScene();
		refreshWindow(ventana);
		break;

	case GLFW_KEY_1:
		if (accion == GLFW_PRESS) {
			Scene::getInstance()->setView(TypeView::PLANT);

			refreshWindow(ventana);
		}
		break;
	case GLFW_KEY_2:
		if (accion == GLFW_PRESS) {
			Scene::getInstance()->setView(TypeView::ELEVATION);

			refreshWindow(ventana);
		}
		break;
	case GLFW_KEY_3:
		if (accion == GLFW_PRESS) {
			Scene::getInstance()->setView(TypeView::PROFILE);

			refreshWindow(ventana);
		}
		break;
	case GLFW_KEY_4:
		if (accion == GLFW_PRESS) {
			Scene::getInstance()->setView(TypeView::ISOMETRIC);

			refreshWindow(ventana);
		}
		break;
	case GLFW_KEY_H:
		if (accion == GLFW_PRESS) {
			mostrarAyuda();
		}
		break;

	case GLFW_KEY_LEFT:
		f = -1;
	case GLFW_KEY_RIGHT:
		f = (f != -1) ? 1 : f;
		if (accion == GLFW_PRESS) {
			switch (movimientoActivo) {
			case Movements::DOLLY:
				Scene::getInstance()->moveCamera(movimientoActivo, f, 0);
				break;
			case Movements::ORBIT:
				Scene::getInstance()->moveCamera(movimientoActivo, 0, 10 * f);
				break;
			case Movements::PAN:
				Scene::getInstance()->moveCamera(movimientoActivo, f);
				break;
			case Movements::ZOOM:
			case Movements::CRANE:
			case Movements::TILT:
			default:
				break;
			}
		}

		refreshWindow(ventana);
		break;
	case GLFW_KEY_UP:
		f = 1;
	case GLFW_KEY_DOWN:
		f = (f != 1) ? -1 : f;
		if (accion == GLFW_PRESS) {
			switch (movimientoActivo) {
			case Movements::TILT:
			case Movements::ZOOM:
				Scene::getInstance()->moveCamera(movimientoActivo, -f);
				break;
			case Movements::CRANE:
				Scene::getInstance()->moveCamera(movimientoActivo, f);
				break;
			case Movements::DOLLY:
				Scene::getInstance()->moveCamera(movimientoActivo, 0, -f);
				break;
			case Movements::ORBIT:
				Scene::getInstance()->moveCamera(movimientoActivo, -10 * f, 0);
				break;
			default:
				break;
			}
		}
		refreshWindow(ventana);
		break;


	}

	//std::cout << "The End" << std::endl;
}
