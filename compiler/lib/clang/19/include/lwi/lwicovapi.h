//
// (c) 2022 Qualcomm Innovation Center, Inc. All rights reserved.
//

#ifndef LWICOVAPI_H
#define LWICOVAPI_H

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

enum LWIErrorCode {
  LWI_ERR_SUCCESS = 0,
  LWI_ERR_INVALID_PARAMETER = -1,
  LWI_ERR_NOT_INITIALIZED = -2,
  LWI_ERR_ALREADY_INITIALIZED = -3,
  LWI_ERR_NOT_IMPLEMENTED = -4,
};

enum {
  LWI_FLAG_TRUNCATED = 1 << 0, /// The coverage data was truncated
  LWI_FLAG_INDEXES = 1 << 1,   /// Indexes are used as identifiers
};

#pragma GCC visibility push(default)

/** Initialize the coverage handler and enable
 * collecting coverage information.
 * @return One of the LWI_ERR_* values.
 */
enum LWIErrorCode lwicov_init(void);

/** Initialize the coverage handler with user-provided memory buffer and enable
 * collecting coverage information.
 * @param buffer_size Size of the memory buffer
 * @param buffer user-allocated memory buffer
 * @return One of the LWI_ERR_* values.
 */
enum LWIErrorCode lwicov_init_ext_mem(size_t buffer_size, void *buffer);

/** Estimate the size of memory buffer required to collect coverage information
 * for the current executable.
 * @param buffer_size Size of the memory buffer
 * @return One of the LWI_ERR_* values.
 */
enum LWIErrorCode lwicov_get_ext_mem_size(size_t *buffer_size);

/** Disable coverage data collection.
 * @return One of the LWI_ERR_* values.
 */
enum LWIErrorCode lwicov_done(void);

/** Test if coverage data collection is active.
 * @return non-zero value if data collection is currently active, zero
 * otherwise.
 */
int lwicov_is_active(void);

/** Read current coverage state flags.
 * @param flags pointer to the returned value
 * @return non-zero value if data collection is currently active, zero
 * otherwise.
 */
enum LWIErrorCode lwicov_read_current_flags(uint32_t *flags);

/** Output callback function.
 * @param probe_id fingerprint value
 * @param arg argument supplied by the user in lwicov_report */
typedef void (*lwicov_callback_t)(uint32_t probe_id, void *arg);

/** Report all collected identifiers using a user-suplied callback function.
 * @param cb callback function
 * @cb_arg user argument
 * @return One of the LWI_ERR_* values. */
enum LWIErrorCode lwicov_report(lwicov_callback_t cb, void *cb_arg);

/** Save the current coverage data to a file.
 * @param file to save to.
 * @return One of the LWI_ERR_* values.
 */
enum LWIErrorCode lwicov_save(FILE *);

/** Obtain the pointer to the internal buffer used for coverage data collection
 * and its size. This function may not be defined for all implementations and
 * the format of the buffer is also implementation-defined.
 * @buffer Pointer to the internal buffer.
 * @size_bytes Size of the buffer, in bytes.
 */
enum LWIErrorCode lwicov_internal_get_buffer(void **buffer, size_t *size_bytes);

#pragma GCC visibility pop

#ifdef __cplusplus
}
#endif

#endif
