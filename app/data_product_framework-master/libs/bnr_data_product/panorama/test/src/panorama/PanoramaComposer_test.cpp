#include "gtest/gtest.h"

#include "bnr_data_product/panorama/PanoramaComposer.hpp"
#include "bnr_data_product/panorama/ProjectedImage.hpp"
#include "gtest_utils/MatUtils.hpp"

using bnr::data_product::panorama::PanoramaComposer;
using bnr::data_product::panorama::ProjectedImage;
using bnr_data_product::gtest_utils::MatUtils;

// Helper method
ProjectedImage getProjectedImage(float x, float y, int32_t num_cols, int32_t num_rows,
    int type, const cv::Scalar& pix_val = cv::Scalar(0), float meters_per_pixel = 1.0f) {
  cv::UMat image(num_rows, num_cols, type);
  image.setTo(pix_val);
  const cv::Point2f position(x, y);
  return ProjectedImage(image, position, meters_per_pixel, pix_val);
}

/* Verify exception thrown on creation of PanoramaComposer w/invalid settings */

// Resolution must be > 0
TEST(PanoramaComposer, failsOnNonPositiveResolution) {
  ASSERT_THROW(PanoramaComposer(1, 1, CV_8UC4, 0.0f), std::invalid_argument);
  ASSERT_THROW(PanoramaComposer(1, 1, CV_8UC4, -0.1f), std::invalid_argument);
}

/* Assert valid creation results in no throw */

TEST(PanoramaComposer, passessOnValidPanoInitSize) {
  ASSERT_NO_THROW(PanoramaComposer(1, 1, CV_8UC4, 1.0f));
  ASSERT_NO_THROW(PanoramaComposer(0, 0, CV_8UC4, 1.0f)); // becomes 1x1
  ASSERT_NO_THROW(PanoramaComposer(-1, -2, CV_8UC4, 1.0f)); // becomes 1x1
}

TEST(PanoramaComposer, passesOnPositiveResolution) {
  ASSERT_NO_THROW(PanoramaComposer(1, 1, CV_8UC4, 0.001f));
  ASSERT_NO_THROW(PanoramaComposer(1, 1, CV_8UC4, 1.0f));
  ASSERT_NO_THROW(PanoramaComposer(1, 1, CV_8UC1, 0.001f));
  ASSERT_NO_THROW(PanoramaComposer(1, 1, CV_32FC1, 2.0f));
}

/* Get pano immediately after construction results in default size pano  */
TEST(PanoramaComposer, getInfoFromEmptyPano) {
  {
    PanoramaComposer pc(1, 1, CV_8UC1, 1.01f);
    ASSERT_EQ(pc.getFullPano().image().size(), cv::Size(1, 1));
    ASSERT_EQ(pc.getFullPano().position(), cv::Point2f(0, 0));
  }
  {
    PanoramaComposer pc(0, 0, CV_8UC1, 1.01);
    ASSERT_EQ(pc.getFullPano().image().size(), cv::Size(1, 1));
    ASSERT_EQ(pc.getFullPano().position(), cv::Point2f(0, 0));
  }
  {
    PanoramaComposer pc(cv::Rect2f(0.0f, 0.0f, 19.6744f, 0.0f), CV_8UC1, .001f);
    ASSERT_EQ(pc.getFullPano().image().size(), cv::Size(19675, 1));
    ASSERT_EQ(pc.getFullPano().position(), cv::Point2f(0, 0));
  }
}

/* Check insert method for invalid and valid types */

