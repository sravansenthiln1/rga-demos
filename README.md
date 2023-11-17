# Rockchip RGA Demos

Examples to use Rockchip RK3588s RGA2-E/RGA3 platform.

Compatible with Edge2

### Check device driver version

```
sudo cat /sys/kernel/debug/rkrga/driver_version
```

### Try Examples:

* [RGA info](/src/rga-info/) - Simple diagnostic info about system RGA

* [RGA copy](/src/rga-copy/) - Copy a RGA image in virtual memory address

* [RGA dmaheap](/src/rga-dmaheap/) - Copy a RGA image stored in a dma-heap

* [RGA dmabuf](/src/rga-dmabuf/) - Copy a RGA image stored in a dma-buf

* [RGA crop](/src/rga-crop/) - Crop into an RGA image

* [RGA rotate](/src/rga-rotate/) - Rotate an RGA image

* [RGA resize](/src/rga-resize/) - Resize an RGA image

* [RGA cvt](/src/rga-cvt) - Converts RGA image from RGB888 to NV12 color format.

* [RGA blend](/src/rga-blend) - Perform alpha blend of filter over RGA image.

* [RGA draw](/src/rga-draw) - Draw rectangles over an RGA image.

### Docs

* IM2D API guide
    -  [RGA-IM2D API GUIDE EN](docs/Rockchip_Developer_Guide_RGA_EN.md)
    -  [RGA-IM2D API GUIDE CN](docs/Rockchip_Developer_Guide_RGA_CN.md)

* RGA FAQ
    -  [RGA FAQ EN](docs/Rockchip_FAQ_RGA_EN.md)
    -  [RGA FAQ CN](docs/Rockchip_FAQ_RGA_CN.md)

#### Operation capability
<table>
    <tr>
      <td rowspan="2">Version</td>
      <td rowspan="2">Codename</td>
      <td rowspan="2">Chip</td>
      <td rowspan="1" colspan="2">Source</td>
      <td rowspan="1" colspan="2">Destination</td>
      <td rowspan="2">Function</td>
      <td rowspan="2">Pixels/Cycle</td>
    </tr>
    <tr>
       <td>min</td>
       <td>max</td>
       <td>min</td>
       <td>max</td>
    </tr>
    <tr>
      <td rowspan="1">RGA2-Enhance</td>
      <td>Orion</td>
      <td>RK3588</td>
      <td rowspan="1">2x2</td>
      <td rowspan="1">8192x8192</td>
      <td rowspan="1">2x2</td>
      <td rowspan="1">4096x4096</td>
      <td rowspan="1">90/180/270 Rotate<br/>X/Y Mirror<br/>Crop<br/>1/16~16 scale<br/>Alpha blend<br/>Color key<br/>Color fill<br/>Color palette<br/>ROP<br/>NN quantize<br/>IOMMU (32bit)</td>
      <td rowspan="1">2</td>
    </tr>
    <tr>
      <td rowspan="1">RGA3</td>
      <td>Orion</td>
      <td>RK3588</td>
      <td>68x2</td>
      <td>8176x8176</td>
      <td>68x2</td>
      <td>8128x8128</td>
      <td>90/180/270 Rotate<br/>X/Y Mirror<br/>Crop<br/>1/8~8 scale<br/>Alpha blend<br/>Color key<br/>FBC<br/>IOMMU (40bit)</td>
      <td>3 (by pass)<br/>2 (scale)</td>
   </tr>
</table>

#### Image format capability

- Conversion with RK3588 possible under BT.601/BT.709/BT.2020(only RGA3)

<table>
   <tr>
      <td>Version</td>
      <td>Codename</td>
      <td>Chip</td>
      <td>Input Data Format</td>
      <td>Output Data Format</td>
   </tr>
   <tr>
      <td rowspan="1">RGA3</td>
      <td>Orion</td>
      <td>RK3588</td>
      <td rowspan="1">
