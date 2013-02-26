#ifndef TYPES_H
#define TYPES_H

#include <Python.h>

#include <limits.h>
#include <stdint.h>

#if UINT64_MAX == ULONG_MAX
#define PYT_UINT64 T_ULONG
#define PYT_SINT64 T_LONG
#elif UINT64_MAX == ULLONG_MAX
#define PYT_UINT64 T_ULONGLONG
#define PYT_SINT64 T_LONGLONG
#else
#error "Don't know how to define PYT_(U|S)INT64"
#endif

#if UINT32_MAX == UINT_MAX
#define PYT_UINT32 T_UINT
#define PYT_SINT32 T_INT
#else
#error "Don't know how to define PYT_(U|S)INT32"
#endif

#if UINT16_MAX == USHRT_MAX
#define PYT_UINT16 T_USHORT
#define PYT_SINT16 T_SHORT
#else
#error "Don't know how to define PYT_(U|S)INT16"
#endif

#define PYT_UINT8 T_UBYTE
#define PYT_SINT8 T_BYTE

#define PY_usf_event_type_t PYT_UINT8
#define PY_usf_line_size_2_t PYT_UINT8

#define PY_usf_version_t PYT_UINT16
#define PY_usf_compression_t PYT_UINT16
#define PY_usf_flags_t PYT_UINT32
#define PY_usf_wtime_t PYT_UINT64
#define PY_usf_line_size_mask_t PYT_UINT32

#define PY_usf_addr_t PYT_UINT64
#define PY_usf_atime_t PYT_UINT64
#define PY_usf_tid_t PYT_UINT16
#define PY_usf_alen_t PYT_UINT16
#define PY_usf_atype_t PYT_UINT8
#define PY_usf_operand_t PYT_UINT8

#define USF_TYPE(t) PY_ ## t

#endif
