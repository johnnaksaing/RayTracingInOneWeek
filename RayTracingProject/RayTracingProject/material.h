#ifndef MATERIAL_H
#define MATERIAL_H

#include "utility.h"

// requirements of material
// Produce a scattered ray (or say it absorbed the incident ray).
// If scattered, say how much the ray should be attenuated.
struct hit_record;

class material {
public:
	virtual bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const = 0;
};

//scatters every direction with same radience
class lambertian : public material {
public:
	color albedo;

public:
	lambertian(const color& a) : albedo(a) {}

	virtual bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override {
		auto scatter_direction = rec.normal + random_in_unit_sphere();

		// Catch degenerate scatter direction
		if (scatter_direction.near_zero())
			scatter_direction = rec.normal;

		// Catch degenerate scatter direction
		scattered = ray(rec.p,scatter_direction);
		attenuation = albedo;
		return true;
	}
};

class metal : public material {
public:
	color albedo;
	double fuzziness;
public:
	metal(const color& a, double fuzz = 0.0) : albedo(a), fuzziness(fuzz < 1? fuzz : 1.0) {}

	virtual bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override {
		auto reflected_direction = reflect(unit_vector(r_in.direction()),rec.normal);

		// Catch degenerate scatter direction
		scattered = ray(rec.p, reflected_direction + fuzziness * random_in_unit_sphere());
		attenuation = albedo;

		return dot(scattered.direction(),rec.normal) > 0;
	}
};


#endif