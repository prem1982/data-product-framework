# data\_product\_framework
Repository which houses Bossa Nova Robotics' data\_product library and associated tests/services

## Setup

### Dependencies
#### Connecting to JFrog Artifactory
Some of the dependencies of this repository are installed from BN's JFrog Artifactory server. In order to install these dependencies, you will have to run the `apt_setup.bash` command in [bnr\_robot\_software](https://github.com/BossaNova/bnr_robot_software). Note that you do not have to run any of the preceding steps detailed in the `README.md` (other than, obviously, cloning the repository) in order to complete your JFrog Artifactory setup.
#### Installing Dependencies
After your JFrog Artifactory setup is complete, you can run `./build/install_deps.sh` to install the dependencies of this repository.

### Bazel
This repository is built with [Bazel](https://bazel.build/).
#### Installing Bazel
Bazel is installed for you via the `install_deps.sh` script. If you wish to manually install Bazel, you can find installation instructions [here](https://docs.bazel.build/versions/master/install-ubuntu.html#install-on-ubuntu).

## Compiling the Repository, Running Unit Tests, and Building the Debian
To compile the repository, run `bazel build --config=release :data_product`

To run all the unit tests, run `bazel test --config=release :data_product_tests`

To build the debian, run `bazel build --config=release :bnr_data_product-debian"`

You can build and test in debug mode by replacing `--config=release` with `--config=debug`.
