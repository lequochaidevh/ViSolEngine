╰──> lspci | grep -E "VGA|3D"
00:02.0 VGA compatible controller: Intel Corporation UHD Graphics 630 (Mobile)
01:00.0 3D controller: NVIDIA Corporation GP107M [GeForce GTX 1050 Mobile] (rev a1)

╰──> lsmod | grep i915
i915                 3067904  7
ttm                    86016  1 i915
drm_kms_helper        311296  2 nvidia_drm,i915
cec                    65536  2 drm_kms_helper,i915
i2c_algo_bit           16384  1 i915
drm                   618496  18 drm_kms_helper,nvidia,nvidia_drm,i915,ttm
video                  61440  2 asus_wmi,i915


╰──> glxinfo | grep "OpenGL renderer"
OpenGL renderer string: NVIDIA GeForce GTX 1050/PCIe/SSE2


### INSTALL

sudo apt install mesa-utils

**USE NVIDIA**
sudo apt install nvidia-container-toolkit
sudo systemctl restart docker

**USE INTEL** // unused
sudo prime-select intel
reboot