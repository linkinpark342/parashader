#ifndef _RADIOSITY_H_
#define _RADIOSITY_H_

#include "vectors.h"
#include "argparser.h"
#include <vector>

class Mesh;
class Face;
class Vertex;
class RayTracer;

class Radiosity {

public:

	// ========================
	// CONSTRUCTOR & DESTRUCTOR
	Radiosity(Mesh *m, ArgParser *args);
	~Radiosity();
	void Reset();
	void Cleanup();
	void ComputeFormFactors();
	void setRayTracer(RayTracer *r)
	{
		raytracer = r;
	}

	// =========
	// ACCESSORS
	Mesh* getMesh() const
	{
		return mesh;
	}
	double getFormFactor(int i, int j) const
	{
		// F_i,j radiant energy leaving i arriving at j
		assert(i >= 0 && i < num_faces);
		assert(j >= 0 && j < num_faces);
		assert(formfactors != NULL);
		return formfactors[i * num_faces + j];
	}
	double getArea(int i) const
	{
		assert(i >= 0 && i < num_faces);
		return area[i];
	}
	Vec3f getUndistributed(int i) const
	{
		assert(i >= 0 && i < num_faces);
		return undistributed[i];
	}
	Vec3f getAbsorbed(int i) const
	{
		assert(i >= 0 && i < num_faces);
		return absorbed[i];
	}
	Vec3f getRadiance(int i) const
	{
		assert(i >= 0 && i < num_faces);
		return radiance[i];
	}

	// =========
	// MODIFIERS
	double Iterate();
	void setFormFactor(int i, int j, double value)
	{
		assert(i >= 0 && i < num_faces);
		assert(j >= 0 && j < num_faces);
		assert(formfactors != NULL);
		formfactors[i * num_faces + j] = value;
	}
	void normalizeFormFactors(int i)
	{
		double sum = 0;
		int j;
		for (j = 0; j < num_faces; j++) {
			sum += getFormFactor(i, j);
		}
		if (sum == 0)
			return;
		for (j = 0; j < num_faces; j++) {
			setFormFactor(i, j, getFormFactor(i, j) / sum);
		}
	}
	void setArea(int i, double value)
	{
		assert(i >= 0 && i < num_faces);
		area[i] = value;
	}
	void setUndistributed(int i, Vec3f value)
	{
		assert(i >= 0 && i < num_faces);
		undistributed[i] = value;
	}
	void findMaxUndistributed();
	void setAbsorbed(int i, Vec3f value)
	{
		assert(i >= 0 && i < num_faces);
		absorbed[i] = value;
	}
	void setRadiance(int i, Vec3f value)
	{
		assert(i >= 0 && i < num_faces);
		radiance[i] = value;
	}
	void setVisibility(int i, int j, double v)
	{
		assert(i >= 0 && i < num_faces);
		assert(j >= 0 && j < num_faces);
		assert(visibilities != NULL);
		visibilities[i * num_faces + j] = v;
	}
	double getVisibility(int i, int j) const
	{
		assert(i >= 0 && i < num_faces);
		assert(j >= 0 && j < num_faces);
		assert(visibilities != NULL);
		return visibilities[i * num_faces + j];
	}

	// =====
	// PAINT
	void Paint(ArgParser *args);
	Vec3f whichVisualization(enum RENDER_MODE mode, Face *f, int i);
	void insertInterpolatedColor(int index, Face *f, Vertex *v);
	void insertColor(Vec3f v);

private:

	double form_factor(const Face *f_i, const Face *f_j) const;
	double visibility(const Face *f_i, const Face *f_j) const;
	void calculateVisibilities();

	// ==============
	// REPRESENTATION
	Mesh *mesh;
	ArgParser *args;
	int num_faces;
	RayTracer *raytracer;

	// a nxn matrix
	// F_i,j radiant energy leaving i arriving at j
	double *formfactors;

	// length n vectors
	double *area;
	double *visibilities;
	Vec3f *undistributed; // energy per unit area
	Vec3f *absorbed; // energy per unit area
	Vec3f *radiance; // energy per unit area

	int max_undistributed_patch; // the patch with the most undistributed energy
	double total_undistributed; // the total amount of undistributed light
	double total_area; // the total area of the scene
};

#endif