RK_FORMAT_RGBA_8888<br/>RK_FORMAT_BGRA_8888<br/>RK_FORMAT_ARGB_8888<br/>RK_FORMAT_ABGR_8888<br/>RK_FORMAT_RGBX_8888<br/>RK_FORMAT_BGRX_8888<br/>RK_FORMAT_XRGB_8888<br/>RK_FORMAT_XBGR_8888<br/>RK_FORMAT_RGB_888<br/>RK_FORMAT_BGR_888<br/>RK_FORMAT_RGB_565<br/>RK_FORMAT_BGR_565<br>RK_FORMAT_YCbCr_420_SP<br/>RK_FORMAT_YCrCbr_420_SP<br/>RK_FORMAT_YCbCr_422_SP<br/>RK_FORMAT_YCrCbr_422_SP<br/>RK_FORMAT_YUYV_422<br/>RK_FORMAT_YVYU_422<br/>RK_FORMAT_UYVY_422<br/>RK_FORMAT_VYUY_422<br/>RK_FORMAT_YCbCr_420_SP_10B<br/>RK_FORMAT_YCrCb_420_SP_10B<br/>RK_FORMAT_YCbCr_422_SP_10B<br/>RK_FORMAT_YCrCb_422_SP_10B
      </td>
      <td rowspan="1">
RK_FORMAT_RGBA_8888<br/>RK_FORMAT_BGRA_8888<br/>RK_FORMAT_RGBX_8888<br/>RK_FORMAT_BGRX_8888<br/>RK_FORMAT_RGB_888<br/>RK_FORMAT_BGR_888<br/>RK_FORMAT_RGB_565<br/>RK_FORMAT_BGR_565<br>RK_FORMAT_YCbCr_420_SP<br/>RK_FORMAT_YCrCbr_420_SP<br/>RK_FORMAT_YCbCr_422_SP<br/>RK_FORMAT_YCrCbr_422_SP<br/>RK_FORMAT_YUYV_422<br/>RK_FORMAT_YVYU_422<br/>RK_FORMAT_UYVY_422<br/>RK_FORMAT_VYUY_422<br/>RK_FORMAT_YCbCr_420_SP_10B<br/>RK_FORMAT_YCrCb_420_SP_10B<br/>RK_FORMAT_YCbCr_422_SP_10B<br/>RK_FORMAT_YCrCb_422_SP_10B
      </td>
   </tr>
</table>

#### Byte alignment requirement

