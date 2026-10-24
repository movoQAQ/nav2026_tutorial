#include <chrono>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/point_stamped.hpp"
#include "tf2/exceptions.h"
#include "tf2/time.h"
#include "tf2_geometry_msgs/tf2_geometry_msgs.hpp"
#include "tf2_ros/buffer.hpp"
#include "tf2_ros/transform_listener.hpp"

using namespace std::chrono_literals;

class PointListener : public rclcpp::Node
{
public:
  PointListener() : Node("point_listener")
  {
    buffer_ = std::make_unique<tf2_ros::Buffer>(this->get_clock());
    listener_ = std::make_unique<tf2_ros::TransformListener>(
      *buffer_, this, true);
    point_pub_ = this->create_publisher<geometry_msgs::msg::PointStamped>(
      "point_in_map", 10);
    timer_ = this->create_wall_timer(500ms, [this]() { convert_point(); });
  }

private:
  void convert_point()
  {
    try {
      // target first, source second; a zero timeout never blocks this callback.
      const auto transform = buffer_->lookupTransform(
        "map", "laser_frame", tf2::TimePointZero, tf2::durationFromSec(0.0));

      geometry_msgs::msg::PointStamped point_laser;
      point_laser.header.frame_id = "laser_frame";
      // This synthetic point is defined at the queried transform's time.
      point_laser.header.stamp = transform.header.stamp;
      point_laser.point.x = 1.0;
      point_laser.point.y = 0.0;
      point_laser.point.z = 0.0;

      geometry_msgs::msg::PointStamped point_map;
      tf2::doTransform(point_laser, point_map, transform);
      point_pub_->publish(point_map);
      RCLCPP_INFO(
        this->get_logger(), "laser (1, 0, 0) -> map (%.3f, %.3f, %.3f)",
        point_map.point.x, point_map.point.y, point_map.point.z);
    } catch (const tf2::TransformException & ex) {
      RCLCPP_WARN_THROTTLE(
        this->get_logger(), *this->get_clock(), 2000,
        "Waiting for map <- laser_frame: %s", ex.what());
    }
  }

  std::unique_ptr<tf2_ros::Buffer> buffer_;
  std::unique_ptr<tf2_ros::TransformListener> listener_;
  rclcpp::Publisher<geometry_msgs::msg::PointStamped>::SharedPtr point_pub_;
  rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<PointListener>());
  rclcpp::shutdown();
  return 0;
}
