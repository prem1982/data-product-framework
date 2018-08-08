"""Doer module that contains ImageChunker

Classes:
ImageChunker -- Decomposes image into chunks
"""

from bnr.object_detection._internal.exceptions import VERIFICATION

class ImageChunker(object):
    """Decomposes input image into potentially overlapping uniform chunks"""

    def __init__(self, chunk_size, chunk_stride):
        """Builds a new ImageChunker using the specified image chunking strides

        Arguments:
        chunk_size -- A tuple(int, int) that represents the chunk dimension in (rows, cols)
        chunk_stride -- A tuple(int, int) that represents the chunk stride in (row_stride, col_stride)
        """
        VERIFICATION.verify_dims(chunk_size, 2, "chunk_size")
        VERIFICATION.verify_dims(chunk_stride, 2, "chunk_stride")
        VERIFICATION.verify_value(chunk_size[0] >= chunk_stride[0],
                                  "chunk_num_rows must be >= chunk_row_stride")
        VERIFICATION.verify_value(chunk_size[1] >= chunk_stride[1],
                                  "chunk_num_cols must be >= chunk_col_stride")

        self._chunk_size = chunk_size
        self._chunk_stride = chunk_stride

    def get_chunked_images(self, image):
        """Generates all image chunks from the input image when iterated over

        Arguments:
        image -- A 3 channel BGR uint8 numpy.ndarray representing the image

        Returns:
        A generator that will give the next image chunk information on each iteration
        Generated value: (chunk_origin, chunk)
        chunk_origin -- (row_start, col_start)
        chunk -- A 3 channel BGR uint8 numpy.ndarray representing the chunk
        """
        VERIFICATION.verify_image(image)

        (chunk_rows, chunk_cols) = self._chunk_size
        (row_stride, col_stride) = self._chunk_stride
        (image_rows, image_cols, _) = image.shape

        row_starts = ImageChunker._get_starts(image_rows, chunk_rows, row_stride)
        col_starts = ImageChunker._get_starts(image_cols, chunk_cols, col_stride)

        for row_start in row_starts:
            for col_start in col_starts:
                chunk_origin = (row_start, col_start)
                chunk = image[row_start:row_start+chunk_rows, col_start:col_start+chunk_cols, :]
                yield (chunk_origin, chunk)

    @staticmethod
    def _get_starts(image_side, chunk_side, stride):
        # Builds list of chunking starting points for a certain dimension
        starts = list(range(0, image_side-chunk_side+1, stride))
        if image_side % chunk_side != 0:
            starts.append(image_side - chunk_side)

        return starts
