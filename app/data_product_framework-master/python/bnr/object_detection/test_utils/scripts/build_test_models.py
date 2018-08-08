#!/usr/bin/env python
"""Build a simple graph that conforms to the specifications required by the TensorflowDetector"""

import sys

import tensorflow as tf

# Argument parsing
NUM_ARGS = 2
if len(sys.argv) != NUM_ARGS:
    print "Usage: " + sys.argv[0] + " <output folder>"
    print "Found " + str(len(sys.argv)) + " arguments, expected " + str(NUM_ARGS) + " arguments"
    sys.exit(-1)

OUTPUT_FOLDER = sys.argv[1]

# pylint: disable=unused-variable
def main():
    """Build and save said graph to model file"""
    network = tf.Graph()
    with network.as_default():
        input_tensor = tf.placeholder(dtype=tf.float32, shape=(1024, 1024, 3), name="x_in")
        with tf.name_scope("decoder"):
            rects_tensor = tf.constant([0.0, 0.0, 1.0, 1.0], dtype=tf.float32,
                                       shape=(1024, 1, 4), name="concat")
            confs_tensor = tf.constant(0.0, dtype=tf.float32, shape=(1024, 1, 2), name="Reshape_4")

    tf.train.write_graph(network, OUTPUT_FOLDER, "valid.pb", as_text=False)

if __name__ == "__main__":
    main()
