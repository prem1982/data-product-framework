"""Generates simple image matrices for unit tests"""
import sys
import os

from PIL import Image
import numpy as np

def _build_gray_uint8_image(output_file):
    # 1 channel (grayscale) image
    arr = np.array(([0, 51], [51, 255])).astype(np.uint8)
    image = Image.fromarray(arr)
    image.save(output_file)

def _build_rgb_uint8_image(output_file):
    # 3 channel (RGB color) image
    arr = np.array(([
        [[0, 51], [51, 255]],  # R
        [[255, 51], [51, 0]],  # G
        [[51, 0], [255, 51]]   # B
    ])).astype(np.uint8).transpose(1, 2, 0)
    image = Image.fromarray(arr, 'RGB')
    image.save(output_file)

def main():
    """Builds and writes the image matrices"""
    base_folder = sys.argv[1]
    _build_gray_uint8_image(os.path.join(base_folder, "gray_2x2_uint8.png"))
    _build_rgb_uint8_image(os.path.join(base_folder, "rgb_2x2_uint8.png"))

if __name__ == "__main__":
    main()
