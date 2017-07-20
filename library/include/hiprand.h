// Copyright (c) 2017 Advanced Micro Devices, Inc. All rights reserved.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#ifndef HIPRAND_H_
#define HIPRAND_H_

#include <hip/hip_runtime.h>

#ifndef HIPRANDAPI
#define HIPRANDAPI
#endif

/// hipRAND random number generator (opaque)
typedef hiprandGenerator_st * hiprandGenerator_t;

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/**
 * hipRAND function call status types
 */
typedef enum hiprandStatus {
    HIPRAND_STATUS_SUCCESS = 0, ///< Success
    HIPRAND_STATUS_VERSION_MISMATCH = 100, ///< Header file and linked library version do not match
    HIPRAND_STATUS_NOT_INITIALIZED = 101, ///< Generator not initialized
    HIPRAND_STATUS_ALLOCATION_FAILED = 102, ///< Memory allocation failed
    HIPRAND_STATUS_TYPE_ERROR = 103, ///< Generator is wrong type
    HIPRAND_STATUS_OUT_OF_RANGE = 104, ///< Argument out of range
    HIPRAND_STATUS_LENGTH_NOT_MULTIPLE = 105, ///< Length requested is not a multple of dimension
    HIPRAND_STATUS_DOUBLE_PRECISION_REQUIRED = 106, ///< GPU does not have double precision
    HIPRAND_STATUS_LAUNCH_FAILURE = 201, ///< Kernel launch failure
    HIPRAND_STATUS_PREEXISTING_FAILURE = 202, ///< Preexisting failure on library entry
    HIPRAND_STATUS_INITIALIZATION_FAILED = 203, ///< Initialization of HIP failed
    HIPRAND_STATUS_ARCH_MISMATCH = 204, ///< Architecture mismatch, GPU does not support requested feature
    HIPRAND_STATUS_INTERNAL_ERROR = 999, ///< Internal library error
    HIPRAND_STATUS_NOT_IMPLEMENTED = 1000
} hiprandStatus_t;

/**
 * hipRAND generator types
 */
typedef enum hiprandRngType {
    HIPRAND_RNG_TEST = 0,
    HIPRAND_RNG_PSEUDO_DEFAULT = 400,
    HIPRAND_RNG_PSEUDO_XORWOW = 401, ///< XORWOW pseudorandom generator
    HIPRAND_RNG_PSEUDO_MRG32K3A = 402, ///< MRG32k3a pseudorandom generator
    HIPRAND_RNG_PSEUDO_MTGP32 = 403, ///< Mersenne Twister MTGP32 pseudorandom generator
    HIPRAND_RNG_PSEUDO_MT19937 = 404, ///< Mersenne Twister 19937
    HIPRAND_RNG_PSEUDO_PHILOX4_32_10 = 405, ///< PHILOX_4x32 (10 rounds) pseudorandom generator
    HIPRAND_RNG_QUASI_DEFAULT = 500, ///< Default quasirandom generator
    HIPRAND_RNG_QUASI_SOBOL32 = 501, ///< Sobol32 quasirandom generator
    HIPRAND_RNG_QUASI_SCRAMBLED_SOBOL32 = 502,  ///< Scrambled Sobol32 quasirandom generator
    HIPRAND_RNG_QUASI_SOBOL64 = 503, ///< Sobol64 quasirandom generator
    HIPRAND_RNG_QUASI_SCRAMBLED_SOBOL64 = 504  ///< Scrambled Sobol64 quasirandom generator
} hiprandRngType_t;


// Host API functions

