#include <ros/ros.h>
#include <nav_msgs/Odometry.h>
#include <sensor_msgs/PointCloud2.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_cloud.h>
#include <geometry_msgs/PointStamped.h>
#include <geometry_msgs/Point.h>
#include <pcl_conversions/pcl_conversions.h>
#include <Eigen/Dense>
#include <vector>
#include <math>

typedef geometry_msgs::Point ROSPoint;
typedef geometry_msgs::PointStamped ROSWayPoint;

struct Point {
    float x;
    float y;
    float operator *(const Point& pt) const
    {
        return x * pt.x + y * pt.y;
    }
    Point operator +(const Point& pt) const
    {
        Point result;
        result.x += pt.x;
        result.y += pt.y;
        return result;
    }
    Point operator -(const Point& pt) const
    {
        Point result;
        result.x -= pt.x;
        result.y -= pt.y;
        return result;
    }
};


class VB_Planner
{
public:
    VB_Planner();
    void Loop();

private:
    // rostopic define
    ros::NodeHandle nh_;
    ros::Subscriber point_cloud_sub_;
    ros::Subscriber odom_sub_;
    ros::Publishder goal_pub_;
    // function define
    Point CPoint(float x, float y);
    float Norm(Point p);
    void PrincipalAnalysis();
    void ElasticRawCast();
    void InitializeParam();
    void OdomHandler(const nav_msgs::Odometry odom_msg);
    ROSWayPoint HandleWaypoint();
    void CloudHandler(const sensor_msgs::PointCloud2ConstPtr cloud_msg);
    bool HitObstacle(Point p);
    // valuable define

    nav_msgs::Odometry odom_;
    Point robot_heading_;
    Point robot_center_;
    ROSPoint goal_waypoint_;
    Point principal_direction_;
    pcl::PointCloud<pcl::PointXYZI>::Ptr laser_cloud_(new pcl::PointCloud<pcl::PointXYZI>());
    pcl::KdTreeFLANN<pcl::PointXYZI>::Ptr kdtree_collision_cloud_(new pcl::KdTreeFLANN<pcl::PointXYZI>());
    // ros  parameter value
    int raw_cast_revolution_;
    float max_sensor_range_;
    int obs_count_thred_;


}