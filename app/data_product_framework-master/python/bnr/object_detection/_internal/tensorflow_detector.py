"""Doer module that contains TensorflowDetector

Classes:
TensorflowDetector -- Runs object detection on an image of a prescribed size
"""

import os

import numpy as np
import tensorflow as tf

from bnr.datastructs.exceptions import DatastructsValueError
from bnr.datastructs.datastructs import Rect, ScoredRect
from bnr.object_detection._internal.exceptions import VERIFICATION

class TensorflowDetector(object):
    """Runs object detection on an image of a prescribed size using a TensorFlow-based neural network"""

    _EXPECTED_RESOLUTION = (1024, 1024)
    _RECT_GRID = (32, 32)
    _INPUT_NAMES = ["x_in:0"]
    _OUTPUT_NAMES = ["decoder/concat:0", "decoder/Reshape_4:0"]

    def __init__(self, model_path):
        """Reads and fully loads the TensorFlow model located at model_path

        Arguments:
        model_path -- Path to the TensorFlow ".pb" model on the local filesystem
        """
        VERIFICATION.verify_type(model_path, str, "model_path must be of str type")
        VERIFICATION.verify_value(os.path.isfile(model_path),
                                  "model_path must point to a valid file on disk")

        model = TensorflowDetector._load_model(model_path)

        self._input_tensors = TensorflowDetector._get_tensors(model, self._INPUT_NAMES)
        self._output_tensors = TensorflowDetector._get_tensors(model, self._OUTPUT_NAMES)
        self._session = tf.Session(graph=model)

    def get_resolution(self):
        """Returns the expected resolution of the underlying neural network"""
        return self._EXPECTED_RESOLUTION

    def run(self, image):
        """Detects objects in the image and returns detected object locations with scoreidence scores

        Arguments:
        image -- A 3 channel BGR uint8 numpy.ndarray representing the image.  The dimensions
                 must be consistent with the TensorFlow model.

        Returns:
        List can be 0 or more elements long, all elements are ScoredRects
        """
        VERIFICATION.verify_image(image, self._EXPECTED_RESOLUTION)

        image_float = image.astype("float32")
        input_data = {self._input_tensors[0]: image_float}
        (raw_rects, raw_scores) = self._session.run(self._output_tensors, feed_dict=input_data)

        (rects, scores) = (TensorflowDetector._get_rects(raw_rects, self._RECT_GRID),
                           TensorflowDetector._get_scores(raw_scores))
        scored_rects = TensorflowDetector._build_scored_rects(rects, scores)

        return scored_rects

    @staticmethod
    def _load_model(model_path):
        # Loads a tensorflow model (graph) from a model (protobuf) path
        with tf.gfile.GFile(model_path, "rb") as model_proto_handle:
            model_proto = tf.GraphDef()
            model_proto.ParseFromString(model_proto_handle.read())

        # pylint: disable=not-context-manager
        with tf.Graph().as_default() as model:
            tf.import_graph_def(model_proto, input_map=None, return_elements=None, name="")

        return model

    @staticmethod
    def _get_tensors(model, names):
        # Gets tensors from a tensorflow model by names
        tensors = [model.get_tensor_by_name(name) for name in names]
        return tensors

    @staticmethod
    def _get_rects(raw_rects, rect_grid):
        # Generate array of rect params from output layer values
        (grid_rows, grid_cols) = rect_grid
        num_elems = grid_rows*grid_cols

        # Transform raw_rects to (x_center, y_center, width, height) format
        rect_shifts = np.zeros((num_elems, 4))
        rect_shifts[:, :2] = rect_grid*np.indices(rect_grid).T.reshape(num_elems, 2)
        rect_bias = np.array([grid_cols/2, grid_rows/2, 0, 0])
        rects_cen = rect_bias + rect_shifts + raw_rects[:, 0, :]

        # Transform (x_center, y_center, width, height) to ScoredRect format
        rects = rects_cen[:, [1, 1, 0, 0]] + np.array([-1, 1, -1, 1])*rects_cen[:, [3, 3, 2, 2]]/2
        return rects

    @staticmethod
    def _get_scores(raw_scores):
        # Generate array of scores from output layer values
        scores = raw_scores[:, 0, 1]
        return scores

    @staticmethod
    def _build_scored_rects(rects, scores):
        # Converts detection arrays to ScoredRects
        scored_rects = []
        for (rect, score) in zip(rects, scores):
            rect_params = tuple(map(int, map(round, rect)))
            try:
                scored_rect = ScoredRect(Rect(*rect_params), float(score))
            except DatastructsValueError:
                pass
            else:
                scored_rects.append(scored_rect)

        return scored_rects