// insert UMat type mismatch -> check exception thrown
TEST(PanoramaComposer, insertWrongTypeFails) {
  { // 8UC1 vs * 8UC4
    PanoramaComposer pc(1, 1, CV_8UC1, 1.0f);
    ASSERT_THROW(pc.insert(getProjectedImage(0.0f, 0.0f, 1, 1, CV_8UC4)), std::invalid_argument);
  }

  { // 8UC4 vs 8UC1
    PanoramaComposer pc(1, 1, CV_8UC4, 1.0f);
    ASSERT_THROW(pc.insert(getProjectedImage(0.0f, 0.0f, 1, 1, CV_8UC1)), std::invalid_argument);
  }
}
// Assert no throw for inserting same type
TEST(PanoramaComposer, insertSingleElementContained) {
  {
    PanoramaComposer pc(1, 1, CV_8UC1, 1.0f);
    ASSERT_NO_THROW(pc.insert(getProjectedImage(0.0f, 0.0f, 1, 1, CV_8UC1)));
  }
  {
    PanoramaComposer pc(5, 5, CV_8UC1, 1.0f);
    pc.insert(getProjectedImage(1.0f, 2.0f, 2, 2, CV_8UC1));
    ASSERT_NO_THROW(pc.insert(getProjectedImage(1.0f, 2.0f, 2, 2, CV_8UC1)));
  }
}

/* Intersection Checks */

// Intersections must always contain at least some "real" pixels, cannot be only background pix
TEST(PanoramaComposer, cannotIntersectWithEmptyPano) {
    PanoramaComposer pc(1, 1, CV_8UC1, 1.0f);
    cv::Rect2f region(0.0f, 0.0f, 1.0f, 1.0f);
    ASSERT_TRUE(pc.getIntersectPixels(region) == nullptr);
}

// valid intersection
TEST(PanoramaComposer, simpleValidIntersectingCase) {
    PanoramaComposer pc(1, 1, CV_8UC1, 1.0f);
    cv::Rect2f region(0.0f, 0.0f, 1.0f, 1.0f);

    pc.insert(getProjectedImage(0.0f, 0.0f, 1, 1, CV_8UC1));
    ASSERT_TRUE(pc.getIntersectPixels(region) != nullptr);
}

// valid non-intersection
TEST(PanoramaComposer, noIntersectionBecauseNoOverlap) {

  {
    // Test 1 - new region fully to right of existing pano segment
    PanoramaComposer pc(10, 10, CV_8UC4, 0.1f);
    pc.insert(getProjectedImage(0.0f, 0.0f, 10, 10, CV_8UC4, cv::Scalar(0), 0.1f)); // inserted at 0,0, extends to 1.0f,1.0f
    cv::Rect2f region(2.0f, 0.0f, 1.0f, 1.0f); // this region starts at 2.0, 0.0f so it can't overlap'
    ASSERT_TRUE(pc.getIntersectPixels(region) == nullptr);
  }

  {
    // Test 2 - new region fully to left of existing pano segment
    PanoramaComposer pc(10, 10, CV_8UC4, 0.1f);
    pc.insert(getProjectedImage(2.0f, 2.0f, 10, 10, CV_8UC4, cv::Scalar(0), 0.1f)); // this also exercises the growth ability of the pano
    cv::Rect2f region = cv::Rect2f(0.0f, 0.0f, 1.0f, 1.0f);
    ASSERT_TRUE(pc.getIntersectPixels(region) == nullptr);
  }
}

// edge case intersection
TEST(PanoramaComposer, edgeTouchingDoesNotIntersect) {
  { // pano is (x,y,w,h) 0,0,1,1 and check against 1,1,1,1
    PanoramaComposer pc(1, 1, CV_8UC1, 1.0f);
    pc.insert(getProjectedImage(0.0f, 0.0f, 1, 1, CV_8UC1));
    cv::Rect2f region(1.0f, 1.0f, 1.0f, 1.0f);
    ASSERT_TRUE(pc.getIntersectPixels(region) == nullptr);
  }

  { // pano is (x,y,w,h) 0,0,1,1 and check against -1,-1,1,1
    PanoramaComposer pc(1, 1, CV_8UC1, 1.0f);
    pc.insert(getProjectedImage(0.0f, 0.0f, 1, 1, CV_8UC1));
    cv::Rect2f region(-1.0f, -1.0f, 1.0f, 1.0f);
    ASSERT_TRUE(pc.getIntersectPixels(region) == nullptr);
  }

  { // pano is (x,y,w,h) 0,0,1,1 and check against -1,-1,1,1 (same meters, different resolution)
    PanoramaComposer pc(2, 2, CV_8UC1, .5f);
    pc.insert(getProjectedImage(0.0f, 0.0f, 2, 2, CV_8UC1, cv::Scalar(0), 0.5f));
    cv::Rect2f region(-1.0f, -1.0f, 1.0f, 1.0f);
    ASSERT_TRUE(pc.getIntersectPixels(region) == nullptr);
  }
}

