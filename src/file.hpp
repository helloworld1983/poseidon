/*******************************************************************************
 * Copyright 2012 Mark Ruvald Pedersen <mark@radix63.dk>
 * Copyright 2012 Rasmus Bo Soerensen <rasmus@rbscloud.dk>
 * Copyright 2012 Jaspur Hoejgaard <jaspurh@gmail.com>
 * Copyright 2013 Technical University of Denmark, DTU Compute.
 * 
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted (subject to the limitations in the
 * disclaimer below) provided that the following conditions are met:
 * 
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 
 * NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE
 * GRANTED BY THIS LICENSE.  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT
 * HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 * The views and conclusions contained in the software and documentation
 * are those of the authors and should not be interpreted as representing
 * official policies, either expressed or implied, of the copyright holder.
 ******************************************************************************/
 
#ifndef FILE_HPP
#define	FILE_HPP

#include <stdexcept>
#include <string>
#include <iostream>
#include <fstream>
#include <cassert>
#include <cstdlib>


namespace snts {

class file {
public:
	file(const std::string& file_path, std::ios_base::openmode mode);
	~file();

	std::string getline();

	template <typename T>
	file& operator >>(T& dest) {
		this->check_for_input();
		this->file_stream >> dest;
		return *this;
	}

	template <typename T>
	file& operator <<(const T& src) {
		this->file_stream << src;
		return *this;
	}

	template <typename Function>
	Function for_each_line(Function f) {
		this->check_for_input();
		while (this->file_stream.good()) {
			f(this->getline());
		}
	}

private:
	void check_for_input() const;
	std::string file_path;
	std::fstream file_stream;
};


struct file_read_error : public std::runtime_error {
	file_read_error(const std::string& msg);
};

}

#endif	/* FILE_HPP */

