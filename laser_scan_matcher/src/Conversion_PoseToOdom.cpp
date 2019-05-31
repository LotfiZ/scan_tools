#include <tf/tf.h>
#include <tf/transform_broadcaster.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Pose2D.h>
#include <laser_scan_matcher/laser_scan_matcher.h>
#include <geometry_msgs/PoseStamped.h>
#include <pcl_conversions/pcl_conversions.h>

double yaw;
ros::Publisher pub_odom_;
nav_msgs::Odometry odom;

void PoseCallback_(const geometry_msgs::PoseStamped::ConstPtr msg) {

	/*static tf::TransformBroadcaster br;
  	tf::Transform transform;*/

//ROS_INFO("%f",msg);

    /**tf::Quaternion q(
        msg->qx,
        msg->qy,
        msg->qz,
        msg->qw);
    tf::Matrix3x3 m(q);
    double roll, pitch, yaw;

    m.getRPY(roll, pitch, yaw);
    
    tf::Quaternion qf = tf::createQuaternionFromRPY(0, 0, yaw);
    ROS_INFO("Yaw : %f",yaw);**/
    
    odom.header.frame_id = "odom";
    odom.child_frame_id = "base_link";
    odom.header.stamp = ros::Time::now();
    odom.pose.pose.position.x = msg->pose.position.x;
    odom.pose.pose.position.y = msg->pose.position.y;
    odom.pose.pose.position.z = msg->pose.position.z;

    odom.pose.pose.orientation.x = msg->pose.orientation.x;
    odom.pose.pose.orientation.y = msg->pose.orientation.y;
    odom.pose.pose.orientation.z = msg->pose.orientation.z;
    odom.pose.pose.orientation.w = msg->pose.orientation.w;
    yaw = tf::getYaw(msg->pose.orientation);
  ROS_INFO("%f",yaw);
    //transform.setOrigin( tf::Vector3(msg->x_m, msg->y_m, 0.0) );
    //transform.setRotation(qf);
    //br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "odom", "base_link"));
    pub_odom_.publish(odom);
    
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "odom_publisher");
    
    ros::NodeHandle nh_;
    
    ros::Subscriber sub_imu_ = nh_.subscribe("pose_stamped", 1, PoseCallback_);
    pub_odom_ = nh_.advertise<nav_msgs::Odometry>("odom", 1);
    
    ros::spin();
    
    return 0;
}
