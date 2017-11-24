#include "Feature.h"

Feature::Feature()
{
  this->image = cv::Mat();
  this->keypoints = std::vector< cv::KeyPoint >();
}

Feature::Feature( std::string image_name )
{
  cv::Mat image, aux, image_gray;
  image = cv::imread(image_name, 1);
  if(!image.data)
  {
    std::cout << "Image Error." << std::endl;
    std::cout << image_name << " can't be loaded." << std::endl;
  }
  else
  {
  double fx, fy;
  fx = 512.0/image.cols;
  fy = 512.0/image.rows;
  aux = cv::Mat(512, 512, image.type());
  cv::resize(image, aux, cv::Size(), fx, fy);
  this->image = aux.clone();

  cv::cvtColor(aux, image_gray, cv::COLOR_RGB2GRAY);
  cv::imwrite("binary.png", image_gray);
  cv::medianBlur(image_gray, image_gray, 3);
  cv::imwrite( "median.jpg", image_gray);
  cv::Ptr<cv::FastFeatureDetector> fast = cv::FastFeatureDetector::create(25);
  fast->detect(image_gray, this->keypoints);
  }
}

cv::Mat Feature::getImage()
{
  return (this->image).clone();
}

std::vector< cv::KeyPoint > Feature::getKeyPoints()
{
  return this->keypoints;
}

void Feature::saveImage( std::string name )
{
  cv::imwrite(name + ".png", this->image);
}

void Feature::saveImageFeature( std::string name )
{
  cv::Mat aux = (this->image).clone();
  cv::drawKeypoints(aux,// original image
                 keypoints,// vector of keypoints
                 aux,// the output image
                 cv::Scalar( 0, 0, 0 ), // keypoint color
                 cv::DrawMatchesFlags::DRAW_OVER_OUTIMG); //drawing flag
  cv::imwrite(name + ".png", aux);
}

std::vector<float> Feature::equal( Feature input )
{
  cv::Mat image_1( (this->image).rows + 4, (this->image).cols + 4, (this->image).type() );
  cv::Mat image_2( (input.getImage()).rows, (input.getImage()).cols, (input.getImage()).type() );

  cv::copyMakeBorder(this->image, image_1, 2, 2, 2, 2, cv::BORDER_CONSTANT, cv::Scalar(0, 0, 0));
  cv::copyMakeBorder(input.getImage(), image_2, 2, 2, 2, 2, cv::BORDER_CONSTANT, cv::Scalar(0, 0, 0));

  std::vector<float> result;
  double N;
  int n, sum = 0;
  if((this->keypoints).size() < input.getKeyPoints().size())
    N = (this->keypoints).size();
  else
    N = input.getKeyPoints().size();
  double o = 0.5;
  double Z = 1.96;
  double e = 0.05;
  n = (N * std::pow(o, 2) * std::pow(Z, 2))/((N - 1) * e + std::pow(o, 2) * std::pow(Z, 2));

  cv::Mat corr;
  std::random_device seeder;
  std::ranlux48 gen(seeder());
  std::normal_distribution<double> distribution (0.0,1.0);
  for(int i = 0; i < n; i++)
  {
    cv::Mat aux_1(9, 9, image_1.type());
    int pos_1 = ((418.0 - 1) / 4.0) * std::abs(distribution(gen));
    cv::Point point_1 = (this->keypoints)[pos_1].pt;
    cv::getRectSubPix(image_1, cv::Size(9, 9), point_1, aux_1);

    for(int j = 0; j < n; j++)
    {
      cv::Mat aux_2(9, 9, image_2.type());
      int pos_2 = ((418.0 - 1) / 4.0) * std::abs(distribution(gen));
      cv::Point point_2 = (input.getKeyPoints())[pos_2].pt;
      cv::getRectSubPix(image_2, cv::Size(9, 9), point_2, aux_2);
      cv::matchTemplate(aux_1, aux_2, corr, cv::TM_CCORR_NORMED);
      if(corr.at<float>(0,0) >= 0.85)
        sum++;
    }
  }
  std::cout << static_cast<float>(sum)/static_cast<float>(n * n);

  cv::matchTemplate(this->image, input.getImage(), corr, cv::TM_CCORR_NORMED);
  std::cout << " corr " << corr.at<float>(0,0) << std::endl;
  result.push_back(static_cast<float>(sum)/static_cast<float>(n * n));
  result.push_back(corr.at<float>(0,0));

  return result;
}
