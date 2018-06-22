#pragma once
#include "Eigen"
#include "csv_io.h"

using namespace Eigen;

int run_prediction(int argc, char *argv[])
{
	return 0;
}



class predictor
{
public:
	predictor();
	~predictor();
private:
	MatrixXf m_Sigma;
	VectorXf m_mu;
	VectorXf m_beta;
};