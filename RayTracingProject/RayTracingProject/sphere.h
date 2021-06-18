#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vec3.h"

class sphere : public hittable {
public:
	point3 center;
	double radius;
	shared_ptr<material> material_ptr;

public:
	//sphere() : center(point3(0,0,0)), radius(0.0) {};
	sphere(point3 c, double r, shared_ptr<material> m) :center(c), radius(r), material_ptr(m) {};
	~sphere() {};
	
	virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;
};



/*	| --------------------> : det = 0
	| ---------***--------> : det = 1
	|       *       *
	|      *         *
	| --------------------> : det = 2
	|     *           *               */

//surface: (vec - center)^2 = r^2
//(P(t) - C)*(P(t) - C) = r^2
//(A + B*t - C)*(A+B*t-C) = r^2
//(B*B)*t^2 + (2B(A-C))*t + (A-C)^2-r^2 = 0
//discriminant of even
bool sphere::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
	vec3 AmC = r.origin() - center;
	auto BB = dot(r.direction(), r.direction());
	auto BAmC = dot(r.direction(), AmC);
	auto AmCAmC = AmC.length_squared() - radius * radius;

	auto det = BAmC * BAmC - BB * AmCAmC;

	//does root exist?
	if (det < 0) { return false; }

	//is root(nearest one) between t_min ~ t_min?
	auto sqrt_d = sqrt(det);

	// return (-BAmC - sqrt(det)) / BB; }
	auto root = (-BAmC - sqrt(det)) / BB;
	if (t_min > root || t_max < root) {
		root = (-BAmC + sqrt(det)) / BB;
		if (t_min > root || t_max < root) return false;
	}
	
	/*
		|          ****
		|       *     .P *  normal(outward to shpere)'s direction = P-C
		|      *     /    *
		|			/
		|     *    C       *
	*/
	// P: ray's point at auto(double) t
	// C: Center is given
	rec.p = r.at(root);
	rec.t = root;
	vec3 outward = vec3(r.at(root) - center) / radius;
	rec.set_face_normal(r,outward);
	rec.mat_ptr = material_ptr;

	return true;
}
#endif // !SPHERE_H