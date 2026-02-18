# GBM, DMA-BUF, ION và Kiến Trúc Render Headless trong Embedded Linux

### GBM LÀ GÌ?

GBM (Generic Buffer Manager) là một thư viện thuộc stack đồ hoạ của Mesa, cho phép:
Tạo buffer đồ hoạ ở mức kernel (DRM)
Dùng cho GPU rendering
Export thành DMA-BUF
Scanout ra màn hình (KMS)
Hoặc xử lý headless (không display)
GBM hoạt động trực tiếp với: `DRM (Direct Rendering Manager)`
thay vì: `X11 / Wayland`

→ Rất quan trọng trong hệ thống embedded / headless / camera / automotive

### TẠI SAO PHẢI DÙNG GBM?

I. Khi KHÔNG cần GBM
Không cần GBM nếu:
Chỉ render ra file ảnh
Chạy trong X11 / Wayland
Không cần zero-copy
Không cần share buffer giữa nhiều subsystem

Ví dụ: `EGL Pbuffer → glReadPixels → save file`
Đơn giản, đủ dùng cho server render.

II. Khi BẮT BUỘC dùng GBM

Cần GBM khi:

1. Zero-copy pipeline

    Ví dụ camera pipeline: `Camera → ISP → GBM buffer → GL → Encoder`
    Không copy RAM.

2. Multi-device sharing
Buffer có thể dùng chung cho:
    GPU
    Video encoder (VAAPI)
    Display controller
    AI accelerator
    
3. Không có window system
Embedded Linux thường không có:
    X11
    Wayland
    Desktop
    GBM + DRM cho phép:`GPU render trực tiếp vào kernel buffer`
4. Scanout trực tiếp ra HDMI

KMS cần: `GBM BO`
Không dùng được Pbuffer.

III. SO SÁNH: EGL CÓ GBM vs KHÔNG GBM
SO SÁNH: EGL CÓ GBM vs KHÔNG GBM

Flow:
```txt
EGL Display
   ↓
Pbuffer Surface
   ↓
GL Context
   ↓
Render
   ↓
glReadPixels
```


Đặc điểm:
| Thuộc tính      | Giá trị |
| --------------- | ------- |
| Zero-copy       | ❌       |
| DMA-BUF         | ❌       |
| Scanout         | ❌       |
| Embedded camera | ❌       |
| Dễ dùng         | ✅       |

EGL + GBM
Flow chuẩn:
```text
/dev/dri/renderD128
        ↓
gbm_device
        ↓
gbm_bo (buffer object)
        ↓
EGLImage
        ↓
GL texture
        ↓
FBO
        ↓
Render
        ↓
Export DMA-BUF / Scanout
```

Đặc điểm:
| Thuộc tính      | Giá trị |
| --------------- | ------- |
| Zero-copy       | ✅       |
| DMA-BUF         | ✅       |
| Scanout         | ✅       |
| Camera pipeline | ✅       |
| Phức tạp        | Cao     |

IV. ĐIỀU KIỆN CẦN ĐỂ CHẠY GBM
ĐIỀU KIỆN CẦN ĐỂ CHẠY GBM

1. Kernel phải có DRM driver
Kiểm tra:`lsmod | grep i915`

Ví dụ:`Intel UHD Graphics 630`

2. Có render node
/dev/dri/renderD128

Render node cho phép:
    Compute
    Rendering
    Không cần quyền KMS

3. Mesa phải hỗ trợ GBM backend `eglinfo | grep GBM`

4. EGL extension cần thiết
Phải có:
```txt
EGL_KHR_image_base
GL_OES_EGL_image
```
Nếu không → không bind được GBM BO vào GL.

5. Không bắt buộc HDMI

GBM render node:
```txt
Không cần connector
Không cần display
Không cần swapbuffers
```

V. CÁC ĐỐI TƯỢNG TRONG GBM

1. GBM Device
open("/dev/dri/renderD128")
Đại diện cho GPU render interface.

2. GBM BO (Buffer Object)
Đây là trung tâm của GBM.

gbm_bo_create(...)
BO có:
```txt
Width
Height
Format (ARGB8888, NV12…)
Usage flag
```
Nó là memory thực nằm trong: `GPU-accessible memory`

