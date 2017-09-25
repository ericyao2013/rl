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

#ifndef RL_HAL_COACH_H
#define RL_HAL_COACH_H

#include <array>
#include <sstream>
#include <string>

#include "CyclicDevice.h"
#include "JointPositionActuator.h"
#include "JointPositionSensor.h"
#include "JointTorqueActuator.h"
#include "JointVelocityActuator.h"
#include "Socket.h"

namespace rl
{
	namespace hal
	{
		class Coach : public CyclicDevice, public JointPositionActuator, public JointPositionSensor, public JointTorqueActuator, public JointVelocityActuator
		{
		public:
			Coach(
				const ::std::size_t& dof,
				const ::std::chrono::nanoseconds& updateRate,
				const ::std::size_t& i = 0,
				const ::std::string& hostname = "localhost",
				const unsigned short int& port = 11235
			);
			
			virtual ~Coach();
			
			void close();
			
			::rl::math::Vector getJointPosition() const;
			
			void open();
			
			void setJointPosition(const ::rl::math::Vector& q);
			
			void setJointTorque(const ::rl::math::Vector& tau);
			
			void setJointVelocity(const ::rl::math::Vector& qd);
			
			void start();
			
			void step();
			
			void stop();
			
		protected:
			
		private:
			::std::size_t i;
			
			::std::array<char, 1024> in;
			
			::std::stringstream out;
			
			Socket socket;
		};
	}
}

#endif // RL_HAL_COACH_H
