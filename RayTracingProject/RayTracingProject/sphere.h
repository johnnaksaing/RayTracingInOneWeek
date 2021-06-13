#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vec3.h"

class sphere : public hittable {
public:
	point3 center;
	double radius;

public:
	sphere() {};
	sphere(point3 c, double r) :center(c), radius(r) {};
	~sphere() {};
	
	virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;
};


//surface: (vec - center)^2 = r^2
//(P(t) - C)*(P(t) - C) = r^2
//(A + B*t - C)*(A+B*t-C) = r^2
//(B*B)*t^2 + (2B(A-C))*t + (A-C)^2-r^2 = 0
//discriminant of even
/*	| --------------------> : det = 0
	| ---------***--------> : det = 1
	|       *       *
	|      *         *
	| --------------------> : det = 2
	|     *           *               */
bool sphere::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
	vec3 AmC = r.origin() - center;
	auto BB = dot(r.direction(), r.direction());
	auto BAmC = dot(r.direction(), AmC);
	auto AmCAmC = dot(AmC, AmC) - radius * radius;

	auto det = BAmC * BAmC - BB * AmCAmC;

	//does root exist?
	if (det < 0) { return false; }

	//is root(nearest one) between t_min ~ t_min?
	auto sqrt_d = sqrt(det);

	// return (-BAmC - sqrt(det)) / BB; }
	auto root = (-BAmC - sqrt(det)) / BB;
	if (t_min > root || t_max < root) {
		root = (-BAmC - sqrt(det)) / BB;
		if (t_min > root || t_max < root) return false;
	}
	
	rec.normal = vec3(r.at(root) - center)/radius;
	rec.p = r.at(root);
	rec.t = root;

	return true;
}
#endif // !SPHERE_H