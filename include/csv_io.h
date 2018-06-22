#pragma once
#include <Eigen>
#include <vector>
#include <fstream>


namespace csv
{
	using namespace Eigen;
	// from stackoverflow.com/questions/34247057/how-to-read-csv-file-and-assign-to-eigen-matrix
	template<typename M>
	M load_csv(const std::string & path)
	{
		std::ifstream indata;
		indata.open(path);
		std::string line;
		std::vector<typename M::Scalar> values;
		int rows = 0;
		while (std::getline(indata, line)) {
			std::stringstream lineStream(line);
			std::string cell;
			while (std::getline(lineStream, cell, ',')) {
				values.push_back(std::stod(cell));
			}
			++rows;
		}
		return Map<const Matrix<typename M::Scalar, M::RowsAtCompileTime, M::ColsAtCompileTime, RowMajor>>(values.data(), rows, values.size() / rows);
	}

	template<typename M>
	void store_csv(const M &m, const char *path)
	{
		const static IOFormat CSVFormat(StreamPrecision, DontAlignCols, ", ", "\n");
		std::ofstream file(path);
		file << m.format(CSVFormat);
	}
}
