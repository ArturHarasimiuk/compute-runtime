/*
 * Copyright (C) 2017-2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "core/helpers/hw_helper.h"
#include "runtime/aub_mem_dump/aub_alloc_dump.inl"
#include "runtime/aub_mem_dump/aub_mem_dump.inl"

#include "aub_mapper.h"

namespace AubMemDump {

enum {
    device = DeviceValues::Bdw
};

// Instantiate these common template implementations.
template struct AubDump<Traits<device, 32>>;
template struct AubDump<Traits<device, 48>>;

template struct AubPageTableHelper32<Traits<device, 32>>;
template struct AubPageTableHelper64<Traits<device, 48>>;
} // namespace AubMemDump

namespace NEO {
using Family = BDWFamily;

static const AubMemDump::LrcaHelperRcs rcs(0x002000);
static const AubMemDump::LrcaHelperBcs bcs(0x022000);
static const AubMemDump::LrcaHelperVcs vcs(0x012000);
static const AubMemDump::LrcaHelperVecs vecs(0x01a000);

const AubMemDump::LrcaHelper *const AUBFamilyMapper<Family>::csTraits[aub_stream::NUM_ENGINES] = {
    &rcs,
    &bcs,
    &vcs,
    &vecs};

const MMIOList AUBFamilyMapper<Family>::globalMMIO;

static const MMIOList mmioListRCS = {
    MMIOPair(0x000020d8, 0x00020000),
    MMIOPair(AubMemDump::computeRegisterOffset(rcs.mmioBase, 0x229c), 0xffff8280),
};

static const MMIOList mmioListBCS = {
    MMIOPair(AubMemDump::computeRegisterOffset(bcs.mmioBase, 0x229c), 0xffff8280),
};

static const MMIOList mmioListVCS = {
    MMIOPair(AubMemDump::computeRegisterOffset(vcs.mmioBase, 0x229c), 0xffff8280),
};

static const MMIOList mmioListVECS = {
    MMIOPair(AubMemDump::computeRegisterOffset(vecs.mmioBase, 0x229c), 0xffff8280),
};

const MMIOList *AUBFamilyMapper<Family>::perEngineMMIO[aub_stream::NUM_ENGINES] = {
    &mmioListRCS,
    &mmioListBCS,
    &mmioListVCS,
    &mmioListVECS};
} // namespace NEO

namespace AubAllocDump {
using namespace NEO;

template SurfaceInfo *getDumpSurfaceInfo<Family>(GraphicsAllocation &gfxAllocation, DumpFormat dumpFormat);

template uint32_t getImageSurfaceTypeFromGmmResourceType<Family>(GMM_RESOURCE_TYPE gmmResourceType);

template void dumpBufferInBinFormat<Family>(GraphicsAllocation &gfxAllocation, AubMemDump::AubFileStream *stream, uint32_t context);

template void dumpImageInBmpFormat<Family>(GraphicsAllocation &gfxAllocation, AubMemDump::AubFileStream *stream, uint32_t context);

template void dumpBufferInTreFormat<Family>(GraphicsAllocation &gfxAllocation, AubMemDump::AubFileStream *stream, uint32_t context);

template void dumpImageInTreFormat<Family>(GraphicsAllocation &gfxAllocation, AubMemDump::AubFileStream *stream, uint32_t context);

template void dumpAllocation<Family>(DumpFormat dumpFormat, GraphicsAllocation &gfxAllocation, AubMemDump::AubFileStream *stream, uint32_t context);
} // namespace AubAllocDump
