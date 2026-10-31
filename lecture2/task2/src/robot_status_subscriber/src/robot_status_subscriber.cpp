#include <functional>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "custom_interfaces/msg/robot_status.hpp"

class RobotStatusSubscriber : public rclcpp::Node
{
public:
  RobotStatusSubscriber() : Node("robot_status_subscriber")
  {
    subscription_ = this->create_subscription<custom_interfaces::msg::RobotStatus>(
      "robot_status", 10,
      std::bind(&RobotStatusSubscriber::topic_callback, this, std::placeholders::_1));
  }

private:
  void topic_callback(const custom_interfaces::msg::RobotStatus & msg) const
  {
    RCLCPP_INFO(
      this->get_logger(), "接收: id=%d, 电量=%.2f%%, 激活状态=%s",
      msg.id, msg.battery_level, msg.is_active ? "true" : "false");
  }

  rclcpp::Subscription<custom_interfaces::msg::RobotStatus>::SharedPtr subscription_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<RobotStatusSubscriber>());
  rclcpp::shutdown();
  return 0;
}
