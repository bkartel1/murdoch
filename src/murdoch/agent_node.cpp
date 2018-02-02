#include "murdoch/agent_node.h"
#include <talmech/auction/auctioneer_agent.h>
#include <talmech/auction/auctioneer_robot.h>
#include <talmech/auction/bidder_agent.h>
#include <talmech/auction/bidder_robot.h>

namespace murdoch
{
AgentNode::AgentNode(const ros::NodeHandlePtr& nh, const ros::Rate& rate)
    : ROSNode::ROSNode(nh, rate)
{
}

void AgentNode::readParameters()
{
  ros::NodeHandle pnh("~");
  std::string agent_type;
  pnh.param("type", agent_type, std::string("robot"));
  std::string id;
  pnh.param("id", id, std::string(""));
  if (id.empty())
  {
    throw utilities::Exception("The agent id must not be null.");
  }
  std::string role_type;
  pnh.param("role", role_type, std::string("bidder"));
  if (agent_type == "agent")
  {
    if (role_type == "auctioneer")
    {
      agent_.reset(new talmech::auction::AuctioneerAgent(nh_, id));
    }
    else if (role_type == "bidder")
    {
      agent_.reset(new talmech::auction::BidderAgent(nh_, id));
    }
    else
    {
      throw utilities::Exception("Unknown role type.");
    }
  }
  else if (agent_type == "robot")
  {
    if (role_type == "auctioneer")
    {
      agent_.reset(new talmech::auction::AuctioneerRobot(nh_, id));
    }
    else if (role_type == "bidder")
    {
      agent_.reset(new talmech::auction::BidderRobot(nh_, id));
    }
    else
    {
      throw utilities::Exception("Unknown role type.");
    }
  }
  else
  {
    throw utilities::Exception("Unknown agent type.");
  }
}
}
