# ##############################################################################
# libs/libm/libm/CMakeLists.txt
#
# SPDX-License-Identifier: Apache-2.0
#
# Licensed to the Apache Software Foundation (ASF) under one or more contributor
# license agreements.  See the NOTICE file distributed with this work for
# additional information regarding copyright ownership.  The ASF licenses this
# file to you under the Apache License, Version 2.0 (the "License"); you may not
# use this file except in compliance with the License.  You may obtain a copy of
# the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
# WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
# License for the specific language governing permissions and limitations under
# the License.
#
# ##############################################################################
if(CONFIG_LIBM)

  if(CONFIG_ARCH_ARM)
    nuttx_add_subdirectory(arm)
  endif()

  # Add the floating point math C files to the build
  set(SRCS
      lib_acosf.c
      lib_asinf.c
      lib_atan2f.c
      lib_atanf.c
      lib_cosf.c
      lib_coshf.c
      lib_expf.c
      lib_fmodf.c
      lib_fmax.c
      lib_fmin.c
      lib_fminf.c
      lib_fmaxf.c
      lib_frexpf.c
      lib_ldexpf.c
      lib_logf.c
      lib_log10f.c
      lib_log2f.c
      lib_modff.c
      lib_powf.c
      lib_sinf.c
      lib_sinhf.c
      lib_tanf.c
      lib_tanhf.c
      lib_asinhf.c
      lib_acoshf.c
      lib_atanhf.c
      lib_erff.c
      lib_copysignf.c
      lib_scalbnf.c
      lib_scalbn.c
      lib_scalbnl.c
      lib_sincos.c
      lib_sincosf.c
      lib_sincosl.c
      lib_acos.c
      lib_asin.c
      lib_atan.c
      lib_atan2.c
      lib_cos.c
      lib_cosh.c
      lib_exp.c
      lib_fabs.c
      lib_fmod.c
      lib_frexp.c
      lib_ldexp.c
      lib_log.c
      lib_log10.c
      lib_log2.c
      lib_modf.c
      lib_pow.c
      lib_sin.c
      lib_sinh.c
      lib_sqrt.c
      lib_tan.c
      lib_tanh.c
      lib_asinh.c
      lib_acosh.c
      lib_atanh.c
      lib_erf.c
      lib_copysign.c
      lib_cbrt.c
      lib_acosl.c
      lib_asinl.c
      lib_atan2l.c
      lib_atanl.c
      lib_ceill.c
      lib_cosl.c
      lib_coshl.c
      lib_expl.c
      lib_fabsl.c
      lib_floorl.c
      lib_fmodl.c
      lib_frexpl.c
      lib_ldexpl.c
      lib_logl.c
      lib_log10l.c
      lib_log2l.c
      lib_modfl.c
      lib_powl.c
      lib_rintl.c
      lib_roundl.c
      lib_sinl.c
      lib_sinhl.c
      lib_sqrtl.c
      lib_tanl.c
      lib_tanhl.c
      lib_asinhl.c
      lib_acoshl.c
      lib_atanhl.c
      lib_erfl.c
      lib_copysignl.c
      lib_truncl.c
      lib_libexpi.c
      lib_libsqrtapprox.c
      lib_libexpif.c
      lib_erfc.c
      lib_erfcf.c
      lib_erfcl.c
      lib_expm1.c
      lib_expm1f.c
      lib_expm1l.c
      lib_lround.c
      lib_lroundf.c
      lib_lroundl.c
      lib_llround.c
      lib_llroundf.c
      lib_llroundl.c
      lib_nan.c
      lib_nanf.c
      lib_nanl.c
      lib_fmax.c
      lib_fmaxf.c
      lib_fmaxl.c
      lib_fmin.c
      lib_fminf.c
      lib_fminl.c
      __cos.c
      __sin.c
      lib_gamma.c
      lib_lgamma.c)

  # Use the C versions of some functions only if architecture specific optimized
  # versions are not provided.

  if(NOT CONFIG_LIBM_ARCH_CEIL)
    list(APPEND SRCS lib_ceil.c)
  endif()

  if(NOT CONFIG_LIBM_ARCH_FLOOR)
    list(APPEND SRCS lib_floor.c)
  endif()

  if(NOT CONFIG_LIBM_ARCH_RINT)
    list(APPEND SRCS lib_rint.c)
  endif()

  if(NOT CONFIG_LIBM_ARCH_ROUND)
    list(APPEND SRCS lib_round.c)
  endif()

  if(NOT CONFIG_LIBM_ARCH_TRUNC)
    list(APPEND SRCS lib_trunc.c)
  endif()

  if(NOT CONFIG_LIBM_ARCH_CEILF)
    list(APPEND SRCS lib_ceilf.c)
  endif()

  if(NOT CONFIG_LIBM_ARCH_FLOORF)
    list(APPEND SRCS lib_floorf.c)
  endif()

  if(NOT CONFIG_LIBM_ARCH_RINTF)
    list(APPEND SRCS lib_rintf.c)
  endif()

  if(NOT CONFIG_LIBM_ARCH_ROUNDF)
    list(APPEND SRCS lib_roundf.c)
  endif()

  if(NOT CONFIG_LIBM_ARCH_TRUNCF)
    list(APPEND SRCS lib_truncf.c)
  endif()

  if(NOT CONFIG_LIBM_ARCH_FABSF)
    list(APPEND SRCS lib_fabsf.c)
  endif()

  if(NOT CONFIG_LIBM_ARCH_SQRTF)
    list(APPEND SRCS lib_sqrtf.c)
  endif()

  target_sources(c PRIVATE ${SRCS})
endif()