TEST(PanoramaComposer, barelyTouchingDoesIntersect) {
  { // pano is (x,y,w,h) 0,0,1,1 and check against .9,.9,1,1
    PanoramaComposer pc(1, 1, CV_8UC1, 1.0f);
    pc.insert(getProjectedImage(0.0f, 0.0f, 1, 1, CV_8UC1));
    cv::Rect2f region(.9f, .9f, 1.0f, 1.0f);
    ASSERT_TRUE(pc.getIntersectPixels(region) != nullptr);
  }

  { // pano is (x,y,w,h) 0,0,1,1 and check against -1,-1,1.1,1.1
    PanoramaComposer pc(1, 1, CV_8UC1, 1.0f);
    pc.insert(getProjectedImage(0.0f, 0.0f, 1, 1, CV_8UC1));
    cv::Rect2f region(-1.0f, -1.0f, 1.1f, 1.1f);
    ASSERT_TRUE(pc.getIntersectPixels(region) != nullptr);
  }

  { // pano is (x,y,w,h) 0,0,1,1 and check against -1,-1,1.1,1.1 (same meters, different resolution)
    PanoramaComposer pc(2, 2, CV_8UC1, .5f);
    pc.insert(getProjectedImage(0.0f, 0.0f, 2, 2, CV_8UC1, cv::Scalar(0), 0.5f));
    cv::Rect2f region(-1.0f, -1.0f, 1.1f, 1.1f);
    ASSERT_TRUE(pc.getIntersectPixels(region) != nullptr);
  }
}

/* Insertion that grows the panorama */
TEST(PanoramaComposer, insertThatGrowsPano) {
  { // Grow to bottom right
    PanoramaComposer pc(3, 3, CV_8UC1, 1.0f);
    uchar insert_data [12] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    cv::Mat image(4, 3, CV_8UC1, insert_data);
    cv::Point2f position(1, 1);
    pc.insert(ProjectedImage(image.getUMat(cv::ACCESS_RW), position, 1.0f, cv::Scalar(0)));

    cv::Mat ref_mat = cv::Mat(5, 4, CV_8UC1, cv::Scalar(0));
    image.copyTo(ref_mat(cv::Rect(1, 1, 3, 4)));

    MatUtils::verifyMatsEQ<uint8_t>(pc.getFullPano().image().getMat(cv::ACCESS_READ),
        ref_mat);
    ASSERT_EQ(pc.getFullPano().position(), cv::Point2f(0.0f, 0.0f));
  }

  { // Grow to top left
    PanoramaComposer pc(cv::Rect2f(1, 1, 2, 3), CV_8UC2, 1.0f, cv::Scalar(1, 2));

    cv::UMat image(3, 2, CV_8UC2, cv::Scalar(3, 4));
    cv::Point2f position(0.0, -1.0);
    pc.insert(ProjectedImage(image, position, 1.0f, cv::Scalar(0)));
    ASSERT_EQ(pc.getFullPano().position(), cv::Point2f(0.0f, -1.0f));
    ASSERT_EQ(pc.getFullPano().image().size(), cv::Size(3, 5));
  }
}

/* Intersection Overlap Pixels */

