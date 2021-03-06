#include "sphere.h"

#include <limits>

// ====================================================================
// ====================================================================

bool Sphere::intersect(const Ray &r, Hit &h) const
{
	const Vec3f &dir = r.getDirection();
	const Vec3f ori(r.getOrigin() - center);

	const double a = dir.Dot3(dir);
	const double b = 2 * dir.Dot3(ori);
	const double c = ori.Dot3(ori) - radius * radius;

	const double d = b * b - 4 * a * c;

	if (d < std::numeric_limits<double>::epsilon() ||
			fabs(d) <= std::numeric_limits<double>::epsilon())
		return false;

	const double t0 = (-b + sqrt(d)) / (2 * a);
	const double t1 = (-b - sqrt(d)) / (2 * a);
	assert(t0 >= t1);

	const double tf = (t1 >= 0) ? t1 : t0;
	if (tf < std::numeric_limits<double>::epsilon() || tf >= h.getT())
		return false;

	const Vec3f point(r.pointAtParameter(tf));
	const Vec3f normal(point - center);
	assert(normal.Length() > 0);
	h.set(tf, material, normal);
	return true;
}

// ====================================================================
// ====================================================================
