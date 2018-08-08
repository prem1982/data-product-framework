"""For ParamsReader"""

import sys
import os

sys.path.append("./python/")

# pylint: disable=wrong-import-position
from pylibs.test_utils.json_helper import build_size_json, build_rect_json, save_json

def _build_params_reader_full(output_file):
    # Builds and writes ParamsReader json
    json = dict()
    label_reader_json = dict()
    label_reader_json["scale_factor"] = 0.1
    label_reader_json["nominal_patch"] = build_rect_json(0.7, 0.8, 0.9, 1.0)

    # price detector
    price_detector_json = dict()
    pre_processor_json = dict()
    pre_processor_json["adaptive_thresh_blocksize"] = 1
    pre_processor_json["adaptive_thresh_mean_value"] = 2
    mser_doer_json = dict()
    mser_doer_json["open_kernel_size"] = build_size_json(4, 3)
    mser_doer_json["close_kernel_size"] = build_size_json(6, 5)
    mser_doer_json["mop_kernel_size"] = build_size_json(8, 7)
    mser_doer_json["erode_kernel_size"] = build_size_json(10, 9)
    mser_doer_json["delta"] = 11
    mser_doer_json["min_area"] = 12
    mser_doer_json["max_area"] = 13
    mser_doer_json["max_variation"] = 0.01
    mser_doer_json["min_diversity"] = 0.02
    mser_doer_json["group_threshold"] = 14
    mser_doer_json["group_epsilon"] = 0.2
    post_processor_json = dict()
    post_processor_json["min_area"] = 15
    post_processor_json["max_area"] = 16
    post_processor_json["height_thresh"] = 17
    post_processor_json["distance_thresh"] = 18
    post_processor_json["y_thresh"] = 19
    post_processor_json["min_aspect"] = 0.3
    post_processor_json["max_aspect"] = 0.4
    post_processor_json["img_buffer"] = 20
    post_processor_json["group_threshold"] = 21
    post_processor_json["group_epsilon"] = 0.5
    price_detector_json["PreProcessorParams"] = pre_processor_json
    price_detector_json["MserDoerParams"] = mser_doer_json
    price_detector_json["PostProcessorParams"] = post_processor_json
    label_reader_json["PriceDetectorParams"] = price_detector_json

    # price reader
    price_reader_json = dict()
    pre_processor_json = dict()
    pre_processor_json["denoising_h"] = 0.6
    pre_processor_json["denoising_templateWindowSize"] = 22
    pre_processor_json["denoising_searchWindowSize"] = 23
    price_reader_json["PreProcessorParams"] = pre_processor_json
    label_reader_json["PriceReaderParams"] = price_reader_json

    # set and save final json
    json["LabelReaderParams"] = label_reader_json
    save_json(output_file, json)

def main():
    """Builds and writes simple json config files"""
    base_folder = sys.argv[1]
    _build_params_reader_full(os.path.join(base_folder, "params_reader_full.json"))

if __name__ == "__main__":
    main()