/**
 * \brief Creates a new random number generator.
 *
 * Creates a new random number generator of type \p rng_type,
 * and returns it in \p generator. That generator will use
 * GPU to create random numbers.
 *
 * Values for \p rng_type are:
 * - HIPRAND_RNG_PSEUDO_DEFAULT
 * - HIPRAND_RNG_PSEUDO_XORWOW
 * - HIPRAND_RNG_PSEUDO_MRG32K3A
 * - HIPRAND_RNG_PSEUDO_MTGP32
 * - HIPRAND_RNG_PSEUDO_MT19937
 * - HIPRAND_RNG_PSEUDO_PHILOX4_32_10
 * - HIPRAND_RNG_QUASI_DEFAULT
 * - HIPRAND_RNG_QUASI_SOBOL32
 * - HIPRAND_RNG_QUASI_SCRAMBLED_SOBOL32
 * - HIPRAND_RNG_QUASI_SOBOL64
 * - HIPRAND_RNG_QUASI_SCRAMBLED_SOBOL64
 *
 * \param generator - Pointer to generator
 * \param rng_type - Type of random number generator to create
 *
 * \return
 * - HIPRAND_STATUS_ALLOCATION_FAILED, if memory allocation failed \n
 * - HIPRAND_STATUS_INITIALIZATION_FAILED if there was a problem setting up the GPU \n
 * - HIPRAND_STATUS_VERSION_MISMATCH if the header file version does not match the
 *   dynamically linked library version \n
 * - HIPRAND_STATUS_TYPE_ERROR if the value for \p rng_type is invalid \n
 * - HIPRAND_STATUS_NOT_IMPLEMENTED if generator of type \p rng_type is not implemented yet
 * - HIPRAND_STATUS_SUCCESS if generator was created successfully \n
 *
 */
hiprandStatus_t HIPRANDAPI
hiprandCreateGenerator(hiprandGenerator_t * generator, hiprandRngType_t rng_type);

/**
 * \brief Creates a new random number generator on host.
 *
 * Creates a new host random number generator of type \p rng_type
 * and returns it in \p generator. Created generator will use
 * host CPU to generate random numbers.
 *
 * Values for \p rng_type are:
 * - HIPRAND_RNG_PSEUDO_DEFAULT
 * - HIPRAND_RNG_PSEUDO_XORWOW
 * - HIPRAND_RNG_PSEUDO_MRG32K3A
 * - HIPRAND_RNG_PSEUDO_MTGP32
 * - HIPRAND_RNG_PSEUDO_MT19937
 * - HIPRAND_RNG_PSEUDO_PHILOX4_32_10
 * - HIPRAND_RNG_QUASI_DEFAULT
 * - HIPRAND_RNG_QUASI_SOBOL32
 * - HIPRAND_RNG_QUASI_SCRAMBLED_SOBOL32
 * - HIPRAND_RNG_QUASI_SOBOL64
 * - HIPRAND_RNG_QUASI_SCRAMBLED_SOBOL64
 *
 * \param generator - Pointer to generator
 * \param rng_type - Type of random number generator to create
 *
 * \return
 * - HIPRAND_STATUS_ALLOCATION_FAILED, if memory allocation failed \n
 * - HIPRAND_STATUS_VERSION_MISMATCH if the header file version does not match the
 *   dynamically linked library version \n
 * - HIPRAND_STATUS_TYPE_ERROR if the value for \p rng_type is invalid \n
 * - HIPRAND_STATUS_NOT_IMPLEMENTED if host generator of type \p rng_type is not implemented yet
 * - HIPRAND_STATUS_SUCCESS if generator was created successfully \n
 */
hiprandStatus_t HIPRANDAPI
hiprandCreateGeneratorHost(hiprandGenerator_t * generator, hiprandRngType_t rng_type);

/**
 * \brief Destroys random number generator.
 *
 * Destroys random number generator and frees related memory.
 *
 * \param generator - Generator to be destroyed
 *
 * \return
 * - HIPRAND_STATUS_NOT_INITIALIZED if the generator was not initialized \n
 * - HIPRAND_STATUS_SUCCESS if generator was destroyed successfully \n
 */
hiprandStatus_t HIPRANDAPI
hiprandDestroyGenerator(hiprandGenerator_t generator);

/**
 * \brief Generates uniformly distributed 32-bit unsigned integers.
 *
 * Generates \p n uniformly distributed 32-bit unsigned integers and
 * saves them to \p output_data.
 *
 * Generated numbers are between \p 0 and \p 2^32, including \p 0 and
 * excluding \p 2^32.
 *
 * \param generator - Generator to use
 * \param output_data - Pointer to memory to store generated numbers
 * \param n - Number of 32-bit unsigned integers to generate
 *
 * \return
 * - HIPRAND_STATUS_NOT_INITIALIZED if the generator was not initialized \n
 * - HIPRAND_STATUS_LAUNCH_FAILURE if generator failed to launch kernel \n
 * - HIPRAND_STATUS_SUCCESS if random numbers were successfully generated \n
 */
hiprandStatus_t HIPRANDAPI
hiprandGenerate(hiprandGenerator_t generator,
                unsigned int * output_data, size_t n);

