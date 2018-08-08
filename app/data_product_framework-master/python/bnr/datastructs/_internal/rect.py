"""Represents a rectangle"""

from bnr.datastructs._internal.exceptions import VERIFICATION

class Rect(object):
    """Represents a rectangular region of interest (ROI) of an image

    Invariants:
    -The ROI is guaranteed to consist of at least one pixel.
    """

    def __init__(self, row_start, row_end, col_start, col_end):
        """Builds a new Rect directly from the passed in arguments.

        Arguments:
        row_start -- starting row of the ROI, inclusive
        row_end -- ending row of the ROI, exclusive
        col_start -- starting col of the ROI, inclusive
        col_end -- ending col of the ROI, inclusive
        """
        VERIFICATION.verify_type(row_start, int, "row_start must be int")
        VERIFICATION.verify_type(row_end, int, "row_end must be int")
        VERIFICATION.verify_type(col_start, int, "col_start must be int")
        VERIFICATION.verify_type(col_end, int, "col_end must be int")
        VERIFICATION.verify_value(row_start < row_end, "Invalid row range, row_start must be < row_end")
        VERIFICATION.verify_value(col_start < col_end, "Invalid col range, col_start must be < col_end")

        self.row_start = row_start
        self.row_end = row_end
        self.col_start = col_start
        self.col_end = col_end

    @classmethod
    def from_dict(cls, input_dict):
        """Factory function that builds a Rect from a dict"""
        expected_keys = set(["row_start", "row_end", "col_start", "col_end"])
        VERIFICATION.verify_type(input_dict, dict, "input must be dict")
        VERIFICATION.verify_value(set(input_dict.keys()) == expected_keys,
                                  "expected keys: {0}".format(expected_keys))

        return cls(input_dict["row_start"],
                   input_dict["row_end"],
                   input_dict["col_start"],
                   input_dict["col_end"])

    def to_tuple(self):
        """Returns a tuple that represents the Rect

        Returns:
        A tuple in the following form:
        (row_start, row_end, col_start, col_end})
        """
        return (self.row_start, self.row_end, self.col_start, self.col_end)

    def to_dict(self):
        """Returns a dict that represents the Rect

        Returns:
        A dict in the following form:
        {"row_start":row_start,
         "row_end":row_end,
         "col_start":col_start,
         "col_end":col_end}
        """
        return self.__dict__


    def area(self):
        """Returns the area of the Rect in number of pixels

        Returns:
        The computed area
        """
        num_rows = self.row_end - self.row_start
        num_cols = self.col_end - self.col_start
        area = num_rows*num_cols
        return area

    def intersection(self, other):
        """Returns the intersection between the current Rect and the input Rect

        Computes and returns a Rect whose ROI covers the exact overlapping region between the
        current object's ROI and the passed in Rect's ROI if such region consists of at least one
        pixel or None if such region is empty.

        Arguments:
        other -- The Rect to compute the intersection against

        Returns:
        A Rect representing the intersection or None if the intersection is empty
        """
        VERIFICATION.verify_type(other, Rect, "intersection target must be Rect")

        funcs = (max, min, max, min)
        intersection_tuple = self._apply_binary_funcs(other, funcs)

        (inter_row_start, inter_row_end, inter_col_start, inter_col_end) = intersection_tuple
        if inter_row_start >= inter_row_end or inter_col_start >= inter_col_end:
            return None

        return Rect(*intersection_tuple)

    def union(self, other):
        """Returns the union between the current Rect and the input Rect

        Computes and returns a Rect of the smallest possible area whose ROI covers both the
        current object's ROI and the passed in Rect's ROI.

        Arguments:
        other -- The Rect to compute the union against

        Returns:
        A Rect representing the union
        """
        VERIFICATION.verify_type(other, Rect, "union target must be Rect")

        funcs = (min, max, min, max)
        union_tuple = self._apply_binary_funcs(other, funcs)
        return Rect(*union_tuple)

    def overlap_ratio(self, other):
        """Returns a measure of overlap between the current and the passed in Rect

        Arguments:
        other -- The Rect to compute the overlap_ratio against

        Returns:
        A measure of the degree of overlap between the current Rect and the passed in Rect.  Larger
        ratios indicate higher degrees of overlap.  A ratio of 0.0 indicates there is no overlap
        and a ratio of 1.0 indicates the two Rects have identical underlying ROIs.
        """
        VERIFICATION.verify_type(other, Rect, "overlap_ratio target must be Rect")

        intersection_rect = self.intersection(other)
        if intersection_rect is None:
            return 0.0

        union_rect = self.union(other)

        overlap_score = float(intersection_rect.area())/float(union_rect.area())
        return overlap_score

    def cover_ratio(self, other):
        """Returns a measure of cover between the current and the passed in Rect

        Arguments:
        other -- The Rect to compute the cover_ratio against

        Returns:
        A measure of the degree of encapsulation between the current Rect and the passed in Rect.
        Larger ratios indicate higher degrees of encapsulation.  A ratio of 0.0 indicates there
        is no encapsulation and a ratio of 1.0 indicates one Rect is completely contained in the
        other.
        """
        VERIFICATION.verify_type(other, Rect, "cover_ratio target must be Rect")

        intersection_rect = self.intersection(other)
        if intersection_rect is None:
            return 0.0

        smaller_rect = self if self.area() < other.area() else other
        cover_score = float(intersection_rect.area())/float(smaller_rect.area())
        return cover_score

    def shifted(self, offset):
        """Shifts and returns a new Rect

        Arguments:
        offset -- The offset to shift the Rect by number of pixels (row_shift, col_shift)
        """
        (row_shift, col_shift) = offset

        return Rect(self.row_start + row_shift,
                    self.row_end + row_shift,
                    self.col_start + col_shift,
                    self.col_end + col_shift)

    def __eq__(self, other):
        """Two Rects are equal when their respective params are equal"""
        rows_same = self.row_start == other.row_start and self.row_end == other.row_end
        cols_same = self.col_start == other.col_start and self.col_end == other.col_end

        return rows_same and cols_same

    def __ne__(self, other):
        """Inverse of equality"""
        return not self.__eq__(other)

    def __hash__(self):
        """Hash based off of the data members"""
        return hash((self.row_start, self.row_end, self.col_start, self.col_end))

    def __repr__(self):
        """Returns a displayable string to represent this Rect"""
        return "[{0}:{1}, {2}:{3}]".format(*self.to_tuple())

    def _apply_binary_funcs(self, other, funcs):
        # Applies generic binary functions to respective pairs of values
        operations = zip(self.to_tuple(), other.to_tuple(), funcs)
        results = tuple([func(val1, val2) for (val1, val2, func) in operations])
        return results