TEST(PanoramaComposer, getIntersectingPixelsBasicCase) {
  {
    // Test 1 - round numbers
    PanoramaComposer pc(10, 10, CV_8UC1, 1.0f);
    pc.insert(getProjectedImage(0.0f, 0.0f, 4, 4, CV_8UC1, cv::Scalar(3), 1.0f));
    cv::Rect2f region = cv::Rect2f(3.0f, 1.0f, 2.0f, 2.0f);

    ProjectedImage pi = *(pc.getIntersectPixels(region));
    ASSERT_EQ(pi.image().cols, 1);
    ASSERT_EQ(pi.image().rows, 2);
  }

  {
    // Test 2 - Non-integer numbers that become ints when pixels are extracted
    PanoramaComposer pc(10, 10, CV_8UC1, 1.0f);
    pc.insert(getProjectedImage(0.0f, 0.0f, 4, 4, CV_8UC1, cv::Scalar(3), 1.0f));
    cv::Rect2f region = cv::Rect2f(2.0f, 1.0f, 3.0f, 2.0f);

    ProjectedImage pi = *(pc.getIntersectPixels(region));
    ASSERT_EQ(pi.image().cols, 2);
    ASSERT_EQ(pi.image().rows, 2);
  }
}

// // intersection w/1 internal pano segment
TEST(PanoramaComposer, validIntersection1) {
  PanoramaComposer pc(0, 0, CV_8UC4, .001f);
  // Insert 1 image into panorama
  cv::UMat image(2955, 318, CV_8UC4, cv::Scalar(10));
  cv::Point2f position(0.031f, -0.053f);
  pc.insert(ProjectedImage(image, position, .001f, cv::Scalar(0)));
  // Get intersecting pixels for next region that will be inserted
  cv::Rect2f buffered_image(0.0654f, -0.3467f, .3792f, 3.5364f);
  cv::UMat image_out;
  cv::Point2f position_out;
  ProjectedImage pi = *(pc.getIntersectPixels(buffered_image));
  image_out = pi.image();
  position_out = pi.position();

  // intersection rect should be (0.0654, -0.053, .2836, 2.955)
  ASSERT_EQ(position_out, cv::Point2f(0.0654f, -0.053f));
  ASSERT_EQ(image_out.cols, 284);
  ASSERT_EQ(image_out.rows, 2955);
  ASSERT_EQ(cv::sum(image_out)[0], 10*284*2955);
}

// intersection 2/1 internal pano segments that are disjoint.
// therefore the returned overlapping pixels will contain some default background as well
TEST(PanoramaComposer, disjoinIntersectionPixels) {
  PanoramaComposer pc(0, 0, CV_8UC4, 0.001f, cv::Scalar(1, 2, 3, 4));

  // Insert 1st image into panorama (0,0,.01,.02)
  int ORIG_IMAGE_PIX = 1;
  cv::UMat image1(20, 10, CV_8UC4);
  image1.setTo(cv::Scalar(ORIG_IMAGE_PIX));
  cv::Point2f position1(0.0f, 0.0f);
  pc.insert(ProjectedImage(image1, position1, .001f, cv::Scalar(0)));

  // Insert 2nd disjoint image into panorama (0.02, 0, .01, .025)
  int SECOND_IMAGE_PIX = 2;
  cv::UMat image2(35, 10, CV_8UC4);
  image2.setTo(cv::Scalar(SECOND_IMAGE_PIX));
  cv::Point2f position2(0.02f, 0.0f);
  pc.insert(ProjectedImage(image2, position2, .001f, cv::Scalar(0)));

  cv::Rect2f buffered_image(0.005f, 0.005f, 0.0301f, 0.0101f);
  ProjectedImage pi = *(pc.getIntersectPixels(buffered_image));

  cv::UMat imageOut = pi.image();
  cv::Point2f position_out = pi.position();
  // Test size of returned intersection
  ASSERT_EQ(position_out, cv::Point2f(0.005f, 0.005f));
  ASSERT_EQ(imageOut.cols, 25);
  ASSERT_EQ(imageOut.rows, 10);

  // Test pixel values in 3 regions of returned interesction
  cv::Mat imageOutMat = imageOut.getMat(cv::ACCESS_READ);
  ASSERT_EQ((int)imageOutMat.at<cv::Vec4b>(0, 0)[0], ORIG_IMAGE_PIX);
  ASSERT_EQ(imageOutMat.at<cv::Vec4b>(0, 7), cv::Vec4b(1, 2, 3, 4));
  ASSERT_EQ((int)imageOutMat.at<cv::Vec4b>(0, 16)[0], SECOND_IMAGE_PIX);
}

