"""Contains all unit tests for the ImageChunker"""

import unittest

import numpy as np

from bnr.object_detection._internal.exceptions import ObjectDetectionFormatError, ObjectDetectionValueError
from bnr.object_detection._internal.image_chunker import ImageChunker

class ImageChunkerTest(unittest.TestCase):
    """Unit test cases for the ImageChunker algorithm"""

    def setUp(self):
        # Define different image and chunk params to test chunker
        # Each element: (image_shape, chunk_size, chunk_stride)
        self.one_chunk = ((1, 1, 3), (1, 1), (1, 1))
        self.adjacent_chunks = ((4, 2, 3), (2, 1), (2, 1))
        self.overlapping_chunks = ((4, 2, 3), (2, 1), (1, 1))

    def test_invalid_inputs(self):
        """Tests that object rejects invalid inputs"""
        self._test_dims([None, 0, (1, 2, 3), (1, 1.0), (1.0, 1)], ObjectDetectionFormatError)
        self._test_dims([(0, 1), (1, 0), (-1, 1), (1, -1)], ObjectDetectionValueError)

    def test_invalid_image(self):
        """Tests case where the image is invalid"""
        self.assertRaises(ObjectDetectionFormatError, ImageChunkerTest._get_chunks_from_image,
                          None, (1, 1), (1, 1))
        self.assertRaises(ObjectDetectionFormatError, ImageChunkerTest._get_chunks,
                          (3, 1, 1), (1, 1), (1, 1), np.float32)
        self.assertRaises(ObjectDetectionFormatError, ImageChunkerTest._get_chunks,
                          (1, 1), (1, 1), (1, 1), np.uint8)
        self.assertRaises(ObjectDetectionFormatError, ImageChunkerTest._get_chunks,
                          (1, 1, 1), (1, 1), (1, 1), np.uint8)

    def test_one_chunk(self):
        """Tests case where the image is the (single) chunk"""
        test_params = self.one_chunk

        chunking_results = ImageChunkerTest._get_chunks(*test_params)
        self.assertEqual(len(chunking_results), 1)
        self._validate_chunk_consistency(chunking_results, test_params[1:])

    def test_adjacent_chunks(self):
        """Tests case where chunks are adjacent"""
        test_params = self.adjacent_chunks

        chunking_results = ImageChunkerTest._get_chunks(*test_params)
        self.assertEqual(len(chunking_results), 4)
        self._validate_chunk_consistency(chunking_results, test_params[1:])

    def test_overlapping_chunks(self):
        """Tests case where chunks overlap"""
        test_params = self.overlapping_chunks

        chunking_results = ImageChunkerTest._get_chunks(*test_params)
        self.assertEqual(len(chunking_results), 6)
        self._validate_chunk_consistency(chunking_results, test_params[1:])

    def _test_dims(self, dims_list, exception):
        # Ensures ImageChunker rejects invalid dims
        for dims in dims_list:
            self.assertRaises(exception, ImageChunker, dims, (1, 1))
            self.assertRaises(exception, ImageChunker, (1, 1), dims)

    def _validate_chunk_consistency(self, chunking_results, chunk_params):
        # Validates certain properties of chunks that should hold
        (chunk_size, chunk_stride) = chunk_params
        expected_chunk_shape = (chunk_size[0], chunk_size[1], 3)

        for chunk_info in chunking_results:
            (chunk_origin, chunk) = chunk_info
            # Chunk origin should be aligned to the stride
            self.assertEqual(chunk_origin[0] % chunk_stride[0], 0)
            self.assertEqual(chunk_origin[1] % chunk_stride[1], 0)
            # Test chunk size is as expected
            self.assertEqual(chunk.shape, expected_chunk_shape)

    @staticmethod
    def _get_chunks(image_shape, chunk_size, chunk_stride, dtype=np.uint8):
        # Get all chunks from an image of all zeros
        image = np.zeros(image_shape, dtype=dtype)
        return ImageChunkerTest._get_chunks_from_image(image, chunk_size, chunk_stride)

    @staticmethod
    def _get_chunks_from_image(image, chunk_size, chunk_stride):
        # Get all chunks from the given image
        chunker = ImageChunker(chunk_size, chunk_stride)
        chunking_results = [chunk_info for chunk_info in chunker.get_chunked_images(image)]
        return chunking_results
