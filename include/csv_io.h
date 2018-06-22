#pragma once
#include <Eigen>
#include <vector>
#include <fstream>


namespace csv
{
	using namespace Eigen;
	// from stackoverflow.com/questions/34247057/how-to-read-csv-file-and-assign-to-eigen-matrix
	template<typename M>
	M load_csv(const std::string & path, bool header = false)
	{
		std::ifstream indata;
		indata.open(path);
		std::string line;
		std::vector<typename M::Scalar> values;
		int rows = 0;

		if (header)
			std::getline(indata, line);

		while (std::getline(indata, line)) {
			std::stringstream lineStream(line);
			std::string cell;
			while (std::getline(lineStream, cell, ',')) {
				values.push_back(std::stof(cell));
			}
			++rows;
		}
		if (rows == 0)
			throw std::string("nonexisting or empty file");
		int cols = values.size() / rows;

		if (cols != M::ColsAtCompileTime && M::ColsAtCompileTime != -1)
			throw std::string("wrong number of columns");

		return Map<const Matrix<typename M::Scalar, M::RowsAtCompileTime, M::ColsAtCompileTime, RowMajor>>(values.data(), rows, cols);
	}

	template<typename M>
	void store_csv(const M &m, std::string path, std::vector<std::string> headers)
	{
		const static IOFormat CSVFormat(StreamPrecision, DontAlignCols, ", ", "\n");
		std::ofstream file(path);

		for (auto header : headers)
			file << header << " ";
		if (headers.size() != 0)
			file << "\n";

		file << m.format(CSVFormat);
	}
}
