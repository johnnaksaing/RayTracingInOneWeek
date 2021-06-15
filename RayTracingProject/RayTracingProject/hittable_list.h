#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include <memory>
#include <vector>

#include "hittable.h"

class hittable_list : public hittable {
public:
	std::vector<std::shared_ptr<hittable>> objects;
public:
	hittable_list() = default;
	hittable_list(std::shared_ptr<hittable> object) { add(object); }

	void add(std::shared_ptr<hittable> object) { objects.push_back(object); }

	virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;

};

bool hittable_list::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
	hit_record rec_temp;
	bool hit_anything = false;
	auto closest = t_max;

	for (const auto& object : objects) {
		if (object->hit(r, t_min, closest, rec_temp)) {
			hit_anything = true;
			closest = rec_temp.t;
			rec = rec_temp;
		}
	}

	return hit_anything;
}

#endif // !HITTABLE_LIST_H