/**
 * \brief Generates uniformly distributed floats.
 *
 * Generates \p n uniformly distributed 32-bit floating-point values
 * and saves them to \p output_data.
 *
 * Generated numbers are between \p 0.0f and \p 1.0f, excluding \p 0.0f and
 * including \p 1.0f.
 *
 * \param generator - Generator to use
 * \param output_data - Pointer to memory to store generated numbers
 * \param n - Number of floats to generate
 *
 * \return
 * - HIPRAND_STATUS_NOT_INITIALIZED if the generator was not initialized \n
 * - HIPRAND_STATUS_LAUNCH_FAILURE if generator failed to launch kernel \n
 * - HIPRAND_STATUS_SUCCESS if random numbers were successfully generated \n
 */
hiprandStatus_t HIPRANDAPI
hiprandGenerateUniform(hiprandGenerator_t generator,
                       float * output_data, size_t n);

/**
 * \brief Generates uniformly distributed double-precision floating-point values.
 *
 * Generates \p n uniformly distributed 64-bit double-precision floating-point
 * values and saves them to \p output_data.
 *
 * Generated numbers are between \p 0.0 and \p 1.0, excluding \p 0.0 and
 * including \p 1.0.
 *
 * \param generator - Generator to use
 * \param output_data - Pointer to memory to store generated numbers
 * \param n - Number of floats to generate
 *
 * \return
 * - HIPRAND_STATUS_NOT_INITIALIZED if the generator was not initialized \n
 * - HIPRAND_STATUS_LAUNCH_FAILURE if generator failed to launch kernel \n
 * - HIPRAND_STATUS_SUCCESS if random numbers were successfully generated \n
 */
hiprandStatus_t HIPRANDAPI
hiprandGenerateUniformDouble(hiprandGenerator_t generator,
                             double * output_data, size_t n);

/**
 * \brief Generates normally distributed floats.
 *
 * Generates \p n normally distributed 32-bit floating-point
 * values and saves them to \p output_data.
 *
 * \param generator - Generator to use
 * \param output_data - Pointer to memory to store generated numbers
 * \param n - Number of floats to generate
 * \param mean - Mean value of normal distribution
 * \param stddev - Standard deviation value of normal distribution
 *
 * \return
 * - HIPRAND_STATUS_NOT_INITIALIZED if the generator was not initialized \n
 * - HIPRAND_STATUS_LAUNCH_FAILURE if generator failed to launch kernel \n
 * - HIPRAND_STATUS_SUCCESS if random numbers were successfully generated \n
 */
hiprandStatus_t HIPRANDAPI
hiprandGenerateNormal(hiprandGenerator_t generator,
                      float * output_data, size_t n,
                      float mean, float stddev);

/**
 * \brief Generates normally distributed doubles.
 *
 * Generates \p n normally distributed 64-bit double-precision floating-point
 * numbers and saves them to \p output_data.
 *
 * \param generator - Generator to use
 * \param output_data - Pointer to memory to store generated numbers
 * \param n - Number of doubles to generate
 * \param mean - Mean value of normal distribution
 * \param stddev - Standard deviation value of normal distribution
 *
 * \return
 * - HIPRAND_STATUS_NOT_INITIALIZED if the generator was not initialized \n
 * - HIPRAND_STATUS_LAUNCH_FAILURE if generator failed to launch kernel \n
 * - HIPRAND_STATUS_SUCCESS if random numbers were successfully generated \n
 */
hiprandStatus_t HIPRANDAPI
hiprandGenerateNormalDouble(hiprandGenerator_t generator,
                            double * output_data, size_t n,
                            double mean, double stddev);

/**
 * \brief Generates log-normally distributed floats.
 *
 * Generates \p n log-normally distributed 32-bit floating-point values
 * and saves them to \p output_data.
 *
 * \param generator - Generator to use
 * \param output_data - Pointer to memory to store generated numbers
 * \param n - Number of floats to generate
 * \param mean - Mean value of log normal distribution
 * \param stddev - Standard deviation value of log normal distribution
 *
 * \return
 * - HIPRAND_STATUS_NOT_INITIALIZED if the generator was not initialized \n
 * - HIPRAND_STATUS_LAUNCH_FAILURE if generator failed to launch kernel \n
 * - HIPRAND_STATUS_SUCCESS if random numbers were successfully generated \n
 */
hiprandStatus_t HIPRANDAPI
hiprandGenerateLogNormal(hiprandGenerator_t generator,
                         float * output_data, size_t n,
                         float mean, float stddev);

