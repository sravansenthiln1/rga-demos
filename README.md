# Rockchip RGA Demos

Examples to use Rockchip RGA2-E/RGA3 platform.

Compatible with Edge2

### Check device driver version

```
sudo cat /sys/kernel/debug/rkrga/driver_version
```

### Try Examples:

* [RGA info](/src/rga-info/) - Simple diagnostic info about system RGA

* [RGA copy](/src/rga-copy/) - Copy a RGA image buffer in virtual memory address

* [RGA DMA](/src/rga-dma/) - Copy a RGA image buf stored in an uncached dma-buf

* [RGA DMA cached](/src/rga-dma-cached/) - Copy a RGA image buf stored in cached dma-buf

* [RGA crop](/src/rga-crop/) - Crop into an RGA image

* [RGA rotate](/src/rga-rotate/) - Rotate an RGA image

* [RGA resize](/src/rga-resize/) - Resize an RGA image

* [RGA color convert](/src/rga-cvt) - Converts RGA RGB888 Image to NV12 image format.
