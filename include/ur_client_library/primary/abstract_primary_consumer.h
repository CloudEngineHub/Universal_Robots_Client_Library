// this is for emacs file handling -*- mode: c++; indent-tabs-mode: nil -*-
//
// -- BEGIN LICENSE BLOCK ----------------------------------------------
// Copyright 2020 FZI Forschungszentrum Informatik
// Created on behalf of Universal Robots A/S
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// -- END LICENSE BLOCK ------------------------------------------------

//----------------------------------------------------------------------
/*!\file
 *
 * \author  Felix Exner exner@fzi.de
 * \date    2020-04-30
 *
 */
//----------------------------------------------------------------------

#ifndef UR_ROBOT_DRIVER_ABSTRACT_PRIMARY_CONSUMER_H_INCLUDED
#define UR_ROBOT_DRIVER_ABSTRACT_PRIMARY_CONSUMER_H_INCLUDED

#include "ur_client_library/log.h"
#include "ur_client_library/comm/pipeline.h"
#include "ur_client_library/primary/robot_message/version_message.h"
#include "ur_client_library/primary/robot_message/error_code_message.h"
#include "ur_client_library/primary/robot_state/kinematics_info.h"
#include "ur_client_library/primary/robot_state/robot_mode_data.h"
#include "ur_client_library/primary/robot_state/configuration_data.h"

namespace urcl
{
namespace primary_interface
{
/*!
 * \brief Base consumer for primary packages
 *
 * Primary interface consumers can inherit from this class in order to implement the visitor
 * pattern for consuming primary packages.
 */
class AbstractPrimaryConsumer : public comm::IConsumer<PrimaryPackage>
{
public:
  AbstractPrimaryConsumer() = default;
  virtual ~AbstractPrimaryConsumer() = default;

  /*!
   * \brief This consume method is usually being called by the Pipeline structure. We don't
   * necessarily need to know the specific package type here, as the packages themselves will take
   * care to be consumed with the correct function (visitor pattern).
   *
   * \param product package as it is received from the robot
   *
   * \returns true on successful consuming
   */
  virtual bool consume(std::shared_ptr<PrimaryPackage> product) final
  {
    if (product != nullptr)
    {
      return product->consumeWith(*this);
    }
    return false;
  }

  // To be implemented in specific consumers
  virtual bool consume(RobotMessage& pkg) = 0;
  virtual bool consume(RobotState& pkg) = 0;
  virtual bool consume(VersionMessage& pkg) = 0;
  virtual bool consume(KinematicsInfo& pkg) = 0;
  virtual bool consume(ErrorCodeMessage& pkg) = 0;
  virtual bool consume(RobotModeData& pkg) = 0;
  virtual bool consume(ConfigurationData& pkg) = 0;

private:
  /* data */
};
}  // namespace primary_interface
}  // namespace urcl

#endif  // ifndef UR_ROBOT_DRIVER_ABSTRACT_PRIMARY_CONSUMER_H_INCLUDED
