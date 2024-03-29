//
// Created by jihaorui on 5/1/21.
//

#ifndef MYSLAM_DATASET_H
#define MYSLAM_DATASET_H
#include "myslam/camera.h"
#include "myslam/common_include.h"
#include "myslam/frame.h"

namespace myslam {

/**
 * 数据集读取
 * 构造时传入配置文件路径，配置文件的dataset_dir为数据集路径
 * Init之后可获得相机和下一帧图像
 */
class Dataset
{
public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW;
    typedef std::shared_ptr<Dataset> Ptr;
    Dataset(const std::string& dataset_path);

    /// 初始化，返回是否成功
    bool Init();

    /// create and return the next frame containing the stereo images
    Frame::Ptr NextFrame();

    /// get time stamp vector
    vector<double> GetTimeStamp() const {
        return times_;
    }

    /// get camera by id
    Camera::Ptr GetCamera(int camera_id) const {
        return cameras_.at(camera_id);
    }

    /// get ground truth poses
    vector<vector<float>> GetGroundTruthPose() const {
        return ground_truth_poses_;
    }

    /// get absolute scale
    double GetAbsoluteScale(int frame_id);

private:
    // Init
    string dataset_path_;
    vector<double> times_;
    vector<Camera::Ptr> cameras_;
    vector<vector<float>> ground_truth_poses_;

    // Next frame
    int current_image_index_ = 0;
};
}  // namespace myslam
#endif //MYSLAM_DATASET_H
