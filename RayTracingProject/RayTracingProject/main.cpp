#include "color.h"
#include "vec3.h"

#include "ray.h"

#include <iostream>

//surface: (vec - center)^2 = r^2
//(P(t) - C)*(P(t) - C) = r^2
//(A + B*t - C)*(A+B*t-C) = r^2
//(B*B)*t^2 + (2B(A-C))*t + (A-C)^2-r^2 = 0's det
/*	| --------------------> : det = 0
	| ---------***--------> : det = 1
	|       *       *
	|      *         *
	| --------------------> : det = 2
	|     *           *               */
double hit_sphere(const point3& center, double radius, const ray& r) {
	vec3 AmC = r.origin() - center;
	auto BB = dot(r.direction(),r.direction());
	auto BAmC = dot(r.direction(), AmC);
	auto AmCAmC = dot(AmC,AmC) - radius * radius;

	auto det = BAmC * BAmC - BB * AmCAmC;

	if (det < 0) { return -1; }
	else // equation's root(one with near-camaera) with even number
		{ return (-BAmC - sqrt(det)) / BB; }
}


//shpere: origin 0,0,-1, radius 0.5
color ray_color(const ray& r) {
	auto t = hit_sphere(point3(0,0,-1), 0.5, r);

	if (t > 0.0) {
		/*
			|          **** 
			|       *     .P *  normal(outward to shpere)'s direction = P-C
			|      *     /    *
			|			/
			|     *    C       *   
		*/
		// P: ray's point at auto(double) t
		// C: C is given
		vec3 normal = unit_vector(r.at(t) - vec3(0,0,-1));
		
		// normal: -1~1 , color: 0~1
		return 0.5*color(normal.x()+1, normal.y()+1, normal.z()+1);
	}
	
	vec3 unit_direction = unit_vector(r.direction());

	t = 0.5 * (unit_direction.y() + 1.0);
	return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

int main()
{
	// Image

	// make image ratio 16:9
	const auto aspect_ratio = 16.0 / 9.0;
	const int image_width = 400;
	const int image_height = static_cast<int>(image_width / aspect_ratio);

	// Camera

	auto viewport_height = 2.0;
	auto viewport_width = aspect_ratio * viewport_height;
	auto focal_length = 1.0;

	auto origin = point3(0, 0, 0);
	auto horizontal = vec3(viewport_width, 0, 0);
	auto vertical = vec3(0, viewport_height, 0);
	auto lower_left_corner = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focal_length);

	// Render

	std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

	for (int j = image_height - 1; j >= 0; --j) {
		std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
		for (int i = 0; i < image_width; ++i) {
			auto u = double(i) / (image_width - 1);
			auto v = double(j) / (image_height - 1);
			ray r(origin, lower_left_corner + u * horizontal + v * vertical - origin);
			color pixel_color = ray_color(r);
			write_color(std::cout, pixel_color);
		}
	}
	std::cerr << "\nDone.\n";

	return 0;
}