3. DMA-BUF
DMA-BUF là: `Linux kernel buffer sharing mechanism`
Cho phép: `Driver A → Driver B`
share buffer không copy.

Ví dụ:
```txt
GBM → VAAPI
GBM → V4L2
GBM → DRM
```

Export: `int fd = gbm_bo_get_fd(bo);`

Đây là zero-copy thật sự.

4. ION LÀ GÌ?
ION là: `Android memory allocator subsystem`
Dùng nhiều trong SoC như:
    Qualcomm
    MediaTek
    Exynos

Khái niệm ION > ION cung cấp: `User space → allocate contiguous memory`

Cho:
    Camera
    GPU
    DSP
    Encoder
Nguyên lý ION
    ION có:`Heap`
Mỗi heap là:
    System heap
    Carveout heap
    Secure heap
    CMA heap

Memory được: `Allocated → exported as DMA-BUF → shared`
ION bản chất là:
```txt
Memory allocator
+
DMA-BUF exporter
```

5. ION -> GBM

| Tiêu chí      | ION              | GBM              |
| ------------- | ---------------- | ---------------- |
| Mục đích      | Memory allocator | Graphics buffer  |
| Dùng cho GPU  | Có               | Có               |
| Android       | Chính            | Không phải chính |
| Linux desktop | Không            | Có               |
| DMA-BUF       | Có               | Có               |

6. Thực tế ION và DMA-BUF nằm ở 2 tầng khác nhau trong kernel.

Phân biệt đúng bản chất
🔹 DMA-BUF là gì?
DMA-BUF là:
Cơ chế chia sẻ buffer giữa các driver trong Linux kernel

Nó KHÔNG phải memory allocator.
Nó chỉ làm:
```txt
Exporter driver  →  Importer driver
        ↕
     share via fd
```

DMA-BUF cung cấp:
    file descriptor (fd)
    attach
    map/unmap
    sync (fence)

ION là gì?

ION là:`Memory allocator subsystem (Android)`

ION làm 2 việc:
    Allocate memory (thường contiguous hoặc special heap)
    Export memory đó thành DMA-BUF

Vậy:
```txt
ION = Allocator + DMA-BUF exporter
DMA-BUF = Sharing framework
```

7. Vì sao người ta nói “DMA-HEAP thay thế ION”?

ION là Android-specific.
    Mainline Linux không muốn:
    allocator riêng
    API riêng
    maintenance riêng
        → Kernel mainline loại bỏ ION
        → Thay bằng:`DMA-HEAP`

DMA-HEAP là:
    Memory allocator chuẩn mainline Linux
    Và cũng export ra DMA-BUF

So sánh kỹ ION vs DMA-BUF vs DMA-HEAP

| Thành phần            | ION       | DMA-BUF           | DMA-HEAP  |
| --------------------- | --------- | ----------------- | --------- |
| Loại                  | Allocator | Sharing framework | Allocator |
| Cấp kernel            | Android   | Mainline          | Mainline  |
| Allocate memory       | ✅         | ❌                 | ✅         |
| Export fd             | ✅         | n/a               | ✅         |
| Share zero-copy       | ✅         | ✅                 | ✅         |
| Physically contiguous | Có thể    | Không liên quan   | Có thể    |

**Vấn đề “physically contiguous pages”**

ION có thể allocate:
    System heap (scatter-gather)
    CMA heap (physically contiguous)
    Carveout heap
    Secure heap

Nhưng DMA-BUF không quan tâm contiguous hay không.
DMA-BUF chỉ nhận: `struct dma_buf *`
Từ allocator.
-> Contiguous hay không là chuyện của allocator.

Zero-Copy: ai thực sự tạo ra?
    Zero-copy không phải do ION.
    Zero-copy có được vì:
        Điều này đạt được khi:
            Memory được share bằng DMA-BUF
            Driver import trực tiếp cùng vùng memory

Ví dụ:
@@@ Không zero-copy
```txt
Camera → malloc buffer
        → memcpy → GPU
```

@@@ Zero-copy
```txt
Camera driver
   ↓
Allocate memory
   ↓
Export DMA-BUF fd
   ↓
GPU import fd
```

