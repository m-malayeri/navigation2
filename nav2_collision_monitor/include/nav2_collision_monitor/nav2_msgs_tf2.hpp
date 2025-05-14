#pragma once

#include <nav2_msgs/msg/polygon_stamped.hpp>
#include <geometry_msgs/msg/point_stamped.hpp>
#include <tf2/transform_datatypes.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.hpp>

namespace tf2
{

template<>
inline
void doTransform(
  const nav2_msgs::msg::PolygonStamped &in,
  nav2_msgs::msg::PolygonStamped &out,
  const geometry_msgs::msg::TransformStamped &transform)
{
  out.header = transform.header;
  out.polygon.points.resize(in.polygon.points.size());

  for (size_t i = 0; i < in.polygon.points.size(); ++i) {
    geometry_msgs::msg::PointStamped point_in, point_out;
    point_in.header = in.header;
    point_in.point.x = in.polygon.points[i].x;
    point_in.point.y = in.polygon.points[i].y;
    point_in.point.z = in.polygon.points[i].z;

    tf2::doTransform(point_in, point_out, transform);

    out.polygon.points[i].x = point_out.point.x;
    out.polygon.points[i].y = point_out.point.y;
    out.polygon.points[i].z = point_out.point.z;
  }
}

}  // namespace tf2