TEST(PanoramaComposer, getDefaultPano) {
  PanoramaComposer pc(0, 0, CV_8UC4);
  ProjectedImage pi = pc.getFullPano();

  cv::UMat image = pi.image();
  cv::Point2f pos = pi.position();
  ASSERT_FALSE(pi.image().empty());

  ASSERT_EQ(pos, cv::Point2f(0.0f, 0.0f));
  ASSERT_EQ(image.cols, 1);
  ASSERT_EQ(image.rows, 1);
}

// insert sequence of 3 regions (1st two overlapping) followed by get full pano
// [ A [ ] B ]  [ C]
TEST(PanoramaComposer, insertAndGetFullPano) {
  PanoramaComposer pc(0, 0, CV_8UC4);

  // Insert 1st image into panorama (0,0,.01,.02)
  int ORIG_IMAGE_PIX = 1;
  cv::UMat image1(20, 10, CV_8UC4);
  image1.setTo(cv::Scalar(ORIG_IMAGE_PIX, ORIG_IMAGE_PIX, ORIG_IMAGE_PIX, ORIG_IMAGE_PIX));
  cv::Point2f position1(0.0f, 0.0f);
  pc.insert(ProjectedImage(image1, position1, .001f, cv::Scalar(0)));

  // Insert 2nd overlapping image into panorama
  int TWO_IMAGE_PIX = 2;
  cv::UMat image2(10, 3, CV_8UC4);
  image2.setTo(cv::Scalar(TWO_IMAGE_PIX, TWO_IMAGE_PIX, TWO_IMAGE_PIX, TWO_IMAGE_PIX));
  cv::Point2f position2(0.009f, -0.005f);
  pc.insert(ProjectedImage(image2, position2, .001f, cv::Scalar(0)));

  // Insert 3nd disjoint image into panorama (0.02, 0, .01, .035)
  int THREE_IMAGE_PIX = 3;
  cv::UMat image3(35, 10, CV_8UC4);
  image3.setTo(cv::Scalar(THREE_IMAGE_PIX, THREE_IMAGE_PIX, THREE_IMAGE_PIX, THREE_IMAGE_PIX));
  cv::Point2f position3(0.02f, 0.0f);
  pc.insert(ProjectedImage(image3, position3, .001f, cv::Scalar(0)));

  ProjectedImage pi = pc.getFullPano();
  cv::UMat image = pi.image();
  cv::Point2f pos = pi.position();

  ASSERT_FALSE(pi.image().empty());
  ASSERT_EQ(pos, cv::Point2f(0.0f, -0.005f));
  ASSERT_EQ(image.cols, 30);
  ASSERT_EQ(image.rows, 40);

  cv::Mat imageOutMat = image.getMat(cv::ACCESS_READ);
  ASSERT_EQ((int)imageOutMat.at<cv::Vec4b>(0, 0)[0], 0);
  ASSERT_EQ((int)imageOutMat.at<cv::Vec4b>(6, 0)[0], ORIG_IMAGE_PIX);
  ASSERT_EQ((int)imageOutMat.at<cv::Vec4b>(0, 10)[0], TWO_IMAGE_PIX);
  ASSERT_EQ((int)imageOutMat.at<cv::Vec4b>(6, 25)[0], THREE_IMAGE_PIX);
}
