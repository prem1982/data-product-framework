"""Contains all unit tests for the Rect data structure"""

import itertools
import unittest

from bnr.datastructs._internal.exceptions import DatastructsFormatError, DatastructsValueError
from bnr.datastructs._internal.rect import Rect

class RectTestSanity(unittest.TestCase):
    """Simple unit test cases for the Rect data structure"""

    def setUp(self):
        """Creates Rects used for multiple individual tests"""
        self.single_pixel = Rect(0, 1, 2, 3)
        self.first_rectangle = Rect(1, 4, 2, 6)
        self.second_rectangle = Rect(2, 5, 3, 7)
        self.single_pixel_dict = {"row_start":0, "row_end":1, "col_start":2, "col_end":3}

    def test_invalid_inputs(self):
        """Tests object rejects invalid inputs"""
        self.assertRaises(DatastructsFormatError, Rect, 0.0, 1, 0, 1)
        self.assertRaises(DatastructsFormatError, Rect, 0, 1.0, 0, 1)
        self.assertRaises(DatastructsFormatError, Rect, 0, 1, 0.0, 1)
        self.assertRaises(DatastructsFormatError, Rect, 0, 1, 0, 1.0)
        self.assertRaises(DatastructsValueError, Rect, 1, 0, 0, 1)
        self.assertRaises(DatastructsValueError, Rect, 0, 1, 1, 0)
        self.assertRaises(DatastructsValueError, Rect, 0, 1, 0, 0)
        self.assertRaises(DatastructsValueError, Rect, 0, 0, 0, 1)

    def test_from_dict(self):
        """Tests Rect.from_dict()"""
        self.assertEqual(Rect.from_dict(self.single_pixel_dict), self.single_pixel)

    def test_to_tuple(self):
        """Tests Rect.to_tuple()"""
        self.assertEqual(self.single_pixel.to_tuple(), (0, 1, 2, 3))

    def test_to_dict(self):
        """Tests Rect.to_dict()"""
        self.assertEqual(self.single_pixel.to_dict(), self.single_pixel_dict)

    def test_area(self):
        """Simple tests for Rect.area()"""
        self.assertEqual(self.single_pixel.area(), 1)
        self.assertEqual(self.first_rectangle.area(), 12)
        self.assertEqual(self.second_rectangle.area(), 12)

    def test_intersection(self):
        """Simple tests for Rect.intersection()"""
        self.assertRaises(DatastructsFormatError, self.single_pixel.intersection, None)
        # A pixel against itself
        intersection_same_rects = self.single_pixel.intersection(self.single_pixel)
        self.assertEqual(intersection_same_rects, self.single_pixel)
        # Two rectangles partially overlapping
        intersection_diff_rects = self.first_rectangle.intersection(self.second_rectangle)
        self.assertEqual(intersection_diff_rects, Rect(2, 4, 3, 6))

    def test_union(self):
        """Simple tests for Rect.union()"""
        self.assertRaises(DatastructsFormatError, self.single_pixel.union, None)
        # A pixel against itself
        union_same_rects = self.single_pixel.union(self.single_pixel)
        self.assertEqual(union_same_rects, self.single_pixel)
        # Two rectangles partially overlapping
        union_diff_rects = self.first_rectangle.union(self.second_rectangle)
        self.assertEqual(union_diff_rects, Rect(1, 5, 2, 7))

    def test_overlap_ratio(self):
        """Simple tests for Rect.overlap_ratio()"""
        self.assertRaises(DatastructsFormatError, self.single_pixel.overlap_ratio, None)
        # A pixel against itself
        overlap_ratio_same_rects = self.single_pixel.overlap_ratio(self.single_pixel)
        self.assertAlmostEqual(overlap_ratio_same_rects, 1.0)
        # Two rectangles partially overlapping
        overlap_diff_rects = self.first_rectangle.overlap_ratio(self.second_rectangle)
        self.assertAlmostEqual(overlap_diff_rects, 0.3)

    def test_cover_ratio(self):
        """Simple tests for Rect.cover_ratio()"""
        self.assertRaises(DatastructsFormatError, self.single_pixel.cover_ratio, None)
        # A pixel against itself
        cover_ratio_same_rects = self.single_pixel.cover_ratio(self.single_pixel)
        self.assertAlmostEqual(cover_ratio_same_rects, 1.0)
        # Two rectangles partially covering
        cover_diff_rects = self.first_rectangle.cover_ratio(self.second_rectangle)
        self.assertAlmostEqual(cover_diff_rects, 0.5)

    def test_shifted(self):
        """Simple tests for Rect.shifted()"""
        offset = (-1, 1)
        self.assertEqual(self.single_pixel.shifted(offset), Rect(-1, 0, 3, 4))

    def test_equality(self):
        """Simple tests for equality"""
        self.assertEqual(self.single_pixel, self.single_pixel)
        self.assertEqual(self.single_pixel, Rect(0, 1, 2, 3))
        self.assertNotEqual(self.single_pixel, Rect(0, 1, 2, 4))

