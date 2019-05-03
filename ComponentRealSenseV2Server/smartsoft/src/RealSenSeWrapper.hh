//--------------------------------------------------------------------------
// Code generated by the SmartSoft MDSD Toolchain Version 2.2
// The SmartSoft Toolchain has been developed by:
//
// Christian Schlegel (schlegel@hs-ulm.de)
// University of Applied Sciences Ulm
// Prittwitzstr. 10
// 89075 Ulm (Germany)
//
// Information about the SmartSoft MDSD Toolchain is available at:
// www.servicerobotik-ulm.de
//
// This file is generated once. Modify this file to your needs.
// If you want the toolchain to re-generate this file, please
// delete it before running the code generator.
//--------------------------------------------------------------------------
// --------------------------------------------------------------------------
//
//  Copyright (C) 2011, 2017 Matthias Lutz, Dennis Stampfer, Matthias Rollenhagen, Nayabrasul Shaik
//
//      lutz@hs-ulm.de
//      stampfer@hs-ulm.de
//      rollenhagen@hs-ulm.de
//      shaik@hs-ulm.de
//
//      ZAFH Servicerobotic Ulm
//      Christian Schlegel
//      University of Applied Sciences
//      Prittwitzstr. 10
//      89075 Ulm
//      Germany
//
//
//  This library is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public
//  License as published by the Free Software Foundation; either
//  version 2.1 of the License, or (at your option) any later version.
//
//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with this library; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
//--------------------------------------------------------------------------

#ifndef REALSENSEWRAPPER_H_
#define REALSENSEWRAPPER_H_

#include <iostream>
#include <stdint.h>
#include <math.h>
#include <vector>

#include "ImageTaskCore.hh"
#include "DomainVision/CommRGBDImage.hh"
#include <librealsense2/rs.hpp>
#include "armadillo.hh"


class RealSenSeWrapper {
private:


//	rs2::context ctx;
//  rs2::device* device;

	rs2::context rs2_context_;

	rs2::device rs2_device_;
	rs2::device_list device_list;


	rs2::sensor rs2_sensor_depth;
	rs2::sensor rs2_sensor_rgb;
	std::vector<rs2::sensor> sensor_list;

	rs2::frameset current_frameset;

	rs2::pipeline pipeline;
	rs2::config config;
	rs2::pipeline_profile pipeline_profile;
	//rs2::format format_[5];

	rs2::error *rs2_error_ = NULL;




	rs2_context* rs2_contextm = NULL;
//
//	rs2_device* rs2_device_;
//	rs2_device_list* device_list;
//
//
//	rs2_sensor* rs2_sensor_depth;
//	rs2_sensor* rs2_sensor_rgb;
//	rs2_sensor_list* sensor_list;
//
//	rs2::frameset current_frameset;
//
//	rs2_pipeline* pipeline;
//	rs2_config* config;
//	rs2_pipeline_profile* pipeline_profile;
//	rs2_format format_[5];

	rs2_error *rs2_c_error_ = NULL;

public:
	//RealSenSeWrapper();
	RealSenSeWrapper(int color_width, int color_height, int color_framerate,
	        int depth_width, int depth_height, int depth_framerate, std::string device_serial_num, float in_baseline);
	virtual ~RealSenSeWrapper();

	void startVideo();
	void stopVideo();
	void getImage(DomainVision::CommRGBDImage& image);
	void getdepthimage(DomainVision::CommDepthImage& comm_depth_frame);
	void getrgbimage(DomainVision::CommVideoImage& comm_rgb_frame);
	bool init_Camera();
	void display_intrinsics_extrinsics();
	void set_baseline(float in_baseline);
	float get_baseline();
	float calulate_invalid_depth_band();
	float get_hfov_rad();
	float get_vfov_rad();
	void post_processing(rs2::depth_frame& input_depth_frame);
	void set_is_postprocess_enabled(bool value);

	// Window size and frame rate to configure the streams
	int color_width_;
	int color_height_;
	int color_framerate_;
	int depth_width_;
    int depth_height_;
	int depth_framerate_;
	std::string device_serial_number_;
	rs2_intrinsics color_intrinsics;
	rs2_intrinsics depth_intrinsics;
	rs2_extrinsics d2c_extrinsics; //depth to color
	rs2_error *rs2_fail;
	float baseline; // baseline distance in mm
	bool is_postprocess_enabled;

};

#endif /* REALSENSEWRAPPER_H_ */