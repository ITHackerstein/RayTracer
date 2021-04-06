#pragma once

#include "../Materials/Material.hpp"
#include "../Utils/Math.hpp"
#include "Hittable.hpp"

class XYRect : public Hittable {
	public:
		XYRect() {}

		XYRect(Vec3 position, double width, double height, std::shared_ptr<Material> material):
			XYRect(position.x(), position.x() + width, position.y(), position.y() + height, position.z(), material) {}

		XYRect(double x0, double x1, double y0, double y1, double z, std::shared_ptr<Material> material):
			m_x0(x0), m_x1(x1), m_y0(y0), m_y1(y1), m_z(z), m_material(material) {}

		virtual bool intersects_ray(const Ray &, double tMin, double tMax, HitRecord &) const override;
		virtual bool bounding_box(AABB &bbox) const override;
		virtual void dump(int indent) const override;
	private:
		double m_x0, m_x1;
		double m_y0, m_y1;
		double m_z;
		std::shared_ptr<Material> m_material;
};

class XZRect : public Hittable {
	public:
		XZRect() {}

		XZRect(Vec3 position, double width, double height, std::shared_ptr<Material> material):
			XZRect(position.x(), position.x() + width, position.z(), position.z() + height, position.y(), material) {}

		XZRect(double x0, double x1, double z0, double z1, double y, std::shared_ptr<Material> material):
			m_x0(x0), m_x1(x1), m_z0(z0), m_z1(z1), m_y(y), m_material(material) {}

		virtual bool intersects_ray(const Ray &, double tMin, double tMax, HitRecord &) const override;
		virtual bool bounding_box(AABB &bbox) const override;
		virtual void dump(int indent) const override;
	private:
		double m_x0, m_x1;
		double m_z0, m_z1;
		double m_y;
		std::shared_ptr<Material> m_material;
};

class YZRect : public Hittable {
	public:
		YZRect() {}

		YZRect(Vec3 position, double width, double height, std::shared_ptr<Material> material):
			YZRect(position.y(), position.y() + width, position.z(), position.z() + height, position.x(), material) {}

		YZRect(double y0, double y1, double z0, double z1, double x, std::shared_ptr<Material> material):
			m_y0(y0), m_y1(y1), m_z0(z0), m_z1(z1), m_x(x), m_material(material) {}

		virtual bool intersects_ray(const Ray &, double tMin, double tMax, HitRecord &) const override;
		virtual bool bounding_box(AABB &bbox) const override;
		virtual void dump(int indent) const override;
	private:
		double m_y0, m_y1;
		double m_z0, m_z1;
		double m_x;
		std::shared_ptr<Material> m_material;
};
