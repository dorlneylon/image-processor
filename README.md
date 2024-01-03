# BMP Image Processing Tool
## Overview
This command-line tool is designed for processing BMP images by providing functionalities to rotate images and apply a sepia filter. Additionally, a SIMD (Single Instruction, Multiple Data) realization is included for efficient sepia processing.

## Features
- Rotate Images:
    Rotate BMP images by specifying the rotation angle.
- Apply Sepia Filter:
  Apply a sepia filter to BMP images for a classic and warm-toned effect. SIMD realization on SSE instructions is provided for optimized performance.

## Usage
### Applying Sepia Filter:
```
./image_transformer <input file> <output file>
```

`<input file>`: Path to the input BMP image file.

`<output file>`: Path to save the resulting sepia-filtered BMP image.

### Rotating Images:

```
./image_transformer <input file> <output file> <rotation_angle>
```

`<input file>`: Path to the input BMP image file.

`<output file>`: Path to save the resulting rotated BMP image.

`<rotation_angle>`: Rotation angle in degrees (clockwise).

## Building
```
make all
```
This will compile the source code and generate the executable `image_transformer`. No extra dependencies required.

## Examples

```
./image_transformer ./input.bmp ./output_rotation.bmp 270
```

![rotation test](./output_rotation.bmp)

```
./image_transformer ./input.bmp ./output_sepia.bmp
```

![sepia test](./output_sepia.bmp)