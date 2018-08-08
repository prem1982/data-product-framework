"""Service to detect objects on images"""

import sys
import json

import scipy

sys.path.append("./python/")

# pylint: disable=wrong-import-position
from bnr.object_detection.object_detector import ObjectDetector

# Argument parsing
NUM_ARGS = 4
if len(sys.argv) != NUM_ARGS:
    print "Usage: " + sys.argv[0] + " <input image list> <model path> <output dataset path>"
    print "Found " + str(len(sys.argv)) + " arguments, expected " + str(NUM_ARGS) + " arguments"
    sys.exit(-1)

IMAGEPATH_LIST_PATH = sys.argv[1]
MODEL_PATH = sys.argv[2]
DATASET_PATH = sys.argv[3]

def main():
    """Runs ObjectDetector on a list of images and writes results to disk"""
    with open(IMAGEPATH_LIST_PATH, "rt") as imagepath_list_handle:
        imagepath_list = [line.strip() for line in imagepath_list_handle.readlines()]

    object_detector = ObjectDetector(MODEL_PATH)

    dataset_json = []
    for imagepath in imagepath_list:
        image = scipy.misc.imread(imagepath)
        detections = object_detector.run(image)

        detections_json = {"path": imagepath, "detections": [det.to_dict() for det in detections]}
        dataset_json.append(detections_json)

    with open(DATASET_PATH, "wt") as json_handle:
        json.dump(dataset_json, json_handle, sort_keys=True, indent=4)

if __name__ == "__main__":
    main()
