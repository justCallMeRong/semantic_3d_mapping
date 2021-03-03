
#include <ros/ros.h>

#include <gridmapping2/shared_gridmap.hpp>

int main(int argc, char *argv[]) {
  ros::init(argc, argv, "shared_grid_map");//节点名称命名为shared_grid_map
  ca::Vec3Ix grid_dimension;//定义一个signed int三维向量，栅格尺寸
  double grid_resolution;//栅格分辨率
  std::string grid_identifier;//栅格id
  ros::NodeHandle n("~");//n 命名空间为/node_namespace/node_name
  
  //读入参数，栅格尺寸、分辨率和id
  n.param<int>("/shared_gridmap/gridDimensionX", grid_dimension(0), 10);
  n.param<int>("/shared_gridmap/gridDimensionY", grid_dimension(1), 10);
  n.param<int>("/shared_gridmap/gridDimensionZ", grid_dimension(2), 5);
  n.param<std::string>("/shared_gridmap/gridIdentifier",grid_identifier,"shared_grid_map");
  n.param<double>("/shared_gridmap/gridResolution", grid_resolution, 0.5);
  
  ca::SharedGridMap gridmap(grid_identifier, grid_dimension, (float)grid_resolution);//把栅格尺寸、分辨率和id传入struct MapParameters里
  bool ok = gridmap.init();//初始化栅格地图，初始化函数定义在shared_gridmap.hpp中
  if (!ok) {
    ROS_ERROR_STREAM("shared gridmap failure");
    return -1;
  }

  ros::spin();

  return 0;
}
