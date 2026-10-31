#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

class TopicSubscribe01 : public rclcpp::Node
{
public:
    TopicSubscribe01(std::string name) : Node(name)
    {
        RCLCPP_INFO(this->get_logger(), "大家好，我是%s.", name.c_str());
        // 创建订阅者，订阅 "command" 话题
        command_subscribe_ = this->create_subscription<std_msgs::msg::String>(
            "command", 10,
            std::bind(&TopicSubscribe01::command_callback, this, std::placeholders::_1));
    }

private:
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr command_subscribe_;
    // 回调函数，处理收到的话题消息
    void command_callback(const std_msgs::msg::String::SharedPtr msg)
    {
        double speed = 0.0f;
        if (msg->data == "forward")
        {
            speed = 0.2f;
        }
        RCLCPP_INFO(this->get_logger(), "收到[%s]指令，发送速度 %f", msg->data.c_str(), speed);
    }
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<TopicSubscribe01>("topic_subscribe");
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
