"""Contains all unit tests for the DetectionDeduplicator"""

import unittest

from bnr.object_detection._internal.detection_deduplicator import DetectionDeduplicator
from bnr.object_detection._internal.exceptions import ObjectDetectionFormatError
from bnr.datastructs.datastructs import Rect, ScoredRect

class DetectionDeduplicatorTestSanity(unittest.TestCase):
    """Sanity unit test cases for the DetectionDeduplicator algorithm"""

    def setUp(self):
        """Define Rects used for multiple individual tests"""
        self.single_pixel = [ScoredRect(Rect(0, 1, 0, 1), 0.0)]
        self.close_dets = [ScoredRect(Rect(0, 10, 0, 20), 0.0),
                           ScoredRect(Rect(1, 10, 0, 20), 0.0),
                          ]
        self.far_dets = [ScoredRect(Rect(0, 10, 0, 20), 0.0),
                         ScoredRect(Rect(10, 20, 20, 40), 0.0),
                        ]

    def test_invalid_detections(self):
        """Invalid detections"""
        deduplicator = DetectionDeduplicator()
        self.assertRaises(ObjectDetectionFormatError, deduplicator.run, None)
        self.assertRaises(ObjectDetectionFormatError, deduplicator.run, Rect(0, 1, 0, 1))
        self.assertRaises(ObjectDetectionFormatError, deduplicator.run, [None])
        self.assertRaises(ObjectDetectionFormatError, deduplicator.run, [Rect(0, 1, 0, 1)])

    def test_no_detections(self):
        """No input elements"""
        deduplicator = DetectionDeduplicator()
        self.assertEqual(deduplicator.run([]), [])

    def test_single_detection(self):
        """One input element"""
        deduplicator = DetectionDeduplicator()
        self.assertEqual(deduplicator.run(self.single_pixel), self.single_pixel)

    def test_close_detections(self):
        """Two close overlapping ScoredRects"""
        deduplicator = DetectionDeduplicator()
        self.assertEqual(deduplicator.run(self.close_dets), [self.close_dets[0]])

    def test_far_detections(self):
        """Two non-overlapping ScoredRects"""
        deduplicator = DetectionDeduplicator()
        self.assertEqual(set(deduplicator.run(self.far_dets)), set(self.far_dets))

    def test_mixed_detections(self):
        """Multiple ScoredRects, some overlapping, some not"""
        input_dets = self.close_dets + self.far_dets
        deduplicator = DetectionDeduplicator()
        # In this case, close_dets happens to be duplicates of far_dets
        self.assertEqual(set(deduplicator.run(input_dets)), set(self.far_dets))

class DetectionDeduplicatorTestAutomated(unittest.TestCase):
    """Automatable unit test cases for the DetectionDeduplicator algorithm"""

    def setUp(self):
        """Define lists of Rects used for multiple individual tests"""
        # All Rects mutually overlap, first is largest
        self.close_dets = []
        for x_start in xrange(0, 10):
            curr_det = ScoredRect(Rect(x_start, 100, 0, 100), 0.0)
            self.close_dets.append(curr_det)

        # All Rects mutually disjoint
        self.far_dets = []
        for x_start in xrange(0, 100, 10):
            curr_det = ScoredRect(Rect(0, 5, 0+x_start, 5+x_start), 0.0)
            self.far_dets.append(curr_det)

    def test_close_detections(self):
        """Multiple mutually overlapping ScoredRects"""
        deduplicator = DetectionDeduplicator()
        self.assertEqual(deduplicator.run(self.close_dets), [self.close_dets[0]])

    def test_far_detections(self):
        """Multiple mutually non-overlapping ScoredRects"""
        deduplicator = DetectionDeduplicator()
        self.assertEqual(set(deduplicator.run(self.far_dets)), set(self.far_dets))