Không copy.
Cơ chế share đó là DMA-BUF, không phải ION.
ION chỉ là allocator ban đầu.

Luồng thực tế trong Qualcomm SoC
    Trong SoC của Qualcomm:
    Thế hệ cũ (Android cũ)
    ```txt
    ION allocate
        ↓
    Export DMA-BUF
        ↓
    Camera / GPU / Encoder import
    ```

    Kernel mới (mainline)
    ```
    DMA-HEAP allocate
        ↓
    Export DMA-BUF
        ↓
    Subsystem import
    ```

ION bị loại bỏ, DMA-BUF vẫn tồn tại.
Phân tích kiến trúc chuẩn hiện đại

Trong hệ thống có GBM đang làm:
```txt
    GBM BO
        ↓
    Internally allocate memory
        ↓
    Export DMA-BUF
        ↓
    Share with other subsystem
```
GBM cũng là allocator + DMA-BUF exporter.
Rất giống ION về vai trò, nhưng chuyên cho graphics.

**Tóm tắt cực rõ**
DMA-BUF
    Framework chia sẻ memory
    Không allocate
    Là nền tảng zero-copy

ION
    Android allocator
    Có heap đặc biệt
    Export ra DMA-BUF

DMA-HEAP
    Allocator chuẩn mainline
    Thay thế ION
    Export ra DMA-BUF

=> Kết luận kỹ thuật
Zero-copy xảy ra vì:
    Memory được share giữa driver bằng DMA-BUF
    Không phải vì ION.
    ION chỉ là allocator thuận tiện cho Android SoC.

Nếu đang làm embedded hiện đại
Nên hiểu pipeline theo thứ tự:
```txt
Allocator (DMA-HEAP / GBM / driver private)
        ↓
DMA-BUF
        ↓
Importer (GPU / V4L2 / Encoder / Display)
```

DMA-BUF là trung tâm.

8. Qualcomm Camera Pipeline (Ví dụ thực tế)

Trong SoC của Qualcomm:
Flow thường là:
```txt
Sensor
  ↓
ISP
  ↓
ION buffer
  ↓
DMA-BUF
  ↓
GPU / Encoder
```

ION đảm nhiệm:
    Contiguous memory
    Cache sync
    Secure heap

GBM có thể được dùng khi:`GPU render → display`

9. ION BUFFER — PHÂN TÍCH SÂU
 Vấn đề ION giải quyết
Trong SoC:
    Camera cần memory contiguous
    GPU cần physical address
    DSP cần truy cập trực tiếp
    malloc() không đủ.

ION:`Kernel allocate physically contiguous pages`

Zero Copy Principle
Thay vì: `Camera → memcpy → GPU`
Camera → DMA-BUF fd → GPU
Không copy.

Secure Heap
ION hỗ trợ:`Protected memory`

Dùng cho:
    DRM video
    Secure camera
    TEE

ION có còn phát triển không?
ION đã bị thay thế trong mainline Linux bởi:`DMA-HEAP`
Kernel mới:`CONFIG_DMA_HEAP`
DMA-HEAP là successor của ION.

10. Kiến Trúc Embedded Chuẩn Hiện Nay
Hiện đại thường dùng:
```txt
DMA-HEAP
   ↓
DMA-BUF
   ↓
GBM
   ↓
EGLImage
   ↓
GL
```

Hoặc:

```
Camera
   ↓
V4L2
   ↓
DMA-BUF
   ↓
GPU
```

11. Khi Nào Nên Dùng GÌ?
    Server render headless→ EGL Pbuffer
    Camera pipeline→ DMA-BUF + GBM
    Android→ ION / DMA-HEAP
    Automotive→ DRM + GBM + zero-copy

12. Tổng Kết
GBM là:`Graphics memory abstraction layer`
ION là:`Memory allocator cho multimedia SoC`
DMA-BUF là:`Cơ chế kernel cho zero-copy sharing`

Kết luận quan trọng

    Nếu mục tiêu là:
    Embedded
    Camera
    AI pipeline
    Zero-copy
    Headless GPU
    → GBM + DMA-BUF là hướng đi đúng.

    Nếu chỉ render ảnh:
    → Pbuffer là đủ.



TODO:
struct dma_buf

attach

map

fence sync

cache coherency