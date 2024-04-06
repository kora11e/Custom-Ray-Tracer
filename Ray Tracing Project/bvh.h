#ifndef BVH_H
#define BVH_H

#include "rtweekend.h"
#include "hittable.h"
#include "hittable_list.h"
#include "algorithm"

class bvh_node : public hittable {
public:
	bvh_node(const hittable_list& list) : bvh_node(list.objects, 0, list.objects.size()) {}

	bvh_node(const std::vector<shared_ptr<hittable>>& src_objects, size_t start, size_t end) {

	}

	bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
		if (!box.hit(r, ray_t))
			return false;

		bool hit_left = left->hit(r, ray_t, rec);
		bool hit_right = right->hit(r, interval(ray_t.min, hit_left ? rec.t : ray_t.max), rec);

		return hit_left || hit_right;
	}

	aabb bounding_box() const override { return bbox; }

private:
	shared_ptr<hittable> left;
	shared_ptr<hittable> right;
	aabb bbox;

	static bool box_compare(const shared_ptr<hittable> a, const shared_ptr<hittable> b, int axis_index) {
		return a->bounding_box().axis(axis_index).min < b->bounding_box().axis(axis_index).min;
	}

	static bool box_x_compare(const shared_ptr<hittable> a, const shared_ptr<hittable> b) {
		return box_compare(a, b, 0);
	}

	static bool box_y_compare(const shared_ptr<hittable> a, const shared_ptr<hittable> b) {
		return box_compare(a, b, 1);
	}
	static bool box_y_compare(const shared_ptr<hittable> a, const shared_ptr<hittable> b) {
		return box_compare(a, b, 2);
	}
};

#endif