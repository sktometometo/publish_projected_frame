#include <ros/ros.h>
#include <tf2_ros/transform_broadcaster.h>
#include <tf2_ros/transform_listener.h>
#include <geometry_msgs/TransformStamped.h>
#include <geometry_msgs/Twist.h>

int main( int argc, char **argv )
{
    ros::init( argc, argv, "publish_projected_frame" );
    ros::NodeHandle private_nh("~");

    std::string fixed_frame("map");
    std::string base_frame("base_link");
    std::string projected_frame("base_footprint");

    if ( private_nh.hasParam("fixed_frame") ) {
        private_nh.getParam("fixed_frame", fixed_frame);
    }
    if ( private_nh.hasParam("base_frame") ) {
        private_nh.getParam("base_frame", base_frame);
    }
    if ( private_nh.hasParam("projected_frame") ) {
        private_nh.getParam("projected_frame", projected_frame);
    }

    tf2_ros::TransformBroadcaster br;
    tf2_ros::Buffer tfBuffer;
    tf2_ros::TransformListener tfListener(tfBuffer);

    geometry_msgs::TransformStamped tf_temp;

    ros::Rate rate(50.0);

    while ( private_nh.ok() ) {
        try {
            tf_temp = tfBuffer.lookupTransform( base_frame, fixed_frame, ros::Time(0) );
        } catch ( tf2::TransformException &ex ) {
            ROS_WARN( "%s", ex.what() );
            ros::Duration(1.0).sleep();
            continue;
        }

        tf_temp.child_frame_id = projected_frame;
        tf_temp.transform.rotation.x = 0.0;
        tf_temp.transform.rotation.y = 0.0;
        tf_temp.transform.rotation.z = 0.0;
        tf_temp.transform.rotation.w = 1.0;
        tf_temp.transform.translation.z = 0.0;
        tf_temp.header.stamp = ros::Time::now();

        br.sendTransform(tf_temp);

        rate.sleep();
    }

    return 0;
}