class RectTestAutomated(unittest.TestCase):
    """Automated test cases for the Rect data structure"""

    def setUp(self):
        """Creates lists of Rects used for multiple individual tests"""
        # Same area and mutually disjoint
        self.lines = [Rect(0, 1, 0, 5),
                      Rect(-5, 0, 0, 1),
                     ]
        self.rectangles = [Rect(0, 4, 0, 2),
                           Rect(-4, 0, -2, 0),
                           Rect(0, 4, -2, 0),
                           Rect(-4, 0, 0, 2),
                          ]

        # Only mutually disjoint
        self.mixed = [Rect(0, 1, 0, 1),
                      Rect(33, 34, 33, 34),
                      Rect(1, 2, 1, 3),
                      Rect(-5, -1, -4, -3),
                      Rect(-4, 4, 10, 20),
                      Rect(-4, -2, 30, 40),
                      Rect(-50, -30, -3, -1),
                      Rect(-40, -35, -100, -90),
                     ]

    def test_area(self):
        """Automatable tests for Rect.area()"""
        self._validate_all_areas(self.lines, 5)
        self._validate_all_areas(self.rectangles, 8)

    def test_intersection(self):
        """Automatable tests for Rect.intersection()"""
        self._validate_disjoint_intersections(self.lines)
        self._validate_disjoint_intersections(self.rectangles)
        self._validate_disjoint_intersections(self.mixed)

    def test_union(self):
        """Automatable tests for Rect.union()"""
        self._validate_disjoint_unions(self.lines)
        self._validate_disjoint_unions(self.rectangles)
        self._validate_disjoint_unions(self.mixed)

    def test_overlap_ratio(self):
        """Automatable tests for Rect.overlap_ratio()"""
        self._validate_disjoint_overlap_ratios(self.lines)
        self._validate_disjoint_overlap_ratios(self.rectangles)
        self._validate_disjoint_overlap_ratios(self.mixed)

    def test_cover_ratio(self):
        """Automatable tests for Rect.cover_ratio()"""
        self._validate_disjoint_cover_ratios(self.lines)
        self._validate_disjoint_cover_ratios(self.rectangles)
        self._validate_disjoint_cover_ratios(self.mixed)

    def _validate_all_areas(self, rects, target_area):
        # Ensure all rects have the same target_area
        for rect in rects:
            self.assertEqual(rect.area(), target_area)

    def _validate_disjoint_intersections(self, rects):
        # Ensures proper Rect.intersection behavior on mutually disjoint Rects
        for rect in rects:
            self.assertEqual(rect.intersection(rect), rect)
        for (rect1, rect2) in itertools.combinations(rects, 2):
            self.assertIsNone(rect1.intersection(rect2))

    def _validate_disjoint_unions(self, rects):
        # Ensures proper Rect.union behavior on mutually disjoint Rects
        for rect in rects:
            self.assertEqual(rect.union(rect), rect)
        for (rect1, rect2) in itertools.combinations(rects, 2):
            self.assertTrue(rect1.union(rect2).area() >= (rect1.area() + rect2.area()))

    def _validate_disjoint_overlap_ratios(self, rects):
        # Ensures proper Rect.overlap_ratio behavior on mutually disjoint Rects
        for rect in rects:
            self.assertAlmostEqual(rect.overlap_ratio(rect), 1.0)
        for (rect1, rect2) in itertools.combinations(rects, 2):
            self.assertAlmostEqual(rect1.overlap_ratio(rect2), 0.0)

    def _validate_disjoint_cover_ratios(self, rects):
        # Ensures proper Rect.cover_ratio behavior on mutually disjoint Rects
        for rect in rects:
            self.assertAlmostEqual(rect.cover_ratio(rect), 1.0)
        for (rect1, rect2) in itertools.combinations(rects, 2):
            self.assertAlmostEqual(rect1.cover_ratio(rect2), 0.0)
