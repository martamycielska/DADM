#ifndef MRI_H
#define MRI_H

#include <QThread>

typedef enum process {RECONSTRUCTION} process;

class MRI
{
public:
    MRI();
    void MRI_recognition();
    void intensity_inhomogenity_correction();
    void non_stationary_noise_estimation();
    void non_stationary_noise_filtering_1();
    void non_stationary_noise_filtering_2();
    void streamline_tractography();
    void skull_stripping();
    void segmentation();
    void upsampling();
    void brain_3d();
    void oblique_imaging();
};

#endif // MRI_H
