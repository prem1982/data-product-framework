"""Contains all unit tests for the TensorflowDetector"""

import unittest

import numpy as np

from bnr.object_detection._internal.tensorflow_detector import TensorflowDetector
from bnr.object_detection._internal.exceptions import ObjectDetectionFormatError, ObjectDetectionValueError

class TensorflowDetectorTestSanity(unittest.TestCase):
    """Sanity unit test cases for the TensorflowDetector algorithm"""

    def setUp(self):
        """Define Rects used for multiple individual tests"""
        self.valid_model_path = "python/bnr/object_detection/test_utils/models/valid.pb"

    def test_invalid_model(self):
        """Invalid model paths"""
        self.assertRaises(ObjectDetectionFormatError, TensorflowDetector, None)
        self.assertRaises(ObjectDetectionValueError, TensorflowDetector, "")
        self.assertRaises(ObjectDetectionValueError, TensorflowDetector, "invalid_model_path.pb")

    def test_invalid_image(self):
        """Invalid images after valid init"""
        detector = TensorflowDetector(self.valid_model_path)

        wrong_type = None
        wrong_dtype = np.zeros((1024, 1024, 3), dtype=np.float32)
        wrong_num_chans = np.zeros((1024, 1024, 1), dtype=np.uint8)
        wrong_resolution = np.zeros((512, 512, 3), dtype=np.uint8)
        invalid_images = [wrong_type, wrong_dtype, wrong_num_chans, wrong_resolution]

        for invalid_image in invalid_images:
            self.assertRaises(ObjectDetectionFormatError, detector.run, invalid_image)

    def test_simple_model(self):
        """Validating expected behavior on a simple model"""
        detector = TensorflowDetector(self.valid_model_path)
        image = np.zeros((1024, 1024, 3), dtype=np.uint8)
        detections = detector.run(image)

        self.assertEqual(len(detections), 1024)
        for detection in detections:
            self.assertAlmostEqual(detection.score, 0.0)
            self.assertEqual(detection.rect.area(), 1)
