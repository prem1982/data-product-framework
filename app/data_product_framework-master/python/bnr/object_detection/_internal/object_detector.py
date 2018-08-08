"""Doer module that contains ObjectDetector

Classes:
ObjectDetector -- Runs end to end object detection on an image of arbitrary size
"""

from bnr.object_detection._internal.exceptions import VERIFICATION
from bnr.object_detection._internal.image_chunker import ImageChunker
from bnr.object_detection._internal.tensorflow_detector import TensorflowDetector
from bnr.object_detection._internal.detection_deduplicator import DetectionDeduplicator

class ObjectDetector(object):
    """Runs user-facing object detection on images of arbitrary sizes"""

    _CHUNK_STRIDE_FACTOR = (2, 2)
    # Filter params
    _MIN_AREA = 5000
    _MIN_SCORE = 0.20

    def __init__(self, model_path):
        """Loads all components of the ObjectDetector

        Arguments:
        model_path -- TensorflowDetector model path
        """
        # Create sub-objects
        tensorflow_detector = TensorflowDetector(model_path)

        chunk_size = tensorflow_detector.get_resolution()
        chunk_stride = tuple([max(1, size/factor) for (size, factor) in
                              zip(chunk_size, self._CHUNK_STRIDE_FACTOR)])
        image_chunker = ImageChunker(chunk_size, chunk_stride)
        detection_deduplicator = DetectionDeduplicator()

        # Set data members
        self._image_chunker = image_chunker
        self._tensorflow_detector = tensorflow_detector
        self._detection_deduplicator = detection_deduplicator

    def run(self, image):
        """Detects objects in the image and returns detected object locations with confidence scores

        Arguments:
        image -- A 3 channel BGR uint8 numpy.ndarray representing the full image

        Returns:
        List can be 0 or more elements long, all elements are ScoredRects
        """
        VERIFICATION.verify_image(image)

        all_dets = []
        for (chunk_origin, chunk) in self._image_chunker.get_chunked_images(image):
            chunk_dets = self._tensorflow_detector.run(chunk)
            image_dets = [det.shifted(chunk_origin) for det in chunk_dets]
            filtered_dets = [det for det in image_dets if
                             det.rect.area() > self._MIN_AREA and
                             det.score > self._MIN_SCORE]
            all_dets.extend(filtered_dets)

        deduped_dets = self._detection_deduplicator.run(all_dets)
        return deduped_dets