<table>
    <tr>
        <th>Version</th>
        <th>Byte Stride</th>
        <th>Format</th>
        <th>Alignment</th>
    </tr>
    <tr>
        <td rowspan="6">RGA2_Enhance</td>
        <td rowspan="6">4</td>
        <td>
            RK_FORMAT_RGBA_8888<br/>RK_FORMAT_BGRA_8888<br/>RK_FORMAT_ARGB_8888<br/>RK_FORMAT_ABGR_8888<br/>RK_FORMAT_RGBX_8888<br/>RK_FORMAT_BGRX_8888<br/>RK_FORMAT_XRGB_8888<br/>RK_FORMAT_XBGR_8888
        </td>
        <td>Width stride does not require alignment</td>
    </tr>
    <tr>
        <td>
            RK_FORMAT_RGBA_4444<br/>RK_FORMAT_BGRA_4444<br/>RK_FORMAT_ARGB_4444<br/>RK_FORMAT_ABGR_4444<br/>RK_FORMAT_RGBA_5551<br/>RK_FORMAT_BGRA_5551<br/>RK_FORMAT_ARGB_5551<br/>RK_FORMAT_ABGR_5551<br/>RK_FORMAT_RGB_565<br/>RK_FORMAT_BGR_565
        </td>
        <td>Width stride must be 2-aligned</td>
    </tr>
    <tr>
        <td>
            RK_FORMAT_YUYV_422<br/>RK_FORMAT_YVYU_422<br/>RK_FORMAT_UYVY_422<br/>RK_FORMAT_VYUY_422<br/>RK_FORMAT_YUYV_420<br/>RK_FORMAT_YVYU_420<br/>RK_FORMAT_UYVY_420<br/>RK_FORMAT_VYUY_420
        </td>
        <td>Width stride must be 2-aligned, x_offset, y_offset, width, height, height stride must be 2-aligned</td>
    </tr>
    <tr>
        <td>
            RK_FORMAT_RGB_888<br/>RK_FORMAT_BGR_888
        </td>
        <td>Width stride must be 4-aligned</td>
    </tr>
    <tr>
        <td>
            RK_FORMAT_YCbCr_420_SP<br/>RK_FORMAT_YCrCbr_420_SP<br/>RK_FORMAT_YCbCr_422_SP<br/>RK_FORMAT_YCrCbr_422_SP<br/>RK_FORMAT_YCbCr_420_P<br/>RK_FORMAT_YCrCbr_420_P<br/>RK_FORMAT_YCbCr_422_P<br/>RK_FORMAT_YCrCbr_422_P<br/>RK_FORMAT_YCbCr_400<br/>RK_FORMAT_Y4
        </td>
        <td>Width stride must be 4-aligned, x_offset, y_offset, width, height, height stride must be 2-aligned</td>
    </tr>
    <tr>
        <td>
            RK_FORMAT_YCbCr_420_SP_10B<br/>RK_FORMAT_YCrCb_420_SP_10B<br/>RK_FORMAT_YCbCr_422_SP_10B<br/>RK_FORMAT_YCrCb_422_SP_10B
        </td>
        <td>Width stride must be 16-aligned, x_offset, y_offset, width, height, height stride must be 2-aligned</td>
    </tr>
    <tr>
        <td rowspan="8">RGA3</td>
        <td rowspan="8">16</td>
        <td>RK_FORMAT_RGBA_8888<br/>RK_FORMAT_BGRA_8888<br/>RK_FORMAT_ARGB_8888<br/>RK_FORMAT_ABGR_8888<br/>RK_FORMAT_RGBX_8888<br/>RK_FORMAT_BGRX_8888<br/>RK_FORMAT_XRGB_8888<br/>RK_FORMAT_XBGR_8888</td>
        <td>Width stride must be 4-aligned</td>
    </tr>
    <tr>
        <td>RK_FORMAT_RGB_565<br/>RK_FORMAT_BGR_565</td>
        <td>Width stride must be 8-aligned</td>
    </tr>
    <tr>
        <td>RK_FORMAT_YUYV_422<br/>RK_FORMAT_YVYU_422<br/>RK_FORMAT_UYVY_422<br/>RK_FORMAT_VYUY_422</td>
        <td>Width stride must be 8-aligned, x_offset, y_offset, width, height, height stride must be 2-aligned</td>
    </tr>
    <tr>
        <td>RK_FORMAT_RGB_888<br/>RK_FORMAT_BGR_888</td>
        <td>Width stride must be 16-aligned</td>
    </tr>
    <tr>
        <td>RK_FORMAT_YCbCr_420_SP<br/>RK_FORMAT_YCrCbr_420_SP<br/>RK_FORMAT_YCbCr_422_SP<br/>RK_FORMAT_YCrCbr_422_SP</td>
        <td>Width stride must be 16-aligned, x_offset, y_offset, width, height, height stride must be 2-aligned</td>
    </tr>
    <tr>
        <td>RK_FORMAT_YCbCr_420_SP_10B<br/>RK_FORMAT_YCrCb_420_SP_10B<br/>RK_FORMAT_YCbCr_422_SP_10B<br/>RK_FORMAT_YCrCb_422_SP_10B</td>
        <td>Width stride must be 64-aligned, x_offset, y_offset, width, height, height stride must be 2-aligned</td>
    </tr>
    <tr>
        <td>FBC mode</td>
        <td>In addition to the format alignment requirements above, width stride, height stride must be 16-aligned</td>
    </tr>
    <tr>
        <td>TILE8*8 mode</td>
        <td>In addition to the format alignment requirements above, width, height must be 8-aligned, input channel width stride, height stride must be 16-aligned</td>
    </tr>
</table>

