#pragma once

#include "../Materials/Material.hpp"
#include "../Utils/Math.hpp"
#include "../Utils/Logging.hpp"
#include "Hittable.hpp"

class XYRect : public Hittable {
	public:
		XYRect() {}

		XYRect(double width, double height, std::shared_ptr<Material> material):
			m_width(width), m_height(height), m_material(material) {}

		virtual bool intersects_ray(const Ray &, double tMin, double tMax, HitRecord &) const override;
		virtual bool bounding_box(AABB &bbox) const override;
		virtual void dump(int indent) const override;
	private:
		double m_width;
		double m_height;
		std::shared_ptr<Material> m_material;
};

class XZRect : public Hittable {
	public:
		XZRect() {}

		XZRect(double width, double height, std::shared_ptr<Material> material):
			m_width(width), m_height(height), m_material(material) {}

		virtual bool intersects_ray(const Ray &, double tMin, double tMax, HitRecord &) const override;
		virtual bool bounding_box(AABB &bbox) const override;
		virtual void dump(int indent) const override;
	private:
		double m_width;
		double m_height;
		std::shared_ptr<Material> m_material;
};

class YZRect : public Hittable {
	public:
		YZRect() {}

		YZRect(double width, double height, std::shared_ptr<Material> material):
			m_width(width), m_height(height), m_material(material) {}

		virtual bool intersects_ray(const Ray &, double tMin, double tMax, HitRecord &) const override;
		virtual bool bounding_box(AABB &bbox) const override;
		virtual void dump(int indent) const override;
	private:
		double m_width;
		double m_height;
		std::shared_ptr<Material> m_material;
};
