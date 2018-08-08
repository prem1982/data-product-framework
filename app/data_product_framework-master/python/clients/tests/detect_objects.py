"""ObjectDetector basic integration test"""

import sys

import scipy

sys.path.append("./python/")

# pylint: disable=wrong-import-position
from bnr.object_detection.object_detector import ObjectDetector

# Argument parsing
NUM_ARGS = 3
if len(sys.argv) != NUM_ARGS:
    print "Usage: " + sys.argv[0] + " <input image> <model path>"
    print "Found " + str(len(sys.argv)) + " arguments, expected " + str(NUM_ARGS) + " arguments"
    sys.exit(-1)

INPUT_IMAGE_PATH = sys.argv[1]
MODEL_PATH = sys.argv[2]

def main():
    """Runs ObjectDetector on a single image"""
    image = scipy.misc.imread(INPUT_IMAGE_PATH)
    object_detector = ObjectDetector(MODEL_PATH)
    detections = object_detector.run(image)
    print detections

if __name__ == "__main__":
    main()
