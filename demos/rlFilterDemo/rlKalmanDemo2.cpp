//
// Copyright (c) 2009, Markus Rickert
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice,
//   this list of conditions and the following disclaimer.
// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//

#include <fstream>
#include <iostream>
#include <rl/math/Kalman.h>
#include <rl/math/Matrix.h>
#include <rl/math/Vector.h>

int
main(int argc, char** argv)
{
	if (argc < 3)
	{
		std::cout << "Usage: rlKalmanDemo2 DATA FILTERED" << std::endl;
		return EXIT_FAILURE;
	}
	
	// plot for [i=2:4] "DATA" using 1:i with lines, for [i=2:4] "FILTERED" using 1:i with lines
	
	std::ifstream data;
	data.open(argv[1]);
	
	std::ofstream filtered;
	filtered.open(argv[2], std::fstream::trunc);
	
	std::size_t ss = 3;
	std::size_t os = 3;
	
	rl::math::Kalman<rl::math::Real> kalman(ss, os);
	
	kalman.stateTransitionModel().setIdentity();
	
	kalman.measurementModel().setIdentity();
	kalman.processNoiseCovariance() = 0.001 * rl::math::Matrix::Identity(ss, ss);
	kalman.measurementNoiseCovariance() = 5 * rl::math::Matrix::Identity(ss, ss);
	
	kalman.statePosteriori().setZero();
	kalman.errorCovariancePosteriori() = 1 * rl::math::Matrix::Identity(ss, ss);
	
	for (std::string line; std::getline(data, line);)
	{
		std::istringstream stream(line);
		
		rl::math::Real time = 0;
		stream >> time;
		
		rl::math::Vector prediction = kalman.predict();
		
		rl::math::Vector measurement(os);
		
		for (std::size_t i = 0; i < os; ++i)
		{
			stream >> measurement(i);
		}
		
		rl::math::Vector estimation = kalman.correct(measurement);
		
		filtered << time;
		
		for (std::size_t i = 0; i < ss; ++i)
		{
			filtered << "\t" << estimation(i);
		}
		
		filtered << std::endl;
	}
	
	data.close();
	filtered.close();
	
	return EXIT_SUCCESS;
}
