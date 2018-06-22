#pragma once
#include <string>

#include "Eigen"
#include "csv_io.h"

using namespace Eigen;

typedef Matrix<float, -1, 6> MatrixX6f;
typedef Matrix<float, 5, 1> VectorC5f;


int run_prediction(int argc, char *argv[]);


class classifier
{
public:
	classifier();
	~classifier() { ; }

	VectorXi predict(const MatrixX6f& data);
private:

	VectorXf predict_gaussian_proba(const VectorXf &vector, const int gaussian_id) const;
	VectorXf predict_regression(const MatrixXf &data) const;

	std::vector<float> m_cov0;
	std::vector<float> m_cov1;
	std::vector<float> m_coeff1;
	std::vector<float> m_coeff0;
	std::vector<float> m_mu0;
	std::vector<float> m_mu1;
	VectorC5f m_beta;
};