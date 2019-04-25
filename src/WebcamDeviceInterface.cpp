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

#include "WebcamDeviceInterface.hpp"

using namespace oi::core;
using namespace oi::client::webcam;


WebcamDeviceInterface::WebcamDeviceInterface(std::string serial, bool withGUI) {
    this->serial = serial;
    this->withGUI = withGUI;
    OpenDevice();
}

int WebcamDeviceInterface::Cycle(oi::core::rgbd::RGBDDevice * streamer) {
    std::chrono::milliseconds timestamp = oi::core::NOW();
    int res = 0;
    
    cv::Mat frame;
    if (cap->read(frame)) {
        res += streamer->QueueHDFrame(frame.data, frame_width(), frame_height(), TJPF_BGR, timestamp);
        cv::imshow("webcam", frame);
        if (this->withGUI && cv::waitKey(10) ) {};
    }
    

    return res;
}


int WebcamDeviceInterface::OpenDevice() {
    cap = new cv::VideoCapture(0);
    if(!cap->isOpened())
        return -1;
    if (this->withGUI) {
        cv::namedWindow("webcam", 1);
    }
    return 1;
}

int WebcamDeviceInterface::CloseDevice() {
    return 1;
}

int WebcamDeviceInterface::frame_width() {
    return cap->get(cv::CAP_PROP_FRAME_WIDTH);
}

int WebcamDeviceInterface::frame_height() {
    return cap->get(cv::CAP_PROP_FRAME_HEIGHT);
}

int WebcamDeviceInterface::send_depth_stride() {
    return 2;
}

int WebcamDeviceInterface::raw_depth_stride() {
    return 4;
}

int WebcamDeviceInterface::raw_color_stride() {
    return 4;
}

float WebcamDeviceInterface::device_cx() {
    return 0.0f;
}

float WebcamDeviceInterface::device_cy() {
    return 0.0f;
}

float WebcamDeviceInterface::device_fx() {
    return 0.0f;
}

float WebcamDeviceInterface::device_fy() {
    return 0.0f;
}

float WebcamDeviceInterface::device_depth_scale() {
    return 0.0f;
}

std::string WebcamDeviceInterface::device_guid() {
    return serial;
}

TJPF WebcamDeviceInterface::color_pixel_format() {
    return TJPF_BGRX;
}

bool WebcamDeviceInterface::supports_depth() {
    return false;
}

bool WebcamDeviceInterface::supports_audio() {
    return false;
}

bool WebcamDeviceInterface::supports_body() {
    return false;
}

bool WebcamDeviceInterface::supports_bidx() {
    return false;
}

bool WebcamDeviceInterface::supports_hd() {
    return true;
}
