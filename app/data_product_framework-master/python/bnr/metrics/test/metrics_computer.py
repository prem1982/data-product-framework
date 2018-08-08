"""Contains all unit tests for the MetricsComputer"""

import unittest

from bnr.metrics._internal.metrics_computer import MetricsComputer
from bnr.metrics._internal.exceptions import MetricsFormatError
from bnr.datastructs.datastructs import Rect, ScoredRect

class MetricsComputerSanityTest(unittest.TestCase):
    """Sanity unit test cases for the MetricsComputer"""

    def setUp(self):
        """Define inputs used for multiple individual tests"""
        self.single_box = [ScoredRect(Rect(0, 10, 0, 20), 0.0)]

        self.ground_truths = [ScoredRect(Rect(0, 10, 0, 10), 0.5),
                              ScoredRect(Rect(10, 20, 20, 30), 0.5),
                              ScoredRect(Rect(-40, -30, -20, -10), 0.5),
                             ]
        self.detections = [ScoredRect(Rect(0, 10, 0, 10), 0.5),
                           ScoredRect(Rect(10, 20, 20, 30), 0.5),
                           ScoredRect(Rect(10, 20, 20, 30), 0.5),
                           ScoredRect(Rect(100, 110, 20, 30), 0.5),
                          ]
    def test_invalid_inputs(self):
        """Invalid inputs"""
        bad_args = [None, 0, ScoredRect(Rect(0, 1, 0, 1), 0.5), [Rect(0, 1, 0, 1)]]
        self._test_bad_args(bad_args)

    def test_no_inputs(self):
        """No detections and no ground_truths"""
        expected_accuracy = dict(num_recall=0, uniq_recall=0, num_precision=0, uniq_precision=0)
        self._run_and_validate([], [], expected_accuracy)

    def test_no_detections(self):
        """No detections but some ground_truths"""
        expected_accuracy = dict(num_recall=0, uniq_recall=0, num_precision=0, uniq_precision=0)
        self._run_and_validate([], self.single_box, expected_accuracy)

    def test_no_ground_truths(self):
        """No ground truths but some detections"""
        expected_accuracy = dict(num_recall=0, uniq_recall=0, num_precision=0, uniq_precision=0)
        self._run_and_validate(self.single_box, [], expected_accuracy)

    def test_hardcoded_example(self):
        """Validate a simple, hardcoded example"""
        expected_accuracy = dict(num_recall=2, uniq_recall=2, num_precision=3, uniq_precision=2)
        self._run_and_validate(self.detections, self.ground_truths, expected_accuracy)

    def _test_bad_args(self, arg_list):
        # Ensures MetricsComputer rejects invalid args
        for arg in arg_list:
            self.assertRaises(MetricsFormatError, MetricsComputer().run, arg, self.single_box)
            self.assertRaises(MetricsFormatError, MetricsComputer().run, self.single_box, arg)

    def _run_and_validate(self, detections, ground_truths, expected_accuracy):
        # Runs and validates a sanity test
        expected_output = dict(max_recall=len(ground_truths), max_precision=len(detections),
                               **expected_accuracy)
        actual_output = MetricsComputer().run(detections, ground_truths)
        self.assertEqual(expected_output, actual_output)

class MetricsComputerAutomatedTest(unittest.TestCase):
    """Automatable unit test cases for MetricsComputer"""

    def setUp(self):
        """Define lists of automatically generated inputs"""
        roi_size = 5
        num_annots = 10
        anchor = ScoredRect(Rect(0, roi_size, 0, roi_size), 0.5)

        self.ground_truths = MetricsComputerAutomatedTest._build_annots(anchor, (0, roi_size), num_annots)
        self.true_dets = [det for det in self.ground_truths]
        self.false_dets = [det.shifted((roi_size, 0)) for det in self.ground_truths]
        self.mixed_dets = self.true_dets[::2] + self.false_dets[1::2]
        self.duplicate_true_dets = self.true_dets + self.true_dets

    def test_false_detections(self):
        """All detections completely miss all ground truths"""
        expected_accuracy = dict(num_recall=0, uniq_recall=0, num_precision=0, uniq_precision=0)
        self._run_and_validate(self.false_dets, self.ground_truths, expected_accuracy)

    def test_true_detections(self):
        """All detections exactly match their respective ground truths"""
        expected_accuracy = dict(num_recall=10, uniq_recall=10, num_precision=10, uniq_precision=10)
        self._run_and_validate(self.true_dets, self.ground_truths, expected_accuracy)

    def test_mixed_detections(self):
        """Half detections miss, half hit the ground truths"""
        expected_accuracy = dict(num_recall=5, uniq_recall=5, num_precision=5, uniq_precision=5)
        self._run_and_validate(self.mixed_dets, self.ground_truths, expected_accuracy)

    def test_duplicate_true_detections(self):
        """Two exact detections for each respective ground truths"""
        expected_accuracy = dict(num_recall=10, uniq_recall=10, num_precision=20, uniq_precision=10)
        self._run_and_validate(self.duplicate_true_dets, self.ground_truths, expected_accuracy)

    def _run_and_validate(self, detections, ground_truths, expected_accuracy):
        # Runs and validates an automated test
        expected_output = dict(max_recall=len(ground_truths), max_precision=len(detections),
                               **expected_accuracy)
        actual_output = MetricsComputer().run(detections, ground_truths)
        self.assertEqual(expected_output, actual_output)

    @staticmethod
    def _build_annots(anchor, shift, num_annots):
        # Builds a list of annotations by repeatedly shifting an anchor
        annots = []
        curr_annot = anchor
        for _ in xrange(num_annots):
            annots.append(curr_annot)
            curr_annot = curr_annot.shifted(shift)

        return annots
