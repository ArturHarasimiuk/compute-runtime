#
# Copyright (C) 2019-2020 Intel Corporation
#
# SPDX-License-Identifier: MIT
#

set(NEO_CORE_KERNEL
  ${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.txt
  ${CMAKE_CURRENT_SOURCE_DIR}/dispatch_kernel_encoder_interface.h
  ${CMAKE_CURRENT_SOURCE_DIR}/grf_config.h
)

set_property(GLOBAL PROPERTY NEO_CORE_KERNEL ${NEO_CORE_KERNEL})
add_subdirectories()
