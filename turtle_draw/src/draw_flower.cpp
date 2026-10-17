#include <chrono>
#include <functional>
#include <memory>

#include "geometry_msgs/msg/twist.hpp"
#include "rclcpp/rclcpp.hpp"
#include "turtlesim/msg/pose.hpp"

using namespace std::chrono_literals;
using std::placeholders::_1;
using namespace std;

class DrawFlower : public rclcpp::Node
{
public:
  bool isSpinnerOn;
  bool isTurnOn;
  int count;
  DrawFlower()
  : Node("draw_flower")
  {
    count=0;
    isSpinnerOn=0;
    isTurnOn=1;
    count=0;
    publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel", 10);
    timer_circle = this->create_wall_timer(
      10ms, std::bind(&DrawFlower::spin_callback, this));
    timer_turn = this->create_wall_timer(
      10ms, std::bind(&DrawFlower::turn_turn, this));
    timer_swap = this->create_wall_timer(
      500ms, std::bind(&DrawFlower::swap_callback, this));
    //Karena waktunya hanya 1/2 detik maka perubahan sudut dan jarak yang ditempuh hanyalah setengah dari nilai pada fungsi

}

  
private:

  void spin_callback()
  {
    if(isSpinnerOn==1){
    geometry_msgs::msg::Twist msg;
    msg.linear.x = 10.0;
    msg.angular.z = 2.6179938779914*2; // ((5*pi)/6)*2 = 300 derajat
    publisher_->publish(msg);
    }
  }

  void turn_turn(){
    if(isTurnOn==1){
    geometry_msgs::msg::Twist msg;
    msg.angular.z = 2.6179938779914; // (5*pi)/6 = 150 derajat
    publisher_->publish(msg);
    }
  }

  void swap_callback(){
      if(isSpinnerOn==0){
        isSpinnerOn=1;
        isTurnOn=0;
      }
      else{
        isSpinnerOn=0;
        isTurnOn=1;
      }
    if(count>=16){
      isSpinnerOn=0;
      isTurnOn=0;
      geometry_msgs::msg::Twist msg;
      publisher_->publish(msg);
    }
    count+=1;
  }

  rclcpp::TimerBase::SharedPtr timer_swap;
  rclcpp::TimerBase::SharedPtr timer_circle;
  rclcpp::TimerBase::SharedPtr timer_turn;
  rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<DrawFlower>());
  rclcpp::shutdown();
  return 0;
}