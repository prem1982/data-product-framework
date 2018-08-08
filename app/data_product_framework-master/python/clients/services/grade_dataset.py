"""Service to grade a (ground truth) annotated dataset"""

import sys
import json

import scipy

sys.path.append("./python/")

# pylint: disable=wrong-import-position
from bnr.datastructs.datastructs import ScoredRect
from bnr.object_detection.object_detector import ObjectDetector
from bnr.metrics.metrics_computer import MetricsComputer
from bnr.metrics.confidence_scorer import ConfidenceScorer

# Argument parsing
NUM_ARGS = 3
if len(sys.argv) != NUM_ARGS:
    print "Usage: " + sys.argv[0] + " <ground truth dataset path> <model path>"
    print "Found " + str(len(sys.argv)) + " arguments, expected " + str(NUM_ARGS) + " arguments"
    sys.exit(-1)

GROUNDTRUTH_PATH = sys.argv[1]
MODEL_PATH = sys.argv[2]

def main():
    """Runs ObjectDetector on each dataset element and grades"""
    with open(GROUNDTRUTH_PATH, "rt") as groundtruth_handle:
        groundtruth_json = json.load(groundtruth_handle)

    object_detector = ObjectDetector(MODEL_PATH)
    metrics_computer = MetricsComputer()
    confidence_scorer = ConfidenceScorer()

    for groundtruth_elem in groundtruth_json:
        groundtruth_annots_dict = groundtruth_elem["detections"]
        path = groundtruth_elem["path"]

        groundtruth_annots = [ScoredRect.from_dict(annot_dict) for annot_dict in groundtruth_annots_dict]

        image = scipy.misc.imread(path)
        detection_annots = object_detector.run(image)
        metrics = metrics_computer.run(detection_annots, groundtruth_annots)
        confidence = confidence_scorer.run(**metrics)

        _print_grades(path, metrics, confidence)

def _print_grades(image_path, metrics, confidence):
    # Print grades for this image
    print "image: {0}".format(image_path)
    print "metrics:"
    for (name, value) in metrics.items():
        print "  {0}:{1}".format(name, value)
    print "confidence: {0}".format(confidence)
    print ""

if __name__ == "__main__":
    main()
