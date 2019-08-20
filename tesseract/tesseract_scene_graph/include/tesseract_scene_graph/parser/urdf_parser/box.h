/**
 * @file box.h
 * @brief Parse box from xml string
 *
 * @author Levi Armstrong
 * @date Dec 18, 2017
 * @version TODO
 * @bug No known bugs
 *
 * @copyright Copyright (c) 2017, Southwest Research Institute
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
#ifndef TESSERACT_SCENE_GRAPH_URDF_PARSER_BOX_H
#define TESSERACT_SCENE_GRAPH_URDF_PARSER_BOX_H

#include <tesseract_common/macros.h>
TESSERACT_COMMON_IGNORE_WARNINGS_PUSH
#include <tesseract_common/status_code.h>
#include <Eigen/Geometry>
#include <tinyxml2.h>
TESSERACT_COMMON_IGNORE_WARNINGS_POP

namespace tesseract_scene_graph
{

class BoxStatusCategory : public tesseract_common::StatusCategory
{
public:
  BoxStatusCategory() : name_("BoxStatusCategory") {}
  const std::string& name() const noexcept override { return name_; }
  std::string message(int code) const override
  {
    switch (code)
    {
      case Success:
        return "Sucessful";
      case ErrorAttributeSize:
        return "Missing or failed parsing box attribute size!";
      case ErrorAttributeSizeConversion:
        return "Failed converting box attribute size to vector!";
      default:
        return "Invalid error code for " + name_ + "!";
    }
  }

  enum
  {
    Success = 0,
    ErrorAttributeSize = -1,
    ErrorAttributeSizeConversion = -2
  };

private:
  std::string name_;
};

inline tesseract_common::StatusCode::Ptr parse(tesseract_geometry::Box::Ptr& box, const tinyxml2::XMLElement* xml_element)
{
  box = nullptr;
  auto status_cat = std::make_shared<BoxStatusCategory>();

  std::string size_string;
  if (QueryStringAttribute(xml_element, "size", size_string) != tinyxml2::XML_SUCCESS)
    return std::make_shared<tesseract_common::StatusCode>(BoxStatusCategory::ErrorAttributeSize, status_cat);

  std::vector<std::string> tokens;
  boost::split(tokens, size_string, boost::is_any_of(" "), boost::token_compress_on);
  if (tokens.size() != 3 || !tesseract_common::isNumeric(tokens))
    return std::make_shared<tesseract_common::StatusCode>(BoxStatusCategory::ErrorAttributeSizeConversion, status_cat);

  box = std::make_shared<tesseract_geometry::Box>(std::stod(tokens[0]), std::stod(tokens[1]), std::stod(tokens[2]));
  return std::make_shared<tesseract_common::StatusCode>(BoxStatusCategory::Success, status_cat);
}

}

#endif // TESSERACT_SCENE_GRAPH_URDF_PARSER_BOX_H