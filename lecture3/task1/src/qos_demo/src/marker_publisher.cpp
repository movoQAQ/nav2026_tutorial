#include <chrono>
#include <cstddef>
#include <functional>
#include <memory>
#include <stdexcept>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "visualization_msgs/msg/marker.hpp"
#include "visualization_msgs/msg/marker_array.hpp"

using namespace std::chrono_literals;

class MarkerPublisher : public rclcpp::Node
{
public:
  MarkerPublisher() : Node("marker_publisher")
  {
    const auto reliability = declare_parameter<std::string>("reliability", "best_effort");
    const auto durability = declare_parameter<std::string>("durability", "volatile");
    const auto depth = declare_parameter<int>("depth", 10);
    publish_once_ = declare_parameter<bool>("publish_once", false);

    if (depth <= 0) {
      throw std::invalid_argument("depth must be greater than zero");
    }

    rclcpp::QoS qos{rclcpp::KeepLast(static_cast<std::size_t>(depth))};
    if (reliability == "reliable") {
      qos.reliable();
    } else if (reliability == "best_effort") {
      qos.best_effort();
    } else {
      throw std::invalid_argument("reliability: use reliable or best_effort");
    }

    if (durability == "transient_local") {
      qos.transient_local();
    } else if (durability == "volatile") {
      qos.durability_volatile();
    } else {
      throw std::invalid_argument("durability: use transient_local or volatile");
    }

    publisher_ = create_publisher<visualization_msgs::msg::MarkerArray>(
      "/visualization_marker_array", qos);

    // First publish happens about one second after startup.
    timer_ = create_wall_timer(1s, std::bind(&MarkerPublisher::publish_marker, this));
    RCLCPP_INFO(
      get_logger(), "QoS: reliability=%s durability=%s depth=%ld publish_once=%s",
      reliability.c_str(), durability.c_str(), depth, publish_once_ ? "true" : "false");
  }

private:
  void publish_marker()
  {
    visualization_msgs::msg::Marker marker;
    marker.header.frame_id = "map";
    marker.header.stamp = now();
    marker.ns = "qos_demo";
    marker.id = 0;
    marker.type = visualization_msgs::msg::Marker::SPHERE;
    marker.action = visualization_msgs::msg::Marker::ADD;
    marker.pose.position.x = 1.0;
    marker.pose.position.y = 2.0;
    marker.pose.position.z = 0.15;
    marker.pose.orientation.w = 1.0;  // Valid identity quaternion.
    marker.scale.x = 0.3;
    marker.scale.y = 0.3;
    marker.scale.z = 0.3;
    marker.color.r = 0.2f;
    marker.color.g = 0.7f;
    marker.color.b = 0.3f;
    marker.color.a = 1.0f;

    visualization_msgs::msg::MarkerArray markers;
    markers.markers.push_back(marker);
    publisher_->publish(markers);
    RCLCPP_INFO(get_logger(), "Published one MarkerArray; stamp=%d", marker.header.stamp.sec);

    if (publish_once_) {
      timer_->cancel();
      RCLCPP_INFO(get_logger(), "No more publishing; keep this node running for late subscribers.");
    }
  }

  bool publish_once_{false};
  rclcpp::Publisher<visualization_msgs::msg::MarkerArray>::SharedPtr publisher_;
  rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  try {
    rclcpp::spin(std::make_shared<MarkerPublisher>());
  } catch (const std::exception & error) {
    RCLCPP_ERROR(rclcpp::get_logger("qos_demo"), "%s", error.what());
    rclcpp::shutdown();
    return 1;
  }
  rclcpp::shutdown();
  return 0;
}