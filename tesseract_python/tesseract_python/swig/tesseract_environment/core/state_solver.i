/**
 * @file state_solver.i
 * @brief SWIG interface file for tesseract_environment/core/state_solver.h
 *
 * @author John Wason
 * @date December 10, 2019
 * @version TODO
 * @bug No known bugs
 *
 * @copyright Copyright (c) 2019, Wason Technology, LLC
 *
 * @par License
 * Software License Agreement (Apache License)
 * @par
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * http://www.apache.org/licenses/LICENSE-2.0
 * @par
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

%{
#include <tesseract_environment/core/state_solver.h>
%}

%shared_ptr(tesseract_environment::StateSolver)

namespace tesseract_environment
{
class StateSolver
{
public:
  using Ptr = std::shared_ptr<StateSolver>;
  using ConstPtr = std::shared_ptr<const StateSolver>;

  virtual ~StateSolver();

  virtual bool init(tesseract_scene_graph::SceneGraph::ConstPtr scene_graph) = 0;

    virtual void setState(const std::unordered_map<std::string, double>& joints) = 0;
  virtual void setState(const std::vector<std::string>& joint_names, const std::vector<double>& joint_values) = 0;
  virtual void setState(const std::vector<std::string>& joint_names,
                        const Eigen::Ref<const Eigen::VectorXd>& joint_values) = 0;

  
  virtual EnvState::Ptr getState(const std::unordered_map<std::string, double>& joints) const = 0;
  virtual EnvState::Ptr getState(const std::vector<std::string>& joint_names,
                                 const std::vector<double>& joint_values) const = 0;
  virtual EnvState::Ptr getState(const std::vector<std::string>& joint_names,
                                 const Eigen::Ref<const Eigen::VectorXd>& joint_values) const = 0;

  virtual EnvState::ConstPtr getCurrentState() const = 0;

  
  virtual Ptr clone() const = 0;

};
}  // namespace tesseract_environment