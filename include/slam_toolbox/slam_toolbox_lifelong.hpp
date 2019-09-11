/*
 * slam_toolbox
 * Copyright Work Modifications (c) 2019, Samsung Research America
 *
 * THE WORK (AS DEFINED BELOW) IS PROVIDED UNDER THE TERMS OF THIS CREATIVE
 * COMMONS PUBLIC LICENSE ("CCPL" OR "LICENSE"). THE WORK IS PROTECTED BY
 * COPYRIGHT AND/OR OTHER APPLICABLE LAW. ANY USE OF THE WORK OTHER THAN AS
 * AUTHORIZED UNDER THIS LICENSE OR COPYRIGHT LAW IS PROHIBITED.
 *
 * BY EXERCISING ANY RIGHTS TO THE WORK PROVIDED HERE, YOU ACCEPT AND AGREE TO
 * BE BOUND BY THE TERMS OF THIS LICENSE. THE LICENSOR GRANTS YOU THE RIGHTS
 * CONTAINED HERE IN CONSIDERATION OF YOUR ACCEPTANCE OF SUCH TERMS AND
 * CONDITIONS.
 *
 */

/* Author: Steven Macenski */

#ifndef SLAM_TOOLBOX_SLAM_TOOLBOX_LIFELONG_H_
#define SLAM_TOOLBOX_SLAM_TOOLBOX_LIFELONG_H_

#include "slam_toolbox/slam_toolbox_common.hpp"

namespace slam_toolbox
{

using namespace ::karto;

class LifelongSlamToolbox : public SlamToolbox
{
public:
  LifelongSlamToolbox(ros::NodeHandle& nh);
  ~LifelongSlamToolbox() {};

protected:
  virtual void laserCallback(
    const sensor_msgs::LaserScan::ConstPtr& scan) override final;
  virtual bool deserializePoseGraphCallback(
    slam_toolbox::DeserializePoseGraph::Request& req,
    slam_toolbox::DeserializePoseGraph::Response& resp) override final;

  void evaluateNodeDepreciation(LocalizedRangeScan* range_scan);
  void removeFromSlamGraph(Vertex<LocalizedRangeScan>*& vertex);
  double computeScore(LocalizedRangeScan* reference_scan, Vertex<LocalizedRangeScan>*>& candidate, const double& initial_score);
  void computeScores(std::map<double, Vertex<LocalizedRangeScan>*>& near_scans, LocalizedRangeScan* range_scan);
  std::map<double, Vertex<LocalizedRangeScan>*> FindScansWithinRadius(LocalizedRangeScan* scan, const double& radius);
  void updateScoresSlamGraph(const double& score, Vertex<LocalizedRangeScan>*& vertex);

  bool use_tree;
};

}

#endif //SLAM_TOOLBOX_SLAM_TOOLBOX_LIFELONG_H_
