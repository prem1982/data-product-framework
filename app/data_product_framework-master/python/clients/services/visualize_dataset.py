"""Service to visualize an annotated dataset"""

import sys
import os
import json

import cv2

sys.path.append("./python/")

# pylint: disable=wrong-import-position
from bnr.datastructs.datastructs import ScoredRect

# Argument parsing
NUM_ARGS = 3
if len(sys.argv) != NUM_ARGS:
    print "Usage: " + sys.argv[0] + " <dataset path> <output folder>"
    print "Found " + str(len(sys.argv)) + " arguments, expected " + str(NUM_ARGS) + " arguments"
    sys.exit(-1)

DATASET_PATH = sys.argv[1]
OUTPUT_FOLDER = sys.argv[2]

COLOR = (0, 255, 0)

def main():
    """Draws out bounding boxes around all detections in a dataset"""
    with open(DATASET_PATH) as dataset_handle:
        dataset_json = json.load(dataset_handle)

    if not os.path.exists(OUTPUT_FOLDER):
        os.makedirs(OUTPUT_FOLDER)

    for dataset_elem in dataset_json:
        path = dataset_elem["path"]
        detections = dataset_elem["detections"]

        image = cv2.imread(path)
        for detection in detections:
            scored_rect = ScoredRect.from_dict(detection)
            _annotate_image(image, scored_rect)

        basename = os.path.basename(path)
        output_image_path = os.path.join(OUTPUT_FOLDER, basename)
        cv2.imwrite(output_image_path, image)

def _annotate_image(image, scored_rect):
    # Draws a single detection on an image
    coords = scored_rect.rect.to_tuple()
    upper_left = (coords[2], coords[0])
    lower_right = (coords[3], coords[1])
    cv2.rectangle(image, upper_left, lower_right, COLOR, 5)

if __name__ == "__main__":
    main()
