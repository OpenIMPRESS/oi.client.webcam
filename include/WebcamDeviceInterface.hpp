/*
This file is part of the OpenIMPRESS project.

OpenIMPRESS is free software: you can redistribute it and/or modify
it under the terms of the Lesser GNU Lesser General Public License as published
by the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

OpenIMPRESS is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with OpenIMPRESS. If not, see <https://www.gnu.org/licenses/>.
*/
#pragma once

#include "opencv2/opencv.hpp"
#include <RGBDDevice.hpp>

namespace oi { namespace client { namespace webcam {

class WebcamDeviceInterface : public oi::core::rgbd::RGBDDeviceInterface {
public:
    WebcamDeviceInterface(std::string serial, bool withGUI);
    int OpenDevice();
    int CloseDevice();
    int Cycle(oi::core::rgbd::RGBDDevice * streamer);
    
    int frame_width();
    int frame_height();
    int send_depth_stride();
    int raw_depth_stride();
    int raw_color_stride();
    
    float device_cx();
    float device_cy();
    float device_fx();
    float device_fy();
    float device_depth_scale();
    
    bool supports_audio();
    bool supports_body();
    bool supports_bidx();
    bool supports_hd();
    bool supports_depth();
    
    std::string device_guid();
    TJPF color_pixel_format();
    
private:
    std::string serial;
    bool withGUI;
    cv::VideoCapture * cap;
};

} } }