/**
 * \brief Generates log-normally distributed doubles.
 *
 * Generates \p n log-normally distributed 64-bit double-precision floating-point
 * values and saves them to \p output_data.
 *
 * \param generator - Generator to use
 * \param output_data - Pointer to memory to store generated numbers
 * \param n - Number of doubles to generate
 * \param mean - Mean value of log normal distribution
 * \param stddev - Standard deviation value of log normal distribution
 *
 * \return
 * - HIPRAND_STATUS_NOT_INITIALIZED if the generator was not initialized \n
 * - HIPRAND_STATUS_LAUNCH_FAILURE if generator failed to launch kernel \n
 * - HIPRAND_STATUS_SUCCESS if random numbers were successfully generated \n
 */
hiprandStatus_t HIPRANDAPI
hiprandGenerateLogNormalDouble(hiprandGenerator_t generator,
                               double * output_data, size_t n,
                               double mean, double stddev);

/**
 * \brief Generates Poisson-distributed 32-bit unsigned integers.
 *
 * Generates \p n Poisson-distributed 32-bit unsigned integers and
 * saves them to \p output_data.
 *
 * \param generator - Generator to use
 * \param output_data - Pointer to memory to store generated numbers
 * \param n - Number of 32-bit unsigned integers to generate
 * \param lambda - lambda for the Poisson distribution
 *
 * \return
 * - HIPRAND_STATUS_NOT_INITIALIZED if the generator was not initialized \n
 * - HIPRAND_STATUS_LAUNCH_FAILURE if generator failed to launch kernel \n
 * - HIPRAND_STATUS_OUT_OF_RANGE if lambda is non-positive \n
 * - HIPRAND_STATUS_SUCCESS if random numbers were successfully generated \n
 */
hiprandStatus_t HIPRANDAPI
hiprandGeneratePoisson(hiprandGenerator_t generator,
                       unsigned int * output_data, size_t n,
                       double lambda);

/**
 * \brief Sets the current stream for kernel launches.
 *
 * Sets the current stream for all kernel launches of the generator.
 * All functions will use this stream.
 *
 * \param generator - Generator to modify
 * \param stream - Stream to use or NULL for default stream
 *
 * \return
 * - HIPRAND_STATUS_NOT_INITIALIZED if the generator was not initialized \n
 * - HIPRAND_STATUS_SUCCESS if stream was set successfully \n
 */
hiprandStatus_t HIPRANDAPI
hiprandSetStream(hiprandGenerator_t generator, hipStream_t stream);

/**
 * \brief Sets the seed of the pseudo-random number generator.
 *
 * Sets the seed of the pseudorandom number generator. This operation
 * resets generator's internal state.
 *
 * \param generator - Generator to modify
 * \param seed - Seed value
 *
 * \return
 * - HIPRAND_STATUS_NOT_INITIALIZED if the generator was not initialized \n
 * - HIPRAND_STATUS_TYPE_ERROR if the generator is a quasirandom number generator \n
 * - HIPRAND_STATUS_SUCCESS if seed was set successfully \n
 */
hiprandStatus_t HIPRANDAPI
hiprandSetPseudoRandomGeneratorSeed(hiprandGenerator_t generator, unsigned long long seed);

/**
 * \brief Sets the offset of the random number generator.
 *
 * Sets the absolute offset of the random number generator. This operation
 * resets generator's internal state.
 *
 * \param generator - Generator to modify
 * \param offset - Absolute offset
 *
 * \return
 * - HIPRAND_STATUS_NOT_INITIALIZED if the generator was not initialized \n
 * - HIPRAND_STATUS_SUCCESS if offset was successfully set \n
 */
hiprandStatus_t HIPRANDAPI
hiprandSetGeneratorOffset(hiprandGenerator_t generator, unsigned long long offset);

/**
 * \brief Returns the version number of the library.
 *
 * Returns in \p version the version number of the underlying dynamically
 * linked cuRAND or rocRAND library.
 *
 * \param version - Version of the library
 *
 * \return
 * - HIPRAND_STATUS_OUT_OF_RANGE if \p version is NULL \n
 * - HIPRAND_STATUS_SUCCESS if the version number was successfully returned \n
 */
hiprandStatus_t HIPRANDAPI
hiprandGetVersion(int * version);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif // HIPRAND_H_
