#include <chrono>
#include <functional>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "custom_interfaces/msg/robot_status.hpp"

class RobotStatusPublisher : public rclcpp::Node
{
public:
  RobotStatusPublisher() : Node("robot_status_publisher")
  {
    publisher_ = this->create_publisher<custom_interfaces::msg::RobotStatus>(
      "robot_status", 10);

    // Read the frequency once at startup.
    const double hz = this->declare_parameter<double>("publish_frequency", 1.0);
    const double safe_hz = hz > 0.0 ? hz : 1.0;
    const auto period = std::chrono::duration<double>(1.0 / safe_hz);

    timer_ = this->create_wall_timer(
      period, std::bind(&RobotStatusPublisher::timer_callback, this));
  }

private:
  void timer_callback()
  {
    custom_interfaces::msg::RobotStatus msg;
    msg.id = 1;
    msg.battery_level = 87.5f;
    msg.is_active = true;

    publisher_->publish(msg);
    RCLCPP_INFO(
      this->get_logger(), "发布: id=%d, 电量=%.2f%%, 激活状态=%s",
      msg.id, msg.battery_level, msg.is_active ? "true" : "false");
  }

  rclcpp::Publisher<custom_interfaces::msg::RobotStatus>::SharedPtr publisher_;
  rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<RobotStatusPublisher>());
  rclcpp::shutdown();
  return 0;
}
