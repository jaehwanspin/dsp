#include <cstddef>
#include <chrono>
#include <cstdlib>
#include <vector>
#include <list>
#include <fstream>
#include <filesystem>
#include <random>
#include <iostream>
#include <execution>
#include <atomic>
#include <memory>
#include <chrono>
#include <iomanip>
#include <atomic>
#include <complex>

#include <dsp/dsp.hpp>

int main(int argc, char** argv)
{
	(void)argc;
	(void)argv;

	auto hey = dsp::kilohertz(13);

	constexpr auto input_filename = "sample_16t.iq";
	
	int result = EXIT_SUCCESS;

	std::vector<std::int16_t> input_buffer;
	std::vector<std::complex<std::float_t>> input_cplx_buffer(128);
	std::vector<std::size_t> indices(16);

	// dsp::internal::create_parallel_indices(indices.begin(), indices.end());

	auto beg = indices.begin();
	for (auto i = 0 ; i < indices.size(); i++)
	{
		std::cout << beg.operator[](i) << std::endl;
	}


	{
		std::random_device rnd_dev;
		std::mt19937 rnd_engine(rnd_dev());
		std::uniform_real_distribution<std::float_t> dist(-128.0, 128.0);
		std::generate(input_cplx_buffer.begin(), input_cplx_buffer.end(), [&dist, &rnd_engine]() { return dist(rnd_engine); });
	}

	// ppi::dsp::internal::fast_fourier_transformer_impl<
	// 	false,
	// 	std::vector<std::complex<std::float_t>>::iterator,
	// 	std::vector<std::complex<std::float_t>>::iterator
	// >::transform(input_cplx_buffer.begin(), input_cplx_buffer.end(), input_cplx_buffer.begin());

	if (!std::filesystem::exists(input_filename))
	{
		std::cerr << "input file not found (" << input_filename << ")\n";
		result = EXIT_FAILURE;
	}
	else
	{
		// read
		{
			const auto pcm_samples_size = std::filesystem::file_size(input_filename);
			input_buffer.resize(pcm_samples_size / sizeof(decltype(input_buffer)::value_type));
			input_cplx_buffer.resize(pcm_samples_size / sizeof(decltype(input_cplx_buffer)::value_type) / 2);

			std::ifstream input_stream(input_filename, std::ios::binary);

			for (auto& single_buffer : input_buffer)
			{
				input_stream.read(reinterpret_cast<char*>(&single_buffer), sizeof(decltype(input_buffer)::value_type));
			}

			input_stream.seekg(0, input_stream.beg);

			for (auto& single_buffer : input_cplx_buffer)
			{
				auto tmp = std::make_tuple<std::float_t, std::float_t>(0, 0);
				input_stream.read(reinterpret_cast<char*>(&tmp),
					sizeof(decltype(tmp)) * 2);
				single_buffer.real(std::get<0>(tmp));
				single_buffer.imag(std::get<1>(tmp));
			}
		}

		// 8t
		{
			constexpr auto output_filename = "sample_8t.iq";
			std::vector<std::int8_t> output_buffer(input_buffer.size());

			//dsp::convert_type(std::execution::par_unseq, input_buffer.begin(), input_buffer.end(), output_buffer.begin());
			dsp::convert_type(std::execution::par_unseq, input_buffer.begin(), input_buffer.end(), output_buffer.begin(),
				[](const double progress) {
					std::cout << std::setprecision(4) << progress << std::endl;
				});
			
			std::ofstream output_stream(output_filename, std::ios::binary);

			output_stream.write(reinterpret_cast<char*>(output_buffer.data()),
				output_buffer.size() * sizeof(decltype(output_buffer)::value_type));
		}

		// 8tr
		{
			constexpr auto output_filename = "sample_8tr.iq";
			std::vector<std::int8_t> output_buffer(input_buffer.size());

			dsp::convert_type<true>(std::execution::par_unseq, input_buffer.begin(), input_buffer.end(), output_buffer.begin());

			std::ofstream output_stream(output_filename, std::ios::binary);

			output_stream.write(reinterpret_cast<char*>(output_buffer.data()),
				output_buffer.size() * sizeof(decltype(output_buffer)::value_type));
		}

		// 16tr
		{
			constexpr auto output_filename = "sample_16tr.iq";
			std::vector<std::int16_t> output_buffer(input_buffer.size());

			dsp::convert_type<true>(std::execution::par_unseq, input_buffer.begin(), input_buffer.end(), output_buffer.begin());

			std::ofstream output_stream(output_filename, std::ios::binary);

			output_stream.write(reinterpret_cast<char*>(output_buffer.data()),
				output_buffer.size() * sizeof(decltype(output_buffer)::value_type));
		}

		// 24t
		{
			constexpr auto output_filename = "sample_24t.iq";
			std::vector<dsp::int24_t> output_buffer(input_buffer.size());

			dsp::convert_type(std::execution::par_unseq, input_buffer.begin(), input_buffer.end(), output_buffer.begin());

			std::ofstream output_stream(output_filename, std::ios::binary);

			output_stream.write(reinterpret_cast<char*>(output_buffer.data()),
				output_buffer.size() * sizeof(decltype(output_buffer)::value_type));
		}

		// 24tr
		{
			constexpr auto output_filename = "sample_24tr.iq";
			std::vector<dsp::int24_t> output_buffer(input_buffer.size());

			dsp::convert_type<true>(std::execution::par_unseq, input_buffer.begin(), input_buffer.end(), output_buffer.begin());

			std::ofstream output_stream(output_filename, std::ios::binary);

			output_stream.write(reinterpret_cast<char*>(output_buffer.data()),
				output_buffer.size() * sizeof(decltype(output_buffer)::value_type));
		}

		// 32t
		{
			constexpr auto output_filename = "sample_32t.iq";
			std::vector<std::int32_t> output_buffer(input_buffer.size());

			dsp::convert_type(std::execution::par_unseq, input_buffer.begin(), input_buffer.end(), output_buffer.begin());

			std::ofstream output_stream(output_filename, std::ios::binary);

			output_stream.write(reinterpret_cast<char*>(output_buffer.data()),
				output_buffer.size() * sizeof(decltype(output_buffer)::value_type));
		}

		// 32tr
		{
			constexpr auto output_filename = "sample_32tr.iq";
			std::vector<std::int32_t> output_buffer(input_buffer.size());

			dsp::convert_type<true>(std::execution::par_unseq, input_buffer.begin(), input_buffer.end(), output_buffer.begin());

			std::ofstream output_stream(output_filename, std::ios::binary);

			output_stream.write(reinterpret_cast<char*>(output_buffer.data()),
				output_buffer.size() * sizeof(decltype(output_buffer)::value_type));
		}

		// 32f
		{
			constexpr auto output_filename = "sample_32f.iq";
			std::vector<std::float_t> output_buffer(input_buffer.size());

			dsp::convert_type(std::execution::par_unseq, input_buffer.begin(), input_buffer.end(), output_buffer.begin());

			std::ofstream output_stream(output_filename, std::ios::binary);

			output_stream.write(reinterpret_cast<char*>(output_buffer.data()),
				output_buffer.size() * sizeof(decltype(output_buffer)::value_type));
		}

		// 64f
		{
			constexpr auto output_filename = "sample_64f.iq";
			std::vector<std::double_t> output_buffer(input_buffer.size());

			dsp::convert_type(std::execution::par_unseq, input_buffer.begin(), input_buffer.end(), output_buffer.begin());

			std::ofstream output_stream(output_filename, std::ios::binary);

			output_stream.write(reinterpret_cast<char*>(output_buffer.data()),
				output_buffer.size() * sizeof(decltype(output_buffer)::value_type));
		}

		std::cout << "done" << std::endl;
	}

	return result;
}
