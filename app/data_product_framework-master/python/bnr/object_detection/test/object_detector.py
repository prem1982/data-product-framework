"""Contains all unit tests for the ObjectDetector"""

import unittest

import numpy as np
from mock import patch

from bnr.datastructs.datastructs import Rect, ScoredRect
from bnr.object_detection._internal.exceptions import ObjectDetectionFormatError
from bnr.object_detection._internal.object_detector import ObjectDetector

CHUNKER_PATH = "bnr.object_detection._internal.object_detector.ImageChunker"
TF_DETECTOR_PATH = "bnr.object_detection._internal.object_detector.TensorflowDetector"
DEDUPER_PATH = "bnr.object_detection._internal.object_detector.DetectionDeduplicator"

@patch(DEDUPER_PATH)
@patch(TF_DETECTOR_PATH)
@patch(CHUNKER_PATH)
class ObjectDetectorTest(unittest.TestCase):
    """ unit test cases for the ObjectDetector algorithm"""

    def setUp(self):
        """Define objects used for multiple individual tests"""
        self.dummy_model_path = ""
        self.dummy_resolution = (1, 1)
        self.dummy_image = np.zeros((1, 1, 3), dtype=np.uint8)

    def test_invalid_image(self, mock_chunker, mock_tf_detector, mock_deduper):
        """Invalid images after valid init"""
        ObjectDetectorTest._set_chunker_outs(mock_chunker, [])
        ObjectDetectorTest._set_tf_detector_outs(mock_tf_detector, self.dummy_resolution, [[]])
        ObjectDetectorTest._set_deduper_outs(mock_deduper, [[]])

        detector = ObjectDetector(self.dummy_model_path)

        wrong_type = None
        wrong_dtype = np.zeros((2048, 1024, 3), dtype=np.float32)
        wrong_num_chans = np.zeros((2048, 1024, 1), dtype=np.uint8)
        invalid_images = [wrong_type, wrong_dtype, wrong_num_chans]

        for invalid_image in invalid_images:
            self.assertRaises(ObjectDetectionFormatError, detector.run, invalid_image)

    def test_trivial_detection(self, mock_chunker, mock_tf_detector, mock_deduper):
        """Validating expected behavior on trivial mocks"""
        ObjectDetectorTest._set_chunker_outs(mock_chunker, [])
        ObjectDetectorTest._set_tf_detector_outs(mock_tf_detector, self.dummy_resolution, [])
        ObjectDetectorTest._set_deduper_outs(mock_deduper, [[]])

        detector = ObjectDetector(self.dummy_model_path)
        detections = detector.run(self.dummy_image)
        self.assertEqual(detections, [])

        self._validate_mock_calls(mock_chunker, mock_tf_detector, mock_deduper)

    def test_typical_detection(self, mock_chunker, mock_tf_detector, mock_deduper):
        """Validating expected behavior on typical mocks"""
        chunk = np.zeros((1024, 1024, 3), dtype=np.uint8)
        chunks = [((0, 0), chunk), ((512, 0), chunk), ((1024, 0), chunk)]
        tf_dets = [[ScoredRect(Rect(0, 512, 0, 512), 0.5)],
                   [ScoredRect(Rect(0, 512, 0, 512), 0.0)],
                   [ScoredRect(Rect(0, 10, 0, 10), 0.5),
                    ScoredRect(Rect(0, 512, 0, 512), 0.4)],
                  ]

        ObjectDetectorTest._set_chunker_outs(mock_chunker, chunks)
        ObjectDetectorTest._set_tf_detector_outs(mock_tf_detector, self.dummy_resolution, tf_dets)
        ObjectDetectorTest._set_deduper_outs(mock_deduper, lambda x: x)

        detector = ObjectDetector(self.dummy_model_path)
        detections = detector.run(self.dummy_image)
        expected_output = [ScoredRect(Rect(0, 512, 0, 512), 0.5),
                           ScoredRect(Rect(1024, 1536, 0, 512), 0.4),
                          ]
        self.assertEqual(detections, expected_output)

        self._validate_mock_calls(mock_chunker, mock_tf_detector, mock_deduper)

    def _validate_mock_calls(self, mock_chunker, mock_tf_detector, mock_deduper):
        # Helper method to validate expected mock calls
        mock_tf_detector().get_resolution.assert_called_once()
        mock_chunker().get_chunked_images.assert_called_once()
        mock_deduper().run.assert_called_once()

        num_out_chunks = len(mock_chunker.return_value.get_chunked_images.return_value)
        self.assertEqual(mock_tf_detector().run.call_count, num_out_chunks)

    @staticmethod
    def _set_chunker_outs(mock_chunker, out_chunks):
        # Sets outputs to mock ImageChunker
        mock_chunker.return_value.get_chunked_images.return_value = out_chunks

    @staticmethod
    def _set_tf_detector_outs(mock_tf_detector, out_resolution, out_dets):
        # Sets outputs to mock TensorflowDetector
        mock_tf_detector.return_value.get_resolution.return_value = out_resolution
        mock_tf_detector.return_value.run.side_effect = out_dets

    @staticmethod
    def _set_deduper_outs(mock_deduper, out_dets):
        # Sets outputs to mock DetectionDeduplicator
        mock_deduper.return_value.run.side_effect = out_dets
