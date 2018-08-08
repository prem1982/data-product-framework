"""Contains all unit tests for the ScoredRect data structure"""

import unittest

from bnr.datastructs._internal.exceptions import DatastructsFormatError
from bnr.datastructs._internal.rect import Rect
from bnr.datastructs._internal.scored_rect import ScoredRect

class ScoredRectTestSanity(unittest.TestCase):
    """Simple unit test cases for the ScoredRect data structure"""

    def setUp(self):
        """Create and set ScoredRects used for multiple individual tests"""
        self.single_pixel = ScoredRect(Rect(0, 1, 2, 3), 0.0)
        self.first_rectangle = ScoredRect(Rect(1, 4, 2, 6), 0.0)
        self.second_rectangle = ScoredRect(Rect(2, 5, 3, 7), 0.0)
        self.single_pixel_dict = {"rect":{"row_start":0, "row_end":1, "col_start":2, "col_end":3},
                                  "score":0.0}

    def test_invalid_inputs(self):
        """Tests object rejects invalid inputs"""
        valid_rect = Rect(0, 1, 2, 3)
        self.assertRaises(DatastructsFormatError, ScoredRect, None, 0.0)
        self.assertRaises(DatastructsFormatError, ScoredRect, 0, 0.0)
        self.assertRaises(DatastructsFormatError, ScoredRect, valid_rect, None)
        self.assertRaises(DatastructsFormatError, ScoredRect, valid_rect, 0)

    def test_from_dict(self):
        """Tests ScoredRect.from_dict()"""
        self.assertEqual(ScoredRect.from_dict(self.single_pixel_dict), self.single_pixel)

    def test_to_tuple(self):
        """Tests ScoredRect.to_tuple()"""
        self.assertEqual(self.single_pixel.to_tuple(), ((0, 1, 2, 3), 0.0))

    def test_to_dict(self):
        """Tests ScoredRect.to_dict()"""
        self.assertEqual(self.single_pixel.to_dict(), self.single_pixel_dict)

    def test_shifted(self):
        """Simple tests for ScoredRect.shifted()"""
        offset = (-1, 1)
        self.assertEqual(self.single_pixel.shifted(offset), ScoredRect(Rect(-1, 0, 3, 4), 0.0))

    def test_equality(self):
        """Simple tests for equality"""
        self.assertEqual(self.single_pixel, self.single_pixel)
        self.assertEqual(self.single_pixel, ScoredRect(Rect(0, 1, 2, 3), 0.0))
        self.assertNotEqual(self.single_pixel, ScoredRect(Rect(0, 1, 2, 4), 0.0))
        self.assertNotEqual(self.single_pixel, ScoredRect(Rect(0, 1, 2, 3), 1.0))
