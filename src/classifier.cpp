#define _USE_MATH_DEFINES

#include <cmath>

#include "classifier.h"

int run_prediction(int argc, char *argv[])
{
	auto mat = csv::load_csv<MatrixX6f>(std::string(argv[1]), true);
	classifier c;

	VectorXi indices = mat.col(0).cast<int>();
	auto predicton = c.predict(mat);

	MatrixXi result(predicton.rows(), 2);
	result << indices, predicton;

	csv::store_csv<MatrixXi>(result, "submission.csv", {"\"ID\"","\"y\""});

	return 0;
}

classifier::classifier()
{
	this->m_cov1 = { 8.92052669f, 402.03800454f, 260.23711347f, 3.97946869f, 1.01071085f};
	this->m_cov0 = { 1.00230119f, 400.05202843f, 255.68929361f, 1.00105835f, 0.9988931f };
	this->m_mu1 = { 2.00978071f, 40.10601485f, -100.06020472f, 9.99965239f, 1.25152167f };
	this->m_mu0 = { -2.00544103f, -0.04849786f, -100.01739565f, 9.99921426f, -1.24015505f };
	this->m_beta << 2.19531247e-01, 1.01552551e-01, 1.28123349e-03,
		-5.34413595e-02, 2.70102081e+00, 5.77751988e+00,
		-3.02542080e-01, -2.18971780e+00, 5.08762749e+00,
		-7.60776108e-01;
	this->m_intercept = -4.40639467;


	this->m_coeff1 = std::vector<float>(5);
	this->m_coeff0 = std::vector<float>(5);
	for (int i = 0; i < 5; ++i)
	{
		this->m_coeff1[i] = 1.0f / (std::sqrt(2.0f*M_PI*this->m_cov1[i]));
		this->m_coeff0[i] = 1.0f / (std::sqrt(2.0f*M_PI*this->m_cov0[i]));
	}
}


VectorXi classifier::predict(const MatrixX6f &m)
{
	MatrixXf data = MatrixXf(m.rows(), 10);
	data.leftCols<5>() = m.rightCols<5>();

	for (int i = 0; i < 5; ++i)
		data.col(i+5) = this->predict_gaussian_proba(data.col(i),i);

	VectorXf probas = this->predict_regression(data);

	return 2 * (probas.array() > 0.5f).cast<int>() - 1;
}


VectorXf classifier::predict_gaussian_proba(const VectorXf &vector, const int gaussian_id) const
{
	auto diff0 = vector.array() - this->m_mu0[gaussian_id];
	auto diff1 = vector.array() - this->m_mu1[gaussian_id];
	auto gaussian0 = (diff0 * diff0 *(-0.5) / this->m_cov0[gaussian_id]).exp()*this->m_coeff0[gaussian_id];
	auto gaussian1 = (diff1 * diff1 *(-0.5) / this->m_cov1[gaussian_id]).exp()*this->m_coeff1[gaussian_id];

	return gaussian1 / (gaussian0 + gaussian1);
}

VectorXf classifier::predict_regression(const MatrixXf &data) const
{
	assert(data.cols() == 10);
	auto dot = data*this->m_beta;
	return 1.0f / (1.0f + (-dot.array() - this->m_intercept).exp());
}
