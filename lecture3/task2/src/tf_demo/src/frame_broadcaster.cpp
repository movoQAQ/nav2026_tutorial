#include <chrono>
#include <cmath>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/transform_stamped.hpp"
#include "tf2/LinearMath/Quaternion.h"
#include "tf2_geometry_msgs/tf2_geometry_msgs.hpp"
#include "tf2_ros/transform_broadcaster.hpp"

using namespace std::chrono_literals;

class FrameBroadcaster : public rclcpp::Node
{
public:
  FrameBroadcaster() : Node("frame_broadcaster")
  {
    motion_ = this->declare_parameter<bool>("motion", false);
    start_time_ = this->now();
    broadcaster_ = std::make_unique<tf2_ros::TransformBroadcaster>(*this);
    timer_ = this->create_wall_timer(50ms, [this]() { broadcast(); });
  }

private:
  void broadcast()
  {
    constexpr double half_pi = 1.5707963267948966;
    const auto stamp = this->now();
    double x = 1.0;
    double y = 2.0;
    double yaw = half_pi;

    if (motion_) {
      const double theta = 0.4 * (stamp - start_time_).seconds();
      x = 1.0 + std::cos(theta);
      y = 2.0 + std::sin(theta);
      yaw = theta + half_pi;
    }

    geometry_msgs::msg::TransformStamped transform;
    transform.header.stamp = stamp;
    transform.header.frame_id = "map";
    transform.child_frame_id = "base_link";
    transform.transform.translation.x = x;
    transform.transform.translation.y = y;
    transform.transform.translation.z = 0.0;

    tf2::Quaternion q;
    q.setRPY(0.0, 0.0, yaw);
    q.normalize();
    transform.transform.rotation = tf2::toMsg(q);
    broadcaster_->sendTransform(transform);
  }

  bool motion_{false};
  rclcpp::Time start_time_;
  std::unique_ptr<tf2_ros::TransformBroadcaster> broadcaster_;
  rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<FrameBroadcaster>());
  rclcpp::shutdown();
  return 0;
}
