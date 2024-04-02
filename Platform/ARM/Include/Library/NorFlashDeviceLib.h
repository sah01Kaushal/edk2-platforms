/** @file  NorFlashDeviceLib.h

  Copyright (c) 2011 - 2024, Arm Limited. All rights reserved.<BR>

  SPDX-License-Identifier: BSD-2-Clause-Patent

**/

#ifndef NOR_FLASH_DEVICE_LIB_H_
#define NOR_FLASH_DEVICE_LIB_H_

#include <Protocol/BlockIo.h>
#include <Protocol/DiskIo.h>
#include <Protocol/FirmwareVolumeBlock.h>

typedef struct _NOR_FLASH_INSTANCE NOR_FLASH_INSTANCE;

#define GET_NOR_BLOCK_ADDRESS(BaseAddr, Lba, LbaSize)  ( BaseAddr + (UINTN)((Lba) * LbaSize) )

#pragma pack (1)
typedef struct {
  VENDOR_DEVICE_PATH          Vendor;
  UINT8                       Index;
  EFI_DEVICE_PATH_PROTOCOL    End;
} NOR_FLASH_DEVICE_PATH;
#pragma pack ()

struct _NOR_FLASH_INSTANCE {
  UINT32                                 Signature;
  EFI_HANDLE                             Handle;

  UINTN                                  HostRegisterBaseAddress;
  UINTN                                  DeviceBaseAddress;
  UINTN                                  RegionBaseAddress;
  UINTN                                  Size;
  EFI_LBA                                StartLba;

  EFI_BLOCK_IO_PROTOCOL                  BlockIoProtocol;
  EFI_BLOCK_IO_MEDIA                     Media;
  EFI_DISK_IO_PROTOCOL                   DiskIoProtocol;

  EFI_FIRMWARE_VOLUME_BLOCK2_PROTOCOL    FvbProtocol;
  VOID                                   *ShadowBuffer;

  NOR_FLASH_DEVICE_PATH                  DevicePath;
};

EFI_STATUS
NorFlashReadCfiData (
  IN  UINTN   DeviceBaseAddress,
  IN  UINTN   CFI_Offset,
  IN  UINT32  NumberOfBytes,
  OUT UINT32  *Data
  );

EFI_STATUS
NorFlashWriteBuffer (
  IN NOR_FLASH_INSTANCE  *Instance,
  IN UINTN               TargetAddress,
  IN UINTN               BufferSizeInBytes,
  IN UINT32              *Buffer
  );

EFI_STATUS
NorFlashWriteFullBlock (
  IN NOR_FLASH_INSTANCE  *Instance,
  IN EFI_LBA             Lba,
  IN UINT32              *DataBuffer,
  IN UINT32              BlockSizeInWords
  );

EFI_STATUS
NorFlashUnlockAndEraseSingleBlock (
  IN NOR_FLASH_INSTANCE  *Instance,
  IN UINTN               BlockAddress
  );

EFI_STATUS
NorFlashWriteSingleBlock (
  IN        NOR_FLASH_INSTANCE  *Instance,
  IN        EFI_LBA             Lba,
  IN        UINTN               Offset,
  IN OUT    UINTN               *NumBytes,
  IN        UINT8               *Buffer
  );

EFI_STATUS
NorFlashWriteBlocks (
  IN  NOR_FLASH_INSTANCE  *Instance,
  IN  EFI_LBA             Lba,
  IN  UINTN               BufferSizeInBytes,
  IN  VOID                *Buffer
  );

EFI_STATUS
NorFlashReadBlocks (
  IN NOR_FLASH_INSTANCE  *Instance,
  IN EFI_LBA             Lba,
  IN UINTN               BufferSizeInBytes,
  OUT VOID               *Buffer
  );

EFI_STATUS
NorFlashRead (
  IN NOR_FLASH_INSTANCE  *Instance,
  IN EFI_LBA             Lba,
  IN UINTN               Offset,
  IN UINTN               BufferSizeInBytes,
  OUT VOID               *Buffer
  );

EFI_STATUS
NorFlashWrite (
  IN        NOR_FLASH_INSTANCE  *Instance,
  IN        EFI_LBA             Lba,
  IN        UINTN               Offset,
  IN OUT    UINTN               *NumBytes,
  IN        UINT8               *Buffer
  );

EFI_STATUS
NorFlashReset (
  IN  NOR_FLASH_INSTANCE  *Instance
  );

EFI_STATUS
NorFlashEraseSingleBlock (
  IN NOR_FLASH_INSTANCE  *Instance,
  IN UINTN               BlockAddress
  );

EFI_STATUS
NorFlashUnlockSingleBlockIfNecessary (
  IN NOR_FLASH_INSTANCE  *Instance,
  IN UINTN               BlockAddress
  );

EFI_STATUS
NorFlashWriteSingleWord (
  IN NOR_FLASH_INSTANCE  *Instance,
  IN UINTN               WordAddress,
  IN UINT32              WriteData
  );

VOID
EFIAPI
NorFlashLock (
  IN EFI_TPL  *OriginalTPL
  );

VOID
EFIAPI
NorFlashUnlock (
  IN EFI_TPL  OriginalTPL
  );

#endif /* NOR_FLASH_DEVICE_LIB_H_ */
